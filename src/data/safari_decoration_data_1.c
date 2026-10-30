// Converted from asm/safari_decoration_data.s (part 1 of 4) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

#include "global.h"

#pragma force_active on

// clang-format off
const u8 gSafariDecorationCameraAngle[20] __attribute__((aligned(4))) = {
    0x62, 0xDD, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC1, 0x05, 0x00, 0x40, 0x06, 0x00,
    0x00, 0x00, 0x4B, 0x00,
};
// clang-format on
