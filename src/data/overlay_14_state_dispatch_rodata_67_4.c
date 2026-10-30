// Converted from asm/overlay_14_state_dispatch_rodata_67.s (part 4 of 6) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

#include "global.h"

#include "constants/pokemon.h"

#include "application/pc_box/pc_box_internal.h"

#pragma force_active on

const WindowTemplate gPCBoxWindowTemplates[44] = {
    { 0x04, 0x08, 0x05, 0x08, 0x02, 0x0F, 0x0069 },
    { 0x04, 0x01, 0x07, 0x08, 0x02, 0x0F, 0x0079 },
    { 0x04, 0x04, 0x09, 0x06, 0x02, 0x0F, 0x0089 },
    { 0x04, 0x01, 0x00, 0x1E, 0x03, 0x0F, 0x000F },
    { 0x04, 0x10, 0x05, 0x02, 0x02, 0x0F, 0x0095 },
    { 0x04, 0x01, 0x05, 0x06, 0x02, 0x0F, 0x0099 },
    { 0x04, 0x01, 0x0D, 0x08, 0x02, 0x0F, 0x00A5 },
    { 0x04, 0x01, 0x11, 0x0B, 0x02, 0x0F, 0x00B5 },
    { 0x04, 0x01, 0x15, 0x0C, 0x02, 0x0F, 0x00CB },
    { 0x06, 0x01, 0x01, 0x0B, 0x02, 0x01, 0x03EA },
    { 0x06, 0x01, 0x03, 0x0B, 0x02, 0x01, 0x03D4 },
    { 0x06, 0x01, 0x05, 0x0B, 0x02, 0x01, 0x03BE },
    { 0x06, 0x01, 0x07, 0x0B, 0x02, 0x01, 0x03A8 },
    { 0x06, 0x01, 0x01, 0x0B, 0x02, 0x01, 0x0392 },
    { 0x06, 0x01, 0x03, 0x0B, 0x02, 0x01, 0x037C },
    { 0x06, 0x01, 0x05, 0x0B, 0x02, 0x01, 0x0366 },
    { 0x06, 0x01, 0x07, 0x0B, 0x02, 0x01, 0x0350 },
    { 0x04, 0x01, 0x0B, 0x08, 0x02, 0x0F, 0x00E3 },
    { 0x04, 0x01, 0x0F, 0x0B, 0x02, 0x0F, 0x00F3 },
    { 0x04, 0x01, 0x13, 0x0C, 0x02, 0x0F, 0x0109 },
    { 0x06, 0x01, 0x01, 0x0C, 0x02, 0x01, 0x03E8 },
    { 0x06, 0x04, 0x03, 0x1B, 0x06, 0x01, 0x032E },
    { 0x06, 0x01, 0x01, 0x0C, 0x02, 0x01, 0x03D0 },
    { 0x06, 0x04, 0x03, 0x1B, 0x06, 0x01, 0x028C },
    { 0x01, 0x00, 0x00, 0x0B, 0x03, 0x0C, 0x03C7 },
    { 0x01, 0x00, 0x00, 0x0B, 0x03, 0x02, 0x03A6 },
    { 0x01, 0x00, 0x00, 0x08, 0x03, 0x0C, 0x038E },
    { 0x01, 0x00, 0x00, 0x08, 0x03, 0x0C, 0x038E },
    { 0x01, 0x00, 0x00, 0x08, 0x03, 0x0C, 0x0376 },
    { 0x00, 0x00, 0x00, 0x0B, 0x03, 0x0C, 0x036D },
    { 0x00, 0x00, 0x00, 0x0B, 0x03, 0x0C, 0x034C },
    { 0x00, 0x00, 0x00, 0x0B, 0x03, 0x0C, 0x032B },
    { 0x00, 0x00, 0x00, 0x0B, 0x03, 0x0C, 0x030A },
    { 0x00, 0x00, 0x00, 0x0B, 0x03, 0x0C, 0x02E9 },
    { 0x00, 0x02, 0x0B, 0x07, 0x02, 0x01, 0x0380 },
    { 0x00, 0x02, 0x0F, 0x07, 0x02, 0x01, 0x0372 },
    { 0x01, 0x02, 0x0F, 0x07, 0x02, 0x01, 0x0368 },
    { 0x00, 0x02, 0x15, 0x1B, 0x02, 0x0B, 0x02B3 },
    { 0x00, 0x02, 0x01, 0x1B, 0x02, 0x0B, 0x02B3 },
    { 0x00, 0x02, 0x15, 0x13, 0x02, 0x0B, 0x02B3 },
    { 0x00, 0x02, 0x15, 0x1B, 0x02, 0x0B, 0x027D },
    { 0x00, 0x16, 0x10, 0x09, 0x04, 0x0C, 0x0259 },
    { 0x01, 0x00, 0x00, 0x11, 0x03, 0x0C, 0x0335 },
    { 0x01, 0x00, 0x00, 0x11, 0x03, 0x02, 0x0302 },
};

