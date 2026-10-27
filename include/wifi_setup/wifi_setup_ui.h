#ifndef POKEHEARTGOLD_WIFI_SETUP_UI_H
#define POKEHEARTGOLD_WIFI_SETUP_UI_H

#include "global.h"

#include <nnsys/g2d_canvas_internal.h>

// UI framework of the access-point setup screens: heap, files, lists and pools, OAM and VRAM allocators, fades,
// text canvases, input and a prioritised task scheduler.

// Screen argument of the display, text, OAM and fade helpers
enum WifiSetupScreen {
    WIFI_SETUP_SCREEN_MAIN,
    WIFI_SETUP_SCREEN_SUB,
};

// Fades started by WifiSetupFade_Start (see gWifiSetupFadeTables)
enum WifiSetupFadeKind {
    WIFI_SETUP_FADE_IN_FROM_BLACK,
    WIFI_SETUP_FADE_OUT_TO_BLACK,
    WIFI_SETUP_FADE_IN_FROM_WHITE,
    WIFI_SETUP_FADE_OUT_TO_WHITE,
};

// Direction of a cursor move on the setup screens
enum WifiSetupCursorDirection {
    WIFI_SETUP_CURSOR_LEFT,
    WIFI_SETUP_CURSOR_UP,
    WIFI_SETUP_CURSOR_RIGHT,
    WIFI_SETUP_CURSOR_DOWN,
};

// Display windows (WifiSetupDisplay_SetWindowRect / _SetWindowPlanes)
enum WifiSetupWindow {
    WIFI_SETUP_WINDOW_0,
    WIFI_SETUP_WINDOW_1,
    WIFI_SETUP_WINDOW_OBJ,
    WIFI_SETUP_WINDOW_OUTSIDE, // outside all windows
};

// Selection of the button bar and of the dialog besides a button index
#define WIFI_SETUP_SELECTED_NONE      (-1)
#define WIFI_SETUP_SELECTED_NOT_SHOWN (-2) // still sliding in

// Font character drawn in place of a space in the text typed on the setup screens
#define WIFI_SETUP_CHAR_SPACE_MARK 0xE01D

typedef struct WifiSetupListNode {
    struct WifiSetupListNode *prev;
    struct WifiSetupListNode *next;
} WifiSetupListNode;

// Doubly linked list with sentinel head and tail nodes.
typedef struct WifiSetupList {
    WifiSetupListNode head;
    WifiSetupListNode tail;
} WifiSetupList;

// Ring buffer of free items: WifiSetupPool_Pop hands one out, WifiSetupPool_Push returns it.
typedef struct WifiSetupPool {
    u16 size;
    u8 head;
    u8 tail;
    void *items[1];
} WifiSetupPool;

// A run of consecutive OAM entries, kept sorted in a list per screen.
typedef struct WifiSetupOamBlock {
    WifiSetupListNode node;
    GXOamAttr *oam;
    u8 count;
} WifiSetupOamBlock;

typedef struct WifiSetupPoint {
    u16 x;
    u16 y;
} WifiSetupPoint;

typedef struct WifiSetupRect {
    u16 left;
    u16 top;
    u16 right;
    u16 bottom;
} WifiSetupRect;

// Area of a text drawn by WifiSetupText_DrawInRect.
typedef struct WifiSetupTextBox {
    u16 x;
    u16 y;
    u16 width;
    u16 height;
} WifiSetupTextBox;

// Copies of path strings (the path is localised in place).
typedef struct WifiSetupPath21 {
    char text[21];
} WifiSetupPath21;

typedef struct WifiSetupPath22 {
    char text[22];
} WifiSetupPath22;

typedef struct WifiSetupPath23 {
    char text[23];
} WifiSetupPath23;

typedef struct WifiSetupPath25 {
    char text[25];
} WifiSetupPath25;

// Position of a key row of the software keyboard or the numeric keypad while it slides in or out.
typedef struct WifiSetupKeyRowPosition {
    int y;
    int x;
} WifiSetupKeyRowPosition;

// Number of keys of one kind in each of the five rows of the keyboard or keypad (row 4: buttons).
typedef struct WifiSetupKeyRowCounts {
    u8 counts[5];
} WifiSetupKeyRowCounts;

// Task queues: the main queue runs once per frame in the main loop, the vblank queue in the vblank interrupt.
enum WifiSetupTaskQueueId {
    WIFI_SETUP_TASK_QUEUE_MAIN,
    WIFI_SETUP_TASK_QUEUE_VBLANK,
};

typedef struct WifiSetupTask WifiSetupTask;

