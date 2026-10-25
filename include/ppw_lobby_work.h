#ifndef POKEHEARTGOLD_PPW_LOBBY_WORK_H
#define POKEHEARTGOLD_PPW_LOBBY_WORK_H

#include "lobby_event_deque.h"
#include "lobby_timer.h"
#include "overlay45_format_buffer_private.h"

#include "../lib/NitroDWC/src/tree-iterator4.h"

// The callbacks the game passes to PPW_LobbyInitializeAsync, in table order.
typedef struct PPWLobbyCallbacks {
    void (*onEnterChannel)(int result, u32 channel);
    void (*onPlayerEnter)(int userId, const void *systemProfile, const void *userProfile, u32 userProfileSize);
    void (*onPlayerLeave)(int userId);
    void (*onStringMessage)(int userId, int channel, int type, const void *text);
    void (*onMessage)(int userId, u32 channel, u32 type, const void *data, u32 size);
    void (*onLocationsChanged)(BOOL success, BOOL broadcast, int channel, int userId, const char *key, const void *data, u32 size, u32 param);
    void (*onPlayerRecordChanged)(int userId, const void *systemProfile);
    void (*onPlayerUpdate)(int userId, const void *userProfile, u32 size);
    void (*onMatchInfo)(int userId, void *info);
    void (*onMatchClosed)(int userId, const void *info);
    void (*onLobbyEvent)(u32 event);
    void (*onOwnRecord)(int result, const void *record, u32 size);
    BOOL (*onScheduleReceived)(int result, const void *schedule);
    void (*onSpecialVisitorsReceived)(int result, const void *records, u32 count);
    void (*onSurveyReceived)(int result, const void *questionnaire);
    void (*onSurveySubmitted)(s32 result);
    void (*onExcessFlood)(int userId);
} PPWLobbyCallbacks;

typedef struct PPWLobbyChannel {
    int kind;
    Str name;
    BOOL usersEnumerated;
    BOOL modeReady;
} PPWLobbyChannel;

// Channel time in seconds (RTC_ConvertDateTimeToSecond).
typedef struct PPWLobbyTime {
    s64 seconds;
} PPWLobbyTime;

// Uploaded as the "b_lib_u_system" channel key.
typedef struct PPWLobbySystemProfile {
    int channel;
    PPWLobbyTime time;
    u32 unk_0C;
} PPWLobbySystemProfile;

// The players a lobby channel holds, the own player included.
#define PPW_LOBBY_MAX_PLAYERS 20

typedef struct PPWLobbyPlayer PPWLobbyPlayer;

typedef struct PPWLobbyPlayerVtable {
    PPWLobbyPlayer *(*destroy)(PPWLobbyPlayer *player);
    void *(*destroyAndFree)(PPWLobbyPlayer *player);
} PPWLobbyPlayerVtable;

struct PPWLobbyPlayer {
    const PPWLobbyPlayerVtable *vtable;
    PPWLobbySystemProfile systemProfile;
    BOOL systemProfileChanged;
    LobbyCharVector userProfile;
    BOOL userProfileChanged;
    int state;
    int id;
    BOOL systemProfileReceived;
    BOOL userProfileReceived;
    BOOL entered;
};

typedef struct PPWLobbyPlayerSetNode {
    struct PPWLobbyPlayerSetNode *left;
    struct PPWLobbyPlayerSetNode *right;
    u32 parent;
    PPWLobbyPlayer *player;
} PPWLobbyPlayerSetNode;

// The other players, a tree of PPWLobbyPlayer keyed by user id. The root field is also the tree's end node.
typedef struct PPWLobbyPlayerSet {
    u32 count;
    PPWLobbyPlayerSetNode *root;
    PPWLobbyPlayerSetNode *leftmost;
} PPWLobbyPlayerSet;

typedef struct PPWLobbyPlayerSetInsertResult {
    PPWLobbyPlayerSetNode *node;
    u8 inserted;
} PPWLobbyPlayerSetInsertResult;

typedef struct PPWLobbyPlayers {
    const void *vtable;
    PPWLobbyPlayerSet playerSet;
    PPWLobbyPlayer self;
} PPWLobbyPlayers;

