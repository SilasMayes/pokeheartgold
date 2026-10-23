#include "global.h"

#include "lobby_event_deque.h"

#include <nitro/code32.h>

void LobbyEventDeque_IteratorAt(LobbyEventDequeIterator *out, LobbyEventDeque *deque, u32 index) {
    LobbyEventDequeMapIterator it;
    LobbyEvent *block;
    LobbyEvent **blocks;
    LobbyEvent **start;
    index += deque->start;
    blocks = deque->map.blocks;
    start = blocks + deque->map.start;
    it.last = blocks + deque->map.capacity;
    it.cur = start;
    it.first = blocks;
    it.mid = start;
    LobbyEventDequeMapIterator_Advance(&it, index / LOBBY_EVENT_BLOCK_SIZE);
    {
        LobbyEvent **cur = it.cur, **first = it.first, **mid = it.mid, **last = it.last;
        block = (deque->map.size == 0) ? NULL : *cur;
        out->block.cur = cur;
        out->block.first = first;
        out->block.mid = mid;
        out->block.last = last;
    }
    out->cur = block + index % LOBBY_EVENT_BLOCK_SIZE;
}