typedef void (*WifiSetupTaskFunc)(WifiSetupTask *task, void *arg);

struct WifiSetupTask {
    WifiSetupListNode node;
    WifiSetupTaskFunc func;
    void *arg;
    u8 priority;
    u8 ownsArg; // arg is freed together with the task
};

// Character canvas (BG screen or OBJ) with the text canvas drawing into it.
typedef struct WifiSetupCanvas {
    G2dCharCanvas charCanvas;
    G2dTextCanvas textCanvas;
    void *charBuf; // BG: character buffer; OBJ: character VRAM block

    union {
        WifiSetupTask *task; // BG: transfer task

        struct {
            u16 charNo;
            u8 width;
            u8 height;
        } obj;
    } u;
} WifiSetupCanvas;

// The "rom:/dwc/utility.bin" archive (WifiSetupArchive_Load).
typedef struct WifiSetupArchiveState {
    void *tables;       // FS archive tables
    u8 poolItems[0x80]; // items of filePool
    WifiSetupPool *filePool;
    FSArchive arc;
    u8 unk_88[0xE4 - 0x88 - sizeof(FSArchive)];
    u16 lockId;
} WifiSetupArchiveState;

typedef struct WifiSetupOamBlockManager {
    WifiSetupOamBlock blocks[32];
    WifiSetupOamBlock first;
    WifiSetupOamBlock last;
    WifiSetupList *list;
    WifiSetupPool *pool;
} WifiSetupOamBlockManager;

// Header of one template in an OAM template file: count entries of 6 bytes at data + offset.
typedef struct WifiSetupOamTemplateHeader {
    u16 count;
    u16 unk_02;
    u32 offset;
} WifiSetupOamTemplateHeader;

typedef struct WifiSetupFade {
    WifiSetupTask *task;
    s16 counter;
    u16 duration;
    u8 kind;
    u8 active;
} WifiSetupFade;

typedef struct WifiSetupBrightnessTable {
    s8 values[4];
} WifiSetupBrightnessTable;

typedef struct WifiSetupTextState {
    G2dFont fonts[2];
    WifiSetupCanvas objCanvases[32];
    WifiSetupCanvas bgCanvases[2];
    WifiSetupPool *objCanvasPool;
    void *fontData[2];
    u8 bgDirty[2];
} WifiSetupTextState;

typedef struct WifiSetupOamBuffer {
    GXOamAttr oam[2][128];
    WifiSetupPool *pools[2];
    WifiSetupTask *task;
} WifiSetupOamBuffer;

typedef struct WifiSetupCharBlock {
    WifiSetupListNode node;
    u16 start;
    u16 size;
} WifiSetupCharBlock;

typedef struct WifiSetupCharVramManager {
    WifiSetupCharBlock blocks[32];
    WifiSetupCharBlock first;
    WifiSetupCharBlock last;
    WifiSetupList *list;
    WifiSetupPool *pool;
} WifiSetupCharVramManager;

typedef struct WifiSetupVramBanks {
    GXVRamBG bg;
    GXVRamOBJ obj;
    GXVRamBGExtPltt bgExtPltt;
    GXVRamOBJExtPltt objExtPltt;
    GXVRamTex tex;
    GXVRamTexPltt texPltt;
    GXVRamClearImage clearImage;
    GXVRamSubBG subBg;
    GXVRamSubOBJ subObj;
    GXVRamSubBGExtPltt subBgExtPltt;
    GXVRamSubOBJExtPltt subObjExtPltt;
    int arm7;
    GXVRamLCDC lcdc;
} WifiSetupVramBanks;

typedef struct WifiSetupTaskQueue {
    WifiSetupPool *taskPool;
    WifiSetupPool *destroyQueue;
    WifiSetupList *list;
    WifiSetupTask head;
    WifiSetupTask tail;
    int capacity;
    u8 enabled;
    WifiSetupTask *taskBuf;
} WifiSetupTaskQueue;

typedef struct WifiSetupInputState {
    TPData samples[5];
    WifiSetupPoint touch;
    WifiSetupPoint prevTouch;
    u16 cont;
    u16 trig;
    u16 repeat;
    u16 release;
    u8 touching : 1;
    u8 touchTrig : 1;
    u8 touchRepeat : 1;
    u8 touchRelease : 1;
} WifiSetupInputState;

typedef struct WifiSetupInput {
    u8 lcdOff;
    u8 touchHoldFrames;
    u8 unk_02[2];
    WifiSetupInputState *state;
} WifiSetupInput;

typedef struct WifiSetupIrqSave {
    OSIrqFunction vblankFunc;
    OSIrqMask mask;
} WifiSetupIrqSave;

