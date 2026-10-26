#include "global.h"

#include "dwc/net_common_internal.h"
#include "lobby_tree.h"

#include <nitro/code32.h>

#include "lobby_mem.h"

extern int printf(const char *, ...);
extern void abort(void);

extern u8 ov45_02255358[];
extern char gLobbyStr_TreeInsertLengthError_4[];

LobbyUserIdSetNode *LobbyUserIdSet_InsertNode(LobbyUserIdSet *set, LobbyUserIdSetNode *parent, int left, int last, const int *key) {
    struct {
        u8 byte;
        u8 pad[3];
        LobbyUserIdSetNode *a, *b;
        void *owner;
        LobbyUserIdSetNode *volatile cleanup;
    } frame;

    LobbyUserIdSetNode *node;
    int *userId;
    u32 *link;
    if (set->count == -1) {
        printf(gLobbyStr_TreeInsertLengthError_4);
        abort();
    }
    frame.byte = 0;
    node = LobbyMem_Alloc(sizeof(LobbyUserIdSetNode));
    frame.owner = &set->root;
    userId = &node->userId;
    frame.cleanup = node;
    frame.a = node;
    if (userId) {
        *userId = *key;
    }
    node->right = 0;
    frame.cleanup = 0;
    node->left = 0;
    link = &node->parent;
    if (link) {
        *link = (u32)parent;
    }
    if (left) {
        parent->left = node;
    } else {
        parent->right = node;
    }
    set->count++;
    frame.b = node;
    LobbyTree_InsertRebalance(node, set->root);
    if (last) {
        set->first = node;
    }
    {
        LobbyUserIdSetNode *cleanup = frame.cleanup;
        if (cleanup) {
            DWC_Free(0, cleanup, 0);
        }
    };
    return node;
}

void *LobbyUserIdSet_Destroy(LobbyUserIdSet *set) {
    if (set->root) {
        LobbyUserIdSet_DestroyNodes(set, set->root);
    }
    return set;
}

void LobbyUserMap_Insert(LobbyUserMapInsertResult *out, LobbyUserMap *map, LobbyUserMapEntry *entry) {
    LobbyUserMapNode *prev;
    u8 left, first;
    LobbyUserMapNode *last;
    last = LobbyUserMap_FindInsertPos(map, &entry->userId, &prev, &left, &first);
    if (!prev || prev->entry.userId < entry->userId) {
        out->node = LobbyUserMap_InsertNode(map, last, left, first, entry);
        out->inserted = ov45_02255358[0];
    } else {
        out->node = prev;
        out->inserted = ov45_02255358[1];
    }
}

void LobbyUserMap_Erase(Iterator *out, LobbyUserMap *map, Iterator node) {
    LobbyUserMapNode *old = node.current;
    if (old == map->first) {
        LobbyTreeIterator_Advance(&node);
        map->first = node.current;
    }
    out->current = LobbyTree_EraseRebalance(old, map->root);
    LobbyString_Destroy(&old->entry.nick);
    if (old) {
        DWC_Free(0, old, 0);
    }
    map->count--;
}

LobbyUserMapNode *LobbyUserMap_InsertNode(LobbyUserMap *map, LobbyUserMapNode *parent, int left, int first, LobbyUserMapEntry *entry) {
    struct {
        u8 flag;
        LobbyUserMapNode *a, *b;
        LobbyUserMapNode **root;
        LobbyUserMapNode *volatile owned;
    } guard;

    LobbyUserMapNode *node, *owned;
    LobbyUserMapEntry *dest;
    u32 *link;
    if (map->count == -1) {
        printf(gLobbyStr_TreeInsertLengthError_4);
        abort();
    }
    guard.flag = 0;
    node = LobbyMem_Alloc(sizeof(LobbyUserMapNode));
    guard.a = node;
    guard.b = node;
    guard.root = &map->root;
    guard.owned = node;
    dest = &node->entry;
    if (dest) {
        dest->userId = entry->userId;
        LobbyString_InitCopy(&dest->nick, &entry->nick);
    }
    node = guard.owned;
    node->right = 0;
    guard.owned = 0;
    node->left = 0;
    link = &node->parent;
    if (link) {
        *link = (u32)parent;
    }
    if (left) {
        parent->left = node;
    } else {
        parent->right = node;
    }
    map->count++;
    LobbyTree_InsertRebalance(node, map->root);
    if (first) {
        map->first = node;
    }
    owned = guard.owned;
    if (owned) {
        DWC_Free(0, owned, 0);
    }
    return node;
}
