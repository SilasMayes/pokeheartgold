#ifndef POKEHEARTGOLD_LOBBY_EVENT_DEQUE_H
#define POKEHEARTGOLD_LOBBY_EVENT_DEQUE_H

// The deque of lobby schedule events. The events are kept in blocks of 128; the deque's map is a ring
// buffer of block pointers that grows at both ends.

#include <nitro/types.h>

#include "lobby_vector.h"

#define LOBBY_EVENT_BLOCK_SIZE 128

// A timed event of the lobby schedule: the seconds after the schedule's start and the event (WIFI_PLAZA_EVENT_*).
typedef struct LobbyEvent {
    s32 time;
    u32 type;
} LobbyEvent;

typedef struct LobbyEventDequeMap {
    LobbyEvent **blocks;
    u32 start;
    u32 size;
    u32 capacity;
} LobbyEventDequeMap;

// A position in the map's ring: cur walks from start (mid) to the end of the array (last) and wraps to first.
typedef struct LobbyEventDequeMapIterator {
    LobbyEvent **cur;
    LobbyEvent **first;
    LobbyEvent **mid;
    LobbyEvent **last;
#ifdef __cplusplus
    LobbyEventDequeMapIterator() {
    }

    LobbyEventDequeMapIterator(LobbyEvent **c, LobbyEvent **f, LobbyEvent **m, LobbyEvent **l)
        : cur(c)
        , first(f)
        , mid(m)
        , last(l) {
    }

    LobbyEventDequeMapIterator(const LobbyEventDequeMapIterator &other)
        : cur(other.cur)
        , first(other.first)
        , mid(other.mid)
        , last(other.last) {
    }

    inline LobbyEventDequeMapIterator(struct LobbyEventDequeMap *map, u32 i);

    inline LobbyEventDequeMapIterator &operator+=(int n);

    LobbyEvent *const &operator*() const {
        return *cur;
    }

    LobbyEventDequeMapIterator &operator++() {
        if (++cur == last) {
            cur = first;
        }
        return *this;
    }
#endif
} LobbyEventDequeMapIterator;

#ifdef __cplusplus
extern "C" LobbyEventDequeMapIterator &LobbyEventDequeMapIterator_Advance(LobbyEventDequeMapIterator *, int);

inline LobbyEventDequeMapIterator &LobbyEventDequeMapIterator::operator+=(int n) {
    return LobbyEventDequeMapIterator_Advance(this, n);
}
#endif

#ifdef __cplusplus
inline LobbyEventDequeMapIterator::LobbyEventDequeMapIterator(LobbyEventDequeMap *map, u32 i)
    : cur(map->blocks + i)
    , first(map->blocks)
    , mid(first + map->start)
    , last(first + map->capacity) {
}
#endif

// The schedule's events in time order, before they are queued in the deque.
typedef struct LobbyEventVector {
    LobbyEvent *data;
    u32 size;
    u32 capacity;
} LobbyEventVector;

// The buffer the map grows through; allocator points at the capacity of the map it grows.
typedef struct LobbyEventDequeMapBuffer {
    LobbyEventDequeMap map;
    u32 *allocator;
} LobbyEventDequeMapBuffer;

// start is the index of the first event in the first block.
typedef struct LobbyEventDeque {
    u32 start;
    u32 size;
    LobbyEventDequeMap map;
} LobbyEventDeque;

typedef struct LobbyEventDequeIterator {
    LobbyEventDequeMapIterator block;
    LobbyEvent *cur;
#ifdef __cplusplus
    LobbyEventDequeIterator(const LobbyEventDequeIterator &other) {
        block.cur = other.block.cur;
        block.first = other.block.first;
        block.mid = other.block.mid;
        block.last = other.block.last;
        cur = other.cur;
    }

    LobbyEvent *SegmentEnd() const {
        return cur ? *block.cur + LOBBY_EVENT_BLOCK_SIZE : cur;
    }

    LobbyEventDequeIterator &operator++() {
        LobbyEvent **m = block.cur;
        if (++cur == *m + LOBBY_EVENT_BLOCK_SIZE) {
            if (++block.cur == block.last) {
                block.cur = block.first;
            }
            cur = *block.cur;
        }
        return *this;
    }

    LobbyEventDequeIterator &operator+=(int n) {
        cur += n - 1;
        return ++*this;
    }
#endif
} LobbyEventDequeIterator;

