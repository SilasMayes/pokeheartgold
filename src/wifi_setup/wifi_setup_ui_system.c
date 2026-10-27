#include <string.h>

#include "global.h"

#include "wifi_setup/wifi_setup_app.h"
#include "wifi_setup/wifi_setup_ui.h"

#include <nitro/code32.h>

#define MODULE_BSS_ADDR(addr) (&gWifiSetupShare + ((addr) - 0x0224F5C8) / 4)

static inline int GX_GetVisiblePlane13(void);
static inline int GXS_GetVisiblePlane13(void);
static inline void OamSetPosition(GXOamAttr *oam, int x, int y);
static inline void OamGetPosition(const GXOamAttr *oam, s32 *x, s32 *y);
static inline const G2dFontGlyph *GetFontGlyph(const G2dFont *font);
static void WifiSetupArchive_ReadDone(void *arg);
static BOOL WifiSetup_HasSameSuffix(const char *str1, const char *str2, int len);
static WifiSetupPool *WifiSetupPool_New(int capacity);
static void WifiSetupPool_Delete(WifiSetupPool *pool);
static void WifiSetupFade_Task(WifiSetupTask *task, void *arg);
static void WifiSetupFade_DelayTask(WifiSetupTask *task, void *arg);
static void WifiSetupText_BgTransferTask(WifiSetupTask *task, void *arg);
static void WifiSetupText_DrawChar(G2dCharCanvas *charCanvas, int x, int y, int color, u16 ch, int font);
static void *WifiSetupHeap_Alloc(u32 size, int align);
static void WifiSetupInput_UpdatePad(void);
static void WifiSetupInput_UpdateTouch(void);
static void WifiSetup_VBlankIntr(void);
static WifiSetupList *WifiSetupList_New(void);
static void WifiSetupList_Delete(WifiSetupList *list);
static void WifiSetupList_Remove(WifiSetupListNode *node);
static void WifiSetupList_InsertBefore(WifiSetupListNode *pos, WifiSetupListNode *node);
static void WifiSetupList_Append(WifiSetupList *list, WifiSetupListNode *node);
static void WifiSetupList_Prepend(WifiSetupList *list, WifiSetupListNode *node);
static void WifiSetupOam_TransferTask(WifiSetupTask *task, void *arg);
static GXOamAttr *WifiSetupOam_Alloc(enum WifiSetupScreen screen);
static GXOamAttr *WifiSetupOam_Get(int screen, int index);
static WifiSetupCharBlock *WifiSetupCharVram_Alloc(enum WifiSetupScreen screen, int size, BOOL fromFront, u32 *outCharNo);
static void WifiSetupCharVram_Free(WifiSetupCharBlock *block);
static void WifiSetup_ClearVram(void);
static WifiSetupTask *WifiSetupTask_CreateEx(enum WifiSetupTaskQueueId queue, WifiSetupTaskFunc func, void *arg, u32 priority, u8 ownsArg);
static void WifiSetupTask_DestroyNow(enum WifiSetupTaskQueueId queue, WifiSetupTask *task);

static inline int GX_GetVisiblePlane13(void) {
    return (reg_GX_DISPCNT & REG_GX_DISPCNT_DISPLAY_MASK) >> REG_GX_DISPCNT_DISPLAY_SHIFT;
}

static inline int GXS_GetVisiblePlane13(void) {
    return (reg_GXS_DB_DISPCNT & REG_GXS_DB_DISPCNT_DISPLAY_MASK) >> REG_GXS_DB_DISPCNT_DISPLAY_SHIFT;
}

static inline void OamSetPosition(GXOamAttr *oam, int x, int y) {
    oam->attr01 = (oam->attr01 & 0xFE00FF00) | (y & 0xFF) | ((x & 0x1FF) << 16);
}

static inline const G2dFontGlyph *GetFontGlyph(const G2dFont *font) {
    return font->pRes->pGlyph;
}

static inline void OamGetPosition(const GXOamAttr *oam, s32 *x, s32 *y) {
    *x = (oam->attr01 & 0x01FF0000) >> 16;
    *y = oam->attr01 & 0xFF;
}


fx32 FX_DivS32(fx32 a, fx32 b);
int GX_DisableBankForARM7(void);
void GX_SetBankForARM7(int bank);
int PM_GetLEDPattern(u32 *pattern);
void PMi_SendLEDPatternCommand(int pattern);
BOOL PM_SetLCDPower(int on);
void TP_RequestAutoSamplingStartAsync(u16 vcount, u16 freq, TPData *bufs, u16 size);
void TP_RequestAutoSamplingStopAsync(void);
void TP_WaitBusy(u32 flag);
u32 TP_CheckBusy(u32 flag);
u16 TP_GetLatestIndexInAuto(void);


void WifiSetupArchive_Unload(void) {
    FS_ChangeDir(gWifiSetupRomPrefix);
    FS_UnloadArchiveTables(&gWifiSetupArchive->arc);
    FS_UnloadArchive(&gWifiSetupArchive->arc);
    FS_ReleaseArchiveName(&gWifiSetupArchive->arc);
    OS_ReleaseLockID(gWifiSetupArchive->lockId);
    gWifiSetupArchive->lockId = 0;
    WifiSetupHeap_FreeAndClear(&gWifiSetupArchive->tables);
    gWifiSetupArchive->tables = NULL;
    WifiSetupHeap_FreeAndClear(MODULE_BSS_ADDR(0x0224F5CC));
}

FSResult WifiSetupArchive_Proc(FSFile *file, FSCommandType command) {
    switch (command) {
    case FS_COMMAND_ACTIVATE:
        CARD_LockRom(gWifiSetupArchive->lockId);
        return FS_RESULT_SUCCESS;
    case FS_COMMAND_IDLE:
        CARD_UnlockRom(gWifiSetupArchive->lockId);
        return FS_RESULT_SUCCESS;
    case FS_COMMAND_WRITEFILE:
        return FS_RESULT_UNSUPPORTED;
    default:
        return FS_RESULT_PROC_UNKNOWN;
    }
}

FSResult WifiSetupArchive_Read(FSArchive *arc, void *dst, u32 pos, u32 len) {
    CARDi_ReadRom((u32)-1, (const void *)(pos + arc->base), dst, len, WifiSetupArchive_ReadDone, arc, TRUE);
    return FS_RESULT_PROC_ASYNC;
}

static void WifiSetupArchive_ReadDone(void *arg) {
    FS_NotifyArchiveAsyncEnd(arg, FS_RESULT_SUCCESS);
}

FSResult WifiSetupArchive_Write(FSArchive *arc, const void *src, u32 pos, u32 len) {
    return FS_RESULT_FAILURE;
}

void *WifiSetupFile_Load(const char *path, u32 *outSize, int align) {
    void *buf;
    FSFile file;
    u32 size;
    int loadAlign;
    void *out;

    WifiSetupPool_Pop(gWifiSetupArchive->filePool);
    FS_InitFile(&file);
    if (!FS_OpenFile(&file, path)) {
        OS_Terminate();
    }
    size = FS_GetLength(&file);
    if (outSize != NULL) {
        *outSize = size;
    }
    // compressed files are loaded with a negative alignment (from the end of the heap)
    if (WifiSetup_HasSameSuffix(path, gWifiSetupCompressedSuffix, 2)) {
        loadAlign = -4;
    } else {
        loadAlign = align;
    }
    buf = WifiSetupHeap_AllocZeroed(size, loadAlign);
    FS_ReadFile(&file, buf, size);
    FS_CloseFile(&file);
    if (loadAlign > 0) {
        return buf;
    }
    size = MI_GetUncompressedSize(buf);
    if (outSize != NULL) {
        *outSize = size;
    }
    out = WifiSetupHeap_AllocZeroed(size, align);
    MI_UncompressLZ8(buf, out);
    WifiSetupHeap_FreeAndClear(&buf);
    return out;
}

void WifiSetupFile_Free(void *data) {
    WifiSetupHeap_FreeAndClear(&data);
    WifiSetupPool_Push(gWifiSetupArchive->filePool, data);
}

static BOOL WifiSetup_HasSameSuffix(const char *str1, const char *str2, int len) {
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    if (len1 < len || len2 < len) {
        return FALSE;
    }
    return memcmp(str1 + (len1 - len), str2 + (len2 - len), len) == 0;
}

