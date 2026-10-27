#include "wifi_setup/wifi_setup_app.h"

#include "global.h"

#include "dwc/dwc_bm_internal.h"
#include "wifi_setup/wifi_setup_access_points.h"
#include "wifi_setup/wifi_setup_screens.h"

#include <nitro/code32.h>

// Access-point setup screens, application core: the setup client request, the entry point and its main loop, text
// banks and the session started from the screens.

extern void GXx_SetMasterBrightness_(vu16 *reg, int brightness);

static void *WifiSetupApp_AossClientAlloc(u32 size);
static void WifiSetupApp_AossClientFree(void *ptr);
static BOOL WifiSetupApp_SetParams(int language, u32 flags);
static void WifiSetupApp_InitSystem(void);
static void WifiSetupApp_InitDisplay(void);
static void WifiSetupApp_Shutdown(void);
static u8 WifiSetupApp_GetLanguageCode(void);
static void WifiSetupTransfer_CancelTask(WifiSetupTask *task, void *arg);
static void WifiSetupTransfer_Task(WifiSetupTask *task, void *arg);

// Starts the setup client: requests settings WEP64 and WEP128 with the setup key, one connection attempt and
// one receive attempt with default timing, from this console's MAC address.
void WifiSetupApp_StartAossClient(void) {
    WifiSetupRequestKey key;
    gWifiSetupClient.request = WifiSetupHeap_AllocZeroed(sizeof(WifiSetupRequest), 4);
    gWifiSetupClient.done = FALSE;
    MI_CpuClear16(&key, sizeof(key));
    key.tag = 'P';
    key.length = 12;
    MI_CpuCopy8(gWifiSetupAossClientName, key.data, 12);
    gWifiSetupClient.request->requestMask = WIFI_SETUP_AOSS_SETTING_WEP64 | WIFI_SETUP_AOSS_SETTING_WEP128;
    gWifiSetupClient.request->key = key;
    gWifiSetupClient.request->connectRetries = 1;
    gWifiSetupClient.request->connectDelay = -1;
    gWifiSetupClient.request->receiveRetries = 1;
    gWifiSetupClient.request->receiveDelay = -1;
    gWifiSetupClient.request->receiveTimeout = -1;
    OS_GetMacAddress(gWifiSetupClient.request->macAddress);
    if (WifiSetup_Startup(WifiSetupApp_AossClientAlloc, WifiSetupApp_AossClientFree)) {
        OS_Terminate();
    }
}

// Stops the setup client; with `apply`, the settings it received are taken over.
void WifiSetupApp_StopAossClient(BOOL apply) {
    WifiSetup_Cleanup();
    if (apply && gWifiSetupClient.request->error == WIFI_SETUP_AOSS_REQUEST_OK && gWifiSetupClient.done == TRUE) {
        WifiSetupConnections_SetFromInfo(&gWifiSetupClient.request->result);
    }
    WifiSetupHeap_FreeAndClear(&ov13_0224F4C8);
}

int WifiSetupApp_PollAossClient(void) {
    u32 error;
    if (!WifiSetup_RunAoss(gWifiSetupClient.request)) {
        gWifiSetupClient.done = TRUE;
        return WIFI_SETUP_CLIENT_DONE;
    }
    error = gWifiSetupClient.request->error;
    if (error == 1 || (u8)(error + 253) <= 2) { // not found yet, or a step timed out (1, 3-5)
        return WIFI_SETUP_CLIENT_BUSY;
    }
    return WIFI_SETUP_CLIENT_FAILED;
}

static void *WifiSetupApp_AossClientAlloc(u32 size) {
    return WifiSetupHeap_AllocZeroed(size, 32);
}

static void WifiSetupApp_AossClientFree(void *ptr) {
    WifiSetupHeap_Free(ptr);
}

