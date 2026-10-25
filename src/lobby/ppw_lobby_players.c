#include "global.h"

#include <nitro/code32.h>

#include "ppw_lobby_internal.h"
#include "ppw_lobby_state.h"

void PPWLobbyPlayer_UpdateState(Session *s) {
    switch (s->state) {
    case PPW_LOBBY_PLAYER_STATE_NEW:
        s->state = (s->systemProfileReceived && s->userProfileReceived) ? PPW_LOBBY_PLAYER_STATE_HAS_PROFILES : PPW_LOBBY_PLAYER_STATE_NEW;
        if (s->state == PPW_LOBBY_PLAYER_STATE_NEW) {
            return;
        }
    case PPW_LOBBY_PLAYER_STATE_HAS_PROFILES:
        if (s->unk10 != 0) {
            s->state = PPW_LOBBY_PLAYER_STATE_READY;
        }
        return;
    case PPW_LOBBY_PLAYER_STATE_READY:
        if (s->entered) {
            s->state = PPW_LOBBY_PLAYER_STATE_ENTERED;
        }
        return;
    case PPW_LOBBY_PLAYER_STATE_ENTERED:
        return;
    }
}

BOOL PPWLobbyPlayers_Add(SessionMgr *m, int id) {
    RTCDate date;
    RTCTime time;
    Session *s;
    volatile InsertResult res2;
    InsertResult res;
    volatile LobbyTag t1;
    volatile LobbyTag t0;
    Session *n = LobbyMem_Alloc(sizeof(Session));
    if (n != NULL) {
        n->vt = &gPPWLobbyPlayerVtable;
        n->channel = PPW_LOBBY_CHANNEL_KIND_INVALID;
        n->time = 0;
        n->unk10 = 0;
        DWC_GetDateTime(&date, &time);
        n->time = RTC_ConvertDateTimeToSecond(&date, &time);
        n->systemProfileChanged = TRUE;
        n->userProfileData = 0;
        n->userProfileSize = 0;
        n->userProfileCapacity = 0;
        n->userProfileChanged = TRUE;
        n->state = PPW_LOBBY_PLAYER_STATE_NEW;
        n->id = id;
        n->systemProfileReceived = FALSE;
        n->userProfileReceived = FALSE;
        n->entered = FALSE;
    }
    s = n;
    PPWLobbyPlayerSet_Insert(&res, &m->list, &s);
    t1.unused = 0;
    res2.current = res.current;
    t0.unused = 0;
    res2.inserted = res.inserted;
    if ((res.inserted & 0xFF) == 0) {
        if (s != NULL) {
            s->vt->dtor((VObj *)s);
        }
        return TRUE;
    }
    return TRUE;
}

BOOL PPWLobbyPlayers_Remove(SessionMgr *m, int id) {
    NodeIter it;
    Node *hdr = (Node *)&m->list.root;
    it.current = m->list.leftmost;
    while (it.current != hdr) {
        Session *s = ((Node *)it.current)->val;
        if (id == s->id) {
            NodeIter tmp;
            if (s != NULL) {
                s->vt->dtor((VObj *)s);
            }
            PPWLobbyPlayerSet_Erase(&tmp, &m->list, it);
            return TRUE;
        }
        LobbyTreeIterator_Advance(&it);
    }
    return FALSE;
}

Session *PPWLobbyPlayers_Find(SessionMgr *m, int id) {
    volatile FindState a;
    volatile FindState b;
    Node *r;
    BOOL e;
    Node *hdr;
    Node *first;
    if (id == m->self.id) {
        return &m->self;
    }
    first = m->list.leftmost;
    hdr = (Node *)&m->list.root;
    a.id = id;
    b.id = id;
    a.end = hdr;
    b.end = hdr;
    a.it.current = first;
    b.it.current = first;
    while (((NodeIter *)&b.it)->current != hdr && id != ((Node *)((NodeIter *)&b.it)->current)->val->id) {
        LobbyTreeIterator_Advance((NodeIter *)&b.it);
    }
    e = ((NodeIter *)&b.it)->current == (Node *)&m->list.root;
    r = b.it.current;
    if (e) {
        return NULL;
    }
    return r->val;
}
