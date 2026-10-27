#include "wifi_setup/wifi_setup_screens.h"

#include "global.h"

#include "dwc/dwc_bm_internal.h"
#include "wifi_setup/wifi_setup_access_points.h"
#include "wifi_setup/wifi_setup_app.h"
#include "wifi_setup/wifi_setup_connection_screens.h"
#include "wifi_setup/wifi_setup_internal.h"
#include "wifi_setup/wifi_setup_keyboard.h"
#include "wifi_setup/wifi_setup_local_wireless.h"
#include "wifi_setup/wifi_setup_scroll_bar.h"
#include "wifi_setup/wifi_setup_settings.h"
#include "wifi_setup/wifi_setup_ui.h"
#include "wifi_setup/wifi_setup_ui_parts.h"

#include <nitro/code32.h>

// Access-point setup screens: setup client start/stop and status, the top menu, the message screens that follow
// it, the list screen and the text entry screen.

extern s32 FX_DivS32(s32 a, s32 b);
extern int swprintf(u16 *buf, u32 n, const u16 *fmt, ...);

static void WifiSetupClient_OnStatus(s32 *status);
static void *WifiSetupClient_Alloc(u32 size);
static void WifiSetupClient_Free(void *ptr);
static void WifiSetupScreens_Quit(void);
static void WifiSetupScreens_FadeIn(void);
static void WifiSetupScreens_WaitFadeIn(void);
static void WifiSetupTopMenu_LoadGraphics(void);
static void WifiSetupTopMenu_FadeIn(void);
static void WifiSetupTopMenu_WaitFadeIn(void);
static void WifiSetupTopMenu_WaitButtonBar(void);
static void WifiSetupTopMenu_Main(void);
static void WifiSetupTopMenu_HandleInput(void);
static void WifiSetupTopMenu_Update(void);
static void WifiSetupTopMenu_CheckButtons(void);
static void WifiSetupTopMenu_Exit(void);
static void WifiSetupTopMenu_WaitFadeOut(void);
static void WifiSetupTopMenu_End(void);
static void WifiSetupTopMenu_MoveCursor(int dir);
static void WifiSetupTopMenu_HighlightSelection(void);
static void WifiSetupEraseConfirm_Init(void);
static void WifiSetupEraseConfirm_LoadGraphics(void);
static void WifiSetupEraseConfirm_FadeIn(void);
static void WifiSetupEraseConfirm_WaitFadeIn(void);
static void WifiSetupEraseConfirm_WaitButtonBar(void);
static void WifiSetupEraseConfirm_Main(void);
static void WifiSetupEraseConfirm_HandleInput(void);
static void WifiSetupEraseConfirm_Update(void);
static void WifiSetupEraseConfirm_CheckButtons(void);
static void WifiSetupEraseConfirm_Exit(void);
static void WifiSetupEraseConfirm_WaitFadeOut(void);
static void WifiSetupEraseConfirm_End(void);
static void WifiSetupEraseConfirm_WaitDialog(void);
static void WifiSetupEraseConfirm_WaitDialogClosed(void);
static void WifiSetupEraseDone_Init(void);
static void WifiSetupEraseDone_LoadGraphics(void);
static void WifiSetupEraseDone_FadeIn(void);
static void WifiSetupEraseDone_WaitFadeIn(void);
static void WifiSetupEraseDone_WaitButtonBar(void);
static void WifiSetupEraseDone_Main(void);
static void WifiSetupEraseDone_HandleInput(void);
static void WifiSetupEraseDone_Update(void);
static void WifiSetupEraseDone_CheckButtons(void);
static void WifiSetupEraseDone_Exit(void);
static void WifiSetupEraseDone_WaitFadeOut(void);
static void WifiSetupEraseDone_PowerOff(void);
static void WifiSetupSystemInfo_Init(void);
static void WifiSetupSystemInfo_LoadGraphics(void);
static void WifiSetupSystemInfo_DrawInfo(void);
static void WifiSetupSystemInfo_FadeIn(void);
static void WifiSetupSystemInfo_WaitFadeIn(void);
static void WifiSetupSystemInfo_WaitButtonBar(void);
static void WifiSetupSystemInfo_Main(void);
static void WifiSetupSystemInfo_HandleInput(void);
static void WifiSetupSystemInfo_Update(void);
static void WifiSetupSystemInfo_CheckButtons(void);
static void WifiSetupSystemInfo_Exit(void);
static void WifiSetupSystemInfo_WaitFadeOut(void);
static void WifiSetupSystemInfo_End(void);
static void WifiSetupOptions_Init(void);
static void WifiSetupOptions_LoadGraphics(void);
static void WifiSetupOptions_FadeIn(void);
static void WifiSetupOptions_WaitFadeIn(void);
static void WifiSetupOptions_WaitButtonBar(void);
static void WifiSetupOptions_Main(void);
static void WifiSetupOptions_HandleInput(void);
static void WifiSetupOptions_Update(void);
static void WifiSetupOptions_CheckButtons(void);
static void WifiSetupOptions_Exit(void);
static void WifiSetupOptions_WaitFadeOut(void);
static void WifiSetupOptions_End(void);
static void WifiSetupOptions_MoveCursor(int dir);
static void WifiSetupOptions_HighlightSelection(void);
static void WifiSetupTransferring_Init(void);
static void WifiSetupTransferring_LoadGraphics(void);
static void WifiSetupTransferring_FadeIn(void);
static void WifiSetupTransferring_WaitFadeIn(void);
static void WifiSetupTransferring_Main(void);
static void WifiSetupTransferring_HandleInput(void);
static void WifiSetupTransferring_Update(void);
static void WifiSetupTransferring_FadeOut(void);
static void WifiSetupTransferring_End(void);
static void WifiSetupTransferring_OnTransferEvent(int event);
static void WifiSetupTransferDone_Init(void);
static void WifiSetupTransferDone_LoadGraphics(void);
static void WifiSetupTransferDone_FadeIn(void);
static void WifiSetupTransferDone_WaitFadeIn(void);
static void WifiSetupTransferDone_WaitButtonBar(void);
static void WifiSetupTransferDone_Main(void);
static void WifiSetupTransferDone_HandleInput(void);
static void WifiSetupTransferDone_Update(void);
static void WifiSetupTransferDone_CheckButtons(void);
static void WifiSetupTransferDone_Exit(void);
static void WifiSetupTransferDone_WaitFadeOut(void);
static void WifiSetupTransferDone_PowerOff(void);
static void WifiSetupTransferInfo_Init(void);
static void WifiSetupTransferInfo_LoadGraphics(void);
static void WifiSetupTransferInfo_FadeIn(void);
static void WifiSetupTransferInfo_WaitFadeIn(void);
static void WifiSetupTransferInfo_WaitButtonBar(void);
static void WifiSetupTransferInfo_Main(void);
static void WifiSetupTransferInfo_HandleInput(void);
static void WifiSetupTransferInfo_Update(void);
static void WifiSetupTransferInfo_CheckButtons(void);
static void WifiSetupTransferInfo_Exit(void);
static void WifiSetupTransferInfo_WaitFadeOut(void);
static void WifiSetupTransferInfo_End(void);
static void WifiSetupTransferIntro_Init(void);
static void WifiSetupTransferIntro_LoadGraphics(void);
static void WifiSetupTransferIntro_FadeIn(void);
static void WifiSetupTransferIntro_WaitFadeIn(void);
static void WifiSetupTransferIntro_WaitButtonBar(void);
static void WifiSetupTransferIntro_Main(void);
static void WifiSetupTransferIntro_HandleInput(void);
static void WifiSetupTransferIntro_Update(void);
static void WifiSetupTransferIntro_CheckButtons(void);
static void WifiSetupTransferIntro_Exit(void);
static void WifiSetupTransferIntro_WaitFadeOut(void);
static void WifiSetupTransferIntro_End(void);
static void WifiSetupTransferCancelled_Init(void);
static void WifiSetupTransferCancelled_LoadGraphics(void);
static void WifiSetupTransferCancelled_FadeIn(void);
static void WifiSetupTransferCancelled_WaitFadeIn(void);
static void WifiSetupTransferCancelled_Main(void);
static void WifiSetupTransferCancelled_Update(void);
static void WifiSetupTransferCancelled_FadeOut(void);
static void WifiSetupTransferCancelled_End(void);
static void WifiSetupTransferCancelled_UpdateTimer(void);
static void WifiSetupTransferFailed_Init(void);
static void WifiSetupTransferFailed_LoadGraphics(void);
static void WifiSetupTransferFailed_FadeIn(void);
static void WifiSetupTransferFailed_WaitFadeIn(void);
static void WifiSetupTransferFailed_WaitButtonBar(void);
static void WifiSetupTransferFailed_Main(void);
static void WifiSetupTransferFailed_HandleInput(void);
static void WifiSetupTransferFailed_Update(void);
static void WifiSetupTransferFailed_CheckButtons(void);
static void WifiSetupTransferFailed_Exit(void);
static void WifiSetupTransferFailed_WaitFadeOut(void);
static void WifiSetupTransferFailed_End(void);
static void WifiSetupTransferConfirm_Init(void);
static void WifiSetupTransferConfirm_LoadGraphics(void);
static void WifiSetupTransferConfirm_FadeIn(void);
static void WifiSetupTransferConfirm_WaitFadeIn(void);
static void WifiSetupTransferConfirm_WaitDialog(void);
static void WifiSetupTransferConfirm_Main(void);
static void WifiSetupTransferConfirm_HandleInput(void);
static void WifiSetupTransferConfirm_Update(void);
static void WifiSetupTransferConfirm_WaitDialogClosed(void);
static void WifiSetupTransferConfirm_WaitFadeOut(void);
static void WifiSetupTransferConfirm_End(void);
static void WifiSetupTransferConfirm_OnTransferEvent(int event);
static BOOL WifiSetupTransferWait_IsLidClosed(void);
static void WifiSetupTransferWait_Init(void);
static void WifiSetupTransferWait_LoadGraphics(void);
static void WifiSetupTransferWait_FadeIn(void);
static void WifiSetupTransferWait_WaitFadeIn(void);
static void WifiSetupTransferWait_WaitButtonBar(void);
static void WifiSetupTransferWait_Main(void);
static void WifiSetupTransferWait_HandleInput(void);
static void WifiSetupTransferWait_Update(void);
static void WifiSetupTransferWait_CheckButtons(void);
static void WifiSetupTransferWait_Exit(void);
static void WifiSetupTransferWait_WaitFadeOut(void);
static void WifiSetupTransferWait_End(void);
static void WifiSetupTransferWait_OnTransferEvent(int event);
static BOOL WifiSetupAoss_IsLidClosed(void);
static void WifiSetupAoss_LoadGraphics(void);
static void WifiSetupAoss_FadeIn(void);
static void WifiSetupAoss_WaitFadeIn(void);
static void WifiSetupAoss_WaitButtonBar(void);
static void WifiSetupAoss_Main(void);
static void WifiSetupAoss_HandleInput(void);
static void WifiSetupAoss_Update(void);
static void WifiSetupAoss_CheckButtons(void);
static void WifiSetupAoss_Exit(void);
static void WifiSetupAoss_WaitFadeOut(void);
static void WifiSetupAoss_End(void);
static void WifiSetupAoss_InputTask(WifiSetupTask *task, void *arg);
static void WifiSetupAoss_WaitErrorDialog(void);
static void WifiSetupAoss_WaitErrorDialogClosed(void);
static void WifiSetupAoss_WaitFinish(void);
static void WifiSetupAoss_Cancel(void);
static void WifiSetupAossDone_Init(void);
static void WifiSetupAossDone_LoadGraphics(void);
static void WifiSetupAossDone_FadeIn(void);
static void WifiSetupAossDone_WaitFadeIn(void);
static void WifiSetupAossDone_Main(void);
static void WifiSetupAossDone_Update(void);
static void WifiSetupAossDone_FadeOut(void);
static void WifiSetupAossDone_End(void);
static void WifiSetupAossDone_UpdateTimer(void);
static void WifiSetupListScreen_LoadGraphics(void);
static void WifiSetupListScreen_CreateScrollBar(void);
static void WifiSetupListScreen_CreateRowObjects(void);
static void WifiSetupListScreen_FadeIn(void);
static void WifiSetupListScreen_WaitFadeIn(void);
static void WifiSetupListScreen_WaitButtonBar(void);
static void WifiSetupListScreen_Main(void);
static void WifiSetupListScreen_HandleInput(void);
static void WifiSetupListScreen_HandleScrollBar(void);
static void WifiSetupListScreen_CheckButtons(void);
static void WifiSetupListScreen_Exit(void);
static void WifiSetupListScreen_WaitFadeOut(void);
static void WifiSetupListScreen_End(void);
static void WifiSetupListScreen_DrawRows(void);
static void WifiSetupListScreen_DrawRowText(int index, int row);
static void WifiSetupListScreen_SetRowIcons(int entry, int row);
static void WifiSetupListScreen_PositionRows(void);
static void WifiSetupListScreen_ScrollUpTask(WifiSetupTask *task, void *arg);
static void WifiSetupListScreen_ScrollDownTask(WifiSetupTask *task, void *arg);
static void WifiSetupListScreen_ScrollBgTask(WifiSetupTask *task, void *arg);
static void WifiSetupListScreen_ShowCursor(void);
static void WifiSetupListScreen_MoveCursor(int input);
static void WifiSetupListScreen_StartScrollUp(void);
static void WifiSetupListScreen_StartScrollDown(void);
static void WifiSetupListScreen_HighlightRescanButton(void);
static void WifiSetupListScreen_WaitErrorDialog(void);
static void WifiSetupListScreen_WaitErrorDialogClosed(void);
static void WifiSetupTextEntry_LoadGraphics(void);
static void WifiSetupTextEntry_FadeIn(void);
static void WifiSetupTextEntry_WaitFadeIn(void);
static void WifiSetupTextEntry_WaitKeyboard(void);
static void WifiSetupTextEntry_Main(void);
static void WifiSetupTextEntry_HandleInput(void);
static void WifiSetupTextEntry_Update(void);
static void WifiSetupTextEntry_Exit(void);
static void WifiSetupTextEntry_CloseKeyboard(void);
static void WifiSetupTextEntry_WaitKeyboardClosed(void);
static void WifiSetupTextEntry_End(void);
static void WifiSetupTextEntry_DrawText(void);
static void WifiSetupTextEntry_UpdateCursor(void);
static void WifiSetupTextEntry_WaitConfirmDialog(void);
static void WifiSetupTextEntry_WaitConfirmDialogClosed(void);
static BOOL WifiSetupTextEntry_IsTextValid(void);
static void WifiSetupTextEntry_WaitErrorDialog(void);
static void WifiSetupTextEntry_WaitErrorDialogClosed(void);

void WifiSetupClient_Start(void) {
    gWifiSetupClientStatus = WifiSetupHeap_AllocZeroed(sizeof(WifiSetupClientStatus), -4);
    if (WifiSetup_StartSimpleStart(0xf, 0x40, WifiSetupClient_OnStatus, WifiSetupClient_Alloc, WifiSetupClient_Free, 0x800) != 1) {
        OS_Terminate();
    }
    OS_Sleep(10);
}

void WifiSetupClient_Stop(void) {
    if (WifiSetup_StopSimpleStart() != 1) {
        OS_Terminate();
    }
    WifiSetupHeap_FreeAndClear(&gWifiSetupClientStatus);
}

int WifiSetupClient_GetResult(void) {
    WifiSetupResult buf;
    switch (gWifiSetupClientStatus->state) {
    case 0:
    case WIFI_SETUP_SIMPLE_START_STARTED:
    case WIFI_SETUP_SIMPLE_START_CONNECTING:
    case WIFI_SETUP_SIMPLE_START_GETTING_SETTINGS:
        return WIFI_SETUP_CLIENT_RESULT_BUSY;
    case WIFI_SETUP_SIMPLE_START_SEARCHING:
        return WIFI_SETUP_CLIENT_RESULT_SEARCHING;
    case WIFI_SETUP_SIMPLE_START_EXCHANGING_KEYS:
        return WIFI_SETUP_CLIENT_RESULT_EXCHANGING_KEYS;
    case WIFI_SETUP_SIMPLE_START_SUCCEEDED:
        if (WifiSetup_GetSimpleStartResult(&buf) != 1) {
            OS_Terminate();
        }
        if (buf.keyType >= WM_WEPMODE_NO && buf.keyType <= WM_WEPMODE_128BIT && buf.unk_24 == 1) {
            return WIFI_SETUP_CLIENT_RESULT_RECEIVED;
        }
        return WIFI_SETUP_CLIENT_RESULT_KEY_UNSUPPORTED;
    case WIFI_SETUP_SIMPLE_START_STOPPED:
        return WIFI_SETUP_CLIENT_RESULT_STOPPED;
    }
}

void WifiSetupClient_StoreResult(void) {
    WifiSetupResult buf;
    if (WifiSetup_GetSimpleStartResult(&buf) != 1) {
        OS_Terminate();
    }
    WifiSetupConnections_SetFromClientResult(&buf);
}

static void WifiSetupClient_OnStatus(s32 *status) {
    *gWifiSetupClientStatus = *(WifiSetupClientStatus *)status;
}

static void *WifiSetupClient_Alloc(u32 size) {
    return WifiSetupHeap_AllocZeroed(size, 0x20);
}

static void WifiSetupClient_Free(void *ptr) {
    WifiSetupHeap_Free(ptr);
}

void WifiSetupScreens_StartQuit(void) {
    WifiSetupFade_Start(WIFI_SETUP_FADE_OUT_TO_WHITE, WIFI_SETUP_SCREEN_SUB, GX_BLEND_PLANEMASK_BG0 | GX_BLEND_PLANEMASK_BG1 | GX_BLEND_PLANEMASK_BG2 | GX_BLEND_PLANEMASK_BG3 | GX_BLEND_PLANEMASK_OBJ | GX_BLEND_PLANEMASK_BD, 0x14);
    WifiSetupFade_Start(WIFI_SETUP_FADE_OUT_TO_WHITE, WIFI_SETUP_SCREEN_MAIN, GX_BLEND_PLANEMASK_BG0 | GX_BLEND_PLANEMASK_BG1 | GX_BLEND_PLANEMASK_BG2 | GX_BLEND_PLANEMASK_BG3 | GX_BLEND_PLANEMASK_OBJ | GX_BLEND_PLANEMASK_BD, 0x14);
    WifiSetupApp_SetStateFunc(WifiSetupScreens_Quit);
}

static void WifiSetupScreens_Quit(void) {
    if (WifiSetupFade_IsActive(WIFI_SETUP_SCREEN_SUB)) {
        return;
    }
    if (WifiSetupFade_IsActive(WIFI_SETUP_SCREEN_MAIN)) {
        return;
    }
    WifiSetupTask_SetQueueEnabled(WIFI_SETUP_TASK_QUEUE_MAIN, FALSE);
    WifiSetupTask_SetQueueEnabled(WIFI_SETUP_TASK_QUEUE_VBLANK, FALSE);
    WifiSetupOamTemplate_Free(1);
    WifiSetupOamTemplate_Free(0);
    WifiSetupBackground_Free();
    WifiSetupCursor_Free();
    WifiSetupText_UnloadBank(gWifiSetupTextBank);
    WifiSetupText_FreeBanks();
    WifiSetupConnections_Free();
    WifiSetupApp_Exit();
}

void WifiSetupScreens_Init(void) {
    WifiSetupConnections_Load();
    WifiSetupText_InitBanks();
    WifiSetupCursor_Init();
    WifiSetupBackground_Init();
    WifiSetupMessage_Reset();
    if (WifiSetupApp_GetLanguage() == 1 && WifiSetupApp_HasOption(2)) {
        gWifiSetupTextBank = WifiSetupText_LoadBank(sStr_MsgUsaBmgL);
    } else {
        gWifiSetupTextBank = WifiSetupText_LoadBank(gWifiSetupMessageBankPaths[WifiSetupApp_GetLanguage()]);
    }
    WifiSetupOamTemplate_Load(1, WifiSetup_LocalizePath(sStr_CharJtMainNceL));
    WifiSetupOamTemplate_Load(0, WifiSetup_LocalizePath(sStr_CharJbMainNceL));
    WifiSetup_LoadGraphics(sStr_CharJtBgMainNcgL, GXS_LoadBG1Char);
    WifiSetup_LoadGraphics(sStr_CharJtBgMainNclL, GXS_LoadBGPltt);
    WifiSetup_LoadGraphics(sStr_CharJtObjMainNcgL, GXS_LoadOBJ);
    WifiSetup_LoadGraphics(sStr_CharXtObjMainNclL, GXS_LoadOBJPltt);
    WifiSetup_LoadGraphics(sStr_CharJbBgStep1_NcgL, GX_LoadBG2Char);
    WifiSetup_LoadGraphics(sStr_CharJbBgStep1_NclL, GX_LoadBGPltt);
    WifiSetup_LoadGraphics(sStr_CharJbObjMainNcgL, GX_LoadOBJ);
    WifiSetup_LoadGraphics(sStr_CharYbObjMainNclL, GX_LoadOBJPltt);
    switch (WifiSetupApp_GetKind()) {
    case WIFI_SETUP_KIND_TOP_MENU:
        WifiSetup_LoadGraphics(sStr_CharJtTopNscL, GXS_LoadBG1Scr);
        break;
    case WIFI_SETUP_KIND_CONNECTION_LIST:
        WifiSetup_LoadGraphics(sStr_CharJtStep1_NscL, GXS_LoadBG1Scr);
        break;
    }
    G2S_SetBG1Priority(3);
    G2_SetBG1Priority(3);
    G2_SetBG1Priority(3);
    WifiSetupDisplay_ShowPlanes(WIFI_SETUP_SCREEN_SUB, GX_PLANEMASK_BG1);
    WifiSetupDisplay_ShowPlanes(WIFI_SETUP_SCREEN_MAIN, GX_PLANEMASK_BG1);
    WifiSetupApp_SetStateFunc(WifiSetupScreens_FadeIn);
}

