// Converted from asm/battle_anim_data.s (part 2 of 17) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

// The C declarations of these do not match the data (see the notes at each
// definition): keep them out of the way of the definitions below.
#define gBattleAnimNoBgPaletteAnimMsg gBattleAnimNoBgPaletteAnimMsg_header_decl

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

#undef gBattleAnimNoBgPaletteAnimMsg

const BattleAnimEmitterOffsetTable gBattleAnimEmitterOffsetsX = {
    {
     { 0, 0, 255, 255, 255, 255 },
     { 0, 0, 255, 255, 255, 255 },
     { 255, 255, 255, -16, 255, -16 },
     { 255, 255, 32, 255, 32, 255 },
     { 255, 255, 255, 16, 255, 4 },
     { 255, 255, -16, 255, 0, 255 },
     },
};

const BattleAnimEmitterOffsetTable gBattleAnimEmitterOffsetsY = {
    {
     { 0, 0, 255, 255, 255, 255 },
     { 0, 0, 255, 255, 255, 255 },
     { 255, 255, 255, 16, 255, 16 },
     { 255, 255, 0, 255, 0, 255 },
     { 255, 255, 255, 0, 255, 0 },
     { 255, 255, 24, 255, 24, 255 },
     },
};

// C declares this const, but it lives in .data
// clang-format off
char gBattleAnimNoBgPaletteAnimMsg[44] = {
    0x42, 0x47, 0x83, 0x70, 0x83, 0x8C, 0x83, 0x62, 0x83, 0x67, 0x83, 0x41, 0x83, 0x6A, 0x83, 0x81, 0x82,
    0xAA, 0x90, 0xDD, 0x92, 0xE8, 0x82, 0xB3, 0x82, 0xEA, 0x82, 0xC4, 0x82, 0xA2, 0x82, 0xC8, 0x82, 0xA2,
    0x42, 0x47, 0x82, 0xC5, 0x82, 0xB7, 0x81, 0x42, 0x00, 0x00,
};
// clang-format on
