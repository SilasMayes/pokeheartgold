// Converted from asm/pokedex_rodata.s (part 4 of 5) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

#include "global.h"

#include "application/pokedex/pokedex_internal.h"

#pragma force_active on

const ManagedSpriteTemplate gPokedexSearchSpriteTemplates[26] = {
    { 172, 16,  0, 0x0027, 10, 0, NNS_G2D_VRAM_TYPE_2DMAIN, { 50576, 50518, 50514, 50514, -1, -1 }, 0, 0 },
    { 18,  60,  0, 0x0038, 35, 1, NNS_G2D_VRAM_TYPE_2DMAIN, { 50576, 50518, 50514, 50514, -1, -1 }, 0, 0 },
    { 238, 60,  0, 0x0035, 35, 1, NNS_G2D_VRAM_TYPE_2DMAIN, { 50576, 50518, 50514, 50514, -1, -1 }, 0, 0 },
    { 18,  132, 0, 0x0038, 35, 1, NNS_G2D_VRAM_TYPE_2DMAIN, { 50576, 50518, 50514, 50514, -1, -1 }, 0, 0 },
    { 238, 132, 0, 0x0035, 35, 1, NNS_G2D_VRAM_TYPE_2DMAIN, { 50576, 50518, 50514, 50514, -1, -1 }, 0, 0 },
    { 52,  68,  0, 0x0029, 30, 1, NNS_G2D_VRAM_TYPE_2DMAIN, { 50576, 50518, 50514, 50514, -1, -1 }, 0, 0 },
    { 52,  64,  0, 0x002B, 20, 0, NNS_G2D_VRAM_TYPE_2DMAIN, { 50576, 50518, 50514, 50514, -1, -1 }, 0, 0 },
    { 52,  64,  0, 0x002B, 20, 0, NNS_G2D_VRAM_TYPE_2DMAIN, { 50576, 50518, 50514, 50514, -1, -1 }, 0, 0 },
    { 52,  64,  0, 0x002B, 20, 0, NNS_G2D_VRAM_TYPE_2DMAIN, { 50576, 50518, 50514, 50514, -1, -1 }, 0, 0 },
    { 52,  64,  0, 0x002B, 20, 0, NNS_G2D_VRAM_TYPE_2DMAIN, { 50576, 50518, 50514, 50514, -1, -1 }, 0, 0 },
    { 52,  64,  0, 0x002B, 20, 0, NNS_G2D_VRAM_TYPE_2DMAIN, { 50576, 50518, 50514, 50514, -1, -1 }, 0, 0 },
    { 204, 132, 0, 0x002A, 30, 1, NNS_G2D_VRAM_TYPE_2DMAIN, { 50576, 50518, 50514, 50514, -1, -1 }, 0, 0 },
    { 204, 136, 0, 0x002B, 20, 0, NNS_G2D_VRAM_TYPE_2DMAIN, { 50576, 50518, 50514, 50514, -1, -1 }, 0, 0 },
    { 204, 136, 0, 0x002B, 20, 0, NNS_G2D_VRAM_TYPE_2DMAIN, { 50576, 50518, 50514, 50514, -1, -1 }, 0, 0 },
    { 204, 136, 0, 0x002B, 20, 0, NNS_G2D_VRAM_TYPE_2DMAIN, { 50576, 50518, 50514, 50514, -1, -1 }, 0, 0 },
    { 204, 136, 0, 0x002B, 20, 0, NNS_G2D_VRAM_TYPE_2DMAIN, { 50576, 50518, 50514, 50514, -1, -1 }, 0, 0 },
    { 204, 136, 0, 0x002B, 20, 0, NNS_G2D_VRAM_TYPE_2DMAIN, { 50576, 50518, 50514, 50514, -1, -1 }, 0, 0 },
    { 128, 128, 0, 0x0017, 10, 1, NNS_G2D_VRAM_TYPE_2DMAIN, { 50576, 50518, 50514, 50514, -1, -1 }, 0, 0 },
    { 242, 64,  0, 0x0010, 10, 1, NNS_G2D_VRAM_TYPE_2DMAIN, { 50576, 50518, 50514, 50514, -1, -1 }, 3, 0 },
    { 242, 12,  0, 5,      20, 1, NNS_G2D_VRAM_TYPE_2DMAIN, { 50576, 50518, 50514, 50514, -1, -1 }, 3, 0 },
    { 242, 140, 0, 8,      20, 1, NNS_G2D_VRAM_TYPE_2DMAIN, { 50576, 50518, 50514, 50514, -1, -1 }, 3, 0 },
    { 242, 76,  0, 4,      20, 1, NNS_G2D_VRAM_TYPE_2DMAIN, { 50576, 50518, 50514, 50514, -1, -1 }, 3, 0 },
    { 64,  136, 0, 0x0018, 10, 1, NNS_G2D_VRAM_TYPE_2DMAIN, { 50576, 50518, 50514, 50514, -1, -1 }, 0, 0 },
    { 184, 136, 0, 0x0019, 10, 1, NNS_G2D_VRAM_TYPE_2DMAIN, { 50576, 50518, 50514, 50514, -1, -1 }, 0, 0 },
    { 92,  136, 0, 0,      10, 0, NNS_G2D_VRAM_TYPE_2DMAIN, { 50583, 50521, 50518, 50518, -1, -1 }, 0, 0 },
    { 48,  24,  0, 0x001C, 20, 1, NNS_G2D_VRAM_TYPE_2DMAIN, { 50576, 50518, 50514, 50514, -1, -1 }, 3, 0 },
};