void WifiSetupOamBlock_InitManager(void) {
    int i;
    gWifiSetupOamBlockManager = WifiSetupHeap_AllocZeroed(sizeof(WifiSetupOamBlockManager) * 2, 4);
    for (i = 0; i < 2; i++) {
        gWifiSetupOamBlockManager[i].pool = WifiSetupPool_NewWithItems(NELEMS(gWifiSetupOamBlockManager[i].blocks), gWifiSetupOamBlockManager[i].blocks, sizeof(WifiSetupOamBlock));
        gWifiSetupOamBlockManager[i].list = WifiSetupList_New();
        gWifiSetupOamBlockManager[i].first.oam = WifiSetupOam_Get(i, 0x40);
        gWifiSetupOamBlockManager[i].last.oam = WifiSetupOam_Get(i, 0x7F) + 1;
        WifiSetupList_Prepend(gWifiSetupOamBlockManager[i].list, &gWifiSetupOamBlockManager[i].first.node);
        WifiSetupList_Append(gWifiSetupOamBlockManager[i].list, &gWifiSetupOamBlockManager[i].last.node);
    }
}

void WifiSetupOamBlock_FreeManager(void) {
    int i;
    for (i = 0; i < 2; i++) {
        WifiSetupList_Delete(gWifiSetupOamBlockManager[i].list);
        WifiSetupPool_Delete(gWifiSetupOamBlockManager[i].pool);
    }
    WifiSetupHeap_FreeAndClear(MODULE_BSS_ADDR(0x0224F5D0));
}

WifiSetupOamBlock *WifiSetupOamBlock_Alloc(enum WifiSetupScreen screen, int count, BOOL fromFront) {
    WifiSetupOamBlock *block;
    WifiSetupOamBlock *cur;
    int irq;

    block = WifiSetupPool_Pop(gWifiSetupOamBlockManager[screen].pool);
    irq = OS_DisableIrqMask(OS_IE_V_BLANK);
    if (fromFront) {
        cur = &gWifiSetupOamBlockManager[screen].first;
        while (cur != &gWifiSetupOamBlockManager[screen].last) {
            WifiSetupOamBlock *next = (WifiSetupOamBlock *)cur->node.next;
            GXOamAttr *start = cur->oam + cur->count;
            if (start + count <= next->oam) {
                block->oam = start;
                WifiSetupList_InsertBefore(&next->node, &block->node);
                break;
            }
            cur = next;
        }
        if (cur == &gWifiSetupOamBlockManager[screen].last) {
            OS_Terminate();
        }
    } else {
        cur = &gWifiSetupOamBlockManager[screen].last;
        while (cur != &gWifiSetupOamBlockManager[screen].first) {
            WifiSetupOamBlock *prev = (WifiSetupOamBlock *)cur->node.prev;
            GXOamAttr *start = cur->oam - count;
            if (start >= prev->oam + prev->count) {
                block->oam = start;
                WifiSetupList_InsertBefore(&cur->node, &block->node);
                break;
            }
            cur = prev;
        }
        if (cur == &gWifiSetupOamBlockManager[screen].first) {
            OS_Terminate();
        }
    }
    OS_EnableIrqMask(irq);
    block->count = count;
    return block;
}

void WifiSetupOamBlock_Free(WifiSetupOamBlock *block) {
    int screen = 0;
    GXOamAttr *oam = block->oam;
    int i;
    for (i = 0; i < block->count; i++) {
        oam->attr01 = (oam->attr01 & 0xC1FFFCFF) | 0x200; // hide
        oam++;
    }
    WifiSetupList_Remove(&block->node);
    if (block >= gWifiSetupOamBlockManager[1].blocks) {
        screen = 1;
    }
    WifiSetupPool_Push(gWifiSetupOamBlockManager[screen].pool, block);
}

GXOamAttr *WifiSetupOamBlock_GetOam(WifiSetupOamBlock *block, int index) {
    return &block->oam[index];
}

u8 WifiSetupOamBlock_GetCount(WifiSetupOamBlock *block) {
    return block->count;
}

// index < 0: every entry of the block. Modes 0x100 and 0x300 (affine) also take the affine parameter.
void WifiSetupOamBlock_SetAffineMode(WifiSetupOamBlock *block, int index, u32 mode, u32 param) {
    GXOamAttr *oam = block->oam;
    if (index >= 0) {
        if (mode != 256 && mode != 768) {
            u32 value = oam[index].attr01 & 0xc1fffcff;
            value |= mode;
            oam[index].attr01 = value;
        } else {
            u32 value = oam[index].attr01 & 0xc1fffcff;
            value |= mode;
            value |= param << 25;
            oam[index].attr01 = value;
        }
        return;
    }
    for (index = 0; index < block->count; index++) {
        u32 value;
        if (mode != 256 && mode != 768) {
            value = oam[index].attr01 & 0xc1fffcff;
            value |= mode;
        } else {
            {
                value = oam[index].attr01 & 0xc1fffcff;
                value |= mode;
            }
            value |= param << 25;
        }
        oam[index].attr01 = value;
    }
}

void WifiSetupOamBlock_SetModeAndPalette(WifiSetupOamBlock *block, int index, u32 mode, u32 palette) {
    GXOamAttr *oam = block->oam;
    int i;
    if (index >= 0) {
        oam[index].attr01 = (oam[index].attr01 & ~0xC00) | (mode << 10);
        oam[index].attr2 = (oam[index].attr2 & ~0xF000) | (palette << 12);
        return;
    }
    for (i = 0; i < block->count; i++) {
        oam[i].attr01 = (oam[i].attr01 & ~0xC00) | (mode << 10);
        oam[i].attr2 = (oam[i].attr2 & ~0xF000) | (palette << 12);
    }
}

// index < 0: moves the whole block so that its first entry lands on (x, y).
void WifiSetupOamBlock_SetPosition(WifiSetupOamBlock *block, int index, int x, int y) {
    GXOamAttr *oam = block->oam;
    if (index >= 0) {
        OamSetPosition(&oam[index], x, y);
    } else {
        int oldX;
        int oldY;
        int curX;
        int curY;
        int i;
        int dx;
        int dy;
        OamGetPosition(&oam[0], (s32 *)&oldX, (s32 *)&oldY);
        OamSetPosition(&oam[0], x, y);
        dx = x - oldX;
        dy = y - oldY;
        for (i = 1; i < block->count; i++) {
            OamGetPosition(&oam[i], (s32 *)&curX, (s32 *)&curY);
            OamSetPosition(&oam[i], curX + dx, curY + dy);
        }
    }
}

void WifiSetupOamBlock_SetPriority(WifiSetupOamBlock *block, int index, u32 priority) {
    GXOamAttr *oam = block->oam;
    int i;
    if (index >= 0) {
        oam[index].attr2 = (oam[index].attr2 & ~0xC00) | (priority << 10);
        return;
    }
    for (i = 0; i < block->count; i++) {
        oam[i].attr2 = (oam[i].attr2 & ~0xC00) | (priority << 10);
    }
}

void WifiSetupOamBlock_GetPosition(WifiSetupOamBlock *block, int index, int *x, int *y) {
    GXOamAttr *oam = block->oam;
    *x = (oam[index].attr01 & 0x01FF0000) >> 16;
    *y = oam[index].attr01 & 0xFF;
}

void WifiSetupOamTemplate_Load(enum WifiSetupScreen screen, const char *path) {
    u32 size;
    gWifiSetupOamTemplateFiles[screen] = WifiSetupFile_Load(path, &size, 4);
}

void WifiSetupOamTemplate_Free(enum WifiSetupScreen screen) {
    WifiSetupFile_Free(gWifiSetupOamTemplateFiles[screen]);
    gWifiSetupOamTemplateFiles[screen] = NULL;
}

void WifiSetupOamTemplate_Copy(enum WifiSetupScreen screen, int index, GXOamAttr *dst) {
    WifiSetupOamTemplateHeader *headers = gWifiSetupOamTemplateFiles[screen];
    u8 *src = (u8 *)headers + headers[index].offset;
    u16 count = headers[index].count;
    GXOamAttr tmp;
    int i;
    MI_CpuClear32(&tmp, sizeof(GXOamAttr));
    for (i = 0; i < count; i++) {
        MI_CpuCopy16(src, &tmp, 6);
        MI_CpuCopy32(&tmp, dst, sizeof(GXOamAttr));
        src += 6;
        dst++;
    }
}