// Entry point: runs the setup screens in `heap` until they exit. Returns -1 for invalid parameters.
int WifiSetupApp_Run(void *heap, s32 language, s32 flags) {
    gWifiSetupApp.heap = heap;
    if (!WifiSetupApp_SetParams(language, flags)) {
        return -1;
    }
    gWifiSetupApp.exit = FALSE;
    WifiSetupApp_InitSystem();
    WifiSetupApp_InitDisplay();
    WifiSetupSound_Init();
    WifiSetupApp_SetStateFunc(WifiSetupScreens_Init);
    do {
        WifiSetupInput_Update();
        gWifiSetupApp.stateFunc();
        WifiSetupTask_RunQueue(WIFI_SETUP_TASK_QUEUE_MAIN);
        WifiSetupInput_UpdateLcdPower();
        WifiSetupLed_SetWirelessPattern();
        OS_WaitVBlankIntr();
    } while (!gWifiSetupApp.exit);
    WifiSetupApp_Shutdown();
    return 0;
}

static BOOL WifiSetupApp_SetParams(int language, u32 flags) {
    gWifiSetupApp.language = language;
    gWifiSetupApp.flags.raw = flags;
    if (language < 0 || language > 6) {
        return FALSE;
    }
    if (language == 1 && ((flags >> 4) & ~2) != 0) {
        return FALSE;
    }
    if (gWifiSetupApp.flags.bits.kind > WIFI_SETUP_KIND_CONNECTION_LIST) {
        return FALSE;
    }
    if (language != 0 && (gWifiSetupApp.flags.bits.options & 1)) {
        return FALSE;
    }
    if (language == 0 && !(gWifiSetupApp.flags.bits.options & 1)) {
        return FALSE;
    }
    return TRUE;
}

static void WifiSetupApp_InitSystem(void) {
    void *work;
    (void)OS_DisableIrq();
    GX_DispOff();
    GXS_DispOff();
    if (!OS_IsTickAvailable()) {
        OS_Terminate();
    }
    if (!OS_IsAlarmAvailable()) {
        OS_Terminate();
    }
    GX_VBlankIntr(FALSE);
    FX_Init();
    FS_Init(FS_DMA_NOT_USE);
    TP_Init();
    RTC_Init();
    GX_DispOff();
    GXS_DispOff();
    WifiSetup_SaveVramBanks();
    WifiSetupHeap_Init(gWifiSetupApp.heap);
    WifiSetup_InstallVBlankIntr();
    WifiSetupTask_InitScheduler();
    WifiSetupArchive_Load();
    WifiSetupInput_Init();
    WifiSetupFade_Init();
    work = WifiSetupHeap_AllocZeroed(0x700, 32);
    DWC_BM_Init(work);
    WifiSetupHeap_FreeAndClear(&work);
}