const ManagedSpriteTemplate gPokedexFormsSpriteTemplates[19] = {
    { 64,  120, 0, 0,      0,  0, NNS_G2D_VRAM_TYPE_2DSUB,  { 50572, 50514, 50513, 50513, -1, -1 }, 0, 0 },
    { 192, 120, 0, 0,      0,  0, NNS_G2D_VRAM_TYPE_2DSUB,  { 50573, 50515, 50513, 50513, -1, -1 }, 0, 0 },
    { 64,  120, 0, 0,      0,  0, NNS_G2D_VRAM_TYPE_2DSUB,  { 50574, 50516, 50513, 50513, -1, -1 }, 0, 0 },
    { 192, 120, 0, 0,      0,  0, NNS_G2D_VRAM_TYPE_2DSUB,  { 50575, 50517, 50513, 50513, -1, -1 }, 0, 0 },
    { 242, 64,  0, 0x000E, 10, 1, NNS_G2D_VRAM_TYPE_2DMAIN, { 50576, 50518, 50514, 50514, -1, -1 }, 0, 0 },
    { 242, 12,  0, 5,      20, 1, NNS_G2D_VRAM_TYPE_2DMAIN, { 50576, 50518, 50514, 50514, -1, -1 }, 0, 0 },
    { 242, 116, 0, 8,      20, 1, NNS_G2D_VRAM_TYPE_2DMAIN, { 50576, 50518, 50514, 50514, -1, -1 }, 0, 0 },
    { 242, 64,  0, 0x003F, 20, 1, NNS_G2D_VRAM_TYPE_2DMAIN, { 50576, 50518, 50514, 50514, -1, -1 }, 0, 0 },
    { 64,  56,  0, 0x0040, 0,  1, NNS_G2D_VRAM_TYPE_2DMAIN, { 50576, 50518, 50514, 50514, -1, -1 }, 0, 0 },
    { 64,  128, 0, 0x0041, 0,  1, NNS_G2D_VRAM_TYPE_2DMAIN, { 50576, 50518, 50514, 50514, -1, -1 }, 0, 0 },
    { 192, 56,  0, 0x0040, 0,  1, NNS_G2D_VRAM_TYPE_2DMAIN, { 50576, 50518, 50514, 50514, -1, -1 }, 0, 0 },
    { 192, 128, 0, 0x0041, 0,  1, NNS_G2D_VRAM_TYPE_2DMAIN, { 50576, 50518, 50514, 50514, -1, -1 }, 0, 0 },
    { 64,  80,  0, 0x0042, 0,  0, NNS_G2D_VRAM_TYPE_2DMAIN, { 50576, 50518, 50514, 50514, -1, -1 }, 0, 0 },
    { 0,   0,   0, 0,      0,  0, NNS_G2D_VRAM_TYPE_2DMAIN, { 50512, 50512, 50512, 50512, -1, -1 }, 3, 0 },
    { 0,   0,   0, 0,      0,  0, NNS_G2D_VRAM_TYPE_2DMAIN, { 50513, 50512, 50512, 50512, -1, -1 }, 3, 0 },
    { 0,   0,   0, 0,      0,  0, NNS_G2D_VRAM_TYPE_2DMAIN, { 50514, 50512, 50512, 50512, -1, -1 }, 3, 0 },
    { 0,   0,   0, 0,      0,  0, NNS_G2D_VRAM_TYPE_2DMAIN, { 50515, 50512, 50512, 50512, -1, -1 }, 3, 0 },
    { 0,   0,   0, 0,      0,  0, NNS_G2D_VRAM_TYPE_2DMAIN, { 50516, 50512, 50512, 50512, -1, -1 }, 3, 0 },
    { 0,   0,   0, 0,      0,  0, NNS_G2D_VRAM_TYPE_2DMAIN, { 50517, 50512, 50512, 50512, -1, -1 }, 3, 0 },
};

const ManagedSpriteTemplate gPokedexMonPicSpriteTemplate0 = {
    48,
    72,
    0,
    0,
    0,
    0,
    NNS_G2D_VRAM_TYPE_2DSUB,
    { 50572, 50514, 50513, 50513, -1, -1 },
    3,
    0,
};

const ManagedSpriteTemplate gPokedexListSprite10Template = {
    48,
    72,
    0,
    0,
    0,
    0,
    NNS_G2D_VRAM_TYPE_2DSUB,
    { 50577, 50519, 50515, 50515, -1, -1 },
    3,
    0,
};

const ManagedSpriteTemplate gPokedexListSprite9Template = {
    112,
    32,
    0,
    0,
    0,
    0,
    NNS_G2D_VRAM_TYPE_2DSUB,
    { 50578, 50519, 50516, 50516, -1, -1 },
    3,
    0,
};

const ManagedSpriteTemplate gPokedexLanguageIconSpriteTemplate = {
    92,
    136,
    0,
    0,
    10,
    0,
    NNS_G2D_VRAM_TYPE_2DMAIN,
    { 50583, 50521, 50518, 50518, -1, -1 },
    0,
    0,
};

const ManagedSpriteTemplate gPokedexMonPicSpriteTemplate1 = {
    48,
    72,
    0,
    0,
    0,
    0,
    NNS_G2D_VRAM_TYPE_2DSUB,
    { 50573, 50515, 50513, 50513, -1, -1 },
    3,
    0,
};
