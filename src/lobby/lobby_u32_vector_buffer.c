#include "global.h"

#include "dwc/net_common_internal.h"
#include "ppw_lobby_internal.h"

#include <nitro/code32.h>

static LobbyU32VectorBuffer *LobbyU32VectorBuffer_Deallocate(LobbyU32VectorBuffer *buffer);

LobbyU32VectorBuffer *LobbyU32VectorBuffer_Destroy(LobbyU32VectorBuffer *buffer) {
    buffer->size = 0;
    LobbyU32VectorBuffer_Deallocate(buffer);
    return buffer;
}

void LobbyU32VectorBuffer_Allocate(LobbyU32VectorBuffer *buffer, u32 capacity, LobbyTag unused) {
    if (capacity > 0x3fffffff) {
        _ZNSt15__vector_commonILb1EE18throw_length_errorEv();
    }
    buffer->data = LobbyMem_Alloc(capacity * sizeof(u32));
    buffer->capacity.value = capacity;
}

static LobbyU32VectorBuffer *LobbyU32VectorBuffer_Deallocate(LobbyU32VectorBuffer *buffer) {
    if (buffer->data) {
        u32 old = buffer->size;

        struct {
            u8 zero;
        } init = { 0 };

        buffer->size -= old;
        if (buffer->data) {
            DWC_Free(0, buffer->data, 0);
        }
    }
    return buffer;
}
