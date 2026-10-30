// Converted from asm/vs_recorder_data.s (part 10 of 14) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

#include "global.h"

#include "application/vs_recorder/vs_recorder_screens.h"

#pragma force_active on

extern const u8 sVsRecorderSearchFacilityListEntriesLong[368];
extern const TouchscreenHitbox sVsRecorderSearchFacilityListHitboxes[3];
extern const TouchscreenHitbox sVsRecorderSearchSpeciesListHitboxes[6];
extern const u8 sVsRecorderSearchLocationListEntries[16];
extern const TouchscreenHitbox sVsRecorderSearchLocationListHitboxes;

// clang-format off
const u8 sVsRecorderSearchFacilityListEntries[80] = {
    0xA9, 0x00, 0x00, 0x00, 0xFA, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xAA, 0x00, 0x00, 0x00, 0xFB, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xAB, 0x00, 0x00, 0x00, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xAC, 0x00, 0x00, 0x00, 0xFD, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xAD, 0x00, 0x00, 0x00, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
// clang-format on

const VsRecorderPartyIconOrder gVsRecorderSearchListIconOrder = {
    { { 0, 1, 2, 3, 4, 5 }, { 0, 1, 2, 3, 4, 5 } },
};

const VsRecorderPartyIconOrder gVsRecorderSearchScrollIconOrder = {
    { { 0, 1, 2, 3, 4, 5 }, { 0, 1, 2, 3, 4, 5 } },
};

const VsRecorderSearchButtonWindows gVsRecorderSearchButtonWindows = {
    { { 7, 3, 20, 2 }, { 7, 8, 20, 2 }, { 7, 13, 20, 2 } },
};

// clang-format off
const VsRecorderListConfig gVsRecorderSearchFacilityListConfigLong = {
    (VsRecorderListEntry *)sVsRecorderSearchFacilityListEntriesLong, 23, 2, 7, 3, 18, 12, 32, 6, 3,
    sVsRecorderSearchFacilityListHitboxes,
};
// clang-format on

// clang-format off
const VsRecorderListConfig gVsRecorderSearchResultListConfig = {
    (VsRecorderListEntry *)sVsRecorderSearchFacilityListEntriesLong, 6, 3, 2, 8, 10, 15, 128, 2, 5, NULL,
};
// clang-format on

// clang-format off
const VsRecorderListConfig gVsRecorderSearchSpeciesListConfig = {
    NULL, 0, 1, 9, 3, 14, 12, 32, 6, 6, sVsRecorderSearchSpeciesListHitboxes,
};
// clang-format on

// clang-format off
const VsRecorderListConfig gVsRecorderSearchLocationListConfig = {
    (VsRecorderListEntry *)sVsRecorderSearchLocationListEntries, 1, 2, 8, 2, 16, 12, 32, 6, 1,
    &sVsRecorderSearchLocationListHitboxes,
};
// clang-format on

// clang-format off
const VsRecorderListConfig gVsRecorderSearchFacilityListConfig = {
    (VsRecorderListEntry *)sVsRecorderSearchFacilityListEntries, 5, 2, 7, 3, 18, 12, 32, 6, 3,
    sVsRecorderSearchFacilityListHitboxes,
};
// clang-format on

const TouchscreenHitbox gVsRecorderSpeciesGroupHitboxes[9] = {
    { 0x18, 0x30, 0x28, 0x48 },
    { 0x18, 0x30, 0x70, 0x90 },
    { 0x18, 0x30, 0xB8, 0xD8 },
    { 0x38, 0x50, 0x28, 0x48 },
    { 0x38, 0x50, 0x70, 0x90 },
    { 0x38, 0x50, 0xB8, 0xD8 },
    { 0x58, 0x70, 0x28, 0x48 },
    { 0x58, 0x70, 0x70, 0x90 },
    { 0x58, 0x70, 0xB8, 0xD8 },
};

const TouchscreenHitbox sVsRecorderSearchSpeciesListHitboxes[6] = {
    { 0x18, 0x28, 0x38, 0xC0 },
    { 0x28, 0x38, 0x38, 0xC0 },
    { 0x38, 0x48, 0x38, 0xC0 },
    { 0x48, 0x58, 0x38, 0xC0 },
    { 0x58, 0x68, 0x38, 0xC0 },
    { 0x68, 0x78, 0x38, 0xC0 },
};

const VsRecorderConditionMsgIds gVsRecorderSearchConditionMsgIds = {
    { 0x00000030, 0x00000031, 0x00000032, 0x0000007D, 0x0000007D, 0x0000007D },
};

const TouchscreenHitbox gVsRecorderSearchConditionHitboxes[5] = {
    { 0x10, 0x30, 0x28, 0xD8 },
    { 0x38, 0x58, 0x28, 0xD8 },
    { 0x60, 0x80, 0x28, 0xD8 },
    { 0x98, 0xB8, 0x20, 0x80 },
    { 0x98, 0xB8, 0x80, 0xE0 },
};

const TouchscreenHitbox gVsRecorderSearchDetailHitboxes[4] = {
    { 0x10, 0x30, 0x40, 0xC8 },
    { 0x40, 0x70, 0x58, 0xA8 },
    { 0x98, 0xB8, 0x80, 0xE0 },
    { 0x98, 0xB8, 0x20, 0x80 },
};
