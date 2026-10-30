// Converted from asm/battle_anim_data.s (part 9 of 17) by tools/s2c.py.
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

const BattleAnimRockStep gBattleAnimRockAttackerSteps[5] = {
    { 3640, 3 },
    { 2730, 3 },
    { 1820, 2 },
    { 910,  2 },
    { 0,    1 },
};

const BattleAnimAfterimagePass gBattleAnimAttackerAfterimagePasses[4] = {
    { 0,  32, 7  },
    { 0,  32, 10 },
    { 32, 0,  7  },
    { 32, 0,  10 },
};

const s16 gBattleAnimShakeBattlefieldAmplitudes[8] = { 12, 10, 8, 6, 4, 2, 1, 0 };

const BattleAnimScaleStepXY gBattleAnimCrossingSpritesScales[3] = {
    { 0x64, 0x64, 0x64, 0x46, 0x08 },
    { 0x64, 0x64, 0x46, 0x78, 0x03 },
    { 0x64, 0x64, 0x78, 0x64, 0x03 },
};

const BattleAnimScaleStepXY gBattleAnimAttackerStretchSteps[3] = {
    { 0x64, 0x96, 0x64, 0x32, 0x08 },
    { 0x96, 0x32, 0x32, 0x96, 0x08 },
    { 0x32, 0x64, 0x96, 0x64, 0x08 },
};

const BattleAnimScaleStepXY gBattleAnimAttackerHopScales[3] = {
    { 0x64, 0x78, 0x64, 0x50, 0x05 },
    { 0x78, 0x64, 0x50, 0x78, 0x05 },
    { 0x64, 0x64, 0x78, 0x64, 0x05 },
};

const s8 gBattleAnimCrossingSpritesArcSigns[5][2] = {
    { 0x01,     (s8)0xFF },
    { (s8)0xFF, 0x01     },
    { 0x01,     (s8)0xFF },
    { 0x01,     (s8)0xFF },
    { 0x01,     (s8)0xFF },
};

const BattleAnimScaleStepXY gBattleAnimLeapOffscreenSteps[2] = {
    { 0x64, 0x0A, 0x64, 0xB4, 0x0A },
    { 0x0A, 0x0A, 0xB4, 0x00, 0x05 },
};

const BattleAnimHopStep gBattleAnimAttackerHopOffsets[3] = {
    { 0x00, 0x10, 0x05 },
    { 0x10, 0x00, 0x05 },
    { 0x00, 0x00, 0x05 },
};

const u8 gBattleAnimBlinkScaleFadeTimings[3][2] = {
    { 0x08, 0x02 },
    { 0x0D, 0x01 },
    { 0x12, 0x03 }
};

const BattleAnimScaleStep gBattleAnimPulseWhiteSteps[2] = {
    { 0x64, 0x73, 0x06 },
    { 0x73, 0x64, 0x06 }
};

const u8 gBattleAnimSquashAfterimageDelays[4] = { 0x02, 0x07, 0x0D, 0x12 };
