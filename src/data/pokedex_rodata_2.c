// Converted from asm/pokedex_rodata.s (part 2 of 5) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

// The C declarations of these do not match the data (see the notes at each
// definition): keep them out of the way of the definitions below.
#define gPokedexAreaMarkerSizes gPokedexAreaMarkerSizes_header_decl
#define gWeightCheckDiffRanges  gWeightCheckDiffRanges_header_decl

#include "global.h"

#include "application/pokedex/pokedex_internal.h"

#pragma force_active on

#undef gPokedexAreaMarkerSizes
#undef gWeightCheckDiffRanges

const ManagedSpriteTemplate gPokedexSizeCheckSpriteTemplates[9] = {
    { 184, 112, 0, 0,      0,  0, NNS_G2D_VRAM_TYPE_2DSUB,  { 50589, 50526, 50523, 50523, -1, -1 }, 1, 0 },
    { 72,  -16, 0, 0,      0,  0, NNS_G2D_VRAM_TYPE_2DMAIN, { 50512, 50512, 50512, 50512, -1, -1 }, 0, 0 },
    { 72,  80,  0, 0,      0,  0, NNS_G2D_VRAM_TYPE_2DSUB,  { 50513, 50513, 50512, 50512, -1, -1 }, 0, 0 },
    { 184, -16, 0, 0,      0,  0, NNS_G2D_VRAM_TYPE_2DMAIN, { 50587, 50525, 50522, 50522, -1, -1 }, 0, 0 },
    { 0,   0,   0, 0,      0,  0, NNS_G2D_VRAM_TYPE_2DSUB,  { 50588, 50526, 50522, 50522, -1, -1 }, 0, 0 },
    { 128, 104, 0, 0x0021, 10, 1, NNS_G2D_VRAM_TYPE_2DMAIN, { 50576, 50518, 50514, 50514, -1, -1 }, 1, 0 },
    { 128, 104, 0, 0x001F, 15, 1, NNS_G2D_VRAM_TYPE_2DMAIN, { 50576, 50518, 50514, 50514, -1, -1 }, 1, 0 },
    { 72,  104, 0, 0x0020, 12, 1, NNS_G2D_VRAM_TYPE_2DMAIN, { 50576, 50518, 50514, 50514, -1, -1 }, 1, 0 },
    { 184, 104, 0, 0x0020, 12, 1, NNS_G2D_VRAM_TYPE_2DMAIN, { 50576, 50518, 50514, 50514, -1, -1 }, 1, 0 },
};

const ManagedSpriteTemplate gPokedexAreaSpriteTemplates[8] = {
    { 36,  112, 0, 0,      0,  0, NNS_G2D_VRAM_TYPE_2DSUB,  { 50512, 50513, 50512, 50512, -1, -1 }, 0, 0 },
    { 128, 128, 0, 0,      0,  0, NNS_G2D_VRAM_TYPE_2DSUB,  { 50588, 50526, 50522, 50522, -1, -1 }, 3, 0 },
    { 32,  108, 0, 0x001A, 10, 3, NNS_G2D_VRAM_TYPE_2DMAIN, { 50576, 50518, 50514, 50514, -1, -1 }, 0, 0 },
    { 32,  76,  0, 0x001B, 9,  0, NNS_G2D_VRAM_TYPE_2DMAIN, { 50576, 50518, 50514, 50514, -1, -1 }, 0, 0 },
    { 242, 96,  0, 0x000E, 10, 1, NNS_G2D_VRAM_TYPE_2DMAIN, { 50576, 50518, 50514, 50514, -1, -1 }, 0, 0 },
    { 242, 44,  0, 5,      20, 1, NNS_G2D_VRAM_TYPE_2DMAIN, { 50576, 50518, 50514, 50514, -1, -1 }, 0, 0 },
    { 242, 148, 0, 8,      20, 1, NNS_G2D_VRAM_TYPE_2DMAIN, { 50576, 50518, 50514, 50514, -1, -1 }, 0, 0 },
    { 242, 96,  0, 0x003F, 20, 1, NNS_G2D_VRAM_TYPE_2DMAIN, { 50576, 50518, 50514, 50514, -1, -1 }, 0, 0 },
};

// clang-format off
BOOL (*const gWeightCheckAnimFuncs[17])(PokedexWeightCheckAnim *anim) = {
    PokedexApp_WeightAnim_Even, PokedexApp_WeightAnim_Tip1, PokedexApp_WeightAnim_Tip2,
    PokedexApp_WeightAnim_Tip3, PokedexApp_WeightAnim_Tip4, PokedexApp_WeightAnim_Tip5,
    PokedexApp_WeightAnim_Tip6, PokedexApp_WeightAnim_Tip7, PokedexApp_WeightAnim_TipToStop,
    PokedexApp_WeightAnim_Throw1, PokedexApp_WeightAnim_Throw2, PokedexApp_WeightAnim_Throw3,
    PokedexApp_WeightAnim_Throw4, PokedexApp_WeightAnim_Throw5, PokedexApp_WeightAnim_Throw6,
    PokedexApp_WeightAnim_Throw7, PokedexApp_WeightAnim_Throw8,
};
// clang-format on

