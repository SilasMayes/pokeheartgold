#include "global.h"

#include <nitro/code32.h>

#include "ppw_lobby_internal.h"
#include "ppw_lobby_state.h"

BOOL PPWLobbyPlayer_HasProfiles(PPWLobbyPlayer *player) {
    return player->state >= PPW_LOBBY_PLAYER_STATE_HAS_PROFILES;
}
