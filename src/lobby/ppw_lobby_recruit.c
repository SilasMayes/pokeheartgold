#include "global.h"

#include "ppw_lobby_state.h"

#include <nitro/code32.h>

#include "ppw_lobby_work.h"

// The work pointer, read from memory again at every use.
static inline PPWLobbyWork *CurrentWork(void) {
    PPWLobbyWork *volatile *work = &gPPWLobbyWork;
    return *work;
}

static inline BOOL release(PPWLobbyWork *work) {
    if (work->recruiting) {
        work->recruiting = FALSE;
        return TRUE;
    }
    return FALSE;
}

void LobbyTimerMap_Erase(Iterator *, LobbyTimerMap *, Iterator);
int PPW_LobbyUpdateRecruitInfo(const PPWLobbyRecruitInfo *info);
int PPW_LobbyStopRecruit(void);

char *LobbyCharVector_Data(LobbyCharVector *p) {
    if (p->size == 0) {
        return 0;
    }
    return p->data;
}

int PPW_LobbyUpdateRecruitInfo(const PPWLobbyRecruitInfo *info) {
    PPWLobbyWork *w = CurrentWork();
    int result;
    if (!w) {
        return PPW_LOBBY_RESULT_ERROR_STATE;
    }
    if (w && w->state == PPW_LOBBY_STATE_ERROR) {
        return PPW_LOBBY_RESULT_ERROR_CONDITION;
    }
    if (w && CurrentWork()->state != PPW_LOBBY_STATE_READY) {
        return PPW_LOBBY_RESULT_ERROR_STATE;
    }
    w = CurrentWork();
    if (!w->recruiting) {
        result = 0;
    } else {
        w->recruitInfo.index = info->index;
        w->recruitInfo.maxPlayers = info->maxPlayers;
        w->recruitInfo.playerCount = info->playerCount;
        w->recruitInfo.state = info->state;
        w->recruitInfo.params = info->params;
        w->recruitInfo.name = info->name;
        result = 1;
    }
    if (!result) {
        return PPW_LOBBY_RESULT_ERROR_STATE;
    }
    return PPW_LOBBY_RESULT_SUCCESS;
}

int PPW_LobbyStopRecruit(void) {
    u32 timerId;
    PPWLobbyWork *w = CurrentWork();
    int result;
    if (!w) {
        return PPW_LOBBY_RESULT_ERROR_STATE;
    }
    if (w && w->state == PPW_LOBBY_STATE_ERROR) {
        return PPW_LOBBY_RESULT_ERROR_CONDITION;
    }
    if (w && CurrentWork()->state != PPW_LOBBY_STATE_READY) {
        return PPW_LOBBY_RESULT_ERROR_STATE;
    }
    w = CurrentWork();
    result = release(w);
    if (!result) {
        return PPW_LOBBY_RESULT_ERROR_STATE;
    }
    w = CurrentWork();
    PPWLobby_SendMessage(w->userId, PPW_LOBBY_CHANNEL_KIND_MAIN, PPW_LOBBY_MESSAGE_FORMAT_BINARY, PPW_LOBBY_MESSAGE_KIND_SYSTEM, PPW_LOBBY_SYSTEM_MESSAGE_STOP_RECRUIT, &w->recruitInfo, sizeof(PPWLobbyRecruitInfo));
    timerId = PPW_LOBBY_TIMER_SEND_RECRUIT_INFO;
    LobbyTimerMap_EraseKey(&CurrentWork()->timers, &timerId);
    return PPW_LOBBY_RESULT_SUCCESS;
}

BOOL LobbyTimerMap_EraseKey(LobbyTimerMap *map, u32 *id) {
    struct {
        Iterator argument, out;
        LobbyTimerMapNode *found;
    } local;

    LobbyTimerMap_Find(&local.found, map, id);
    if (local.found == (LobbyTimerMapNode *)&map->root) {
        return FALSE;
    }
    local.argument.current = local.found;
    LobbyTimerMap_Erase(&local.out, map, local.argument);
    return TRUE;
}