GXOamAttr *WifiSetupOamTemplate_AllocOam(enum WifiSetupScreen screen, int index) {
    GXOamAttr *oam = WifiSetupOam_Alloc(screen);
    WifiSetupOamTemplate_Copy(screen, index, oam);
    return oam;
}

WifiSetupOamBlock *WifiSetupOamTemplate_AllocBlock(enum WifiSetupScreen screen, int index, BOOL fromFront) {
    WifiSetupOamBlock *block = WifiSetupOamBlock_Alloc(screen, gWifiSetupOamTemplateFiles[screen][index].count, fromFront);
    WifiSetupOamTemplate_Copy(screen, index, WifiSetupOamBlock_GetOam(block, 0));
    return block;
}

static WifiSetupPool *WifiSetupPool_New(int capacity) {
    WifiSetupPool *pool = WifiSetupHeap_AllocZeroed((capacity + 1) * 4 + 8, 4);
    pool->size = capacity + 1;
    pool->head = 0;
    pool->tail = 0;
    return pool;
}

WifiSetupPool *WifiSetupPool_NewWithItems(int count, void *items, int stride) {
    WifiSetupPool *pool = WifiSetupPool_New(count);
    int i;
    for (i = 0; i < count; i++) {
        pool->items[i] = items;
        items = (u8 *)items + stride;
    }
    pool->tail = count;
    return pool;
}

static void WifiSetupPool_Delete(WifiSetupPool *pool) {
    WifiSetupHeap_FreeAndClear(&pool);
}

void *WifiSetupPool_Push(WifiSetupPool *pool, void *item) {
    int irq = OS_DisableIrqMask(OS_IE_V_BLANK);
    int next = FX_ModS32(pool->tail + 1, pool->size);
    if (next == pool->head) {
        OS_Terminate();
    }
    pool->items[pool->tail] = item;
    pool->tail = next;
    OS_EnableIrqMask(irq);
}

void *WifiSetupPool_Pop(WifiSetupPool *pool) {
    void *ret = NULL;
    int irq = OS_DisableIrqMask(OS_IE_V_BLANK);
    if (pool->head != pool->tail) {
        pool->tail = FX_ModS32(pool->tail + pool->size - 1, pool->size);
        ret = pool->items[pool->tail];
    }
    OS_EnableIrqMask(irq);
    return ret;
}

void WifiSetupFade_Init(void) {
    gWifiSetupFades = WifiSetupHeap_AllocZeroed(sizeof(WifiSetupFade) * 2, 4);
    G2_SetBlendBrightness(0x3F, 0x10);
    G2S_SetBlendBrightness(0x3F, 0x10);
}

void WifiSetupFade_Free(void) {
    WifiSetupHeap_FreeAndClear(&gWifiSetupFades);
}

u8 WifiSetupFade_IsActive(enum WifiSetupScreen screen) {
    WifiSetupFade *fade;
    if (screen == WIFI_SETUP_SCREEN_SUB) {
        fade = &gWifiSetupFades[0];
    } else {
        fade = &gWifiSetupFades[1];
    }
    return fade->active;
}

BOOL WifiSetupFade_Start(enum WifiSetupFadeKind kind, enum WifiSetupScreen screen, int planes, int duration) {
    WifiSetupBrightnessTable start = gWifiSetupFadeTables[2];
    WifiSetupFade *fade;
    if (screen == WIFI_SETUP_SCREEN_SUB) {
        fade = &gWifiSetupFades[0];
    } else {
        fade = &gWifiSetupFades[1];
    }
    if (fade->active) {
        return FALSE;
    }
    if (screen == WIFI_SETUP_SCREEN_SUB) {
        G2S_SetBlendBrightness(planes, start.values[kind]);
    } else {
        G2_SetBlendBrightness(planes, start.values[kind]);
    }
    fade->task = WifiSetupTask_Create(WIFI_SETUP_TASK_QUEUE_VBLANK, WifiSetupFade_Task, fade, 0xC8);
    fade->counter = 0;
    fade->kind = kind;
    fade->duration = duration;
    fade->active = 1;
    return TRUE;
}

static void WifiSetupFade_Task(WifiSetupTask *task, void *arg) {
    WifiSetupFade *fade = arg;
    WifiSetupBrightnessTable flags = gWifiSetupFadeTables[1];
    WifiSetupBrightnessTable end = gWifiSetupFadeTables[0];
    int brightness;
    u8 kindFlags;
    fade->counter++;
    brightness = FX_DivS32(fade->counter << 4, fade->duration);
    kindFlags = flags.values[fade->kind];
    if (kindFlags & 1) {
        brightness = 16 - brightness;
    }
    if (kindFlags & 0x10) {
        brightness = -brightness;
    }
    if (fade == gWifiSetupFades) {
        G2x_ChangeBlendBrightness_((u16 *)&reg_G2S_DB_BLDCNT, brightness);
    } else {
        G2x_ChangeBlendBrightness_((u16 *)&reg_G2_BLDCNT, brightness);
    }
    if (fade->counter < fade->duration) {
        return;
    }
    if (fade == gWifiSetupFades) {
        G2x_ChangeBlendBrightness_((u16 *)&reg_G2S_DB_BLDCNT, end.values[fade->kind]);
    } else {
        G2x_ChangeBlendBrightness_((u16 *)&reg_G2_BLDCNT, end.values[fade->kind]);
    }
    fade->active = 0;
    WifiSetupTask_DestroyLater(WIFI_SETUP_TASK_QUEUE_VBLANK, task);
}

BOOL WifiSetupFade_StartDelay(int duration) {
    WifiSetupFade *fade = gWifiSetupFades;
    if (fade->active) {
        return FALSE;
    }
    fade->task = WifiSetupTask_Create(WIFI_SETUP_TASK_QUEUE_VBLANK, WifiSetupFade_DelayTask, fade, 0xC8);
    fade->counter = 0;
    fade->duration = duration;
    fade->active = 1;
    return TRUE;
}

static void WifiSetupFade_DelayTask(WifiSetupTask *task, void *arg) {
    WifiSetupFade *fade = arg;
    fade->counter++;
    if (fade->counter < fade->duration) {
        return;
    }
    fade->active = 0;
    WifiSetupTask_DestroyLater(WIFI_SETUP_TASK_QUEUE_VBLANK, task);
}

void WifiSetupText_Init(void) {
    WifiSetupTextState *text;
    int i;
    gWifiSetupText = text = WifiSetupHeap_AllocZeroed(sizeof(WifiSetupTextState), 4);
    gWifiSetupText->objCanvasPool = WifiSetupPool_NewWithItems(NELEMS(text->objCanvases), text->objCanvases, sizeof(WifiSetupCanvas));
    if (WifiSetupApp_GetLanguage() == 6) {
        for (i = 0; i < 2; i++) {
            gWifiSetupText->fontData[i] = WifiSetupFile_Load(gWifiSetupFontPathsKorean[i], NULL, 4);
            NNS_G2dFontInitUTF16(&gWifiSetupText->fonts[i], gWifiSetupText->fontData[i]);
        }
    } else {
        for (i = 0; i < 2; i++) {
            gWifiSetupText->fontData[i] = WifiSetupFile_Load(gWifiSetupFontPaths[i], NULL, 4);
            NNS_G2dFontInitUTF16(&gWifiSetupText->fonts[i], gWifiSetupText->fontData[i]);
        }
    }
}

void WifiSetupText_Free(void) {
    int i;
    for (i = 0; i < 2; i++) {
        WifiSetupFile_Free(gWifiSetupText->fontData[i]);
    }
    WifiSetupPool_Delete(gWifiSetupText->objCanvasPool);
    WifiSetupHeap_FreeAndClear(MODULE_BSS_ADDR(0x0224F5E0));
}

