// Converted from asm/battle_anim_data.s (part 5 of 17) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

// The C declarations of these do not match the data (see the notes at each
// definition): keep them out of the way of the definitions below.
#define gBattleAnimEmitterCameraAngles gBattleAnimEmitterCameraAngles_header_decl

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

#undef gBattleAnimEmitterCameraAngles

// C declares this non-const, but it lives in .rodata
const CameraAngle gBattleAnimEmitterCameraAngles[6] = {
    { 0xC200, 0x1740, 0x1000, 0 },
    { 0,      0,      0xE890, 0 },
    { 0xC200, 0x1740, 0x1000, 0 },
    { 0xD000, 0x2000, 0x1000, 0 },
    { 0x2000, 0x2000, 0,      0 },
    { 0x2420, 0x0EA0, 0,      0 },
};
