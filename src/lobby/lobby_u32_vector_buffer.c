#include "global.h"

#include "dwc/net_common_internal.h"
#include "ppw_lobby_internal.h"

#include <nitro/code32.h>

static LobbyU32VectorBuffer *LobbyU32VectorBuffer_Deallocate(LobbyU32VectorBuffer *b);

LobbyU32VectorBuffer *LobbyU32VectorBuffer_Destroy(LobbyU32VectorBuffer *b) {
    b->size = 0;
    LobbyU32VectorBuffer_Deallocate(b);
    return b;
}

void LobbyU32VectorBuffer_Allocate(LobbyU32VectorBuffer *b, u32 cap, LobbyTag unused) {
    if (cap > 0x3fffffff) {
        _ZNSt15__vector_commonILb1EE18throw_length_errorEv();
    }
    b->data = LobbyMem_Alloc(cap * sizeof(u32));
    b->capacity.value = cap;
}

static LobbyU32VectorBuffer *LobbyU32VectorBuffer_Deallocate(LobbyU32VectorBuffer *b) {
    if (b->data) {
        u32 old = b->size;

        struct {
            u8 zero;
        } init = { 0 };

        b->size -= old;
        if (b->data) {
            DWC_Free(0, b->data, 0);
        }
    }
    return b;
}
