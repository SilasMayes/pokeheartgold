#include "global.h"

#include <nitro/code32.h>

#include "ppw_lobby_internal.h"

BOOL PPWLobbyPlayers_IsFull(SessionMgr *m) {
    LobbyU32Vector v;
    BOOL made = FALSE;
    BOOL res = FALSE;
    if (m->list.count + 1 == PPW_LOBBY_MAX_PLAYERS) {
        PPWLobbyPlayers_GetEnteredIds(&v, m);
        made = TRUE;
        if (v.size + 1 == PPW_LOBBY_MAX_PLAYERS) {
            res = TRUE;
        }
    }
    if (made) {
        LobbyU32Vector_Destroy(&v);
    }
    return res;
}

void PPWLobbyPlayers_GetEnteredIds(LobbyU32Vector *out, SessionMgr *m) {
    NodeIter it;
    u32 id;
    Node *hdr;
    out->data = NULL;
    out->size = 0;
    out->capacity = 0;
    VecReserve(out, m->list.count);
    hdr = (Node *)&m->list.root;
    it.current = m->list.leftmost;
    while (it.current != hdr) {
        Session *s = ((Node *)it.current)->val;
        if (s->entered != 0) {
            id = s->id;
            TouchTag();
            if (out->size < out->capacity) {
                out->size++;
                out->data[out->size - 1] = id;
            } else {
                LobbyTag t2 = { 0 };
                LobbyU32Vector_PushBackSlow(out, &id, t2);
            }
        }
        LobbyTreeIterator_Advance(&it);
    }
}
