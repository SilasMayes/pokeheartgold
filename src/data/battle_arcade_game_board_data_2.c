// Converted from asm/battle_arcade_game_board_data.s (part 2 of 3) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

// The C declarations of these do not match the data (see the notes at each
// definition): keep them out of the way of the definitions below.
#define gBattleArcadeGameBoardResObjCounts gBattleArcadeGameBoardResObjCounts_header_decl

#include "global.h"

#pragma force_active on

#undef gBattleArcadeGameBoardResObjCounts

// clang-format off
const u8 gBattleArcadeGameBoardCharTransferTemplate[16] = {
    0x20, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x6E, 0x00, 0x00, 0x00,
};
// clang-format on

// clang-format off
const u8 gBattleArcadeGameBoardWindowTemplates[16] = {
    0x01, 0x02, 0x13, 0x1B, 0x04, 0x0C, 0x01, 0x00, 0x01, 0x18, 0x0D, 0x07, 0x04, 0x0D, 0x6D, 0x00,
};
// clang-format on

// C declares this non-const, but it lives in .rodata
const u8 gBattleArcadeGameBoardResObjCounts[4] = { 0x0B, 0x0B, 0x0B, 0x0B };
