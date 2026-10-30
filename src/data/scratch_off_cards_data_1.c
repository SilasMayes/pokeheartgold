// Converted from asm/scratch_off_cards_data.s (part 1 of 9) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

#include "global.h"

#pragma force_active on

// clang-format off
static const u8 sScratchOffCardsUnusedPositions[16] __attribute__((aligned(4))) = {
    0x58, 0x00, 0xA0, 0x00, 0x44, 0x00, 0xA0, 0x00, 0x26, 0x00, 0x38, 0x00, 0x44, 0x00, 0x44, 0x00,
};
// clang-format on

// clang-format off
u8 gScratchOffCardsMatchPaletteFiles[8] __attribute__((aligned(4))) = {
    0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D,
};
// clang-format on
