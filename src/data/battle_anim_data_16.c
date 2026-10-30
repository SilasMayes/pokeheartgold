// Converted from asm/battle_anim_data.s (part 16 of 17) by tools/s2c.py.
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

const BattleAnimEmitterCounts gBattleAnimEmitterCounts = {
    { 5, 0x0000000B, 6, 7, 2, 1, 2, 1, 1, 4, 3, 3, 2, 9, 1, 1, 1, 2, 1, 1, 1, 1 },
};

const BallSealEmitDelays gBallSealEmitDelays = {
    { 0x00, 0x08, 0x0E, 0x14, 0x14, 0x10, 0x10 }
};
