// Converted from asm/frontier_script_commands_data.s (part 3 of 11) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

#include "global.h"

#include "frontier/battle_factory_setup.h"
#include "frontier/battle_hall_setup.h"
#include "frontier/battle_tower_setup.h"
#include "frontier/frontier_link_lobby.h"

#include "frontier_script_commands_misc_internal.h"

#pragma force_active on

// clang-format off
const u8 gBattleArcadePlayerMonIconPositions[16] = {
    0x21, 0x00, 0x14, 0x00, 0x27, 0x00, 0x2B, 0x00, 0x2B, 0x00, 0x42, 0x00, 0x2E, 0x00, 0x59, 0x00,
};
// clang-format on

// clang-format off
const u8 gBattleArcadeOpponentMonIconPositions[16] = {
    0xDE, 0x00, 0x14, 0x00, 0xD8, 0x00, 0x2B, 0x00, 0xD5, 0x00, 0x42, 0x00, 0xD2, 0x00, 0x59, 0x00,
};
// clang-format on

const u16 gBattleArcadeBerries_Rank0[8] = { 0x0095, 0x0096, 0x0097, 0x0098, 0x0099, 0x009C, 0x009E, 0x009D };

// MWCC gives a char array a section of its own, which the linker starts 4-aligned; to stay at
// offset 0x32 next to its neighbours it is written as the only row of a 2-D array, which shares
// their section.
const u8 gBattleArcadeRankBattlePoints[1][10] = {
    { 0x03, 0x0A, 0x05, 0x06, 0x07, 0x04, 0x09, 0x02, 0x0A, 0x00 }
};

// MWCC gives a char array a section of its own, which the linker starts 4-aligned; to stay at
// offset 0x2c next to its neighbours it is written as the only row of a 2-D array, which shares
// their section.
const u8 gBattleArcadeRoundCursorSpeeds[1][6] = {
    { 0x07, 0x05, 0x04, 0x04, 0x00, 0x03 }
};
