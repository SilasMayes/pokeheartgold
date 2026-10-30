// Converted from asm/battle_anim_data.s (part 4 of 17) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

// The C declarations of these do not match the data (see the notes at each
// definition): keep them out of the way of the definitions below.
#define gBattleAnimEmitterFlagCallbacks gBattleAnimEmitterFlagCallbacks_header_decl
#define gBattleAnimSpriteDrawPriorities gBattleAnimSpriteDrawPriorities_header_decl

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

#undef gBattleAnimEmitterFlagCallbacks
#undef gBattleAnimSpriteDrawPriorities

const BattleAnimEmitterFlagMasks gBattleAnimEmitterFlagMasks = {
    { 0, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 65278 },
};

// C declares this non-const, but it lives in .rodata
// clang-format off
const BattleAnimEmitterConfigCb gBattleAnimEmitterFlagCallbacks[14] = {
    BattleAnimEmitterFlagCb_Nop0, BattleAnimEmitterFlagCb_SetGravity, BattleAnimEmitterFlagCb_Nop2,
    BattleAnimEmitterFlagCb_Nop3, BattleAnimEmitterFlagCb_SetMagnetPos,
    BattleAnimEmitterFlagCb_SetMagnetForce, BattleAnimEmitterFlagCb_SetSpinAngle,
    BattleAnimEmitterFlagCb_SetSpinAxis, BattleAnimEmitterFlagCb_Nop8, BattleAnimEmitterFlagCb_Nop9,
    BattleAnimEmitterFlagCb_Nop10, BattleAnimEmitterFlagCb_Nop11, BattleAnimEmitterFlagCb_SetConvergencePos,
    BattleAnimEmitterFlagCb_SetConvergenceForce,
};
// clang-format on

// C declares this const, but it lives in .data
int gBattleAnimSpriteDrawPriorities[4] = { 20, 10, 10, 20 };
