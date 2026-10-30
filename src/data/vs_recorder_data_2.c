// Converted from asm/vs_recorder_data.s (part 2 of 14) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

#include "global.h"

#include "application/vs_recorder/vs_recorder_screens.h"

#pragma force_active on

// clang-format off
const u32 gVsRecorderBoxDataWindowFillColors[9] = {
    0, 0, 0x000000CC, 0x0000001B, 0x00000013, 0x0000001A, 0x000F0D00, 0x000F0100, 0x000F0D00,
};
// clang-format on

const TouchscreenHitbox gVsRecorderBoxListHitboxes[3] = {
    { 0x10, 0x30, 0x38, 0xC8 },
    { 0x40, 0x70, 0x38, 0xC8 },
    { 0x98, 0xB8, 0x50, 0xB0 },
};
