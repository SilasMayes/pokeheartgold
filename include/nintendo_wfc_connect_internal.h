#ifndef POKEHEARTGOLD_NINTENDO_WFC_CONNECT_INTERNAL_H
#define POKEHEARTGOLD_NINTENDO_WFC_CONNECT_INTERNAL_H

#include "global.h"

#include "bg_window.h"
#include "frontier_data_access.h"
#include "frontier_wifi_upload_record.h"
#include "gf_gfx_planes.h"
#include "heap.h"
#include "obj_char_transfer.h"
#include "save_wii_message.h"
#include "sprite.h"
#include "touchscreen.h"

// NintendoWifiConnectArgs.mode
enum NintendoWfcMode {
    NINTENDO_WFC_MODE_DOWNLOAD_ROOM,
    NINTENDO_WFC_MODE_UPLOAD_RECORD,
    NINTENDO_WFC_MODE_CHECK_LEADERS,
};

// Text alignment of the aligned text printers: the given x, centered or right-aligned
enum NintendoWfcTextAlign {
    NINTENDO_WFC_ALIGN_X,
    NINTENDO_WFC_ALIGN_CENTER,
    NINTENDO_WFC_ALIGN_RIGHT,
};

enum NintendoWfcPaletteScreens {
    NINTENDO_WFC_PALETTE_BOTH_SCREENS,
    NINTENDO_WFC_PALETTE_MAIN_SCREEN,
    NINTENDO_WFC_PALETTE_SUB_SCREEN,
};

enum NintendoWfcInitState {
    NINTENDO_WFC_INIT_SETUP,
    NINTENDO_WFC_INIT_START_WIRELESS,
};

enum NintendoWfcDisconnectStep {
    NINTENDO_WFC_DISCONNECT_PRINT,
    NINTENDO_WFC_DISCONNECT_CLEANUP,
    NINTENDO_WFC_DISCONNECT_PRINT_DONE,
    NINTENDO_WFC_DISCONNECT_WAIT_PRINT,
};

enum NintendoWfcMainState {
    NINTENDO_WFC_MAIN_WAIT_STARTUP,
    NINTENDO_WFC_MAIN_SESSION_INIT,
    NINTENDO_WFC_MAIN_WAIT_FADE_IN,
    NINTENDO_WFC_MAIN_SESSION_MAIN,
    NINTENDO_WFC_MAIN_SESSION_EXIT,
    NINTENDO_WFC_MAIN_DONE,
};

// Background palette cycling (VBlank task): three blends of 7 steps each between consecutive base palettes,
// played forwards and backwards.
#define NINTENDO_WFC_PALETTE_CYCLE_STEPS 21

typedef struct NintendoWfcPaletteCycle {
    SysTask *task;
    BOOL active;
    u16 basePltt[64];
    u16 cyclePltt[NINTENDO_WFC_PALETTE_CYCLE_STEPS * 16];
    s16 index;
    s8 direction;
    u8 tick;
    u32 screens; // 0: both, 1: main only, 2: sub only
} NintendoWfcPaletteCycle;

// Touch YES/NO menu on the sub screen.
typedef struct NintendoWfcYesNoMenu {
    BgConfig *bgConfig;
    Sprite *cursorSprite;
    Window yesWindow;
    Window noWindow;
    enum HeapID heapID;
    u8 initialChoice;
    u8 state; // index into gNintendoWfcYesNoStates
    u8 bgPltt;
    u8 bgLayer;
    u8 fontPltt;
    u8 baseTile;
    u8 textBgLayer;
    u8 choice; // 0: yes, 1: no
    int cursorOffsetY;
} NintendoWfcYesNoMenu;

typedef struct NintendoWfcConnect NintendoWfcConnect;

enum NintendoWfcHttpState {
    NINTENDO_WFC_HTTP_NONE,
    NINTENDO_WFC_HTTP_IDLE,
    NINTENDO_WFC_HTTP_ROOM_COUNT,
    NINTENDO_WFC_HTTP_DOWNLOAD = 4,
    NINTENDO_WFC_HTTP_UPLOAD = 6,
    NINTENDO_WFC_HTTP_INFO = 8,
    NINTENDO_WFC_HTTP_SET_PROFILE = 10,
    NINTENDO_WFC_HTTP_DONE = 12,
};

