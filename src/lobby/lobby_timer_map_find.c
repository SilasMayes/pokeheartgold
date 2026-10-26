#include "global.h"

#include <nitro/code32.h>

#include "lobby_timer.h"

void LobbyTimerMap_Find(LobbyTimerMapNode **out, LobbyTimerMap *map, u32 *key) {
    LobbyTimerMapNode *node = LobbyTimerMap_LowerBound(map, key, map->root, (LobbyTimerMapNode *)&map->root);
    if (node == (LobbyTimerMapNode *)&map->root || *key < node->id) {
        *out = (LobbyTimerMapNode *)&map->root;
    } else {
        *out = node;
    }
}

LobbyTimerMapNode *LobbyTimerMap_LowerBound(LobbyTimerMap *map, u32 *key, LobbyTimerMapNode *node, LobbyTimerMapNode *best) {
    if (node) {
        u32 id = *key;
        do {
            if (node->id >= id) {
                best = node;
                node = node->left;
            } else {
                node = node->right;
            }
        } while (node);
    }
    return best;
}
