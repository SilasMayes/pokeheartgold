// Converted from asm/dwc_lobby_data.s (part 2 of 5) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

#include "global.h"

#include "lobby_chat_internal.h"
#include "lobby_chat_manager.h"
#include "lobby_event_deque.h"
#include "ppw_lobby_work.h"

#pragma force_active on

extern const u8 gLobbyStr_D[];
extern const u8 gLobbyStr_D1[];
extern const u8 gLobbyStr_D2[];
extern const u8 gLobbyStr_D3[];
extern const u8 gLobbyStr_D4[];
extern const u8 gLobbyStr_D5[];
extern const u8 gLobbyStr_D6[];
extern const u8 gLobbyStr_D7[];
extern const u8 gLobbyStr_D8[];
extern const u8 gLobbyStr_D9[];
extern const u8 gLobbyStr_R[];
extern const u8 gLobbyStr_T[];

// 0x02254DC4
const void *const gLobbyChatPrefixNames[12] = {
    gLobbyStr_R,
    gLobbyStr_D,
    gLobbyStr_D1,
    gLobbyStr_D2,
    gLobbyStr_D3,
    gLobbyStr_D4,
    gLobbyStr_D5,
    gLobbyStr_D6,
    gLobbyStr_D7,
    gLobbyStr_D8,
    gLobbyStr_D9,
    gLobbyStr_T,
};

// 0x02254DBC
const char gLobbyStr_GSP[8] = "#GSP";

// 0x022577DC
LobbyChatManager *gLobbyChatManager;

// 0x022577E0
u8 gLobbyChatNextRequestId[4];
