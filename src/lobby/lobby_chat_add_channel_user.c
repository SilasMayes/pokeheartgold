#include "global.h"

#include "dwc/net_common_internal.h"

#include <nitro/code32.h>

#include "lobby_chat_internal.h"

void LobbyChannelMap_MakeEntry(LobbyChannelMapEntry *dst, Str *name, LobbyChannel *src) {
    LobbyString_InitCopy(&dst->name, name);
    dst->channel.usersEnumerated = src->usersEnumerated;
    dst->channel.users.count = 0;
    dst->channel.users.root = NULL;
    dst->channel.users.first = (LobbyUserIdSetNode *)&dst->channel.users.root;
    LobbyUserIdSet_Assign(&dst->channel.users, &src->users);
    dst->channel.userLimit = src->userLimit;
    dst->channel.callbacks = src->callbacks;
}

LobbyChannelCallbacks *LobbyChat_GetChannelCallbacks(LobbyChatManager *manager, Str *key) {
    LobbyChannelMap *channels = &manager->channelMap;
    Iter it;
    LobbyChannelMapNode *node;
    LobbyChannelMap_Find(&it, channels, key);
    node = it.current;
    return node == (LobbyChannelMapNode *)&channels->root ? NULL : &node->entry.channel.callbacks;
}

void LobbyChannelMap_Find(Iter *out, LobbyChannelMap *map, Str *key) {
    LobbyChannelMapNode *node = LobbyChannelMap_LowerBound(map, key, map->root, (LobbyChannelMapNode *)&map->root);
    if (node == (LobbyChannelMapNode *)&map->root || StrLess(key, &node->entry.name)) {
        out->current = &map->root;
        return;
    }
    out->current = node;
}

LobbyChannelMapNode *LobbyChannelMap_LowerBound(LobbyChannelMap *map, Str *key, LobbyChannelMapNode *node, LobbyChannelMapNode *best) {
    while (node != NULL) {
        if (!StrLess(&node->entry.name, key)) {
            best = node;
            node = node->left;
        } else {
            node = node->right;
        }
    }
    return best;
}

// Add the user to the channel's user set and record its nick; returns the user ID or -1.
int LobbyChat_AddChannelUser(LobbyChatManager *manager, Str *nick, Str *channel) {
    LobbyChannelMap *channels = &manager->channelMap;
    int id;
    Iter it;
    LobbyChannelMapNode *node;
    LobbyUserIdSetInsertResult inserted;
    LobbyTag userTag;
    LobbyTag nickTag;
    id = LobbyChat_GetUserIdFromNick(nick);
    if (id == -1) {
        return -1;
    }
    LobbyChannelMap_Find(&it, channels, channel);
    node = it.current;
    if (node == (LobbyChannelMapNode *)&channels->root) {
        return -1;
    }
    LobbyUserIdSet_Insert(&inserted, &node->entry.channel.users, &id);
    userTag = (LobbyTag) { 0 };
    nickTag = (LobbyTag) { 0 };
    LobbyString_Assign(&LobbyUserMap_GetOrInsert(&manager->userMap, &id)->nick, nick);
    return id;
}

LobbyUserMapEntry *LobbyUserMap_GetOrInsert(LobbyUserMap *map, int *key) {
    LobbyUserMapNode *pos;
    u8 insertLeft;
    u8 isLeftmost;
    LobbyUserMapNode *parent = LobbyUserMap_FindInsertPos2(map, key, &pos, &insertLeft, &isLeftmost);
    if (pos == NULL || pos->entry.userId < *key) {
        Str empty;
        LobbyUserMapEntry pair;
        LobbyUserMapNode *node;
        StrInit(&empty);
        PairInit(&pair, key, &empty);
        node = LobbyUserMap_InsertNode(map, parent, insertLeft, isLeftmost, &pair);
        LobbyString_Destroy(&pair.nick);
        LobbyString_Destroy(&empty);
        return &node->entry;
    }
    return &pos->entry;
}

LobbyUserMapNode *LobbyUserMap_FindInsertPos2(LobbyUserMap *map, int *key, LobbyUserMapNode **pos, u8 *insertLeft, u8 *isLeftmost) {
    LobbyUserMapNode *parent;
    LobbyUserMapNode *node;
    *pos = NULL;
    node = map->root;
    *insertLeft = 1;
    *isLeftmost = 1;
    parent = (LobbyUserMapNode *)&map->root;
    while (node != NULL) {
        parent = node;
        if (*key < node->entry.userId) {
            node = node->left;
            *insertLeft = 1;
        } else {
            *pos = node;
            node = node->right;
            *insertLeft = 0;
            *isLeftmost = 0;
        }
    }
    return parent;
}
