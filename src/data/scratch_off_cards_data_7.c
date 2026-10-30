// Converted from asm/scratch_off_cards_data.s (part 7 of 9) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

#include "global.h"

#pragma force_active on

// clang-format off
const s8 gScratchOffCardsBounceY[8] = {
    (s8)0xFC, (s8)0xFC, (s8)0xFC, (s8)0xFC, (s8)0xFC, (s8)0xFC, (s8)0xFC, (s8)0xFC,
};
// clang-format on

const u8 gScratchOffCardsPrizeNameY[4] = { 0x0A, 0x0C, 0x06, 0x08 };
