// Converted from asm/main_menu_data.s (part 6 of 8) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

// The C declarations of these do not match the data (see the notes at each
// definition): keep them out of the way of the definitions below.
#define gFmt_StrLf           gFmt_StrLf_header_decl
#define gFmt_NotMyParentGgid gFmt_NotMyParentGgid_header_decl

#include "global.h"

#include "application/main_menu/agb_cartridge.h"
#include "application/main_menu/main_menu_util.h"

#pragma force_active on

#undef gFmt_StrLf
#undef gFmt_NotMyParentGgid

// C declares this const, but it lives in .data
char gFmt_NotMyParentGgid[32] = "not my parent ggid (%d != %d)\n";

// C declares this const, but it lives in .data
char gFmt_StrLf[4] = "%s\n";
