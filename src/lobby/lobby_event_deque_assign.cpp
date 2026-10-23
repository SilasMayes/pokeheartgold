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

void LobbyEventDeque_Assign(LobbyEventDeque *d, LobbyEventVectorIterator first, const LobbyEventVectorIterator &last, LobbyTag) {
    u32 n = Distance(first, last);
    u32 m = Min(d->size, n);
    LobbyEventVectorIterator mid = first;
    mid.p += m;
    LobbyEventDeque_Copy(first, mid, LobbyEventDeque_IteratorAt(d, 0));
    n -= m;
    if (n != 0) {
        LobbyTag t;
        LobbyEventDeque_AppendRange(d, &mid, last, t);
    } else {
        u32 size = d->size;
        if (m < size) {
            LobbyEventDeque_EraseAtEnd(d, size - m, LobbyTag());
        }
    }
}
