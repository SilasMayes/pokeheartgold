#include <nitro/types.h>

#include "lobby_vector.h"

#include <nitro/code32.h>

class Allocator {
public:
    u32 recommend(LobbyCharVector *vector, u32 growth);
};

extern "C" {
void *memmove(void *, const void *, u32);
void LobbyCharVector_Reallocate(LobbyCharVector *, u32, u32);
void LobbyCharVector_AssignRange(LobbyCharVector *vector, const char *first, const char *last, int unused);
}

inline u32 Allocator::recommend(LobbyCharVector *vector, u32 growth) {
    return LobbyCharVector_RecommendSize(vector, growth);
}

struct Iter {
    const u8 *p;
    u32 extra;

    const u8 &operator*() const {
        return *p;
    }

    Iter &operator++() {
        ++p;
        return *this;
    }

    bool operator!=(const Iter &o) const {
        return p != o.p;
    }

    bool operator==(const Iter &o) const {
        return p == o.p;
    }
};

union Ch {
    u8 u;
    char c;
};

struct Narrow {
    char operator()(u8 c) const {
        Ch ch;
        ch.u = c;
        return ch.c;
    }
};

inline char Cast(const Iter &it) {
    Narrow narrow = Narrow();
    return narrow(*it);
}

extern "C" void LobbyCharVector_AssignIterRange(LobbyCharVector *vector, Iter first, Iter last);

extern "C" void LobbyCharVector_AssignRange(LobbyCharVector *vector, const char *first, const char *last, int unused) {
    u32 len = last - first;
    if (len > vector->capacity) {
        volatile u8 tag = 0;
        LobbyCharVector_Reallocate(vector, len, LobbyCharVector_RecommendSize(vector, len - vector->capacity));
    }
    memmove(vector->data, first, (u32)last - (u32)first);
    vector->size = len;
}

extern "C" void LobbyCharVector_AssignIterRange(LobbyCharVector *vector, Iter first, Iter last) {
    u32 len = last.p - first.p;
    u32 cap = vector->capacity;
    if (len > cap) {
        u32 growth = len - cap;
        Allocator allocator = Allocator();
        LobbyCharVector_Reallocate(vector, len, allocator.recommend(vector, growth));
    }
    {
        Iter it = first;
        char *dst = vector->data;
        for (; it != last; ++it) {
            *dst++ = Cast(it);
        }
    }
    vector->size = len;
}
