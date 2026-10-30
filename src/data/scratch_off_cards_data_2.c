// Converted from asm/scratch_off_cards_data.s (part 2 of 9) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

#include "global.h"

#pragma force_active on

// clang-format off
const u8 gScratchOffCardsResultSpritePositions[12] = {
    0x34, 0x00, 0x44, 0x00, 0x6C, 0x00, 0x44, 0x00, 0xA4, 0x00, 0x44, 0x00,
};
// clang-format on

const u8 gScratchOffCardsLastCardButtonHitbox[8] = { 0xA4, 0xBF, 0x5E, 0xA4, 0xFF, 0x00, 0x00, 0x00 };

const u8 gScratchOffCardsNextCardButtonHitbox[8] = { 0xA4, 0xBF, 0x4C, 0xB4, 0xFF, 0x00, 0x00, 0x00 };

#pragma explicit_zero_data on
// zero bytes after gScratchOffCardsMatchPaletteFiles in the asm
static u8 gScratchOffCardsMatchPaletteFiles_pad[4] = { 0 };
#pragma explicit_zero_data reset
