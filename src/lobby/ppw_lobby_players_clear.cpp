#include <nitro/types.h>

#include <nitro/code32.h>

#include "ppw_lobby_work.h"

extern "C" void LobbyTreeIterator_Advance(Iterator *it);

void PPWLobbyPlayers_Clear(PPWLobbyPlayers *players) {
    Iterator it;
    Iterator position;
    Iterator next;
    it.current = players->playerSet.leftmost;
    while (it.current != &players->playerSet.root) {
        PPWLobbyPlayer *player = ((PPWLobbyPlayerSetNode *)it.current)->player;
        if (player != NULL) {
            player->vtable->destroyAndFree(player);
        }
        position = it;
        LobbyTreeIterator_Advance(&it);
        PPWLobbyPlayerSet_Erase(&next, &players->playerSet, position);
    }
}
