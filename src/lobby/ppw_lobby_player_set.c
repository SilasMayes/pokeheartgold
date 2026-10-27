#include "global.h"

#include "dwc/net_common_internal.h"

#include <nitro/code32.h>

#include "lobby_mem.h"
#include "ppw_lobby_internal.h"

void PPWLobbyPlayerSet_Insert(PPWLobbyPlayerSetInsertResult *out, PPWLobbyPlayerSet *set, PPWLobbyPlayer **key) {
    PPWLobbyPlayerSetNode *parent;
    u8 left;
    u8 leftmost;
    PPWLobbyPlayerSetNode *position = PPWLobbyPlayerSet_FindInsertPos(set, key, &parent, &left, &leftmost);
    if (parent == NULL || parent->player->id < (*key)->id) {
        out->node = PPWLobbyPlayerSet_InsertNode(set, position, left, leftmost, key);
        out->inserted = ov45_02255200[0];
        return;
    }
    out->node = parent;
    out->inserted = ov45_02255200[1];
}

void PPWLobbyPlayerSet_Erase(Iterator *out, PPWLobbyPlayerSet *set, Iterator position) {
    PPWLobbyPlayerSetNode *node = position.current;
    if (node == set->leftmost) {
        LobbyTreeIterator_Advance(&position);
        set->leftmost = position.current;
    }
    out->current = LobbyTree_EraseRebalance(node, set->root);
    if (node != NULL) {
        DWC_Free(0, node, 0);
    }
    set->count--;
}

PPWLobbyPlayerSetNode *PPWLobbyPlayerSet_InsertNode(PPWLobbyPlayerSet *set, PPWLobbyPlayerSetNode *parent, u8 left, u8 leftmost, PPWLobbyPlayer **key) {
    PPWLobbyPlayerSetNode *node;
    PPWLobbyPlayerSetNode *pending;
    PPWLobbyPlayer **player;
    u32 *parentField;

    volatile struct {
        PPWLobbyPlayerSetNode *node;
        PPWLobbyPlayerSetNode *inserted;
        PPWLobbyPlayerSetNode **root;
        PPWLobbyPlayerSetNode *pending;
    } holder;

    if (set->count == (u32)-1) {
        printf(gLobbyStr_TreeInsertLengthError_2);
        abort();
    }
    {
        LobbyTag tag = { 0 };
    }
    node = LobbyMem_Alloc(sizeof(PPWLobbyPlayerSetNode));
    holder.root = &set->root;
    player = &node->player;
    holder.pending = node;
    holder.node = node;
    if (player != NULL) {
        *player = *key;
    }
    node->right = NULL;
    holder.pending = NULL;
    node->left = NULL;
    parentField = &node->parent;
    if (parentField != NULL) {
        *parentField = (u32)parent;
    }
    if (left) {
        parent->left = node;
    } else {
        parent->right = node;
    }
    set->count++;
    holder.inserted = node;
    LobbyTree_InsertRebalance(node, set->root);
    if (leftmost) {
        set->leftmost = node;
    }
    pending = holder.pending;
    if (pending != NULL) {
        DWC_Free(0, pending, 0);
    }
    return node;
}

static inline int Distance(const u32 *first, const u32 *last) {
    return last - first;
}

void LobbyU32Vector_Reserve(LobbyU32Vector *vector, u32 capacity) {
    LobbyU32Vector buffer;
    u32 *first;
    int moved;
    buffer.data = NULL;
    buffer.size = 0;
    buffer.capacity = 0;
    {
        LobbyTag tag = { 0 };
        LobbyU32Vector_Allocate(&buffer, capacity, tag);
    }
    first = vector->data;
    moved = Distance(vector->data, first + vector->size);
    TouchTag();
    memcpy(buffer.data + buffer.size, first, moved * sizeof(u32));
    memset(first, 0, moved * sizeof(u32));
    buffer.size += moved;
    TouchTag();
    vector->size = 0;
    {
        u32 *bufferCapacity = &buffer.capacity;
        u32 oldCapacity = vector->capacity;
        vector->capacity = *bufferCapacity;
        *bufferCapacity = oldCapacity;
    }
    SwapPtr((void **)&vector->data, (void **)&buffer.data);
    SwapU32(&vector->size, &buffer.size);
    LobbyU32Vector_Destroy2(&buffer);
}