const ManagedSpriteTemplate gPCBoxMonIconSpriteTemplate = {
    24,
    48,
    0,
    0,
    10,
    0,
    NNS_G2D_VRAM_TYPE_2DMAIN,
    { 49401, 49401, 49401, 49401, -1, -1 },
    3,
    0,
};

const ManagedSpriteTemplate gPCBoxItemIconSprite12Template = {
    0,
    0,
    0,
    0,
    0,
    0,
    NNS_G2D_VRAM_TYPE_2DSUB,
    { 49440, 49405, 49403, 49403, -1, -1 },
    0,
    0,
};

const ManagedSpriteTemplate gPCBoxItemIconSpriteTemplate = {
    0,
    0,
    0,
    0,
    0,
    0,
    NNS_G2D_VRAM_TYPE_2DMAIN,
    { 49439, 49404, 49403, 49403, -1, -1 },
    0,
    0,
};

const ManagedSpriteTemplate gPCBoxUiSprite1Template = {
    156,
    28,
    0,
    3,
    0,
    0,
    NNS_G2D_VRAM_TYPE_2DMAIN,
    { 49453, 49409, 49407, 49407, -1, -1 },
    3,
    0,
};

const ManagedSpriteTemplate gPCBoxMonPicSprite2Template = {
    140,
    100,
    0,
    0,
    10,
    0,
    NNS_G2D_VRAM_TYPE_2DSUB,
    { 49437, 49402, 49402, 49402, -1, -1 },
    1,
    0,
};

const ManagedSpriteTemplate gPCBoxUiSprite8Template = {
    128,
    -28,
    0,
    6,
    5,
    0,
    NNS_G2D_VRAM_TYPE_2DMAIN,
    { 49453, 49409, 49407, 49407, -1, -1 },
    1,
    0,
};

const ManagedSpriteTemplate gPCBoxUiSprite7Template = {
    128,
    -40,
    0,
    5,
    5,
    0,
    NNS_G2D_VRAM_TYPE_2DMAIN,
    { 49453, 49409, 49407, 49407, -1, -1 },
    1,
    0,
};

const ManagedSpriteTemplate gPCBoxUiSprite5Template = {
    244,
    -21,
    0,
    3,
    5,
    0,
    NNS_G2D_VRAM_TYPE_2DMAIN,
    { 49453, 49409, 49407, 49407, -1, -1 },
    1,
    0,
};

const ManagedSpriteTemplate gPCBoxUiSprite6Template = {
    43,
    -21,
    0,
    0,
    5,
    0,
    NNS_G2D_VRAM_TYPE_2DMAIN,
    { 49453, 49409, 49407, 49407, -1, -1 },
    1,
    0,
};

const ManagedSpriteTemplate gPCBoxUiSprite9Template = {
    128,
    128,
    0,
    8,
    0,
    0,
    NNS_G2D_VRAM_TYPE_2DMAIN,
    { 49453, 49409, 49407, 49407, -1, -1 },
    0,
    0,
};

const ManagedSpriteTemplate gPCBoxUiSprite10Template = {
    128,
    160,
    0,
    0x000D,
    0,
    0,
    NNS_G2D_VRAM_TYPE_2DMAIN,
    { 49453, 49409, 49407, 49407, -1, -1 },
    0,
    0,
};

