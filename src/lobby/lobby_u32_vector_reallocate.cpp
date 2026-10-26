#include <nitro/types.h>

#include "lobby_vector.h"

#include <nitro/code32.h>

extern "C" void DWC_Free(int, void *, u32);

struct Alloc {
    void release(u32 *p) {
        if (p) {
            DWC_Free(0, p, 0);
        }
    }
};

void LobbyU32Vector_Reallocate(LobbyU32Vector *v, u32 unused, u32 cap) {
    u32 n = v->size;
    Alloc a = Alloc();
    v->size -= n;
    if (v->data) {
        a.release(v->data);
        v->data = NULL;
        v->capacity = 0;
    }
    LobbyU32Vector_Allocate(v, cap, LobbyTag(LobbyTag()));
}
