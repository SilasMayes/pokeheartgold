// Converted from asm/apricorn_box_screens_data.s (part 1 of 3) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

#include "global.h"

#include "application/apricorn_box/apricorn_box_screen_internal.h"

#pragma force_active on

const u8 gApricornBoxQuantityDigitX[4] __attribute__((aligned(4))) = { 0x02, 0x08, 0x00, 0x00 };
