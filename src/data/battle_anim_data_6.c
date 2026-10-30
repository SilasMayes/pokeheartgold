// Converted from asm/battle_anim_data.s (part 6 of 17) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

// The C declarations of these do not match the data (see the notes at each
// definition): keep them out of the way of the definitions below.
#define gBattleAnimEmitterCameraCallbacks gBattleAnimEmitterCameraCallbacks_header_decl

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

#undef gBattleAnimEmitterCameraCallbacks

const BattleAnimPosition gBattleAnimBattlerScreenPositions[2][6] = {
    { { 64, 112 }, { 192, 48 }, { 216, 112 }, { 80, 42 },  { 0, 0 },    { 0, 0 }    },
    { { 64, 112 }, { 192, 48 }, { 40, 112 },  { 216, 50 }, { 80, 120 }, { 176, 42 } },
};

// C declares this non-const, but it lives in .rodata
// clang-format off
const BattleAnimEmitterConfigCb gBattleAnimEmitterCameraCallbacks[9] = {
    BattleAnimEmitterCameraCb_ResetAngle, BattleAnimEmitterCameraCb_SetPresetAngle4,
    BattleAnimEmitterCameraCb_SetAngleFromScript, BattleAnimEmitterCameraCb_SetPresetAngle3,
    BattleAnimEmitterCameraCb_SetAngleByMode, BattleAnimEmitterCameraCb_SetPresetAngle0,
    BattleAnimEmitterCameraCb_SetPresetAngle1, BattleAnimEmitterCameraCb_LookAtBattlerA,
    BattleAnimEmitterCameraCb_LookAtBattlerB,
};
// clang-format on