static void WifiSetupScreens_FadeIn(void) {
    WifiSetupFade_Start(WIFI_SETUP_FADE_IN_FROM_WHITE, WIFI_SETUP_SCREEN_SUB, GX_BLEND_PLANEMASK_BG1, 0x14);
    WifiSetupFade_Start(WIFI_SETUP_FADE_IN_FROM_WHITE, WIFI_SETUP_SCREEN_MAIN, GX_BLEND_PLANEMASK_BG1, 0x14);
    WifiSetupApp_SetStateFunc(WifiSetupScreens_WaitFadeIn);
}

static void WifiSetupScreens_WaitFadeIn(void) {
    if (WifiSetupFade_IsActive(WIFI_SETUP_SCREEN_SUB)) {
        return;
    }
    if (WifiSetupFade_IsActive(WIFI_SETUP_SCREEN_MAIN)) {
        return;
    }
    switch (WifiSetupApp_GetKind()) {
    case WIFI_SETUP_KIND_TOP_MENU:
        WifiSetupApp_SetTransition(WIFI_SETUP_BANNER_KEEP, WIFI_SETUP_BUTTON_BAR_CREATE);
        WifiSetupApp_SetStateFunc(WifiSetupTopMenu_Init);
        break;
    case WIFI_SETUP_KIND_CONNECTION_LIST:
        WifiSetupApp_SetTransition(WIFI_SETUP_BANNER_OPEN, WIFI_SETUP_BUTTON_BAR_CREATE);
        WifiSetupApp_SetStateFunc(WifiSetupConnectionList_Init);
        break;
    }
}

void WifiSetupTopMenu_Init(void) {
    int i;
    WifiSetupTopMenu_LoadGraphics();
    WifiSetupBackground_LoadHeader(0);
    WifiSetupMessage_Show(0x2e, -1, 0);
    WifiSetupBanner_LoadScreen(4);
    i = gWifiSetupTopMenu.selected * 4;
    WifiSetupCursor_ShowCorners(gWifiSetupTopMenuCursorLeft[i], gWifiSetupTopMenuCursorRight[i], gWifiSetupTopMenuCursorTop[i], gWifiSetupTopMenuCursorBottom[i]);
    WifiSetupApp_SetStateFunc(WifiSetupTopMenu_FadeIn);
}

static void WifiSetupTopMenu_LoadGraphics(void) {
    WifiSetupPath22 name;
    name = gWifiSetupTopMenuYbBgStep11NclPath;
    WifiSetup_LoadGraphics(sStr_CharJbBgStep1_NcgL_2, GX_LoadBG2Char);
    WifiSetup_LoadGraphics(sStr_CharJbBgStep1_NclL_2, GX_LoadBGPltt);
    WifiSetup_LoadGraphics(sStr_CharJb2MenuNscL, GX_LoadBG2Scr);
    gWifiSetupTopMenu.graphics = WifiSetupFile_Load(WifiSetup_LocalizePath(name.text), NULL, 4);
    G2S_SetBG0Priority(3);
    G2S_SetBG1Priority(3);
    G2_SetBG1Priority(3);
    G2_SetBG2Priority(3);
}

static void WifiSetupTopMenu_FadeIn(void) {
    WifiSetupFade_Start(WIFI_SETUP_FADE_IN_FROM_WHITE, WIFI_SETUP_SCREEN_SUB, GX_BLEND_PLANEMASK_BG0, 8);
    WifiSetupFade_Start(WIFI_SETUP_FADE_IN_FROM_WHITE, WIFI_SETUP_SCREEN_MAIN, GX_BLEND_PLANEMASK_BG2 | GX_BLEND_PLANEMASK_OBJ, 8);
    WifiSetupDisplay_ShowPlanes(WIFI_SETUP_SCREEN_SUB, GX_PLANEMASK_BG0);
    WifiSetupDisplay_ShowPlanes(WIFI_SETUP_SCREEN_MAIN, GX_PLANEMASK_BG2 | GX_PLANEMASK_OBJ);
    WifiSetupApp_SetStateFunc(WifiSetupTopMenu_WaitFadeIn);
}

static void WifiSetupTopMenu_WaitFadeIn(void) {
    if (WifiSetupFade_IsActive(WIFI_SETUP_SCREEN_SUB)) {
        return;
    }
    if (WifiSetupFade_IsActive(WIFI_SETUP_SCREEN_MAIN)) {
        return;
    }
    WifiSetupButtonBar_Show(0);
    WifiSetupApp_SetStateFunc(WifiSetupTopMenu_WaitButtonBar);
}

static void WifiSetupTopMenu_WaitButtonBar(void) {
    if (WifiSetupButtonBar_GetSelected() == WIFI_SETUP_SELECTED_NOT_SHOWN) {
        return;
    }
    WifiSetupButtonBar_Unlock();
    WifiSetupApp_SetStateFunc(WifiSetupTopMenu_Main);
}

static void WifiSetupTopMenu_Main(void) {
    WifiSetupTopMenu_HandleInput();
    WifiSetupTopMenu_Update();
    WifiSetupTopMenu_CheckButtons();
}

static void WifiSetupTopMenu_HandleInput(void) {
    u32 i;
    WifiSetupRect *entry = gWifiSetupTopMenuTouchRects;
    for (i = 0; i < 2; i++, entry++) {
        if (WifiSetupInput_IsTouchPressed(entry)) {
            int idx;
            WifiSetupButtonBar_SelectIfNone(1);
            gWifiSetupTopMenu.selected = i;
            idx = gWifiSetupTopMenu.selected * 4;
            WifiSetupCursor_ShowCorners(gWifiSetupTopMenuCursorLeft[idx], gWifiSetupTopMenuCursorRight[idx], gWifiSetupTopMenuCursorTop[idx], gWifiSetupTopMenuCursorBottom[idx]);
            return;
        }
    }
    if (WifiSetupInput_IsKeyPressed(PAD_BUTTON_A)) {
        WifiSetupButtonBar_SelectIfNone(1);
        return;
    }
    if (WifiSetupInput_IsKeyPressed(PAD_BUTTON_B)) {
        WifiSetupButtonBar_SelectIfNone(0);
        return;
    }
    if (WifiSetupInput_IsKeyRepeated(PAD_KEY_UP)) {
        WifiSetupTopMenu_MoveCursor(WIFI_SETUP_CURSOR_UP);
        return;
    }
    if (WifiSetupInput_IsKeyRepeated(PAD_KEY_DOWN)) {
        WifiSetupTopMenu_MoveCursor(WIFI_SETUP_CURSOR_DOWN);
        return;
    }
    if (WifiSetupInput_IsKeyRepeated(PAD_KEY_LEFT)) {
        WifiSetupTopMenu_MoveCursor(WIFI_SETUP_CURSOR_LEFT);
        return;
    }
    if (WifiSetupInput_IsKeyRepeated(PAD_KEY_RIGHT)) {
        WifiSetupTopMenu_MoveCursor(WIFI_SETUP_CURSOR_RIGHT);
    }
}

static void WifiSetupTopMenu_Update(void) {
}

static void WifiSetupTopMenu_CheckButtons(void) {
    switch (WifiSetupButtonBar_GetSelected()) {
    case 0:
        WifiSetupSound_Play(7);
        WifiSetupApp_SetStateFunc(WifiSetupScreens_StartQuit);
        break;
    case 1:
        WifiSetupSound_Play(6);
        WifiSetupTopMenu_HighlightSelection();
        WifiSetupApp_SetStateFunc(WifiSetupTopMenu_Exit);
        break;
    }
}

static void WifiSetupTopMenu_Exit(void) {
    WifiSetupButtonBar_Lock();
    WifiSetupFade_StartDelay(8);
    WifiSetupApp_SetStateFunc(WifiSetupTopMenu_WaitFadeOut);
}

static void WifiSetupTopMenu_WaitFadeOut(void) {
    if (WifiSetupFade_IsActive(WIFI_SETUP_SCREEN_SUB)) {
        return;
    }
    WifiSetupFade_Start(WIFI_SETUP_FADE_OUT_TO_WHITE, WIFI_SETUP_SCREEN_SUB, GX_BLEND_PLANEMASK_BG0, 8);
    WifiSetupFade_Start(WIFI_SETUP_FADE_OUT_TO_WHITE, WIFI_SETUP_SCREEN_MAIN, GX_BLEND_PLANEMASK_BG1 | GX_BLEND_PLANEMASK_BG2 | GX_BLEND_PLANEMASK_OBJ, 8);
    WifiSetupApp_SetStateFunc(WifiSetupTopMenu_End);
}

static void WifiSetupTopMenu_End(void) {
    if (WifiSetupFade_IsActive(WIFI_SETUP_SCREEN_SUB)) {
        return;
    }
    if (WifiSetupFade_IsActive(WIFI_SETUP_SCREEN_MAIN)) {
        return;
    }
    WifiSetupCursor_Hide();
    WifiSetupMessage_Hide();
    WifiSetupFile_Free(gWifiSetupTopMenu.graphics);
    WifiSetupDisplay_HidePlanes(WIFI_SETUP_SCREEN_SUB, GX_PLANEMASK_BG0);
    WifiSetupDisplay_HidePlanes(WIFI_SETUP_SCREEN_MAIN, GX_PLANEMASK_BG2 | GX_PLANEMASK_OBJ);
    switch (gWifiSetupTopMenu.selected) {
    case 0:
        WifiSetupApp_SetTransition(WIFI_SETUP_BANNER_OPEN, WIFI_SETUP_BUTTON_BAR_KEEP);
        WifiSetupApp_SetStateFunc(WifiSetupConnectionList_Init);
        break;
    case 1:
        WifiSetupApp_SetTransition(WIFI_SETUP_BANNER_KEEP, WIFI_SETUP_BUTTON_BAR_KEEP);
        WifiSetupApp_SetStateFunc(WifiSetupOptions_Init);
        break;
    }
}

static void WifiSetupTopMenu_MoveCursor(int dir) {
    int idx;
    if (dir == WIFI_SETUP_CURSOR_UP || dir == WIFI_SETUP_CURSOR_DOWN) {
        return;
    }
    gWifiSetupTopMenu.selected ^= 1;
    WifiSetupSound_Play(8);
    idx = gWifiSetupTopMenu.selected * 4;
    WifiSetupCursor_ShowCorners(gWifiSetupTopMenuCursorLeft[idx], gWifiSetupTopMenuCursorRight[idx], gWifiSetupTopMenuCursorTop[idx], gWifiSetupTopMenuCursorBottom[idx]);
}

static void WifiSetupTopMenu_HighlightSelection(void) {
    WifiSetupBytePair tbl = gWifiSetupTopMenuPaletteRows;
    WifiSetupPalette_LoadRow(gWifiSetupTopMenu.graphics, tbl.values[gWifiSetupTopMenu.selected], tbl.values[gWifiSetupTopMenu.selected]);
}

static void WifiSetupEraseConfirm_Init(void) {
    gWifiSetupEraseConfirmed = FALSE;
    WifiSetupEraseConfirm_LoadGraphics();
    WifiSetupBackground_LoadHeader(0x12);
    WifiSetupMessage_Show(0x3b, -1, 0);
    WifiSetup_PrintMessage(0x17);
    WifiSetupApp_SetStateFunc(WifiSetupEraseConfirm_FadeIn);
}

static void WifiSetupEraseConfirm_LoadGraphics(void) {
    WifiSetup_LoadGraphics(sStr_CharYb5MultiNscL, GX_LoadBG2Scr);
    G2S_SetBG0Priority(3);
    G2S_SetBG1Priority(3);
    G2_SetBG0Priority(3);
    G2_SetBG1Priority(3);
    G2_SetBG2Priority(3);
}

static void WifiSetupEraseConfirm_FadeIn(void) {
    WifiSetupFade_Start(WIFI_SETUP_FADE_IN_FROM_WHITE, WIFI_SETUP_SCREEN_SUB, GX_BLEND_PLANEMASK_BG0, 8);
    WifiSetupFade_Start(WIFI_SETUP_FADE_IN_FROM_WHITE, WIFI_SETUP_SCREEN_MAIN, GX_BLEND_PLANEMASK_BG0 | GX_BLEND_PLANEMASK_BG2 | GX_BLEND_PLANEMASK_OBJ, 8);
    WifiSetupDisplay_ShowPlanes(WIFI_SETUP_SCREEN_SUB, GX_PLANEMASK_BG0);
    WifiSetupDisplay_ShowPlanes(WIFI_SETUP_SCREEN_MAIN, GX_PLANEMASK_BG0 | GX_PLANEMASK_BG2 | GX_PLANEMASK_OBJ);
    WifiSetupApp_SetStateFunc(WifiSetupEraseConfirm_WaitFadeIn);
}

static void WifiSetupEraseConfirm_WaitFadeIn(void) {
    if (WifiSetupFade_IsActive(WIFI_SETUP_SCREEN_SUB)) {
        return;
    }
    if (WifiSetupFade_IsActive(WIFI_SETUP_SCREEN_MAIN)) {
        return;
    }
    WifiSetupButtonBar_Show(3);
    WifiSetupApp_SetStateFunc(WifiSetupEraseConfirm_WaitButtonBar);
}

static void WifiSetupEraseConfirm_WaitButtonBar(void) {
    if (WifiSetupButtonBar_GetSelected() == WIFI_SETUP_SELECTED_NOT_SHOWN) {
        return;
    }
    WifiSetupButtonBar_Unlock();
    WifiSetupApp_SetStateFunc(WifiSetupEraseConfirm_Main);
}

static void WifiSetupEraseConfirm_Main(void) {
    WifiSetupEraseConfirm_HandleInput();
    WifiSetupEraseConfirm_Update();
    WifiSetupEraseConfirm_CheckButtons();
}

static void WifiSetupEraseConfirm_HandleInput(void) {
    if (WifiSetupInput_IsKeyPressed(PAD_BUTTON_A)) {
        WifiSetupButtonBar_SelectIfNone(1);
    }
    if (WifiSetupInput_IsKeyPressed(PAD_BUTTON_B)) {
        WifiSetupButtonBar_SelectIfNone(0);
    }
}

static void WifiSetupEraseConfirm_Update(void) {
}

static void WifiSetupEraseConfirm_CheckButtons(void) {
    switch (WifiSetupButtonBar_GetSelected()) {
    case 0:
        WifiSetupSound_Play(7);
        WifiSetupApp_SetStateFunc(WifiSetupEraseConfirm_Exit);
        break;
    case 1:
        WifiSetupSound_Play(6);
        WifiSetupDialog_Open(0x18, 0, 1, -1, 0);
        WifiSetupButtonBar_Lock();
        WifiSetupApp_SetStateFunc(WifiSetupEraseConfirm_WaitDialog);
        break;
    }
}

static void WifiSetupEraseConfirm_Exit(void) {
    WifiSetupButtonBar_Lock();
    WifiSetupFade_StartDelay(8);
    WifiSetupApp_SetStateFunc(WifiSetupEraseConfirm_WaitFadeOut);
}

static void WifiSetupEraseConfirm_WaitFadeOut(void) {
    if (WifiSetupFade_IsActive(WIFI_SETUP_SCREEN_SUB)) {
        return;
    }
    WifiSetupButtonBar_Close();
    if (!gWifiSetupEraseConfirmed) {
        WifiSetupFade_Start(WIFI_SETUP_FADE_OUT_TO_WHITE, WIFI_SETUP_SCREEN_SUB, GX_BLEND_PLANEMASK_BG0, 8);
    }
    WifiSetupFade_Start(WIFI_SETUP_FADE_OUT_TO_WHITE, WIFI_SETUP_SCREEN_MAIN, GX_BLEND_PLANEMASK_BG0 | GX_BLEND_PLANEMASK_BG2 | GX_BLEND_PLANEMASK_OBJ, 8);
    WifiSetupApp_SetStateFunc(WifiSetupEraseConfirm_End);
}

static void WifiSetupEraseConfirm_End(void) {
    if (WifiSetupFade_IsActive(WIFI_SETUP_SCREEN_MAIN)) {
        return;
    }
    if (!gWifiSetupEraseConfirmed) {
        if (WifiSetupFade_IsActive(WIFI_SETUP_SCREEN_SUB)) {
            return;
        }
    }
    if (!WifiSetupButtonBar_IsNotClosing()) {
        return;
    }
    WifiSetupText_FreeBgCanvas(WIFI_SETUP_SCREEN_MAIN);
    if (!gWifiSetupEraseConfirmed) {
        WifiSetupMessage_Hide();
        WifiSetupDisplay_HidePlanes(WIFI_SETUP_SCREEN_SUB, GX_PLANEMASK_BG0);
    }
    WifiSetupDisplay_HidePlanes(WIFI_SETUP_SCREEN_MAIN, GX_PLANEMASK_BG0 | GX_PLANEMASK_BG2 | GX_PLANEMASK_OBJ);
    if (!gWifiSetupEraseConfirmed) {
        WifiSetupApp_SetTransition(WIFI_SETUP_BANNER_KEEP, WIFI_SETUP_BUTTON_BAR_CREATE);
        WifiSetupApp_SetStateFunc(WifiSetupOptions_Init);
    } else {
        WifiSetupApp_SetTransition(WIFI_SETUP_BANNER_KEEP, WIFI_SETUP_BUTTON_BAR_CREATE);
        WifiSetupApp_SetStateFunc(WifiSetupEraseDone_Init);
    }
}

static void WifiSetupEraseConfirm_WaitDialog(void) {
    int selected = WifiSetupDialog_GetSelected();
    if (selected != 0) {
        if (selected != 1) {
            return;
        }
        WifiSetupSound_Play(0xe);
        gWifiSetupEraseConfirmed = TRUE;
    } else {
        WifiSetupSound_Play(7);
    }
    WifiSetupDialog_Close();
    WifiSetupApp_SetStateFunc(WifiSetupEraseConfirm_WaitDialogClosed);
}

static void WifiSetupEraseConfirm_WaitDialogClosed(void) {
    if (WifiSetupDialog_IsOpen()) {
        return;
    }
    WifiSetupApp_SetStateFunc(WifiSetupEraseConfirm_Exit);
}

static void WifiSetupEraseDone_Init(void) {
    WifiSetupEraseDone_LoadGraphics();
    WifiSetup_PrintMessage(0x19);
    WifiSetupConnections_Reset();
    WifiSetupApp_SetStateFunc(WifiSetupEraseDone_FadeIn);
}

static void WifiSetupEraseDone_LoadGraphics(void) {
    WifiSetup_LoadGraphics(sStr_CharYb5MultiNscL_2, GX_LoadBG2Scr);
    G2S_SetBG0Priority(3);
    G2S_SetBG1Priority(3);
    G2_SetBG0Priority(3);
    G2_SetBG1Priority(3);
    G2_SetBG2Priority(3);
}

static void WifiSetupEraseDone_FadeIn(void) {
    WifiSetupFade_Start(WIFI_SETUP_FADE_IN_FROM_WHITE, WIFI_SETUP_SCREEN_MAIN, GX_BLEND_PLANEMASK_BG0 | GX_BLEND_PLANEMASK_BG2 | GX_BLEND_PLANEMASK_OBJ, 8);
    WifiSetupDisplay_ShowPlanes(WIFI_SETUP_SCREEN_MAIN, GX_PLANEMASK_BG0 | GX_PLANEMASK_BG2 | GX_PLANEMASK_OBJ);
    WifiSetupApp_SetStateFunc(WifiSetupEraseDone_WaitFadeIn);
}

static void WifiSetupEraseDone_WaitFadeIn(void) {
    if (WifiSetupFade_IsActive(WIFI_SETUP_SCREEN_MAIN)) {
        return;
    }
    WifiSetupButtonBar_Show(5);
    WifiSetupApp_SetStateFunc(WifiSetupEraseDone_WaitButtonBar);
}

