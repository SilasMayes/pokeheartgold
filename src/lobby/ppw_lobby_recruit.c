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

char *LobbyCharVector_Data(LobbyCharVector *vector) {
    if (vector->size == 0) {
        return 0;
    }
    return vector->data;
}

int PPW_LobbyUpdateRecruitInfo(const PPWLobbyRecruitInfo *info) {
    PPWLobbyWork *work = CurrentWork();
    int result;
    if (!work) {
        return PPW_LOBBY_RESULT_ERROR_STATE;
    }
    if (work && work->state == PPW_LOBBY_STATE_ERROR) {
        return PPW_LOBBY_RESULT_ERROR_CONDITION;
    }
    if (work && CurrentWork()->state != PPW_LOBBY_STATE_READY) {
        return PPW_LOBBY_RESULT_ERROR_STATE;
    }
    work = CurrentWork();
    if (!work->recruiting) {
        result = 0;
    } else {
        work->recruitInfo.index = info->index;
        work->recruitInfo.maxPlayers = info->maxPlayers;
        work->recruitInfo.playerCount = info->playerCount;
        work->recruitInfo.state = info->state;
        work->recruitInfo.params = info->params;
        work->recruitInfo.name = info->name;
        result = 1;
    }
    if (!result) {
        return PPW_LOBBY_RESULT_ERROR_STATE;
    }
    return PPW_LOBBY_RESULT_SUCCESS;
}

int PPW_LobbyStopRecruit(void) {
    u32 timerId;
    PPWLobbyWork *work = CurrentWork();
    int result;
    if (!work) {
        return PPW_LOBBY_RESULT_ERROR_STATE;
    }
    if (work && work->state == PPW_LOBBY_STATE_ERROR) {
        return PPW_LOBBY_RESULT_ERROR_CONDITION;
    }
    if (work && CurrentWork()->state != PPW_LOBBY_STATE_READY) {
        return PPW_LOBBY_RESULT_ERROR_STATE;
    }
    work = CurrentWork();
    result = release(work);
    if (!result) {
        return PPW_LOBBY_RESULT_ERROR_STATE;
    }
    work = CurrentWork();
    PPWLobby_SendMessage(work->userId, PPW_LOBBY_CHANNEL_KIND_MAIN, PPW_LOBBY_MESSAGE_FORMAT_BINARY, PPW_LOBBY_MESSAGE_KIND_SYSTEM, PPW_LOBBY_SYSTEM_MESSAGE_STOP_RECRUIT, &work->recruitInfo, sizeof(PPWLobbyRecruitInfo));
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
