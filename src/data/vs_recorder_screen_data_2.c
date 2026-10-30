// Converted from asm/vs_recorder_screen_data.s (part 2 of 3) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

#include "global.h"

#include "msgdata/msg/msg_0013.h"

#include "vs_recorder_app_internal.h"

#pragma force_active on

extern const struct VsRecorderMenuEntry sVsRecorderQuitMenu[5];

// not static: used in another part of asm/vs_recorder_screen_data.s
const struct VsRecorderMenuEntry sVsRecorderMode6Menu[3] = {
    { 1, 1, msg_0013_00059, 1, 11, 3, 0xFBFBFBFB, (int)0xFBFBFBFB, NULL                },
    { 1, 1, msg_0013_00058, 1, 10, 3, 100,        (int)0xFBFBFBFB, NULL                },
    { 1, 1, msg_0013_00002, 2, 2,  3, 999,        (int)0xFBFBFBFB, sVsRecorderQuitMenu },
};
