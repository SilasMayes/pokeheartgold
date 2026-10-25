#include "global.h"

#include "dwc/net_common_internal.h"

#include "ppw_lobby_work.h"

#include <nitro/code32.h>
#include <stdarg.h>

typedef union S {
    struct {
        u32 flag : 1;
        u32 cap : 31;
        u32 len;
        char *ptr;
    } l;

    struct {
        u8 flag : 1;
        u8 len : 7;
        char data[11];
    } s;
} S;

typedef struct Vec {
    S *data;
    u32 len, cap, z, extra;
} Vec;

extern void _ZNSt15__vector_commonILb1EE18throw_length_errorEv(void);
#include "overlay45_string_search.h"
u32 LobbyStringVector_RecommendSize(Vec *p, u32 n, ...);

void PPWLobbyPlayerSet_DestroyNodes(PPWLobbyPlayerSet *set, PPWLobbyPlayerSetNode *node) {
    if (node->left) {
        PPWLobbyPlayerSet_DestroyNodes(set, node->left);
    }
    if (node->right) {
        PPWLobbyPlayerSet_DestroyNodes(set, node->right);
    }
    if (node) {
        DWC_Free(0, node, 0);
    }
}

u32 LobbyStringVector_RecommendSize(Vec *p, u32 n, ...) {
    u32 cap = p->cap, a, b;
    va_list ap;
    va_start(ap, n);
    va_end(ap);
    if (n > 0x15555555 - cap) {
        _ZNSt15__vector_commonILb1EE18throw_length_errorEv();
    }
    if (cap < 0x071c71c7) {
        a = (cap + 1) * 3 / 5;
        return cap + *(n > a ? &n : &a);
    }
    if (cap < 0x0e38e38e) {
        b = (cap + 1) / 2;
        return cap + *(n > b ? &n : &b);
    }
    return 0x15555555;
}
