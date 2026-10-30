// Converted from asm/bag_app_data.s (part 5 of 5) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

#include "global.h"

#include "constants/items.h"
#include "constants/sndseq.h"

#include "application/bag/bag_app.h"
#include "msgdata/msg/msg_0010.h"

#pragma force_active on

const ManagedSpriteTemplate gBagSpriteTemplates[39] = {
    { 177, 14,  0, 0,      0, 0, NNS_G2D_VRAM_TYPE_2DMAIN, { 49401, 49401, 49401, 49402, 0, 0 }, 1, 0 },
    { 22,  59,  0, 0,      0, 0, NNS_G2D_VRAM_TYPE_2DSUB,  { 49404, 49403, 49404, 49405, 0, 0 }, 1, 0 },
    { 152, 59,  0, 0,      0, 0, NNS_G2D_VRAM_TYPE_2DSUB,  { 49405, 49404, 49404, 49405, 0, 0 }, 1, 0 },
    { 22,  100, 0, 0,      0, 0, NNS_G2D_VRAM_TYPE_2DSUB,  { 49406, 49405, 49404, 49405, 0, 0 }, 1, 0 },
    { 152, 100, 0, 0,      0, 0, NNS_G2D_VRAM_TYPE_2DSUB,  { 49407, 49406, 49404, 49405, 0, 0 }, 1, 0 },
    { 22,  139, 0, 0,      0, 0, NNS_G2D_VRAM_TYPE_2DSUB,  { 49408, 49407, 49404, 49405, 0, 0 }, 1, 0 },
    { 152, 139, 0, 0,      0, 0, NNS_G2D_VRAM_TYPE_2DSUB,  { 49409, 49408, 49404, 49405, 0, 0 }, 1, 0 },
    { 48,  112, 0, 0,      0, 0, NNS_G2D_VRAM_TYPE_2DMAIN, { 49411, 49410, 49406, 49407, 0, 0 }, 0, 0 },
    { 144, 112, 0, 0,      0, 0, NNS_G2D_VRAM_TYPE_2DMAIN, { 49412, 49410, 49406, 49407, 0, 0 }, 0, 0 },
    { 16,  16,  0, 0,      1, 0, NNS_G2D_VRAM_TYPE_2DSUB,  { 49403, 49402, 49403, 49404, 0, 0 }, 0, 0 },
    { 48,  16,  0, 1,      1, 1, NNS_G2D_VRAM_TYPE_2DSUB,  { 49403, 49402, 49403, 49404, 0, 0 }, 0, 0 },
    { 80,  16,  0, 2,      1, 2, NNS_G2D_VRAM_TYPE_2DSUB,  { 49403, 49402, 49403, 49404, 0, 0 }, 0, 0 },
    { 112, 16,  0, 3,      1, 3, NNS_G2D_VRAM_TYPE_2DSUB,  { 49403, 49402, 49403, 49404, 0, 0 }, 0, 0 },
    { 144, 16,  0, 4,      1, 4, NNS_G2D_VRAM_TYPE_2DSUB,  { 49403, 49402, 49403, 49404, 0, 0 }, 0, 0 },
    { 176, 16,  0, 5,      1, 5, NNS_G2D_VRAM_TYPE_2DSUB,  { 49403, 49402, 49403, 49404, 0, 0 }, 0, 0 },
    { 208, 16,  0, 6,      1, 6, NNS_G2D_VRAM_TYPE_2DSUB,  { 49403, 49402, 49403, 49404, 0, 0 }, 0, 0 },
    { 240, 16,  0, 7,      1, 7, NNS_G2D_VRAM_TYPE_2DSUB,  { 49403, 49402, 49403, 49404, 0, 0 }, 0, 0 },
    { 24,  176, 0, 0x000C, 1, 8, NNS_G2D_VRAM_TYPE_2DSUB,  { 49403, 49402, 49403, 49404, 0, 0 }, 0, 0 },
    { 64,  176, 0, 0x000D, 1, 8, NNS_G2D_VRAM_TYPE_2DSUB,  { 49403, 49402, 49403, 49404, 0, 0 }, 0, 0 },
    { 224, 176, 0, 0x0010, 1, 8, NNS_G2D_VRAM_TYPE_2DSUB,  { 49403, 49402, 49403, 49404, 0, 0 }, 0, 0 },
    { 16,  16,  0, 8,      0, 9, NNS_G2D_VRAM_TYPE_2DSUB,  { 49403, 49402, 49403, 49404, 0, 0 }, 1, 0 },
    { 16,  48,  0, 0x0013, 1, 9, NNS_G2D_VRAM_TYPE_2DSUB,  { 49403, 49402, 49403, 49404, 0, 0 }, 1, 0 },
    { 144, 48,  0, 0x0013, 1, 9, NNS_G2D_VRAM_TYPE_2DSUB,  { 49403, 49402, 49403, 49404, 0, 0 }, 1, 0 },
    { 16,  88,  0, 0x0013, 1, 9, NNS_G2D_VRAM_TYPE_2DSUB,  { 49403, 49402, 49403, 49404, 0, 0 }, 1, 0 },
    { 144, 88,  0, 0x0013, 1, 9, NNS_G2D_VRAM_TYPE_2DSUB,  { 49403, 49402, 49403, 49404, 0, 0 }, 1, 0 },
    { 16,  128, 0, 0x0013, 1, 9, NNS_G2D_VRAM_TYPE_2DSUB,  { 49403, 49402, 49403, 49404, 0, 0 }, 1, 0 },
    { 144, 128, 0, 0x0013, 1, 9, NNS_G2D_VRAM_TYPE_2DSUB,  { 49403, 49402, 49403, 49404, 0, 0 }, 1, 0 },
    { 16,  48,  0, 0x0014, 0, 9, NNS_G2D_VRAM_TYPE_2DSUB,  { 49403, 49402, 49403, 49404, 0, 0 }, 0, 0 },
    { 48,  144, 0, 0x0016, 0, 8, NNS_G2D_VRAM_TYPE_2DSUB,  { 49403, 49402, 49403, 49404, 0, 0 }, 0, 0 },
    { 144, 144, 0, 0x0016, 0, 8, NNS_G2D_VRAM_TYPE_2DSUB,  { 49403, 49402, 49403, 49404, 0, 0 }, 0, 0 },
    { 48,  176, 0, 0x0016, 0, 8, NNS_G2D_VRAM_TYPE_2DSUB,  { 49403, 49402, 49403, 49404, 0, 0 }, 0, 0 },
    { 144, 176, 0, 0x0016, 0, 8, NNS_G2D_VRAM_TYPE_2DSUB,  { 49403, 49402, 49403, 49404, 0, 0 }, 0, 0 },
    { 136, 104, 0, 0x0019, 0, 8, NNS_G2D_VRAM_TYPE_2DSUB,  { 49403, 49402, 49403, 49404, 0, 0 }, 0, 0 },
    { 168, 104, 0, 0x0019, 0, 8, NNS_G2D_VRAM_TYPE_2DSUB,  { 49403, 49402, 49403, 49404, 0, 0 }, 0, 0 },
    { 200, 104, 0, 0x0019, 0, 8, NNS_G2D_VRAM_TYPE_2DSUB,  { 49403, 49402, 49403, 49404, 0, 0 }, 0, 0 },
    { 136, 152, 0, 0x001B, 0, 8, NNS_G2D_VRAM_TYPE_2DSUB,  { 49403, 49402, 49403, 49404, 0, 0 }, 0, 0 },
    { 168, 152, 0, 0x001B, 0, 8, NNS_G2D_VRAM_TYPE_2DSUB,  { 49403, 49402, 49403, 49404, 0, 0 }, 0, 0 },
    { 200, 152, 0, 0x001B, 0, 8, NNS_G2D_VRAM_TYPE_2DSUB,  { 49403, 49402, 49403, 49404, 0, 0 }, 0, 0 },
    { 136, 176, 0, 0x001F, 0, 8, NNS_G2D_VRAM_TYPE_2DSUB,  { 49403, 49402, 49403, 49404, 0, 0 }, 0, 0 },
};

