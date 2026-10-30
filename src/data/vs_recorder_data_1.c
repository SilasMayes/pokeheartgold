// Converted from asm/vs_recorder_data.s (part 1 of 14) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

#include "global.h"

#include "application/vs_recorder/vs_recorder_screens.h"

#pragma force_active on

const VsRecorderBoxWindowRect sVsRecorderBoxListButtonWindows[4] = {
    { 0x08, 0x03, 0x10, 0x02 },
    { 0x09, 0x0A, 0x0E, 0x02 },
    { 0x79, 0x00, 0x00, 0x00 },
    { 0x3B, 0x00, 0x00, 0x00 },
};

const TouchscreenHitbox gVsRecorderBoxDataHitboxes[2] = {
    { 0x20, 0x60, 0x48, 0xB8 },
    { 0x98, 0xB8, 0x50, 0xB0 },
};

const VsRecorderBoxWindowRect gVsRecorderBoxListTitleWindows[1] __attribute__((aligned(4))) = {
    { 0x04, 0x03, 0x18, 0x02 },
};
