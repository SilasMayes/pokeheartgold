#include <nitro/types.h>

#include "lobby_string.h"

#include <nitro/code32.h>

struct It {
    char *p;

    It(char *q)
        : p(q) {
    }

    char &operator*() const {
        return *p;
    }

    It &operator++() {
        ++p;
        return *this;
    }

    bool operator!=(const It &o) const {
        return p != o.p;
    }
};

inline It Begin(Str *s) {
    return It(!s->l.isLong ? s->s.buf : s->l.ptr);
}

inline It End(Str *s) {
    char *data;
    u32 len;
    if (!s->l.isLong) {
        data = s->s.buf;
        len = s->s.len;
    } else {
        data = s->l.ptr;
        len = s->l.size;
    }
    return It(data + len);
}

extern "C" int LobbyString_ToLowerChar(int c);

inline It Transform(It first, It last, It out, int (*f)(int)) {
    for (; first != last; ++first, ++out) {
        *out = f(*first);
    }
    return out;
}

extern "C" int LobbyString_CompareNoCase(Str *a, Str *b, u32 length) {
    Transform(Begin(a), End(a), Begin(a), LobbyString_ToLowerChar);
    Transform(Begin(b), End(b), Begin(b), LobbyString_ToLowerChar);
    return LobbyString_CompareSubstring(a, 0, length, b);
}