// C declares this non-const, but it lives in .rodata
const PokedexWeightRange gWeightCheckDiffRanges[17] = {
    { 0,      0      },
    { 1,      1      },
    { 2,      2      },
    { 3,      3      },
    { 4,      4      },
    { 5,      5      },
    { 6,      6      },
    { 7,      7      },
    { 8,      0x000F },
    { 0x0010, 0x001E },
    { 0x001F, 0x0032 },
    { 0x0033, 0x004B },
    { 0x004C, 0x0069 },
    { 0x006A, 0x009B },
    { 0x009C, 0x00EB },
    { 0x00EC, 0x015E },
    { 0x015F, 0xFFFF },
};

const ManagedSpriteTemplate gPokedexSearchSprite43Template = {
    224,
    264,
    0,
    0,
    20,
    0,
    NNS_G2D_VRAM_TYPE_2DSUB,
    { 50591, 50528, 50525, 50525, -1, -1 },
    1,
    0,
};

const ManagedSpriteTemplate gPokedexEntryTabCursorSpriteTemplate = {
    32,
    176,
    0,
    3,
    10,
    0,
    NNS_G2D_VRAM_TYPE_2DMAIN,
    { 50576, 50518, 50514, 50514, -1, -1 },
    0,
    0,
};

const ManagedSpriteTemplate gAreaMarkerSpriteTemplate = {
    192,
    128,
    0,
    0,
    20,
    0,
    NNS_G2D_VRAM_TYPE_2DSUB,
    { 50586, 50524, 50521, 50521, -1, -1 },
    3,
    0,
};

const ManagedSpriteTemplate gMonIconSpriteTemplate = {
    48,
    24,
    0,
    0,
    10,
    0,
    NNS_G2D_VRAM_TYPE_2DMAIN,
    { 50512, 50512, 50512, 50512, -1, -1 },
    3,
    0,
};

const ManagedSpriteTemplate gTypeIconSpriteTemplate = {
    168,
    72,
    0,
    0,
    10,
    0,
    NNS_G2D_VRAM_TYPE_2DSUB,
    { 50579, 50520, 50517, 50517, -1, -1 },
    3,
    0,
};

const ManagedSpriteTemplate gFootprintSpriteTemplate = {
    120,
    80,
    0,
    0,
    10,
    0,
    NNS_G2D_VRAM_TYPE_2DSUB,
    { 50585, 50523, 50520, 50520, -1, -1 },
    3,
    0,
};

const ManagedSpriteTemplate gLanguageIconSpriteTemplate = {
    0,
    8,
    0,
    0,
    10,
    0,
    NNS_G2D_VRAM_TYPE_2DSUB,
    { 50584, 50522, 50519, 50519, -1, -1 },
    3,
    0,
};

const ManagedSpriteTemplate gPokedexBodyTypeIconSpriteTemplate = {
    0,
    0,
    0,
    0,
    20,
    0,
    NNS_G2D_VRAM_TYPE_2DMAIN,
    { 50592, 50529, 50526, 50526, -1, -1 },
    0,
    0,
};

const OamManagerParam gPokedexOamManagerParam = { 0, 128, 0, 32, 0, 128, 0, 32 };

// clang-format off
const u16 gListScrollbarSizeThresholds[12] = {
    0x000F, 0x002D, 0x005A, 0x0087, 0x00B4, 0x00E1, 0x010E, 0x013B, 0x0168, 0x0195, 0x01C2, 0x01EF,
};
// clang-format on

// C declares this non-const, but it lives in .rodata
const u8 gPokedexAreaMarkerSizes[12][2] = {
    { 0x08, 0x08 },
    { 0x10, 0x08 },
    { 0x18, 0x08 },
    { 0x20, 0x08 },
    { 0x28, 0x08 },
    { 0x30, 0x08 },
    { 0x08, 0x10 },
    { 0x08, 0x18 },
    { 0x08, 0x20 },
    { 0x08, 0x28 },
    { 0x10, 0x10 },
    { 0x18, 0x10 },
};

const SpriteResourceCountsListUnion gSpriteResourceCapacities = { 81, 18, 15, 15, 0, 0 };

// clang-format off
const OamCharTransferParam gPokedexOamCharTransferParam = {
    1024, 65536, 16384, GX_OBJVRAMMODE_CHAR_1D_64K, GX_OBJVRAMMODE_CHAR_1D_64K,
};
// clang-format on

const u16 gPokedexAreaScrollbarSizeSteps[9] = { 1, 4, 7, 0x000A, 0x000D, 0x0010, 0x0014, 0x0018, 0x00FF };

const u16 gPokedexFormScrollbarSizeSteps[9] = { 1, 4, 7, 0x000A, 0x000D, 0x0010, 0x0014, 0x0018, 0x001C };

const TileRect gPokedexMonPicSpriteRect = { 0, 0, 10, 10 };

const TileRect gPokedexMonPicBgRect = { 0, 0, 10, 10 };