WifiSetupCanvas *WifiSetupText_AllocObjCanvas(enum WifiSetupScreen screen, int width, int height, BOOL fromFront, u32 *numObjs, int font) {
    u32 charNo;
    WifiSetupCanvas *canvas = WifiSetupPool_Pop(gWifiSetupText->objCanvasPool);
    canvas->u.obj.width = width;
    canvas->u.obj.height = height;
    canvas->charBuf = WifiSetupCharVram_Alloc(screen, width * height, fromFront, &charNo);
    canvas->u.obj.charNo = charNo;
    *numObjs = NNSi_G2dCalcRequiredOBJ(width, height);
    {
        u32 tile = charNo;
        u32 base = screen == WIFI_SETUP_SCREEN_SUB ? HW_DB_OBJ_VRAM : HW_OBJ_VRAM;
        NNS_G2dCharCanvasInitForOBJ1D(&canvas->charCanvas, (void *)(base + (tile << 7)), width, height, 4);
    }
    canvas->charCanvas.vtable->pClear(&canvas->charCanvas, 0);
    {
        G2dFont *fontPtr = &gWifiSetupText->fonts[font];
        canvas->textCanvas.pCanvas = &canvas->charCanvas;
        canvas->textCanvas.pFont = fontPtr;
    }
    canvas->textCanvas.hSpace = 1;
    canvas->textCanvas.vSpace = 1;
    return canvas;
}

void WifiSetupText_FreeObjCanvas(WifiSetupCanvas *canvas) {
    WifiSetupCharVram_Free(canvas->charBuf);
    WifiSetupPool_Push(gWifiSetupText->objCanvasPool, canvas);
}

WifiSetupCanvas *WifiSetupText_InitBgCanvas(enum WifiSetupScreen screen, int font) {
    u32 height = gWifiSetupTextScreenHeights[screen * 2], width = gWifiSetupTextScreenWidths[screen * 2];
    WifiSetupCanvas *canvas = &gWifiSetupText->bgCanvases[screen];
    void *screenBuf;
    canvas->charBuf = WifiSetupHeap_AllocZeroed(width * height * 32, 32);
    if (screen == WIFI_SETUP_SCREEN_SUB) {
        G2S_BG0Mosaic(FALSE);
        G2S_SetBG0Control(GX_BG_SCRSIZE_TEXT_256x256, GX_BG_COLORMODE_16, GX_BG_SCRBASE_0x6000, GX_BG_CHARBASE_0x00000, GX_BG_EXTPLTT_01);
    } else {
        G2_BG0Mosaic(FALSE);
        G2_SetBG0Control(GX_BG_SCRSIZE_TEXT_256x256, GX_BG_COLORMODE_16, GX_BG_SCRBASE_0x6000, GX_BG_CHARBASE_0x00000, GX_BG_EXTPLTT_01);
    }
    NNS_G2dCharCanvasInitForBG(&canvas->charCanvas, canvas->charBuf, width, height, 4);
    {
        WifiSetupTextState *text = gWifiSetupText;
        int sub = screen == WIFI_SETUP_SCREEN_SUB;
        canvas->textCanvas.pCanvas = &canvas->charCanvas;
        canvas->textCanvas.pFont = &text->fonts[font];
        canvas->textCanvas.hSpace = 1;
        canvas->textCanvas.vSpace = 1;
        if (sub) {
            screenBuf = G2S_GetBG0ScrPtr();
        } else {
            screenBuf = G2_GetBG0ScrPtr();
        }
    }
    NNS_G2dMapScrToCharText(screenBuf, width, height, 0, 0, 32, gWifiSetupTextScreenCharBases[screen], 15);
    WifiSetupText_Clear(canvas, 0);
    canvas->u.task = WifiSetupTask_Create(WIFI_SETUP_TASK_QUEUE_VBLANK, WifiSetupText_BgTransferTask, &gWifiSetupText->bgDirty[screen], 200);
    return canvas;
}

static void WifiSetupText_BgTransferTask(WifiSetupTask *task, void *arg) {
    u8 *dirty = arg;
    if (*dirty == 0) {
        return;
    }
    if (dirty == &gWifiSetupText->bgDirty[0]) {
        DC_FlushRange(gWifiSetupText->bgCanvases[0].charBuf, 0x6000);
        GX_LoadBG0Char(gWifiSetupText->bgCanvases[0].charBuf, 0, 0x6000);
    } else {
        DC_FlushRange(gWifiSetupText->bgCanvases[1].charBuf, 0x3000);
        GXS_LoadBG0Char(gWifiSetupText->bgCanvases[1].charBuf, 0x3000, 0x3000);
    }
    *dirty = 0;
}

void WifiSetupText_FreeCanvas(WifiSetupCanvas *canvas) {
    WifiSetupTask_Destroy(WIFI_SETUP_TASK_QUEUE_VBLANK, canvas->u.task);
    if (canvas == &gWifiSetupText->bgCanvases[0]) {
        MIi_CpuClear16(0, G2_GetBG0CharPtr(), 0x6000);
    } else {
        MIi_CpuClear16(0, G2_GetBG0CharPtr(), 0x3000);
    }
    WifiSetupHeap_FreeAndClear(&canvas->charBuf);
}

void WifiSetupText_FreeBgCanvas(enum WifiSetupScreen screen) {
    WifiSetupText_FreeCanvas(&gWifiSetupText->bgCanvases[screen]);
}

void WifiSetupText_Draw(WifiSetupCanvas *canvas, int x, int y, int color, u32 flags, const u16 *text) {
    const G2dFont *font = canvas->textCanvas.pFont;
    G2dTextDirection dir = { 0, 0 };
    switch (GetFontGlyph(font)->rotation) {
    case 0:
    case 7:
        dir.x = 1;
        break;
    case 1:
    case 2:
        dir.y = 1;
        break;
    case 3:
    case 4:
        dir.x = -1;
        break;
    case 5:
    case 6:
        dir.y = -1;
        break;
    }
    NNSi_G2dTextCanvasDrawText(&canvas->textCanvas, x, y, color, flags, text, dir);
}

static void WifiSetupText_DrawChar(G2dCharCanvas *charCanvas, int x, int y, int color, u16 ch, int font) {
    NNS_G2dCharCanvasDrawChar(charCanvas, &gWifiSetupText->fonts[font], x, y, color, ch);
}

// Draws every character centred in a cell of advance pixels.
void WifiSetupText_DrawMonospace(WifiSetupCanvas *canvas, int x, int y, int color, int advance, const u16 *text, int font) {
    G2dFont *fontPtr;
    u16 glyph;
    const G2dCharWidths *widths;
    while (*text != 0) {
        fontPtr = &gWifiSetupText->fonts[font];
        glyph = NNS_G2dFontFindGlyphIndex(fontPtr, *text);
        if (glyph == G2D_FONT_NO_GLYPH) {
            glyph = fontPtr->pRes->alterCharIndex;
        }
        widths = NNS_G2dFontGetCharWidthsFromIndex(fontPtr, glyph);
        WifiSetupText_DrawChar(&canvas->charCanvas, x + ((advance - widths->charWidth) >> 1), y, color, *text, font);
        text++;
        x += advance;
    }
}

void WifiSetupText_DrawInRect(WifiSetupCanvas *canvas, int x, int y, int width, int height, int color, u32 flags, const u16 *text) {
    const G2dFont *font = canvas->textCanvas.pFont;
    G2dTextDirection dir = { 0, 0 };
    switch (GetFontGlyph(font)->rotation) {
    case 0:
    case 7:
        dir.x = 1;
        break;
    case 1:
    case 2:
        dir.y = 1;
        break;
    case 3:
    case 4:
        dir.x = -1;
        break;
    case 5:
    case 6:
        dir.y = -1;
        break;
    }
    NNSi_G2dTextCanvasDrawTextRect(&canvas->textCanvas, x, y, width, height, color, flags, text, dir);
}

void WifiSetupText_Clear(WifiSetupCanvas *canvas, int color) {
    canvas->charCanvas.vtable->pClear(&canvas->charCanvas, color);
}

