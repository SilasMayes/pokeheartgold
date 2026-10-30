// Converted from asm/hall_of_fame_showcase_data.s (part 3 of 3) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

#include "global.h"

#include "hall_of_fame_showcase_internal.h"

#pragma force_active on

// 0x021E7408
const ManagedSpriteTemplate gHallOfFameShowcaseNextPageSpriteTemplate = {
    244,
    104,
    0,
    1,
    0,
    0,
    NNS_G2D_VRAM_TYPE_2DMAIN,
    { 56526, 56526, 56515, 56515, -1, -1 },
    1,
    0,
};

// 0x021E73D4
const ManagedSpriteTemplate gHallOfFameShowcasePrevPageSpriteTemplate = {
    12,
    104,
    0,
    0,
    0,
    0,
    NNS_G2D_VRAM_TYPE_2DMAIN,
    { 56526, 56526, 56515, 56515, -1, -1 },
    1,
    0,
};

// 0x021E73A0
const ManagedSpriteTemplate gHallOfFameShowcaseCursorSpriteTemplate = {
    56,
    72,
    0,
    3,
    0,
    1,
    NNS_G2D_VRAM_TYPE_2DMAIN,
    { 56526, 56526, 56515, 56515, -1, -1 },
    0,
    0,
};

// 0x021E743C
const ManagedSpriteTemplate gHallOfFameShowcaseExitSpriteTemplate = {
    224,
    176,
    0,
    2,
    0,
    0,
    NNS_G2D_VRAM_TYPE_2DMAIN,
    { 56526, 56526, 56515, 56515, -1, -1 },
    1,
    0,
};
