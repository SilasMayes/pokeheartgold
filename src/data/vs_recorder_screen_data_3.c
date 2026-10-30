// Converted from asm/vs_recorder_screen_data.s (part 3 of 3) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

#include "global.h"

#include "msgdata/msg/msg_0013.h"

#include "vs_recorder_app_internal.h"

#pragma force_active on

extern const struct VsRecorderMenuEntry sVsRecorderMode0Menu[5];
extern const struct VsRecorderMenuEntry sVsRecorderMode1Menu[5];
extern const struct VsRecorderMenuEntry sVsRecorderMode2Menu[5];
extern const struct VsRecorderMenuEntry sVsRecorderMode3Menu[5];
extern const struct VsRecorderMenuEntry sVsRecorderMode4Menu[5];
extern const struct VsRecorderMenuEntry sVsRecorderMode5Menu[5];
extern const struct VsRecorderMenuEntry sVsRecorderMode6Menu[3];

const VsRecorderMenuEntry sVsRecorderRootMenu[7] = {
    { 1, 1, 255, 65535, 0, 9, 0xFBFBFBFB, (int)0xFBFBFBFB, sVsRecorderMode0Menu },
    { 1, 1, 255, 65535, 0, 9, 0xFBFBFBFB, (int)0xFBFBFBFB, sVsRecorderMode1Menu },
    { 1, 1, 255, 65535, 0, 9, 0xFBFBFBFB, (int)0xFBFBFBFB, sVsRecorderMode2Menu },
    { 1, 1, 255, 65535, 0, 9, 0xFBFBFBFB, (int)0xFBFBFBFB, sVsRecorderMode3Menu },
    { 1, 1, 255, 65535, 0, 9, 0xFBFBFBFB, (int)0xFBFBFBFB, sVsRecorderMode4Menu },
    { 1, 1, 255, 65535, 0, 9, 0xFBFBFBFB, (int)0xFBFBFBFB, sVsRecorderMode5Menu },
    { 1, 1, 255, 65535, 0, 9, 0xFBFBFBFB, (int)0xFBFBFBFB, sVsRecorderMode6Menu },
};

// clang-format off
const u8 sVsRecorderMode6MenuTail[68] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};
// clang-format on

// zero bytes after sVsRecorderMode6Menu in the asm
static const u8 sVsRecorderMode6Menu_pad[4] = { 0 };