void WifiSetupText_ShowObjCanvas(WifiSetupCanvas *canvas, int x, int y, WifiSetupOamBlock *block, u32 priority) {
    GXOamAttr *oam = WifiSetupOamBlock_GetOam(block, 0);
    WifiSetupOamBlock_SetAffineMode(block, -1, 0, 0);
    WifiSetupOamBlock_SetModeAndPalette(block, -1, 0, 0xF);
    WifiSetupOamBlock_SetPriority(block, -1, priority);
    NNS_G2dArrangeOBJ1D(oam, canvas->u.obj.width, canvas->u.obj.height, x, y, 0, canvas->u.obj.charNo, 2);
}

void WifiSetupText_MarkDirty(WifiSetupCanvas *canvas) {
    if (canvas == &gWifiSetupText->bgCanvases[0]) {
        gWifiSetupText->bgDirty[0] = 1;
    } else {
        gWifiSetupText->bgDirty[1] = 1;
    }
}

void WifiSetup_SetPoint(u16 x, u16 y, WifiSetupPoint *point) {
    point->x = x;
    point->y = y;
}

void WifiSetup_SetRect(int left, int top, int right, int bottom, WifiSetupRect *rect) {
    rect->left = left;
    rect->top = top;
    rect->right = right;
    rect->bottom = bottom;
}

void WifiSetup_RectFromPosSize(const WifiSetupPoint *pos, const WifiSetupPoint *size, WifiSetupRect *rect) {
    rect->left = pos->x;
    rect->top = pos->y;
    rect->right = pos->x + size->x;
    rect->bottom = pos->y + size->y;
}

void WifiSetupDisplay_ShowPlanes(enum WifiSetupScreen screen, int planes) {
    if (screen == WIFI_SETUP_SCREEN_SUB) {
        GXS_SetVisiblePlane(planes | GXS_GetVisiblePlane13());
    } else {
        GX_SetVisiblePlane(planes | GX_GetVisiblePlane13());
    }
}

void WifiSetupDisplay_HidePlanes(enum WifiSetupScreen screen, int planes) {
    if (screen == WIFI_SETUP_SCREEN_SUB) {
        GXS_SetVisiblePlane(~planes & GXS_GetVisiblePlane13());
    } else {
        GX_SetVisiblePlane(~planes & GX_GetVisiblePlane13());
    }
}

void WifiSetupDisplay_SetWindowRect(enum WifiSetupScreen screen, enum WifiSetupWindow window, WifiSetupRect *rect) {
    if (screen == WIFI_SETUP_SCREEN_SUB) {
        if (window == WIFI_SETUP_WINDOW_0) {
            G2S_SetWnd0Position(rect->left, rect->top, rect->right, rect->bottom);
        } else {
            G2S_SetWnd1Position(rect->left, rect->top, rect->right, rect->bottom);
        }
    } else {
        if (window == WIFI_SETUP_WINDOW_0) {
            G2_SetWnd0Position(rect->left, rect->top, rect->right, rect->bottom);
        } else {
            G2_SetWnd1Position(rect->left, rect->top, rect->right, rect->bottom);
        }
    }
}

void WifiSetupDisplay_SetWindowPlanes(enum WifiSetupScreen screen, enum WifiSetupWindow window, int planes, BOOL effect) {
    switch (window) {
    case WIFI_SETUP_WINDOW_0:
        if (screen == WIFI_SETUP_SCREEN_SUB) {
            G2S_SetWnd0InsidePlane(planes, effect);
        } else {
            G2_SetWnd0InsidePlane(planes, effect);
        }
        break;
    case WIFI_SETUP_WINDOW_1:
        if (screen == WIFI_SETUP_SCREEN_SUB) {
            G2S_SetWnd1InsidePlane(planes, effect);
        } else {
            G2_SetWnd1InsidePlane(planes, effect);
        }
        break;
    case WIFI_SETUP_WINDOW_OBJ:
        if (screen == WIFI_SETUP_SCREEN_SUB) {
            u32 tmp = (reg_G2S_DB_WINOUT & ~REG_G2S_DB_WINOUT_OBJWININ_MASK) | (planes << REG_G2S_DB_WINOUT_OBJWININ_SHIFT);
            if (effect) {
                tmp |= (0x20 << REG_G2S_DB_WINOUT_OBJWININ_SHIFT);
            }
            reg_G2S_DB_WINOUT = tmp;
        } else {
            u32 tmp = (reg_G2_WINOUT & ~REG_G2_WINOUT_OBJWININ_MASK) | (planes << REG_G2_WINOUT_OBJWININ_SHIFT);
            if (effect) {
                tmp |= (0x20 << REG_G2_WINOUT_OBJWININ_SHIFT);
            }
            reg_G2_WINOUT = tmp;
        }
        break;
    case WIFI_SETUP_WINDOW_OUTSIDE:
        if (screen == WIFI_SETUP_SCREEN_SUB) {
            G2S_SetWndOutsidePlane(planes, effect);
        } else {
            G2_SetWndOutsidePlane(planes, effect);
        }
        break;
    }
}

void WifiSetupHeap_Init(void *mem) {
    MI_CpuFill8(mem, 0, 0x40000);
    gWifiSetupHeap = NNS_FndCreateExpHeapEx(mem, 0x40000, 0);
    if (gWifiSetupHeap == NULL) {
        OS_Terminate();
    }
}

void WifiSetupHeap_Destroy(void) {
    NNS_FndDestroyExpHeap(gWifiSetupHeap);
    gWifiSetupHeap = NULL;
}

static void *WifiSetupHeap_Alloc(u32 size, int align) {
    void *mem;
    int irq;
    irq = OS_DisableIrqMask(OS_IE_V_BLANK);
    mem = NNS_FndAllocFromExpHeapEx(gWifiSetupHeap, size, align);
    if (mem == NULL) {
        OS_Terminate();
    }
    OS_EnableIrqMask(irq);
    return mem;
}

void *WifiSetupHeap_AllocZeroed(u32 size, int align) {
    void *mem = WifiSetupHeap_Alloc(size, align);
    MI_CpuFill8(mem, 0, size);
    return mem;
}

// ptr points to the pointer to free; it is set to NULL.
void WifiSetupHeap_FreeAndClear(void *ptr) {
    int irq = OS_DisableIrqMask(OS_IE_V_BLANK);
    if (*(void **)ptr == NULL) {
        return;
    }
    NNS_FndFreeToExpHeap(gWifiSetupHeap, *(void **)ptr);
    OS_EnableIrqMask(irq);
    *(void **)ptr = NULL;
}

void WifiSetupHeap_Free(void *mem) {
    int irq = OS_DisableIrqMask(OS_IE_V_BLANK);
    if (mem == NULL) {
        return;
    }
    NNS_FndFreeToExpHeap(gWifiSetupHeap, mem);
    OS_EnableIrqMask(irq);
}

void WifiSetupInput_Init(void) {
    TPCalibrateParam calibrate;
    gWifiSetupInput.state = WifiSetupHeap_AllocZeroed(sizeof(WifiSetupInputState), 4);
    if (!TP_GetUserInfo(&calibrate)) {
        OS_Terminate();
    }
    TP_SetCalibrateParam(&calibrate);
    TP_RequestAutoSamplingStartAsync(0, 4, gWifiSetupInput.state->samples, NELEMS(gWifiSetupInput.state->samples));
    TP_WaitBusy(2);
    if (TP_CheckBusy(2)) {
        OS_Terminate();
    }
    WifiSetupInput_Update();
}

void WifiSetupInput_Free(void) {
    do {
        TP_RequestAutoSamplingStopAsync();
        TP_WaitBusy(4);
    } while (TP_CheckBusy(4));
    WifiSetupHeap_FreeAndClear(&gWifiSetupInput.state);
}

void WifiSetupInput_Update(void) {
    WifiSetupInput_UpdatePad();
    WifiSetupInput_UpdateTouch();
}

// Key repeat: first after 40 frames, then every 7 frames.
static void WifiSetupInput_UpdatePad(void) {
    int i;
    u8 *holdFrames;
    WifiSetupInputState *state = gWifiSetupInput.state;
    u16 pad = PAD_Read();
    gWifiSetupInput.state->trig = (state->cont ^ pad) & pad;
    gWifiSetupInput.state->release = state->cont & (state->cont ^ pad);
    gWifiSetupInput.state->cont = pad;
    gWifiSetupInput.state->repeat = gWifiSetupInput.state->trig;
    holdFrames = gWifiSetupInputHoldFrames;
    for (i = 0; i < 14; i++) {
        u16 bit = 1 << i;
        if ((pad & bit) == 0) {
            *holdFrames = 0;
        } else {
            (*holdFrames)++;
            if (*holdFrames == 40) {
                gWifiSetupInput.state->repeat |= bit;
            } else if (*holdFrames == 47) {
                gWifiSetupInput.state->repeat |= bit;
                *holdFrames = 40;
            }
        }
        holdFrames++;
    }
}

