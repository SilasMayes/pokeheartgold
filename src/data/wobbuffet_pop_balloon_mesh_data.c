// Converted from asm/wobbuffet_pop_balloon_mesh_data.s by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout. Keep that when editing, or rerun tools/s2c.py.

#include "global.h"

#include "wobbuffet_pop_internal.h"

#pragma force_active on

// 0x02262C38
const ManagedSpriteTemplate gWobbuffetPopHandleSpriteTemplate = {
    0,
    0,
    0,
    0,
    14,
    0,
    NNS_G2D_VRAM_TYPE_2DMAIN,
    { 10003, 10005, 10003, 10003, -1, -1 },
    1,
    0,
};

const WobbuffetPopTouchArea gWobbuffetPopBalloonTouchAreas[12] = {
    { 0x40, 0xC0, 0x10, 0xA8 },
    { 0x28, 0xD8, 0x00, 0xA8 },
    { 0x54, 0xAC, 0x08, 0xA8 },
    { 0x00, 0x00, 0x00, 0x00 },
    { 0x00, 0xFF, 0x0F, 0x00 },
    { 0x00, 0xFF, 0x0F, 0x00 },
    { 0x00, 0xFF, 0x0F, 0x00 },
    { 0x00, 0x00, 0x00, 0x00 },
    { 0x00, 0x00, 0x00, 0x01 },
    { 0xF0, 0x00, 0x00, 0x01 },
    { 0xF0, 0x00, 0x00, 0x01 },
    { 0xF0, 0x00, 0x00, 0x00 },
};

// MWCC gives a char array a section of its own, which the linker starts 4-aligned; to stay at
// offset 0x0 next to its neighbours it is written as the only row of a 2-D array, which shares
// their section.
const u8 _02262C04[1][1] __attribute__((aligned(4))) = { { 0x80 } };
