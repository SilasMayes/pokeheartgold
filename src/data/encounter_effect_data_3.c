// Converted from asm/encounter_effect_data.s (part 3 of 3) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

// The C declarations of these do not match the data (see the notes at each
// definition): keep them out of the way of the definitions below.
#define gBlockWipeColumnOrder gBlockWipeColumnOrder_header_decl

#include <nitro/fs/overlay.h>

#include "global.h"

#include "field/encounter_effect.h"

#pragma force_active on

#undef gBlockWipeColumnOrder

// C declares this non-const, but it lives in .rodata
const u8 gBlockWipeColumnOrder[8] = { 0x00, 0x02, 0x05, 0x07, 0x01, 0x06, 0x03, 0x04 };
