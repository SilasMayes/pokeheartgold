#ifndef POKEHEARTGOLD_LOBBY_CHAT_MANAGER_H
#define POKEHEARTGOLD_LOBBY_CHAT_MANAGER_H

// Lobby chat: the chat session and the channels it is in, for the C and C++ chat sources.

#include <nitro/types.h>

#include "lobby_chat_request.h"
#include "lobby_string.h"
#include "lobby_timer.h"
#include "lobby_tree.h"

// The longest channel key and key value SetChannelKey and GetChannelKeysAsync accept, terminator included.
#define LOBBY_CHAT_KEY_SIZE   20
#define LOBBY_CHAT_VALUE_SIZE 400

enum LobbyChatState {
    LOBBY_CHAT_STATE_INIT,
    LOBBY_CHAT_STATE_CONNECTING,
    LOBBY_CHAT_STATE_CONNECTED, // logged in, waits 60 frames before READY
    LOBBY_CHAT_STATE_READY,
    LOBBY_CHAT_STATE_DISCONNECTING,
    LOBBY_CHAT_STATE_ERROR,
};

// What the session passes on to the code that started it: private messages from users and excess flood notices.
typedef struct LobbyChatCallbacks {
    void (*onMessage)();
    void (*onExcessFlood)();
    void *param;
} LobbyChatCallbacks;

// What a channel reports to the code that entered it, with that code's parameter.
typedef struct LobbyChannelCallbacks {
    void (*onUserJoined)(const char *channel, int userId, void *param);
    void (*onUserParted)(const char *channel, int userId, void *param);
    void (*onChannelMessage)(const char *channel, int userId, void *message, void *param);
    void (*onBroadcastKeyChanged)(const char *channel, int userId, void *key, void *value, void *param);
    void (*onTopicChanged)(const char *channel, void *topic, void *param);
    void *param;
} LobbyChannelCallbacks;

// A channel the session is in: its users, the user limit it was entered with and its callbacks.
typedef struct LobbyChannel {
    BOOL usersEnumerated;
    LobbyUserIdSet users;
    int userLimit;
    LobbyChannelCallbacks callbacks;
} LobbyChannel;

// The channel map: full channel name -> channel.
typedef struct LobbyChannelMapEntry {
    Str name;
    LobbyChannel channel;
} LobbyChannelMapEntry;

typedef struct LobbyChannelMapNode {
    struct LobbyChannelMapNode *left;
    struct LobbyChannelMapNode *right;
    u32 parent;
    LobbyChannelMapEntry entry;
} LobbyChannelMapNode;

typedef struct LobbyChannelMap {
    int count;
    LobbyChannelMapNode *root;
    u8 padding_08[4];
    LobbyChannelMapNode *first;
} LobbyChannelMap;

typedef struct LobbyChannelMapInsertResult {
    LobbyChannelMapNode *node;
    u8 inserted;
} LobbyChannelMapInsertResult;

// The chat session: the CHAT connection, the strings it logged in with and the user, channel, request and timer maps.
typedef struct LobbyChatManager {
    void *connection;
    int state;
    int userId;
    Str nick;
    Str user;
    Str realName;
    Str gameName;
    Str gameKey;
    Str channelPrefix;
    u32 unk54;
    int lastError;
    int connectedFrames;
    int disconnected;
    LobbyChatCallbacks callbacks;
    LobbyUserMap userMap;
    LobbyChannelMap channelMap;
    LobbyRequestMap requestMap;
    LobbyTimerMap timerMap;
} LobbyChatManager;

#ifdef __cplusplus
extern "C" {
#endif

extern LobbyChatManager *gLobbyChatManager;

void *LobbyChannelMap_Destroy(LobbyChannelMap *map);
void LobbyChannelMap_DestroyNodes(LobbyChannelMap *map, LobbyChannelMapNode *node);
void LobbyChannelMap_Erase(Iterator *out, LobbyChannelMap *map, Iterator node);
int LobbyChannelMap_EraseKey(LobbyChannelMap *map, Str *key);
void LobbyChannelMap_Find(Iterator *out, LobbyChannelMap *map, Str *key);
LobbyChannelMapNode *LobbyChannelMap_FindInsertPos(LobbyChannelMap *map, Str *key, LobbyChannelMapNode **found, u8 *left, u8 *empty);
void LobbyChannelMap_Insert(LobbyChannelMapInsertResult *out, LobbyChannelMap *map, LobbyChannelMapEntry *entry);
LobbyChannelMapNode *LobbyChannelMap_InsertNode(LobbyChannelMap *, LobbyChannelMapNode *, u8, u8, LobbyChannelMapEntry *);

void LobbyChatManager_GetNick(Str *out, LobbyChatManager *manager);
int LobbyChat_FindUserIdByNick(LobbyChatManager *manager, const Str *nick);
void LobbyChat_StripChannelPrefix(Str *out, LobbyChatManager *manager, Str *name);
LobbyChannelCallbacks *LobbyChat_GetChannelCallbacks(LobbyChatManager *manager, Str *key);
int LobbyChat_SetChannelUsersEnumerated(LobbyChatManager *manager, Str *channel);
int LobbyChat_GetChannelUserLimit(LobbyChatManager *manager, Str *channel);
int LobbyChat_AddChannelUser(LobbyChatManager *manager, Str *nick, Str *channel);
int LobbyChat_LeaveChannel(const char *channel);
int LobbyChat_Process(void);
int LobbyChat_Shutdown(void);
int LobbyChat_GetLastError(void);
int LobbyChat_ToErrorCode(int error);
int LobbyChat_IsInChannel(char *channel);
int LobbyChat_SendChannelMessage(const char *channel, const char *message);
int LobbyChat_SendUserMessage(int userId, const char *message);
int LobbyChat_SetChannelKey(const char *channel, int userId, const char *key, const char *value);
int LobbyChat_GetChannelKeysAsync(const char *channel, int userId, const char *key, LobbyGetChannelKeysCallback callback, u32 param);

// The C++ code takes the strings these return by value.
#ifdef __cplusplus
Str LobbyChat_GetFullChannelName(LobbyChatManager *manager, const Str &name);
Str LobbyChat_GetUserNick(LobbyChatManager *manager, int userId);
#else
void LobbyChat_GetFullChannelName(Str *out, LobbyChatManager *manager, Str *name);
void LobbyChat_GetUserNick(Str *out, LobbyChatManager *manager, int userId);
#endif

#ifdef __cplusplus
}
#endif

#endif // POKEHEARTGOLD_LOBBY_CHAT_MANAGER_H
