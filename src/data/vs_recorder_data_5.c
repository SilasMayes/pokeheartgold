// Converted from asm/vs_recorder_data.s (part 5 of 14) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

#include "global.h"

#include "application/vs_recorder/vs_recorder_screens.h"

#pragma force_active on

// clang-format off
const VsRecorderListConfig gVsRecorderRankingsThisWeekListConfig = {
    NULL, 12, 1, 4, 15, 24, 8, 256, 2, 4, NULL,
};
// clang-format on

// clang-format off
const VsRecorderListConfig gVsRecorderRankingsLastWeekListConfig = {
    NULL, 12, 2, 4, 15, 24, 8, 256, 2, 2, NULL,
};
// clang-format on

const VsRecorderRankingsWindowRect gVsRecorderRankingsThisWeekWindows[2] = {
    { 4, 3, 0x00000018, 4 },
    { 4, 9, 0x00000018, 4 },
};

const VsRecorderRankingsWindowRect gVsRecorderRankingsLastWeekWindows[2] = {
    { 4, 3, 0x00000018, 4 },
    { 4, 9, 0x00000018, 4 },
};

const VsRecorderRankingsWindowRect gVsRecorderRankingsButtonLabelWindows[2] = {
    { 7, 4,          0x00000012, 2 },
    { 7, 0x0000000B, 0x00000012, 2 },
};

const TouchscreenHitbox gVsRecorderRankingsHitboxes[3] = {
    { 0x18, 0x38, 0x30, 0xD0 },
    { 0x50, 0x70, 0x30, 0xD0 },
    { 0x98, 0xB8, 0x50, 0xB0 },
};

const VsRecorderRankingTeamCounts gVsRecorderRankingTeamCounts = {
    { 16, 12, 20 }
};
