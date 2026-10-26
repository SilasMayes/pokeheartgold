#ifndef POKEHEARTGOLD_LOBBY_TREE_H
#define POKEHEARTGOLD_LOBBY_TREE_H

// The red-black trees behind the lobby's user id sets and user maps. A tree keeps its node count, its
// root and its leftmost node. The root field is also the tree's end node: end() points at it and the root's parent
// is its address. A node's parent field holds the parent's address with the node's colour in bit 0 (set: red).

#include <nitro/types.h>

#include "lobby_string.h"

#include "../lib/NitroDWC/src/tree-iterator4.h"

typedef struct LobbyUserIdSetNode {
    struct LobbyUserIdSetNode *left;
    struct LobbyUserIdSetNode *right;
    u32 parent;
    int userId;
} LobbyUserIdSetNode;

typedef struct LobbyUserIdSet {
    int count;
    LobbyUserIdSetNode *root;
    LobbyUserIdSetNode *first;
} LobbyUserIdSet;

typedef struct LobbyUserIdSetInsertResult {
    LobbyUserIdSetNode *node;
    u8 inserted;
} LobbyUserIdSetInsertResult;

// The user map: user id -> nickname.
typedef struct LobbyUserMapEntry {
    int userId;
    Str nick;
} LobbyUserMapEntry;

typedef struct LobbyUserMapNode {
    struct LobbyUserMapNode *left;
    struct LobbyUserMapNode *right;
    u32 parent;
    LobbyUserMapEntry entry;
} LobbyUserMapNode;

typedef struct LobbyUserMap {
    int count;
    LobbyUserMapNode *root;
    u8 padding_08[4];
    LobbyUserMapNode *first;
} LobbyUserMap;

typedef struct LobbyUserMapInsertResult {
    LobbyUserMapNode *node;
    u8 inserted;
} LobbyUserMapInsertResult;

#ifdef __cplusplus
extern "C" {
#endif

void LobbyUserIdSet_Assign(LobbyUserIdSet *set, LobbyUserIdSet *other);
void LobbyUserIdSet_CopyNodes(LobbyUserIdSet *set, LobbyUserIdSetNode *parent, LobbyUserIdSetNode *src, BOOL left);
void *LobbyUserIdSet_Destroy(LobbyUserIdSet *set);
void *LobbyUserIdSet_Destroy2(LobbyUserIdSet *set);
void LobbyUserIdSet_DestroyNodes(LobbyUserIdSet *set, LobbyUserIdSetNode *node);
void LobbyUserIdSet_Erase(Iterator *out, LobbyUserIdSet *set, Iterator node);
int LobbyUserIdSet_EraseKey(LobbyUserIdSet *set, const int *key);
void LobbyUserIdSet_Find(Iterator *out, LobbyUserIdSet *set, const int *key);
LobbyUserIdSetNode *LobbyUserIdSet_FindInsertPos(LobbyUserIdSet *set, int *key, LobbyUserIdSetNode **prev, u8 *left, u8 *first);
void LobbyUserIdSet_Insert(LobbyUserIdSetInsertResult *out, LobbyUserIdSet *set, int *key);
LobbyUserIdSetNode *LobbyUserIdSet_InsertNode(LobbyUserIdSet *set, LobbyUserIdSetNode *parent, int left, int last, const int *key);
void LobbyUserIdSet_Swap(LobbyUserIdSet *, LobbyUserIdSet *);
void *LobbyUserMap_Destroy(LobbyUserMap *map);
BOOL LobbyUserMap_EraseKey(LobbyUserMap *map, int *key);
void LobbyUserMap_DestroyNodes(LobbyUserMap *map, LobbyUserMapNode *node);
void LobbyUserMap_Erase(Iterator *out, LobbyUserMap *map, Iterator node);
LobbyUserMapNode *LobbyUserMap_FindInsertPos(LobbyUserMap *map, int *key, LobbyUserMapNode **prev, u8 *left, u8 *first);
void LobbyUserMap_Insert(LobbyUserMapInsertResult *out, LobbyUserMap *map, LobbyUserMapEntry *entry);
LobbyUserMapNode *LobbyUserMap_InsertNode(LobbyUserMap *map, LobbyUserMapNode *parent, int left, int first, LobbyUserMapEntry *entry);

#ifdef __cplusplus
}
#endif

// The rebalancing shared by every lobby tree, after a node is linked in or before one is unlinked; root is the
// tree's root field.
#ifndef __cplusplus
void LobbyTree_InsertRebalance(void *node, void *root);
void *LobbyTree_EraseRebalance(void *node, void *root);
#endif

// The flags the tree inserts report, and the error they print when a tree is full.
#ifndef __cplusplus
extern u8 ov45_02255358[];
extern char gLobbyStr_TreeInsertLengthError_3[];
extern char gLobbyStr_TreeInsertLengthError_4[];
int printf(const char *, ...);
void abort(void);
#endif

#endif // POKEHEARTGOLD_LOBBY_TREE_H
