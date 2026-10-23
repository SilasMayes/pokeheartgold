#include <nitro/types.h>

#include <nitro/code32.h>

#include "ppw_lobby_work.h"

BOOL PPWLobbySchedule_SetVipRecords(PPWLobbySchedule *schedule, const void *data, u32 size) {
    PPWLobbySchedule_ValidateVipRecords(schedule, data, size);
    const PPWLobbyVipRecord *first = (const PPWLobbyVipRecord *)data;
    LobbyVipVector_AssignRange(&schedule->vips, first, first + size / sizeof(PPWLobbyVipRecord), LobbyTag());
    return TRUE;
}
