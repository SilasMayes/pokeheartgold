#include "global.h"

#include "ppw_lobby_internal.h"
#include "lobby_event_deque.h"

#include <nitro/code32.h>

void LobbyEventDequeMap_Allocate(LobbyEventDequeMap *map, u32 n, LobbyTag unused) {
    if (!(gLobbyEventDequeMapMaxSizeSet & 1)) {
        gLobbyEventDequeMapMaxSize = 0x3FFFFFFE;
        gLobbyEventDequeMapMaxSizeSet |= 1;
    }
    if (n > gLobbyEventDequeMapMaxSize) {
        LobbyEventDequeMap_LengthError();
    }
    map->blocks = LobbyMem_Alloc((n + 1) * sizeof(LobbyEvent *));
    map->capacity = n + 1;
}

LobbyEventDequeMapIterator *LobbyEventDequeMapIterator_Advance2(LobbyEventDequeMapIterator *it, int n) {
    int size = it->last - it->first;
    n += it->cur - it->first;
    if (n < 0) {
        n += size;
    } else if (n >= size) {
        n -= size;
    }
    it->cur = it->first + n;
    return it;
}

int LobbyEventDequeMapIterator_Distance2(const LobbyEventDequeMapIterator *x, const LobbyEventDequeMapIterator *y) {
    int n;
    LobbyEvent **m = x->mid;
    n = x->cur - y->cur;
    if (x->cur >= m) {
        if (y->cur < m) {
            n -= x->last - x->first;
        }
    } else {
        if (y->cur >= m) {
            n += x->last - x->first;
        }
    }
    return n;
}