// Main screen: BG mode 0, BG VRAM bank A, OBJ bank B (1D mapping); sub screen: banks H and I.
static void WifiSetupApp_InitDisplay(void) {
    GX_VBlankIntr(FALSE);
    GX_SetBankForBG(GX_VRAM_BG_128_A);
    GX_SetBankForOBJ(GX_VRAM_OBJ_128_B);
    GX_SetGraphicsMode(GX_DISPMODE_GRAPHICS, GX_BGMODE_0, GX_BG0_AS_2D);
    GX_SetVisiblePlane(0);
    GX_SetVisibleWnd(0);
    GXx_SetMasterBrightness_(&reg_GX_MASTER_BRIGHT, 0);
    GX_SetOBJVRamModeChar(GX_OBJVRAMMODE_CHAR_1D_128K);
    G2_BG0Mosaic(FALSE);
    G2_BG1Mosaic(FALSE);
    G2_BG2Mosaic(FALSE);
    G2_BG3Mosaic(FALSE);
    G2_SetBG0Offset(0, 0);
    G2_SetBG1Offset(0, 0);
    G2_SetBG2Offset(0, 0);
    G2_SetBG3Offset(0, 0);
    G2x_SetBlendBrightness_(&reg_G2_BLDCNT, 63, 16);
    GX_SetBankForSubBG(GX_VRAM_SUB_BG_32_H);
    GX_SetBankForSubOBJ(GX_VRAM_SUB_OBJ_16_I);
    GXS_SetGraphicsMode(GX_BGMODE_0);
    GXS_SetVisiblePlane(0);
    GXS_SetVisibleWnd(0);
    GXx_SetMasterBrightness_(&reg_GXS_DB_MASTER_BRIGHT, 0);
    GXS_SetOBJVRamModeChar(GX_OBJVRAMMODE_CHAR_1D_32K);
    G2S_BG0Mosaic(FALSE);
    G2S_BG1Mosaic(FALSE);
    G2S_BG2Mosaic(FALSE);
    G2S_BG3Mosaic(FALSE);
    G2S_SetBG0Offset(0, 0);
    G2S_SetBG1Offset(0, 0);
    G2S_SetBG2Offset(0, 0);
    G2S_SetBG3Offset(0, 0);
    G2x_SetBlendBrightness_(&reg_G2S_DB_BLDCNT, 63, 16);
    G2_SetBG0Control(GX_BG_SCRSIZE_TEXT_256x256, GX_BG_COLORMODE_16, GX_BG_SCRBASE_0x6000, GX_BG_CHARBASE_0x00000, GX_BG_EXTPLTT_01);
    G2_SetBG1Control(GX_BG_SCRSIZE_TEXT_256x256, GX_BG_COLORMODE_16, GX_BG_SCRBASE_0x6800, GX_BG_CHARBASE_0x08000, GX_BG_EXTPLTT_01);
    G2_SetBG2ControlText(GX_BG_SCRSIZE_TEXT_256x256, GX_BG_COLORMODE_16, GX_BG_SCRBASE_0x7000, GX_BG_CHARBASE_0x10000);
    G2_SetBG3ControlText(GX_BG_SCRSIZE_TEXT_256x256, GX_BG_COLORMODE_16, GX_BG_SCRBASE_0x7800, GX_BG_CHARBASE_0x10000);
    G2S_SetBG0Control(GX_BG_SCRSIZE_TEXT_256x256, GX_BG_COLORMODE_16, GX_BG_SCRBASE_0x6000, GX_BG_CHARBASE_0x00000, GX_BG_EXTPLTT_01);
    G2S_SetBG1Control(GX_BG_SCRSIZE_TEXT_256x256, GX_BG_COLORMODE_16, GX_BG_SCRBASE_0x6800, GX_BG_CHARBASE_0x00000, GX_BG_EXTPLTT_01);
    G2S_SetBG2ControlText(GX_BG_SCRSIZE_TEXT_256x256, GX_BG_COLORMODE_16, GX_BG_SCRBASE_0x7000, GX_BG_CHARBASE_0x00000);
    G2S_SetBG3ControlText(GX_BG_SCRSIZE_TEXT_256x256, GX_BG_COLORMODE_16, GX_BG_SCRBASE_0x7800, GX_BG_CHARBASE_0x00000);
    GX_SetBGScrOffset(GX_BGSCROFFSET_0x00000);
    GX_SetBGCharOffset(GX_BGCHAROFFSET_0x00000);
    GX_SetDispSelect(GX_DISP_SELECT_SUB_MAIN);
    WifiSetupText_Init();
    WifiSetupOam_Init();
    WifiSetupCharVram_Init();
    WifiSetupOamBlock_InitManager();
    GX_DispOn();
    GXS_DispOn();
    GX_VBlankIntr(TRUE);
}

static void WifiSetupApp_Shutdown(void) {
    GX_DispOff();
    GXS_DispOff();
    WifiSetupLed_SetOn();
    WifiSetupInput_Free();
    WifiSetup_RestoreVBlankIntr();
    WifiSetupSound_Free();
    WifiSetupOamBlock_FreeManager();
    WifiSetupOam_Free();
    WifiSetupText_Free();
    WifiSetupFade_Free();
    WifiSetupArchive_Unload();
    WifiSetupTask_FreeScheduler();
    WifiSetupHeap_Destroy();
    WifiSetup_RestoreVramBanks();
}

void WifiSetupApp_SetStateFunc(WifiSetupAppStateFunc func) {
    gWifiSetupApp.stateFunc = func;
}

void WifiSetupApp_SetTransition(enum WifiSetupBannerMode bannerMode, enum WifiSetupButtonBarMode buttonBarMode) {
    gWifiSetupApp.bannerMode = bannerMode;
    gWifiSetupApp.buttonBarMode = buttonBarMode;
}

void WifiSetupApp_GetTransition(enum WifiSetupBannerMode *bannerMode, enum WifiSetupButtonBarMode *buttonBarMode) {
    if (bannerMode != NULL) {
        *bannerMode = gWifiSetupApp.bannerMode;
    }
    if (buttonBarMode != NULL) {
        *buttonBarMode = gWifiSetupApp.buttonBarMode;
    }
}

