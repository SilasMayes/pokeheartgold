#include "global.h"

#include <nitro/code32.h>

#include "ppw_lobby_internal.h"

BOOL PPWLobbyPlayers_IsFull(PPWLobbyPlayers *players) {
    LobbyU32Vector ids;
    BOOL made = FALSE;
    BOOL res = FALSE;
    if (players->playerSet.count + 1 == PPW_LOBBY_MAX_PLAYERS) {
        PPWLobbyPlayers_GetEnteredIds(&ids, players);
        made = TRUE;
        if (ids.size + 1 == PPW_LOBBY_MAX_PLAYERS) {
            res = TRUE;
        }
    }
    if (made) {
        LobbyU32Vector_Destroy(&ids);
    }
    return res;
}

void PPWLobbyPlayers_GetEnteredIds(LobbyU32Vector *out, PPWLobbyPlayers *players) {
    Iterator it;
    u32 id;
    PPWLobbyPlayerSetNode *end;
    out->data = NULL;
    out->size = 0;
    out->capacity = 0;
    VecReserve(out, players->playerSet.count);
    end = (PPWLobbyPlayerSetNode *)&players->playerSet.root;
    it.current = players->playerSet.leftmost;
    while (it.current != end) {
        PPWLobbyPlayer *player = ((PPWLobbyPlayerSetNode *)it.current)->player;
        if (player->entered) {
            id = player->id;
            TouchTag();
            if (out->size < out->capacity) {
                out->size++;
                out->data[out->size - 1] = id;
            } else {
                LobbyTag tag = { 0 };
                LobbyU32Vector_PushBackSlow(out, &id, tag);
            }
        }
        LobbyTreeIterator_Advance(&it);
    }
}
