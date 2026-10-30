// Converted from asm/touchscreen_menu_data.s (part 7 of 10) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

#include "global.h"

#pragma force_active on

const u8 gTouchscreenMenuActionTypeToString[8] = { 0x01, 0x00, 0x01, 0x03, 0x04, 0x00, 0x00, 0x00 };

// global: C declares it extern although the asm label was local
const u8 sTouchscreenChoiceMenu2ItemNeighbors[8] = { 0x00, 0x01, 0xFF, 0xFF, 0x00, 0x01, 0xFF, 0xFF };
