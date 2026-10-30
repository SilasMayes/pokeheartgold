// Converted from asm/palpad_data.s (part 5 of 5) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

#include "global.h"

#include "application/palpad/palpad_internal.h"

#pragma force_active on

#pragma explicit_zero_data on
// zero bytes after gPalPadCursorSpriteTemplate in the asm
static u8 gPalPadCursorSpriteTemplate_pad[4] = { 0 };
#pragma explicit_zero_data reset
