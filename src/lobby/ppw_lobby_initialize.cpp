#include <nitro/types.h>

extern "C" {
#include <nitro/rtc.h>
}

#include "ppw_lobby_state.h"

#include <nitro/code32.h>

#include "lobby_mem.h"

#include <size_t.h>

extern "C" void DWC_GetDateTime(RTCDate *, RTCTime *);
extern "C" void DWC_Free(int, void *, int);
extern "C" char gPPWLobbyPlayersVtable[], gPPWLobbyPlayerVtable[];
extern "C" void PPWLobby_OnPlayerMessage();
extern "C" void PPWLobby_OnExcessFlood();
extern "C" void PPWLobbySchedule_Init(void *);
extern "C" void LobbyVipVector_Destroy(void *);
extern "C" void LobbyEventDeque_Destroy(void *);
extern "C" void LobbyEventVector_Destroy(void *);
extern "C" void LobbyTimerMap_Clear(void *);
extern "C" void LobbyTimerMap_Destroy(void *);
extern "C" void PPWLobbyPlayers_Clear(void *);
extern "C" void LobbyCharVector_Destroy(void *);
extern "C" void PPWLobbyPlayerSet_Destroy(void *);
extern "C" void LobbyString_Destroy(void *);
extern "C" void PPWLobbyPlayers_SetSelf(void *, u32, u32, u32);
extern "C" void PPWLobby_StartCheckProfile(void);

struct Callbacks {
    void (*connected)();
    void (*error)();
    int kind;

    Callbacks(void (*c)(), void (*e)(), int k)
        : connected(c)
        , error(e)
        , kind(k) {
    }
};

extern "C" enum PPWLobbyResult LobbyChat_Initialize(u32, u32, u32, Callbacks *, u32);

inline void *operator new(std::size_t, void *p) {
    return p;
}

struct Config {
    u32 words[17];
};

struct Str {
    u32 words[3];

    Str() {
        u32 i;
        u32 *p = words;
        for (i = 0; i < 3; i++) {
            p[i] = 0;
        }
    }

    void Destroy() {
        LobbyString_Destroy(this);
    }
};

// The C++ view of PPWLobbyChannel.
struct Channel {
    PPWLobbyChannelKind kind;
    Str name;
    BOOL usersEnumerated;
    BOOL modeReady;

    Channel()
        : kind(PPW_LOBBY_CHANNEL_KIND_INVALID) {
    }
};

struct List {
    u32 size;
    void *head;
    void **tail;

    List()
        : size(0)
        , head(0)
        , tail(&head) {
    }
};

struct Info {
    int id;
    s64 mid;
    int z;

    Info()
        : id(PPW_LOBBY_CHANNEL_KIND_INVALID)
        , mid(0)
        , z(0) {
        RTCTime time;
        RTCDate date;
        DWC_GetDateTime(&date, &time);
        mid = RTC_ConvertDateTimeToSecond(&date, &time);
    }
};

struct Vec {
    char *ptr;
    u32 size, cap;

    Vec()
        : ptr(0)
        , size(0)
        , cap(0) {
    }
};

struct Sessions {
    const void *vtbl;
    List list;
    const void *alloc;
    Info info;
    int valid;
    Vec field;
    int dirty;
    int pad120;
    int last;

    Sessions()
        : vtbl(gPPWLobbyPlayersVtable)
        , alloc(gPPWLobbyPlayerVtable)
        , valid(1)
        , dirty(1)
        , last(-1) {
    }

    void Destroy() {
        vtbl = gPPWLobbyPlayersVtable;
        PPWLobbyPlayers_Clear(this);
        LobbyCharVector_Destroy(&field);
        PPWLobbyPlayerSet_Destroy(&list);
    }
};

struct Tree {
    u32 size;
    void *root;
    void *unk;
    void **leftmost;

    Tree()
        : size(0)
        , root(0)
        , leftmost(&root) {
    }
};

struct Channels {
    Channel main;
    Channel sub;
};

struct Work {
    PPWLobbyState state;
    PPWLobbyError error;
    Config cfg;
    u32 userId;
    u32 prefix;
    u32 arg7;
    Str channelBaseName;
    BOOL isNewChannel;
    BOOL recruiting;
    BOOL submittingQuestionnaire;
    u32 unk_70;
    u8 pad74[0xb8 - 0x74];
    Channels channels;
    Sessions sessions;
    u8 pad128[0x134 - 0x128];
    Tree tree;
    u8 schedule[0x170 - 0x144];
    u8 events[0x17c - 0x170];
    u8 pendingEvents[0x194 - 0x17c];
    u8 vips[0x47c - 0x194];

    Work(u32 prefix, const Config &c, u32 userId, u32 a7)
        : state(PPW_LOBBY_STATE_NOT_INITIALIZED)
        , error(PPW_LOBBY_ERROR_NONE)
        , cfg(c)
        , userId(userId)
        , prefix(prefix)
        , arg7(a7)
        , isNewChannel(0)
        , recruiting(0)
        , submittingQuestionnaire(0)
        , unk_70(0) {
        PPWLobbySchedule_Init(schedule);
    }

    void Destroy() {
        LobbyVipVector_Destroy(vips);
        LobbyEventDeque_Destroy(pendingEvents);
        LobbyEventVector_Destroy(events);
        LobbyTimerMap_Clear(&tree);
        LobbyTimerMap_Destroy(&tree);
        sessions.Destroy();
        channels.sub.name.Destroy();
        channels.main.name.Destroy();
        channelBaseName.Destroy();
    }
};

extern "C" Work *gPPWLobbyWork;

inline void Free(void *p) {
    if (p) {
        DWC_Free(0, p, 0);
    }
}

inline void Delete(Work *w) {
    if (w) {
        w->Destroy();
        Free(w);
    }
}


extern "C" enum PPWLobbyResult PPWLobby_Initialize(u32 gameName, u32 secretKey, u32 prefix, const Config *cfg, u32 userId, u32 playerData, u32 playerDataSize, u32 a7);

extern "C" enum PPWLobbyResult PPWLobby_Initialize(u32 gameName, u32 secretKey, u32 prefix, const Config *cfg, u32 userId, u32 playerData, u32 playerDataSize, u32 a7) {
    if (gPPWLobbyWork != NULL) {
        return PPW_LOBBY_RESULT_ERROR_STATE;
    }
    Callbacks cbs(PPWLobby_OnPlayerMessage, PPWLobby_OnExcessFlood, 5);
    gPPWLobbyWork = new (LobbyMem_Alloc(sizeof(Work))) Work(prefix, *cfg, userId, a7);
    if (gPPWLobbyWork == NULL) {
        return PPW_LOBBY_RESULT_ERROR_ALLOC;
    }
    PPWLobbyResult result = LobbyChat_Initialize(gameName, secretKey, prefix, &cbs, userId);
    {
        Work *g = gPPWLobbyWork;
        PPWLobbyError error = PPWLobbyErrorMap().Map(result);
        if (error != PPW_LOBBY_ERROR_NONE) {
            g->error = error;
            g->state = PPW_LOBBY_STATE_ERROR;
        }
    }
    if (result != 0) {
        Work *w = gPPWLobbyWork;
        if (w != NULL) {
            Delete(w);
            gPPWLobbyWork = NULL;
        }
        return result;
    }
    PPWLobbyPlayers_SetSelf(&gPPWLobbyWork->sessions, userId, playerData, playerDataSize);
    PPWLobby_StartCheckProfile();
    gPPWLobbyWork->state = PPW_LOBBY_STATE_CONNECTING;
    return PPW_LOBBY_RESULT_SUCCESS;
}
