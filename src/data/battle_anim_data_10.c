// Converted from asm/battle_anim_data.s (part 10 of 17) by tools/s2c.py.
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

const BattleAnimScatterArea gBattleAnimScatterAreas[6] = {
    { 30, 40,  50, 53 },
    { 30, 93,  50, 53 },
    { 30, 146, 50, 53 },
    { 80, 40,  50, 53 },
    { 80, 93,  50, 53 },
    { 80, 146, 50, 53 },
};

const BattleAnimPosition gBattleAnimSlidingSpritePairTargets[4][2] = {
    { { 120, 80 }, { 136, 80 } },
    { { 120, 80 }, { 136, 80 } },
    { { 120, 80 }, { 136, 80 } },
    { { 88, 80 },  { 168, 80 } },
};

const s16 gBattleAnimSlidingSpritePairPositions[6][2] = {
    { 80,  50  },
    { 180, 50  },
    { 80,  100 },
    { 180, 100 },
    { 80,  75  },
    { 180, 75  },
};

const BattleAnimPosition gBattleAnimScatterTargets[6] = {
    { 0,   0   },
    { 128, 0   },
    { 256, 0   },
    { 0,   170 },
    { 128, 170 },
    { 256, 170 },
};

const u8 gBattleAnimBlinkCenterTimings[3][2] = {
    { 0x14, 0x02 },
    { 0x0D, 0x01 },
    { 0x12, 0x03 }
};

const u8 gBattleAnimSlidingSpritePairDurations[4] = { 0x05, 0x05, 0x05, 0x03 };
