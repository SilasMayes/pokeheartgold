#include "global.h"

#include "dwc/net_common_internal.h"
#include "lobby_chat_manager.h"
#include "lobby_tree.h"

#include <nitro/code32.h>

#include "lobby_mem.h"

void *LobbyChannelMap_Destroy(LobbyChannelMap *map) {
    if (map->root) {
        LobbyChannelMap_DestroyNodes(map, map->root);
    }
    return map;
}

void LobbyUserIdSet_Insert(LobbyUserIdSetInsertResult *out, LobbyUserIdSet *set, int *key) {
    LobbyUserIdSetNode *prev;
    u8 left, first;
    LobbyUserIdSetNode *last;
    last = LobbyUserIdSet_FindInsertPos(set, key, &prev, &left, &first);
    if (!prev || prev->userId < *key) {
        out->node = LobbyUserIdSet_InsertNode(set, last, left, first, key);
        out->inserted = ov45_02255358[3];
    } else {
        out->node = prev;
        out->inserted = ov45_02255358[7];
    }
}

void LobbyUserIdSet_Erase(Iterator *out, LobbyUserIdSet *set, Iterator node) {
    LobbyUserIdSetNode *old = node.current;
    if (node.current == set->first) {
        LobbyTreeIterator_Advance(&node);
        set->first = node.current;
    }
    out->current = LobbyTree_EraseRebalance(old, set->root);
    if (old) {
        DWC_Free(0, old, 0);
    }
    set->count--;
}

void LobbyUserIdSet_Assign(LobbyUserIdSet *set, LobbyUserIdSet *other) {
    struct {
        u8 pad0;
        u8 byte;
        u8 pad[2];
        LobbyUserIdSetNode *a, *b;
        void *owner;
        LobbyUserIdSetNode *cleanup;
        LobbyUserIdSet tree;
    } frame;

    LobbyUserIdSetNode *node;
    int *userId;
    u32 flag;
    if (!other->root) {
        return;
    }
    frame.byte = 0;
    node = LobbyMem_Alloc(sizeof(LobbyUserIdSetNode));
    frame.owner = &set->root;
    frame.a = node;
    frame.b = node;
    frame.cleanup = node;
    userId = &node->userId;
    {
        LobbyUserIdSetNode *root = other->root;
        if (userId) {
            *userId = root->userId;
        }
    };
    frame.tree.count = 0;
    frame.tree.root = NULL;
    frame.tree.first = (LobbyUserIdSetNode *)&frame.tree.root;
    node = frame.cleanup;
    node->right = NULL;
    node->left = NULL;
    node->parent = (u32)&frame.tree.root | (node->parent & 1);
    flag = (other->root->parent & 1) != 0;
    node = frame.cleanup;
    if (flag) {
        node->parent |= 1;
    } else {
        node->parent &= ~1;
    }
    node = frame.cleanup;
    frame.tree.root = node;
    frame.tree.count = 1;
    frame.tree.first = node;
    {
        LobbyUserIdSetNode *root = other->root;
        frame.cleanup = NULL;
        if (root->right) {
            LobbyUserIdSet_CopyNodes(&frame.tree, node, root, 0);
        }
    }
    if (other->root->left) {
        LobbyUserIdSet_CopyNodes(&frame.tree, frame.tree.root, other->root, 1);
    }
    LobbyUserIdSet_Swap(set, &frame.tree);
    LobbyUserIdSet_Destroy2(&frame.tree);
    {
        LobbyUserIdSetNode *cleanup = frame.cleanup;
        if (cleanup) {
            DWC_Free(0, cleanup, 0);
        }
    };
}
