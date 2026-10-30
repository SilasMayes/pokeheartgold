// Converted from asm/pokeathlon_disc_catch_rodata.s by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout. Keep that when editing, or rerun tools/s2c.py.

#include "global.h"

#include "pokeathlon/pokeathlon_disc_catch.h"

#pragma force_active on

const PokeathlonDiscCatchBgTemplates gPokeathlonDiscCatchBgTemplates = {
    {
     { 0, 0, 0x00000800, 0, 0x01, 0x00, 0x00, 0x01, 0x00, 0x03, 0x00, 0x00, 0 },
     { 0, 0, 0x00000800, 0, 0x01, 0x00, 0x01, 0x02, 0x00, 0x01, 0x00, 0x00, 0 },
     { 0, 0, 0x00000800, 0, 0x01, 0x00, 0x02, 0x03, 0x00, 0x00, 0x00, 0x00, 0 },
     { 0, 0, 0x00000800, 0, 0x01, 0x00, 0x00, 0x01, 0x00, 0x03, 0x00, 0x00, 0 },
     { 0, 0, 0x00000800, 0, 0x01, 0x00, 0x01, 0x02, 0x00, 0x02, 0x00, 0x00, 0 },
     { 0, 0, 0x00000800, 0, 0x01, 0x00, 0x02, 0x04, 0x00, 0x01, 0x00, 0x00, 0 },
     { 0, 0, 0x00000800, 0, 0x01, 0x00, 0x03, 0x06, 0x00, 0x00, 0x00, 0x00, 0 },
     },
};

const ManagedSpriteTemplate gPokeathlonDiscCatchDiscTopSpriteTemplate = {
    0,
    0,
    0,
    0,
    0,
    65535,
    NNS_G2D_VRAM_TYPE_2DSUB,
    { 10003, 10003, 10002, 10002, 0, 0 },
    1,
    0,
};

const ManagedSpriteTemplate gPokeathlonDiscCatchDiscTouchSpriteTemplate = {
    0,
    0,
    0,
    0,
    0,
    65535,
    NNS_G2D_VRAM_TYPE_2DMAIN,
    { 10002, 10002, 10002, 10002, 0, 0 },
    1,
    0,
};

const ManagedSpriteTemplate gPokeathlonDiscCatchEffectSpriteTemplate = {
    0,
    0,
    0,
    0,
    0,
    65535,
    NNS_G2D_VRAM_TYPE_2DMAIN,
    { 10000, 10000, 10000, 10000, 0, 0 },
    1,
    0,
};

const s16 gPokeathlonDiscCatchMonStartPositions[POKEATHLON_PARTICIPANTS][POKEATHLON_TEAM_SIZE][2] = {
    { { 40, 40 },  { 40, 88 },  { 40, 152 }  },
    { { 96, 40 },  { 96, 88 },  { 96, 152 }  },
    { { 160, 40 }, { 160, 88 }, { 160, 152 } },
    { { 216, 40 }, { 216, 88 }, { 216, 152 } },
};

// clang-format off
const GraphicsBanks gPokeathlonDiscCatchGraphicsBanks = {
    GX_VRAM_BG_64_E, GX_VRAM_BGEXTPLTT_NONE, GX_VRAM_SUB_BG_128_C, GX_VRAM_SUB_BGEXTPLTT_NONE,
    GX_VRAM_OBJ_256_AB, GX_VRAM_OBJEXTPLTT_NONE, GX_VRAM_SUB_OBJ_16_I, GX_VRAM_SUB_OBJEXTPLTT_NONE,
    GX_VRAM_TEX_NONE, GX_VRAM_TEXPLTT_NONE,
};
// clang-format on

const OamManagerParam gPokeathlonDiscCatchOamManagerParam = { 0, 126, 0, 32, 1, 126, 0, 32 };

const u32 gPokeathlonDiscCatchBgLayers[7] = { 0, 1, 2, 4, 5, 6, 7 };

const SpriteResourceCountsListUnion gPokeathlonDiscCatchSpriteResourceCounts = { 6, 6, 5, 5, 0, 0 };

// clang-format off
const OamCharTransferParam gPokeathlonDiscCatchOamCharTransferParam = {
    0, 262144, 16384, GX_OBJVRAMMODE_CHAR_1D_256K, GX_OBJVRAMMODE_CHAR_1D_256K,
};
// clang-format on

// clang-format off
const GraphicsModes gPokeathlonDiscCatchGraphicsModes = {
    GX_DISPMODE_GRAPHICS, GX_BGMODE_0, GX_BGMODE_0, GX_BG0_AS_2D,
};
// clang-format on

const u32 gPokeathlonDiscCatchPhaseSeconds[4] = { 0x00000037, 0x00000028, 0x00000014, 0 };

const VecFx32 gPokeathlonDiscCatchTouchDistances = { 1048576, 1048576, 1048576 };

const VecFx32 gPokeathlonDiscCatchFacingReference = { 0, 0, 4096 };

// clang-format off
const WindowTemplate gPokeathlonDiscCatchScoreWindowTemplate __attribute__((aligned(4))) = {
    0x02, 0x00, 0x14, 0x20, 0x02, 0x0F, 1,
};
// clang-format on