#define NINTENDO_WFC_DOWNLOAD_SIZE       0xA38 // a room's trainers and leaders
#define NINTENDO_WFC_HTTP_TIMEOUT_FRAMES 3600  // frames to wait for a request before the restart error

// Status byte at the start of a Battle Tower server response.
enum NintendoWfcServerStatus {
    NINTENDO_WFC_SERVER_OK = 1,
    NINTENDO_WFC_SERVER_BAD_ROOM,
    NINTENDO_WFC_SERVER_MAINTENANCE,
    NINTENDO_WFC_SERVER_CROWDED,
    NINTENDO_WFC_SERVER_ERROR,
};

// NintendoWfcHttp_GetResult; a room count request gives the room count instead of OK.
enum NintendoWfcHttpResult {
    NINTENDO_WFC_HTTP_RESULT_DISCONNECTED = -7,
    NINTENDO_WFC_HTTP_RESULT_NOT_CONNECTED,
    NINTENDO_WFC_HTTP_RESULT_FATAL, // shows the restart error
    NINTENDO_WFC_HTTP_RESULT_CANCELED,
    NINTENDO_WFC_HTTP_RESULT_BAD_ROOM,
    NINTENDO_WFC_HTTP_RESULT_SERVER_ERROR,
    NINTENDO_WFC_HTTP_RESULT_UPLOAD_CROWDED,
    NINTENDO_WFC_HTTP_RESULT_OK,
    NINTENDO_WFC_HTTP_RESULT_MAINTENANCE,
    NINTENDO_WFC_HTTP_RESULT_CROWDED,
};

typedef struct NintendoWfcHttpResponse {
    u8 unk_0[3];
    volatile u8 status; // first byte of the response buffer gNintendoWfcHttpShortResponse
    u32 unk_4;
    u8 *buffer;
} NintendoWfcHttpResponse;

// The HTTP request state of the Wi-Fi Battle Tower (gamestats) requests. On the DS the request and
// response buffers are the labels after gNintendoWfcHttp (gNintendoWfcHttpFriendKey is its friendKey,
// gNintendoWfcHttpRequestBuffer starts at rank); the port has them all in this one object.
typedef struct NintendoWfcHttp {
    volatile s32 state; // enum NintendoWfcHttpState
    s32 result; // enum NintendoWfcHttpResult
    u32 profileId;
    u64 friendKey;
#ifdef SDK_PORT
    union {
        struct {
            u8 rank;
            u8 room;
        };
        u8 requestBuffer[0xEF]; // the longest request: an upload record, rank, room, wins, friend key
    };
    NintendoWfcHttpResponse response;
#else
    u8 rank; // first byte of the request buffer gNintendoWfcHttpRequestBuffer
    u8 room;
#endif
} NintendoWfcHttp;

typedef struct NintendoWfcGlobal {
    NNSFndHeapHandle heap; // heap of the DWC allocator callbacks
    NintendoWfcConnect *wfc;
    u8 unk_8[0xC];
} NintendoWfcGlobal;

typedef enum NintendoWfcMainState (*NintendoWfcScreenFunc)(NintendoWfcConnect *wfc, int state);

// The init, main and exit functions of each screen.
typedef struct NintendoWfcScreenFuncs {
    NintendoWfcScreenFunc init;
    NintendoWfcScreenFunc main;
    NintendoWfcScreenFunc exit;
} NintendoWfcScreenFuncs;

typedef struct NintendoWfcPadKeyFlash {
    u8 x;
    u8 y;
} NintendoWfcPadKeyFlash;

// cursor x/y of the touch YES/NO menu per choice
typedef struct NintendoWfcCursorPos {
    u16 x;
    u16 y;
} NintendoWfcCursorPos;