extern WifiSetupArchiveState *gWifiSetupArchive;
extern WifiSetupOamBlockManager *gWifiSetupOamBlockManager;
extern WifiSetupOamTemplateHeader *gWifiSetupOamTemplateFiles[];
extern WifiSetupFade *gWifiSetupFades;
extern WifiSetupTextState *gWifiSetupText;
extern NNSFndHeapHandle gWifiSetupHeap;
extern WifiSetupInput gWifiSetupInput;
extern u8 gWifiSetupInputHoldFrames[];
extern WifiSetupIrqSave gWifiSetupIrqSave;
extern WifiSetupOamBuffer *gWifiSetupOamBuffer;
extern WifiSetupCharVramManager *gWifiSetupCharVram;
extern WifiSetupVramBanks gWifiSetupSavedVramBanks;
extern WifiSetupTaskQueue *gWifiSetupTaskQueues;
extern WifiSetupBrightnessTable gWifiSetupFadeTables[3]; // end, flags and start values per fade kind
extern const u16 gWifiSetupTextScreenCharBases[];
extern const u16 gWifiSetupTextScreenWidths[];
extern const u16 gWifiSetupTextScreenHeights[];
extern u8 gWifiSetupTaskQueueCapacities[];
extern char gWifiSetupRomPrefix[];
extern char gWifiSetupCompressedSuffix[];
extern char *gWifiSetupFontPathsKorean[];
extern char *gWifiSetupFontPaths[];

void WifiSetupArchive_Load(void);
void WifiSetupArchive_Unload(void);
FSResult WifiSetupArchive_Proc(FSFile *file, FSCommandType command);
FSResult WifiSetupArchive_Read(FSArchive *arc, void *dst, u32 pos, u32 len);
FSResult WifiSetupArchive_Write(FSArchive *arc, const void *src, u32 pos, u32 len);
void *WifiSetupFile_Load(const char *path, u32 *outSize, int align);
void WifiSetupFile_Free(void *data);

void WifiSetupOamBlock_InitManager(void);
void WifiSetupOamBlock_FreeManager(void);
WifiSetupOamBlock *WifiSetupOamBlock_Alloc(enum WifiSetupScreen screen, int count, BOOL fromFront);
void WifiSetupOamBlock_Free(WifiSetupOamBlock *block);
GXOamAttr *WifiSetupOamBlock_GetOam(WifiSetupOamBlock *block, int index);
u8 WifiSetupOamBlock_GetCount(WifiSetupOamBlock *block);
void WifiSetupOamBlock_SetAffineMode(WifiSetupOamBlock *block, int index, u32 mode, u32 param);
void WifiSetupOamBlock_SetModeAndPalette(WifiSetupOamBlock *block, int index, u32 mode, u32 palette);
void WifiSetupOamBlock_SetPosition(WifiSetupOamBlock *block, int index, int x, int y);
void WifiSetupOamBlock_SetPriority(WifiSetupOamBlock *block, int index, u32 priority);
void WifiSetupOamBlock_GetPosition(WifiSetupOamBlock *block, int index, int *x, int *y);

void WifiSetupOamTemplate_Load(enum WifiSetupScreen screen, const char *path);
void WifiSetupOamTemplate_Free(enum WifiSetupScreen screen);
void WifiSetupOamTemplate_Copy(enum WifiSetupScreen screen, int index, GXOamAttr *dst);
GXOamAttr *WifiSetupOamTemplate_AllocOam(enum WifiSetupScreen screen, int index);
WifiSetupOamBlock *WifiSetupOamTemplate_AllocBlock(enum WifiSetupScreen screen, int index, BOOL fromFront);

WifiSetupPool *WifiSetupPool_NewWithItems(int count, void *items, int stride);
void *WifiSetupPool_Push(WifiSetupPool *pool, void *item);
void *WifiSetupPool_Pop(WifiSetupPool *pool);

void WifiSetupFade_Init(void);
void WifiSetupFade_Free(void);
u8 WifiSetupFade_IsActive(enum WifiSetupScreen screen);
BOOL WifiSetupFade_Start(enum WifiSetupFadeKind kind, enum WifiSetupScreen screen, int planes, int duration);
BOOL WifiSetupFade_StartDelay(int duration);

