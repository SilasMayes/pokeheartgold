// Converted from asm/battle_controller_opponent_data.s (part 2 of 2) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

#include "global.h"

#include "constants/pokemon.h"
#include "constants/sndseq.h"

#pragma force_active on

// 0x0226D350
// clang-format off
const u8 gBattleEncounterTerrains[24] = {
    0x09, 0x17, 0x05, 0x13, 0x0D, 0x11, 0x0F, 0x07, 0x15, 0x0B, 0x19, 0x0B, 0x0B, 0x0B, 0x0B, 0x0B, 0x0B,
    0x15, 0x0B, 0x0B, 0x0B, 0x0B, 0x0B, 0x0B,
};
// clang-format on
