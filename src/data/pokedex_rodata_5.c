// Converted from asm/pokedex_rodata.s (part 5 of 5) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

#include "global.h"

#include "application/pokedex/pokedex_internal.h"

#pragma force_active on

// clang-format off
const u16 gPokedexMonPicBgTilemap[50] = {
    0x0201, 0x0403, 0x0605, 0x0807, 0x4241, 0x0A09, 0x0C0B, 0x0E0D, 0x100F, 0x4443, 0x1211, 0x1413, 0x1615,
    0x1817, 0x4645, 0x1A19, 0x1C1B, 0x1E1D, 0x201F, 0x4847, 0x2221, 0x2423, 0x2625, 0x2827, 0x4A49, 0x2A29,
    0x2C2B, 0x2E2D, 0x302F, 0x4C4B, 0x3231, 0x3433, 0x3635, 0x3837, 0x4E4D, 0x3A39, 0x3C3B, 0x3E3D, 0x403F,
    0x504F, 0x5251, 0x5453, 0x5A59, 0x5C5B, 0x6261, 0x5655, 0x5857, 0x5E5D, 0x605F, 0x6463,
};
// clang-format on

const ManagedSpriteTemplate gPokedexSearchSprite26Template = {
    128,
    80,
    0,
    0,
    20,
    0,
    NNS_G2D_VRAM_TYPE_2DSUB,
    { 50590, 50527, 50524, 50524, -1, -1 },
    3,
    0,
};

const ManagedSpriteTemplate gPokedexSearchSprite27Template = {
    128,
    80,
    0,
    0,
    10,
    0,
    NNS_G2D_VRAM_TYPE_2DSUB,
    { 50590, 50527, 50524, 50524, -1, -1 },
    3,
    0,
};
