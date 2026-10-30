// Converted from asm/vs_recorder_data.s (part 3 of 14) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

#include "global.h"

#include "application/vs_recorder/vs_recorder_screens.h"

#pragma force_active on

const VsRecorderBoxWindowRect gVsRecorderBoxDataWindows[6] = {
    { 0x01, 0x02, 0x09, 0x03 },
    { 0x0F, 0x01, 0x0D, 0x03 },
    { 0x01, 0x15, 0x1E, 0x02 },
    { 0x06, 0x00, 0x00, 0x00 },
    { 0x04, 0x00, 0x00, 0x00 },
    { 0x00, 0x00, 0x00, 0x00 },
};
