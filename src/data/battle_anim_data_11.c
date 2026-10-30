// Converted from asm/battle_anim_data.s (part 11 of 17) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

// The C declarations of these do not match the data (see the notes at each
// definition): keep them out of the way of the definitions below.
#define gBattleAnimObjWindowBgFiles gBattleAnimObjWindowBgFiles_header_decl

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

#undef gBattleAnimObjWindowBgFiles

// C declares this as `const BattleAnimObjWindowBgFiles gBattleAnimObjWindowBgFiles[]`, but the label
// holds 12 more bytes of data after it.
const struct {
    u32 unk0[16];
    u8 unk40[12];
} gBattleAnimObjWindowBgFiles = {
    { 0x36, 0x126, 0x37, 0x37, 0x30, 0x123, 0x31, 0x31, 0x32, 0x124, 0x33, 0x33, 0x34, 0x125, 0x35, 0x35 },
    { 0x00, 0x17, 0x00, 0x00, 0x00, 0x4D, 0x00, 0x00, 0x00, 0xF0, 0xFF, 0xFF },
};

const u16 gBattleAnimDarkSpriteDrawFlags[6] __attribute__((aligned(4))) = { 0, 0, 1, 0, 0, 1 };