static void WifiSetupEraseDone_WaitButtonBar(void) {
    if (WifiSetupButtonBar_GetSelected() == WIFI_SETUP_SELECTED_NOT_SHOWN) {
        return;
    }
    WifiSetupButtonBar_Unlock();
    WifiSetupApp_SetStateFunc(WifiSetupEraseDone_Main);
}

static void WifiSetupEraseDone_Main(void) {
    WifiSetupEraseDone_HandleInput();
    WifiSetupEraseDone_Update();
    WifiSetupEraseDone_CheckButtons();
}

static void WifiSetupEraseDone_HandleInput(void) {
    if (WifiSetupInput_IsKeyPressed(PAD_BUTTON_A)) {
        WifiSetupButtonBar_SelectIfNone(0);
    }
}

static void WifiSetupEraseDone_Update(void) {
}

static void WifiSetupEraseDone_CheckButtons(void) {
    if (WifiSetupButtonBar_GetSelected() != 0) {
        return;
    }
    WifiSetupSound_Play(6);
    WifiSetupApp_SetStateFunc(WifiSetupEraseDone_Exit);
}

static void WifiSetupEraseDone_Exit(void) {
    WifiSetupButtonBar_Lock();
    WifiSetupFade_StartDelay(8);
    WifiSetupApp_SetStateFunc(WifiSetupEraseDone_WaitFadeOut);
}

static void WifiSetupEraseDone_WaitFadeOut(void) {
    if (WifiSetupFade_IsActive(WIFI_SETUP_SCREEN_SUB)) {
        return;
    }
    WifiSetupFade_Start(WIFI_SETUP_FADE_OUT_TO_WHITE, WIFI_SETUP_SCREEN_SUB, GX_BLEND_PLANEMASK_BG0 | GX_BLEND_PLANEMASK_BG1 | GX_BLEND_PLANEMASK_BG2 | GX_BLEND_PLANEMASK_BG3 | GX_BLEND_PLANEMASK_OBJ | GX_BLEND_PLANEMASK_BD, 0x40);
    WifiSetupFade_Start(WIFI_SETUP_FADE_OUT_TO_WHITE, WIFI_SETUP_SCREEN_MAIN, GX_BLEND_PLANEMASK_BG0 | GX_BLEND_PLANEMASK_BG1 | GX_BLEND_PLANEMASK_BG2 | GX_BLEND_PLANEMASK_BG3 | GX_BLEND_PLANEMASK_OBJ | GX_BLEND_PLANEMASK_BD, 0x40);
    WifiSetupApp_SetStateFunc(WifiSetupEraseDone_PowerOff);
}

static void WifiSetupEraseDone_PowerOff(void) {
    if (WifiSetupFade_IsActive(WIFI_SETUP_SCREEN_SUB)) {
        return;
    }
    if (WifiSetupFade_IsActive(WIFI_SETUP_SCREEN_MAIN)) {
        return;
    }
    OS_SpinWait(0x1000000);
    PM_ForceToPowerOff();
}

static void WifiSetupSystemInfo_Init(void) {
    WifiSetupSystemInfo_LoadGraphics();
    WifiSetupBackground_LoadHeader(0x11);
    WifiSetupMessage_Show(0x3a, -1, 0);
    WifiSetupSystemInfo_DrawInfo();
    WifiSetupApp_SetStateFunc(WifiSetupSystemInfo_FadeIn);
}

static void WifiSetupSystemInfo_LoadGraphics(void) {
    WifiSetup_LoadGraphics(sStr_CharJb5InfoNscL, GX_LoadBG2Scr);
    G2S_SetBG0Priority(3);
    G2S_SetBG1Priority(3);
    G2_SetBG0Priority(3);
    G2_SetBG1Priority(3);
    G2_SetBG2Priority(3);
}

