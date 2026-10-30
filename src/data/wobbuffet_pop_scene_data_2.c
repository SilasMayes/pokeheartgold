// Converted from asm/wobbuffet_pop_scene_data.s (part 2 of 2) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

#include "global.h"

#include "wobbuffet_pop_internal.h"

#pragma force_active on

extern void WobbuffetPop_HandleCountdownEvent(void);
extern void WobbuffetPop_HandleDemoEvent(void);
extern void WobbuffetPop_HandleFinishEvent(void);
extern void WobbuffetPop_HandleNewBalloonEvent(void);
extern void WobbuffetPop_HandlePopEvent(void);
extern void WobbuffetPop_HandlePumpEvent(void);
extern void WobbuffetPop_HandleSyncEvent(void);

// clang-format off
void (*const gWobbuffetPopEventFuncs[8])(WobbuffetPop *game, WobbuffetPopEvent *event) = {
    NULL, (void (*)(WobbuffetPop *, WobbuffetPopEvent *))WobbuffetPop_HandlePumpEvent,
    (void (*)(WobbuffetPop *, WobbuffetPopEvent *))WobbuffetPop_HandlePopEvent,
    (void (*)(WobbuffetPop *, WobbuffetPopEvent *))WobbuffetPop_HandleNewBalloonEvent,
    (void (*)(WobbuffetPop *, WobbuffetPopEvent *))WobbuffetPop_HandleCountdownEvent,
    (void (*)(WobbuffetPop *, WobbuffetPopEvent *))WobbuffetPop_HandleFinishEvent,
    (void (*)(WobbuffetPop *, WobbuffetPopEvent *))WobbuffetPop_HandleSyncEvent,
    (void (*)(WobbuffetPop *, WobbuffetPopEvent *))WobbuffetPop_HandleDemoEvent,
};
// clang-format on
