// Converted from asm/main_menu_data.s (part 8 of 8) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

// The C declarations of these do not match the data (see the notes at each
// definition): keep them out of the way of the definitions below.
#define gMysteryGiftWfcEmptyString gMysteryGiftWfcEmptyString_header_decl

#include "global.h"

#include "application/main_menu/agb_cartridge.h"
#include "application/main_menu/main_menu_util.h"

#pragma force_active on

#undef gMysteryGiftWfcEmptyString

#pragma explicit_zero_data on
// C declares this const, but it lives in .data
char gMysteryGiftWfcEmptyString[4] = { 0x00, 0x00, 0x00, 0x00 };
#pragma explicit_zero_data reset