const BagAppCursorPos gBagAppCursorPositions[21] = {
    { 0x10, 0x10, 0x08, 0x09 },
    { 0x30, 0x10, 0x08, 0x09 },
    { 0x50, 0x10, 0x08, 0x09 },
    { 0x70, 0x10, 0x08, 0x09 },
    { 0x90, 0x10, 0x08, 0x09 },
    { 0xB0, 0x10, 0x08, 0x09 },
    { 0xD0, 0x10, 0x08, 0x09 },
    { 0xF0, 0x10, 0x08, 0x09 },
    { 0x30, 0x38, 0x0A, 0x09 },
    { 0xB0, 0x38, 0x0A, 0x09 },
    { 0x30, 0x60, 0x0A, 0x09 },
    { 0xB0, 0x60, 0x0A, 0x09 },
    { 0x30, 0x88, 0x0A, 0x09 },
    { 0xB0, 0x88, 0x0A, 0x09 },
    { 0x18, 0xB0, 0x0E, 0x09 },
    { 0x40, 0xB0, 0x0E, 0x09 },
    { 0xE0, 0xB0, 0x11, 0x09 },
    { 0x30, 0x90, 0x17, 0x09 },
    { 0x90, 0x90, 0x17, 0x09 },
    { 0x30, 0xB0, 0x17, 0x09 },
    { 0x90, 0xB0, 0x17, 0x09 },
};

