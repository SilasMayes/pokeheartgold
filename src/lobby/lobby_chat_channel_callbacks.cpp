#include <nitro/types.h>

#include <nitro/code32.h>

#include "lobby_chat_manager.h"
#include "ppw_lobby_state.h"


extern "C" void LobbyChat_OnChannelModeChanged(struct ChatConnection *chat, const char *name, u32 mode, u32 id);

inline void KeyInit(LobbyRequest *key, u32 id) {
    key->vtable = &gLobbyRequestVtable;
    key->id = id;
    key->param = 0;
}

inline LobbyRequestMapIterator FindIt(LobbyChatManager *manager, u32 id) {
    LobbyRequest key;
    KeyInit(&key, id);
    LobbyRequest *kp = &key;
    return LobbyRequestMap_Find(&manager->requestMap, kp);
}

struct Tag {};
struct Vec;
extern "C" void LobbyU32Vector_AssignRange(Vec *v, u32 *first, u32 *last, Tag t);
extern "C" void LobbyU32Vector_Destroy(Vec *v);
extern "C" void *LobbyU32Vector_Data2(Vec *v);

struct Vec {
    u32 *ptr;
    u32 size;
    u32 cap;

    Vec()
        : ptr(0)
        , size(0)
        , cap(0) {
    }

    Vec &operator=(const Vec &o) {
        if (this != &o) {
            LobbyU32Vector_AssignRange(this, o.ptr, o.ptr + o.size, Tag());
        }
        return *this;
    }

    void destroy() {
        LobbyU32Vector_Destroy(this);
    }

    u32 count() const {
        return size;
    }
};

extern "C" Vec LobbyChat_AddChannelUsers(LobbyChatManager *map, int count, const char **names, const Str &key);
extern "C" int chatGetChannelNumUsersA(struct ChatConnection *chat, const char *channel);
extern "C" void chatSetChannelLimitA(struct ChatConnection *chat, const char *channel, int limit);
extern "C" void chatEnumUsersA(struct ChatConnection *chat, const char *channel, void *callback, u32 param, u32 blocking);

extern "C" void LobbyChat_OnEnterChannelEnumUsers(struct ChatConnection *chat, int result, const char *name, int count, const char **nicks, u32 modes, u32 id);
extern "C" void LobbyChat_OnEnterChannel(struct ChatConnection *chat, int ok, int error, const char *name, u32 id);
extern "C" void LobbyChat_OnGetChannelKeys(struct ChatConnection *chat, int result, const char *name, const char *user, int count, const char **keys, const char **values, u32 id);
extern "C" void LobbyChat_OnBroadcastKeyChanged(struct ChatConnection *chat, char *channel, char *nick, void *key, void *value);
extern "C" void LobbyChat_OnGetChannelMode(struct ChatConnection *chat, int result, const char *name, u32 mode, u32 id);

#pragma push
#pragma opt_propagation off

extern "C" void LobbyChat_OnEnterChannelEnumUsers(struct ChatConnection *chat, int result, const char *name, int count, const char **nicks, u32 modes, u32 id) {
    if (gLobbyChatManager != NULL && gLobbyChatManager->state == LOBBY_CHAT_STATE_ERROR) {
        return;
    }
    if (result == 1) {
        Str usersChannelName;
        LobbyString_InitFromCStr(&usersChannelName, name);
        Vec tmp = LobbyChat_AddChannelUsers(gLobbyChatManager, count, nicks, usersChannelName);
        tmp.destroy();
        LobbyString_Destroy(&usersChannelName);
    }
    {
        Str enumeratedName;
        LobbyString_InitFromCStr(&enumeratedName, name);
        LobbyChat_SetChannelUsersEnumerated(gLobbyChatManager, &enumeratedName);
        LobbyString_Destroy(&enumeratedName);
    }
    int sid = id;
    LobbyChatManager *manager = gLobbyChatManager;
    LobbyRequestMapIterator it = FindIt(manager, sid);
    LobbyEnterChannelRequest *request;
    if (it.node == (LobbyRequestMapNode *)&manager->requestMap.root) {
        request = NULL;
    } else {
        LobbyRequestMapNode *nd = it.node;
        request = (LobbyEnterChannelRequest *)nd->request;
    }
    Str fullName;
    LobbyString_InitFromCStr(&fullName, name);
    Str strippedName;
    LobbyChat_StripChannelPrefix(&strippedName, gLobbyChatManager, &fullName);
    LobbyEnterChannelCallback cb = request->callback;
    const char *str = strippedName.c_str();
    cb(result == 1, 0, str, request->getParam());
    LobbyString_Destroy(&strippedName);
    LobbyString_Destroy(&fullName);
    LobbyRequestMap_DeleteKey(&gLobbyChatManager->requestMap, sid);
    if (result != 0) {
        return;
    }
    Str fullNameToLeave;
    LobbyString_InitFromCStr(&fullNameToLeave, name);
    Str nameToLeave;
    LobbyChat_StripChannelPrefix(&nameToLeave, gLobbyChatManager, &fullNameToLeave);
    LobbyChat_LeaveChannel(nameToLeave.c_str());
    LobbyString_Destroy(&nameToLeave);
    LobbyString_Destroy(&fullNameToLeave);
}

