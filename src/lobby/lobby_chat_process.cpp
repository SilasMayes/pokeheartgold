#include <nitro/types.h>

extern "C" {
#include <nitro/rtc.h>
}

#include <nitro/code32.h>

#include "lobby_chat_manager.h"
#include "ppw_lobby_state.h"

extern "C" void DWC_GetDateTime(RTCDate *date, RTCTime *time);
extern "C" void chatThink(struct ChatConnection *chat);

struct It;
extern "C" void LobbyTreeIterator_Advance(It *it);

struct It {
    LobbyTimerMapNode *n;

    It() {
    }

    It(LobbyTimerMapNode *p)
        : n(p) {
    }

    It &operator++() {
        LobbyTreeIterator_Advance(this);
        return *this;
    }

    It operator++(int) {
        LobbyTimerMapNode *old = n;
        LobbyTreeIterator_Advance(this);
        return It(old);
    }

    bool operator!=(const It &o) const {
        return n != o.n;
    }

    LobbyTimerMapNode *operator->() const {
        return n;
    }
};

extern "C" It LobbyTimerMap_Erase(LobbyTimerMap *t, It pos);

static inline bool IsFatal() {
    return gLobbyChatManager != NULL && gLobbyChatManager->state == LOBBY_CHAT_STATE_ERROR;
}

static inline LobbyChatState GetState() {
    return gLobbyChatManager->state;
}

static inline bool Tick(LobbyTimerMapNode *n, const s64 &now) {
    if (now - n->timer.lastTime > n->timer.interval) {
        n->timer.lastTime = now;
        if (!n->timer.callback(n->timer.param)) {
            return false;
        }
    }
    return true;
}

static inline void SetError(LobbyChatManager *m, PPWLobbyError code) {
    m->lastError = code;
    m->state = LOBBY_CHAT_STATE_ERROR;
}

static inline void UpdateState(LobbyChatManager *m) {
    switch (m->state) {
    case LOBBY_CHAT_STATE_INIT:
    case LOBBY_CHAT_STATE_CONNECTING:
    case LOBBY_CHAT_STATE_READY:
    case LOBBY_CHAT_STATE_DISCONNECTING:
        break;
    case LOBBY_CHAT_STATE_CONNECTED:
        if (m->connectedFrames++ == 60) {
            m->connectedFrames = 0;
            if (m->state != LOBBY_CHAT_STATE_ERROR) {
                m->state = LOBBY_CHAT_STATE_READY;
            }
        }
        break;
    }
}

static inline int Timer_Update(LobbyTimerMapNode *t, s64 now) {
    if (now - t->timer.lastTime > t->timer.interval) {
        t->timer.lastTime = now;
        if (!t->timer.callback(t->timer.param)) {
            return 0;
        }
    }
    return 1;
}

static inline It Iterator_Make(LobbyTimerMapNode *p) {
    It t;
    t.n = p;
    return t;
}

#pragma push
#pragma opt_common_subs off

extern "C" enum LobbyChatState LobbyChat_Process(void) {
    LobbyChatManager *g = gLobbyChatManager;
    if (g == NULL) {
        return LOBBY_CHAT_STATE_INIT;
    }
    if (g != NULL && g->state == LOBBY_CHAT_STATE_ERROR) {
        return LOBBY_CHAT_STATE_ERROR;
    }
    struct ChatConnection *connection = g->connection;
    if (connection != NULL) {
        chatThink(connection);
    }
    LobbyChatManager *w = gLobbyChatManager;
    RTCTime time;
    RTCDate date;
    s64 now;
    LobbyTimerMapNode *end;
    It it;
    DWC_GetDateTime(&date, &time);
    now = RTC_ConvertDateTimeToSecond(&date, &time);
    it.n = w->timerMap.leftmost;
    end = (LobbyTimerMapNode *)&w->timerMap.root;
    for (LobbyTimerMapNode *n = it.n; n != end; n = it.n) {
        if (!Timer_Update(n, now)) {
            LobbyTimerMapNode *saved = it.n;
            LobbyTreeIterator_Advance(&it);
            LobbyTimerMap_Erase(&w->timerMap, Iterator_Make(saved));
        } else {
            LobbyTreeIterator_Advance(&it);
        }
    }
    LobbyChatManager *g2 = gLobbyChatManager;
    if (g2 != NULL && g2->state == LOBBY_CHAT_STATE_ERROR) {
        return LOBBY_CHAT_STATE_ERROR;
    }
    LobbyChatManager *m2 = gLobbyChatManager;
    if (g2->unk54 >= 3) {
        g2->unk54 = 0;
        SetError(gLobbyChatManager, PPW_LOBBY_ERROR_SESSION);
        return GetState();
    }
    UpdateState(m2);
    return GetState();
}

#pragma pop
