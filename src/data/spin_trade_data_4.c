// Converted from asm/spin_trade_data.s (part 4 of 6) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

#include "global.h"

#pragma force_active on

// 0x021EA594
// clang-format off
const u8 gSpinTradeResObjCounts[24] = {
    0x60, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00,
    0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00,
};
// clang-format on

// 0x021EA580
const int gSpinTradeMarkerAnimIds[5] = { 11, 12, 13, 14, 15 };