// A position in a vector of events, the source of the deque's range operations.
typedef struct LobbyEventVectorIterator {
    LobbyEvent *p;
#ifdef __cplusplus
    LobbyEventVectorIterator() {
    }

    LobbyEventVectorIterator(LobbyEvent *q)
        : p(q) {
    }

    LobbyEvent *base() const {
        return p;
    }

    LobbyEventVectorIterator &operator+=(int n) {
        p += n;
        return *this;
    }

    bool operator!=(const LobbyEventVectorIterator &o) const {
        return p != o.p;
    }

    int operator-(const LobbyEventVectorIterator &o) const {
        return p - o.p;
    }

    LobbyEventVectorIterator operator+(int n) const {
        LobbyEventVectorIterator t(*this);
        t.p += n;
        return t;
    }
#endif
} LobbyEventVectorIterator;

// The buffer the stable sort of the events merges through: as many events as could be allocated.
typedef struct LobbySortTemporaryBuffer {
    LobbyEvent *data;
    int count;
} LobbySortTemporaryBuffer;

#ifdef __cplusplus
extern "C" {
#endif

extern u32 gLobbyDequeMaxSizeInit;
extern u32 gLobbyDequeMaxSize;
extern u32 gLobbyEventDequeMapMaxSizeSet;
extern u32 gLobbyEventDequeMapMaxSize;
extern u32 gLobbyEventDequeMapBufferMaxSizeSet;
extern u32 gLobbyEventDequeMapBufferMaxSize;
extern char gLobbyStr_DequeLengthError[];
extern char gLobbyStr_CdequeLengthError[];

LobbyEventDeque *LobbyEventDeque_Destroy(LobbyEventDeque *deque);
LobbyEventDeque *LobbyEventDeque_Destroy2(LobbyEventDeque *deque);
void LobbyEventDeque_AddBackCapacity(LobbyEventDeque *deque, u32 count);
void LobbyEventDeque_EraseAtBegin(LobbyEventDeque *deque, u32 count, LobbyTag tag);
void LobbyEventDeque_EraseAtEnd(LobbyEventDeque *deque, u32 count, LobbyTag tag);
void LobbyEventDeque_LengthError(const char *message);
LobbyEventDequeMap *LobbyEventDequeMap_Destroy(LobbyEventDequeMap *map);
void LobbyEventDequeMap_Allocate(LobbyEventDequeMap *map, u32 capacity, LobbyTag tag);
LobbyEventDequeMapIterator *LobbyEventDequeMapIterator_Advance2(LobbyEventDequeMapIterator *it, int n);
int LobbyEventDequeMapIterator_Distance2(const LobbyEventDequeMapIterator *a, const LobbyEventDequeMapIterator *b);
void LobbyEventDequeMap_Reserve(LobbyEventDequeMap *map, u32 size);
u32 LobbyEventDequeMap_RecommendSize(LobbyEventDequeMap *map, u32 extra);
void LobbyEventDequeMap_LengthError(void);
LobbyEventDequeMapBuffer *LobbyEventDequeMapBuffer_Destroy(LobbyEventDequeMapBuffer *buffer);
void LobbyEventDequeMapBuffer_Allocate(LobbyEventDequeMapBuffer *buffer, u32 capacity, LobbyTag tag);
void LobbyEventVector_Allocate(LobbyEventVector *vector, u32 capacity, LobbyTag tag);
void LobbyEventVector_Reallocate(LobbyEventVector *vector, u32 unused, u32 capacity);
u32 LobbyEventVector_RecommendSize(LobbyEventVector *vector, u32 extra);
void LobbyEventVector_AssignRange(LobbyEventVector *vector, const LobbyEvent *first, const LobbyEvent *last, LobbyTag tag);
void LobbySort_GetTemporaryBuffer(LobbySortTemporaryBuffer *buffer, int n);

// The C code passes the iterators by pointer and returns them through a pointer to the result; the C++ code
// passes them by reference and returns them by value.
#ifdef __cplusplus
LobbyEventDequeIterator LobbyEventDeque_IteratorAt(LobbyEventDeque *deque, u32 index);
void LobbyEventDeque_AppendRange(LobbyEventDeque *deque, LobbyEventVectorIterator *first, const LobbyEventVectorIterator &last, LobbyTag tag);
void LobbyEventDeque_Assign(LobbyEventDeque *deque, LobbyEventVectorIterator first, const LobbyEventVectorIterator &last, LobbyTag tag);
LobbyEventDequeIterator LobbyEventDeque_Copy(LobbyEventVectorIterator first, LobbyEventVectorIterator last, LobbyEventDequeIterator result);
LobbyEventDequeIterator LobbyEventDeque_UninitializedCopy(LobbyEventVectorIterator first, LobbyEventVectorIterator last, LobbyEventDequeIterator result, LobbyTag tag, u32 *count);
void LobbyEventDequeMapBuffer_AppendRange(LobbyEventDequeMapBuffer *buffer, const LobbyEventDequeMapIterator &first, const LobbyEventDequeMapIterator &last, LobbyTag tag);
void LobbyEventDequeMapBuffer_PrependRange(LobbyEventDequeMapBuffer *buffer, const LobbyEventDequeMapIterator &first, const LobbyEventDequeMapIterator &last, LobbyTag tag);
#else
void LobbyEventDeque_IteratorAt(LobbyEventDequeIterator *out, LobbyEventDeque *deque, u32 index);
void LobbyEventDequeMapIterator_Advance(LobbyEventDequeMapIterator *it, int n);
int LobbyEventDequeMapIterator_Distance(const LobbyEventDequeMapIterator *a, const LobbyEventDequeMapIterator *b);
void LobbyEventDequeMap_InitCopy(LobbyEventDequeMap *map, LobbyEventDequeMapIterator first, const LobbyEventDequeMapIterator *last);
void LobbyEventDequeMap_AppendRange(LobbyEventDequeMap *map, const LobbyEventDequeMapIterator *first, const LobbyEventDequeMapIterator *last, LobbyTag tag);
LobbyEvent **LobbyEventDequeMap_CopyToArray(LobbyEventDequeMapIterator first, LobbyEventDequeMapIterator last, LobbyEvent **dest);
void LobbyEventDequeMapBuffer_AppendRange(LobbyEventDequeMapBuffer *buffer, const LobbyEventDequeMapIterator *first, const LobbyEventDequeMapIterator *last, LobbyTag tag);
void LobbyEventDequeMapBuffer_PrependRange(LobbyEventDequeMapBuffer *buffer, const LobbyEventDequeMapIterator *first, const LobbyEventDequeMapIterator *last, LobbyTag tag);
void LobbyEventDeque_AppendRange(LobbyEventDeque *deque, LobbyEventVectorIterator *first, LobbyEventVectorIterator *last, LobbyTag tag);
void LobbyEventDeque_UninitializedCopy(LobbyEventDequeIterator *out, LobbyEventVectorIterator first, LobbyEventVectorIterator last, LobbyEventDequeIterator *result, void *unused, u32 *count);
void LobbyEventDequeMap_Copy(LobbyEventDequeMapIterator *out, LobbyEventDequeMapIterator *first, LobbyEventDequeMapIterator *last, LobbyEventDequeMapIterator *dest);
void LobbyEventDequeMap_CopyBackward(LobbyEventDequeMapIterator *out, LobbyEventDequeMapIterator *first, LobbyEventDequeMapIterator *last, LobbyEventDequeMapIterator *dest);
#endif

#ifdef __cplusplus
}
#endif

#endif // POKEHEARTGOLD_LOBBY_EVENT_DEQUE_H
