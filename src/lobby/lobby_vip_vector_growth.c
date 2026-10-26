#include "global.h"

#include "dwc/net_common_internal.h"

#include "ppw_lobby_work.h"

#include <nitro/code32.h>
#include "ppw_lobby_internal.h"


void LobbyVipVector_Reallocate(PPWLobbyVipVector *vector, u32 unused, u32 capacity) {
    u32 size = vector->size;
    LobbyTag old = { 0 };
    volatile LobbyTag copy;
    (void)old;
    vector->size -= size;
    if (vector->data) {
        if (vector->data) {
            DWC_Free(0, vector->data, 0);
        }
        vector->data = NULL;
        vector->capacity = 0;
    }
    LobbyTag fresh = { 0 };
    copy.unused = 0;
    LobbyVipVector_Allocate(vector, capacity, fresh);
}

u32 LobbyVipVector_RecommendSize(PPWLobbyVipVector *vector, u32 extra) {
    u32 capacity = vector->capacity, growth, half;
    if (extra > 0x1fffffff - capacity) {
        _ZNSt15__vector_commonILb1EE18throw_length_errorEv();
    }
    if (capacity < 0xaaaaaaa) {
        growth = (capacity + 1) * 3 / 5;
        return capacity + *(extra > growth ? &extra : &growth);
    }
    if (capacity < 0x15555554) {
        half = (capacity + 1) / 2;
        return capacity + *(extra > half ? &extra : &half);
    }
    return 0x1fffffff;
}
