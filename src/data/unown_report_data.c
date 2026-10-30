// Converted from asm/unown_report_data.s by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout. Keep that when editing, or rerun tools/s2c.py.

#include "global.h"

#pragma force_active on

// 0x021E6B82
// MWCC gives a char array a section of its own, which the linker starts 4-aligned; to stay at
// offset 0x16 next to its neighbours it is written as the only row of a 2-D array, which shares
// their section.
// clang-format off
const u8 gUnownReportHitboxes[1][18] = {
{
    0xA0, 0xC0, 0xC0, 0x00, 0x10, 0x25, 0xDC, 0xF4, 0x78, 0x8D, 0xDC, 0xF4, 0xFF, 0x00, 0x00, 0x00,
    0x00, 0x00,
}
};
// clang-format on

// 0x021E6B74
// MWCC gives a char array a section of its own, which the linker starts 4-aligned; to stay at
// offset 0x8 next to its neighbours it is written as the only row of a 2-D array, which shares
// their section.
// clang-format off
const u8 gUnownReportResdatIds[1][14] = {
{
    0x06, 0x00, 0x07, 0x00, 0x05, 0x00, 0x04, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x49, 0x00,
}
};
// clang-format on

// clang-format off
static const u8 sUnownReportUnused[8] __attribute__((aligned(4))) = {
    0x00, 0x0F, 0x07, 0x00, 0x00, 0x0F, 0x01, 0x00,
};
// clang-format on
