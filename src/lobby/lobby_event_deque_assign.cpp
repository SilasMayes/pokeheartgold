#include <nitro/types.h>

#include "lobby_event_deque.h"

#include <nitro/code32.h>

inline int Distance(LobbyEventVectorIterator first, LobbyEventVectorIterator last) {
    return last.p - first.p;
}

template <class T>
inline const T &Min(const T &a, const T &b) {
    return a < b ? a : b;
}

void LobbyEventDeque_Assign(LobbyEventDeque *deque, LobbyEventVectorIterator first, const LobbyEventVectorIterator &last, LobbyTag) {
    u32 count = Distance(first, last);
    u32 copied = Min(deque->size, count);
    LobbyEventVectorIterator mid = first;
    mid.p += copied;
    LobbyEventDeque_Copy(first, mid, LobbyEventDeque_IteratorAt(deque, 0));
    count -= copied;
    if (count != 0) {
        LobbyTag tag;
        LobbyEventDeque_AppendRange(deque, &mid, last, tag);
    } else {
        u32 size = deque->size;
        if (copied < size) {
            LobbyEventDeque_EraseAtEnd(deque, size - copied, LobbyTag());
        }
    }
}
