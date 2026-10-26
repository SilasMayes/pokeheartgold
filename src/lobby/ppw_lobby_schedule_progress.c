#include "global.h"

#include "dwc/net_common_internal.h"

#include <nitro/code32.h>

#include "lobby_chat_manager.h"
#include "ppw_lobby_state.h"
#include "ppw_lobby_work.h"

BOOL PPWLobbySchedule_GetQuestionnaire(PPWLobbySchedule *schedule, void *out) {
    if (!schedule->hasQuestionnaire) {
        return FALSE;
    }
    MI_CpuCopy8(schedule->questionnaire, out, sizeof(schedule->questionnaire));
    return TRUE;
}

BOOL PPWLobbySchedule_SetQuestionnaire(PPWLobbySchedule *schedule, const void *in) {
    MI_CpuCopy8(in, schedule->questionnaire, sizeof(schedule->questionnaire));
    schedule->hasQuestionnaire = TRUE;
    return TRUE;
}

void PPWLobbySchedule_Process(PPWLobbySchedule *schedule) {
    Str name;
    RTCTime time;
    RTCDate date;
    u32 zero;
    LobbyEvent *event;
    s64 now;
    switch (schedule->state) {
    case 0:
    case 1:
    case 2:
    case 3:
        break;
    case PPW_LOBBY_SCHEDULE_STATE_LOADED:
        if (!PPWLobbySchedule_CanStart(schedule)) {
            return;
        }
        PPWLobbyChannel_GetName(&name, &PPWLobby_GetWork()->mainChannel);
        LobbyChat_SetChannelMode(name.l.isLong == 0 ? name.s.buf : name.l.ptr, &gPPWLobbyMainChannelSecretMode);
        LobbyString_Destroy(&name);
        zero = 0;
        PPWLobby_SendMessage(-1, PPW_LOBBY_CHANNEL_KIND_MAIN, PPW_LOBBY_MESSAGE_FORMAT_BINARY, PPW_LOBBY_MESSAGE_KIND_SYSTEM, PPW_LOBBY_SYSTEM_MESSAGE_START_SCHEDULE, &zero, sizeof(zero));
        PPWLobbySchedule_Start(schedule);
        return;
    case PPW_LOBBY_SCHEDULE_STATE_STARTED:
        if (!schedule->pendingEvents.size) {
            return;
        }
        event = schedule->pendingEvents.map.blocks[(schedule->pendingEvents.map.start + (schedule->pendingEvents.start / LOBBY_EVENT_BLOCK_SIZE)) % schedule->pendingEvents.map.capacity] + (schedule->pendingEvents.start % LOBBY_EVENT_BLOCK_SIZE);
        DWC_GetDateTime(&date, &time);
        now = RTC_ConvertDateTimeToSecond(&date, &time);
        if (event->time > now - schedule->startTime) {
            return;
        }
        do {
            LobbyTag tag;
            PPWLobby_GetWork()->callbacks.onLobbyEvent(event->type);
            memset(&tag, 0, sizeof tag);
            LobbyEventDeque_EraseAtBegin(&schedule->pendingEvents, 1, tag);
            if (!schedule->pendingEvents.size) {
                return;
            }
            {
                LobbyEvent *next = schedule->pendingEvents.map.blocks[(schedule->pendingEvents.map.start + (schedule->pendingEvents.start / LOBBY_EVENT_BLOCK_SIZE)) % schedule->pendingEvents.map.capacity] + (schedule->pendingEvents.start % LOBBY_EVENT_BLOCK_SIZE);
                event->time = next->time;
                event->type = next->type;
            }
        } while (event->time <= now - schedule->startTime);
        break;
    }
}

BOOL PPWLobbySchedule_CanStart(PPWLobbySchedule *schedule) {
    RTCTime time;
    RTCDate date;
    s64 now;
    if (schedule->state == PPW_LOBBY_SCHEDULE_STATE_STARTED || PPWLobby_GetWork()->state != PPW_LOBBY_STATE_READY) {
        return FALSE;
    }
    if (schedule->startTime != 0) {
        return FALSE;
    }
    if (schedule->startRequested) {
        return TRUE;
    }
    if (PPWLobbyPlayers_IsFull(&PPWLobby_GetWork()->players)) {
        return TRUE;
    }
    DWC_GetDateTime(&date, &time);
    now = RTC_ConvertDateTimeToSecond(&date, &time);
    return schedule->time.seconds + (s64)(u64)schedule->lockTime < now;
}

BOOL PPWLobbySchedule_Start(PPWLobbySchedule *schedule) {
    RTCTime time;
    RTCDate date;
    if (schedule->state != PPW_LOBBY_SCHEDULE_STATE_STARTED && PPWLobby_GetWork()->state == PPW_LOBBY_STATE_READY) {
        DWC_GetDateTime(&date, &time);
        schedule->startTime = RTC_ConvertDateTimeToSecond(&date, &time);
        schedule->state = PPW_LOBBY_SCHEDULE_STATE_STARTED;
        schedule->startRequested = FALSE;
        PPWLobby_GetWork()->callbacks.onLobbyEvent(0);
        return TRUE;
    }
    schedule->startRequested = TRUE;
    return FALSE;
}
