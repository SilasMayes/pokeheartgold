// Converted from asm/vs_recorder_data.s (part 9 of 14) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

#include "global.h"

#include "application/vs_recorder/vs_recorder_screens.h"

#pragma force_active on

const VsRecorderSlotButtonTable gVsRecorderSearchSlotMsgIds = {
    { 8, 8, 8, 3 }
};

const VsRecorderSlotButtonTable gVsRecorderSearchSlotAnims = {
    { 0, 0, 0, 1 }
};

// clang-format off
const u8 sVsRecorderSearchLocationListEntries[16] = {
    0x10, 0x00, 0x00, 0x00, 0x0D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
// clang-format on

const TouchscreenHitbox gVsRecorderSearchSaveSlotHitboxes[4] = {
    { 0x19, 0x39, 0x32, 0xD2 },
    { 0x3D, 0x5D, 0x32, 0xD2 },
    { 0x61, 0x81, 0x32, 0xD2 },
    { 0x85, 0xA5, 0x32, 0xD2 },
};

const VsRecorderSearchButtonMsgIds gVsRecorderSearchButtonMsgIds = {
    { 0x00000030, 0x00000031, 0x00000032 }
};

const TouchscreenHitbox sVsRecorderSearchFacilityListHitboxes[3] = {
    { 0x18, 0x38, 0x30, 0xD0 },
    { 0x38, 0x58, 0x30, 0xD0 },
    { 0x58, 0x78, 0x30, 0xD0 },
};

const TouchscreenHitbox gVsRecorderSearchOverwriteHitboxes[2] = {
    { 0x28, 0x48, 0x20, 0x78 },
    { 0x28, 0x48, 0x90, 0xE8 },
};

const TouchscreenHitbox gVsRecorderSearchBackHitbox = { 0x98, 0xB8, 0x50, 0xB0 };

const TouchscreenHitbox sVsRecorderSearchLocationListHitboxes = { 0x18, 0x38, 0x38, 0xC8 };

const TouchscreenHitbox gVsRecorderSearchResultOpenHitbox = { 0x20, 0x60, 0x50, 0xB0 };
