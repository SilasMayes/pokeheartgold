// Converted from asm/wobbuffet_pop_data.s (part 1 of 4) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

#include "global.h"

#include "wobbuffet_pop_internal.h"

#pragma force_active on

extern void WobbuffetPop_HostFinishGame(void);
extern void WobbuffetPop_HostPlayGame(void);
extern void WobbuffetPop_HostStartGame(void);

// clang-format off
BOOL (*const gWobbuffetPopHostSteps[6])(WobbuffetPop *game, WobbuffetPopSequence *sequence) = {
    (BOOL (*)(WobbuffetPop *, WobbuffetPopSequence *))WobbuffetPop_HostStartGame,
    (BOOL (*)(WobbuffetPop *, WobbuffetPopSequence *))WobbuffetPop_HostPlayGame,
    (BOOL (*)(WobbuffetPop *, WobbuffetPopSequence *))WobbuffetPop_HostFinishGame, NULL,
    (BOOL (*)(WobbuffetPop *, WobbuffetPopSequence *))0x0001881E,
    (BOOL (*)(WobbuffetPop *, WobbuffetPopSequence *))0x00005000,
};
// clang-format on

const CameraAngle gWobbuffetPopCameraAngle __attribute__((aligned(4))) = { 0, 0, 0, 0 };