void WifiSetupText_Init(void);
void WifiSetupText_Free(void);
WifiSetupCanvas *WifiSetupText_AllocObjCanvas(enum WifiSetupScreen screen, int width, int height, BOOL fromFront, u32 *numObjs, int font);
void WifiSetupText_FreeObjCanvas(WifiSetupCanvas *canvas);
void WifiSetupText_FreeCanvas(WifiSetupCanvas *canvas);
WifiSetupCanvas *WifiSetupText_InitBgCanvas(enum WifiSetupScreen screen, int font);
void WifiSetupText_FreeBgCanvas(enum WifiSetupScreen screen);
void WifiSetupText_Draw(WifiSetupCanvas *canvas, int x, int y, int color, u32 flags, const u16 *text);
void WifiSetupText_DrawMonospace(WifiSetupCanvas *canvas, int x, int y, int color, int advance, const u16 *text, int font);
void WifiSetupText_DrawInRect(WifiSetupCanvas *canvas, int x, int y, int width, int height, int color, u32 flags, const u16 *text);
void WifiSetupText_Clear(WifiSetupCanvas *canvas, int color);
void WifiSetupText_ShowObjCanvas(WifiSetupCanvas *canvas, int x, int y, WifiSetupOamBlock *block, u32 priority);
void WifiSetupText_MarkDirty(WifiSetupCanvas *canvas);

void WifiSetup_SetPoint(u16 x, u16 y, WifiSetupPoint *point);
void WifiSetup_SetRect(int left, int top, int right, int bottom, WifiSetupRect *rect);
void WifiSetup_RectFromPosSize(const WifiSetupPoint *pos, const WifiSetupPoint *size, WifiSetupRect *rect);
void WifiSetupDisplay_ShowPlanes(enum WifiSetupScreen screen, int planes);
void WifiSetupDisplay_HidePlanes(enum WifiSetupScreen screen, int planes);
void WifiSetupDisplay_SetWindowRect(enum WifiSetupScreen screen, enum WifiSetupWindow window, WifiSetupRect *rect);
void WifiSetupDisplay_SetWindowPlanes(enum WifiSetupScreen screen, enum WifiSetupWindow window, int planes, BOOL effect);

void WifiSetupHeap_Init(void *mem);
void WifiSetupHeap_Destroy(void);
void *WifiSetupHeap_AllocZeroed(u32 size, int align);
void WifiSetupHeap_FreeAndClear(void *ptr);
void WifiSetupHeap_Free(void *mem);

void WifiSetupInput_Init(void);
void WifiSetupInput_Free(void);
void WifiSetupInput_Update(void);
BOOL WifiSetupInput_IsKeyPressed(u16 mask);
BOOL WifiSetupInput_IsKeyRepeated(u16 mask);
BOOL WifiSetupInput_IsKeyReleased(u16 mask);
BOOL WifiSetupInput_IsTouchHeld(WifiSetupRect *rect);
BOOL WifiSetupInput_IsTouchPressed(WifiSetupRect *rect);
BOOL WifiSetupInput_IsTouchRepeated(WifiSetupRect *rect);
BOOL WifiSetupInput_IsTouchReleased(WifiSetupRect *rect);
BOOL WifiSetupInput_IsTouchPressedInBox(WifiSetupRect *box);
BOOL WifiSetupInput_GetTouchPos(WifiSetupPoint *out);
void WifiSetupInput_UpdateLcdPower(void);

void WifiSetup_InstallVBlankIntr(void);
void WifiSetup_RestoreVBlankIntr(void);

void WifiSetupOam_Init(void);
void WifiSetupOam_Free(void);
void WifiSetupOam_Release(GXOamAttr *oam);

void WifiSetupCharVram_Init(void);

int WifiSetup_StrNLen(const u8 *str, int max);
void WifiSetup_SaveVramBanks(void);
void WifiSetup_RestoreVramBanks(void);
void WifiSetupLed_SetWirelessPattern(void);
void WifiSetupLed_SetOn(void);

void WifiSetupTask_InitScheduler(void);
void WifiSetupTask_FreeScheduler(void);
void WifiSetupTask_RunQueue(enum WifiSetupTaskQueueId queue);
WifiSetupTask *WifiSetupTask_Create(enum WifiSetupTaskQueueId queue, WifiSetupTaskFunc func, void *arg, u32 priority);
void WifiSetupTask_SetFunc(WifiSetupTask *task, WifiSetupTaskFunc func);
void WifiSetupTask_DestroyLater(enum WifiSetupTaskQueueId queue, WifiSetupTask *task);
void WifiSetupTask_Destroy(enum WifiSetupTaskQueueId queue, WifiSetupTask *task);
void WifiSetupTask_SetQueueEnabled(enum WifiSetupTaskQueueId queue, u8 enabled);

#endif // POKEHEARTGOLD_WIFI_SETUP_UI_H