extern NintendoWfcHttp gNintendoWfcHttp;
#ifdef SDK_PORT
#define gNintendoWfcHttpFriendKey     ((u8 *)&gNintendoWfcHttp.friendKey)
#define gNintendoWfcHttpRequestBuffer (gNintendoWfcHttp.requestBuffer)
#define ov72_0223B900                 (gNintendoWfcHttp.requestBuffer + 0xCC)
#define gNintendoWfcHttpResponse      (gNintendoWfcHttp.response)
#define gNintendoWfcHttpShortResponse ((u8 *)&gNintendoWfcHttp.response.status) // 2 bytes: status, unk_4
#else
extern u8 gNintendoWfcHttpFriendKey[];
extern u8 gNintendoWfcHttpRequestBuffer[];
extern u8 ov72_0223B900[];
extern NintendoWfcHttpResponse gNintendoWfcHttpResponse; // 0xEC bytes into the request buffer
extern u8 gNintendoWfcHttpShortResponse[];
#endif
// Inside ov72_0223B900 (src/data/nintendo_wfc_connect_data_3.c): MWCC cannot lay it out as an object of
// its own where the ROM has it.
#define gNintendoWfcHttpUploadFriendKey (ov72_0223B900 + 0x1B)
extern NintendoWfcGlobal gNintendoWfcGlobal;
extern const char gNintendoWfcRoomNumUrl[];
extern const char gNintendoWfcDownloadUrl[];
extern const char gNintendoWfcUploadUrl[];
extern const char gNintendoWfcInfoUrl[];
extern const char gNintendoWfcSetProfileUrl[];
extern const NintendoWfcScreenFuncs gNintendoWfcScreens[];
extern enum NintendoWfcMainState (*const gNintendoWfcStates[])(NintendoWfcConnect *wfc);
extern BOOL (*const gNintendoWfcNumberInputStates[])(NintendoWfcConnect *wfc);
extern BOOL (*const gNintendoWfcYesNoStates[])(NintendoWfcYesNoMenu *menu);
extern const ObjCharTransferTemplate gNintendoWfcObjCharTransferTemplate;
extern const GraphicsModes gNintendoWfcGraphicsModes;
extern const GraphicsBanks gNintendoWfcGraphicsBanks;
extern const BgTemplate gNintendoWfcBgTemplate_Sub1;
extern const BgTemplate gNintendoWfcBgTemplate_Sub2;
extern const BgTemplate gNintendoWfcBgTemplate_Main1;
extern const BgTemplate gNintendoWfcBgTemplate_Main0;
extern const BgTemplate gNintendoWfcBgTemplate_Sub0;
extern const u16 gNintendoWfcButtonSpritePositions[][2];
extern const u16 gNintendoWfcDigitSpritePositions[][3][2];
extern const u16 gNintendoWfcPadCursorPositions[][2];
extern const u8 gNintendoWfcPadKeysUpFromLeftButton[];
extern const u8 gNintendoWfcPadKeysDownFromLeftButton[];
extern const u8 gNintendoWfcPadKeysUpFromRightButton[];
extern const u8 gNintendoWfcPadKeysDownFromRightButton[];
extern const int gNintendoWfcNumberInputWindowX[];
extern const NintendoWfcPadKeyFlash gNintendoWfcPadKeyFlashes[];
extern const u8 gNintendoWfcPadNeighbors[][4];
extern const TouchscreenHitbox gNintendoWfcYesNoHitboxes[];
extern const TouchscreenHitbox gNintendoWfcPadHitboxes_Max100[];
extern const TouchscreenHitbox gNintendoWfcPadHitboxes[];
extern const NintendoWfcCursorPos gNintendoWfcYesNoCursorPositions[];

