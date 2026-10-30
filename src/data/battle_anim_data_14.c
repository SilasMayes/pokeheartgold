// Converted from asm/battle_anim_data.s (part 14 of 17) by tools/s2c.py.
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
const BallThrowFunc gBallThrowCaptureStateFuncs[28] = {
    BallThrow_CaptureStateIdle, BallThrow_CaptureStateThrow, BallThrow_CaptureStateGoToOpen,
    BallThrow_CaptureStateOpen, BallThrow_CaptureStateOpenDone, BallThrow_CaptureStateDeflect,
    BallThrow_CaptureStateDeflectDone, BallThrow_CaptureStateStartFall, BallThrow_CaptureStateGoToFlash,
    BallThrow_CaptureStateFlash, BallThrow_CaptureStateGoToDrop, BallThrow_CaptureStateDrop,
    BallThrow_CaptureStateNone, BallThrow_CaptureStateBounce, BallThrow_CaptureStateBounceDone,
    BallThrow_CaptureStateShakeWait, BallThrow_CaptureStateGoToShake, BallThrow_CaptureStateShake,
    BallThrow_CaptureStateShakeDone, BallThrow_CaptureStateGoToSkip, BallThrow_CaptureStateSkip,
    BallThrow_CaptureStateClick, BallThrow_CaptureStateClickDone, BallThrow_CaptureStateRestorePalette,
    BallThrow_CaptureStateGoToFadeOut, BallThrow_CaptureStateFadeOut, BallThrow_CaptureStateGoToEnd,
    BallThrow_CaptureStateEnd,
};
// clang-format on

// clang-format off
const s16 gBallThrowShakeOffsets[36] = {
    -2, 0, 2, 2, 0, -2, 255, 255, 255, 0, 0, 0, -1, 0, 1, 1, 0, -1, 255, 255, 255, 0, 0, 0, -1, 0, 1, 1, 0,
    -1, 0, 0, 0, 0, 0, 255,
};
// clang-format on

const BallThrowSpinningKinds gBallThrowSpinningKinds = {
    { 6, 7, 8, 9, 0x0000000A, 0x0000000B, 0x0000000C, 0x0000000D, 0x0000000F, 0x00000010, 0x00000011 },
};

const BallThrowBounceSound gBallThrowBounceSounds[5] = {
    { 1,  1510 },
    { 8,  1510 },
    { 14, 1511 },
    { 18, 1512 },
    { 20, 1513 },
};
