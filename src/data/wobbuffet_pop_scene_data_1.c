// Converted from asm/wobbuffet_pop_scene_data.s (part 1 of 2) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

// The C declarations of these do not match the data (see the notes at each
// definition): keep them out of the way of the definitions below.
#define gWobbuffetPopCommands gWobbuffetPopCommands_header_decl

#include "global.h"

#include "wobbuffet_pop_internal.h"

#pragma force_active on

#undef gWobbuffetPopCommands

extern void CommCmd_GetSize0(void);
extern void WobbuffetPop_GetEventCommandSize(void);
extern void WobbuffetPop_GetPlayerValueCommandSize(void);
extern void WobbuffetPop_RecvEvent(void);
extern void WobbuffetPop_RecvFinished(void);
extern void WobbuffetPop_RecvPlayerValue(void);

// C declares this as `const u32 gWobbuffetPopCommands[]`, but an address sits where that type has an
// integer field.
void (*const gWobbuffetPopCommands[12])(void) = {
    NULL,
    CommCmd_GetSize0,
    NULL,
    WobbuffetPop_RecvPlayerValue,
    WobbuffetPop_GetPlayerValueCommandSize,
    NULL,
    WobbuffetPop_RecvEvent,
    WobbuffetPop_GetEventCommandSize,
    NULL,
    WobbuffetPop_RecvFinished,
    CommCmd_GetSize0,
    NULL,
};

const s32 gWobbuffetPopBalloonAirRates[3] = { 100, 125, 88 };
