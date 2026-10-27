#include "global.h"

#include "lobby_chat_manager.h"
#include "ppw_lobby_internal.h"
#include "ppw_lobby_state.h"

#include <nitro/code32.h>


static inline BOOL active(PPWLobbyWork *w) {
    return w->subChannel.kind == PPW_LOBBY_CHANNEL_KIND_INVALID ? FALSE : TRUE;
}

#pragma opt_propagation off

enum PPWLobbyChannelState PPW_LobbyGetSubChannelState(void) {
    Str text;
    PPWLobbyWork *w = gPPWLobbyWork;
    BOOL inChannel;
    if (!w) {
        return PPW_LOBBY_CHANNEL_STATE_ERROR;
    }
    if (w && w->state == PPW_LOBBY_STATE_ERROR) {
        return PPW_LOBBY_CHANNEL_STATE_ERROR;
    }
    if (w && PPWLobby_GetState() != PPW_LOBBY_STATE_READY) {
        return PPW_LOBBY_CHANNEL_STATE_ERROR;
    }
    {
        BOOL enabled = active(w);
        if (!enabled) {
            return PPW_LOBBY_CHANNEL_STATE_NONE;
        }
    }
    PPWLobbyChannel_GetName(&text, &w->subChannel);
    inChannel = LobbyChat_IsInChannel(!text.l.isLong ? text.s.buf : text.l.ptr);
    LobbyString_Destroy(&text);
    if (inChannel) {
        return PPW_LOBBY_CHANNEL_STATE_JOINED;
    }
    return PPW_LOBBY_CHANNEL_STATE_JOINING;
}