// A special visitor of the lobby: player id and visitor value, as the game receives them.
typedef struct PPWLobbyVipRecord {
    u32 id;
    u32 value;
} PPWLobbyVipRecord;

typedef struct PPWLobbyVipVector {
    PPWLobbyVipRecord *data;
    u32 size;
    u32 capacity;
} PPWLobbyVipVector;

// The schedule record as the server sends it and PPWLobbySchedule_Copy writes it: a header and the timed events.
typedef struct PPWLobbyScheduleRecord {
    u32 lockTime;
    u32 unk_04;
    u32 roomFlag;
    u8 roomType;
    u8 season;
    u16 eventCount;
    LobbyEvent events[1];
} PPWLobbyScheduleRecord;

// The event schedule the server sends for the lobby, and the questionnaire.
typedef struct PPWLobbySchedule {
    int state;
    BOOL hasTime;
    PPWLobbyTime time;
    s64 startTime;
    BOOL startRequested;
    u32 lockTime;
    u32 unk_20;
    u32 roomFlag;
    u8 roomType;
    u8 season;
    LobbyEventVector events;
    LobbyEventDeque pendingEvents;
    PPWLobbyVipVector vips;
    u8 questionnaire[0x2D8];
    BOOL hasQuestionnaire;
} PPWLobbySchedule;

// What the own player shows the other players while recruiting for a match (the game's match info): the match
// numbers, the match parameters and the match name.
typedef struct PPWLobbyRecruitInfo {
    int index;
    int maxPlayers;
    int playerCount;
    int state;
    struct {
        u8 bytes[32];
    } params;
    struct {
        char text[20];
    } name;
} PPWLobbyRecruitInfo;

typedef struct PPWLobbyWork {
    int state;
    int error;
    PPWLobbyCallbacks callbacks;
    u32 userId;
    u32 prefix;
    u32 unk_54;
    Str channelBaseName;
    BOOL isNewChannel;
    BOOL recruiting;
    BOOL submittingQuestionnaire;
    u32 unk_70;
    PPWLobbyRecruitInfo recruitInfo;
    PPWLobbyChannel mainChannel;
    PPWLobbyChannel subChannel;
    PPWLobbyPlayers players;
    LobbyTimerMap timers;
    PPWLobbySchedule schedule;
} PPWLobbyWork;

// What PPW_LobbyGetTimeInfo reports: the current time, the channel time and the schedule's start time, in seconds.
typedef struct PPWLobbyTimeInfo {
    s64 currentTime;
    PPWLobbyTime channelTime;
    s64 startTime;
} PPWLobbyTimeInfo;

// A web request of the lobby (schedule, VIP list, profile check, questionnaire), sent through the stats upload
// client (key and server for StatsUpload_Start; page, pid and body for the upload). It is retried up to retries
// times and reports its answer to callback.
typedef struct PPWLobbyWebRequest PPWLobbyWebRequest;

// What a web request reports when the server has answered: success, the answer, and the request's param.
typedef void (*PPWLobbyWebCallback)(BOOL success, u8 *data, u32 size, void *param);

typedef struct PPWLobbyWebRequestVtable {
    void *unk_00;
    void (*destroy)(PPWLobbyWebRequest *request);
} PPWLobbyWebRequestVtable;

struct PPWLobbyWebRequest {
    const PPWLobbyWebRequestVtable *vtable;
    int retries;
    int server;
    Str key;
    Str page;
    int pid;
    LobbyCharVector body;
    PPWLobbyWebCallback callback;
    void *param;
    BOOL useLastHash;
};

struct ChatChannelMode;
struct DwcUserData;