void WifiSetupApp_SetScreenArgs(int arg0, int arg1) {
    gWifiSetupApp.screenArg0 = arg0;
    gWifiSetupApp.screenArg1 = arg1;
}

void WifiSetupApp_GetScreenArgs(int *arg0, int *arg1) {
    if (arg0 != NULL) {
        *arg0 = gWifiSetupApp.screenArg0;
    }
    if (arg1 != NULL) {
        *arg1 = gWifiSetupApp.screenArg1;
    }
}

u8 WifiSetupApp_GetLanguage(void) {
    return gWifiSetupApp.language;
}

u32 WifiSetupApp_GetKind(void) {
    return gWifiSetupApp.flags.bits.kind;
}

BOOL WifiSetupApp_HasOption(u32 mask) {
    return (mask & gWifiSetupApp.flags.bits.options) ? TRUE : FALSE;
}

void WifiSetupApp_Exit(void) {
    gWifiSetupApp.exit = TRUE;
}

// Character naming the language's files: '1' + language, with two exceptions.
static u8 WifiSetupApp_GetLanguageCode(void) {
    u8 language = gWifiSetupApp.language;
    if (language == 6) {
        return '8';
    }
    if (language == 1 && !(gWifiSetupApp.flags.bits.options & 2)) {
        return '7';
    }
    return language + '1';
}

void WifiSetupText_InitBanks(void) {
    gWifiSetupTextBanks = WifiSetupHeap_AllocZeroed(sizeof(WifiSetupTextBanks), 4);
    gWifiSetupTextBanks->pool = WifiSetupPool_NewWithItems(8, gWifiSetupTextBanks, sizeof(WifiSetupTextBank));
}

void WifiSetupText_FreeBanks(void) {
    WifiSetupHeap_FreeAndClear(&gWifiSetupTextBanks);
}

WifiSetupTextBank *WifiSetupText_LoadBank(const char *path) {
    u32 size;
    WifiSetupTextBank *bank = WifiSetupPool_Pop(gWifiSetupTextBanks->pool);
    WifiSetupMessageFile *file = WifiSetupFile_Load(path, &size, 4);
    WifiSetupMessageInfo *info;
    bank->file = file;
    info = &file->info;
    bank->offsets = info->offsets;
    bank->strings = (u8 *)info + info->size + 8;
    return bank;
}

void WifiSetupText_UnloadBank(WifiSetupTextBank *bank) {
    WifiSetupFile_Free(bank->file);
    WifiSetupPool_Push(gWifiSetupTextBanks->pool, bank);
}

u16 *WifiSetupText_GetString(WifiSetupTextBank *bank, int index) {
    return (u16 *)(bank->strings + bank->offsets[(u16)index]);
}

// Returns string `index` with character `pos` (if >= 0) replaced by the digit `digit`.
u16 *WifiSetupText_GetStringWithDigit(WifiSetupTextBank *bank, u32 index, int pos, u32 digit) {
    u16 *str = (u16 *)(bank->strings + bank->offsets[(u16)index]);
    if (pos >= 0) {
        digit += '0';
        str[pos] = digit;
    }
    return str;
}

void WifiSetupTransfer_Start(WifiSetupSessionCallback callback) {
    WifiSetupSessionParams params;
    gWifiSetupSession = WifiSetupHeap_AllocZeroed(sizeof(WifiSetupSession), 32);
    gWifiSetupSession->callback = callback;
    gWifiSetupSession->missedEvent = FALSE;
    gWifiSetupSession->cancelled = FALSE;
    params = gWifiSetupTransferSessionParams;
    params.title = WifiSetupText_GetString(gWifiSetupTextBank, 0);
    params.description = WifiSetupText_GetString(gWifiSetupTextBank, 1);
    params.languageCode = WifiSetupApp_GetLanguageCode();
    WifiSetupShare_Init(&gWifiSetupSession->share, &params);
    if (!WifiSetupShare_Start()) {
        OS_Terminate();
    }
    gWifiSetupSession->task = WifiSetupTask_Create(WIFI_SETUP_TASK_QUEUE_MAIN, WifiSetupTransfer_Task, NULL, 120);
}

void WifiSetupTransfer_Cancel(void) {
    WifiSetupTask_Create(WIFI_SETUP_TASK_QUEUE_MAIN, WifiSetupTransfer_CancelTask, NULL, 120);
}

