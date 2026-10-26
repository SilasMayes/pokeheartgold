#include <nitro/types.h>

#include <nitro/code32.h>

#include "ppw_lobby_work.h"

class Less {};

extern "C" void LobbySort_StableSort(LobbyEventVectorIterator, LobbyEventVectorIterator, Less);

inline LobbyEventVectorIterator Begin(LobbyEventVector *events) {
    return LobbyEventVectorIterator(events->data);
}

inline LobbyEventVectorIterator End(LobbyEventVector *events) {
    return LobbyEventVectorIterator(events->data + events->size);
}

inline void Sort(LobbyEventVectorIterator first, LobbyEventVectorIterator last, Less less) {
    LobbySort_StableSort(first, last, less);
}

inline void Assign(LobbyEventDeque *deque, LobbyEventVectorIterator first, LobbyEventVectorIterator last) {
    LobbyTag tag;
    LobbyEventDeque_Assign(deque, first, last, tag);
}

// Takes over a schedule record from the server: its header, and its events sorted by time.
BOOL PPWLobbySchedule_Load(PPWLobbySchedule *schedule, const void *data, u32 size) {
    const PPWLobbyScheduleRecord *record = (const PPWLobbyScheduleRecord *)data;
    Less less;
    if (!PPWLobbySchedule_IsSizeValid(schedule, data, size)) {
        return FALSE;
    }
    schedule->roomType = record->roomType;
    schedule->season = record->season;
    schedule->lockTime = record->lockTime;
    schedule->unk_20 = record->unk_04;
    schedule->roomFlag = record->roomFlag;
    {
        u32 count = record->eventCount;
        LobbyEventVector_AssignRange(&schedule->events, record->events, record->events + count, LobbyTag());
    }
    Sort(Begin(&schedule->events), End(&schedule->events), less);
    Assign(&schedule->pendingEvents, Begin(&schedule->events), End(&schedule->events));
    return TRUE;
}
