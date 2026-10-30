// Converted from asm/safari_decoration_data.s (part 4 of 4) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

#include "global.h"

#pragma force_active on

extern const u8 gSafariDecorationObjectGroup0[8];
extern const u8 gSafariDecorationObjectGroup1[8];
extern const u8 gSafariDecorationObjectGroup2[8];
extern const u8 gSafariDecorationObjectGroup3[8];

const u8 gSafariDecorationTrainerGroups[10][4] = {
    { 0x00, 0x01, 0x02, 0x03 },
    { 0x00, 0x01, 0x02, 0x03 },
    { 0x00, 0x01, 0x02, 0x03 },
    { 0x01, 0x02, 0x03, 0x00 },
    { 0x01, 0x02, 0x03, 0x00 },
    { 0x01, 0x02, 0x03, 0x00 },
    { 0x02, 0x03, 0x00, 0x01 },
    { 0x02, 0x03, 0x00, 0x01 },
    { 0x03, 0x00, 0x01, 0x02 },
    { 0x03, 0x00, 0x01, 0x02 },
};

const struct {
    u32 unk0;
    const void *unk4;
} gSafariDecorationObjectGroups[4] = {
    { 6, gSafariDecorationObjectGroup0 },
    { 6, gSafariDecorationObjectGroup1 },
    { 6, gSafariDecorationObjectGroup2 },
    { 6, gSafariDecorationObjectGroup3 },
};

const u8 gSafariDecorationObjectGroup2[8] = { 0x06, 0x07, 0x08, 0x15, 0x16, 0x17, 0, 0 };

const u8 gSafariDecorationObjectGroup0[8] = { 0x00, 0x01, 0x02, 0x13, 0x14, 0x0C, 0, 0 };

const u8 gSafariDecorationObjectGroup1[8] = { 0x03, 0x04, 0x05, 0x0D, 0x0E, 0x11, 0, 0 };

const u8 gSafariDecorationObjectGroup3[8] = { 0x09, 0x0A, 0x0B, 0x0F, 0x10, 0x12, 0, 0 };
