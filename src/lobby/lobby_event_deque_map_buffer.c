#include "global.h"

#include "ppw_lobby_internal.h"
#include "lobby_event_deque.h"

#include <nitro/code32.h>

LobbyEventDequeMapBuffer *LobbyEventDequeMapBuffer_Destroy(LobbyEventDequeMapBuffer *buffer) {
    if (buffer->map.blocks != NULL) {
        u32 count = buffer->map.size;
        LobbyTag tag = { 0 };
        buffer->map.size -= count;
        if (buffer->map.blocks != NULL) {
            DWC_Free(0, buffer->map.blocks, 0);
        }
    }
    return buffer;
}

void LobbyEventDequeMapBuffer_Allocate(LobbyEventDequeMapBuffer *buffer, u32 capacity, LobbyTag tag) {
    if (!(gLobbyEventDequeMapBufferMaxSizeSet & 1)) {
        gLobbyEventDequeMapBufferMaxSize = 0x3FFFFFFE;
        gLobbyEventDequeMapBufferMaxSizeSet |= 1;
    }
    if (capacity > gLobbyEventDequeMapBufferMaxSize) {
        LobbyEventDequeMap_LengthError();
    }
    buffer->map.blocks = LobbyMem_Alloc((capacity + 1) * sizeof(LobbyEvent *));
    buffer->map.capacity = capacity + 1;
}

void LobbyEventDequeMapBuffer_PrependRange(LobbyEventDequeMapBuffer *buffer, const LobbyEventDequeMapIterator *first, const LobbyEventDequeMapIterator *last, LobbyTag tag) {
    LobbyEventDequeMap *map = &buffer->map;
    LobbyEvent **dst = map->blocks + map->start;
    if (first->cur <= last->cur) {
        int count = last->cur - first->cur;
        int added;
        memmove(dst - count, first->cur, count * sizeof(LobbyEvent *));
        added = last->cur - first->cur;
        map->size += added;
        map->start -= added;
    } else {
        int n1 = last->cur - last->first;
        LobbyEvent **p = dst - n1;
        int n2;
        int total;
        memmove(p, last->first, n1 * sizeof(LobbyEvent *));
        n2 = first->last - first->cur;
        memmove(p - n2, first->cur, n2 * sizeof(LobbyEvent *));
        total = (last->cur - last->first) + (first->last - first->cur);
        map->start -= total;
        map->size += total;
    }
}

void LobbyEventDequeMapBuffer_AppendRange(LobbyEventDequeMapBuffer *buffer, const LobbyEventDequeMapIterator *first, const LobbyEventDequeMapIterator *last, LobbyTag tag) {
    LobbyEventDequeMap *map = &buffer->map;
    LobbyEvent **dst = map->blocks + (map->start + map->size) % map->capacity;
    if (first->cur <= last->cur) {
        memmove(dst, first->cur, (last->cur - first->cur) * sizeof(LobbyEvent *));
        map->size += last->cur - first->cur;
    } else {
        int n1 = first->last - first->cur;
        memmove(dst, first->cur, n1 * sizeof(LobbyEvent *));
        memmove(dst + n1, last->first, (last->cur - last->first) * sizeof(LobbyEvent *));
        map->size += (first->last - first->cur) + (last->cur - last->first);
    }
}

void LobbyEventDequeMapIterator_Advance(LobbyEventDequeMapIterator *it, int n) {
    int size = it->last - it->first;
    n += it->cur - it->first;
    if (n < 0) {
        n += size;
    } else if (n >= size) {
        n -= size;
    }
    it->cur = it->first + n;
}

int LobbyEventDequeMapIterator_Distance(const LobbyEventDequeMapIterator *it, const LobbyEventDequeMapIterator *from) {
    LobbyEvent **mid;
    LobbyEvent **other;
    LobbyEvent **cur;
    int count;
    mid = it->mid;
    other = from->cur;
    cur = it->cur;
    count = cur - other;
    if (cur >= mid) {
        if (other < mid) {
            count -= it->last - it->first;
        }
    } else {
        if (other >= mid) {
            count += it->last - it->first;
        }
    }
    return count;
}

void LobbyVipVector_Allocate(PPWLobbyVipVector *vector, u32 capacity, LobbyTag tag) {
    if (capacity > 0x1FFFFFFF) {
        _ZNSt15__vector_commonILb1EE18throw_length_errorEv();
    }
    vector->data = LobbyMem_Alloc(capacity * sizeof(PPWLobbyVipRecord));
    vector->capacity = capacity;
}

void LobbyEventVector_Allocate(LobbyEventVector *vector, u32 capacity, LobbyTag tag) {
    if (capacity > 0x1FFFFFFF) {
        _ZNSt15__vector_commonILb1EE18throw_length_errorEv();
    }
    vector->data = LobbyMem_Alloc(capacity * sizeof(LobbyEvent));
    vector->capacity = capacity;
}

void LobbyEventDequeMap_InitCopy(LobbyEventDequeMap *map, LobbyEventDequeMapIterator first, const LobbyEventDequeMapIterator *last) {
    LobbyEventDequeMapIterator lastCopy;
    LobbyEventDequeMapIterator firstCopy;
    int count;
    lastCopy = *last;
    firstCopy = first;
    count = LobbyEventDequeMapIterator_Distance2(&lastCopy, &firstCopy);
    if (count == 0) {
        return;
    }
    {
        LobbyTag allocateTag = { 0 };
        LobbyEventDequeMap_Allocate(map, count, allocateTag);
    }
    {
        LobbyTag appendTag = { 0 };
        LobbyEventDequeMap_AppendRange(map, &first, last, appendTag);
    }
}

void LobbyEventDequeMap_AppendRange(LobbyEventDequeMap *map, const LobbyEventDequeMapIterator *first, const LobbyEventDequeMapIterator *last, LobbyTag unused) {
    LobbyEvent **target;
    int count, chunk;
    LobbyEventDequeMapIterator firstEnd, secondStart, firstStart, secondFrom;
    if (!map->blocks) {
        return;
    }
    target = map->blocks + (map->start + map->size) % map->capacity;
    count = LobbyEventDequeMapIterator_Distance2(last, first);
    chunk = (map->blocks + map->capacity) - target;
    chunk = *(count < chunk ? &count : &chunk);
    map->size += count;
    firstStart.cur = first->cur;
    firstStart.first = first->first;
    firstStart.mid = first->mid;
    firstStart.last = first->last;
    {
        LobbyEventDequeMapIterator *advanced = LobbyEventDequeMapIterator_Advance2(&firstStart, chunk);
        firstEnd.cur = advanced->cur;
        firstEnd.first = advanced->first;
        firstEnd.mid = advanced->mid;
        firstEnd.last = advanced->last;
    }
    LobbyEventDequeMap_CopyToArray(*first, firstEnd, target);
    count -= chunk;
    if (!count) {
        return;
    }
    secondFrom.cur = first->cur;
    secondFrom.first = first->first;
    secondFrom.mid = first->mid;
    secondFrom.last = first->last;
    {
        LobbyEventDequeMapIterator *advanced = LobbyEventDequeMapIterator_Advance2(&secondFrom, chunk);
        secondStart.cur = advanced->cur;
        secondStart.first = advanced->first;
        secondStart.mid = advanced->mid;
        secondStart.last = advanced->last;
    }
    LobbyEventDequeMap_CopyToArray(secondStart, *last, map->blocks);
}