static void WifiSetupInput_UpdateTouch(void) {
    int tries;
    int index;
    int wasTouching;
    u8 touched;
    int changed;
    TPData calibrated;

    wasTouching = gWifiSetupInput.state->touching ? 1 : 0;
    touched = 0;
    index = TP_GetLatestIndexInAuto();
    gWifiSetupInput.state->prevTouch = gWifiSetupInput.state->touch;
    tries = 0;
    do {
        TPData *sample = &gWifiSetupInput.state->samples[index];
        if (sample->touch == TP_TOUCH_ON && sample->validity == TP_VALIDITY_VALID) {
            touched = 1;
            TP_GetCalibratedPoint(&calibrated, sample);
            WifiSetup_SetPoint(calibrated.x, calibrated.y, &gWifiSetupInput.state->touch);
            break;
        }
        tries++;
        index = FX_ModS32(index + 4, 5);
    } while (tries < 4);
    changed = touched ^ wasTouching;
    gWifiSetupInput.state->touchTrig = touched & changed;
    gWifiSetupInput.state->touchRelease = wasTouching & changed;
    gWifiSetupInput.state->touching = touched;
    gWifiSetupInput.state->touchRepeat = gWifiSetupInput.state->touchTrig;
    if (!touched) {
        gWifiSetupInput.touchHoldFrames = 0;
        return;
    }
    gWifiSetupInput.touchHoldFrames++;
    if (gWifiSetupInput.touchHoldFrames == 40) {
        gWifiSetupInput.state->touchRepeat = 1;
    } else if (gWifiSetupInput.touchHoldFrames == 47) {
        gWifiSetupInput.state->touchRepeat = 1;
        gWifiSetupInput.touchHoldFrames = 40;
    }
}

BOOL WifiSetupInput_IsKeyPressed(u16 mask) {
    if (PAD_DetectFold()) {
        return FALSE;
    }
    return mask == (mask & gWifiSetupInput.state->trig);
}

BOOL WifiSetupInput_IsKeyRepeated(u16 mask) {
    if (PAD_DetectFold()) {
        return FALSE;
    }
    return mask == (mask & gWifiSetupInput.state->repeat);
}

BOOL WifiSetupInput_IsKeyReleased(u16 mask) {
    if (PAD_DetectFold()) {
        return FALSE;
    }
    return mask == (mask & gWifiSetupInput.state->release);
}

BOOL WifiSetupInput_IsTouchHeld(WifiSetupRect *rect) {
    WifiSetupInputState *state;
    if (PAD_DetectFold()) {
        return FALSE;
    }
    state = gWifiSetupInput.state;
    if (!state->touching) {
        return FALSE;
    }
    if (rect->left > state->touch.x) {
        return FALSE;
    }
    if (rect->right < state->touch.x) {
        return FALSE;
    }
    if (rect->top > state->touch.y) {
        return FALSE;
    }
    return rect->bottom >= state->touch.y;
}

BOOL WifiSetupInput_IsTouchPressed(WifiSetupRect *rect) {
    WifiSetupInputState *state;
    if (PAD_DetectFold()) {
        return FALSE;
    }
    state = gWifiSetupInput.state;
    if (!state->touchTrig) {
        return FALSE;
    }
    if (rect->left > state->touch.x) {
        return FALSE;
    }
    if (rect->right < state->touch.x) {
        return FALSE;
    }
    if (rect->top > state->touch.y) {
        return FALSE;
    }
    return rect->bottom >= state->touch.y;
}

BOOL WifiSetupInput_IsTouchRepeated(WifiSetupRect *rect) {
    WifiSetupInputState *state;
    if (PAD_DetectFold()) {
        return FALSE;
    }
    state = gWifiSetupInput.state;
    if (!state->touchRepeat) {
        return FALSE;
    }
    if (rect->left > state->touch.x) {
        return FALSE;
    }
    if (rect->right < state->touch.x) {
        return FALSE;
    }
    if (rect->top > state->touch.y) {
        return FALSE;
    }
    return rect->bottom >= state->touch.y;
}

BOOL WifiSetupInput_IsTouchReleased(WifiSetupRect *rect) {
    WifiSetupInputState *state;
    if (PAD_DetectFold()) {
        return FALSE;
    }
    state = gWifiSetupInput.state;
    if (!state->touchRelease) {
        return FALSE;
    }
    if (rect->left > state->touch.x) {
        return FALSE;
    }
    if (rect->right < state->touch.x) {
        return FALSE;
    }
    if (rect->top > state->touch.y) {
        return FALSE;
    }
    return rect->bottom >= state->touch.y;
}

// box: left/top are the position, right/bottom the width and height.
BOOL WifiSetupInput_IsTouchPressedInBox(WifiSetupRect *box) {
    WifiSetupRect rect;
    if (PAD_DetectFold()) {
        return FALSE;
    }
    rect.left = box->left;
    rect.top = box->top;
    rect.right = box->left + box->right;
    rect.bottom = box->top + box->bottom;
    return WifiSetupInput_IsTouchPressed(&rect);
}

BOOL WifiSetupInput_GetTouchPos(WifiSetupPoint *out) {
    WifiSetupInputState *state;
    if (PAD_DetectFold()) {
        return FALSE;
    }
    state = gWifiSetupInput.state;
    if (!state->touching) {
        *out = state->prevTouch;
        return FALSE;
    }
    *out = state->touch;
    return TRUE;
}

// Turns the LCDs off while the lid is closed and back on when it opens.
void WifiSetupInput_UpdateLcdPower(void) {
    if (gWifiSetupInput.lcdOff) {
        if (PAD_DetectFold()) {
            return;
        }
        if (!PM_SetLCDPower(1)) {
            return;
        }
        gWifiSetupInput.lcdOff = 0;
    } else {
        if (!PAD_DetectFold()) {
            return;
        }
        if (PM_SetLCDPower(0)) {
            gWifiSetupInput.lcdOff = 1;
        }
    }
}

void WifiSetup_InstallVBlankIntr(void) {
    gWifiSetupIrqSave.mask = reg_OS_IE;
    OS_SetIrqMask(OS_IE_SPFIFO_RECV | OS_IE_TIMER1 | OS_IE_TIMER0);
    OS_EnableIrqMask(OS_IE_V_BLANK);
    gWifiSetupIrqSave.vblankFunc = OS_GetIrqFunction(OS_IE_V_BLANK);
    OS_SetIrqFunction(OS_IE_V_BLANK, WifiSetup_VBlankIntr);
    OS_ResetRequestIrqMask(OS_IE_V_BLANK);
    OS_EnableIrq();
    OS_EnableInterrupts();
}

void WifiSetup_RestoreVBlankIntr(void) {
    OS_DisableIrq();
    OS_SetIrqMask(gWifiSetupIrqSave.mask);
    OS_SetIrqFunction(OS_IE_V_BLANK, gWifiSetupIrqSave.vblankFunc);
}

// Runs the vblank task queue and sets the vblank bit of the interrupt check flags.
static void WifiSetup_VBlankIntr(void) {
    WifiSetupTask_RunQueue(WIFI_SETUP_TASK_QUEUE_VBLANK);
    OS_SetIrqCheckFlag(OS_IE_V_BLANK);
}

static WifiSetupList *WifiSetupList_New(void) {
    WifiSetupList *list = WifiSetupHeap_AllocZeroed(sizeof(WifiSetupList), 4);
    list->head.prev = NULL;
    list->head.next = &list->tail;
    list->tail.prev = &list->head;
    list->tail.next = NULL;
    return list;
}

static void WifiSetupList_Delete(WifiSetupList *list) {
    WifiSetupHeap_FreeAndClear(&list);
}

