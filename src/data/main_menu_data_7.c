// Converted from asm/main_menu_data.s (part 7 of 8) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

// The C declarations of these do not match the data (see the notes at each
// definition): keep them out of the way of the definitions below.
#define gStr_IPGE             gStr_IPGE_header_decl
#define gStr_K5WfPEw9T3cvqzHa gStr_K5WfPEw9T3cvqzHa_header_decl

#include "global.h"

#include "application/main_menu/agb_cartridge.h"
#include "application/main_menu/main_menu_util.h"

#pragma force_active on

#undef gStr_IPGE
#undef gStr_K5WfPEw9T3cvqzHa

// C declares this const, but it lives in .data
char gStr_K5WfPEw9T3cvqzHa[20] = "K5WfPEw9T3cvqzHa";

// C declares this const, but it lives in .data
char gStr_IPGE[8] = "IPGE";
