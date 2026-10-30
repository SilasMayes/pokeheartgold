// Converted from asm/battle_anim_data.s (part 17 of 17) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

#include "global.h"

#include "battle/battle_anim_ball.h"
#include "battle/battle_anim_battler_util.h"
#include "battle/battle_anim_effects.h"
#include "battle/battle_anim_emitter.h"
#include "battle/battle_anim_funcs.h"
#include "battle/battle_anim_internal.h"
#include "battle/battle_anim_move_effects.h"
#include "battle/battle_anim_util.h"

#pragma force_active on

const s16 gBattlerPokepicPositions[2][6][3] = {
    {
     { 0x0150, 0x0070, (s16)0xFE00 },
     { (s16)0xFFB0, 0x0032, (s16)0xFD80 },
     { 0x013C, 0x0070, (s16)0xFE00 },
     { (s16)0xFFC4, 0x0032, (s16)0xFF9C },
     { 0x0164, 0x0078, 0x0000 },
     { (s16)0xFF9C, 0x002A, (s16)0xFD80 },
     },
    {
     { (s16)0xFFB0, 0x0070, (s16)0xFE00 },
     { 0x0150, 0x0032, (s16)0xFD80 },
     { (s16)0xFFB0, 0x0070, (s16)0xFE00 },
     { 0x0150, 0x0032, (s16)0xFD80 },
     { (s16)0xFFB0, 0x0070, (s16)0xFE00 },
     { 0x0150, 0x0032, (s16)0xFD80 },
     },
};

const s16 gBattlerSlideInTargetX[6][2] = {
    { 64,  32  },
    { 192, 224 },
    { 40,  32  },
    { 216, 224 },
    { 80,  32  },
    { 176, 224 },
};
