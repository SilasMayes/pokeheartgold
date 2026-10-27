#include <nitro/types.h>

#include <nitro/code32.h>

#include "lobby_mem.h"

#include "lobby_chat_manager.h"
#include "ppw_lobby_state.h"


extern "C" const u32 gLobbyChatNextRequestId;


extern "C" void chatGetChannelKeysA(struct ChatConnection *chat, const char *channel, const char *nick, int count, const char **keys, void (*callback)(), u32 param, u32 blocking);
extern "C" void chatEnumChannelsA(struct ChatConnection *chat, const char *filter, void (*callbackEach)(), void (*callbackAll)(), u32 param, u32 blocking);
extern "C" void chatEnumUsersA(struct ChatConnection *chat, const char *channel, void (*callback)(), u32 param, u32 blocking);
extern "C" int chatInChannelA(struct ChatConnection *chat, const char *channel);
extern "C" void LobbyChat_OnGetChannelKeys();
extern "C" void LobbyChat_OnEnumChannelsEach();
extern "C" void LobbyChat_OnEnumChannels();
extern "C" void LobbyChat_OnEnumUsers();
extern "C" unsigned long strlen(const char *);
extern "C" const char gLobbyStr_Empty_17[];

inline bool StrEquals(const Str *s, const char *cstr) {
    return LobbyString_CompareCStr(s, cstr) == 0;
}

inline LobbyChatManager *GetMgr() {
    return gLobbyChatManager;
}

inline void BaseInit(LobbyRequest *request, u32 param) {
    request->vtable = &gLobbyRequestVtable;
    request->id = 0;
    request->param = param;
}

// The id counter is only changed here; it is declared const so that stores through the new handler cannot alias it.
inline u32 NextHandlerId() {
    u32 id = gLobbyChatNextRequestId;
    *(u32 *)&gLobbyChatNextRequestId = id + 1;
    return id;
}

inline LobbyCallbackRequest *NewHandler(LobbyRequestVtable *vtable, u32 callback, u32 param) {
    LobbyCallbackRequest *request = (LobbyCallbackRequest *)LobbyMem_Alloc(sizeof(LobbyCallbackRequest));
    if (request) {
        BaseInit(request, param);
        request->id = NextHandlerId();
        request->vtable = vtable;
        request->callback = callback;
    }
    return request;
}

extern "C" enum PPWLobbyResult LobbyChat_EnumChannelsAsync(const char *name, u32 callback, u32 param);
extern "C" enum PPWLobbyResult LobbyChat_EnumUsersAsync(const char *name, u32 callback, u32 param);

struct IdTag {};

inline u32 GetId(LobbyCallbackRequest *request, IdTag, IdTag) {
    return request->vtable->getId(request);
}

#pragma opt_common_subs off

enum PPWLobbyResult LobbyChat_GetChannelKeysAsync(const char *name, int userId, const char *key, LobbyGetChannelKeysCallback callback, u32 param) {
    LobbyChatManager *manager = gLobbyChatManager;
    if (manager == NULL) {
        return PPW_LOBBY_RESULT_ERROR_STATE;
    }
    if (manager != NULL && manager->state == LOBBY_CHAT_STATE_ERROR) {
        return PPW_LOBBY_RESULT_ERROR_CONDITION;
    }
    if (manager != NULL && GetMgr()->state != LOBBY_CHAT_STATE_READY) {
        return PPW_LOBBY_RESULT_ERROR_STATE;
    }
    if (strlen(key) + 1 > LOBBY_CHAT_KEY_SIZE) {
        return PPW_LOBBY_RESULT_ERROR_PARAM;
    }
    Str nick;
    LobbyString_InitFromCStr(&nick, gLobbyStr_Empty_17);
    if (userId == -1) {
        LobbyString_AssignCStr(&nick, gLobbyStr_Empty_17);
    } else {
        Str userNick = LobbyChat_GetUserNick(GetMgr(), userId);
        LobbyString_Assign(&nick, &userNick);
        LobbyString_Destroy(&userNick);
        if (StrEquals(&nick, gLobbyStr_Empty_17)) {
            LobbyString_Destroy(&nick);
            return PPW_LOBBY_RESULT_ERROR_PARAM;
        }
    }
    manager = GetMgr();
    LobbyRequestMapInsertResult res;
    LobbyCallbackRequest *request = NewHandler(&gLobbyGetChannelKeysRequestVtable, (u32)callback, param);
    LobbyRequestMap_Insert(&res, &manager->requestMap, &request);
    u32 id = GetId(request, IdTag(), IdTag());
    Str channelName;
    LobbyString_InitFromCStr(&channelName, name);
    Str fullName = LobbyChat_GetFullChannelName(GetMgr(), channelName);
    chatGetChannelKeysA(GetMgr()->connection, fullName.c_str(), nick.c_str(), 1, &key, LobbyChat_OnGetChannelKeys, id, 0);
    LobbyString_Destroy(&fullName);
    LobbyString_Destroy(&channelName);
    LobbyString_Destroy(&nick);
    return PPW_LOBBY_RESULT_SUCCESS;
}

