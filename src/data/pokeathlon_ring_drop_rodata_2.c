// Converted from asm/pokeathlon_ring_drop_rodata.s (part 2 of 2) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

#include "global.h"

#include "pokeathlon/pokeathlon_ring_drop.h"

#pragma force_active on

const PokeathlonRingDropBgTemplates gPokeathlonRingDropBgTemplates = {
    {
     { 0, 0, 0x00000800, 0, 0x01, 0x00, 0x1F, 0x00, 0x00, 0x01, 0x00, 0x00, 0 },
     { 0, 0, 0x00000800, 0, 0x01, 0x00, 0x1E, 0x01, 0x00, 0x02, 0x00, 0x00, 0 },
     { 0, 0, 0x00000800, 0, 0x01, 0x00, 0x1D, 0x02, 0x00, 0x03, 0x00, 0x00, 0 },
     { 0, 0, 0x00000800, 0, 0x01, 0x00, 0x1C, 0x03, 0x00, 0x00, 0x00, 0x00, 0 },
     { 0, 0, 0x00000800, 0, 0x01, 0x00, 0x00, 0x01, 0x00, 0x03, 0x00, 0x00, 0 },
     { 0, 0, 0x00000800, 0, 0x01, 0x00, 0x01, 0x02, 0x00, 0x00, 0x00, 0x00, 0 },
     { 0, 0, 0x00000800, 0, 0x01, 0x00, 0x02, 0x03, 0x00, 0x01, 0x00, 0x00, 0 },
     },
};

const s16 gPokeathlonRingDropJumpHeights[5][10] = {
    { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0  },
    { 8,  14, 18, 20, 21, 22, 22, 23, 23, 24 },
    { 10, 18, 24, 28, 29, 30, 30, 31, 31, 32 },
    { 10, 19, 27, 33, 37, 38, 38, 39, 39, 40 },
    { 10, 19, 27, 34, 40, 44, 45, 46, 47, 48 },
};

const ManagedSpriteTemplate gPokeathlonRingDropSpriteTemplate = {
    0,
    0,
    0,
    0,
    0,
    65535,
    NNS_G2D_VRAM_TYPE_2DMAIN,
    { 10000, 10000, 10000, 10000, 0, 0 },
    2,
    0,
};

// clang-format off
const GraphicsBanks gPokeathlonRingDropGraphicsBanks = {
    GX_VRAM_BG_64_E, GX_VRAM_BGEXTPLTT_NONE, GX_VRAM_SUB_BG_128_C, GX_VRAM_SUB_BGEXTPLTT_NONE,
    GX_VRAM_OBJ_256_AB, GX_VRAM_OBJEXTPLTT_NONE, GX_VRAM_SUB_OBJ_16_I, GX_VRAM_SUB_OBJEXTPLTT_NONE,
    GX_VRAM_TEX_NONE, GX_VRAM_TEXPLTT_NONE,
};
// clang-format on

const OamManagerParam gPokeathlonRingDropOamManagerParam = { 0, 126, 0, 32, 1, 126, 0, 32 };

const u32 gPokeathlonRingDropBgLayers[7] = { 0, 1, 2, 3, 4, 5, 6 };

const PokeathlonRingDropSwitchSpot gPokeathlonRingDropSwitchSpots[POKEATHLON_PARTICIPANTS] = {
    { 48,  48,  64 },
    { 208, 48,  64 },
    { 32,  144, 64 },
    { 224, 144, 64 },
};

const SpriteResourceCountsListUnion gPokeathlonRingDropSpriteResourceCounts = { 6, 7, 5, 5, 0, 0 };

// clang-format off
const OamCharTransferParam gPokeathlonRingDropOamCharTransferParam = {
    0, 262144, 16384, GX_OBJVRAMMODE_CHAR_1D_256K, GX_OBJVRAMMODE_CHAR_1D_256K,
};
// clang-format on

const s16 gPokeathlonRingDropMonStartPositions[POKEATHLON_PARTICIPANTS][2] = {
    { 72,  96  },
    { 184, 96  },
    { 64,  136 },
    { 192, 136 },
};

// clang-format off
const GraphicsModes gPokeathlonRingDropGraphicsModes = {
    GX_DISPMODE_GRAPHICS, GX_BGMODE_0, GX_BGMODE_0, GX_BG0_AS_2D,
};
// clang-format on

const s16 gPokeathlonRingDropRingEdge[4][2] = {
    { 32,  160 },
    { 48,  64  },
    { 208, 64  },
    { 224, 160 }
};

const VecFx32 gPokeathlonRingDropDirectionReference = { 0, 0, 4096 };
