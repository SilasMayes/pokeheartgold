#include "global.h"

#include <nitro/code32.h>

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

void LobbyU32Vector_Reserve(LobbyU32Vector *v, u32 n) {
    LobbyU32Vector b;
    u32 *first;
    int cnt;
    b.data = NULL;
    b.size = 0;
    b.capacity = 0;
    {
        LobbyTag ta = { 0 };
        LobbyU32Vector_Allocate(&b, n, ta);
    }
    first = v->data;
    cnt = Distance(v->data, first + v->size);
    TouchTag();
    memcpy(b.data + b.size, first, cnt * sizeof(u32));
    memset(first, 0, cnt * sizeof(u32));
    b.size += cnt;
    TouchTag();
    v->size = 0;
    {
        u32 *pcap = &b.capacity;
        u32 t = v->capacity;
        v->capacity = *pcap;
        *pcap = t;
    }
    SwapPtr((void **)&v->data, (void **)&b.data);
    SwapU32(&v->size, &b.size);
    LobbyU32Vector_Destroy2(&b);
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

LobbyU32Vector *LobbyU32Vector_Destroy2(LobbyU32Vector *v) {
    if (v->data != NULL) {
        u32 n = v->size;
        LobbyTag a = { 0 };
        v->size -= n;
        if (v->data != NULL) {
            DWC_Free(0, v->data, 0);
        }
    }
    return v;
}

void LobbyU32Vector_Allocate(LobbyU32Vector *v, u32 n, LobbyTag unused) {
    if (n > 0x3FFFFFFF) {
        _ZNSt15__vector_commonILb1EE18throw_length_errorEv();
    }
    v->data = LobbyMem_Alloc(n * sizeof(u32));
    v->capacity = n;
}

u32 LobbyU32Vector_RecommendSize(LobbyU32Vector *v, u32 n) {
    u32 cap = v->capacity;
    u32 g1;
    u32 g2;
    if (n > 0x3FFFFFFF - cap) {
        _ZNSt15__vector_commonILb1EE18throw_length_errorEv();
    }
    if (cap < 0x15555555) {
        g1 = (cap + 1) * 3 / 5;
        return cap + *(n > g1 ? &n : &g1);
    }
    if (cap < 0x2AAAAAAA) {
        g2 = (cap + 1) / 2;
        return cap + *(n > g2 ? &n : &g2);
    }
    return 0x3FFFFFFF;
}

void LobbyU32Vector_AppendFillSlow(LobbyU32Vector *v, u32 n, u32 *x) {
    volatile LobbyTag t4;
    LobbyU32VectorBuffer b;
    u32 *first;
    int cnt;
    b.data = NULL;
    b.size = 0;
    b.capacity.value = 0;
    b.start = 0;
    b.capacity.allocator = &v->capacity;
    {
        u32 rec = LobbyU32Vector_RecommendSize(v, v->size + n - v->capacity);
        LobbyTag t3 = { 0 };
        t4.unused = 0;
        LobbyU32VectorBuffer_Allocate(&b, rec, t3);
    }
    b.start = v->size;
    TouchTag();
    {
        u32 *p = b.data + b.start + b.size;
        u32 i = n;
        while (i != 0) {
            *p++ = *x;
            i--;
        }
    }
    b.size += n;
    first = v->data;
    cnt = Distance(v->data, first + v->size);
    TouchTag();
    b.start -= cnt;
    memcpy(b.data + b.start, first, cnt * sizeof(u32));
    memset(first, 0, cnt * sizeof(u32));
    b.size += cnt;
    TouchTag();
    v->size = 0;
    {
        u32 *pcap = &b.capacity.value;
        u32 t = v->capacity;
        v->capacity = *pcap;
        *pcap = t;
    }
    SwapPtr((void **)&v->data, (void **)&b.data);
    SwapU32(&v->size, &b.size);
    LobbyU32VectorBuffer_Destroy(&b);
}
