#ifndef POKEHEARTGOLD_NINTENDO_WFC_CONNECT_UNUSED_H
#define POKEHEARTGOLD_NINTENDO_WFC_CONNECT_UNUSED_H

#include <nitro.h>

#include <dwc/net_common_internal.h>

#include "global.h"

#include "frontier_data_access.h"
#include "frontier_wifi_upload_record.h"
#include "msgdata.h"
#include "nintendo_wfc_connect.h"
#include "nintendo_wfc_connect_internal.h"
#include "render_window.h"
#include "save_wii_message.h"
#include "sprite.h"
#include "yes_no_prompt.h"

enum NintendoWfcUnusedState {
    NINTENDO_WFC_UNUSED_STATE_ASK_CONNECT,
    NINTENDO_WFC_UNUSED_STATE_HANDLE_CONNECT_CHOICE,
    NINTENDO_WFC_UNUSED_STATE_START_CONNECT,
    NINTENDO_WFC_UNUSED_STATE_WAIT_CONNECT,
    NINTENDO_WFC_UNUSED_STATE_START_AUTH,
    NINTENDO_WFC_UNUSED_STATE_WAIT_AUTH,
    NINTENDO_WFC_UNUSED_STATE_INIT_HTTP,
    NINTENDO_WFC_UNUSED_STATE_REQUEST_INFO,
    NINTENDO_WFC_UNUSED_STATE_WAIT_INFO,
    NINTENDO_WFC_UNUSED_STATE_REQUEST_SET_PROFILE,
    NINTENDO_WFC_UNUSED_STATE_WAIT_SET_PROFILE,
    NINTENDO_WFC_UNUSED_STATE_REQUEST_ROOM_COUNT,
    NINTENDO_WFC_UNUSED_STATE_WAIT_ROOM_COUNT,
    NINTENDO_WFC_UNUSED_STATE_ASK_CHALLENGE_ROOM,
    NINTENDO_WFC_UNUSED_STATE_START_CHALLENGE_ROOM_INPUT,
    NINTENDO_WFC_UNUSED_STATE_HANDLE_CHALLENGE_ROOM_INPUT,
    NINTENDO_WFC_UNUSED_STATE_PRINT_RECEIVING_TRAINERS,
    NINTENDO_WFC_UNUSED_STATE_REQUEST_TRAINERS_DOWNLOAD,
    NINTENDO_WFC_UNUSED_STATE_WAIT_TRAINERS_DOWNLOAD,
    NINTENDO_WFC_UNUSED_STATE_PRINT_TRAINERS_RECEIVED,
    NINTENDO_WFC_UNUSED_STATE_PRINT_ROOM_UNAVAILABLE,
    NINTENDO_WFC_UNUSED_STATE_ASK_CANCEL_CHALLENGE,
    NINTENDO_WFC_UNUSED_STATE_HANDLE_CANCEL_CHALLENGE_CHOICE,
    NINTENDO_WFC_UNUSED_STATE_ASK_CANCEL_DOWNLOAD,
    NINTENDO_WFC_UNUSED_STATE_HANDLE_CANCEL_DOWNLOAD_CHOICE,
    NINTENDO_WFC_UNUSED_STATE_PRINT_SENDING_RECORD,
    NINTENDO_WFC_UNUSED_STATE_REQUEST_UPLOAD,
    NINTENDO_WFC_UNUSED_STATE_WAIT_UPLOAD,
    NINTENDO_WFC_UNUSED_STATE_PRINT_RECORD_SENT,
    NINTENDO_WFC_UNUSED_STATE_ASK_LEADERS_RANK,
    NINTENDO_WFC_UNUSED_STATE_START_LEADERS_RANK_INPUT,
    NINTENDO_WFC_UNUSED_STATE_HANDLE_LEADERS_RANK_INPUT,
    NINTENDO_WFC_UNUSED_STATE_ASK_LEADERS_ROOM,
    NINTENDO_WFC_UNUSED_STATE_START_LEADERS_ROOM_INPUT,
    NINTENDO_WFC_UNUSED_STATE_HANDLE_LEADERS_ROOM_INPUT,
    NINTENDO_WFC_UNUSED_STATE_PRINT_RECEIVING_LEADERS,
    NINTENDO_WFC_UNUSED_STATE_REQUEST_LEADERS_DOWNLOAD,
    NINTENDO_WFC_UNUSED_STATE_WAIT_LEADERS_DOWNLOAD,
    NINTENDO_WFC_UNUSED_STATE_PRINT_LEADERS_RECEIVED,
    NINTENDO_WFC_UNUSED_STATE_START_SAVE,
    NINTENDO_WFC_UNUSED_STATE_SAVE,
    NINTENDO_WFC_UNUSED_STATE_PRINT_DISCONNECTING,
    NINTENDO_WFC_UNUSED_STATE_CLOSE_CONNECTION,
    NINTENDO_WFC_UNUSED_STATE_PRINT_DISCONNECTED,
    NINTENDO_WFC_UNUSED_STATE_UNUSED_IDLE,
    NINTENDO_WFC_UNUSED_STATE_START_DISCONNECT,
    NINTENDO_WFC_UNUSED_STATE_START_EXIT,
    NINTENDO_WFC_UNUSED_STATE_WAIT_MESSAGE,
    NINTENDO_WFC_UNUSED_STATE_OPEN_YES_NO_PROMPT,
    NINTENDO_WFC_UNUSED_STATE_WAIT_MESSAGE_AND_DELAY,
    NINTENDO_WFC_UNUSED_STATE_UNUSED_HANDLE_YES_NO,
    NINTENDO_WFC_UNUSED_STATE_ASK_LOG_OUT,
    NINTENDO_WFC_UNUSED_STATE_HANDLE_LOG_OUT_CHOICE,
    NINTENDO_WFC_UNUSED_STATE_SHOW_HTTP_ERROR,
    NINTENDO_WFC_UNUSED_STATE_DISCONNECT,
    NINTENDO_WFC_UNUSED_STATE_SHOW_DWC_ERROR,
    NINTENDO_WFC_UNUSED_STATE_WAIT_ERROR_DISMISS,
};

