#include "global.h"

#include "dwc/net_common_internal.h"

#include <nitro/code32.h>

#include "lobby_mem.h"
#include "ppw_lobby_internal.h"
#include "ppw_lobby_state.h"

void PPWLobbyPlayer_UpdateState(PPWLobbyPlayer *player) {
    switch (player->state) {
    case PPW_LOBBY_PLAYER_STATE_NEW:
        player->state = (player->systemProfileReceived && player->userProfileReceived) ? PPW_LOBBY_PLAYER_STATE_HAS_PROFILES : PPW_LOBBY_PLAYER_STATE_NEW;
        if (player->state == PPW_LOBBY_PLAYER_STATE_NEW) {
            return;
        }
    case PPW_LOBBY_PLAYER_STATE_HAS_PROFILES:
        if (player->systemProfile.unk_0C != 0) {
            player->state = PPW_LOBBY_PLAYER_STATE_READY;
        }
        return;
    case PPW_LOBBY_PLAYER_STATE_READY:
        if (player->entered) {
            player->state = PPW_LOBBY_PLAYER_STATE_ENTERED;
        }
        return;
    case PPW_LOBBY_PLAYER_STATE_ENTERED:
        return;
    }
}

BOOL PPWLobbyPlayers_Add(PPWLobbyPlayers *players, int id) {
    RTCDate date;
    RTCTime time;
    PPWLobbyPlayer *player;
    volatile PPWLobbyPlayerSetInsertResult resultCopy;
    PPWLobbyPlayerSetInsertResult result;
    volatile LobbyTag tag1;
    volatile LobbyTag tag0;
    PPWLobbyPlayer *newPlayer = LobbyMem_Alloc(sizeof(PPWLobbyPlayer));
    if (newPlayer != NULL) {
        newPlayer->vtable = &gPPWLobbyPlayerVtable;
        newPlayer->systemProfile.channel = PPW_LOBBY_CHANNEL_KIND_INVALID;
        newPlayer->systemProfile.time.seconds = 0;
        newPlayer->systemProfile.unk_0C = 0;
        DWC_GetDateTime(&date, &time);
        newPlayer->systemProfile.time.seconds = RTC_ConvertDateTimeToSecond(&date, &time);
        newPlayer->systemProfileChanged = TRUE;
        newPlayer->userProfile.data = NULL;
        newPlayer->userProfile.size = 0;
        newPlayer->userProfile.capacity = 0;
        newPlayer->userProfileChanged = TRUE;
        newPlayer->state = PPW_LOBBY_PLAYER_STATE_NEW;
        newPlayer->id = id;
        newPlayer->systemProfileReceived = FALSE;
        newPlayer->userProfileReceived = FALSE;
        newPlayer->entered = FALSE;
    }
    player = newPlayer;
    PPWLobbyPlayerSet_Insert(&result, &players->playerSet, &player);
    tag1.unused = 0;
    resultCopy.node = result.node;
    tag0.unused = 0;
    resultCopy.inserted = result.inserted;
    if ((result.inserted & 0xFF) == 0) {
        if (player != NULL) {
            player->vtable->destroyAndFree(player);
        }
        return TRUE;
    }
    return TRUE;
}

BOOL PPWLobbyPlayers_Remove(PPWLobbyPlayers *players, int id) {
    Iterator it;
    PPWLobbyPlayerSetNode *end = (PPWLobbyPlayerSetNode *)&players->playerSet.root;
    it.current = players->playerSet.leftmost;
    while (it.current != end) {
        PPWLobbyPlayer *player = ((PPWLobbyPlayerSetNode *)it.current)->player;
        if (id == player->id) {
            Iterator next;
            if (player != NULL) {
                player->vtable->destroyAndFree(player);
            }
            PPWLobbyPlayerSet_Erase(&next, &players->playerSet, it);
            return TRUE;
        }
        LobbyTreeIterator_Advance(&it);
    }
    return FALSE;
}

PPWLobbyPlayer *PPWLobbyPlayers_Find(PPWLobbyPlayers *players, int id) {
    volatile FindState first;
    volatile FindState search;
    PPWLobbyPlayerSetNode *found;
    BOOL atEnd;
    PPWLobbyPlayerSetNode *end;
    PPWLobbyPlayerSetNode *leftmost;
    if (id == players->self.id) {
        return &players->self;
    }
    leftmost = players->playerSet.leftmost;
    end = (PPWLobbyPlayerSetNode *)&players->playerSet.root;
    first.id = id;
    search.id = id;
    first.end = end;
    search.end = end;
    first.it.current = leftmost;
    search.it.current = leftmost;
    while (((Iterator *)&search.it)->current != end && id != ((PPWLobbyPlayerSetNode *)((Iterator *)&search.it)->current)->player->id) {
        LobbyTreeIterator_Advance((Iterator *)&search.it);
    }
    atEnd = ((Iterator *)&search.it)->current == (PPWLobbyPlayerSetNode *)&players->playerSet.root;
    found = search.it.current;
    if (atEnd) {
        return NULL;
    }
    return found->player;
}