static void WifiSetupTransfer_CancelTask(WifiSetupTask *task, void *arg) {
    if (!WifiSetupShare_Cancel()) {
        return;
    }
    gWifiSetupSession->cancelled = TRUE;
    WifiSetupTask_DestroyLater(WIFI_SETUP_TASK_QUEUE_MAIN, task);
}

BOOL WifiSetupTransfer_IsFinished(void) {
    return gWifiSetupSession == NULL;
}

void WifiSetupTransfer_SetCallback(WifiSetupSessionCallback callback) {
    gWifiSetupSession->callback = callback;
}

void WifiSetupTransfer_StartDownload(void) {
    WifiSetupShare_StartDownload();
}

WifiSetupMbParentUser *WifiSetupTransfer_GetChildUser(void) {
    return &gWifiSetupSession->childUser;
}

WifiSetupSession *gWifiSetupSession;

static void WifiSetupTransfer_Task(WifiSetupTask *task, void *arg) {
    u8 state;
    u8 changed;

    WifiSetupShare_Update();
    if (gWifiSetupSession->missedEvent && !gWifiSetupSession->cancelled) {
        if (gWifiSetupSession->callback != NULL) {
            gWifiSetupSession->callback(WIFI_SETUP_TRANSFER_EVENT_CHILD_ENTERED);
        }
        return;
    }
    WifiSetupShare_GetState(&state, &changed);
    switch (state) {
    case WIFI_SETUP_SHARE_STATE_ENTRY_REQUESTED:
        if (!changed) {
            return;
        }
        {
            WifiSetupMbParentUser *dst = &gWifiSetupSession->childUser;
            WifiSetupMbParentUser *src = WifiSetupShare_GetChildUser();
            MI_CpuCopy16(src, dst, sizeof(WifiSetupMbParentUser));
        }
        if (gWifiSetupSession->callback == NULL) {
            gWifiSetupSession->missedEvent = TRUE;
            return;
        }
        gWifiSetupSession->callback(WIFI_SETUP_TRANSFER_EVENT_CHILD_ENTERED);
        return;
    case WIFI_SETUP_SHARE_STATE_ENTRY_CANCELLED:
        if (!changed) {
            return;
        }
        if (gWifiSetupSession->callback == NULL) {
            gWifiSetupSession->missedEvent = TRUE;
            return;
        }
        gWifiSetupSession->callback(WIFI_SETUP_TRANSFER_EVENT_ENTRY_CANCELLED);
        return;
    case WIFI_SETUP_SHARE_STATE_STOPPED:
    case WIFI_SETUP_SHARE_STATE_ABORTED:
        if (!changed) {
            return;
        }
        if (gWifiSetupSession->callback == NULL) {
            gWifiSetupSession->missedEvent = TRUE;
            return;
        }
        gWifiSetupSession->callback(WIFI_SETUP_TRANSFER_EVENT_STOPPED);
        return;
    case WIFI_SETUP_SHARE_STATE_FAILED:
    case WIFI_SETUP_SHARE_STATE_ERROR:
        if (!changed) {
            return;
        }
        if (gWifiSetupSession->callback == NULL) {
            gWifiSetupSession->missedEvent = TRUE;
            return;
        }
        gWifiSetupSession->callback(WIFI_SETUP_TRANSFER_EVENT_FAILED);
        return;
    case WIFI_SETUP_SHARE_STATE_DONE:
        if (!changed) {
            return;
        }
        if (gWifiSetupSession->callback == NULL) {
            gWifiSetupSession->missedEvent = TRUE;
            return;
        }
        gWifiSetupSession->callback(WIFI_SETUP_TRANSFER_EVENT_DONE);
        return;
    case WIFI_SETUP_SHARE_STATE_IDLE:
    case WIFI_SETUP_SHARE_STATE_MEASURE_CHANNEL:
    case WIFI_SETUP_SHARE_STATE_SHARING:
    case WIFI_SETUP_SHARE_STATE_CHILD_READY:
        break;
    case WIFI_SETUP_SHARE_STATE_END:
        WifiSetupTask_DestroyLater(WIFI_SETUP_TASK_QUEUE_MAIN, task);
        WifiSetupHeap_FreeAndClear(&gWifiSetupSession);
        break;
    }
}
