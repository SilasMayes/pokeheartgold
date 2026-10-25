#include <nitro/types.h>

#include <nitro/code32.h>

#include "lobby_chat_manager.h"

extern "C" void LobbyTreeIterator_Advance(Iterator *it);

struct HasUser {
    int userId;

    HasUser(int id)
        : userId(id) {
    }

    bool operator()(LobbyChannelMapEntry &entry) const {
        Iterator found;
        LobbyUserIdSet_Find(&found, &entry.channel.users, &userId);
        return found.current != &entry.channel.users.root;
    }
};

static inline void FindChannel(Iterator *it, LobbyChannelMap *map, HasUser pred) {
    void *end = &map->root;
    it->current = map->first;
    while (it->current != end && !pred(((LobbyChannelMapNode *)it->current)->entry)) {
        LobbyTreeIterator_Advance(it);
    }
}

// The user stays while any channel the session is in still holds them.
BOOL LobbyChat_RemoveUserIfUnused(LobbyChatManager *manager, int userId) {
    Iterator it;
    FindChannel(&it, &manager->channelMap, HasUser(userId));
    if (it.current != &manager->channelMap.root) {
        return FALSE;
    }
    LobbyUserMap_EraseKey(&manager->userMap, &userId);
    return TRUE;
}
