// Converted from asm/dwc_lobby_data.s (part 3 of 5) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

// The C declarations of these do not match the data (see the notes at each
// definition): keep them out of the way of the definitions below.
#define gLobbyMemReserve gLobbyMemReserve_header_decl

#include "global.h"

#include "lobby_chat_internal.h"
#include "lobby_chat_manager.h"
#include "lobby_event_deque.h"
#include "ppw_lobby_work.h"

#pragma force_active on

#undef gLobbyMemReserve

// 0x02254E05
// MWCC gives a char array a section of its own, which the linker starts 4-aligned; to stay at
// offset 0x101 next to its neighbours it is written as the only row of a 2-D array, which shares
// their section.
const char gStatsUploadStr_0123456789abcdef_2[1][17] = { "0123456789abcdef" };

// 0x02254DF4
// MWCC gives a char array a section of its own, which the linker starts 4-aligned; to stay at
// offset 0xf0 next to its neighbours it is written as the only row of a 2-D array, which shares
// their section.
const char gStatsUploadStr_0123456789abcdef[1][17] = { "0123456789abcdef" };

// 0x022577E4
VoidFunc gLobbyMemOutOfMemoryHandler;

// 0x022577E8
// A header declares it differently.
u8 gLobbyMemReserve[8];
