#include <nitro/types.h>

#include <nitro/code32.h>

#include "lobby_mem.h"

#include "lobby_chat_manager.h"
#include "ppw_lobby_state.h"


extern "C" const u32 gLobbyChatNextRequestId;


extern "C" void chatGetChannelModeA(struct ChatConnection *chat, const char *channel, void (*callback)(), u32 param, u32 blocking);
extern "C" void LobbyChat_OnGetChannelMode();

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

inline LobbyCallbackRequest *NewHandler(u32 callback, u32 param) {
    LobbyCallbackRequest *request = (LobbyCallbackRequest *)LobbyMem_Alloc(sizeof(LobbyCallbackRequest));
    if (request) {
        BaseInit(request, param);
        request->id = NextHandlerId();
        request->vtable = &gLobbyGetChannelModeRequestVtable;
        request->callback = callback;
    }
    return request;
}

extern "C" enum PPWLobbyResult LobbyChat_GetChannelModeAsync(const char *name, u32 callback, u32 param);

struct IdTag {};

inline u32 GetId(LobbyCallbackRequest *request, IdTag, IdTag) {
    return request->vtable->getId(request);
}

#pragma opt_common_subs off

extern "C" enum PPWLobbyResult LobbyChat_GetChannelModeAsync(const char *name, u32 callback, u32 param) {
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
    LobbyRequestMapInsertResult result;
    LobbyCallbackRequest *request;
    request = NewHandler(callback, param);
    LobbyRequestMap_Insert(&result, &manager->requestMap, &request);
    u32 id = GetId(request, IdTag(), IdTag());
    Str channelName;
    LobbyString_InitFromCStr(&channelName, name);
    Str fullName = LobbyChat_GetFullChannelName(GetMgr(), channelName);
    chatGetChannelModeA(GetMgr()->connection, fullName.c_str(), LobbyChat_OnGetChannelMode, id, 0);
    LobbyString_Destroy(&fullName);
    LobbyString_Destroy(&channelName);
    return PPW_LOBBY_RESULT_SUCCESS;
}

#pragma opt_common_subs reset
