// Converted from asm/spin_trade_data.s (part 3 of 6) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

#include "global.h"

#pragma force_active on

// 0x021EA558
const int gSpinTradeMarkerModelIds[5] = { 6, 7, 8, 9, 10 };

// 0x021EA56C
// clang-format off
const u8 gSpinTradeOamCharTransferParam[20] = {
    0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x40, 0x00, 0x00, 0x10, 0x00, 0x10, 0x00,
    0x10, 0x00, 0x00, 0x00,
};
// clang-format on