#pragma pop

#pragma push
#pragma opt_propagation off

extern "C" void LobbyChat_OnEnterChannel(struct ChatConnection *chat, int ok, int error, const char *name, u32 id) {
    if (gLobbyChatManager != NULL && gLobbyChatManager->state == LOBBY_CHAT_STATE_ERROR) {
        return;
    }
    if (ok == 1) {
        Str fullName;
        LobbyString_InitFromCStr(&fullName, name);
        int userLimit = LobbyChat_GetChannelUserLimit(gLobbyChatManager, &fullName);
        LobbyString_Destroy(&fullName);
        if (userLimit != 0) {
            int numUsers = chatGetChannelNumUsersA(gLobbyChatManager->connection, name);
            if (userLimit == -1) {
                ok = 0;
                error = 7;
            } else if (numUsers > userLimit || numUsers == -1) {
                ok = 0;
                error = 2;
            } else {
                chatSetChannelLimitA(gLobbyChatManager->connection, name, userLimit);
            }
        }
    }
    if (ok == 1) {
        Str nick;
        LobbyChatManager_GetNick(&nick, gLobbyChatManager);
        Str channelName;
        LobbyString_InitFromCStr(&channelName, name);
        LobbyChat_AddChannelUser(gLobbyChatManager, &nick, &channelName);
        LobbyString_Destroy(&channelName);
        LobbyString_Destroy(&nick);
        chatEnumUsersA(chat, name, (void *)LobbyChat_OnEnterChannelEnumUsers, id, FALSE);
        return;
    }
    {
        Str fullName;
        LobbyString_InitFromCStr(&fullName, name);
        Str strippedName;
        LobbyChat_StripChannelPrefix(&strippedName, gLobbyChatManager, &fullName);
        LobbyChat_LeaveChannel(strippedName.c_str());
        LobbyString_Destroy(&strippedName);
        LobbyString_Destroy(&fullName);
    }
    int sid = id;
    LobbyChatManager *manager = gLobbyChatManager;
    LobbyRequestMapIterator it = FindIt(manager, sid);
    LobbyEnterChannelRequest *request = it.node == (LobbyRequestMapNode *)&manager->requestMap.root ? 0 : (LobbyEnterChannelRequest *)it.node->request;
    Str fullName;
    LobbyString_InitFromCStr(&fullName, name);
    Str strippedName;
    LobbyChat_StripChannelPrefix(&strippedName, gLobbyChatManager, &fullName);
    const char *str = strippedName.c_str();
    LobbyEnterChannelCallback cb = request->callback;
    cb(0, error, str, request->getParam());
    LobbyString_Destroy(&strippedName);
    LobbyString_Destroy(&fullName);
    LobbyRequestMap_DeleteKey(&gLobbyChatManager->requestMap, sid);
}

#pragma pop

#pragma push
#pragma opt_propagation off

