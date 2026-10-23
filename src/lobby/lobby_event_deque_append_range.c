#include "global.h"

#include "lobby_event_deque.h"

#include <nitro/code32.h>

static inline int Equal(const LobbyEventVectorIterator *first, const LobbyEvent *last) {
    return first->p == last;
}

static inline long Distance(LobbyEventVectorIterator first, LobbyEventVectorIterator last) {
    LobbyEventVectorIterator *a = &first, *b = &last;
    return b->p - a->p;
}

void LobbyEventDeque_AppendRange(LobbyEventDeque *deque, LobbyEventVectorIterator *first, LobbyEventVectorIterator *last, LobbyTag tag) {
    LobbyEventDequeIterator result, pos;
    u32 count, available;
    if (Equal(first, last->p)) {
        return;
    }
    count = Distance(*first, *last);
    if (deque->map.size == 0) {
        available = 0;
    } else {
        available = (deque->map.size - 1) * LOBBY_EVENT_BLOCK_SIZE;
    }
    available -= deque->start + deque->size;
    if (count > available) {
        LobbyEventDeque_AddBackCapacity(deque, count - available);
    }
    LobbyEventDeque_IteratorAt(&pos, deque, deque->size);
    LobbyEventDeque_UninitializedCopy(&result, *first, *last, &pos, &deque->map.blocks, &deque->size);
}