static void WifiSetupList_Remove(WifiSetupListNode *node) {
    int irq = OS_DisableIrqMask(OS_IE_V_BLANK);
    node->prev->next = node->next;
    node->next->prev = node->prev;
    node->next = NULL;
    node->prev = NULL;
    OS_EnableIrqMask(irq);
}

static void WifiSetupList_InsertBefore(WifiSetupListNode *pos, WifiSetupListNode *node) {
    int irq = OS_DisableIrqMask(OS_IE_V_BLANK);
    pos->prev->next = node;
    node->prev = pos->prev;
    node->next = pos;
    pos->prev = node;
    OS_EnableIrqMask(irq);
}

static void WifiSetupList_Append(WifiSetupList *list, WifiSetupListNode *node) {
    WifiSetupList_InsertBefore(&list->tail, node);
}

static void WifiSetupList_Prepend(WifiSetupList *list, WifiSetupListNode *node) {
    WifiSetupList_InsertBefore(list->head.next, node);
}

void WifiSetupOam_Init(void) {
    WifiSetupOamBuffer *buffer;
    int i;
    gWifiSetupOamBuffer = buffer = WifiSetupHeap_AllocZeroed(sizeof(WifiSetupOamBuffer), 4);
    MI_CpuFillFast(buffer, 0x200, sizeof(buffer->oam));
    for (i = 0; i < 2; i++) {
        gWifiSetupOamBuffer->pools[i] = WifiSetupPool_NewWithItems(0x40, gWifiSetupOamBuffer->oam[i], sizeof(GXOamAttr));
    }
    gWifiSetupOamBuffer->task = WifiSetupTask_Create(WIFI_SETUP_TASK_QUEUE_VBLANK, WifiSetupOam_TransferTask, NULL, 0xC8);
}

static void WifiSetupOam_TransferTask(WifiSetupTask *task, void *arg) {
    DC_FlushRange(gWifiSetupOamBuffer, sizeof(gWifiSetupOamBuffer->oam));
    GX_LoadOAM(gWifiSetupOamBuffer->oam[0], 0, sizeof(gWifiSetupOamBuffer->oam[0]));
    GXS_LoadOAM(gWifiSetupOamBuffer->oam[1], 0, sizeof(gWifiSetupOamBuffer->oam[1]));
}

void WifiSetupOam_Free(void) {
    WifiSetupTask_Destroy(WIFI_SETUP_TASK_QUEUE_VBLANK, gWifiSetupOamBuffer->task);
    WifiSetupHeap_FreeAndClear(MODULE_BSS_ADDR(0x0224F608));
}

static GXOamAttr *WifiSetupOam_Alloc(enum WifiSetupScreen screen) {
    return WifiSetupPool_Pop(gWifiSetupOamBuffer->pools[screen]);
}

void WifiSetupOam_Release(GXOamAttr *oam) {
    enum WifiSetupScreen screen;
    oam->attr01 = (oam->attr01 & 0xC1FFFCFF) | 0x200; // hide
    screen = WIFI_SETUP_SCREEN_MAIN;
    if (oam >= gWifiSetupOamBuffer->oam[WIFI_SETUP_SCREEN_SUB]) {
        screen = WIFI_SETUP_SCREEN_SUB;
    }
    WifiSetupPool_Push(gWifiSetupOamBuffer->pools[screen], oam);
}

static GXOamAttr *WifiSetupOam_Get(int screen, int index) {
    return &gWifiSetupOamBuffer->oam[screen][index];
}

void WifiSetupCharVram_Init(void) {
    int i;
    gWifiSetupCharVram = WifiSetupHeap_AllocZeroed(sizeof(WifiSetupCharVramManager) * 2, 4);
    for (i = 0; i < 2; i++) {
        gWifiSetupCharVram[i].pool = WifiSetupPool_NewWithItems(NELEMS(gWifiSetupCharVram[i].blocks), gWifiSetupCharVram[i].blocks, sizeof(WifiSetupCharBlock));
        gWifiSetupCharVram[i].list = WifiSetupList_New();
        gWifiSetupCharVram[i].first.start = 0x300;
        gWifiSetupCharVram[i].last.start = 0x400;
        WifiSetupList_Prepend(gWifiSetupCharVram[i].list, &gWifiSetupCharVram[i].first.node);
        WifiSetupList_Append(gWifiSetupCharVram[i].list, &gWifiSetupCharVram[i].last.node);
    }
}

// size in bytes; allocated in units of 4 (tile numbers 0x300-0x3FF are managed).
static WifiSetupCharBlock *WifiSetupCharVram_Alloc(enum WifiSetupScreen screen, int size, BOOL fromFront, u32 *outCharNo) {
    WifiSetupCharBlock *block;
    WifiSetupCharBlock *cur;
    int irq;
    int blockSize;

    block = WifiSetupPool_Pop(gWifiSetupCharVram[screen].pool);
    blockSize = ((size + 3) & ~3) >> 2;
    block->size = blockSize;
    irq = OS_DisableIrqMask(OS_IE_V_BLANK);
    if (fromFront) {
        cur = &gWifiSetupCharVram[screen].first;
        while (cur != &gWifiSetupCharVram[screen].last) {
            WifiSetupCharBlock *next = (WifiSetupCharBlock *)cur->node.next;
            int start = cur->start + cur->size;
            if (start + blockSize <= next->start) {
                block->start = start;
                WifiSetupList_InsertBefore(&next->node, &block->node);
                break;
            }
            cur = next;
        }
        if (cur == &gWifiSetupCharVram[screen].last) {
            OS_Terminate();
        }
    } else {
        cur = &gWifiSetupCharVram[screen].last;
        while (cur != &gWifiSetupCharVram[screen].first) {
            WifiSetupCharBlock *prev = (WifiSetupCharBlock *)cur->node.prev;
            int start = cur->start - blockSize;
            if (start >= prev->start + prev->size) {
                block->start = start;
                WifiSetupList_InsertBefore(&cur->node, &block->node);
                break;
            }
            cur = prev;
        }
        if (cur == &gWifiSetupCharVram[screen].first) {
            OS_Terminate();
        }
    }
    *outCharNo = block->start;
    OS_EnableIrqMask(irq);
    return block;
}

static void WifiSetupCharVram_Free(WifiSetupCharBlock *block) {
    int screen = 0;
    WifiSetupList_Remove(&block->node);
    if (block >= gWifiSetupCharVram[1].blocks) {
        screen = 1;
    }
    WifiSetupPool_Push(gWifiSetupCharVram[screen].pool, block);
}

int WifiSetup_StrNLen(const u8 *str, int max) {
    int i;
    for (i = 0; i < max; i++) {
        if (str[i] == 0) {
            break;
        }
    }
    return i;
}

void WifiSetup_SaveVramBanks(void) {
    gWifiSetupSavedVramBanks.bg = GX_DisableBankForBG();
    gWifiSetupSavedVramBanks.obj = GX_DisableBankForOBJ();
    gWifiSetupSavedVramBanks.bgExtPltt = GX_DisableBankForBGExtPltt();
    gWifiSetupSavedVramBanks.objExtPltt = GX_DisableBankForOBJExtPltt();
    gWifiSetupSavedVramBanks.tex = GX_DisableBankForTex();
    gWifiSetupSavedVramBanks.texPltt = GX_DisableBankForTexPltt();
    gWifiSetupSavedVramBanks.clearImage = GX_DisableBankForClearImage();
    gWifiSetupSavedVramBanks.subBg = GX_DisableBankForSubBG();
    gWifiSetupSavedVramBanks.subObj = GX_DisableBankForSubOBJ();
    gWifiSetupSavedVramBanks.subBgExtPltt = GX_DisableBankForSubBGExtPltt();
    gWifiSetupSavedVramBanks.subObjExtPltt = GX_DisableBankForSubOBJExtPltt();
    gWifiSetupSavedVramBanks.arm7 = GX_DisableBankForARM7();
    gWifiSetupSavedVramBanks.lcdc = GX_DisableBankForLCDC();
    GX_SetBankForARM7(gWifiSetupSavedVramBanks.arm7);
    WifiSetup_ClearVram();
}

