#include "global.h"

#include "dwc/net_common_internal.h"

#include "lobby_chat_manager.h"

#include <nitro/code32.h>
#define P(p, o) (*(void **)((char *)(p) + (o)))

extern void __msl_assertion_failed(char *, char *, char *, int);
extern char gLobbyStr_DataNeNULL[];
extern char gLobbyStr_ChatCallbacksC[];
extern char gLobbyStr_ciCallbacksArrayElementFreeFn[];
extern void ciCallbacksArrayElementFreeFn(void *p);

void *LobbyUserMap_Destroy(LobbyUserMap *map) {
    if (map->root) {
        LobbyUserMap_DestroyNodes(map, map->root);
    }
    return map;
}

void *LobbyRequestMap_Destroy(LobbyRequestMap *map) {
    if (map->root) {
        LobbyRequestMap_DestroyNodes(map, map->root);
    }
    return map;
}

LobbyChannelMapNode *LobbyChannelMap_FindInsertPos(LobbyChannelMap *map, Str *key, LobbyChannelMapNode **found, u8 *left, u8 *empty) {
    LobbyChannelMapNode *parent;
    LobbyChannelMapNode *node;
    _Bool comparison;
    *found = NULL;
    node = map->root;
    *left = 1;
    *empty = 1;
    parent = (LobbyChannelMapNode *)&map->root;
    while (node) {
        parent = node;
        comparison = LobbyString_Compare(key, &node->entry.name) < 0;
        if (comparison) {
            node = node->left;
            *left = 1;
        } else {
            *found = node;
            node = node->right;
            *left = 0;
            *empty = 0;
        }
    }
    return parent;
}

LobbyUserIdSetNode *LobbyUserIdSet_FindInsertPos(LobbyUserIdSet *set, int *key, LobbyUserIdSetNode **prev, u8 *left, u8 *first) {
    LobbyUserIdSetNode *node, *last;
    *prev = NULL;
    node = set->root;
    *left = 1;
    *first = 1;
    last = (LobbyUserIdSetNode *)&set->root;
    while (node) {
        last = node;
        if (*key < node->userId) {
            node = node->left;
            *left = 1;
        } else {
            *prev = node;
            node = node->right;
            *left = 0;
            *first = 0;
        }
    }
    return last;
}

LobbyUserMapNode *LobbyUserMap_FindInsertPos(LobbyUserMap *map, int *key, LobbyUserMapNode **prev, u8 *left, u8 *first) {
    LobbyUserMapNode *node, *last;
    *prev = NULL;
    node = map->root;
    *left = 1;
    *first = 1;
    last = (LobbyUserMapNode *)&map->root;
    while (node) {
        last = node;
        if (*key < node->entry.userId) {
            node = node->left;
            *left = 1;
        } else {
            *prev = node;
            node = node->right;
            *left = 0;
            *first = 0;
        }
    }
    return last;
}

void LobbyChannelMap_DestroyNodes(LobbyChannelMap *map, LobbyChannelMapNode *node) {
    if (node->left) {
        LobbyChannelMap_DestroyNodes(map, node->left);
    }
    if (node->right) {
        LobbyChannelMap_DestroyNodes(map, node->right);
    }
    LobbyUserIdSet_Destroy(&node->entry.channel.users);
    LobbyString_Destroy(&node->entry.name);
    if (node) {
        DWC_Free(0, node, 0);
    }
}

void *LobbyUserIdSet_Destroy2(LobbyUserIdSet *set) {
    if (set->root) {
        LobbyUserIdSet_DestroyNodes(set, set->root);
    }
    return set;
}

void LobbyUserIdSet_Swap(LobbyUserIdSet *set, LobbyUserIdSet *other) {
    int count;
    LobbyUserIdSetNode *node;
    if (set == other) {
        return;
    }
    count = set->count;
    set->count = other->count;
    other->count = count;
    node = set->root;
    set->root = other->root;
    other->root = node;
    node = set->first;
    set->first = other->first;
    other->first = node;
    if (!set->root) {
        set->first = (LobbyUserIdSetNode *)&set->root;
    } else {
        set->root->parent = (u32)&set->root | (set->root->parent & 1);
    }
    if (!other->root) {
        other->first = (LobbyUserIdSetNode *)&other->root;
    } else {
        other->root->parent = (u32)&other->root | (other->root->parent & 1);
    }
}

void LobbyUserIdSet_DestroyNodes(LobbyUserIdSet *set, LobbyUserIdSetNode *node) {
    if (node->left) {
        LobbyUserIdSet_DestroyNodes(set, node->left);
    }
    if (node->right) {
        LobbyUserIdSet_DestroyNodes(set, node->right);
    }
    if (node) {
        DWC_Free(0, node, 0);
    }
}

void LobbyUserMap_DestroyNodes(LobbyUserMap *map, LobbyUserMapNode *node) {
    if (node->left) {
        LobbyUserMap_DestroyNodes(map, node->left);
    }
    if (node->right) {
        LobbyUserMap_DestroyNodes(map, node->right);
    }
    LobbyString_Destroy(&node->entry.nick);
    if (node) {
        DWC_Free(0, node, 0);
    }
}

void LobbyRequestMap_DestroyNodes(LobbyRequestMap *map, LobbyRequestMapNode *node) {
    if (node->left) {
        LobbyRequestMap_DestroyNodes(map, node->left);
    }
    if (node->right) {
        LobbyRequestMap_DestroyNodes(map, node->right);
    }
    if (node) {
        DWC_Free(0, node, 0);
    }
}

void ciCallbacksArrayElementFreeFn(void *p) {
    if (!p) {
        __msl_assertion_failed(gLobbyStr_DataNeNULL, gLobbyStr_ChatCallbacksC, gLobbyStr_ciCallbacksArrayElementFreeFn, 164);
    }
    DWCi_GsFree(P(p, 20));
}
