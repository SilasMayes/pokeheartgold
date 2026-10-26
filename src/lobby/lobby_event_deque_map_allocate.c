#include "global.h"

#include "ppw_lobby_internal.h"
#include "lobby_event_deque.h"

#include <nitro/code32.h>

void LobbyEventDequeMap_Allocate(LobbyEventDequeMap *map, u32 capacity, LobbyTag unused) {
    if (!(gLobbyEventDequeMapMaxSizeSet & 1)) {
        gLobbyEventDequeMapMaxSize = 0x3FFFFFFE;
        gLobbyEventDequeMapMaxSizeSet |= 1;
    }
    if (capacity > gLobbyEventDequeMapMaxSize) {
        LobbyEventDequeMap_LengthError();
    }
    map->blocks = LobbyMem_Alloc((capacity + 1) * sizeof(LobbyEvent *));
    map->capacity = capacity + 1;
}

LobbyEventDequeMapIterator *LobbyEventDequeMapIterator_Advance2(LobbyEventDequeMapIterator *it, int offset) {
    int size = it->last - it->first;
    offset += it->cur - it->first;
    if (offset < 0) {
        offset += size;
    } else if (offset >= size) {
        offset -= size;
    }
    it->cur = it->first + offset;
    return it;
}

int LobbyEventDequeMapIterator_Distance2(const LobbyEventDequeMapIterator *it, const LobbyEventDequeMapIterator *from) {
    int count;
    LobbyEvent **mid = it->mid;
    count = it->cur - from->cur;
    if (it->cur >= mid) {
        if (from->cur < mid) {
            count -= it->last - it->first;
        }
    } else {
        if (from->cur >= mid) {
            count += it->last - it->first;
        }
    }
    return count;
}