const int gQuantityButtonSprites[2][6] = {
    { 0, 1, 3, 4, 0, 0 },
    { 0, 1, 2, 3, 4, 5 }
};

const int gQuantityButtonAnims[2][6] = {
    { 25, 25, 27, 27, 0,  0  },
    { 25, 25, 25, 27, 27, 27 }
};

const BagAppCursorPos gBagAppMoveCursorPositions[9] = {
    { 0x30, 0x38, 0x14, 0x09 },
    { 0xB0, 0x38, 0x14, 0x09 },
    { 0x30, 0x60, 0x14, 0x09 },
    { 0xB0, 0x60, 0x14, 0x09 },
    { 0x30, 0x88, 0x14, 0x09 },
    { 0xB0, 0x88, 0x14, 0x09 },
    { 0x18, 0xB0, 0x0E, 0x09 },
    { 0x40, 0xB0, 0x0E, 0x09 },
    { 0xE0, 0xB0, 0x11, 0x09 },
};

const OamManagerParam gBagOamManagerParam = { 0, 128, 0, 32, 0, 128, 0, 32 };

const BagAppCursorPos gBagAppQuantityCursorPositions[8] = {
    { 0x88, 0x68, 0x1D, 0x09 },
    { 0xA8, 0x68, 0x1D, 0x09 },
    { 0xC8, 0x68, 0x1D, 0x09 },
    { 0x88, 0xA0, 0x1D, 0x09 },
    { 0xA8, 0xA0, 0x1D, 0x09 },
    { 0xC8, 0xA0, 0x1D, 0x09 },
    { 0xA0, 0xB0, 0x11, 0x09 },
    { 0xE0, 0xB0, 0x11, 0x09 },
};

const int gHiddenQuantityButtons[2][4] = {
    { 0, 3, 0, 0 },
    { 0, 1, 3, 4 }
};

const SpriteResourceCountsListUnion gBagSpriteResourceCounts = { 12, 10, 6, 7, 0, 0 };

// clang-format off
const OamCharTransferParam gBagOamCharTransferParam = {
    39, 131072, 16384, GX_OBJVRAMMODE_CHAR_1D_32K, GX_OBJVRAMMODE_CHAR_1D_32K,
};
// clang-format on

const int gQuantityButtonCounts[2] = { 4, 6 };

const int gHiddenQuantityButtonCounts[2] = { 2, 4 };