typedef struct BattleRoomDownload BattleRoomDownload;

typedef struct NintendoWfcUnused {
    NintendoWifiConnectArgs *args;
    BgConfig *bgConfig;
    u8 padding_0008[8];
    int mode; // index into sNintendoWfcUnusedModes
    int nextMode;
    int unk_0018;
    int state; // index into sNintendoWfcUnusedStates
    int nextState;
    void *heapMem;
    NNSFndHeapHandle expHeap;
    NetConnection connection;
    u32 ownRank;
    int rank;
    int roomCount;
    int room;
    BattleRoomDownloadData downloadBuffer;
    FrontierWifiUploadRecord uploadRecord;
    u8 padding_0BBC[0x14];
    MessageFormat *msgFormat;
    MsgData *msgDataTower; // Wi-Fi Battle Tower
    MsgData *msgDataWfc;   // Nintendo WFC
    MsgData *msgDataError; // Nintendo WFC errors
    String *msgString;
    String *titleString;
    String *roomString;
    String *rankString;
    String *errorString;
    u32 textPrinterId;
    SpriteList *spriteList;
    G2dRenderer renderer;
    GF_2DGfxResMan *resMan[4];
    SpriteResource *resObjs[4];
    u8 padding_0D44[0x20];
    SpriteResourcesHeader spriteHeader;
    u8 padding_0D88[0x48];
    Sprite *arrows[2]; // up/down arrows next to the number windows
    Window msgWindow;
    Window rankWindow;
    Window roomWindow;
    Window titleWindow;
    Window errorWindow;
    u8 padding_0E28[0xE4];
    WaitingIcon *waitingIcon;
    int dwcError;
    int dwcErrorCode;
    int dwcErrorType;
    int httpResult; // enum NintendoWfcHttpResult
    int messageTimer;
    WifiServerProfile profile;
    u32 profileResponse[2];
    s16 subState;
    s16 subTimer;
    int timeoutCounter;
    NintendoWfcPaletteCycle paletteCycle;
    YesNoPrompt *yesNoPrompt;
} NintendoWfcUnused;

typedef struct NintendoWfcUnusedGlobal {
    NintendoWfcUnused *wfc;
    NNSFndHeapHandle heap; // heap of the DWC allocator callbacks
} NintendoWfcUnusedGlobal;

typedef int (*NintendoWfcUnusedModeFunc)(NintendoWfcUnused *wfc, int state);

// The session functions of each mode.
typedef struct NintendoWfcUnusedModeRow {
    NintendoWfcUnusedModeFunc init;
    NintendoWfcUnusedModeFunc main;
    NintendoWfcUnusedModeFunc exit;
} NintendoWfcUnusedModeRow;

extern const u16 gNintendoWfcUnusedArrowPositions[2][2];

void CommState_InitWfcSession(SaveData *saveData);
void CommState_FreeWfcSession(void);
void CommState_ShowRestartErrorAndHalt(void);
int RecordMixing_State_AbortLeave(int errorCode, int errorType);

