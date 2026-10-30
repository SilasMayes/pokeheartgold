// Converted from asm/vs_recorder_data.s (part 13 of 14) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

#include "global.h"

#include "application/vs_recorder/vs_recorder_screens.h"

#pragma force_active on

const VsRecorderNumberPadKeys gVsRecorderNumberPadKeys = {
    {
     { 32, 80, 20, 20 },
     { 80, 80, 20, 20 },
     { 128, 80, 20, 20 },
     { 176, 80, 20, 20 },
     { 224, 80, 20, 20 },
     { 32, 128, 20, 20 },
     { 80, 128, 20, 20 },
     { 128, 128, 20, 20 },
     { 176, 128, 20, 20 },
     { 224, 128, 20, 20 },
     { 76, 176, 60, 12 },
     { 192, 176, 60, 12 },
     },
};

const VsRecorderNumberPadStartX gVsRecorderNumberPadStartX = {
    { { 56, 20, 8 }, { 56, 12, 0 } }
};

// clang-format off
const VsRecorderNumberPadFunc gVsRecorderNumberPadStates[4] = {
    VsRecorder_NumberPadInit, VsRecorder_NumberPadInput, VsRecorder_NumberPadSwitchGroup,
    VsRecorder_NumberPadFree,
};
// clang-format on
