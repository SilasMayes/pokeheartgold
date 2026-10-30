// Converted from asm/dwc_lobby_data.s (part 4 of 5) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

// The C declarations of these do not match the data (see the notes at each
// definition): keep them out of the way of the definitions below.
#define ciCookieBuffer  ciCookieBuffer_header_decl
#define ciCookieCounter ciCookieCounter_header_decl
#define ciSendfBuffer   ciSendfBuffer_header_decl

#include "global.h"

#include "lobby_chat_internal.h"
#include "lobby_chat_manager.h"
#include "lobby_event_deque.h"
#include "ppw_lobby_work.h"

#pragma force_active on

#undef ciCookieBuffer
#undef ciCookieCounter
#undef ciSendfBuffer

// 0x022577F4
// C declares this as `int ciCookieCounter`, but s2c could not read that type (its header needs
// generated files).
u8 ciCookieCounter[4];

// 0x022577F0
// C declares this as `char ciCookieBuffer[]`, but s2c could not read that type (its header needs
// generated files).
u8 ciCookieBuffer[4];

// 0x022577F8
// C declares this as `char ciSendfBuffer[]`, but s2c could not read that type (its header needs
// generated files).
u8 ciSendfBuffer[4096];