#ifdef __cplusplus
extern "C" {
#endif

extern PPWLobbyWork *gPPWLobbyWork;

// The modes the lobby sets on its channels (the user limit is the channel's player count).
extern const struct ChatChannelMode gPPWLobbyMainChannelMode;
extern const struct ChatChannelMode gPPWLobbyMainChannelSecretMode;
extern const struct ChatChannelMode gPPWLobbyFootChannelMode;
extern const struct ChatChannelMode gPPWLobbyClockChannelMode;
extern const struct ChatChannelMode gPPWLobbyNewsChannelMode;

PPWLobbyWork *PPWLobby_GetWork(void);
int PPWLobby_Initialize(const char *, const char *, int, const PPWLobbyCallbacks *, u32, const void *, u32, u32);
Str *PPWLobby_GetChannelBaseName(Str *out, PPWLobbyWork *work);
void PPWLobbyChannel_GetName(Str *out, PPWLobbyChannel *channel);
void PPWLobby_GetChannelName(Str *out, PPWLobbyChannel *channels, int subChannel);
PPWLobbyPlayer *PPWLobbyPlayer_Destroy(PPWLobbyPlayer *player);
PPWLobbyPlayers *PPWLobbyPlayers_Destroy(PPWLobbyPlayers *players);
PPWLobbyWebRequest *PPWLobbyWebRequest_Delete(PPWLobbyWebRequest *request);
void *PPWLobbyWebRequest_Destroy(PPWLobbyWebRequest *request);
void *PPWLobbyPlayers_Delete(PPWLobbyPlayers *players);
void *PPWLobbyPlayer_Delete(PPWLobbyPlayer *player);
void *PPWLobbyPlayerSet_Destroy(PPWLobbyPlayerSet *set);
void PPWLobbyPlayerSet_DestroyNodes(PPWLobbyPlayerSet *set, PPWLobbyPlayerSetNode *node);
void PPWLobbyPlayerSet_Erase(Iterator *out, PPWLobbyPlayerSet *set, Iterator position);
void PPWLobby_GenerateChannelBaseName(Str *out);
int PPWLobby_GetWebResultError(u32 type);
int PPWLobby_HandleLibraryData(BOOL success, BOOL broadcast, int kind, int userId, const char *key, const u8 *data, u32 len, u32 param);
void PPWLobby_HandleReceivedData(BOOL success, BOOL broadcast, const char *channel, int userId, const char *key, const char *value, u32 param);
void PPWLobby_OnCheckProfile(BOOL success, u8 *response, u32 responseSize, void *param);
void PPWLobby_OnEnterSubChannel(BOOL success, int error, const char *channel, int kind);
void PPWLobby_OnEnumChannels(int, int, char **, int, int *);
void PPWLobby_OnExcessFlood(int);
void PPWLobby_OnGetChannelKeys(BOOL success, const char *channel, int userId, const char *key, const char *value, u32 param);
void PPWLobby_OnGetChannelTime(BOOL result, const char *channel, int userId, const char *key, const char *value, u32 param);
void PPWLobby_OnGetLobbyData(BOOL success, const char *channel, int userId, const char *key, const char *value, u32 param);
void PPWLobby_OnGetQuestionnaire(BOOL success, u8 *response, u32 responseSize, void *param);
void PPWLobby_OnGetSchedule(BOOL success, u8 *response, u32 responseSize, void *param);
void PPWLobby_OnGetVip(BOOL success, u8 *response, u32 responseSize, void *param);
void PPWLobby_OnPlayerMessage(int, int, int);
void PPWLobby_OnSubmitQuestionnaire(BOOL status, u8 *data, u32 size, void *param);
void PPWLobby_OnTopicChanged(void);
int PPWLobby_ParseWebResponse(BOOL valid, u8 *data, u32 size, void **output, u32 *length);
int PPWLobby_SetChannelData(int userId, int kind, const char *key, const void *data, u32 size);
void PPWLobby_StartCheckProfile(void);
int PPWLobby_TimerPollChannelMode(void);
int PPWLobby_TimerRequestChannelTime(void);
int PPWLobby_TimerRequestLobbyData(void);
int PPWLobby_TimerSendRecruitInfo(void);
int PPWLobby_TimerUploadSystemProfile(void);
int PPWLobby_TimerUploadUserProfile(void);
int PPW_LobbyInitializeAsync(const char *gameName, const char *secretKey, int prefix, const PPWLobbyCallbacks *callbacks, const struct DwcUserData *userData, const void *playerData, u32 playerDataSize);
int PPW_LobbyShutdownAsync(void);
int PPW_LobbyProcess(void);
int PPW_LobbyJoinSubChannelAsync(int channel);
int PPW_LobbyLeaveSubChannel(void);
int PPW_LobbyGetSubChannelState(void);
int PPW_LobbyGetMyUserId(void);
int PPW_LobbySendChannelBinaryMessage(int channel, int type, const void *data, int size);
int PPW_LobbySendPlayerBinaryMessage(int userId, int type, const void *data, int size);
int PPW_LobbySetChannelData(int userId, int channel, const char *key, const void *data, u32 size);
int PPW_LobbyGetChannelDataAsync(int userId, int channel, const char *key, u32 param);
int PPW_LobbyUpdateMyProfile(const void *data, u32 size, int force);
int PPW_LobbyGetTimeInfo(PPWLobbyTimeInfo *timeInfo);
int PPW_LobbyGetSchedule(PPWLobbyScheduleRecord *records, u32 *size);
int PPW_LobbySubmitQuestionnaire(int mode);
int PPW_LobbyGetLastError(void);
int PPW_LobbyInitResultToLastError(int result);
int PPW_LobbyToErrorCode(int error);
int PPWLobby_SendMessage(int id, int channel, int type, int mode, int arg, const void *data, u32 size);
BOOL PPWLobbySchedule_GetQuestionnaire(PPWLobbySchedule *schedule, void *out);
BOOL PPWLobbySchedule_SetQuestionnaire(PPWLobbySchedule *schedule, const void *in);
void PPWLobbySchedule_Process(PPWLobbySchedule *schedule);
BOOL PPWLobbySchedule_CanStart(PPWLobbySchedule *schedule);
BOOL PPWLobbySchedule_Start(PPWLobbySchedule *schedule);
PPWLobbySchedule *PPWLobbySchedule_Init(PPWLobbySchedule *schedule);
BOOL PPWLobbySchedule_Copy(PPWLobbySchedule *schedule, PPWLobbyScheduleRecord *out, u32 *size);
void PPWLobbySchedule_CopyToVector(LobbyCharVector *out, PPWLobbySchedule *schedule);
LobbyEvent *LobbyEventVector_Data(LobbyEventVector *vector);
LobbyEventVector *LobbyEventVector_Destroy(LobbyEventVector *vector);
PPWLobbyVipVector *LobbyVipVector_Destroy(PPWLobbyVipVector *vector);
void LobbyVipVector_Allocate(PPWLobbyVipVector *vector, u32 capacity, LobbyTag tag);
void LobbyVipVector_Reallocate(PPWLobbyVipVector *vector, u32 unused, u32 capacity);
void LobbyVipVector_AssignRange(PPWLobbyVipVector *vector, const PPWLobbyVipRecord *first, const PPWLobbyVipRecord *last, LobbyTag tag);
u32 LobbyVipVector_RecommendSize(PPWLobbyVipVector *vector, u32 extra);
BOOL PPWLobbySchedule_IsSizeValid(PPWLobbySchedule *schedule, const void *data, u32 size);
BOOL PPWLobbySchedule_Load(PPWLobbySchedule *schedule, const void *data, u32 size);
BOOL PPWLobbySchedule_ValidateVipRecords(PPWLobbySchedule *schedule, const void *data, u32 size);
BOOL PPWLobbySchedule_SetVipRecords(PPWLobbySchedule *schedule, const void *data, u32 size);
void PPWLobbyPlayers_Clear(PPWLobbyPlayers *);
void PPWLobbyPlayers_UpdateStates(PPWLobbyPlayers *);
void PPWLobbyPlayer_UpdateState(PPWLobbyPlayer *player);
BOOL PPWLobbyPlayers_AllHaveProfiles(PPWLobbyPlayers *players);
BOOL PPWLobbyPlayers_IsFull(PPWLobbyPlayers *players);
void PPWLobby_MakeChannelName(Str *out, u32 kind, Str *baseName);
int PPWLobby_EnterMainChannel(void);
BOOL PPWLobby_IsMainChannelReady(void);

#ifdef __cplusplus
}
#endif

// The start of the player record the game uploads as its user profile.
typedef struct PPWLobbyUserProfile {
    u32 lobbyId;
    u32 trainerId;
    u8 unk_08[0x31];
    u8 language;
    u8 unk_3A[8];
    u8 version;
} PPWLobbyUserProfile;

#endif // POKEHEARTGOLD_PPW_LOBBY_WORK_H
