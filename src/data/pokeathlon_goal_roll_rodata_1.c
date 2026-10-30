// Converted from asm/pokeathlon_goal_roll_rodata.s (part 1 of 3) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

#include "global.h"

#include "pokeathlon/pokeathlon_goal_roll.h"

#pragma force_active on

const PokeathlonGoalRollWindowData gPokeathlonGoalRollWindowData = {
    { 0x03, 0x00, 0x14, 0x20, 0x02, 0x0F, 1 },
    { 0, 0x4000, 0xC000, 0x8000 },
};

const u8 gPokeathlonGoalRollPaletteData[4] __attribute__((aligned(4))) = { 0x01, 0x03, 0x01, 0x02 };