extern "C" enum PPWLobbyResult LobbyChat_EnumChannelsAsync(const char *name, u32 callback, u32 param) {
    LobbyChatManager *manager = gLobbyChatManager;
    if (manager == NULL) {
        return PPW_LOBBY_RESULT_ERROR_STATE;
    }
    if (manager != NULL && manager->state == LOBBY_CHAT_STATE_ERROR) {
        return PPW_LOBBY_RESULT_ERROR_CONDITION;
    }
    if (manager != NULL && GetMgr()->state != LOBBY_CHAT_STATE_READY) {
        return PPW_LOBBY_RESULT_ERROR_STATE;
    }
    LobbyRequestMapInsertResult res;
    LobbyCallbackRequest *request = NewHandler(&gLobbyEnumChannelsRequestVtable, callback, param);
    LobbyRequestMap_Insert(&res, &manager->requestMap, &request);
    u32 id = GetId(request, IdTag(), IdTag());
    Str channelName;
    LobbyString_InitFromCStr(&channelName, name);
    Str fullName = LobbyChat_GetFullChannelName(GetMgr(), channelName);
    chatEnumChannelsA(GetMgr()->connection, fullName.c_str(), LobbyChat_OnEnumChannelsEach, LobbyChat_OnEnumChannels, id, 0);
    LobbyString_Destroy(&fullName);
    LobbyString_Destroy(&channelName);
    return PPW_LOBBY_RESULT_SUCCESS;
}

extern "C" enum PPWLobbyResult LobbyChat_EnumUsersAsync(const char *name, u32 callback, u32 param) {
    LobbyChatManager *manager = gLobbyChatManager;
    if (manager == NULL) {
        return PPW_LOBBY_RESULT_ERROR_STATE;
    }
    if (manager != NULL && manager->state == LOBBY_CHAT_STATE_ERROR) {
        return PPW_LOBBY_RESULT_ERROR_CONDITION;
    }
    if (manager != NULL && GetMgr()->state != LOBBY_CHAT_STATE_READY) {
        return PPW_LOBBY_RESULT_ERROR_STATE;
    }
    {
        Str channelName;
        LobbyString_InitFromCStr(&channelName, name);
        Str fullName = LobbyChat_GetFullChannelName(GetMgr(), channelName);
        BOOL exists = chatInChannelA(GetMgr()->connection, fullName.c_str()) == 0;
        LobbyString_Destroy(&fullName);
        LobbyString_Destroy(&channelName);
        if (exists) {
            return PPW_LOBBY_RESULT_ERROR_CHANNEL;
        }
    }
    manager = GetMgr();
    LobbyRequestMapInsertResult res;
    LobbyCallbackRequest *request = NewHandler(&gLobbyEnumUsersRequestVtable, callback, param);
    LobbyRequestMap_Insert(&res, &manager->requestMap, &request);
    u32 id = GetId(request, IdTag(), IdTag());
    Str channelName;
    LobbyString_InitFromCStr(&channelName, name);
    Str fullName = LobbyChat_GetFullChannelName(GetMgr(), channelName);
    chatEnumUsersA(GetMgr()->connection, fullName.c_str(), LobbyChat_OnEnumUsers, id, 0);
    LobbyString_Destroy(&fullName);
    LobbyString_Destroy(&channelName);
    return PPW_LOBBY_RESULT_SUCCESS;
}

#pragma opt_common_subs reset
