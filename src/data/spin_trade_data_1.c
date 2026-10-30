// Converted from asm/spin_trade_data.s (part 1 of 6) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

// The C declarations of these do not match the data (see the notes at each
// definition): keep them out of the way of the definitions below.
#define gSpinTradeHoverOffsets gSpinTradeHoverOffsets_header_decl

#include "global.h"

#pragma force_active on

#undef gSpinTradeHoverOffsets

// C declares this const, but it lives in .data
int gSpinTradeHoverOffsets[16] = { 4, 6, 8, 10, 11, 12, 12, 12, 11, 10, 9, 8, 6, 4, 0, 0 };

// clang-format off
const u8 gSpinTradeBonusRanges5P[16] = {
    0x00, 0x00, 0xD7, 0x00, 0x43, 0x01, 0x67, 0x01, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00,
};
// clang-format on

const u8 gSpinTradeBonusRanges3P[8] = { 0x00, 0x00, 0xC6, 0x00, 0x56, 0x01, 0x67, 0x01 };

// 0x021EA4FC
const u8 gSpinTradeMsgWindowTemplate[8] = { 0x01, 0x02, 0x13, 0x1A, 0x04, 0x0F, 0x28, 0x00 };

const u8 gSpinTradeBonusRanges2P[4] __attribute__((aligned(4))) = { 0x00, 0x00, 0xB4, 0x00 };
