#include "global.h"

#include "ppw_lobby_internal.h"
#include "lobby_event_deque.h"

#include <nitro/code32.h>

LobbyEventDequeMapBuffer *LobbyEventDequeMapBuffer_Destroy(LobbyEventDequeMapBuffer *buffer) {
    if (buffer->map.blocks != NULL) {
        u32 n = buffer->map.size;
        LobbyTag a = { 0 };
        buffer->map.size -= n;
        if (buffer->map.blocks != NULL) {
            DWC_Free(0, buffer->map.blocks, 0);
        }
    }
    return buffer;
}

void LobbyEventDequeMapBuffer_Allocate(LobbyEventDequeMapBuffer *buffer, u32 n, LobbyTag tag) {
    if (!(gLobbyEventDequeMapBufferMaxSizeSet & 1)) {
        gLobbyEventDequeMapBufferMaxSize = 0x3FFFFFFE;
        gLobbyEventDequeMapBufferMaxSizeSet |= 1;
    }
    if (n > gLobbyEventDequeMapBufferMaxSize) {
        LobbyEventDequeMap_LengthError();
    }
    buffer->map.blocks = LobbyMem_Alloc((n + 1) * sizeof(LobbyEvent *));
    buffer->map.capacity = n + 1;
}

void LobbyEventDequeMapBuffer_PrependRange(LobbyEventDequeMapBuffer *buffer, const LobbyEventDequeMapIterator *a, const LobbyEventDequeMapIterator *b, LobbyTag tag) {
    LobbyEventDequeMap *d = &buffer->map;
    LobbyEvent **dst = d->blocks + d->start;
    if (a->cur <= b->cur) {
        int n = b->cur - a->cur;
        int m;
        memmove(dst - n, a->cur, n * sizeof(LobbyEvent *));
        m = b->cur - a->cur;
        d->size += m;
        d->start -= m;
    } else {
        int n1 = b->cur - b->first;
        LobbyEvent **p = dst - n1;
        int n2;
        int total;
        memmove(p, b->first, n1 * sizeof(LobbyEvent *));
        n2 = a->last - a->cur;
        memmove(p - n2, a->cur, n2 * sizeof(LobbyEvent *));
        total = (b->cur - b->first) + (a->last - a->cur);
        d->start -= total;
        d->size += total;
    }
}

void LobbyEventDequeMapBuffer_AppendRange(LobbyEventDequeMapBuffer *buffer, const LobbyEventDequeMapIterator *a, const LobbyEventDequeMapIterator *b, LobbyTag tag) {
    LobbyEventDequeMap *d = &buffer->map;
    LobbyEvent **dst = d->blocks + (d->start + d->size) % d->capacity;
    if (a->cur <= b->cur) {
        memmove(dst, a->cur, (b->cur - a->cur) * sizeof(LobbyEvent *));
        d->size += b->cur - a->cur;
    } else {
        int n1 = a->last - a->cur;
        memmove(dst, a->cur, n1 * sizeof(LobbyEvent *));
        memmove(dst + n1, b->first, (b->cur - b->first) * sizeof(LobbyEvent *));
        d->size += (a->last - a->cur) + (b->cur - b->first);
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

int LobbyEventDequeMapIterator_Distance(const LobbyEventDequeMapIterator *a, const LobbyEventDequeMapIterator *b) {
    LobbyEvent **mid;
    LobbyEvent **other;
    LobbyEvent **cur;
    int count;
    mid = a->mid;
    other = b->cur;
    cur = a->cur;
    count = cur - other;
    if (cur >= mid) {
        if (other < mid) {
            count -= a->last - a->first;
        }
    } else {
        if (other >= mid) {
            count += a->last - a->first;
        }
    }
    return count;
}

void LobbyVipVector_Allocate(PPWLobbyVipVector *vector, u32 n, LobbyTag tag) {
    if (n > 0x1FFFFFFF) {
        _ZNSt15__vector_commonILb1EE18throw_length_errorEv();
    }
    vector->data = LobbyMem_Alloc(n * sizeof(PPWLobbyVipRecord));
    vector->capacity = n;
}

void LobbyEventVector_Allocate(LobbyEventVector *vector, u32 n, LobbyTag tag) {
    if (n > 0x1FFFFFFF) {
        _ZNSt15__vector_commonILb1EE18throw_length_errorEv();
    }
    vector->data = LobbyMem_Alloc(n * sizeof(LobbyEvent));
    vector->capacity = n;
}

void LobbyEventDequeMap_InitCopy(LobbyEventDequeMap *d, LobbyEventDequeMapIterator a, const LobbyEventDequeMapIterator *b) {
    LobbyEventDequeMapIterator tb;
    LobbyEventDequeMapIterator ta;
    int n;
    tb = *b;
    ta = a;
    n = LobbyEventDequeMapIterator_Distance2(&tb, &ta);
    if (n == 0) {
        return;
    }
    {
        LobbyTag t1 = { 0 };
        LobbyEventDequeMap_Allocate(d, n, t1);
    }
    {
        LobbyTag t0 = { 0 };
        LobbyEventDequeMap_AppendRange(d, &a, b, t0);
    }
}

void LobbyEventDequeMap_AppendRange(LobbyEventDequeMap *d, const LobbyEventDequeMapIterator *first, const LobbyEventDequeMapIterator *last, LobbyTag unused) {
    LobbyEvent **target;
    int count, chunk;
    LobbyEventDequeMapIterator b, e, a, c;
    if (!d->blocks) {
        return;
    }
    target = d->blocks + (d->start + d->size) % d->capacity;
    count = LobbyEventDequeMapIterator_Distance2(last, first);
    chunk = (d->blocks + d->capacity) - target;
    chunk = *(count < chunk ? &count : &chunk);
    d->size += count;
    a.cur = first->cur;
    a.first = first->first;
    a.mid = first->mid;
    a.last = first->last;
    {
        LobbyEventDequeMapIterator *p = LobbyEventDequeMapIterator_Advance2(&a, chunk);
        b.cur = p->cur;
        b.first = p->first;
        b.mid = p->mid;
        b.last = p->last;
    }
    LobbyEventDequeMap_CopyToArray(*first, b, target);
    count -= chunk;
    if (!count) {
        return;
    }
    c.cur = first->cur;
    c.first = first->first;
    c.mid = first->mid;
    c.last = first->last;
    {
        LobbyEventDequeMapIterator *p = LobbyEventDequeMapIterator_Advance2(&c, chunk);
        e.cur = p->cur;
        e.first = p->first;
        e.mid = p->mid;
        e.last = p->last;
    }
    LobbyEventDequeMap_CopyToArray(e, *last, d->blocks);
}