extern "C" void LobbyChat_OnGetChannelKeys(struct ChatConnection *chat, int result, const char *name, const char *user, int count, const char **keys, const char **values, u32 id) {
    if (gLobbyChatManager != NULL && gLobbyChatManager->state == LOBBY_CHAT_STATE_ERROR) {
        return;
    }
    if (name == NULL) {
        return;
    }
    int userId;
    if (user == NULL) {
        userId = -1;
    } else {
        Str nick;
        LobbyString_InitFromCStr(&nick, user);
        userId = LobbyChat_FindUserIdByNick(gLobbyChatManager, &nick);
        LobbyString_Destroy(&nick);
    }
    int sid = id;
    const char *key, *value;
    LobbyGetChannelKeysRequest *request;
    LobbyChatManager *manager = gLobbyChatManager;
    LobbyRequestMapIterator it = FindIt(manager, sid);
    if (it.node == (LobbyRequestMapNode *)&manager->requestMap.root) {
        request = NULL;
    } else {
        LobbyRequestMapNode *nd = it.node;
        request = (LobbyGetChannelKeysRequest *)nd->request;
    }
    key = NULL;
    value = key;
    if (result == 1 && count > 0) {
        key = *keys;
        value = *values;
    }
    Str fullName;
    LobbyString_InitFromCStr(&fullName, name);
    Str strippedName;
    LobbyChat_StripChannelPrefix(&strippedName, gLobbyChatManager, &fullName);
    const char *str = strippedName.c_str();
    LobbyGetChannelKeysCallback cb = request->callback;
    cb(result == 1, str, userId, key, value, request->getParam());
    LobbyString_Destroy(&strippedName);
    LobbyString_Destroy(&fullName);
    LobbyRequestMap_DeleteKey(&gLobbyChatManager->requestMap, sid);
}

#pragma pop

// A key without a user is a channel key; it is reported with user ID -1.
extern "C" void LobbyChat_OnBroadcastKeyChanged(struct ChatConnection *chat, char *channel, char *nick, void *key, void *value) {
    Str nickStr;
    Str channelKey;
    Str fullName;
    Str channelName;
    int userId;
    LobbyChannelCallbacks *callbacks;
    if (gLobbyChatManager && gLobbyChatManager->state == LOBBY_CHAT_STATE_ERROR) {
        return;
    }
    if (!nick) {
        userId = -1;
    } else {
        LobbyString_InitFromCStr(&nickStr, nick);
        userId = LobbyChat_FindUserIdByNick(gLobbyChatManager, &nickStr);
        LobbyString_Destroy(&nickStr);
    }
    LobbyString_InitFromCStr(&channelKey, channel);
    callbacks = LobbyChat_GetChannelCallbacks(gLobbyChatManager, &channelKey);
    LobbyString_Destroy(&channelKey);
    LobbyString_InitFromCStr(&fullName, channel);
    LobbyChat_StripChannelPrefix(&channelName, gLobbyChatManager, &fullName);
    callbacks->onBroadcastKeyChanged(channelName.c_str(), userId, key, value, callbacks->param);
    LobbyString_Destroy(&channelName);
    LobbyString_Destroy(&fullName);
}

#pragma push
#pragma opt_propagation off

extern "C" void LobbyChat_OnGetChannelMode(struct ChatConnection *chat, int result, const char *name, u32 mode, u32 id) {
    if (gLobbyChatManager != NULL && gLobbyChatManager->state == LOBBY_CHAT_STATE_ERROR) {
        return;
    }
    if (result == 0) {
        return;
    }
    LobbyChat_OnChannelModeChanged(chat, name, mode, id);
    int sid = id;
    LobbyChatManager *manager = gLobbyChatManager;
    LobbyRequestMapIterator it = FindIt(manager, sid);
    LobbyGetChannelModeRequest *request = it.node == (LobbyRequestMapNode *)&manager->requestMap.root ? 0 : (LobbyGetChannelModeRequest *)it.node->request;
    Str fullName;
    LobbyString_InitFromCStr(&fullName, name);
    Str strippedName;
    LobbyChat_StripChannelPrefix(&strippedName, gLobbyChatManager, &fullName);
    const char *str = strippedName.c_str();
    LobbyGetChannelModeCallback cb = request->callback;
    cb(result == 1, str, mode, request->getParam());
    LobbyString_Destroy(&strippedName);
    LobbyString_Destroy(&fullName);
    LobbyRequestMap_DeleteKey(&gLobbyChatManager->requestMap, sid);
}

#pragma pop
