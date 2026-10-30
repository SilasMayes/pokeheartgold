// Converted from asm/dwc_lobby_data.s (part 5 of 5) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

// The C declarations of these do not match the data (see the notes at each
// definition): keep them out of the way of the definitions below.
#define gStatsUploadRandomState gStatsUploadRandomState_header_decl

#include "global.h"

#include "lobby_chat_internal.h"
#include "lobby_chat_manager.h"
#include "lobby_event_deque.h"
#include "ppw_lobby_work.h"

#pragma force_active on

#undef gStatsUploadRandomState

// 0x022587F8
// C declares this as `u32 gStatsUploadRandomState`, but s2c could not read that type (its header needs
// generated files).
u8 gStatsUploadRandomState[8];
