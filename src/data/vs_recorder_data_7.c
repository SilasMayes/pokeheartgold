// Converted from asm/vs_recorder_data.s (part 7 of 14) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

#include "global.h"

#include "application/vs_recorder/vs_recorder_screens.h"

#pragma force_active on

const VsRecorderIconPositions gVsRecorderVideoListIconPositions = {
    {
     { 104, 72 },
     { 128, 72 },
     { 152, 72 },
     { 176, 72 },
     { 200, 72 },
     { 224, 72 },
     { 104, 96 },
     { 128, 96 },
     { 152, 96 },
     { 176, 96 },
     { 200, 96 },
     { 224, 96 },
     { 104, 120 },
     { 128, 120 },
     { 152, 120 },
     { 176, 120 },
     { 200, 120 },
     { 224, 120 },
     { 104, 144 },
     { 128, 144 },
     { 152, 144 },
     { 176, 144 },
     { 200, 144 },
     { 224, 144 },
     { 104, 168 },
     { 128, 168 },
     { 152, 168 },
     { 176, 168 },
     { 200, 168 },
     { 224, 168 },
     },
};

const VsRecorderPartyIconOrder gVsRecorderScrollIconOrder = {
    { { 0, 1, 2, 3, 4, 5 }, { 0, 1, 2, 3, 4, 5 } }
};

const VsRecorderPartyIconOrder gVsRecorderListIconOrder = {
    { { 0, 1, 2, 3, 4, 5 }, { 0, 1, 2, 3, 4, 5 } }
};

const VsRecorderListConfig gVsRecorderVideoListConfig = { NULL, 6, 3, 2, 8, 10, 15, 128, 2, 5, NULL };

const TouchscreenHitbox gVsRecorderVideoDetailHitboxes[4] = {
    { 0x10, 0x30, 0x40, 0xC8 },
    { 0x40, 0x70, 0x58, 0xA8 },
    { 0x98, 0xB8, 0x80, 0xE0 },
    { 0x98, 0xB8, 0x20, 0x80 },
};

const VsRecorderSlotButtonTable gVsRecorderSaveSlotMsgIds = {
    { 8, 8, 8, 3 }
};

const TouchscreenHitbox gVsRecorderSaveSlotHitboxes[4] = {
    { 0x19, 0x39, 0x32, 0xD2 },
    { 0x3D, 0x5D, 0x32, 0xD2 },
    { 0x61, 0x81, 0x32, 0xD2 },
    { 0x85, 0xA5, 0x32, 0xD2 },
};

const VsRecorderSlotButtonTable gVsRecorderSaveSlotAnims = {
    { 0, 0, 0, 1 }
};

const VsRecorderTitleMsgIds gVsRecorderVideoListTitleMsgIds = {
    { 0x00000061, 0x00000062, 0x0000007B }
};

const TouchscreenHitbox gVsRecorderOverwriteHitboxes[2] = {
    { 0x28, 0x48, 0x20, 0x78 },
    { 0x28, 0x48, 0x90, 0xE8 },
};

const TouchscreenHitbox gVsRecorderVideoListExitHitbox = { 0x98, 0xB8, 0x50, 0xB0 };

const TouchscreenHitbox gVsRecorderVideoListOpenHitbox = { 0x20, 0x60, 0x50, 0xB0 };