void LobbyU32Vector_PushBackSlow(LobbyU32Vector *v, u32 *x, LobbyTag unused) {
    TouchTag();
    LobbyU32Vector_RecommendSize(v, 1);
    LobbyU32Vector_AppendFillSlow(v, 1, x);
}

PPWLobbyPlayerSetNode *PPWLobbyPlayerSet_FindInsertPos(PPWLobbyPlayerSet *set, PPWLobbyPlayer **key, PPWLobbyPlayerSetNode **parent, u8 *left, u8 *leftmost) {
    PPWLobbyPlayerSetNode *position;
    PPWLobbyPlayerSetNode *node;
    *parent = NULL;
    node = set->root;
    *left = 1;
    *leftmost = 1;
    position = (PPWLobbyPlayerSetNode *)&set->root;
    while (node != NULL) {
        position = node;
        if ((*key)->id < node->player->id) {
            node = node->left;
            *left = 1;
        } else {
            *parent = node;
            node = node->right;
            *left = 0;
            *leftmost = 0;
        }
    }
    return position;
}

LobbyU32Vector *LobbyU32Vector_Destroy2(LobbyU32Vector *vector) {
    if (vector->data != NULL) {
        u32 count = vector->size;
        LobbyTag tag = { 0 };
        vector->size -= count;
        if (vector->data != NULL) {
            DWC_Free(0, vector->data, 0);
        }
    }
    return vector;
}

void LobbyU32Vector_Allocate(LobbyU32Vector *vector, u32 capacity, LobbyTag unused) {
    if (capacity > 0x3FFFFFFF) {
        _ZNSt15__vector_commonILb1EE18throw_length_errorEv();
    }
    vector->data = LobbyMem_Alloc(capacity * sizeof(u32));
    vector->capacity = capacity;
}

u32 LobbyU32Vector_RecommendSize(LobbyU32Vector *vector, u32 extra) {
    u32 capacity = vector->capacity;
    u32 growth;
    u32 half;
    if (extra > 0x3FFFFFFF - capacity) {
        _ZNSt15__vector_commonILb1EE18throw_length_errorEv();
    }
    if (capacity < 0x15555555) {
        growth = (capacity + 1) * 3 / 5;
        return capacity + *(extra > growth ? &extra : &growth);
    }
    if (capacity < 0x2AAAAAAA) {
        half = (capacity + 1) / 2;
        return capacity + *(extra > half ? &extra : &half);
    }
    return 0x3FFFFFFF;
}

void LobbyU32Vector_AppendFillSlow(LobbyU32Vector *vector, u32 count, u32 *value) {
    volatile LobbyTag t4;
    LobbyU32VectorBuffer buffer;
    u32 *first;
    int moved;
    buffer.data = NULL;
    buffer.size = 0;
    buffer.capacity.value = 0;
    buffer.start = 0;
    buffer.capacity.allocator = &vector->capacity;
    {
        u32 newCapacity = LobbyU32Vector_RecommendSize(vector, vector->size + count - vector->capacity);
        LobbyTag t3 = { 0 };
        t4.unused = 0;
        LobbyU32VectorBuffer_Allocate(&buffer, newCapacity, t3);
    }
    buffer.start = vector->size;
    TouchTag();
    {
        u32 *dst = buffer.data + buffer.start + buffer.size;
        u32 remaining = count;
        while (remaining != 0) {
            *dst++ = *value;
            remaining--;
        }
    }
    buffer.size += count;
    first = vector->data;
    moved = Distance(vector->data, first + vector->size);
    TouchTag();
    buffer.start -= moved;
    memcpy(buffer.data + buffer.start, first, moved * sizeof(u32));
    memset(first, 0, moved * sizeof(u32));
    buffer.size += moved;
    TouchTag();
    vector->size = 0;
    {
        u32 *bufferCapacity = &buffer.capacity.value;
        u32 oldCapacity = vector->capacity;
        vector->capacity = *bufferCapacity;
        *bufferCapacity = oldCapacity;
    }
    SwapPtr((void **)&vector->data, (void **)&buffer.data);
    SwapU32(&vector->size, &buffer.size);
    LobbyU32VectorBuffer_Destroy(&buffer);
}
