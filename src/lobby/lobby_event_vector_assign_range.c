#include "global.h"

#include <nitro/code32.h>

#include "ppw_lobby_work.h"

// The buffer the stable sort merges through: as many events as could be allocated.
typedef struct LobbySortTemporaryBuffer {
    LobbyEvent *data;
    int count;
} LobbySortTemporaryBuffer;

extern LobbySortTemporaryBuffer gLobbySortEmptyBuffer;
extern char _ZSt7nothrow[];
void *_ZnamRKSt9nothrow_t(u32, void *);
void LobbySort_GetTemporaryBuffer(LobbySortTemporaryBuffer *buffer, int n);

void LobbySort_GetTemporaryBuffer(LobbySortTemporaryBuffer *buffer, int n) {
    buffer->data = NULL;
    buffer->count = gLobbySortEmptyBuffer.count;
    while (n > 0) {
        buffer->data = _ZnamRKSt9nothrow_t(n * sizeof(LobbyEvent), _ZSt7nothrow);
        if (buffer->data) {
            buffer->count = n;
            return;
        }
        n /= 2;
    }
}

void LobbyEventVector_AssignRange(LobbyEventVector *p, const LobbyEvent *first, const LobbyEvent *last, LobbyTag tag) {
    u32 n = last - first, growth;
    const LobbyEvent *end;
    LobbyEvent *dest;
    volatile u8 a, c, d, b;
    if (p->capacity < n) {
        a = 0;
        growth = LobbyEventVector_RecommendSize(p, n - p->capacity);
    } else {
        end = first;
        end += *(p->size < n ? &p->size : &n);
        dest = p->data;
        while (first < end) {
            dest->key = first->key;
            dest->payload = first->payload;
            ++first;
            ++dest;
        }
        if (n < p->size) {
            u32 old = p->size;
            c = 0;
            p->size = *(volatile u32 *)&p->size - (old - n);
            return;
        }
        if (p->size >= n) {
            return;
        }
        d = 0;
        dest = *(LobbyEvent *volatile *)&p->data + *(volatile u32 *)&p->size;
        while (end != last) {
            if (dest) {
                *dest = *end;
            }
            ++p->size;
            ++end;
            ++dest;
        }
        return;
    }
    LobbyEventVector_Reallocate(p, n, growth);
    b = 0;
    dest = p->data + *(volatile u32 *)&p->size;
    for (; first != last; ++first, ++dest) {
        if (dest) {
            *dest = *first;
        }
        ++p->size;
    }
}

// A schedule record is at least its header and holds eventCount events.
BOOL PPWLobbySchedule_IsSizeValid(PPWLobbySchedule *schedule, const void *data, u32 size) {
    const PPWLobbyScheduleRecord *record = data;
    if (size < offsetof(PPWLobbyScheduleRecord, events)) {
        return FALSE;
    }
    return size >= (record->eventCount - 1) * sizeof(LobbyEvent) + sizeof(PPWLobbyScheduleRecord);
}
