// Converted from asm/vs_recorder_data.s (part 14 of 14) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

// The C declarations of these do not match the data (see the notes at each
// definition): keep them out of the way of the definitions below.
#define gVsRecorderDeleteSubStates gVsRecorderDeleteSubStates_header_decl

#include "global.h"

#include "application/vs_recorder/vs_recorder_screens.h"

#pragma force_active on

#undef gVsRecorderDeleteSubStates

// C declares this non-const, but it lives in .rodata
// clang-format off
const VsRecorderScreenFunc gVsRecorderDeleteSubStates[4] = {
    VsRecorder_DeleteInit, VsRecorder_DeleteEnter, VsRecorder_DeleteMain, VsRecorder_DeleteExit,
};
// clang-format on

const TouchscreenHitbox gVsRecorderDeleteYesHitbox = { 0x28, 0x48, 0x20, 0x78 };

const TouchscreenHitbox gVsRecorderDeleteNoHitbox = { 0x28, 0x48, 0x90, 0xE8 };
