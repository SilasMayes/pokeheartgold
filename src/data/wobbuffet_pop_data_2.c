// Converted from asm/wobbuffet_pop_data.s (part 2 of 4) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

#include "global.h"

#include "wobbuffet_pop_internal.h"

#pragma force_active on

// clang-format off
const u8 gWobbuffetPopNameWindowIndices[20] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x03, 0x02, 0x00, 0x00,
    0x03, 0x01, 0x02,
};
// clang-format on

const u8 gWobbuffetPopSeatOrders[5][4] = {
    { 0x00, 0x00, 0x00, 0x00 },
    { 0x00, 0x00, 0x00, 0x00 },
    { 0x00, 0x01, 0x00, 0x00 },
    { 0x00, 0x02, 0x01, 0x00 },
    { 0x00, 0x03, 0x01, 0x02 },
};

// clang-format off
const GraphicsModes gWobbuffetPopGraphicsModes = {
    GX_DISPMODE_GRAPHICS, GX_BGMODE_0, GX_BGMODE_1, GX_BG0_AS_3D,
};
// clang-format on

const VecFx32 gWobbuffetPopCameraTarget = { 0, 100382, 0 };
