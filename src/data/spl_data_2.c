// Converted from asm/spl_data.s (part 2 of 2) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

// The C declarations of these do not match the data (see the notes at each
// definition): keep them out of the way of the definitions below.
#define gSplAxisY gSplAxisY_header_decl

#include "global.h"

#include "spl_internal.h"

#pragma force_active on

#undef gSplAxisY

// C declares this const, but it lives in .data
VecFx16 gSplAxisY = { 0, 0x1000, 0 };
