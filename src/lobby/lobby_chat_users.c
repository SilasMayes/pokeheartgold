#include "global.h"

#include "dwc/net_common_internal.h"

#include <nitro/code32.h>

#include "lobby_chat_internal.h"

void LobbyUserIdSet_Find(Iter *out, LobbyUserIdSet *set, const int *key) {
    LobbyUserIdSetNode *node = LobbyUserIdSet_LowerBound(set, key, set->root, (LobbyUserIdSetNode *)&set->root);
    if (node == (LobbyUserIdSetNode *)&set->root || *key < node->userId) {
        out->current = &set->root;
        return;
    }
    out->current = node;
}

LobbyUserIdSetNode *LobbyUserIdSet_LowerBound(LobbyUserIdSet *set, const int *key, LobbyUserIdSetNode *node, LobbyUserIdSetNode *best) {
    while (node != NULL) {
        if (node->userId >= *key) {
            best = node;
            node = node->left;
        } else {
            node = node->right;
        }
    }
    return best;
}

BOOL LobbyUserMap_EraseKey(LobbyUserMap *map, int *key) {
    Iter it;
    Iter res;
    Iter tmp;
    LobbyUserMap_Find(&it, map, key);
    if (it.current == &map->root) {
        return FALSE;
    }
    tmp.current = it.current;
    LobbyUserMap_Erase(&res, map, tmp);
    return TRUE;
}

void LobbyUserMap_Find(Iter *out, LobbyUserMap *map, int *key) {
    LobbyUserMapNode *node = LobbyUserMap_LowerBound(map, key, map->root, (LobbyUserMapNode *)&map->root);
    if (node == (LobbyUserMapNode *)&map->root || *key < node->entry.userId) {
        out->current = &map->root;
        return;
    }
    out->current = node;
}

LobbyUserMapNode *LobbyUserMap_LowerBound(LobbyUserMap *map, int *key, LobbyUserMapNode *node, LobbyUserMapNode *best) {
    while (node != NULL) {
        if (node->entry.userId >= *key) {
            best = node;
            node = node->left;
        } else {
            node = node->right;
        }
    }
    return best;
}

BOOL LobbyChat_RemoveChannelUser(LobbyChatManager *manager, Str *nick, Str *channel) {
    LobbyChannelMap *channels = &manager->channelMap;
    int id;
    Iter it;
    id = LobbyChat_GetUserIdFromNick(nick);
    if (id == -1) {
        return FALSE;
    }
    LobbyChannelMap_Find(&it, channels, channel);
    if (it.current == &channels->root) {
        return FALSE;
    }
    if (!LobbyUserIdSet_EraseKey(&((LobbyChannelMapNode *)it.current)->entry.channel.users, &id)) {
        return FALSE;
    }
    LobbyChat_RemoveUserIfUnused(manager, id);
    return TRUE;
}

int LobbyUserIdSet_EraseKey(LobbyUserIdSet *set, const int *key) {
    Iter it, out;
    LobbyUserIdSet_Find(&it, set, key);
    if (it.current == &set->root) {
        return 0;
    }
    LobbyUserIdSet_Erase(&out, set, (Iterator) { it.current });
    return 1;
}