static void WifiSetupSystemInfo_DrawInfo(void) {
    DwcWiFiInfo info;
    u32 parts[4];
    u16 buf[20];
    u8 mac[6];
    u64 id;
    int i;
    WifiSetupCanvas *win = WifiSetupText_InitBgCanvas(WIFI_SETUP_SCREEN_MAIN, 0);
    OS_GetMacAddress(mac);
    swprintf(buf, NELEMS(buf), gWifiSetupSystemInfoMacFormat, mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
    WifiSetupText_DrawInRect(win, 8, 0x40, 0xf0, 0x1c, 2, 0x480, buf);
    DWCi_BM_GetWiFiInfo(&info);
    if (info.userId != 0) {
        id = info.userId;
        parts[3] = (id % 10) * 1000;
        id /= 10;
        for (i = 0; i < 3; i++) {
            parts[2 - i] = id % 10000;
            id /= 10000;
        }
        swprintf(buf, NELEMS(buf), gWifiSetupSystemInfoIdFormat, parts[0], parts[1], parts[2], parts[3]);
    } else {
        swprintf(buf, NELEMS(buf), gWifiSetupSystemInfoNoIdText);
    }
    WifiSetupText_DrawInRect(win, 8, 0x78, 0xf0, 0x1c, 2, 0x480, buf);
    WifiSetupText_MarkDirty(win);
}

static void WifiSetupSystemInfo_FadeIn(void) {
    WifiSetupFade_Start(WIFI_SETUP_FADE_IN_FROM_WHITE, WIFI_SETUP_SCREEN_SUB, GX_BLEND_PLANEMASK_BG0, 8);
    WifiSetupFade_Start(WIFI_SETUP_FADE_IN_FROM_WHITE, WIFI_SETUP_SCREEN_MAIN, GX_BLEND_PLANEMASK_BG0 | GX_BLEND_PLANEMASK_BG2 | GX_BLEND_PLANEMASK_OBJ, 8);
    WifiSetupDisplay_ShowPlanes(WIFI_SETUP_SCREEN_SUB, GX_PLANEMASK_BG0);
    WifiSetupDisplay_ShowPlanes(WIFI_SETUP_SCREEN_MAIN, GX_PLANEMASK_BG0 | GX_PLANEMASK_BG2 | GX_PLANEMASK_OBJ);
    WifiSetupApp_SetStateFunc(WifiSetupSystemInfo_WaitFadeIn);
}

static void WifiSetupSystemInfo_WaitFadeIn(void) {
    if (WifiSetupFade_IsActive(WIFI_SETUP_SCREEN_SUB)) {
        return;
    }
    if (WifiSetupFade_IsActive(WIFI_SETUP_SCREEN_MAIN)) {
        return;
    }
    WifiSetupButtonBar_Show(2);
    WifiSetupApp_SetStateFunc(WifiSetupSystemInfo_WaitButtonBar);
}

static void WifiSetupSystemInfo_WaitButtonBar(void) {
    if (WifiSetupButtonBar_GetSelected() == WIFI_SETUP_SELECTED_NOT_SHOWN) {
        return;
    }
    WifiSetupButtonBar_Unlock();
    WifiSetupApp_SetStateFunc(WifiSetupSystemInfo_Main);
}

static void WifiSetupSystemInfo_Main(void) {
    WifiSetupSystemInfo_HandleInput();
    WifiSetupSystemInfo_Update();
    WifiSetupSystemInfo_CheckButtons();
}

static void WifiSetupSystemInfo_HandleInput(void) {
    if (WifiSetupInput_IsKeyPressed(PAD_BUTTON_B)) {
        WifiSetupButtonBar_SelectIfNone(0);
    }
}

static void WifiSetupSystemInfo_Update(void) {
}

static void WifiSetupSystemInfo_CheckButtons(void) {
    if (WifiSetupButtonBar_GetSelected() != 0) {
        return;
    }
    WifiSetupSound_Play(7);
    WifiSetupApp_SetStateFunc(WifiSetupSystemInfo_Exit);
}

static void WifiSetupSystemInfo_Exit(void) {
    WifiSetupButtonBar_Lock();
    WifiSetupFade_StartDelay(8);
    WifiSetupApp_SetStateFunc(WifiSetupSystemInfo_WaitFadeOut);
}

static void WifiSetupSystemInfo_WaitFadeOut(void) {
    if (WifiSetupFade_IsActive(WIFI_SETUP_SCREEN_SUB)) {
        return;
    }
    WifiSetupButtonBar_Close();
    WifiSetupFade_Start(WIFI_SETUP_FADE_OUT_TO_WHITE, WIFI_SETUP_SCREEN_SUB, GX_BLEND_PLANEMASK_BG0, 8);
    WifiSetupFade_Start(WIFI_SETUP_FADE_OUT_TO_WHITE, WIFI_SETUP_SCREEN_MAIN, GX_BLEND_PLANEMASK_BG0 | GX_BLEND_PLANEMASK_BG2 | GX_BLEND_PLANEMASK_OBJ, 8);
    WifiSetupApp_SetStateFunc(WifiSetupSystemInfo_End);
}

static void WifiSetupSystemInfo_End(void) {
    if (WifiSetupFade_IsActive(WIFI_SETUP_SCREEN_SUB)) {
        return;
    }
    if (WifiSetupFade_IsActive(WIFI_SETUP_SCREEN_MAIN)) {
        return;
    }
    if (!WifiSetupButtonBar_IsNotClosing()) {
        return;
    }
    WifiSetupText_FreeBgCanvas(WIFI_SETUP_SCREEN_MAIN);
    WifiSetupMessage_Hide();
    WifiSetupDisplay_HidePlanes(WIFI_SETUP_SCREEN_SUB, GX_PLANEMASK_BG0);
    WifiSetupDisplay_HidePlanes(WIFI_SETUP_SCREEN_MAIN, GX_PLANEMASK_BG0 | GX_PLANEMASK_BG2 | GX_PLANEMASK_OBJ);
    WifiSetupApp_SetTransition(WIFI_SETUP_BANNER_KEEP, WIFI_SETUP_BUTTON_BAR_CREATE);
    WifiSetupApp_SetStateFunc(WifiSetupOptions_Init);
}

static void WifiSetupOptions_Init(void) {
    int idx;
    gWifiSetupOptions.confirmed = FALSE;
    WifiSetupOptions_LoadGraphics();
    WifiSetupBackground_LoadHeader(0x10);
    WifiSetupBanner_LoadScreen(3);
    WifiSetupMessage_Show(0x39, -1, 0);
    gWifiSetupOptions.oam = WifiSetupOamTemplate_AllocOam(0, 0x5b);
    gWifiSetupOptions.oam->attr01 = (gWifiSetupOptions.oam->attr01 & 0xFE00FF00) | 0x84 | 0xE00000;
    gWifiSetupOptions.oam->attr2 = (gWifiSetupOptions.oam->attr2 & ~0xc00) | 0xc00;
    idx = gWifiSetupOptions.selected * 4;
    WifiSetupCursor_ShowCorners(gWifiSetupOptionsCursorLeft[idx], gWifiSetupOptionsCursorRight[idx], gWifiSetupOptionsCursorTop[idx], gWifiSetupOptionsCursorBottom[idx]);
    WifiSetupApp_SetStateFunc(WifiSetupOptions_FadeIn);
}

static void WifiSetupOptions_LoadGraphics(void) {
    WifiSetupPath22 plttName;
    WifiSetupPath23 graphicsName;
    DwcWiFiInfo info;
    u8 *src;
    u8 *dst;
    int i;
    u8 *pal;
    plttName = gWifiSetupOptionsYbBgOptionNclPath;
    graphicsName = gWifiSetupOptionsYbBgOption1NclPath;
    WifiSetup_LoadGraphics(gWifiSetupOptionsJbBgOptionNcgPath, GX_LoadBG2Char);
    WifiSetup_LoadGraphics(gWifiSetupOptionsJb5OptMenuNscPath, GX_LoadBG2Scr);
    gWifiSetupOptions.graphics = WifiSetupFile_Load(WifiSetup_LocalizePath(graphicsName.text), NULL, 4);
    pal = WifiSetupFile_Load(WifiSetup_LocalizePath(plttName.text), NULL, 4);
    DWCi_BM_GetWiFiInfo(&info);
    if (info.userId == 0) {
        src = pal + 0xc0;
        dst = pal + 0x40;
        for (i = 0; i < 2; i++) {
            MI_CpuCopy8(src, dst, 0x20);
            src += 0x20;
            dst += 0x20;
        }
    }
    DC_FlushRange(pal, HW_BG_PLTT_SIZE);
    GX_LoadBGPltt(pal, 0, HW_BG_PLTT_SIZE);
    WifiSetupFile_Free(pal);
    G2S_SetBG0Priority(3);
    G2S_SetBG1Priority(3);
    G2_SetBG1Priority(3);
    G2_SetBG2Priority(3);
}

static void WifiSetupOptions_FadeIn(void) {
    WifiSetupFade_Start(WIFI_SETUP_FADE_IN_FROM_WHITE, WIFI_SETUP_SCREEN_SUB, GX_BLEND_PLANEMASK_BG0, 8);
    WifiSetupFade_Start(WIFI_SETUP_FADE_IN_FROM_WHITE, WIFI_SETUP_SCREEN_MAIN, GX_BLEND_PLANEMASK_BG2 | GX_BLEND_PLANEMASK_OBJ, 8);
    WifiSetupDisplay_ShowPlanes(WIFI_SETUP_SCREEN_SUB, GX_PLANEMASK_BG0);
    WifiSetupDisplay_ShowPlanes(WIFI_SETUP_SCREEN_MAIN, GX_PLANEMASK_BG2 | GX_PLANEMASK_OBJ);
    WifiSetupApp_SetStateFunc(WifiSetupOptions_WaitFadeIn);
}

static void WifiSetupOptions_WaitFadeIn(void) {
    if (WifiSetupFade_IsActive(WIFI_SETUP_SCREEN_SUB)) {
        return;
    }
    if (WifiSetupFade_IsActive(WIFI_SETUP_SCREEN_MAIN)) {
        return;
    }
    WifiSetupButtonBar_Show(0);
    WifiSetupApp_SetStateFunc(WifiSetupOptions_WaitButtonBar);
}

static void WifiSetupOptions_WaitButtonBar(void) {
    if (WifiSetupButtonBar_GetSelected() == WIFI_SETUP_SELECTED_NOT_SHOWN) {
        return;
    }
    WifiSetupButtonBar_Unlock();
    WifiSetupApp_SetStateFunc(WifiSetupOptions_Main);
}

static void WifiSetupOptions_Main(void) {
    WifiSetupOptions_HandleInput();
    WifiSetupOptions_Update();
    WifiSetupOptions_CheckButtons();
}

static void WifiSetupOptions_HandleInput(void) {
    u32 i;
    WifiSetupRect *entry = gWifiSetupOptionsTouchRects;
    for (i = 0; i < 3; i++, entry++) {
        if (WifiSetupInput_IsTouchPressed(entry)) {
            int idx;
            WifiSetupButtonBar_SelectIfNone(1);
            gWifiSetupOptions.selected = i;
            idx = gWifiSetupOptions.selected * 4;
            WifiSetupCursor_ShowCorners(gWifiSetupOptionsCursorLeft[idx], gWifiSetupOptionsCursorRight[idx], gWifiSetupOptionsCursorTop[idx], gWifiSetupOptionsCursorBottom[idx]);
            return;
        }
    }
    if (WifiSetupInput_IsKeyPressed(PAD_BUTTON_A)) {
        WifiSetupButtonBar_SelectIfNone(1);
        return;
    }
    if (WifiSetupInput_IsKeyPressed(PAD_BUTTON_B)) {
        WifiSetupButtonBar_SelectIfNone(0);
        return;
    }
    if (WifiSetupInput_IsKeyRepeated(PAD_KEY_UP)) {
        WifiSetupOptions_MoveCursor(WIFI_SETUP_CURSOR_UP);
        return;
    }
    if (WifiSetupInput_IsKeyRepeated(PAD_KEY_DOWN)) {
        WifiSetupOptions_MoveCursor(WIFI_SETUP_CURSOR_DOWN);
    }
}

static void WifiSetupOptions_Update(void) {
}

static void WifiSetupOptions_CheckButtons(void) {
    DwcWiFiInfo info;
    switch (WifiSetupButtonBar_GetSelected()) {
    case 0:
        WifiSetupSound_Play(7);
        break;
    case 1:
        DWCi_BM_GetWiFiInfo(&info);
        if (gWifiSetupOptions.selected != 0 && info.userId == 0) {
            WifiSetupSound_Play(9);
            WifiSetupButtonBar_SetSelected(WIFI_SETUP_SELECTED_NONE);
            return;
        }
        WifiSetupSound_Play(6);
        WifiSetupOptions_HighlightSelection();
        gWifiSetupOptions.confirmed = TRUE;
        break;
    default:
        return;
    }
    WifiSetupApp_SetStateFunc(WifiSetupOptions_Exit);
}

static void WifiSetupOptions_Exit(void) {
    WifiSetupButtonBar_Lock();
    WifiSetupFade_StartDelay(8);
    WifiSetupApp_SetStateFunc(WifiSetupOptions_WaitFadeOut);
}

static void WifiSetupOptions_WaitFadeOut(void) {
    if (WifiSetupFade_IsActive(WIFI_SETUP_SCREEN_SUB)) {
        return;
    }
    if (gWifiSetupOptions.confirmed) {
        WifiSetupButtonBar_Close();
    }
    WifiSetupFade_Start(WIFI_SETUP_FADE_OUT_TO_WHITE, WIFI_SETUP_SCREEN_SUB, GX_BLEND_PLANEMASK_BG0, 8);
    WifiSetupFade_Start(WIFI_SETUP_FADE_OUT_TO_WHITE, WIFI_SETUP_SCREEN_MAIN, GX_BLEND_PLANEMASK_BG2 | GX_BLEND_PLANEMASK_OBJ, 8);
    WifiSetupApp_SetStateFunc(WifiSetupOptions_End);
}

static void WifiSetupOptions_End(void) {
    if (WifiSetupFade_IsActive(WIFI_SETUP_SCREEN_SUB)) {
        return;
    }
    if (WifiSetupFade_IsActive(WIFI_SETUP_SCREEN_MAIN)) {
        return;
    }
    if (!WifiSetupButtonBar_IsNotClosing()) {
        return;
    }
    WifiSetupOam_Release(gWifiSetupOptions.oam);
    WifiSetupCursor_Hide();
    WifiSetupMessage_Hide();
    WifiSetupFile_Free(gWifiSetupOptions.graphics);
    WifiSetupDisplay_HidePlanes(WIFI_SETUP_SCREEN_SUB, GX_PLANEMASK_BG0);
    WifiSetupDisplay_HidePlanes(WIFI_SETUP_SCREEN_MAIN, GX_PLANEMASK_BG2 | GX_PLANEMASK_OBJ);
    if (!gWifiSetupOptions.confirmed) {
        WifiSetupApp_SetTransition(WIFI_SETUP_BANNER_KEEP, WIFI_SETUP_BUTTON_BAR_KEEP);
        WifiSetupApp_SetStateFunc(WifiSetupTopMenu_Init);
        return;
    }
    switch (gWifiSetupOptions.selected) {
    case 0:
        WifiSetupApp_SetTransition(WIFI_SETUP_BANNER_KEEP, WIFI_SETUP_BUTTON_BAR_CREATE);
        WifiSetupApp_SetStateFunc(WifiSetupSystemInfo_Init);
        break;
    case 1:
        WifiSetupApp_SetTransition(WIFI_SETUP_BANNER_KEEP, WIFI_SETUP_BUTTON_BAR_CREATE);
        WifiSetupApp_SetStateFunc(WifiSetupEraseConfirm_Init);
        break;
    case 2:
        WifiSetupApp_SetTransition(WIFI_SETUP_BANNER_KEEP, WIFI_SETUP_BUTTON_BAR_CREATE);
        WifiSetupApp_SetStateFunc(WifiSetupTransferIntro_Init);
        break;
    }
}

static void WifiSetupOptions_MoveCursor(int dir) {
    int idx;
    if (dir == WIFI_SETUP_CURSOR_UP) {
        gWifiSetupOptions.selected = FX_ModS32(gWifiSetupOptions.selected + 2, 3);
    } else {
        gWifiSetupOptions.selected = FX_ModS32(gWifiSetupOptions.selected + 1, 3);
    }
    WifiSetupSound_Play(8);
    idx = gWifiSetupOptions.selected * 4;
    WifiSetupCursor_ShowCorners(gWifiSetupOptionsCursorLeft[idx], gWifiSetupOptionsCursorRight[idx], gWifiSetupOptionsCursorTop[idx], gWifiSetupOptionsCursorBottom[idx]);
}

static void WifiSetupOptions_HighlightSelection(void) {
    WifiSetupPalette_LoadRow(gWifiSetupOptions.graphics, gWifiSetupOptionsPaletteRows[gWifiSetupOptions.selected], gWifiSetupOptionsPaletteRows[gWifiSetupOptions.selected]);
}

static void WifiSetupTransferring_Init(void) {
    WifiSetupTransferring_LoadGraphics();
    WifiSetup_PrintMessage(0x1e);
    WifiSetupBusyIcon_Create(0);
    WifiSetupSignalIcon_Create(1);
    WifiSetupSound_Play(0xb);
    WifiSetupApp_SetStateFunc(WifiSetupTransferring_FadeIn);
}

static void WifiSetupTransferring_LoadGraphics(void) {
    WifiSetup_LoadGraphics(gWifiSetupTransferringYb5MultiNscPath, GX_LoadBG2Scr);
    G2S_SetBG0Priority(3);
    G2S_SetBG1Priority(3);
    G2_SetBG0Priority(3);
    G2_SetBG1Priority(3);
    G2_SetBG2Priority(3);
}

static void WifiSetupTransferring_FadeIn(void) {
    WifiSetupFade_Start(WIFI_SETUP_FADE_IN_FROM_WHITE, WIFI_SETUP_SCREEN_MAIN, GX_BLEND_PLANEMASK_BG0 | GX_BLEND_PLANEMASK_BG2 | GX_BLEND_PLANEMASK_OBJ, 8);
    WifiSetupDisplay_ShowPlanes(WIFI_SETUP_SCREEN_MAIN, GX_PLANEMASK_BG0 | GX_PLANEMASK_BG2 | GX_PLANEMASK_OBJ);
    WifiSetupApp_SetStateFunc(WifiSetupTransferring_WaitFadeIn);
}

static void WifiSetupTransferring_WaitFadeIn(void) {
    if (WifiSetupFade_IsActive(WIFI_SETUP_SCREEN_MAIN)) {
        return;
    }
    WifiSetupTransfer_SetCallback(WifiSetupTransferring_OnTransferEvent);
    WifiSetupApp_SetStateFunc(WifiSetupTransferring_Main);
}

static void WifiSetupTransferring_Main(void) {
    WifiSetupTransferring_HandleInput();
    WifiSetupTransferring_Update();
}

static void WifiSetupTransferring_HandleInput(void) {
}

static void WifiSetupTransferring_Update(void) {
}

static void WifiSetupTransferring_FadeOut(void) {
    WifiSetupFade_Start(WIFI_SETUP_FADE_OUT_TO_WHITE, WIFI_SETUP_SCREEN_MAIN, GX_BLEND_PLANEMASK_BG0 | GX_BLEND_PLANEMASK_BG2 | GX_BLEND_PLANEMASK_OBJ, 8);
    WifiSetupApp_SetStateFunc(WifiSetupTransferring_End);
}

static void WifiSetupTransferring_End(void) {
    if (WifiSetupFade_IsActive(WIFI_SETUP_SCREEN_MAIN)) {
        return;
    }
    if (!WifiSetupTransfer_IsFinished()) {
        return;
    }
    WifiSetupSignalIcon_Destroy();
    WifiSetupBusyIcon_Destroy();
    WifiSetupText_FreeBgCanvas(WIFI_SETUP_SCREEN_MAIN);
    WifiSetupDisplay_HidePlanes(WIFI_SETUP_SCREEN_MAIN, GX_PLANEMASK_BG0 | GX_PLANEMASK_BG2 | GX_PLANEMASK_OBJ);
    WifiSetupApp_SetTransition(WIFI_SETUP_BANNER_KEEP, WIFI_SETUP_BUTTON_BAR_CREATE);
    if (gWifiSetupTransferResult == WIFI_SETUP_TRANSFER_RESULT_FAILED) {
        WifiSetupApp_SetStateFunc(WifiSetupTransferFailed_Init);
    } else if (gWifiSetupTransferResult == WIFI_SETUP_TRANSFER_RESULT_CANCELLED) {
        WifiSetupApp_SetStateFunc(WifiSetupTransferCancelled_Init);
    } else {
        WifiSetupApp_SetStateFunc(WifiSetupTransferDone_Init);
    }
}

static void WifiSetupTransferring_OnTransferEvent(int event) {
    if (event == WIFI_SETUP_TRANSFER_EVENT_DONE) {
        WifiSetupConnections_Reset();
        gWifiSetupTransferResult = WIFI_SETUP_TRANSFER_RESULT_DONE;
        WifiSetupSound_Stop();
        WifiSetupSound_Play(0x10);
    } else if (event == WIFI_SETUP_TRANSFER_EVENT_STOPPED) {
        gWifiSetupTransferResult = WIFI_SETUP_TRANSFER_RESULT_CANCELLED;
        WifiSetupSound_Stop();
        WifiSetupSound_Play(0x12);
    } else {
        gWifiSetupTransferResult = WIFI_SETUP_TRANSFER_RESULT_FAILED;
        WifiSetupSound_Stop();
        WifiSetupSound_Play(0x12);
    }
    WifiSetupTransfer_SetCallback(NULL);
    WifiSetupTransfer_Cancel();
    WifiSetupApp_SetStateFunc(WifiSetupTransferring_FadeOut);
}

static void WifiSetupTransferDone_Init(void) {
    WifiSetupTransferDone_LoadGraphics();
    WifiSetup_PrintMessage(0x1f);
    WifiSetupApp_SetStateFunc(WifiSetupTransferDone_FadeIn);
}

static void WifiSetupTransferDone_LoadGraphics(void) {
    G2S_SetBG0Priority(3);
    G2S_SetBG1Priority(3);
    G2_SetBG0Priority(3);
    G2_SetBG1Priority(3);
    G2_SetBG2Priority(3);
}

static void WifiSetupTransferDone_FadeIn(void) {
    WifiSetupFade_Start(WIFI_SETUP_FADE_IN_FROM_WHITE, WIFI_SETUP_SCREEN_MAIN, GX_BLEND_PLANEMASK_BG0 | GX_BLEND_PLANEMASK_BG2 | GX_BLEND_PLANEMASK_OBJ, 8);
    WifiSetupDisplay_ShowPlanes(WIFI_SETUP_SCREEN_MAIN, GX_PLANEMASK_BG0 | GX_PLANEMASK_BG2 | GX_PLANEMASK_OBJ);
    WifiSetupApp_SetStateFunc(WifiSetupTransferDone_WaitFadeIn);
}

static void WifiSetupTransferDone_WaitFadeIn(void) {
    if (WifiSetupFade_IsActive(WIFI_SETUP_SCREEN_MAIN)) {
        return;
    }
    WifiSetupButtonBar_Show(5);
    WifiSetupApp_SetStateFunc(WifiSetupTransferDone_WaitButtonBar);
}

static void WifiSetupTransferDone_WaitButtonBar(void) {
    if (WifiSetupButtonBar_GetSelected() == WIFI_SETUP_SELECTED_NOT_SHOWN) {
        return;
    }
    WifiSetupButtonBar_Unlock();
    WifiSetupApp_SetStateFunc(WifiSetupTransferDone_Main);
}

static void WifiSetupTransferDone_Main(void) {
    WifiSetupTransferDone_HandleInput();
    WifiSetupTransferDone_Update();
    WifiSetupTransferDone_CheckButtons();
}

static void WifiSetupTransferDone_HandleInput(void) {
    if (WifiSetupInput_IsKeyPressed(PAD_BUTTON_A)) {
        WifiSetupButtonBar_SelectIfNone(0);
    }
}

static void WifiSetupTransferDone_Update(void) {
}

static void WifiSetupTransferDone_CheckButtons(void) {
    if (WifiSetupButtonBar_GetSelected() != 0) {
        return;
    }
    WifiSetupSound_Play(6);
    WifiSetupApp_SetStateFunc(WifiSetupTransferDone_Exit);
}

static void WifiSetupTransferDone_Exit(void) {
    WifiSetupButtonBar_Lock();
    WifiSetupFade_StartDelay(8);
    WifiSetupApp_SetStateFunc(WifiSetupTransferDone_WaitFadeOut);
}

static void WifiSetupTransferDone_WaitFadeOut(void) {
    if (WifiSetupFade_IsActive(WIFI_SETUP_SCREEN_SUB)) {
        return;
    }
    WifiSetupFade_Start(WIFI_SETUP_FADE_OUT_TO_WHITE, WIFI_SETUP_SCREEN_SUB, GX_BLEND_PLANEMASK_BG0 | GX_BLEND_PLANEMASK_BG1 | GX_BLEND_PLANEMASK_BG2 | GX_BLEND_PLANEMASK_BG3 | GX_BLEND_PLANEMASK_OBJ | GX_BLEND_PLANEMASK_BD, 0x40);
    WifiSetupFade_Start(WIFI_SETUP_FADE_OUT_TO_WHITE, WIFI_SETUP_SCREEN_MAIN, GX_BLEND_PLANEMASK_BG0 | GX_BLEND_PLANEMASK_BG1 | GX_BLEND_PLANEMASK_BG2 | GX_BLEND_PLANEMASK_BG3 | GX_BLEND_PLANEMASK_OBJ | GX_BLEND_PLANEMASK_BD, 0x40);
    WifiSetupApp_SetStateFunc(WifiSetupTransferDone_PowerOff);
}

static void WifiSetupTransferDone_PowerOff(void) {
    if (WifiSetupFade_IsActive(WIFI_SETUP_SCREEN_SUB)) {
        return;
    }
    if (WifiSetupFade_IsActive(WIFI_SETUP_SCREEN_MAIN)) {
        return;
    }
    OS_SpinWait(0x1000000);
    PM_ForceToPowerOff();
}

static void WifiSetupTransferInfo_Init(void) {
    WifiSetupTransferInfo_LoadGraphics();
    WifiSetup_PrintMessage(0x1a);
    WifiSetupApp_SetStateFunc(WifiSetupTransferInfo_FadeIn);
}

static void WifiSetupTransferInfo_LoadGraphics(void) {
    G2S_SetBG0Priority(3);
    G2S_SetBG1Priority(3);
    G2_SetBG0Priority(3);
    G2_SetBG1Priority(3);
    G2_SetBG2Priority(3);
}

static void WifiSetupTransferInfo_FadeIn(void) {
    WifiSetupFade_Start(WIFI_SETUP_FADE_IN_FROM_WHITE, WIFI_SETUP_SCREEN_MAIN, GX_BLEND_PLANEMASK_BG0 | GX_BLEND_PLANEMASK_BG2 | GX_BLEND_PLANEMASK_OBJ, 8);
    WifiSetupDisplay_ShowPlanes(WIFI_SETUP_SCREEN_MAIN, GX_PLANEMASK_BG0 | GX_PLANEMASK_BG2 | GX_PLANEMASK_OBJ);
    WifiSetupApp_SetStateFunc(WifiSetupTransferInfo_WaitFadeIn);
}

static void WifiSetupTransferInfo_WaitFadeIn(void) {
    if (WifiSetupFade_IsActive(WIFI_SETUP_SCREEN_SUB)) {
        return;
    }
    if (WifiSetupFade_IsActive(WIFI_SETUP_SCREEN_MAIN)) {
        return;
    }
    WifiSetupButtonBar_Show(4);
    WifiSetupApp_SetStateFunc(WifiSetupTransferInfo_WaitButtonBar);
}

static void WifiSetupTransferInfo_WaitButtonBar(void) {
    if (WifiSetupButtonBar_GetSelected() == WIFI_SETUP_SELECTED_NOT_SHOWN) {
        return;
    }
    WifiSetupButtonBar_Unlock();
    WifiSetupApp_SetStateFunc(WifiSetupTransferInfo_Main);
}

static void WifiSetupTransferInfo_Main(void) {
    WifiSetupTransferInfo_HandleInput();
    WifiSetupTransferInfo_Update();
    WifiSetupTransferInfo_CheckButtons();
}

static void WifiSetupTransferInfo_HandleInput(void) {
    if (WifiSetupInput_IsKeyPressed(PAD_BUTTON_A)) {
        WifiSetupButtonBar_SelectIfNone(0);
    }
}

static void WifiSetupTransferInfo_Update(void) {
}

static void WifiSetupTransferInfo_CheckButtons(void) {
    if (WifiSetupButtonBar_GetSelected() != 0) {
        return;
    }
    WifiSetupSound_Play(6);
    WifiSetupApp_SetStateFunc(WifiSetupTransferInfo_Exit);
}

static void WifiSetupTransferInfo_Exit(void) {
    WifiSetupButtonBar_Lock();
    WifiSetupFade_StartDelay(8);
    WifiSetupApp_SetStateFunc(WifiSetupTransferInfo_WaitFadeOut);
}

static void WifiSetupTransferInfo_WaitFadeOut(void) {
    if (WifiSetupFade_IsActive(WIFI_SETUP_SCREEN_SUB)) {
        return;
    }
    WifiSetupButtonBar_Close();
    WifiSetupFade_Start(WIFI_SETUP_FADE_OUT_TO_WHITE, WIFI_SETUP_SCREEN_MAIN, GX_BLEND_PLANEMASK_BG0 | GX_BLEND_PLANEMASK_BG2 | GX_BLEND_PLANEMASK_OBJ, 8);
    WifiSetupApp_SetStateFunc(WifiSetupTransferInfo_End);
}

static void WifiSetupTransferInfo_End(void) {
    if (WifiSetupFade_IsActive(WIFI_SETUP_SCREEN_MAIN)) {
        return;
    }
    if (!WifiSetupButtonBar_IsNotClosing()) {
        return;
    }
    WifiSetupText_FreeBgCanvas(WIFI_SETUP_SCREEN_MAIN);
    WifiSetupDisplay_HidePlanes(WIFI_SETUP_SCREEN_MAIN, GX_PLANEMASK_BG0 | GX_PLANEMASK_BG2 | GX_PLANEMASK_OBJ);
    WifiSetupApp_SetTransition(WIFI_SETUP_BANNER_KEEP, WIFI_SETUP_BUTTON_BAR_CREATE);
    WifiSetupApp_SetStateFunc(WifiSetupTransferWait_Init);
}

static void WifiSetupTransferIntro_Init(void) {
    gWifiSetupTransferIntroProceed = FALSE;
    WifiSetupTransferIntro_LoadGraphics();
    WifiSetupBackground_LoadHeader(0x13);
    WifiSetupMessage_Show(0x3c, -1, 0);
    WifiSetup_PrintMessage(0x1b);
    WifiSetupApp_SetStateFunc(WifiSetupTransferIntro_FadeIn);
}

static void WifiSetupTransferIntro_LoadGraphics(void) {
    WifiSetup_LoadGraphics(gWifiSetupTransferIntroYb5MultiNscPath, GX_LoadBG2Scr);
    G2S_SetBG0Priority(3);
    G2S_SetBG1Priority(3);
    G2_SetBG0Priority(3);
    G2_SetBG1Priority(3);
    G2_SetBG2Priority(3);
}

static void WifiSetupTransferIntro_FadeIn(void) {
    WifiSetupFade_Start(WIFI_SETUP_FADE_IN_FROM_WHITE, WIFI_SETUP_SCREEN_SUB, GX_BLEND_PLANEMASK_BG0, 8);
    WifiSetupFade_Start(WIFI_SETUP_FADE_IN_FROM_WHITE, WIFI_SETUP_SCREEN_MAIN, GX_BLEND_PLANEMASK_BG0 | GX_BLEND_PLANEMASK_BG2 | GX_BLEND_PLANEMASK_OBJ, 8);
    WifiSetupDisplay_ShowPlanes(WIFI_SETUP_SCREEN_SUB, GX_PLANEMASK_BG0);
    WifiSetupDisplay_ShowPlanes(WIFI_SETUP_SCREEN_MAIN, GX_PLANEMASK_BG0 | GX_PLANEMASK_BG2 | GX_PLANEMASK_OBJ);
    WifiSetupApp_SetStateFunc(WifiSetupTransferIntro_WaitFadeIn);
}

static void WifiSetupTransferIntro_WaitFadeIn(void) {
    if (WifiSetupFade_IsActive(WIFI_SETUP_SCREEN_MAIN)) {
        return;
    }
    WifiSetupButtonBar_Show(3);
    WifiSetupApp_SetStateFunc(WifiSetupTransferIntro_WaitButtonBar);
}

static void WifiSetupTransferIntro_WaitButtonBar(void) {
    if (WifiSetupButtonBar_GetSelected() == WIFI_SETUP_SELECTED_NOT_SHOWN) {
        return;
    }
    WifiSetupButtonBar_Unlock();
    WifiSetupApp_SetStateFunc(WifiSetupTransferIntro_Main);
}

static void WifiSetupTransferIntro_Main(void) {
    WifiSetupTransferIntro_HandleInput();
    WifiSetupTransferIntro_Update();
    WifiSetupTransferIntro_CheckButtons();
}

static void WifiSetupTransferIntro_HandleInput(void) {
    if (WifiSetupInput_IsKeyPressed(PAD_BUTTON_A)) {
        WifiSetupButtonBar_SelectIfNone(1);
    }
    if (WifiSetupInput_IsKeyPressed(PAD_BUTTON_B)) {
        WifiSetupButtonBar_SelectIfNone(0);
    }
}

static void WifiSetupTransferIntro_Update(void) {
}

static void WifiSetupTransferIntro_CheckButtons(void) {
    switch (WifiSetupButtonBar_GetSelected()) {
    case 0:
        WifiSetupSound_Play(7);
        break;
    case 1:
        WifiSetupSound_Play(6);
        gWifiSetupTransferIntroProceed = TRUE;
        break;
    default:
        return;
    }
    WifiSetupApp_SetStateFunc(WifiSetupTransferIntro_Exit);
}

static void WifiSetupTransferIntro_Exit(void) {
    WifiSetupButtonBar_Lock();
    WifiSetupFade_StartDelay(8);
    WifiSetupApp_SetStateFunc(WifiSetupTransferIntro_WaitFadeOut);
}

static void WifiSetupTransferIntro_WaitFadeOut(void) {
    if (WifiSetupFade_IsActive(WIFI_SETUP_SCREEN_SUB)) {
        return;
    }
    WifiSetupButtonBar_Close();
    if (!gWifiSetupTransferIntroProceed) {
        WifiSetupFade_Start(WIFI_SETUP_FADE_OUT_TO_WHITE, WIFI_SETUP_SCREEN_SUB, GX_BLEND_PLANEMASK_BG0, 8);
    }
    WifiSetupFade_Start(WIFI_SETUP_FADE_OUT_TO_WHITE, WIFI_SETUP_SCREEN_MAIN, GX_BLEND_PLANEMASK_BG0 | GX_BLEND_PLANEMASK_BG2 | GX_BLEND_PLANEMASK_OBJ, 8);
    WifiSetupApp_SetStateFunc(WifiSetupTransferIntro_End);
}

static void WifiSetupTransferIntro_End(void) {
    if (WifiSetupFade_IsActive(WIFI_SETUP_SCREEN_MAIN)) {
        return;
    }
    if (!gWifiSetupTransferIntroProceed) {
        if (WifiSetupFade_IsActive(WIFI_SETUP_SCREEN_SUB)) {
            return;
        }
    }
    if (!WifiSetupButtonBar_IsNotClosing()) {
        return;
    }
    WifiSetupText_FreeBgCanvas(WIFI_SETUP_SCREEN_MAIN);
    if (!gWifiSetupTransferIntroProceed) {
        WifiSetupMessage_Hide();
        WifiSetupDisplay_HidePlanes(WIFI_SETUP_SCREEN_SUB, GX_PLANEMASK_BG0);
    }
    WifiSetupDisplay_HidePlanes(WIFI_SETUP_SCREEN_MAIN, GX_PLANEMASK_BG0 | GX_PLANEMASK_BG2 | GX_PLANEMASK_OBJ);
    if (!gWifiSetupTransferIntroProceed) {
        WifiSetupApp_SetTransition(WIFI_SETUP_BANNER_KEEP, WIFI_SETUP_BUTTON_BAR_CREATE);
        WifiSetupApp_SetStateFunc(WifiSetupOptions_Init);
    } else {
        WifiSetupApp_SetTransition(WIFI_SETUP_BANNER_KEEP, WIFI_SETUP_BUTTON_BAR_CREATE);
        WifiSetupApp_SetStateFunc(WifiSetupTransferInfo_Init);
    }
}

static void WifiSetupTransferCancelled_Init(void) {
    gWifiSetupTransferCancelledTimer = 0;
    WifiSetupTransferCancelled_LoadGraphics();
    WifiSetup_PrintMessage(0x21);
    WifiSetupApp_SetStateFunc(WifiSetupTransferCancelled_FadeIn);
}

static void WifiSetupTransferCancelled_LoadGraphics(void) {
    WifiSetup_LoadGraphics(gWifiSetupTransferCancelledYb5MultiNscPath, GX_LoadBG2Scr);
    G2S_SetBG0Priority(3);
    G2S_SetBG1Priority(3);
    G2_SetBG1Priority(3);
    G2_SetBG2Priority(3);
}

static void WifiSetupTransferCancelled_FadeIn(void) {
    WifiSetupFade_Start(WIFI_SETUP_FADE_IN_FROM_WHITE, WIFI_SETUP_SCREEN_MAIN, GX_BLEND_PLANEMASK_BG0 | GX_BLEND_PLANEMASK_BG2 | GX_BLEND_PLANEMASK_OBJ, 8);
    WifiSetupDisplay_ShowPlanes(WIFI_SETUP_SCREEN_MAIN, GX_PLANEMASK_BG0 | GX_PLANEMASK_BG2 | GX_PLANEMASK_OBJ);
    WifiSetupApp_SetStateFunc(WifiSetupTransferCancelled_WaitFadeIn);
}

static void WifiSetupTransferCancelled_WaitFadeIn(void) {
    if (WifiSetupFade_IsActive(WIFI_SETUP_SCREEN_MAIN)) {
        return;
    }
    if (!WifiSetupTransfer_IsFinished()) {
        return;
    }
    WifiSetupApp_SetStateFunc(WifiSetupTransferCancelled_Main);
}

static void WifiSetupTransferCancelled_Main(void) {
    WifiSetupTransferCancelled_UpdateTimer();
    WifiSetupTransferCancelled_Update();
}

static void WifiSetupTransferCancelled_Update(void) {
}

static void WifiSetupTransferCancelled_FadeOut(void) {
    WifiSetupFade_Start(WIFI_SETUP_FADE_OUT_TO_WHITE, WIFI_SETUP_SCREEN_SUB, GX_BLEND_PLANEMASK_BG0, 8);
    WifiSetupFade_Start(WIFI_SETUP_FADE_OUT_TO_WHITE, WIFI_SETUP_SCREEN_MAIN, GX_BLEND_PLANEMASK_BG0 | GX_BLEND_PLANEMASK_BG2 | GX_BLEND_PLANEMASK_OBJ, 8);
    WifiSetupApp_SetStateFunc(WifiSetupTransferCancelled_End);
}

static void WifiSetupTransferCancelled_End(void) {
    if (WifiSetupFade_IsActive(WIFI_SETUP_SCREEN_SUB)) {
        return;
    }
    if (WifiSetupFade_IsActive(WIFI_SETUP_SCREEN_MAIN)) {
        return;
    }
    WifiSetupText_FreeBgCanvas(WIFI_SETUP_SCREEN_MAIN);
    WifiSetupMessage_Hide();
    WifiSetupDisplay_HidePlanes(WIFI_SETUP_SCREEN_SUB, GX_PLANEMASK_BG0);
    WifiSetupDisplay_HidePlanes(WIFI_SETUP_SCREEN_MAIN, GX_PLANEMASK_BG0 | GX_PLANEMASK_BG2 | GX_PLANEMASK_OBJ);
    WifiSetupApp_SetTransition(WIFI_SETUP_BANNER_KEEP, WIFI_SETUP_BUTTON_BAR_CREATE);
    WifiSetupApp_SetStateFunc(WifiSetupOptions_Init);
}

static void WifiSetupTransferCancelled_UpdateTimer(void) {
    if (++gWifiSetupTransferCancelledTimer < 0x78) {
        return;
    }
    WifiSetupApp_SetStateFunc(WifiSetupTransferCancelled_FadeOut);
}

static void WifiSetupTransferFailed_Init(void) {
    WifiSetupTransferFailed_LoadGraphics();
    WifiSetup_PrintMessage(0x20);
    gWifiSetupTransferFailed[0] = WifiSetupMessage_Show(0x3c, -1, 0);
    WifiSetupApp_SetStateFunc(WifiSetupTransferFailed_FadeIn);
}

static void WifiSetupTransferFailed_LoadGraphics(void) {
    WifiSetup_LoadGraphics(gWifiSetupTransferFailedYb5MultiNscPath, GX_LoadBG2Scr);
    G2S_SetBG0Priority(3);
    G2S_SetBG1Priority(3);
    G2_SetBG0Priority(3);
    G2_SetBG1Priority(3);
    G2_SetBG2Priority(3);
}

static void WifiSetupTransferFailed_FadeIn(void) {
    WifiSetupFade_Start(WIFI_SETUP_FADE_IN_FROM_WHITE, WIFI_SETUP_SCREEN_MAIN, GX_BLEND_PLANEMASK_BG0 | GX_BLEND_PLANEMASK_BG2 | GX_BLEND_PLANEMASK_OBJ, 8);
    WifiSetupDisplay_ShowPlanes(WIFI_SETUP_SCREEN_MAIN, GX_PLANEMASK_BG0 | GX_PLANEMASK_BG2 | GX_PLANEMASK_OBJ);
    if (gWifiSetupTransferFailed[0] != 0) {
        WifiSetupFade_Start(WIFI_SETUP_FADE_IN_FROM_WHITE, WIFI_SETUP_SCREEN_SUB, GX_BLEND_PLANEMASK_BG0, 8);
        WifiSetupDisplay_ShowPlanes(WIFI_SETUP_SCREEN_SUB, GX_PLANEMASK_BG0);
    }
    WifiSetupApp_SetStateFunc(WifiSetupTransferFailed_WaitFadeIn);
}

static void WifiSetupTransferFailed_WaitFadeIn(void) {
    if (WifiSetupFade_IsActive(WIFI_SETUP_SCREEN_SUB)) {
        return;
    }
    if (WifiSetupFade_IsActive(WIFI_SETUP_SCREEN_MAIN)) {
        return;
    }
    WifiSetupButtonBar_Show(3);
    WifiSetupApp_SetStateFunc(WifiSetupTransferFailed_WaitButtonBar);
}

static void WifiSetupTransferFailed_WaitButtonBar(void) {
    if (WifiSetupButtonBar_GetSelected() == WIFI_SETUP_SELECTED_NOT_SHOWN) {
        return;
    }
    if (!WifiSetupTransfer_IsFinished()) {
        return;
    }
    WifiSetupButtonBar_Unlock();
    WifiSetupApp_SetStateFunc(WifiSetupTransferFailed_Main);
}

static void WifiSetupTransferFailed_Main(void) {
    WifiSetupTransferFailed_HandleInput();
    WifiSetupTransferFailed_Update();
    WifiSetupTransferFailed_CheckButtons();
}

static void WifiSetupTransferFailed_HandleInput(void) {
    if (WifiSetupInput_IsKeyPressed(PAD_BUTTON_A)) {
        WifiSetupButtonBar_SelectIfNone(1);
    }
    if (WifiSetupInput_IsKeyPressed(PAD_BUTTON_B)) {
        WifiSetupButtonBar_SelectIfNone(0);
    }
}

static void WifiSetupTransferFailed_Update(void) {
}

static void WifiSetupTransferFailed_CheckButtons(void) {
    int selected = WifiSetupButtonBar_GetSelected();
    if (selected != 0) {
        if (selected != 1) {
            return;
        }
        gWifiSetupTransferFailed[1] = 1;
        WifiSetupSound_Play(6);
    } else {
        gWifiSetupTransferFailed[1] = 0;
        WifiSetupSound_Play(7);
    }
    WifiSetupApp_SetStateFunc(WifiSetupTransferFailed_Exit);
}

static void WifiSetupTransferFailed_Exit(void) {
    WifiSetupButtonBar_Lock();
    WifiSetupFade_StartDelay(8);
    WifiSetupApp_SetStateFunc(WifiSetupTransferFailed_WaitFadeOut);
}

static void WifiSetupTransferFailed_WaitFadeOut(void) {
    if (WifiSetupFade_IsActive(WIFI_SETUP_SCREEN_SUB)) {
        return;
    }
    WifiSetupButtonBar_Close();
    if (gWifiSetupTransferFailed[1] == 0) {
        WifiSetupFade_Start(WIFI_SETUP_FADE_OUT_TO_WHITE, WIFI_SETUP_SCREEN_SUB, GX_BLEND_PLANEMASK_BG0, 8);
    }
    WifiSetupFade_Start(WIFI_SETUP_FADE_OUT_TO_WHITE, WIFI_SETUP_SCREEN_MAIN, GX_BLEND_PLANEMASK_BG0 | GX_BLEND_PLANEMASK_BG2 | GX_BLEND_PLANEMASK_OBJ, 8);
    WifiSetupApp_SetStateFunc(WifiSetupTransferFailed_End);
}

static void WifiSetupTransferFailed_End(void) {
    if (WifiSetupFade_IsActive(WIFI_SETUP_SCREEN_SUB)) {
        return;
    }
    if (WifiSetupFade_IsActive(WIFI_SETUP_SCREEN_MAIN)) {
        return;
    }
    if (!WifiSetupButtonBar_IsNotClosing()) {
        return;
    }
    WifiSetupText_FreeBgCanvas(WIFI_SETUP_SCREEN_MAIN);
    if (gWifiSetupTransferFailed[1] == 0) {
        WifiSetupMessage_Hide();
        WifiSetupDisplay_HidePlanes(WIFI_SETUP_SCREEN_SUB, GX_PLANEMASK_BG0);
    }
    WifiSetupDisplay_HidePlanes(WIFI_SETUP_SCREEN_MAIN, GX_PLANEMASK_BG0 | GX_PLANEMASK_BG2 | GX_PLANEMASK_OBJ);
    if (gWifiSetupTransferFailed[1] == 0) {
        WifiSetupApp_SetTransition(WIFI_SETUP_BANNER_KEEP, WIFI_SETUP_BUTTON_BAR_CREATE);
        WifiSetupApp_SetStateFunc(WifiSetupOptions_Init);
    } else {
        WifiSetupApp_SetTransition(WIFI_SETUP_BANNER_KEEP, WIFI_SETUP_BUTTON_BAR_CREATE);
        WifiSetupApp_SetStateFunc(WifiSetupTransferWait_Init);
    }
}

static void WifiSetupTransferConfirm_Init(void) {
    u16 buf[11];
    WifiSetupMbParentUser *user = WifiSetupTransfer_GetChildUser();
    WifiSetupCanvas *win = WifiSetupText_InitBgCanvas(WIFI_SETUP_SCREEN_MAIN, 0);
    gWifiSetupTransferConfirm[1] = 0;
    gWifiSetupTransferConfirm[0] = 0;
    WifiSetupTransferConfirm_LoadGraphics();
    MIi_CpuClear16(0, buf, sizeof(buf));
    MIi_CpuCopy16(user->name, buf, user->nameLength * 2);
    WifiSetupText_DrawInRect(win, 8, 0x35, 0xf0, 0x1c, 2, 0x480, buf);
    WifiSetupText_MarkDirty(win);
    WifiSetupTransfer_SetCallback(WifiSetupTransferConfirm_OnTransferEvent);
    WifiSetupDialog_Open(0x1d, 4, 0, -1, 0);
    WifiSetupApp_SetStateFunc(WifiSetupTransferConfirm_FadeIn);
}

static void WifiSetupTransferConfirm_LoadGraphics(void) {
    WifiSetup_LoadGraphics(gWifiSetupTransferConfirmJb5MoveNscPath, GX_LoadBG2Scr);
    G2S_SetBG0Priority(3);
    G2S_SetBG1Priority(3);
    G2_SetBG0Priority(3);
    G2_SetBG1Priority(3);
    G2_SetBG2Priority(3);
}

static void WifiSetupTransferConfirm_FadeIn(void) {
    WifiSetupFade_Start(WIFI_SETUP_FADE_IN_FROM_WHITE, WIFI_SETUP_SCREEN_MAIN, GX_BLEND_PLANEMASK_BG0 | GX_BLEND_PLANEMASK_BG2 | GX_BLEND_PLANEMASK_OBJ, 8);
    WifiSetupDisplay_ShowPlanes(WIFI_SETUP_SCREEN_MAIN, GX_PLANEMASK_BG0 | GX_PLANEMASK_BG2 | GX_PLANEMASK_OBJ);
    WifiSetupApp_SetStateFunc(WifiSetupTransferConfirm_WaitFadeIn);
}

static void WifiSetupTransferConfirm_WaitFadeIn(void) {
    if (WifiSetupFade_IsActive(WIFI_SETUP_SCREEN_MAIN)) {
        return;
    }
    WifiSetupApp_SetStateFunc(WifiSetupTransferConfirm_WaitDialog);
}

static void WifiSetupTransferConfirm_WaitDialog(void) {
    if (WifiSetupDialog_GetSelected() == WIFI_SETUP_SELECTED_NOT_SHOWN) {
        return;
    }
    WifiSetupApp_SetStateFunc(WifiSetupTransferConfirm_Main);
}

static void WifiSetupTransferConfirm_Main(void) {
    WifiSetupTransferConfirm_HandleInput();
    WifiSetupTransferConfirm_Update();
    switch (WifiSetupDialog_GetSelected()) {
    case 0:
        gWifiSetupTransferConfirm[1] = 0;
        WifiSetupSound_Play(7);
        break;
    case 1:
        gWifiSetupTransferConfirm[1] = 1;
        WifiSetupSound_Play(0xe);
        break;
    default:
        return;
    }
    WifiSetupTransfer_SetCallback(NULL);
    WifiSetupDialog_Close();
    WifiSetupApp_SetStateFunc(WifiSetupTransferConfirm_WaitDialogClosed);
}

static void WifiSetupTransferConfirm_HandleInput(void) {
}

static void WifiSetupTransferConfirm_Update(void) {
}

static void WifiSetupTransferConfirm_WaitDialogClosed(void) {
    if (WifiSetupDialog_IsOpen()) {
        return;
    }
    if (gWifiSetupTransferConfirm[1] == 0) {
        WifiSetupFade_Start(WIFI_SETUP_FADE_OUT_TO_WHITE, WIFI_SETUP_SCREEN_SUB, GX_BLEND_PLANEMASK_BG0, 8);
    }
    WifiSetupFade_Start(WIFI_SETUP_FADE_OUT_TO_WHITE, WIFI_SETUP_SCREEN_MAIN, GX_BLEND_PLANEMASK_BG0 | GX_BLEND_PLANEMASK_BG2 | GX_BLEND_PLANEMASK_OBJ, 8);
    WifiSetupApp_SetStateFunc(WifiSetupTransferConfirm_WaitFadeOut);
}

static void WifiSetupTransferConfirm_WaitFadeOut(void) {
    if (WifiSetupFade_IsActive(WIFI_SETUP_SCREEN_SUB)) {
        return;
    }
    if (WifiSetupFade_IsActive(WIFI_SETUP_SCREEN_MAIN)) {
        return;
    }
    if (gWifiSetupTransferConfirm[0] == 0 && gWifiSetupTransferConfirm[1] == 1) {
        WifiSetupTransfer_StartDownload();
    } else {
        WifiSetupTransfer_Cancel();
    }
    WifiSetupApp_SetStateFunc(WifiSetupTransferConfirm_End);
}

static void WifiSetupTransferConfirm_End(void) {
    if (gWifiSetupTransferConfirm[0] != 0 || gWifiSetupTransferConfirm[1] == 0) {
        if (!WifiSetupTransfer_IsFinished()) {
            return;
        }
    }
    WifiSetupText_FreeBgCanvas(WIFI_SETUP_SCREEN_MAIN);
    WifiSetupDisplay_HidePlanes(WIFI_SETUP_SCREEN_MAIN, GX_PLANEMASK_BG0 | GX_PLANEMASK_BG2 | GX_PLANEMASK_OBJ);
    if (gWifiSetupTransferConfirm[1] == 0) {
        WifiSetupMessage_Hide();
        WifiSetupDisplay_HidePlanes(WIFI_SETUP_SCREEN_SUB, GX_PLANEMASK_BG0);
    }
    WifiSetupApp_SetTransition(WIFI_SETUP_BANNER_KEEP, WIFI_SETUP_BUTTON_BAR_CREATE);
    if (gWifiSetupTransferConfirm[0] != 0) {
        WifiSetupApp_SetStateFunc(WifiSetupTransferFailed_Init);
    } else if (gWifiSetupTransferConfirm[1] == 0) {
        WifiSetupDisplay_HidePlanes(WIFI_SETUP_SCREEN_SUB, GX_PLANEMASK_BG0);
        WifiSetupApp_SetStateFunc(WifiSetupOptions_Init);
    } else {
        WifiSetupApp_SetStateFunc(WifiSetupTransferring_Init);
    }
}

static void WifiSetupTransferConfirm_OnTransferEvent(int event) {
    gWifiSetupTransferConfirm[0] = 1;
}

static BOOL WifiSetupTransferWait_IsLidClosed(void) {
    return PAD_DetectFold() ? TRUE : FALSE;
}

static void WifiSetupTransferWait_Init(void) {
    WifiSetupTransfer_Start(WifiSetupTransferWait_OnTransferEvent);
    gWifiSetupTransferWaitResult = WIFI_SETUP_TRANSFER_WAIT_BACK;
    WifiSetupTransferWait_LoadGraphics();
    WifiSetup_PrintMessage(0x1c);
    WifiSetupBusyIcon_Create(0);
    WifiSetupSound_Play(0xb);
    WifiSetupApp_SetStateFunc(WifiSetupTransferWait_FadeIn);
}

static void WifiSetupTransferWait_LoadGraphics(void) {
    WifiSetup_LoadGraphics(gWifiSetupTransferWaitYb5MultiNscPath, GX_LoadBG2Scr);
    G2S_SetBG0Priority(3);
    G2S_SetBG1Priority(3);
    G2_SetBG0Priority(3);
    G2_SetBG1Priority(3);
    G2_SetBG2Priority(3);
}

static void WifiSetupTransferWait_FadeIn(void) {
    WifiSetupFade_Start(WIFI_SETUP_FADE_IN_FROM_WHITE, WIFI_SETUP_SCREEN_MAIN, GX_BLEND_PLANEMASK_BG0 | GX_BLEND_PLANEMASK_BG2 | GX_BLEND_PLANEMASK_OBJ, 8);
    WifiSetupDisplay_ShowPlanes(WIFI_SETUP_SCREEN_MAIN, GX_PLANEMASK_BG0 | GX_PLANEMASK_BG2 | GX_PLANEMASK_OBJ);
    WifiSetupApp_SetStateFunc(WifiSetupTransferWait_WaitFadeIn);
}

static void WifiSetupTransferWait_WaitFadeIn(void) {
    if (WifiSetupFade_IsActive(WIFI_SETUP_SCREEN_MAIN)) {
        return;
    }
    WifiSetupButtonBar_Show(1);
    WifiSetupApp_SetStateFunc(WifiSetupTransferWait_WaitButtonBar);
}

static void WifiSetupTransferWait_WaitButtonBar(void) {
    if (WifiSetupButtonBar_GetSelected() == WIFI_SETUP_SELECTED_NOT_SHOWN) {
        return;
    }
    WifiSetupApp_SetStateFunc(WifiSetupTransferWait_Main);
}

static void WifiSetupTransferWait_Main(void) {
    WifiSetupTransferWait_HandleInput();
    WifiSetupTransferWait_Update();
    WifiSetupTransferWait_CheckButtons();
}

static void WifiSetupTransferWait_HandleInput(void) {
    if (WifiSetupInput_IsKeyPressed(PAD_BUTTON_B)) {
        WifiSetupButtonBar_SelectIfNone(0);
        return;
    }
    if (WifiSetupTransferWait_IsLidClosed()) {
        WifiSetupButtonBar_SelectIfNone(0);
    }
}

static void WifiSetupTransferWait_Update(void) {
}

static void WifiSetupTransferWait_CheckButtons(void) {
    if (WifiSetupButtonBar_GetSelected() != 0) {
        return;
    }
    WifiSetupSound_Stop();
    WifiSetupSound_Play(7);
    WifiSetupApp_SetStateFunc(WifiSetupTransferWait_Exit);
}

static void WifiSetupTransferWait_Exit(void) {
    if (gWifiSetupTransferWaitResult == WIFI_SETUP_TRANSFER_WAIT_BACK) {
        WifiSetupTransfer_Cancel();
    }
    WifiSetupButtonBar_Lock();
    WifiSetupFade_StartDelay(8);
    WifiSetupApp_SetStateFunc(WifiSetupTransferWait_WaitFadeOut);
}

static void WifiSetupTransferWait_WaitFadeOut(void) {
    if (WifiSetupFade_IsActive(WIFI_SETUP_SCREEN_SUB)) {
        return;
    }
    if (gWifiSetupTransferWaitResult == WIFI_SETUP_TRANSFER_WAIT_BACK) {
        if (!WifiSetupTransfer_IsFinished()) {
            return;
        }
    }
    WifiSetupButtonBar_Close();
    if (gWifiSetupTransferWaitResult == WIFI_SETUP_TRANSFER_WAIT_BACK) {
        WifiSetupFade_Start(WIFI_SETUP_FADE_OUT_TO_WHITE, WIFI_SETUP_SCREEN_SUB, GX_BLEND_PLANEMASK_BG0, 8);
    }
    WifiSetupFade_Start(WIFI_SETUP_FADE_OUT_TO_WHITE, WIFI_SETUP_SCREEN_MAIN, GX_BLEND_PLANEMASK_BG0 | GX_BLEND_PLANEMASK_BG2 | GX_BLEND_PLANEMASK_OBJ, 8);
    WifiSetupApp_SetStateFunc(WifiSetupTransferWait_End);
}

static void WifiSetupTransferWait_End(void) {
    if (WifiSetupFade_IsActive(WIFI_SETUP_SCREEN_MAIN)) {
        return;
    }
    if (gWifiSetupTransferWaitResult == WIFI_SETUP_TRANSFER_WAIT_BACK) {
        if (WifiSetupFade_IsActive(WIFI_SETUP_SCREEN_SUB)) {
            return;
        }
    }
    if (!WifiSetupButtonBar_IsNotClosing()) {
        return;
    }
    if (gWifiSetupTransferWaitResult == WIFI_SETUP_TRANSFER_WAIT_BACK) {
        if (!WifiSetupTransfer_IsFinished()) {
            return;
        }
    }
    WifiSetupBusyIcon_Destroy();
    WifiSetupText_FreeBgCanvas(WIFI_SETUP_SCREEN_MAIN);
    if (gWifiSetupTransferWaitResult == WIFI_SETUP_TRANSFER_WAIT_BACK) {
        WifiSetupMessage_Hide();
        WifiSetupDisplay_HidePlanes(WIFI_SETUP_SCREEN_SUB, GX_PLANEMASK_BG0);
    }
    WifiSetupDisplay_HidePlanes(WIFI_SETUP_SCREEN_MAIN, GX_PLANEMASK_BG0 | GX_PLANEMASK_BG2 | GX_PLANEMASK_OBJ);
    if (gWifiSetupTransferWaitResult == WIFI_SETUP_TRANSFER_WAIT_BACK) {
        WifiSetupApp_SetTransition(WIFI_SETUP_BANNER_KEEP, WIFI_SETUP_BUTTON_BAR_CREATE);
        WifiSetupApp_SetStateFunc(WifiSetupOptions_Init);
    } else if (gWifiSetupTransferWaitResult == WIFI_SETUP_TRANSFER_WAIT_FAILED) {
        WifiSetupApp_SetTransition(WIFI_SETUP_BANNER_KEEP, WIFI_SETUP_BUTTON_BAR_CREATE);
        WifiSetupApp_SetStateFunc(WifiSetupTransferFailed_Init);
    } else {
        WifiSetupApp_SetTransition(WIFI_SETUP_BANNER_KEEP, WIFI_SETUP_BUTTON_BAR_CREATE);
        WifiSetupApp_SetStateFunc(WifiSetupTransferConfirm_Init);
    }
}

static void WifiSetupTransferWait_OnTransferEvent(int event) {
    WifiSetupSound_Stop();
    if (event == WIFI_SETUP_TRANSFER_EVENT_CHILD_ENTERED) {
        gWifiSetupTransferWaitResult = WIFI_SETUP_TRANSFER_WAIT_CHILD_ENTERED;
        WifiSetupSound_Play(0x10);
    } else {
        gWifiSetupTransferWaitResult = WIFI_SETUP_TRANSFER_WAIT_FAILED;
        WifiSetupSound_Play(0x12);
    }
    WifiSetupTransfer_SetCallback(NULL);
    WifiSetupApp_SetStateFunc(WifiSetupTransferWait_Exit);
}

static BOOL WifiSetupAoss_IsLidClosed(void) {
    return PAD_DetectFold() ? TRUE : FALSE;
}

void WifiSetupAoss_Init(void) {
    gWifiSetupAoss.counter = 0;
    WifiSetupAoss_LoadGraphics();
    WifiSetupBackground_LoadSlotHeader();
    WifiSetupMessage_Show(0x36, -1, 0);
    WifiSetupBanner_Show(2);
    WifiSetup_PrintMessage(0x22);
    WifiSetupBusyIcon_Create(0);
    WifiSetupApp_StartAossClient();
    WifiSetupSound_Play(0xb);
    WifiSetupApp_SetStateFunc(WifiSetupAoss_FadeIn);
}

static void WifiSetupAoss_LoadGraphics(void) {
    WifiSetup_LoadGraphics(gWifiSetupAossJbBgStep3NcgPath, GX_LoadBG2Char);
    WifiSetup_LoadGraphics(gWifiSetupAossYbBgStep3NclPath, GX_LoadBGPltt);
    WifiSetup_LoadGraphics(gWifiSetupAossXb4MultiNscPath, GX_LoadBG2Scr);
    G2S_SetBG0Priority(3);
    G2S_SetBG1Priority(3);
    G2_SetBG0Priority(3);
    G2_SetBG1Priority(3);
    G2_SetBG2Priority(3);
}

static void WifiSetupAoss_FadeIn(void) {
    WifiSetupFade_Start(WIFI_SETUP_FADE_IN_FROM_WHITE, WIFI_SETUP_SCREEN_SUB, GX_BLEND_PLANEMASK_BG0, 8);
    WifiSetupFade_Start(WIFI_SETUP_FADE_IN_FROM_WHITE, WIFI_SETUP_SCREEN_MAIN, GX_BLEND_PLANEMASK_BG0 | GX_BLEND_PLANEMASK_BG2 | GX_BLEND_PLANEMASK_OBJ, 8);
    WifiSetupDisplay_ShowPlanes(WIFI_SETUP_SCREEN_SUB, GX_PLANEMASK_BG0);
    WifiSetupDisplay_ShowPlanes(WIFI_SETUP_SCREEN_MAIN, GX_PLANEMASK_BG0 | GX_PLANEMASK_BG2 | GX_PLANEMASK_OBJ);
    WifiSetupApp_SetStateFunc(WifiSetupAoss_WaitFadeIn);
}

static void WifiSetupAoss_WaitFadeIn(void) {
    if (WifiSetupFade_IsActive(WIFI_SETUP_SCREEN_SUB)) {
        return;
    }
    if (WifiSetupFade_IsActive(WIFI_SETUP_SCREEN_MAIN)) {
        return;
    }
    WifiSetupButtonBar_Show(1);
    WifiSetupApp_SetStateFunc(WifiSetupAoss_WaitButtonBar);
}

static void WifiSetupAoss_WaitButtonBar(void) {
    if (WifiSetupButtonBar_GetSelected() == WIFI_SETUP_SELECTED_NOT_SHOWN) {
        return;
    }
    gWifiSetupAoss.task = WifiSetupTask_Create(WIFI_SETUP_TASK_QUEUE_VBLANK, WifiSetupAoss_InputTask, 0, 0x78);
    WifiSetupApp_SetStateFunc(WifiSetupAoss_Main);
}

static void WifiSetupAoss_Main(void) {
    WifiSetupAoss_HandleInput();
    WifiSetupAoss_Update();
    WifiSetupAoss_CheckButtons();
    switch (WifiSetupApp_PollAossClient()) {
    case WIFI_SETUP_CLIENT_BUSY:
        return;
    case WIFI_SETUP_CLIENT_DONE:
        if (gWifiSetupAoss.task == NULL) {
            return;
        }
        gWifiSetupAoss.done = TRUE;
        WifiSetupTask_Destroy(WIFI_SETUP_TASK_QUEUE_VBLANK, gWifiSetupAoss.task);
        gWifiSetupAoss.task = NULL;
        WifiSetupApp_SetStateFunc(WifiSetupAoss_WaitFinish);
        break;
    case WIFI_SETUP_CLIENT_FAILED:
        if (gWifiSetupAoss.task == NULL) {
            return;
        }
        WifiSetupSound_Stop();
        WifiSetupDialog_Open(0xc, 1, 1, -1, 0);
        WifiSetupSound_Play(9);
        WifiSetupButtonBar_Lock();
        WifiSetupTask_Destroy(WIFI_SETUP_TASK_QUEUE_VBLANK, gWifiSetupAoss.task);
        gWifiSetupAoss.task = NULL;
        WifiSetupApp_SetStateFunc(WifiSetupAoss_WaitErrorDialog);
        break;
    }
}

static void WifiSetupAoss_HandleInput(void) {
    if (WifiSetupInput_IsKeyPressed(PAD_BUTTON_B)) {
        WifiSetupButtonBar_SelectIfNone(0);
        return;
    }
    if (WifiSetupAoss_IsLidClosed()) {
        WifiSetupButtonBar_SelectIfNone(0);
    }
}

static void WifiSetupAoss_Update(void) {
}

static void WifiSetupAoss_CheckButtons(void) {
    if (WifiSetupButtonBar_GetSelected() != 0) {
        return;
    }
    if (gWifiSetupAoss.task == NULL) {
        return;
    }
    WifiSetupTask_DestroyLater(WIFI_SETUP_TASK_QUEUE_VBLANK, gWifiSetupAoss.task);
    gWifiSetupAoss.task = NULL;
    WifiSetupButtonBar_Lock();
    WifiSetupApp_SetStateFunc(WifiSetupAoss_Cancel);
}

static void WifiSetupAoss_Exit(void) {
    WifiSetupButtonBar_Lock();
    if (gWifiSetupAoss.task != NULL) {
        WifiSetupTask_Destroy(WIFI_SETUP_TASK_QUEUE_VBLANK, gWifiSetupAoss.task);
    }
    WifiSetupFade_StartDelay(8);
    WifiSetupApp_SetStateFunc(WifiSetupAoss_WaitFadeOut);
}

static void WifiSetupAoss_WaitFadeOut(void) {
    if (WifiSetupFade_IsActive(WIFI_SETUP_SCREEN_SUB)) {
        return;
    }
    WifiSetupButtonBar_Close();
    if (!gWifiSetupAoss.done) {
        WifiSetupFade_Start(WIFI_SETUP_FADE_OUT_TO_WHITE, WIFI_SETUP_SCREEN_SUB, GX_BLEND_PLANEMASK_BG0, 8);
    }
    WifiSetupFade_Start(WIFI_SETUP_FADE_OUT_TO_WHITE, WIFI_SETUP_SCREEN_MAIN, GX_BLEND_PLANEMASK_BG0 | GX_BLEND_PLANEMASK_BG2 | GX_BLEND_PLANEMASK_OBJ, 8);
    WifiSetupApp_SetStateFunc(WifiSetupAoss_End);
}

static void WifiSetupAoss_End(void) {
    if (WifiSetupFade_IsActive(WIFI_SETUP_SCREEN_MAIN)) {
        return;
    }
    if (!gWifiSetupAoss.done) {
        if (WifiSetupFade_IsActive(WIFI_SETUP_SCREEN_SUB)) {
            return;
        }
    }
    if (!WifiSetupButtonBar_IsNotClosing()) {
        return;
    }
    WifiSetupApp_StopAossClient(gWifiSetupAoss.done ? TRUE : FALSE);
    WifiSetupBusyIcon_Destroy();
    WifiSetupText_FreeBgCanvas(WIFI_SETUP_SCREEN_MAIN);
    if (!gWifiSetupAoss.done) {
        WifiSetupMessage_Hide();
        WifiSetupDisplay_HidePlanes(WIFI_SETUP_SCREEN_SUB, GX_PLANEMASK_BG0);
    }
    WifiSetupDisplay_HidePlanes(WIFI_SETUP_SCREEN_MAIN, GX_PLANEMASK_BG0 | GX_PLANEMASK_BG2 | GX_PLANEMASK_OBJ);
    if (!gWifiSetupAoss.done) {
        WifiSetupApp_SetTransition(WIFI_SETUP_BANNER_CHANGE, WIFI_SETUP_BUTTON_BAR_CREATE);
        WifiSetupApp_SetStateFunc(WifiSetupMethodMenu_Init);
    } else {
        WifiSetupApp_SetTransition(WIFI_SETUP_BANNER_KEEP, WIFI_SETUP_BUTTON_BAR_KEEP);
        WifiSetupApp_SetStateFunc(WifiSetupAossDone_Init);
    }
}

static void WifiSetupAoss_InputTask(WifiSetupTask *task, void *arg) {
    WifiSetupInput_Update();
    WifiSetupTask_RunQueue(WIFI_SETUP_TASK_QUEUE_MAIN);
    WifiSetupAoss_HandleInput();
    WifiSetupAoss_CheckButtons();
}

static void WifiSetupAoss_WaitErrorDialog(void) {
    if (WifiSetupDialog_GetSelected() != 0) {
        return;
    }
    WifiSetupSound_Play(6);
    WifiSetupDialog_Close();
    WifiSetupApp_SetStateFunc(WifiSetupAoss_WaitErrorDialogClosed);
}

static void WifiSetupAoss_WaitErrorDialogClosed(void) {
    if (WifiSetupDialog_IsOpen()) {
        return;
    }
    WifiSetupApp_SetStateFunc(WifiSetupAoss_Exit);
}

static void WifiSetupAoss_WaitFinish(void) {
    WifiSetupAoss_HandleInput();
    WifiSetupAoss_Update();
    WifiSetupAoss_CheckButtons();
    gWifiSetupAoss.counter++;
    if (gWifiSetupAoss.counter < 0x438) {
        return;
    }
    WifiSetupSound_Stop();
    WifiSetupApp_SetStateFunc(WifiSetupAoss_Exit);
}

static void WifiSetupAoss_Cancel(void) {
    WifiSetupSound_Stop();
    WifiSetupSound_Play(7);
    gWifiSetupAoss.done = FALSE;
    WifiSetupApp_SetStateFunc(WifiSetupAoss_Exit);
}

static void WifiSetupAossDone_Init(void) {
    gWifiSetupAossDoneTimer = 0;
    WifiSetupAossDone_LoadGraphics();
    WifiSetupBackground_LoadSlotHeader();
    WifiSetup_PrintMessage(0x23);
    WifiSetupSound_Play(0x10);
    WifiSetupApp_SetStateFunc(WifiSetupAossDone_FadeIn);
}

static void WifiSetupAossDone_LoadGraphics(void) {
    WifiSetup_LoadGraphics(gWifiSetupAossDoneXb4MultiNscPath, GX_LoadBG2Scr);
    G2S_SetBG0Priority(3);
    G2S_SetBG1Priority(3);
    G2_SetBG1Priority(3);
    G2_SetBG2Priority(3);
}

static void WifiSetupAossDone_FadeIn(void) {
    WifiSetupFade_Start(WIFI_SETUP_FADE_IN_FROM_WHITE, WIFI_SETUP_SCREEN_MAIN, GX_BLEND_PLANEMASK_BG0 | GX_BLEND_PLANEMASK_BG2 | GX_BLEND_PLANEMASK_OBJ, 8);
    WifiSetupDisplay_ShowPlanes(WIFI_SETUP_SCREEN_MAIN, GX_PLANEMASK_BG0 | GX_PLANEMASK_BG2 | GX_PLANEMASK_OBJ);
    WifiSetupApp_SetStateFunc(WifiSetupAossDone_WaitFadeIn);
}

static void WifiSetupAossDone_WaitFadeIn(void) {
    if (WifiSetupFade_IsActive(WIFI_SETUP_SCREEN_MAIN)) {
        return;
    }
    WifiSetupApp_SetStateFunc(WifiSetupAossDone_Main);
}

static void WifiSetupAossDone_Main(void) {
    WifiSetupAossDone_UpdateTimer();
    WifiSetupAossDone_Update();
}

static void WifiSetupAossDone_Update(void) {
}

static void WifiSetupAossDone_FadeOut(void) {
    WifiSetupFade_Start(WIFI_SETUP_FADE_OUT_TO_WHITE, WIFI_SETUP_SCREEN_SUB, GX_BLEND_PLANEMASK_BG0, 8);
    WifiSetupFade_Start(WIFI_SETUP_FADE_OUT_TO_WHITE, WIFI_SETUP_SCREEN_MAIN, GX_BLEND_PLANEMASK_BG0 | GX_BLEND_PLANEMASK_BG2 | GX_BLEND_PLANEMASK_OBJ, 8);
    WifiSetupApp_SetStateFunc(WifiSetupAossDone_End);
}

static void WifiSetupAossDone_End(void) {
    if (WifiSetupFade_IsActive(WIFI_SETUP_SCREEN_SUB)) {
        return;
    }
    if (WifiSetupFade_IsActive(WIFI_SETUP_SCREEN_MAIN)) {
        return;
    }
    WifiSetupText_FreeBgCanvas(WIFI_SETUP_SCREEN_MAIN);
    WifiSetupMessage_Hide();
    WifiSetupDisplay_HidePlanes(WIFI_SETUP_SCREEN_SUB, GX_PLANEMASK_BG0);
    WifiSetupDisplay_HidePlanes(WIFI_SETUP_SCREEN_MAIN, GX_PLANEMASK_BG0 | GX_PLANEMASK_BG2 | GX_PLANEMASK_OBJ);
    WifiSetupApp_SetTransition(WIFI_SETUP_BANNER_KEEP, WIFI_SETUP_BUTTON_BAR_KEEP);
    WifiSetupApp_SetScreenArgs(0, WIFI_SETUP_TEST_NEW_SETTINGS);
    WifiSetupApp_SetStateFunc(WifiSetupTestPrompt_Init);
}

static void WifiSetupAossDone_UpdateTimer(void) {
    if (++gWifiSetupAossDoneTimer < 0x78) {
        return;
    }
    WifiSetupApp_SetStateFunc(WifiSetupAossDone_FadeOut);
}

void WifiSetupListScreen_Init(void) {
    int result;
    gWifiSetupListScreen.work = WifiSetupHeap_AllocZeroed(sizeof(WifiSetupListWork), 4);
    WifiSetupApp_GetScreenArgs(&result, 0);
    if (result == 0) {
        gWifiSetupListScreen.selected = 0;
        gWifiSetupListScreen.position = 0;
    }
    gWifiSetupListScreen.work->count = WifiSetupApScan_GetEntries(&gWifiSetupListScreen.work->entries);
    WifiSetupListScreen_LoadGraphics();
    WifiSetupBackground_LoadSlotHeader();
    WifiSetupMessage_Show(0x34, -1, 0);
    WifiSetupBanner_Show(2);
    WifiSetupListScreen_CreateScrollBar();
    WifiSetupListScreen_CreateRowObjects();
    gWifiSetupListScreen.work->canvas = WifiSetupText_InitBgCanvas(WIFI_SETUP_SCREEN_MAIN, 0);
    gWifiSetupListScreen.work->scrollBgTask = WifiSetupTask_Create(WIFI_SETUP_TASK_QUEUE_VBLANK, WifiSetupListScreen_ScrollBgTask, 0, 0x6e);
    WifiSetupListScreen_DrawRows();
    WifiSetupListScreen_ShowCursor();
    WifiSetupApp_SetStateFunc(WifiSetupListScreen_FadeIn);
}

static void WifiSetupListScreen_LoadGraphics(void) {
    WifiSetupPath25 scrName;
    WifiSetupPath22 plttName;
    scrName = gWifiSetupListScreenXb4ApListBackNscPath;
    plttName = gWifiSetupListScreenYbBgStep31NclPath;
    WifiSetup_LoadGraphics(gWifiSetupListScreenJb4ApListNscPath, GX_LoadBG3Scr);
    gWifiSetupListScreen.work->bgScreenFile = WifiSetupFile_Load(WifiSetup_LocalizePath(scrName.text), 0, 4);
    WifiSetupBgScreen_Create(gWifiSetupListScreen.work->bgScreenFile);
    WifiSetupBgScreen_MarkDirty();
    gWifiSetupListScreen.work->paletteFile = WifiSetupFile_Load(WifiSetup_LocalizePath(plttName.text), 0, 4);
    G2S_SetBG0Priority(3);
    G2S_SetBG1Priority(3);
    G2_SetBG0Priority(3);
    G2_SetBG1Priority(2);
    G2_SetBG2Priority(3);
    G2_SetBG3Priority(2);
}

static void WifiSetupListScreen_CreateScrollBar(void) {
    int mode;
    int val;
    WifiSetupListWork *big = gWifiSetupListScreen.work;
    big->total = (big->count - 4) * 0x1c;
    big = gWifiSetupListScreen.work;
    val = 0;
    if (big->count <= 4) {
        mode = 0;
        big->scrollBarRange = 0;
    } else if (big->count <= 8) {
        big->scrollBarRange = 0x1f;
        mode = 1;
    } else {
        big->scrollBarRange = 0x37;
        mode = 2;
    }
    if (mode != 0) {
        val = FX_DivS32(gWifiSetupListScreen.position * gWifiSetupListScreen.work->scrollBarRange, gWifiSetupListScreen.work->total);
    }
    WifiSetupScrollBar_Create(mode, 0x55, 0xec, 0x3f, val);
}

static void WifiSetupListScreen_CreateRowObjects(void) {
    int count = gWifiSetupListScreen.work->count;
    if (count > 5) {
        count = 5;
    }
    int i = 0;
    for (; i < count; i++) {
        gWifiSetupListScreen.work->rowOams[i] = WifiSetupOamTemplate_AllocOam(0, 46);
        gWifiSetupListScreen.work->iconOams[i] = WifiSetupOamTemplate_AllocOam(0, 24);
    }
    for (i = 0; (u32)i < 3; i++) {
        WifiSetupOamTemplate_Copy(0, gWifiSetupListScreenRowTemplates[i], gWifiSetupListScreen.work->rowOams[0]);
        gWifiSetupListScreen.work->rowKindChars[i] = gWifiSetupListScreen.work->rowOams[0]->attr2 & 1023;
    }
    for (i = 0; (u32)i < 4; i++) {
        WifiSetupOamTemplate_Copy(0, gWifiSetupListScreenIconTemplates[i], gWifiSetupListScreen.work->iconOams[0]);
        gWifiSetupListScreen.work->iconChars[i] = gWifiSetupListScreen.work->iconOams[0]->attr2 & 1023;
    }
    for (i = 0; i < count; i++) {
        gWifiSetupListScreen.work->rowOams[i]->attr2 = (gWifiSetupListScreen.work->rowOams[i]->attr2 & ~0xC00) | 0xC00;   // priority 3
        gWifiSetupListScreen.work->iconOams[i]->attr2 = (gWifiSetupListScreen.work->iconOams[i]->attr2 & ~0xC00) | 0xC00; // priority 3
    }
}

static void WifiSetupListScreen_FadeIn(void) {
    WifiSetupFade_Start(WIFI_SETUP_FADE_IN_FROM_WHITE, WIFI_SETUP_SCREEN_SUB, GX_BLEND_PLANEMASK_BG0, 8);
    WifiSetupFade_Start(WIFI_SETUP_FADE_IN_FROM_WHITE, WIFI_SETUP_SCREEN_MAIN, GX_BLEND_PLANEMASK_BG0 | GX_BLEND_PLANEMASK_BG2 | GX_BLEND_PLANEMASK_BG3 | GX_BLEND_PLANEMASK_OBJ, 8);
    WifiSetupDisplay_ShowPlanes(WIFI_SETUP_SCREEN_SUB, GX_PLANEMASK_BG0);
    WifiSetupDisplay_ShowPlanes(WIFI_SETUP_SCREEN_MAIN, GX_PLANEMASK_BG0 | GX_PLANEMASK_BG2 | GX_PLANEMASK_BG3 | GX_PLANEMASK_OBJ);
    WifiSetupApp_SetStateFunc(WifiSetupListScreen_WaitFadeIn);
}

static void WifiSetupListScreen_WaitFadeIn(void) {
    if (WifiSetupFade_IsActive(WIFI_SETUP_SCREEN_SUB)) {
        return;
    }
    if (WifiSetupFade_IsActive(WIFI_SETUP_SCREEN_MAIN)) {
        return;
    }
    WifiSetupButtonBar_Show(0);
    WifiSetupApp_SetStateFunc(WifiSetupListScreen_WaitButtonBar);
}

static void WifiSetupListScreen_WaitButtonBar(void) {
    if (WifiSetupButtonBar_GetSelected() == WIFI_SETUP_SELECTED_NOT_SHOWN) {
        return;
    }
    WifiSetupButtonBar_Unlock();
    WifiSetupApp_SetStateFunc(WifiSetupListScreen_Main);
}

static void WifiSetupListScreen_Main(void) {
    WifiSetupListScreen_HandleInput();
    WifiSetupListScreen_HandleScrollBar();
    WifiSetupListScreen_CheckButtons();
}

static void WifiSetupListScreen_HandleInput(void) {
    int i;
    WifiSetupRect *box;
    if (gWifiSetupListScreen.work->task || gWifiSetupListScreen.work->draggingScrollBar) {
        return;
    }
    if (WifiSetupInput_IsTouchPressed(&gWifiSetupInputPanelRect)) {
        gWifiSetupListScreen.work->selected = -1;
        for (i = 0, box = gWifiSetupListScreenTouchRects; (u32)i < 5; i++, box++) {
            if (WifiSetupInput_IsTouchPressed(box)) {
                if (i < 4) {
                    gWifiSetupListScreen.work->selected = i;
                    break;
                }
                WifiSetupButtonBar_SelectIfNone(1);
                gWifiSetupListScreen.selected = i;
                WifiSetupListScreen_ShowCursor();
                return;
            }
        }
    }
    if (WifiSetupInput_IsTouchReleased(&gWifiSetupInputPanelRect)) {
        WifiSetupRect *pos;
        int j;
        for (j = 0, pos = gWifiSetupListScreenTouchRects; j < 4; j++, pos++) {
            if (WifiSetupInput_IsTouchReleased(pos)) {
                if (gWifiSetupListScreen.work->selected != j) {
                    break;
                }
                if (j >= gWifiSetupListScreen.work->count) {
                    WifiSetupSound_Play(9);
                    break;
                }
                WifiSetupButtonBar_SelectIfNone(1);
                gWifiSetupListScreen.selected = j;
                WifiSetupListScreen_ShowCursor();
                return;
            }
        }
    }
    if (WifiSetupInput_IsKeyPressed(PAD_BUTTON_A)) {
        WifiSetupButtonBar_SelectIfNone(1);
        WifiSetupScrollBar_Disable();
        return;
    }
    if (WifiSetupInput_IsKeyPressed(PAD_BUTTON_B)) {
        WifiSetupButtonBar_SelectIfNone(0);
        return;
    }
    if (WifiSetupInput_IsKeyRepeated(PAD_BUTTON_L)) {
        WifiSetupListScreen_StartScrollDown();
        return;
    }
    if (WifiSetupInput_IsKeyReleased(PAD_BUTTON_L)) {
        gWifiSetupListScreen.work->cursorLimitSoundPlayed = 0;
        return;
    }
    if (WifiSetupInput_IsKeyRepeated(PAD_BUTTON_R)) {
        WifiSetupListScreen_StartScrollUp();
        return;
    }
    if (WifiSetupInput_IsKeyReleased(PAD_BUTTON_R)) {
        gWifiSetupListScreen.work->cursorLimitSoundPlayed = 0;
        return;
    }
    if (WifiSetupInput_IsKeyRepeated(PAD_KEY_UP)) {
        WifiSetupListScreen_MoveCursor(1);
        return;
    }
    if (WifiSetupInput_IsKeyReleased(PAD_KEY_UP)) {
        gWifiSetupListScreen.work->cursorLimitSoundPlayed = 0;
        return;
    }
    if (WifiSetupInput_IsKeyRepeated(PAD_KEY_DOWN)) {
        WifiSetupListScreen_MoveCursor(3);
        return;
    }
    if (WifiSetupInput_IsKeyReleased(PAD_KEY_DOWN)) {
        gWifiSetupListScreen.work->cursorLimitSoundPlayed = 0;
    }
}

static void WifiSetupListScreen_HandleScrollBar(void) {
    if (gWifiSetupListScreen.work->task) {
        return;
    }
    if (gWifiSetupListScreen.work->delay) {
        gWifiSetupListScreen.work->delay--;
    }
    switch (WifiSetupScrollBar_GetEvent()) {
    case WIFI_SETUP_SCROLL_BAR_EVENT_NONE:
        break;
    case WIFI_SETUP_SCROLL_BAR_EVENT_GRABBED:
        gWifiSetupListScreen.work->draggingScrollBar = 1;
        WifiSetupButtonBar_Lock();
        break;
    case WIFI_SETUP_SCROLL_BAR_EVENT_DRAGGED:
        if (gWifiSetupListScreen.work->delay) {
            break;
        }
        WifiSetupCursor_Hide();
        gWifiSetupListScreen.position = FX_DivS32(gWifiSetupListScreen.work->total * WifiSetupScrollBar_GetValue(), gWifiSetupListScreen.work->scrollBarRange);
        WifiSetupListScreen_DrawRows();
        gWifiSetupListScreen.work->delay = 4;
        break;
    case WIFI_SETUP_SCROLL_BAR_EVENT_RELEASED: {
        int mod;
        gWifiSetupListScreen.work->draggingScrollBar = 0;
        WifiSetupButtonBar_Unlock();
        gWifiSetupListScreen.position = FX_DivS32(gWifiSetupListScreen.work->total * WifiSetupScrollBar_GetValue(), gWifiSetupListScreen.work->scrollBarRange);
        WifiSetupSound_Play(19);
        WifiSetupListScreen_DrawRows();
        mod = FX_ModS32(gWifiSetupListScreen.position, 28);
        if (mod == 0) {
            WifiSetupListScreen_ShowCursor();
        } else if (mod < 14) {
            gWifiSetupListScreen.work->task = WifiSetupTask_Create(WIFI_SETUP_TASK_QUEUE_MAIN, WifiSetupListScreen_ScrollUpTask, 0, 120);
        } else {
            gWifiSetupListScreen.work->task = WifiSetupTask_Create(WIFI_SETUP_TASK_QUEUE_MAIN, WifiSetupListScreen_ScrollDownTask, 0, 120);
        }
        break;
    }
    case 4:
        if (gWifiSetupListScreen.position == 0) {
            if (gWifiSetupListScreen.work->scrollLimitSoundPlayed == 0) {
                WifiSetupSound_Play(9);
                gWifiSetupListScreen.work->scrollLimitSoundPlayed = 1;
            }
        } else {
            WifiSetupSound_Play(19);
            gWifiSetupListScreen.work->task = WifiSetupTask_Create(WIFI_SETUP_TASK_QUEUE_MAIN, WifiSetupListScreen_ScrollUpTask, 0, 120);
        }
        break;
    case 6:
        if (gWifiSetupListScreen.work->count <= 4 || gWifiSetupListScreen.position == gWifiSetupListScreen.work->total) {
            if (gWifiSetupListScreen.work->scrollLimitSoundPlayed == 0) {
                WifiSetupSound_Play(9);
                gWifiSetupListScreen.work->scrollLimitSoundPlayed = 1;
            }
        } else {
            WifiSetupSound_Play(19);
            gWifiSetupListScreen.work->task = WifiSetupTask_Create(WIFI_SETUP_TASK_QUEUE_MAIN, WifiSetupListScreen_ScrollDownTask, 0, 120);
        }
        break;
    case 5:
    case 7:
        gWifiSetupListScreen.work->scrollLimitSoundPlayed = 0;
        break;
    }
}

static void WifiSetupListScreen_CheckButtons(void) {
    int result, index;
    WifiSetupListWork *work;
    if (gWifiSetupListScreen.work->task || gWifiSetupListScreen.work->draggingScrollBar) {
        return;
    }
    result = WifiSetupButtonBar_GetSelected();
    switch (result) {
    case 0:
        WifiSetupSound_Play(7);
        break;
    case 1:
        if (gWifiSetupListScreen.selected == 4) {
            gWifiSetupListScreen.work->confirmed = 1;
            WifiSetupSound_Play(6);
            WifiSetupListScreen_HighlightRescanButton();
        } else {
            index = FX_DivS32(gWifiSetupListScreen.position, 28) + gWifiSetupListScreen.selected;
            work = gWifiSetupListScreen.work;
            if (work->entries[index].security == WIFI_SETUP_SECURITY_WPA) {
                WifiSetupSound_Play(9);
                WifiSetupScrollBar_Disable();
                WifiSetupButtonBar_Lock();
                WifiSetupDialog_Open(14, 1, 1, -1, 0);
                WifiSetupApp_SetStateFunc(WifiSetupListScreen_WaitErrorDialog);
                return;
            }
            work->confirmed = 1;
            gWifiSetupListScreen.work->index = index;
            WifiSetupSound_Play(6);
        }
        break;
    default:
        return;
    }
    WifiSetupApp_SetStateFunc(WifiSetupListScreen_Exit);
}

static void WifiSetupListScreen_Exit(void) {
    WifiSetupButtonBar_Lock();
    WifiSetupFade_StartDelay(8);
    WifiSetupApp_SetStateFunc(WifiSetupListScreen_WaitFadeOut);
}

static void WifiSetupListScreen_WaitFadeOut(void) {
    if (WifiSetupFade_IsActive(WIFI_SETUP_SCREEN_SUB)) {
        return;
    }
    if (gWifiSetupListScreen.work->confirmed) {
        WifiSetupButtonBar_Close();
    } else {
        WifiSetupButtonBar_Lock();
    }
    WifiSetupFade_Start(WIFI_SETUP_FADE_OUT_TO_WHITE, WIFI_SETUP_SCREEN_SUB, GX_BLEND_PLANEMASK_BG0, 8);
    WifiSetupFade_Start(WIFI_SETUP_FADE_OUT_TO_WHITE, WIFI_SETUP_SCREEN_MAIN, GX_BLEND_PLANEMASK_BG0 | GX_BLEND_PLANEMASK_BG2 | GX_BLEND_PLANEMASK_BG3 | GX_BLEND_PLANEMASK_OBJ, 8);
    WifiSetupApp_SetStateFunc(WifiSetupListScreen_End);
}

static void WifiSetupListScreen_End(void) {
    int i;
    if (WifiSetupFade_IsActive(WIFI_SETUP_SCREEN_SUB)) {
        return;
    }
    if (WifiSetupFade_IsActive(WIFI_SETUP_SCREEN_MAIN)) {
        return;
    }
    if (!WifiSetupButtonBar_IsNotClosing()) {
        return;
    }
    WifiSetupTask_Destroy(WIFI_SETUP_TASK_QUEUE_VBLANK, gWifiSetupListScreen.work->scrollBgTask);
    for (i = 0; i < 5; i++) {
        if (gWifiSetupListScreen.work->rowOams[i]) {
            WifiSetupOam_Release(gWifiSetupListScreen.work->rowOams[i]);
        }
        if (gWifiSetupListScreen.work->iconOams[i]) {
            WifiSetupOam_Release(gWifiSetupListScreen.work->iconOams[i]);
        }
    }
    WifiSetupText_FreeCanvas(gWifiSetupListScreen.work->canvas);
    WifiSetupScrollBar_Destroy();
    WifiSetupCursor_Hide();
    WifiSetupMessage_Hide();
    WifiSetupBgScreen_Destroy();
    WifiSetupFile_Free(gWifiSetupListScreen.work->bgScreenFile);
    WifiSetupFile_Free(gWifiSetupListScreen.work->paletteFile);
    WifiSetupDisplay_HidePlanes(WIFI_SETUP_SCREEN_SUB, GX_PLANEMASK_BG0);
    WifiSetupDisplay_HidePlanes(WIFI_SETUP_SCREEN_MAIN, GX_PLANEMASK_BG0 | GX_PLANEMASK_BG2 | GX_PLANEMASK_BG3 | GX_PLANEMASK_OBJ);
    G2_SetBG0Offset(0, 0);
    G2_SetBG2Offset(0, 0);
    if (!gWifiSetupListScreen.work->confirmed) {
        WifiSetupApScan_FreeWork();
        WifiSetupConnections_Edit(WifiSetupConnections_GetEdit()->index);
        WifiSetupApp_SetTransition(WIFI_SETUP_BANNER_CHANGE, WIFI_SETUP_BUTTON_BAR_KEEP);
        WifiSetupApp_SetStateFunc(WifiSetupMethodMenu_Init);
    } else if (gWifiSetupListScreen.selected == 4) {
        WifiSetupApScan_FreeWork();
        WifiSetupApp_SetTransition(WIFI_SETUP_BANNER_KEEP, WIFI_SETUP_BUTTON_BAR_CREATE);
        WifiSetupApp_SetStateFunc(WifiSetupApScanScreen_Init);
    } else {
        WifiSetupConnections_SetSsid(gWifiSetupListScreen.work->entries[gWifiSetupListScreen.work->index].ssid);
        WifiSetupApp_SetTransition(WIFI_SETUP_BANNER_KEEP, WIFI_SETUP_BUTTON_BAR_KEEP);
        if (gWifiSetupListScreen.work->entries[gWifiSetupListScreen.work->index].security) {
            WifiSetupApp_SetTransition(WIFI_SETUP_BANNER_KEEP, WIFI_SETUP_BUTTON_BAR_CREATE);
            WifiSetupApp_SetScreenArgs(1, 1);
            WifiSetupApp_SetStateFunc(WifiSetupTextEntry_Init);
        } else {
            WifiSetupApp_SetTransition(WIFI_SETUP_BANNER_KEEP, WIFI_SETUP_BUTTON_BAR_CREATE);
            WifiSetupApp_SetScreenArgs(0, WIFI_SETUP_TEST_NEW_SETTINGS);
            WifiSetupApp_SetStateFunc(WifiSetupTestPrompt_Init);
        }
    }
    WifiSetupHeap_FreeAndClear(&ov13_0224F53C);
}

static void WifiSetupListScreen_DrawRows(void) {
    int start = FX_DivS32(gWifiSetupListScreen.position, 28), count = gWifiSetupListScreen.work->count, row, i, second;
    WifiSetupText_Clear(gWifiSetupListScreen.work->canvas, 0);
    if (count > 5) {
        count = 5;
    }
    row = start;
    for (i = 0; i < count; i++) {
        WifiSetupListScreen_DrawRowText(row, i);
        row++;
    }
    second = start;
    for (row = 0; row < count; row++) {
        WifiSetupListScreen_SetRowIcons(second, row);
        second++;
    }
    WifiSetupText_MarkDirty(gWifiSetupListScreen.work->canvas);
    WifiSetupListScreen_PositionRows();
}

static void WifiSetupListScreen_DrawRowText(int index, int row) {
    int length = WifiSetup_StrNLen(gWifiSetupListScreen.work->entries[index].ssid, 32), y = row * 28, i, n;
    u16 text[17];
    if (index >= gWifiSetupListScreen.work->count) {
        return;
    }
    if (length <= 16) {
        y += 6;
    }
    MI_CpuFill8(text, 0, 34);
    n = length <= 16 ? length : 16;
    for (i = 0; i < n; i++) {
        text[i] = gWifiSetupListScreen.work->entries[index].ssid[i];
    }
    WifiSetupText_DrawMonospace(gWifiSetupListScreen.work->canvas, 10, y, 2, 10, text, 1);
    if (length <= 16) {
        return;
    }
    MI_CpuFill8(text, 0, 34);
    n = length - 16;
    for (i = 0; i < n; i++) {
        text[i] = gWifiSetupListScreen.work->entries[index].ssid[i + 16];
    }
    WifiSetupText_DrawMonospace(gWifiSetupListScreen.work->canvas, 10, y + 12, 2, 10, text, 1);
}

static void WifiSetupListScreen_SetRowIcons(int entry, int row) {
    GXOamAttr *oam;
    if (entry >= gWifiSetupListScreen.work->count) {
        return;
    }
    oam = gWifiSetupListScreen.work->rowOams[row];
    oam->attr2 = (oam->attr2 & ~0x3ff) | gWifiSetupListScreen.work->rowKindChars[gWifiSetupListScreen.work->entries[entry].security];
    oam = gWifiSetupListScreen.work->iconOams[row];
    oam->attr2 = (oam->attr2 & ~0x3ff) | gWifiSetupListScreen.work->iconChars[gWifiSetupListScreen.work->entries[entry].linkLevel];
}

static void WifiSetupListScreen_PositionRows(void) {
    int y = 54 - FX_ModS32(gWifiSetupListScreen.position, 28), count = gWifiSetupListScreen.work->count, i;
    if (count > 5) {
        count = 5;
    }
    for (i = 0; i < count; i++, y += 28) {
        GXOamAttr *oam = gWifiSetupListScreen.work->rowOams[i];
        oam->attr01 = (oam->attr01 & 0xfe00ff00) | ((y - 2) & 255) | 0xb30000;
        oam = gWifiSetupListScreen.work->iconOams[i];
        oam->attr01 = (oam->attr01 & 0xfe00ff00) | ((y + 1) & 255) | 0xd20000;
    }
    gWifiSetupListScreen.work->bgScrollDirty = 1;
}

static void WifiSetupListScreen_ScrollUpTask(WifiSetupTask *task, void *arg) {
    int rem;
    WifiSetupScrollBar_Disable();
    WifiSetupCursor_Hide();
    if (gWifiSetupListScreen.position > 4) {
        gWifiSetupListScreen.position -= 4;
    } else {
        gWifiSetupListScreen.position = 0;
    }
    rem = FX_ModS32(gWifiSetupListScreen.position, 28);
    if (rem == 24) {
        WifiSetupListScreen_DrawRows();
        return;
    }
    if (rem > 24) {
        gWifiSetupListScreen.position += 28 - rem;
        rem = 0;
    }
    WifiSetupListScreen_PositionRows();
    if (rem) {
        return;
    }
    WifiSetupScrollBar_SetValue(FX_DivS32(gWifiSetupListScreen.position * gWifiSetupListScreen.work->scrollBarRange, gWifiSetupListScreen.work->total));
    WifiSetupScrollBar_Enable();
    WifiSetupListScreen_ShowCursor();
    gWifiSetupListScreen.work->task = NULL;
    WifiSetupTask_DestroyLater(WIFI_SETUP_TASK_QUEUE_MAIN, task);
}

static void WifiSetupListScreen_ScrollDownTask(WifiSetupTask *task, void *arg) {
    int rem;
    WifiSetupScrollBar_Disable();
    WifiSetupCursor_Hide();
    gWifiSetupListScreen.position += 4;
    rem = FX_ModS32(gWifiSetupListScreen.position, 28);
    if (rem >= 4) {
        WifiSetupListScreen_PositionRows();
        return;
    }
    gWifiSetupListScreen.position -= rem;
    WifiSetupListScreen_DrawRows();
    WifiSetupScrollBar_SetValue(FX_DivS32(gWifiSetupListScreen.position * gWifiSetupListScreen.work->scrollBarRange, gWifiSetupListScreen.work->total));
    WifiSetupScrollBar_Enable();
    WifiSetupListScreen_ShowCursor();
    gWifiSetupListScreen.work->task = NULL;
    WifiSetupTask_DestroyLater(WIFI_SETUP_TASK_QUEUE_MAIN, task);
}

static void WifiSetupListScreen_ScrollBgTask(WifiSetupTask *task, void *arg) {
    int x;
    if (!gWifiSetupListScreen.work->bgScrollDirty) {
        return;
    }
    x = FX_ModS32(gWifiSetupListScreen.position, 28) - 50;
    G2_SetBG0Offset(0, x);
    G2_SetBG2Offset(0, x);
    gWifiSetupListScreen.work->bgScrollDirty = 0;
}

static void WifiSetupListScreen_ShowCursor(void) {
    unsigned x = gWifiSetupListScreen.selected;
    WifiSetupCursor_ShowPair(x < 4 ? 2 : 3, gWifiSetupListScreenCursorLeft[x * 4], gWifiSetupListScreenCursorRight[x * 4], gWifiSetupListScreenCursorTop[x * 4]);
}

static void WifiSetupListScreen_MoveCursor(int input) {
    int changed = 1;
    int state = gWifiSetupListScreen.selected;
    switch (state) {
    case 0:
        if (input == 1) {
            if (gWifiSetupListScreen.position == 0) {
                gWifiSetupListScreen.selected = 4;
            } else {
                WifiSetupSound_Play(19);
                gWifiSetupListScreen.work->task = WifiSetupTask_Create(WIFI_SETUP_TASK_QUEUE_MAIN, WifiSetupListScreen_ScrollUpTask, 0, 120);
                return;
            }
        } else {
            if (gWifiSetupListScreen.work->count > 1) {
                gWifiSetupListScreen.selected = state + 1;
            } else {
                changed = 0;
            }
        }
        break;
    case 1:
    case 2:
        if (input == 1) {
            gWifiSetupListScreen.selected = state - 1;
        } else {
            if (gWifiSetupListScreen.work->count > state + 1) {
                gWifiSetupListScreen.selected = state + 1;
            } else {
                changed = 0;
            }
        }
        break;
    case 3:
        if (input == 1) {
            gWifiSetupListScreen.selected = state - 1;
        } else {
            WifiSetupListScreen_StartScrollDown();
            return;
        }
        break;
    case 4:
        if (input == 1) {
            changed = 0;
        } else {
            gWifiSetupListScreen.position = 0;
            gWifiSetupListScreen.selected = 0;
            WifiSetupListScreen_DrawRows();
            WifiSetupScrollBar_SetValue(0);
        }
        break;
    }
    if (!changed) {
        if (gWifiSetupListScreen.work->cursorLimitSoundPlayed) {
            return;
        }
        WifiSetupSound_Play(9);
        gWifiSetupListScreen.work->cursorLimitSoundPlayed = 1;
        return;
    }
    WifiSetupSound_Play(8);
    WifiSetupListScreen_ShowCursor();
}

static void WifiSetupListScreen_StartScrollUp(void) {
    if (!gWifiSetupListScreen.position) {
        if (gWifiSetupListScreen.work->cursorLimitSoundPlayed) {
            return;
        }
        WifiSetupSound_Play(9);
        gWifiSetupListScreen.work->cursorLimitSoundPlayed = 1;
        return;
    }
    WifiSetupSound_Play(19);
    gWifiSetupListScreen.work->task = WifiSetupTask_Create(WIFI_SETUP_TASK_QUEUE_MAIN, WifiSetupListScreen_ScrollUpTask, 0, 120);
}

static void WifiSetupListScreen_StartScrollDown(void) {
    if (gWifiSetupListScreen.position == gWifiSetupListScreen.work->total || gWifiSetupListScreen.work->count <= 4) {
        if (gWifiSetupListScreen.work->cursorLimitSoundPlayed) {
            return;
        }
        WifiSetupSound_Play(9);
        gWifiSetupListScreen.work->cursorLimitSoundPlayed = 1;
        return;
    }
    WifiSetupSound_Play(19);
    gWifiSetupListScreen.work->task = WifiSetupTask_Create(WIFI_SETUP_TASK_QUEUE_MAIN, WifiSetupListScreen_ScrollDownTask, 0, 120);
}

static void WifiSetupListScreen_HighlightRescanButton(void) {
    WifiSetupPaletteRow palette = gWifiSetupListScreenRescanPaletteRow;
    WifiSetupPalette_LoadRow(gWifiSetupListScreen.work->paletteFile, palette.row, palette.row);
}

static void WifiSetupListScreen_WaitErrorDialog(void) {
    if (WifiSetupDialog_GetSelected()) {
        return;
    }
    WifiSetupSound_Play(6);
    WifiSetupDialog_Close();
    WifiSetupApp_SetStateFunc(WifiSetupListScreen_WaitErrorDialogClosed);
}

static void WifiSetupListScreen_WaitErrorDialogClosed(void) {
    if (WifiSetupDialog_IsOpen()) {
        return;
    }
    WifiSetupButtonBar_Unlock();
    WifiSetupScrollBar_Enable();
    WifiSetupApp_SetStateFunc(WifiSetupListScreen_Main);
}

void WifiSetupTextEntry_Init(void) {
    WifiSetupBytePair messages = gWifiSetupTextEntryParams.messages;
    int field, fromList;
    gWifiSetupTextEntry = WifiSetupHeap_AllocZeroed(sizeof(WifiSetupTextEntry), 4);
    WifiSetupApp_GetScreenArgs(&field, &fromList);
    if (field == 0) {
        WifiSetupConnections_GetSsid(gWifiSetupTextEntry->text);
        gWifiSetupTextEntry->length = WifiSetup_StrNLen(gWifiSetupTextEntry->text, 32);
    }
    WifiSetupTextEntry_LoadGraphics();
    WifiSetupBackground_LoadHeader(field + 9);
    if (fromList == 1) {
        WifiSetupMessage_Show(53, -1, 0);
    } else {
        WifiSetupMessage_Show(messages.values[field], -1, 0);
    }
    WifiSetupBanner_Show(2);
    gWifiSetupTextEntry->canvas = WifiSetupText_InitBgCanvas(WIFI_SETUP_SCREEN_MAIN, 0);
    gWifiSetupTextEntry->cursor = WifiSetupOamTemplate_AllocOam(0, 62);
    {
        GXOamAttr *cursor = gWifiSetupTextEntry->cursor;
        cursor->attr2 = (cursor->attr2 & ~0xc00) | 0xc00;
    }
    WifiSetupTextEntry_UpdateCursor();
    WifiSetupTextEntry_DrawText();
    WifiSetupApp_SetStateFunc(WifiSetupTextEntry_FadeIn);
}

static void WifiSetupTextEntry_LoadGraphics(void) {
    WifiSetup_LoadGraphics(gWifiSetupTextEntryYbObjKbNclPath, GX_LoadOBJPltt);
    WifiSetup_LoadGraphics(gWifiSetupTextEntryJbBgStep3NcgPath, GX_LoadBG2Char);
    WifiSetup_LoadGraphics(gWifiSetupTextEntryYbBgStep3NclPath, GX_LoadBGPltt);
    WifiSetup_LoadGraphics(gWifiSetupTextEntryXb4EditNscPath, GX_LoadBG2Scr);
    G2S_SetBG0Priority(3);
    G2S_SetBG1Priority(3);
    G2_SetBG0Priority(2);
    G2_SetBG1Priority(3);
    G2_SetBG2Priority(3);
}

static void WifiSetupTextEntry_FadeIn(void) {
    WifiSetupFade_Start(WIFI_SETUP_FADE_IN_FROM_WHITE, WIFI_SETUP_SCREEN_SUB, GX_BLEND_PLANEMASK_BG0, 8);
    WifiSetupFade_Start(WIFI_SETUP_FADE_IN_FROM_WHITE, WIFI_SETUP_SCREEN_MAIN, GX_BLEND_PLANEMASK_BG0 | GX_BLEND_PLANEMASK_BG2 | GX_BLEND_PLANEMASK_OBJ, 8);
    WifiSetupDisplay_ShowPlanes(WIFI_SETUP_SCREEN_SUB, GX_PLANEMASK_BG0);
    WifiSetupDisplay_ShowPlanes(WIFI_SETUP_SCREEN_MAIN, GX_PLANEMASK_BG0 | GX_PLANEMASK_BG2 | GX_PLANEMASK_OBJ);
    WifiSetupApp_SetStateFunc(WifiSetupTextEntry_WaitFadeIn);
}

static void WifiSetupTextEntry_WaitFadeIn(void) {
    if (WifiSetupFade_IsActive(WIFI_SETUP_SCREEN_SUB)) {
        return;
    }
    if (WifiSetupFade_IsActive(WIFI_SETUP_SCREEN_MAIN)) {
        return;
    }
    WifiSetupKeyboard_Create();
    WifiSetupSound_Play(20);
    if (gWifiSetupTextEntry->length == 0) {
        WifiSetupKeyboard_SetCanDelete(FALSE);
    }
    if (gWifiSetupTextEntry->length == WIFI_SETUP_TEXT_ENTRY_MAX_LENGTH) {
        WifiSetupKeyboard_SetCanType(FALSE);
    }
    WifiSetupApp_SetStateFunc(WifiSetupTextEntry_WaitKeyboard);
}

static void WifiSetupTextEntry_WaitKeyboard(void) {
    if (WifiSetupKeyboard_GetInput() == WIFI_SETUP_KEYBOARD_INPUT_BUSY) {
        return;
    }
    WifiSetupApp_SetStateFunc(WifiSetupTextEntry_Main);
}

static void WifiSetupTextEntry_Main(void) {
    WifiSetupTextEntry_HandleInput();
    WifiSetupTextEntry_Update();
}

static void WifiSetupTextEntry_HandleInput(void) {
    int input = WifiSetupKeyboard_GetInput();
    switch (input) {
    case WIFI_SETUP_KEYBOARD_INPUT_NONE:
        break;
    case WIFI_SETUP_KEYBOARD_INPUT_DELETE:
        if (gWifiSetupTextEntry->length == 0) {
            break;
        }
        WifiSetupSound_Play(3);
        gWifiSetupTextEntry->length--;
        gWifiSetupTextEntry->text[gWifiSetupTextEntry->length] = 0;
        if (gWifiSetupTextEntry->length == 0) {
            WifiSetupKeyboard_SetCanDelete(FALSE);
        }
        WifiSetupKeyboard_SetCanType(TRUE);
        break;
    case WIFI_SETUP_KEYBOARD_INPUT_BACK:
        WifiSetupSound_Play(7);
        gWifiSetupTextEntry->result = WIFI_SETUP_TEXT_ENTRY_CANCELLED;
        WifiSetupApp_SetStateFunc(WifiSetupTextEntry_Exit);
        return;
    case WIFI_SETUP_KEYBOARD_INPUT_OK:
        if (WifiSetupTextEntry_IsTextValid()) {
            WifiSetupSound_Play(6);
            gWifiSetupTextEntry->result = WIFI_SETUP_TEXT_ENTRY_ACCEPTED;
        } else {
            gWifiSetupTextEntry->result = WIFI_SETUP_TEXT_ENTRY_INVALID;
            WifiSetupSound_Play(9);
        }
        gWifiSetupTextEntry->cursor->attr01 = (gWifiSetupTextEntry->cursor->attr01 & 0xc1fffcff) | 0x200;
        WifiSetupApp_SetStateFunc(WifiSetupTextEntry_Exit);
        return;
    case WIFI_SETUP_CHAR_SPACE_MARK:
    default:
        if (gWifiSetupTextEntry->length == WIFI_SETUP_TEXT_ENTRY_MAX_LENGTH) {
            break;
        }
        WifiSetupSound_Play(1);
        gWifiSetupTextEntry->text[gWifiSetupTextEntry->length] = input;
        gWifiSetupTextEntry->length++;
        WifiSetupKeyboard_SetCanDelete(TRUE);
        if (gWifiSetupTextEntry->length == WIFI_SETUP_TEXT_ENTRY_MAX_LENGTH) {
            WifiSetupKeyboard_SetCanType(FALSE);
        }
        break;
    }
    WifiSetupTextEntry_DrawText();
    WifiSetupTextEntry_UpdateCursor();
}

static void WifiSetupTextEntry_Update(void) {
}

static void WifiSetupTextEntry_Exit(void) {
    WifiSetupFade_StartDelay(8);
    WifiSetupApp_SetStateFunc(WifiSetupTextEntry_CloseKeyboard);
}

static void WifiSetupTextEntry_CloseKeyboard(void) {
    if (WifiSetupFade_IsActive(WIFI_SETUP_SCREEN_SUB)) {
        return;
    }
    WifiSetupKeyboard_Close();
    WifiSetupSound_Play(21);
    WifiSetupApp_SetStateFunc(WifiSetupTextEntry_WaitKeyboardClosed);
}

static void WifiSetupTextEntry_WaitKeyboardClosed(void) {
    u32 messages[2];
    int fromList;
    messages[0] = gWifiSetupTextEntryParams.confirmMessages[0];
    messages[1] = gWifiSetupTextEntryParams.confirmMessages[1];
    if (WifiSetupKeyboard_Exists()) {
        return;
    }
    if (gWifiSetupTextEntry->result == WIFI_SETUP_TEXT_ENTRY_CANCELLED) {
        WifiSetupApp_SetStateFunc(WifiSetupTextEntry_End);
        return;
    }
    if (gWifiSetupTextEntry->result == WIFI_SETUP_TEXT_ENTRY_INVALID) {
        WifiSetupDialog_Open(6, 3, 1, -1, 0);
        WifiSetupApp_SetStateFunc(WifiSetupTextEntry_WaitErrorDialog);
        return;
    }
    WifiSetupApp_GetScreenArgs(0, &fromList);
    WifiSetupDialog_Open(messages[fromList], 2, 1, -1, 0);
    WifiSetupApp_SetStateFunc(WifiSetupTextEntry_WaitConfirmDialog);
}

static void WifiSetupTextEntry_End(void) {
    int field, fromList;
    WifiSetupMessage_Hide();
    WifiSetupOam_Release(gWifiSetupTextEntry->cursor);
    WifiSetupText_FreeBgCanvas(WIFI_SETUP_SCREEN_MAIN);
    WifiSetup_LoadGraphics(gWifiSetupTextEntryYbObjMainNclPath, GX_LoadOBJPltt);
    WifiSetupDisplay_HidePlanes(WIFI_SETUP_SCREEN_SUB, GX_PLANEMASK_BG0);
    WifiSetupDisplay_HidePlanes(WIFI_SETUP_SCREEN_MAIN, GX_PLANEMASK_BG0 | GX_PLANEMASK_BG2 | GX_PLANEMASK_OBJ);
    WifiSetupApp_GetScreenArgs(&field, &fromList);
    if (fromList == 0) {
        WifiSetupApp_SetTransition(WIFI_SETUP_BANNER_CHANGE, WIFI_SETUP_BUTTON_BAR_CREATE);
        WifiSetupApp_SetScreenArgs(0, field);
        WifiSetupApp_SetStateFunc(WifiSetupSettings_Init);
    } else if (gWifiSetupTextEntry->result == WIFI_SETUP_TEXT_ENTRY_CANCELLED) {
        WifiSetupApp_SetTransition(WIFI_SETUP_BANNER_KEEP, WIFI_SETUP_BUTTON_BAR_CREATE);
        WifiSetupApp_SetScreenArgs(1, 0);
        WifiSetupApp_SetStateFunc(WifiSetupListScreen_Init);
    } else {
        WifiSetupApp_SetTransition(WIFI_SETUP_BANNER_KEEP, WIFI_SETUP_BUTTON_BAR_KEEP);
        WifiSetupApp_SetScreenArgs(0, WIFI_SETUP_TEST_NEW_SETTINGS);
        WifiSetupApp_SetStateFunc(WifiSetupTestPrompt_Init);
    }
    WifiSetupHeap_FreeAndClear(ov13_0224F53C + 4);
}

static void WifiSetupTextEntry_DrawText(void) {
    WifiSetupTextBox rect = { 0 };
    u16 tile[2];
    int j, i;
    rect.y = 32;
    rect.width = 14;
    rect.height = 16;
    WifiSetupText_Clear(gWifiSetupTextEntry->canvas, 0);
    tile[1] = 0;
    i = 0;
    j = 0;
    for (; i < WIFI_SETUP_TEXT_ENTRY_MAX_LENGTH; i++, j++) {
        u8 ch;
        if (i == 16) {
            j = 0;
            rect.y = 49;
        }
        ch = gWifiSetupTextEntry->text[i];
        if (ch == ' ') {
            tile[0] = WIFI_SETUP_CHAR_SPACE_MARK;
        } else {
            tile[0] = ch;
        }
        rect.x = gWifiSetupTextEntryColumnX[j];
        WifiSetupText_DrawInRect(gWifiSetupTextEntry->canvas, rect.x, rect.y, rect.width, rect.height, 2, 0x480, tile);
    }
    WifiSetupText_MarkDirty(gWifiSetupTextEntry->canvas);
}

static void WifiSetupTextEntry_UpdateCursor(void) {
    unsigned x = gWifiSetupTextEntry->length;
    GXOamAttr *cursor = gWifiSetupTextEntry->cursor;
    int col = x & 15, row = (int)x >> 4;
    if (x >= 32) {
        row = 1;
        col = 15;
    }
    cursor->attr01 = (cursor->attr01 & 0xfe00ff00) | gWifiSetupTextEntryCursorRowY[row] | ((u32)gWifiSetupTextEntryColumnX[col] << 23 >> 7);
}

static void WifiSetupTextEntry_WaitConfirmDialog(void) {
    gWifiSetupTextEntry->result = WifiSetupDialog_GetSelected();
    switch (gWifiSetupTextEntry->result) {
    case 0:
        WifiSetupSound_Play(7);
        break;
    case 1:
        WifiSetupSound_Play(14);
        break;
    default:
        return;
    }
    WifiSetupDialog_Close();
    WifiSetupApp_SetStateFunc(WifiSetupTextEntry_WaitConfirmDialogClosed);
}

static void WifiSetupTextEntry_WaitConfirmDialogClosed(void) {
    void (*storeFuncs[2])(u8 *);
    int field;
    storeFuncs[0] = gWifiSetupTextEntryParams.storeFuncs[0];
    storeFuncs[1] = gWifiSetupTextEntryParams.storeFuncs[1];
    if (WifiSetupDialog_IsOpen()) {
        return;
    }
    if (gWifiSetupTextEntry->result == WIFI_SETUP_TEXT_ENTRY_CANCELLED) {
        gWifiSetupTextEntry->cursor->attr01 &= 0xc1fffcff;
        WifiSetupApp_SetStateFunc(WifiSetupTextEntry_WaitFadeIn);
        return;
    }
    WifiSetupApp_GetScreenArgs(&field, 0);
    storeFuncs[field](gWifiSetupTextEntry->text);
    WifiSetupApp_SetStateFunc(WifiSetupTextEntry_End);
}

static BOOL WifiSetupTextEntry_IsTextValid(void) {
    int field, fromList, len;
    WifiSetupApp_GetScreenArgs(&field, &fromList);
    if (fromList == 1) {
        WifiSetupMessage_Show(0x35, -1, 0);
    }
    WifiSetupApp_GetScreenArgs(&field, &fromList);
    if (field == 0) {
        return gWifiSetupTextEntry->text[0] != 0;
    }
    if (fromList == 1 && gWifiSetupTextEntry->text[0] == 0) {
        return FALSE;
    }
    len = WifiSetup_StrNLen(gWifiSetupTextEntry->text, WIFI_SETUP_TEXT_ENTRY_MAX_LENGTH);
    switch (len) {
    case 0:
    case 5:
    case 13:
    case 16:
        return TRUE;
    case 10:
    case 26:
    case 32: {
        int i;
        for (i = 0; i < len; i++) {
            unsigned int ch = gWifiSetupTextEntry->text[i];
            if (ch >= '0' && ch <= '9') {
                continue;
            }
            if (ch >= 'A' && ch <= 'F') {
                continue;
            }
            if (ch >= 'a' && ch <= 'f') {
                continue;
            }
            return FALSE;
        }
    }
        return TRUE;
    default:
        return FALSE;
    }
}

static void WifiSetupTextEntry_WaitErrorDialog(void) {
    if (WifiSetupDialog_GetSelected()) {
        return;
    }
    WifiSetupSound_Play(6);
    WifiSetupDialog_Close();
    WifiSetupApp_SetStateFunc(WifiSetupTextEntry_WaitErrorDialogClosed);
}

static void WifiSetupTextEntry_WaitErrorDialogClosed(void) {
    if (WifiSetupDialog_IsOpen()) {
        return;
    }
    gWifiSetupTextEntry->cursor->attr01 &= 0xc1fffcff;
    WifiSetupApp_SetStateFunc(WifiSetupTextEntry_WaitFadeIn);
}
