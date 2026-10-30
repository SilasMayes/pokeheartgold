// Converted from asm/frontier_script_commands_data.s (part 5 of 11) by tools/s2c.py.
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
const u8 gBattleArcadeRoundValues_Multi[12] = {
    0x00, 0x07, 0x08, 0x09, 0x0A, 0x0D, 0x0E, 0x10, 0x11, 0x00, 0x00, 0x00,
};
// clang-format on

// clang-format off
const u8 gBattleArcadeRoundValues_Single[12] = {
    0x00, 0x02, 0x02, 0x02, 0x02, 0x04, 0x04, 0x05, 0x06, 0x00, 0x00, 0x00,
};
// clang-format on

const u16 gBattleTowerAllySprites[6] = { 0x008D, 0x0091, 0x008E, 0x008F, 0x0090, 0 };
