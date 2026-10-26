#include <nitro/types.h>

#include "lobby_event_deque.h"

#include <nitro/code32.h>
#include <size_t.h>

inline void *operator new(std::size_t, void *p) {
    return p;
}

template <class T>
inline const T &Min(const T &a, const T &b) {
    return b < a ? b : a;
}


inline LobbyEvent *UninitCopy(LobbyEventVectorIterator first, LobbyEventVectorIterator last, LobbyEvent *out, u32 *count) {
    for (; first != last; ++first.p, ++out) {
        new (out) LobbyEvent(*first.p);
        ++*count;
    }
    return out;
}

inline LobbyEvent *CopyRange(const LobbyEventVectorIterator &first, const LobbyEventVectorIterator &last, LobbyEvent *out) {
    LobbyEvent *src = first.base();
    LobbyEvent *dst = out;
    LobbyEvent *end = last.base();
    for (; src < end; ++src, ++dst) {
        *dst = *src;
    }
    return dst;
}

inline LobbyEvent *Copy(LobbyEventVectorIterator first, LobbyEventVectorIterator last, LobbyEvent *out) {
    return CopyRange(first, last, out);
}

LobbyEventDequeIterator LobbyEventDeque_UninitializedCopy(LobbyEventVectorIterator first, LobbyEventVectorIterator last, LobbyEventDequeIterator result, LobbyTag, u32 *count) {
    if (first != last) {
        int remaining = last - first;
        for (;;) {
            int step;
            LobbyEventVectorIterator mid;
            int room = result.SegmentEnd() - result.cur;
            step = Min(remaining, room);
            mid = first + step;
            UninitCopy(first, mid, result.cur, count);
            remaining -= step;
            result += step;
            if (remaining == 0) {
                break;
            }
            first = mid;
        }
    }
    return result;
}

LobbyEventDequeIterator LobbyEventDeque_Copy(LobbyEventVectorIterator first, LobbyEventVectorIterator last, LobbyEventDequeIterator result) {
    if (first != last) {
        int remaining = last - first;
        for (;;) {
            int step;
            LobbyEventVectorIterator mid;
            int room = result.SegmentEnd() - result.cur;
            step = Min(remaining, room);
            mid = first + step;
            Copy(first, mid, result.cur);
            remaining -= step;
            result += step;
            if (remaining == 0) {
                break;
            }
            first = mid;
        }
    }
    return result;
}
