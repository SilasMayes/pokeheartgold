#include <nitro/types.h>

#include "ppw_lobby_state.h"

extern "C" {
#include <nitro/rtc.h>
}

#include <nitro/code32.h>
extern "C" char *strncpy(char *, const char *, unsigned);
struct Str;
extern "C" Str *LobbyString_Destroy(Str *);
extern "C" void LobbyString_Assign(Str *, const Str *);

struct Str {
    union {
        struct {
            u32 isLong : 1;
            u32 capacity : 31;
            u32 size;
            char *data;
        } l;

        struct {
            u8 isLong : 1;
            u8 size : 7;
            char data[11];
        } s;

        u32 words[3];
    } raw;

    Str() {
    }

    Str(const Str &o);

    const char *CStr() const {
        return !raw.l.isLong ? raw.s.data : raw.l.data;
    }

    Str &operator=(const Str &o) {
        LobbyString_Assign(this, &o);
        return *this;
    }
};

// The C++ view of PPWLobbyRecruitInfo.
struct RecruitInfo {
    int index;
    int maxPlayers;
    int playerCount;
    int state;
    u8 params[32];
    char name[20];
};

struct Info {
    s64 time;
    s64 period;
    u32 z;
    void (*cb)();

    Info() {
    }

    Info(s64 now, s64 d, void (*c)())
        : time(now)
        , period(d)
        , z(0)
        , cb(c) {
        time -= d;
    }
};

template <class A, class B>
struct Pair {
    A first;
    B second;

    Pair(const A &a, const B &b)
        : first(a)
        , second(b) {
    }

    template <class C, class D>
    Pair(const Pair<C, D> &o)
        : first(o.first) {
        const Info *s = &o.second;
        Info *d = &second;
        *d = *s;
    }
};

typedef Pair<u32, Info> RawEntry;
typedef Pair<const u32, Info> Entry;

struct Result {
    void *it;
    int ok;
};

struct Container {
    u8 pad[4];
};

struct Work {
    int state;
    u8 pad04[0x4c - 4];
    u32 userId;
    u8 pad50[0x68 - 0x50];
    BOOL recruiting;
    u8 pad6c[0x74 - 0x6c];
    RecruitInfo recruitInfo;
    u8 padb8[0x134 - 0xb8];
    Container timers;
};

extern "C" Work *gPPWLobbyWork;
extern "C" char gLobbyFmt_M_IntUnderscoreUint[];
extern "C" void PPWLobby_TimerSendRecruitInfo();
extern "C" u32 current_time(void);
extern "C" Str LobbyString_FormatN(int, const char *, ...);
extern "C" void DWC_GetDateTime(RTCDate *, RTCTime *);
extern "C" RawEntry LobbyTimerMap_MakeEntry(int, const Info &);
extern "C" Result LobbyTimerMap_Insert(Container *, const Entry &);
extern "C" int PPW_LobbyStartRecruit(RecruitInfo *info);

struct Tag {};

inline Entry ConstructEntry(Tag, const RawEntry &r) {
    return Entry(r);
}

inline Entry ConvertEntry(Tag, const RawEntry &r) {
    return ConstructEntry(Tag(), r);
}

inline Result InsertEntry(Container *c, const Entry &e) {
    return LobbyTimerMap_Insert(c, e);
}

#pragma opt_common_subs off

extern "C" int PPW_LobbyStartRecruit(RecruitInfo *info) {
    Work *w = gPPWLobbyWork;
    if (w == NULL) {
        return PPW_LOBBY_RESULT_ERROR_STATE;
    }
    if (w != NULL && w->state == PPW_LOBBY_STATE_ERROR) {
        return PPW_LOBBY_RESULT_ERROR_CONDITION;
    }
    if (w != NULL && gPPWLobbyWork->state != PPW_LOBBY_STATE_READY) {
        return PPW_LOBBY_RESULT_ERROR_STATE;
    }
    Str value;
    u32 *p = value.raw.words;
    for (u32 i = 0; i < 3; i++) {
        p[i] = 0;
    }
    int ok = 0;
    Work *g = gPPWLobbyWork;
    if (!g->recruiting) {
        g->recruiting = TRUE;
        g->recruitInfo = *info;
        Str tmp = LobbyString_FormatN(20, gLobbyFmt_M_IntUnderscoreUint, g->userId, current_time() % 1000);
        value = tmp;
        LobbyString_Destroy(&tmp);
        strncpy(g->recruitInfo.name, value.CStr(), sizeof(g->recruitInfo.name) - 1);
        ok = 1;
    }
    if (!ok) {
        LobbyString_Destroy(&value);
        return PPW_LOBBY_RESULT_ERROR_STATE;
    }
    strncpy(info->name, value.CStr(), sizeof(info->name) - 1);
    Work *h = gPPWLobbyWork;
    RTCDate date;
    RTCTime time;
    DWC_GetDateTime(&date, &time);
    InsertEntry(&h->timers, ConvertEntry(Tag(), LobbyTimerMap_MakeEntry(PPW_LOBBY_TIMER_SEND_RECRUIT_INFO, Info(RTC_ConvertDateTimeToSecond(&date, &time), 21, PPWLobby_TimerSendRecruitInfo))));
    LobbyString_Destroy(&value);
    return PPW_LOBBY_RESULT_SUCCESS;
}

#pragma opt_common_subs reset
