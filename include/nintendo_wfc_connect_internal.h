#ifndef POKEHEARTGOLD_NINTENDO_WFC_CONNECT_INTERNAL_H
#define POKEHEARTGOLD_NINTENDO_WFC_CONNECT_INTERNAL_H

#include "global.h"

#include "bg_window.h"
#include "frontier_wifi_upload_record.h"
#include "gf_gfx_planes.h"
#include "heap.h"
#include "obj_char_transfer.h"
#include "save_wii_message.h"
#include "sprite.h"
#include "sys_task_api.h"
#include "touchscreen.h"

enum NintendoWfcPaletteScreens {
    NINTENDO_WFC_PALETTE_BOTH_SCREENS,
    NINTENDO_WFC_PALETTE_MAIN_SCREEN,
    NINTENDO_WFC_PALETTE_SUB_SCREEN,
};

// Background palette cycling (VBlank task).
typedef struct NintendoWfcPaletteCycle {
    SysTask *task;
    int active;
    u16 basePltt[64];
    u16 cyclePltt[21 * 16];
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

// The HTTP request state of the Wi-Fi Battle Tower (gamestats) requests.
typedef struct NintendoWfcHttp {
    volatile s32 state; // enum NintendoWfcHttpState
    s32 result;
    u32 profileId;
    u64 friendKey;
    u8 rank; // first byte of the request buffer gNintendoWfcHttpRequestBuffer
    u8 room;
} NintendoWfcHttp;

typedef struct NintendoWfcHttpResponse {
    u8 unk_0[3];
    volatile u8 status; // first byte of the response buffer gNintendoWfcHttpShortResponse
    u32 unk_4;
    u8 *buffer;
} NintendoWfcHttpResponse;

typedef struct NintendoWfcGlobal {
    NNSFndHeapHandle heap; // heap of the DWC allocator callbacks
    NintendoWfcConnect *wfc;
    u8 unk_8[0xC];
} NintendoWfcGlobal;

typedef int (*NintendoWfcScreenFunc)(NintendoWfcConnect *wfc, int state);

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
extern u8 gNintendoWfcHttpFriendKey[];
extern u8 gNintendoWfcHttpRequestBuffer[];
extern u8 ov72_0223B900[];
extern u8 gNintendoWfcHttpUploadFriendKey[];
extern NintendoWfcHttpResponse gNintendoWfcHttpResponse;
extern u8 gNintendoWfcHttpShortResponse[];
extern NintendoWfcGlobal gNintendoWfcGlobal;
extern const char gNintendoWfcRoomNumUrl[];
extern const char gNintendoWfcDownloadUrl[];
extern const char gNintendoWfcUploadUrl[];
extern const char gNintendoWfcInfoUrl[];
extern const char gNintendoWfcSetProfileUrl[];
extern const NintendoWfcScreenFuncs gNintendoWfcScreens[];
extern int (*const gNintendoWfcStates[])(NintendoWfcConnect *wfc);
extern int (*const gNintendoWfcNumberInputStates[])(NintendoWfcConnect *wfc);
extern int (*const gNintendoWfcYesNoStates[])(NintendoWfcYesNoMenu *menu);
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
void NintendoWfcHttp_RequestDownload(int rank, int room, void *buffer);
void NintendoWfcHttp_RequestUpload(int rank, int room, int winCount, FrontierWifiUploadRecord *record);
void NintendoWfcHttp_RequestInfo(void);
void NintendoWfcHttp_RequestSetProfile(WifiServerProfile *profile, u32 *response);
int NintendoWfc_SessionInit(NintendoWfcConnect *wfc, int state);
int NintendoWfc_SessionMain(NintendoWfcConnect *wfc, int state);
int NintendoWfc_SessionExit(NintendoWfcConnect *wfc, int state);
int NintendoWfc_AskConnect(NintendoWfcConnect *wfc);
int NintendoWfc_HandleConnectChoice(NintendoWfcConnect *wfc);
int NintendoWfc_AskLogOut(NintendoWfcConnect *wfc);
int NintendoWfc_HandleLogOutChoice(NintendoWfcConnect *wfc);
int NintendoWfc_StartConnect(NintendoWfcConnect *wfc);
int NintendoWfc_WaitConnect(NintendoWfcConnect *wfc);
int NintendoWfc_StartAuth(NintendoWfcConnect *wfc);
int NintendoWfc_WaitAuth(NintendoWfcConnect *wfc);
int NintendoWfc_InitHttp(NintendoWfcConnect *wfc);
int NintendoWfc_RequestInfo(NintendoWfcConnect *wfc);
int NintendoWfc_WaitInfo(NintendoWfcConnect *wfc);
int NintendoWfc_RequestSetProfile(NintendoWfcConnect *wfc);
int NintendoWfc_WaitSetProfile(NintendoWfcConnect *wfc);
int NintendoWfc_RequestRoomCount(NintendoWfcConnect *wfc);
int NintendoWfc_WaitRoomCount(NintendoWfcConnect *wfc);
int NintendoWfc_AskChallengeRoom(NintendoWfcConnect *wfc);
int NintendoWfc_StartChallengeRoomInput(NintendoWfcConnect *wfc);
int NintendoWfc_HandleChallengeRoomInput(NintendoWfcConnect *wfc);
int NintendoWfc_PrintReceivingTrainers(NintendoWfcConnect *wfc);
int NintendoWfc_PrintRoomUnavailable(NintendoWfcConnect *wfc);
int NintendoWfc_RequestTrainersDownload(NintendoWfcConnect *wfc);
int NintendoWfc_WaitTrainersDownload(NintendoWfcConnect *wfc);
int NintendoWfc_PrintTrainersReceived(NintendoWfcConnect *wfc);
int NintendoWfc_PrintSendingRecord(NintendoWfcConnect *wfc);
int NintendoWfc_RequestUpload(NintendoWfcConnect *wfc);
int NintendoWfc_WaitUpload(NintendoWfcConnect *wfc);
int NintendoWfc_PrintRecordSent(NintendoWfcConnect *wfc);
int NintendoWfc_AskLeadersRank(NintendoWfcConnect *wfc);
int NintendoWfc_StartLeadersRankInput(NintendoWfcConnect *wfc);
int NintendoWfc_HandleLeadersRankInput(NintendoWfcConnect *wfc);
int NintendoWfc_AskLeadersRoom(NintendoWfcConnect *wfc);
int NintendoWfc_StartLeadersRoomInput(NintendoWfcConnect *wfc);
int NintendoWfc_HandleLeadersRoomInput(NintendoWfcConnect *wfc);
int NintendoWfc_PrintReceivingLeaders(NintendoWfcConnect *wfc);
int NintendoWfc_RequestLeadersDownload(NintendoWfcConnect *wfc);
int NintendoWfc_WaitLeadersDownload(NintendoWfcConnect *wfc);
int NintendoWfc_PrintLeadersReceived(NintendoWfcConnect *wfc);
int NintendoWfc_StartDisconnect(NintendoWfcConnect *wfc);
int NintendoWfc_StartSave(NintendoWfcConnect *wfc);
int NintendoWfc_Save(NintendoWfcConnect *wfc);
int NintendoWfc_AskCancelChallenge(NintendoWfcConnect *wfc);
int NintendoWfc_HandleCancelChallengeChoice(NintendoWfcConnect *wfc);
int NintendoWfc_AskCancelDownload(NintendoWfcConnect *wfc);
int NintendoWfc_HandleCancelDownloadChoice(NintendoWfcConnect *wfc);
int NintendoWfc_PrintDisconnecting(NintendoWfcConnect *wfc);
int NintendoWfc_CloseConnection(NintendoWfcConnect *wfc);
int NintendoWfc_PrintDisconnected(NintendoWfcConnect *wfc);
int NintendoWfc_UnusedState_Idle(void);
int NintendoWfc_StartExit(NintendoWfcConnect *wfc);
int NintendoWfc_UnusedState_HandleYesNo(NintendoWfcConnect *wfc);
int NintendoWfc_ShowHttpError(NintendoWfcConnect *wfc);
int NintendoWfc_Disconnect(NintendoWfcConnect *wfc);
int NintendoWfc_WaitMessage(NintendoWfcConnect *wfc);
int NintendoWfc_WaitMessageAndDelay(NintendoWfcConnect *wfc);
int NintendoWfc_OpenYesNoMenu(NintendoWfcConnect *wfc);
int NintendoWfc_ShowDwcError(NintendoWfcConnect *wfc);
int NintendoWfc_WaitErrorDismiss(NintendoWfcConnect *wfc);
int NintendoWfc_NumberInput_FadeOut(NintendoWfcConnect *wfc);
int NintendoWfc_NumberInput_Setup(NintendoWfcConnect *wfc);
int NintendoWfc_NumberInput_WaitFadeIn(NintendoWfcConnect *wfc);
BOOL NintendoWfc_NumberInput_Main(NintendoWfcConnect *wfc);
int NintendoWfc_NumberInput_UnusedState4(void);
int NintendoWfc_NumberInput_UnusedState5(void);
int NintendoWfc_NumberInput_UnusedState6(void);
int NintendoWfc_NumberInput_StartFadeOut(NintendoWfcConnect *wfc);
int NintendoWfc_NumberInput_Teardown(NintendoWfcConnect *wfc);
int NintendoWfc_NumberInput_WaitButtonFlash(NintendoWfcConnect *wfc);
int NintendoWfc_NumberInput_WaitFadeOut(NintendoWfcConnect *wfc);
int NintendoWfc_NumberInput_Finish(void);

#endif // POKEHEARTGOLD_NINTENDO_WFC_CONNECT_INTERNAL_H