const ManagedSpriteTemplate gPCBoxTypeIconSprite13Template = {
    160,
    48,
    0,
    0,
    0,
    0,
    NNS_G2D_VRAM_TYPE_2DSUB,
    { 49441, 49406, 49404, 49404, -1, -1 },
    1,
    0,
};

const ManagedSpriteTemplate gPCBoxTypeIconSprite14Template = {
    194,
    48,
    0,
    0,
    0,
    0,
    NNS_G2D_VRAM_TYPE_2DSUB,
    { 49442, 49406, 49404, 49404, -1, -1 },
    1,
    0,
};

const ManagedSpriteTemplate gPCBoxUiSprite0Template = {
    12,
    28,
    0,
    1,
    0,
    0,
    NNS_G2D_VRAM_TYPE_2DMAIN,
    { 49453, 49409, 49407, 49407, -1, -1 },
    3,
    0,
};

const ManagedSpriteTemplate gPCBoxWallpaperListSpriteTemplate = {
    59,
    -21,
    0,
    0,
    10,
    0,
    NNS_G2D_VRAM_TYPE_2DMAIN,
    { 49449, 49408, 49406, 49406, -1, -1 },
    1,
    0,
};

const ManagedSpriteTemplate gPCBoxTrayBoxSpriteTemplate = {
    43,
    -21,
    0,
    0,
    10,
    0,
    NNS_G2D_VRAM_TYPE_2DMAIN,
    { 49443, 49407, 49405, 49405, -1, -1 },
    1,
    0,
};

const ManagedSpriteTemplate gPCBoxMonPicSprite3Template = {
    140,
    100,
    0,
    0,
    10,
    0,
    NNS_G2D_VRAM_TYPE_2DSUB,
    { 49438, 49403, 49402, 49402, -1, -1 },
    1,
    0,
};

const ManagedSpriteTemplate gPCBoxUiSprite4Template = {
    12,
    -21,
    0,
    1,
    5,
    0,
    NNS_G2D_VRAM_TYPE_2DMAIN,
    { 49453, 49409, 49407, 49407, -1, -1 },
    1,
    0,
};

const OamManagerParam gPCBoxOamManagerParam = { 0, 128, 0, 32, 0, 128, 0, 32 };

const PCBoxScreenPos gPCBoxPartySlotPositions[6] = {
    { 0x28, 0xD0  },
    { 0x50, 0xD8  },
    { 0x28, 0xF0  },
    { 0x50, 0xF8  },
    { 0x28, 0x110 },
    { 0x50, 0x118 },
};

const SpriteResourceCountsListUnion gPCBoxSpriteResourceCounts = { 53, 9, 7, 7, 0, 0 };

// clang-format off
const OamCharTransferParam gPCBoxOamCharTransferParam = {
    69, 65536, 16384, GX_OBJVRAMMODE_CHAR_1D_64K, GX_OBJVRAMMODE_CHAR_1D_64K,
};
// clang-format on

const TileRect gPCBoxMonPicRect = { 0, 0, 10, 10 };

const u8 gPCBoxThumbnailTiles[12] = { 0x0E, 0x0F, 0x05, 0x02, 0x0D, 0x0C, 0x06, 0x0B, 0x0A, 0x09, 0x00, 0x00 };

const u8 gPCBoxPartyIconOffsets[6][2] = {
    { 0x18, 0x10 },
    { 0x40, 0x18 },
    { 0x18, 0x30 },
    "@8",
    { 0x18, 0x50 },
    "@X",
};

const s8 gPCBoxOutlineOffsetsX[8] = { 0x01, (s8)0xFF, 0x00, 0x00, 0x01, 0x01, (s8)0xFF, (s8)0xFF };

const u8 gPCBoxTrayCursorX[8] = { 0x50, 0x60, 0x70, 0x90, 0xA0, 0xB0, 0x00, 0x00 };

const s8 gPCBoxOutlineOffsetsY[8] = { 0x00, 0x00, 0x01, (s8)0xFF, 0x01, (s8)0xFF, 0x01, (s8)0xFF };