void WifiSetup_RestoreVramBanks(void) {
    OSIntrMode irq;
    GX_DisableBankForBG();
    GX_DisableBankForOBJ();
    GX_DisableBankForSubBG();
    GX_DisableBankForSubOBJ();
    WifiSetup_ClearVram();
    GX_SetBankForBG(gWifiSetupSavedVramBanks.bg);
    GX_SetBankForOBJ(gWifiSetupSavedVramBanks.obj);
    GX_SetBankForBGExtPltt(gWifiSetupSavedVramBanks.bgExtPltt);
    GX_SetBankForOBJExtPltt(gWifiSetupSavedVramBanks.objExtPltt);
    GX_SetBankForTex(gWifiSetupSavedVramBanks.tex);
    GX_SetBankForTexPltt(gWifiSetupSavedVramBanks.texPltt);
    GX_SetBankForClearImage(gWifiSetupSavedVramBanks.clearImage);
    GX_SetBankForSubBG(gWifiSetupSavedVramBanks.subBg);
    GX_SetBankForSubOBJ(gWifiSetupSavedVramBanks.subObj);
    GX_SetBankForSubBGExtPltt(gWifiSetupSavedVramBanks.subBgExtPltt);
    GX_SetBankForSubOBJExtPltt(gWifiSetupSavedVramBanks.subObjExtPltt);
    GX_SetBankForLCDC(gWifiSetupSavedVramBanks.lcdc);
    G2_BlendNone();
    G2S_BlendNone();
    G2_SetBG0Offset(0, 0);
    G2_SetBG1Offset(0, 0);
    G2_SetBG2Offset(0, 0);
    G2_SetBG3Offset(0, 0);
    G2S_SetBG0Offset(0, 0);
    G2S_SetBG1Offset(0, 0);
    G2S_SetBG2Offset(0, 0);
    G2S_SetBG3Offset(0, 0);
    irq = OS_DisableInterrupts();
    PM_SetLCDPower(1);
    OS_RestoreInterrupts(irq);
}

static void WifiSetup_ClearVram(void) {
    GX_SetBankForLCDC((GXVRamLCDC)(GX_VRAM_LCDC_A | GX_VRAM_LCDC_B | GX_VRAM_LCDC_E | GX_VRAM_LCDC_F | GX_VRAM_LCDC_G | GX_VRAM_LCDC_H | GX_VRAM_LCDC_I));
    MIi_CpuClearFast(0, (void *)HW_LCDC_VRAM, 0x40000);
    MIi_CpuClearFast(0, (void *)(HW_LCDC_VRAM + 0x80000), 0x24000);
    GX_DisableBankForLCDC();
    MIi_CpuClearFast(0x200, (void *)HW_OAM, HW_OAM_SIZE);
    MIi_CpuClearFast(0, (void *)HW_PLTT, HW_PLTT_SIZE);
    MIi_CpuClearFast(0x200, (void *)HW_DB_OAM, HW_DB_OAM_SIZE);
    MIi_CpuClearFast(0, (void *)HW_DB_PLTT, HW_DB_PLTT_SIZE);
}

void WifiSetupLed_SetWirelessPattern(void) {
    u32 pattern;
    if (PM_GetLEDPattern(&pattern) != 0) {
        return;
    }
    if (pattern == 0xF) {
        return;
    }
    PMi_SendLEDPatternCommand(0xF);
}

void WifiSetupLed_SetOn(void) {
    PMi_SendLEDPatternCommand(1);
}

void WifiSetupTask_InitScheduler(void) {
    int i;
    u8 *capacity;
    gWifiSetupTaskQueues = WifiSetupHeap_AllocZeroed(sizeof(WifiSetupTaskQueue) * 2, 4);
    capacity = gWifiSetupTaskQueueCapacities;
    for (i = 0; i < 2; i++) {
        gWifiSetupTaskQueues[i].capacity = *capacity;
        gWifiSetupTaskQueues[i].taskBuf = WifiSetupHeap_AllocZeroed(*capacity * sizeof(WifiSetupTask), 4);
        gWifiSetupTaskQueues[i].taskPool = WifiSetupPool_NewWithItems(*capacity, gWifiSetupTaskQueues[i].taskBuf, sizeof(WifiSetupTask));
        gWifiSetupTaskQueues[i].destroyQueue = WifiSetupPool_New(*capacity++);
        gWifiSetupTaskQueues[i].list = WifiSetupList_New();
        gWifiSetupTaskQueues[i].head.priority = 0;
        gWifiSetupTaskQueues[i].tail.priority = 0xFF;
        WifiSetupList_Prepend(gWifiSetupTaskQueues[i].list, &gWifiSetupTaskQueues[i].head.node);
        WifiSetupList_Append(gWifiSetupTaskQueues[i].list, &gWifiSetupTaskQueues[i].tail.node);
        gWifiSetupTaskQueues[i].enabled = 1;
    }
}

void WifiSetupTask_FreeScheduler(void) {
    int i;
    for (i = 0; i < 2; i++) {
        WifiSetupList_Delete(gWifiSetupTaskQueues[i].list);
        WifiSetupPool_Delete(gWifiSetupTaskQueues[i].taskPool);
    }
    WifiSetupHeap_FreeAndClear(MODULE_BSS_ADDR(0x0224F644));
}

// Runs every task of the queue in priority order, then destroys the tasks queued for destruction.
void WifiSetupTask_RunQueue(enum WifiSetupTaskQueueId queue) {
    WifiSetupTask *task;
    int i;
    if (!gWifiSetupTaskQueues[queue].enabled) {
        return;
    }
    for (task = (WifiSetupTask *)gWifiSetupTaskQueues[queue].head.node.next; task != &gWifiSetupTaskQueues[queue].tail; task = (WifiSetupTask *)task->node.next) {
        task->func(task, task->arg);
    }
    for (i = 0; i < gWifiSetupTaskQueues[queue].capacity; i++) {
        task = WifiSetupPool_Pop(gWifiSetupTaskQueues[queue].destroyQueue);
        if (task == NULL) {
            return;
        }
        WifiSetupTask_DestroyNow(queue, task);
    }
}

WifiSetupTask *WifiSetupTask_Create(enum WifiSetupTaskQueueId queue, WifiSetupTaskFunc func, void *arg, u32 priority) {
    return WifiSetupTask_CreateEx(queue, func, arg, priority, 0);
}

static WifiSetupTask *WifiSetupTask_CreateEx(enum WifiSetupTaskQueueId queue, WifiSetupTaskFunc func, void *arg, u32 priority, u8 ownsArg) {
    WifiSetupTask *task;
    WifiSetupTask *cur;
    int irq;
    task = WifiSetupPool_Pop(gWifiSetupTaskQueues[queue].taskPool);
    task->func = func;
    task->arg = arg;
    task->priority = priority;
    task->ownsArg = ownsArg;
    irq = OS_DisableIrqMask(OS_IE_V_BLANK);
    for (cur = (WifiSetupTask *)gWifiSetupTaskQueues[queue].head.node.next;; cur = (WifiSetupTask *)cur->node.next) {
        if (priority < cur->priority) {
            WifiSetupList_InsertBefore(&cur->node, &task->node);
            break;
        }
    }
    OS_EnableIrqMask(irq);
    return task;
}

void WifiSetupTask_SetFunc(WifiSetupTask *task, WifiSetupTaskFunc func) {
    task->func = func;
}

void WifiSetupTask_DestroyLater(enum WifiSetupTaskQueueId queue, WifiSetupTask *task) {
    WifiSetupPool_Push(gWifiSetupTaskQueues[queue].destroyQueue, task);
}

void WifiSetupTask_Destroy(enum WifiSetupTaskQueueId queue, WifiSetupTask *task) {
    WifiSetupTask_DestroyNow(queue, task);
}

static void WifiSetupTask_DestroyNow(enum WifiSetupTaskQueueId queue, WifiSetupTask *task) {
    if (task->ownsArg) {
        WifiSetupHeap_FreeAndClear(&task->arg);
    }
    WifiSetupList_Remove(&task->node);
    WifiSetupPool_Push(gWifiSetupTaskQueues[queue].taskPool, task);
}

void WifiSetupTask_SetQueueEnabled(enum WifiSetupTaskQueueId queue, u8 enabled) {
    gWifiSetupTaskQueues[queue].enabled = enabled;
}
