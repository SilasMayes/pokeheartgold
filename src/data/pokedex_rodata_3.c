// Converted from asm/pokedex_rodata.s (part 3 of 5) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

#include "global.h"

#include "application/pokedex/pokedex_internal.h"

#pragma force_active on

const ManagedSpriteTemplate gPokedexListSpriteTemplates[8] = {
    { 128, 128, 0, 0x0017, 10, 1, NNS_G2D_VRAM_TYPE_2DMAIN, { 50576, 50518, 50514, 50514, -1, -1 }, 0, 0 },
    { 242, 64,  0, 0x0010, 10, 1, NNS_G2D_VRAM_TYPE_2DMAIN, { 50576, 50518, 50514, 50514, -1, -1 }, 3, 0 },
    { 242, 12,  0, 5,      20, 1, NNS_G2D_VRAM_TYPE_2DMAIN, { 50576, 50518, 50514, 50514, -1, -1 }, 3, 0 },
    { 242, 140, 0, 8,      20, 1, NNS_G2D_VRAM_TYPE_2DMAIN, { 50576, 50518, 50514, 50514, -1, -1 }, 3, 0 },
    { 242, 76,  0, 4,      20, 1, NNS_G2D_VRAM_TYPE_2DMAIN, { 50576, 50518, 50514, 50514, -1, -1 }, 3, 0 },
    { 48,  24,  0, 1,      0,  0, NNS_G2D_VRAM_TYPE_2DMAIN, { 50576, 50518, 50514, 50514, -1, -1 }, 3, 0 },
    { 64,  136, 0, 0x0018, 10, 1, NNS_G2D_VRAM_TYPE_2DMAIN, { 50576, 50518, 50514, 50514, -1, -1 }, 0, 0 },
    { 184, 136, 0, 0x0019, 10, 1, NNS_G2D_VRAM_TYPE_2DMAIN, { 50576, 50518, 50514, 50514, -1, -1 }, 0, 0 },
};
