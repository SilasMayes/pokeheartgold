// Converted from asm/battle_anim_data.s (part 1 of 17) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

// The C declarations of these do not match the data (see the notes at each
// definition): keep them out of the way of the definitions below.
#define gStr_HaikeiSubSystemLaunchLimit gStr_HaikeiSubSystemLaunchLimit_header_decl

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

#undef gStr_HaikeiSubSystemLaunchLimit

// clang-format off
void (*const gBattleAnimEmitterCallbackTable[23])(SPLEmitter *) = {
    (void (*)(SPLEmitter *))BattleAnimEmitterCb_None,
    (void (*)(SPLEmitter *))BattleAnimEmitterCb_SetPositionAtFirstOpponent,
    (void (*)(SPLEmitter *))BattleAnimEmitterCb_SetPositionAtBattler0,
    (void (*)(SPLEmitter *))BattleAnimEmitterCb_SetPositionAtAttacker,
    (void (*)(SPLEmitter *))BattleAnimEmitterCb_SetPositionAtDefender,
    (void (*)(SPLEmitter *))BattleAnimEmitterCb_AttackerToDefender,
    (void (*)(SPLEmitter *))BattleAnimEmitterCb_DefenderToAttacker,
    (void (*)(SPLEmitter *))BattleAnimEmitterCb_ConvergeBySide,
    (void (*)(SPLEmitter *))BattleAnimEmitterCb_ConvergeUp,
    (void (*)(SPLEmitter *))BattleAnimEmitterCb_ConvergeToDefender,
    (void (*)(SPLEmitter *))BattleAnimEmitterCb_ConvergeToAttacker,
    (void (*)(SPLEmitter *))BattleAnimEmitterCb_ConvergeFromScript,
    (void (*)(SPLEmitter *))BattleAnimEmitterCb_MagnetBySide,
    (void (*)(SPLEmitter *))BattleAnimEmitterCb_MagnetUp,
    (void (*)(SPLEmitter *))BattleAnimEmitterCb_MagnetToDefender,
    (void (*)(SPLEmitter *))BattleAnimEmitterCb_MagnetToAttacker,
    (void (*)(SPLEmitter *))BattleAnimEmitterCb_MagnetFromScript,
    (void (*)(SPLEmitter *))BattleAnimEmitterCb_ConfigureFromScript,
    (void (*)(SPLEmitter *))BattleAnimEmitterCb_SetPositionByBattlerTypes,
    (void (*)(SPLEmitter *))BattleAnimEmitterCb_SetPositionAtAttackerSide,
    (void (*)(SPLEmitter *))BattleAnimEmitterCb_SetPositionAtDefenderSide,
    (void (*)(SPLEmitter *))BattleAnimEmitterCb_SetPositionAtAttacker2,
    (void (*)(SPLEmitter *))BattleAnimEmitterCb_Dummy,
};
// clang-format on

// C declares this const, but it lives in .data
// Shift-JIS: " HaikeiSubSystemコマンド同時起動数の限界です。 "
char gStr_HaikeiSubSystemLaunchLimit[48] __attribute__((aligned(4))) = " HaikeiSubSystem\203R\203}\203\223\203h\223\257\216\236\213N\223\256\220\224\202\314\214\300\212E\202\305\202\267\201B ";
