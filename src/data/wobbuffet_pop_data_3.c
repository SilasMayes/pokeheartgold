// Converted from asm/wobbuffet_pop_data.s (part 3 of 4) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

#include "global.h"

#include "wobbuffet_pop_internal.h"

#pragma force_active on

// clang-format off
const GraphicsBanks gWobbuffetPopBanks = {
    GX_VRAM_BG_128_B, GX_VRAM_BGEXTPLTT_NONE, GX_VRAM_SUB_BG_128_C, GX_VRAM_SUB_BGEXTPLTT_NONE,
    GX_VRAM_OBJ_64_E, GX_VRAM_OBJEXTPLTT_NONE, GX_VRAM_SUB_OBJ_16_I, GX_VRAM_SUB_OBJEXTPLTT_NONE,
    GX_VRAM_TEX_0_A, GX_VRAM_TEXPLTT_01_FG,
};
// clang-format on

const OamManagerParam gWobbuffetPopOamManagerParam = { 0, 128, 0, 32, 0, 128, 0, 32 };

const SpriteResourceCountsListUnion gWobbuffetPopSpriteResourceCounts = { 96, 32, 64, 64, 2, 2 };

// clang-format off
const OamCharTransferParam gWobbuffetPopOamCharTransfer = {
    96, 65536, 16384, GX_OBJVRAMMODE_CHAR_1D_128K, GX_OBJVRAMMODE_CHAR_1D_32K,
};
// clang-format on