void NintendoWfcHttp_Update(void);
s32 NintendoWfcHttp_GetResult(void);
void NintendoWfcHttp_Init(u32 profileId, u64 friendKey);
BOOL NintendoWfcHttp_IsDone(void);
void NintendoWfcHttp_RequestRoomCount(int rank);
void NintendoWfcHttp_RequestDownload(int rank, int room, BattleRoomDownloadData *download);
void NintendoWfcHttp_RequestUpload(int rank, int room, int winCount, FrontierWifiUploadRecord *record);
void NintendoWfcHttp_RequestInfo(void);
void NintendoWfcHttp_RequestSetProfile(WifiServerProfile *profile, u32 *response);
enum NintendoWfcMainState NintendoWfc_SessionInit(NintendoWfcConnect *wfc, int state);
enum NintendoWfcMainState NintendoWfc_SessionMain(NintendoWfcConnect *wfc, int state);
enum NintendoWfcMainState NintendoWfc_SessionExit(NintendoWfcConnect *wfc, int state);
enum NintendoWfcMainState NintendoWfc_AskConnect(NintendoWfcConnect *wfc);
enum NintendoWfcMainState NintendoWfc_HandleConnectChoice(NintendoWfcConnect *wfc);
enum NintendoWfcMainState NintendoWfc_AskLogOut(NintendoWfcConnect *wfc);
enum NintendoWfcMainState NintendoWfc_HandleLogOutChoice(NintendoWfcConnect *wfc);
enum NintendoWfcMainState NintendoWfc_StartConnect(NintendoWfcConnect *wfc);
enum NintendoWfcMainState NintendoWfc_WaitConnect(NintendoWfcConnect *wfc);
enum NintendoWfcMainState NintendoWfc_StartAuth(NintendoWfcConnect *wfc);
enum NintendoWfcMainState NintendoWfc_WaitAuth(NintendoWfcConnect *wfc);
enum NintendoWfcMainState NintendoWfc_InitHttp(NintendoWfcConnect *wfc);
enum NintendoWfcMainState NintendoWfc_RequestInfo(NintendoWfcConnect *wfc);
enum NintendoWfcMainState NintendoWfc_WaitInfo(NintendoWfcConnect *wfc);
enum NintendoWfcMainState NintendoWfc_RequestSetProfile(NintendoWfcConnect *wfc);
enum NintendoWfcMainState NintendoWfc_WaitSetProfile(NintendoWfcConnect *wfc);
enum NintendoWfcMainState NintendoWfc_RequestRoomCount(NintendoWfcConnect *wfc);
enum NintendoWfcMainState NintendoWfc_WaitRoomCount(NintendoWfcConnect *wfc);
enum NintendoWfcMainState NintendoWfc_AskChallengeRoom(NintendoWfcConnect *wfc);
enum NintendoWfcMainState NintendoWfc_StartChallengeRoomInput(NintendoWfcConnect *wfc);
enum NintendoWfcMainState NintendoWfc_HandleChallengeRoomInput(NintendoWfcConnect *wfc);
enum NintendoWfcMainState NintendoWfc_PrintReceivingTrainers(NintendoWfcConnect *wfc);
enum NintendoWfcMainState NintendoWfc_PrintRoomUnavailable(NintendoWfcConnect *wfc);
enum NintendoWfcMainState NintendoWfc_RequestTrainersDownload(NintendoWfcConnect *wfc);
enum NintendoWfcMainState NintendoWfc_WaitTrainersDownload(NintendoWfcConnect *wfc);
enum NintendoWfcMainState NintendoWfc_PrintTrainersReceived(NintendoWfcConnect *wfc);
enum NintendoWfcMainState NintendoWfc_PrintSendingRecord(NintendoWfcConnect *wfc);
enum NintendoWfcMainState NintendoWfc_RequestUpload(NintendoWfcConnect *wfc);
enum NintendoWfcMainState NintendoWfc_WaitUpload(NintendoWfcConnect *wfc);
enum NintendoWfcMainState NintendoWfc_PrintRecordSent(NintendoWfcConnect *wfc);
enum NintendoWfcMainState NintendoWfc_AskLeadersRank(NintendoWfcConnect *wfc);
enum NintendoWfcMainState NintendoWfc_StartLeadersRankInput(NintendoWfcConnect *wfc);
enum NintendoWfcMainState NintendoWfc_HandleLeadersRankInput(NintendoWfcConnect *wfc);
enum NintendoWfcMainState NintendoWfc_AskLeadersRoom(NintendoWfcConnect *wfc);
enum NintendoWfcMainState NintendoWfc_StartLeadersRoomInput(NintendoWfcConnect *wfc);
enum NintendoWfcMainState NintendoWfc_HandleLeadersRoomInput(NintendoWfcConnect *wfc);
enum NintendoWfcMainState NintendoWfc_PrintReceivingLeaders(NintendoWfcConnect *wfc);
enum NintendoWfcMainState NintendoWfc_RequestLeadersDownload(NintendoWfcConnect *wfc);
enum NintendoWfcMainState NintendoWfc_WaitLeadersDownload(NintendoWfcConnect *wfc);
enum NintendoWfcMainState NintendoWfc_PrintLeadersReceived(NintendoWfcConnect *wfc);
enum NintendoWfcMainState NintendoWfc_StartDisconnect(NintendoWfcConnect *wfc);
enum NintendoWfcMainState NintendoWfc_StartSave(NintendoWfcConnect *wfc);
enum NintendoWfcMainState NintendoWfc_Save(NintendoWfcConnect *wfc);
enum NintendoWfcMainState NintendoWfc_AskCancelChallenge(NintendoWfcConnect *wfc);
enum NintendoWfcMainState NintendoWfc_HandleCancelChallengeChoice(NintendoWfcConnect *wfc);
enum NintendoWfcMainState NintendoWfc_AskCancelDownload(NintendoWfcConnect *wfc);
enum NintendoWfcMainState NintendoWfc_HandleCancelDownloadChoice(NintendoWfcConnect *wfc);
enum NintendoWfcMainState NintendoWfc_PrintDisconnecting(NintendoWfcConnect *wfc);
enum NintendoWfcMainState NintendoWfc_CloseConnection(NintendoWfcConnect *wfc);
enum NintendoWfcMainState NintendoWfc_PrintDisconnected(NintendoWfcConnect *wfc);
enum NintendoWfcMainState NintendoWfc_UnusedState_Idle(void);
enum NintendoWfcMainState NintendoWfc_StartExit(NintendoWfcConnect *wfc);
enum NintendoWfcMainState NintendoWfc_UnusedState_HandleYesNo(NintendoWfcConnect *wfc);
enum NintendoWfcMainState NintendoWfc_ShowHttpError(NintendoWfcConnect *wfc);
enum NintendoWfcMainState NintendoWfc_Disconnect(NintendoWfcConnect *wfc);
enum NintendoWfcMainState NintendoWfc_WaitMessage(NintendoWfcConnect *wfc);
enum NintendoWfcMainState NintendoWfc_WaitMessageAndDelay(NintendoWfcConnect *wfc);
enum NintendoWfcMainState NintendoWfc_OpenYesNoMenu(NintendoWfcConnect *wfc);
enum NintendoWfcMainState NintendoWfc_ShowDwcError(NintendoWfcConnect *wfc);
enum NintendoWfcMainState NintendoWfc_WaitErrorDismiss(NintendoWfcConnect *wfc);
BOOL NintendoWfc_NumberInput_FadeOut(NintendoWfcConnect *wfc);
BOOL NintendoWfc_NumberInput_Setup(NintendoWfcConnect *wfc);
BOOL NintendoWfc_NumberInput_WaitFadeIn(NintendoWfcConnect *wfc);
BOOL NintendoWfc_NumberInput_Main(NintendoWfcConnect *wfc);
BOOL NintendoWfc_NumberInput_UnusedState4(void);
BOOL NintendoWfc_NumberInput_UnusedState5(void);
BOOL NintendoWfc_NumberInput_UnusedState6(void);
BOOL NintendoWfc_NumberInput_StartFadeOut(NintendoWfcConnect *wfc);
BOOL NintendoWfc_NumberInput_Teardown(NintendoWfcConnect *wfc);
BOOL NintendoWfc_NumberInput_WaitButtonFlash(NintendoWfcConnect *wfc);
BOOL NintendoWfc_NumberInput_WaitFadeOut(NintendoWfcConnect *wfc);
BOOL NintendoWfc_NumberInput_Finish(void);
BOOL NintendoWfcYesNo_Start(NintendoWfcYesNoMenu *menu);
BOOL NintendoWfcYesNo_HandleInput(NintendoWfcYesNoMenu *menu);
BOOL NintendoWfcYesNo_UnusedState2(void);
BOOL NintendoWfcYesNo_WaitClose(NintendoWfcYesNoMenu *menu);

#endif // POKEHEARTGOLD_NINTENDO_WFC_CONNECT_INTERNAL_H
