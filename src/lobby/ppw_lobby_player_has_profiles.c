#include "global.h"

#include <nitro/code32.h>

#include "ppw_lobby_internal.h"
#include "ppw_lobby_state.h"

BOOL PPWLobbyPlayer_HasProfiles(Session *s) {
    return s->state >= PPW_LOBBY_PLAYER_STATE_HAS_PROFILES;
}
