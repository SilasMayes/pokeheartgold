#include "global.h"

#include <nitro/code32.h>

#include "ppw_lobby_internal.h"

void PPWLobbyPlayerSet_Insert(InsertResult *out, List *l, Session **key) {
    Node *parent;
    u8 left;
    u8 flag;
    Node *y = PPWLobbyPlayerSet_FindInsertPos(l, key, &parent, &left, &flag);
    if (parent == NULL || parent->val->id < (*key)->id) {
        out->current = PPWLobbyPlayerSet_InsertNode(l, y, left, flag, key);
        out->inserted = ov45_02255200[0];
        return;
    }
    out->current = parent;
    out->inserted = ov45_02255200[1];
}

void PPWLobbyPlayerSet_Erase(NodeIter *out, List *l, NodeIter it) {
    Node *n = it.current;
    if (n == l->leftmost) {
        LobbyTreeIterator_Advance(&it);
        l->leftmost = it.current;
    }
    out->current = LobbyTree_EraseRebalance(n, l->root);
    if (n != NULL) {
        DWC_Free(0, n, 0);
    }
    l->count--;
}

Node *PPWLobbyPlayerSet_InsertNode(List *l, Node *parent, u8 left, u8 flag, Session **key) {
    Node *n;
    Node *tmp;
    Session **pv;
    u32 *pp;

    volatile struct {
        Node *a;
        Node *b;
        void **c;
        Node *d;
    } h;

    if (l->count == (u32)-1) {
        printf(gLobbyStr_TreeInsertLengthError_2);
        abort();
    }
    {
        LobbyTag t = { 0 };
    }
    n = LobbyMem_Alloc(sizeof(Node));
    h.c = &l->root;
    pv = &n->val;
    h.d = n;
    h.a = n;
    if (pv != NULL) {
        *pv = *key;
    }
    n->right = NULL;
    h.d = NULL;
    n->left = NULL;
    pp = &n->parent;
    if (pp != NULL) {
        *pp = (u32)parent;
    }
    if (left) {
        parent->left = n;
    } else {
        parent->right = n;
    }
    l->count++;
    h.b = n;
    LobbyTree_InsertRebalance(n, l->root);
    if (flag) {
        l->leftmost = n;
    }
    tmp = h.d;
    if (tmp != NULL) {
        DWC_Free(0, tmp, 0);
    }
    return n;
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

Node *PPWLobbyPlayerSet_FindInsertPos(List *l, Session **key, Node **parent, u8 *left, u8 *flag) {
    Node *y;
    Node *x;
    *parent = NULL;
    x = l->root;
    *left = 1;
    *flag = 1;
    y = (Node *)&l->root;
    while (x != NULL) {
        y = x;
        if ((*key)->id < x->val->id) {
            x = x->left;
            *left = 1;
        } else {
            *parent = x;
            x = x->right;
            *left = 0;
            *flag = 0;
        }
    }
    return y;
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