int NintendoWfcUnused_SessionInit(NintendoWfcUnused *wfc, int state);
int NintendoWfcUnused_SessionMain(NintendoWfcUnused *wfc, int state);
int NintendoWfcUnused_SessionExit(NintendoWfcUnused *wfc, int state);
int NintendoWfcUnused_AskConnect(NintendoWfcUnused *wfc);
int NintendoWfcUnused_HandleConnectChoice(NintendoWfcUnused *wfc);
int NintendoWfcUnused_AskLogOut(NintendoWfcUnused *wfc);
int NintendoWfcUnused_HandleLogOutChoice(NintendoWfcUnused *wfc);
int NintendoWfcUnused_StartConnect(NintendoWfcUnused *wfc);
int NintendoWfcUnused_WaitConnect(NintendoWfcUnused *wfc);
int NintendoWfcUnused_StartAuth(NintendoWfcUnused *wfc);
int NintendoWfcUnused_WaitAuth(NintendoWfcUnused *wfc);
int NintendoWfcUnused_InitHttp(NintendoWfcUnused *wfc);
int NintendoWfcUnused_RequestInfo(NintendoWfcUnused *wfc);
int NintendoWfcUnused_WaitInfo(NintendoWfcUnused *wfc);
int NintendoWfcUnused_RequestSetProfile(NintendoWfcUnused *wfc);
int NintendoWfcUnused_WaitSetProfile(NintendoWfcUnused *wfc);
int NintendoWfcUnused_RequestRoomCount(NintendoWfcUnused *wfc);
int NintendoWfcUnused_WaitRoomCount(NintendoWfcUnused *wfc);
int NintendoWfcUnused_AskChallengeRoom(NintendoWfcUnused *wfc);
int NintendoWfcUnused_StartChallengeRoomInput(NintendoWfcUnused *wfc);
int NintendoWfcUnused_HandleChallengeRoomInput(NintendoWfcUnused *wfc);
int NintendoWfcUnused_PrintReceivingTrainers(NintendoWfcUnused *wfc);
int NintendoWfcUnused_PrintRoomUnavailable(NintendoWfcUnused *wfc);
int NintendoWfcUnused_RequestTrainersDownload(NintendoWfcUnused *wfc);
int NintendoWfcUnused_WaitTrainersDownload(NintendoWfcUnused *wfc);
int NintendoWfcUnused_PrintTrainersReceived(NintendoWfcUnused *wfc);
int NintendoWfcUnused_PrintSendingRecord(NintendoWfcUnused *wfc);
int NintendoWfcUnused_RequestUpload(NintendoWfcUnused *wfc);
int NintendoWfcUnused_WaitUpload(NintendoWfcUnused *wfc);
int NintendoWfcUnused_PrintRecordSent(NintendoWfcUnused *wfc);
int NintendoWfcUnused_AskLeadersRank(NintendoWfcUnused *wfc);
int NintendoWfcUnused_StartLeadersRankInput(NintendoWfcUnused *wfc);
int NintendoWfcUnused_HandleLeadersRankInput(NintendoWfcUnused *wfc);
int NintendoWfcUnused_AskLeadersRoom(NintendoWfcUnused *wfc);
int NintendoWfcUnused_StartLeadersRoomInput(NintendoWfcUnused *wfc);
int NintendoWfcUnused_HandleLeadersRoomInput(NintendoWfcUnused *wfc);
int NintendoWfcUnused_PrintReceivingLeaders(NintendoWfcUnused *wfc);
int NintendoWfcUnused_RequestLeadersDownload(NintendoWfcUnused *wfc);
int NintendoWfcUnused_WaitLeadersDownload(NintendoWfcUnused *wfc);
int NintendoWfcUnused_PrintLeadersReceived(NintendoWfcUnused *wfc);
int NintendoWfcUnused_StartDisconnect(NintendoWfcUnused *wfc);
int NintendoWfcUnused_AskCancelChallenge(NintendoWfcUnused *wfc);
int NintendoWfcUnused_HandleCancelChallengeChoice(NintendoWfcUnused *wfc);
int NintendoWfcUnused_AskCancelDownload(NintendoWfcUnused *wfc);
int NintendoWfcUnused_HandleCancelDownloadChoice(NintendoWfcUnused *wfc);
int NintendoWfcUnused_PrintDisconnecting(NintendoWfcUnused *wfc);
int NintendoWfcUnused_CloseConnection(NintendoWfcUnused *wfc);
int NintendoWfcUnused_PrintDisconnected(NintendoWfcUnused *wfc);
int NintendoWfcUnused_UnusedState_Idle(NintendoWfcUnused *wfc);
int NintendoWfcUnused_UnusedState_HandleYesNo(NintendoWfcUnused *wfc);
int NintendoWfcUnused_StartSave(NintendoWfcUnused *wfc);
int NintendoWfcUnused_Save(NintendoWfcUnused *wfc);
int NintendoWfcUnused_StartExit(NintendoWfcUnused *wfc);
int NintendoWfcUnused_ShowHttpError(NintendoWfcUnused *wfc);
int NintendoWfcUnused_Disconnect(NintendoWfcUnused *wfc);
int NintendoWfcUnused_WaitMessage(NintendoWfcUnused *wfc);
int NintendoWfcUnused_WaitMessageAndDelay(NintendoWfcUnused *wfc);
int NintendoWfcUnused_OpenYesNoPrompt(NintendoWfcUnused *wfc);
int NintendoWfcUnused_ShowDwcError(NintendoWfcUnused *wfc);
int NintendoWfcUnused_WaitErrorDismiss(NintendoWfcUnused *wfc);

YesNoPrompt *NintendoWfcUnused_CreateYesNoPrompt(BgConfig *bgConfig, u8 y, int tileStart);
int NintendoWfcUnused_HandleYesNoPrompt(YesNoPrompt *prompt);
void NintendoWfcUnused_SetState(NintendoWfcUnused *wfc, int state, int nextState);
int NintendoWfcUnused_GetWifiIconLevel(NintendoWfcUnused *wfc);
void NintendoWfcUnused_SetNextMode(NintendoWfcUnused *wfc, int mode, int a2);

#endif // POKEHEARTGOLD_NINTENDO_WFC_CONNECT_UNUSED_H
