// Converted from asm/battle_anim_data.s (part 13 of 17) by tools/s2c.py.
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

// clang-format off
const BallThrowFunc gBallThrowBallAnimFuncs[18] = {
    BallThrow_BallAnimThrow, BallThrow_BallAnimOpen, BallThrow_BallAnimDeflect, BallThrow_BallAnimFall,
    BallThrow_BallAnimShake, BallThrow_BallAnimSkip, BallThrow_BallAnimClick, BallThrow_BallAnimFade, NULL,
    (BallThrowFunc)0x00000002, (BallThrowFunc)0x00000002, (BallThrowFunc)0x00000002,
    (BallThrowFunc)0x00000002, (BallThrowFunc)0x00000006, (BallThrowFunc)0x00000001,
    (BallThrowFunc)0x00000006, NULL, (BallThrowFunc)0x00000006,
};
// clang-format on

const BallThrowFlashingKinds gBallThrowFlashingKinds = {
    { 6, 7, 8, 9, 0x0000000A, 0x0000000B }
};

// clang-format off
const BallThrowFunc gBallThrowModeFuncs[6] = {
    BallThrow_RunThrowArc, BallThrow_ThrowArcAndOpen, BallThrow_Wobble, BallThrow_RunCaptureState,
    BallThrow_TrackPosition, BallThrow_OpenInPlace,
};
// clang-format on

const BallThrowStaticSpriteKinds gBallThrowStaticSpriteKinds = {
    { 3, 5, 1 }
};
