#include <nitro/types.h>

#include <nitro/code32.h>

#include "lobby_vector.h"
#include "ppw_lobby_state.h"
#include "ppw_lobby_work.h"

extern "C" void LobbyTreeIterator_Advance(Iterator *it);

// What onPlayerEnter reports of a player's system profile: the channel time and the channel.
struct PlayerRecord {
    u32 timeLow, timeHigh;
    int channel;
};

static inline PPWLobbyPlayer *PlayerAt(const Iterator &it) {
    return ((PPWLobbyPlayerSetNode *)it.current)->player;
}

#pragma opt_propagation off

void PPWLobbyPlayers_UpdateStates(PPWLobbyPlayers *players) {
    PPWLobbyPlayer *profilePlayer;
    BOOL notChanged;
    u32 userProfileSize;
    int id;
    Iterator it;
    PPWLobbyPlayerSetNode *end;
    it.current = players->playerSet.leftmost;
    end = (PPWLobbyPlayerSetNode *)&players->playerSet.root;
    if (it.current != end) {
        notChanged = FALSE;
        do {
            PPWLobbyPlayer_UpdateState(PlayerAt(it));
            switch (PlayerAt(it)->state) {
            case PPW_LOBBY_PLAYER_STATE_NEW:
            case PPW_LOBBY_PLAYER_STATE_HAS_PROFILES:
            case PPW_LOBBY_PLAYER_STATE_ENTERED:
                break;
            case PPW_LOBBY_PLAYER_STATE_READY: {
                PPWLobbyPlayer *player = PlayerAt(it);
                player->systemProfileChanged = notChanged;
                profilePlayer = PlayerAt(it);
                profilePlayer->userProfileChanged = notChanged;
                const PlayerRecord &recordRef = (PlayerRecord) { .channel = player->systemProfile.channel, .timeLow = ((u32 *)&player->systemProfile.time)[0], .timeHigh = ((u32 *)&player->systemProfile.time)[1] };
                PlayerRecord record = recordRef;
                userProfileSize = profilePlayer->userProfile.size;
                id = PlayerAt(it)->id;
                PPWLobbyWork *work = PPWLobby_GetWork();
                work->callbacks.onPlayerEnter(id, &record, LobbyByteVector_Data(&profilePlayer->userProfile), userProfileSize);
                PlayerAt(it)->entered = TRUE;
                break;
            }
            }
            LobbyTreeIterator_Advance(&it);
        } while (it.current != end);
    }
}

#pragma opt_propagation reset
