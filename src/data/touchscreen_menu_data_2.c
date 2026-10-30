// Converted from asm/touchscreen_menu_data.s (part 2 of 10) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

#include "global.h"

#pragma force_active on

const u32 gTouchscreenMenuActionMsgIds[5] = { 0x00000011, 0x00000012, 0x00000013, 0x00000016, 0x00000017 };
