// Converted from asm/plaza_game_swalot_plop_data.s (part 4 of 6) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

#include "global.h"

#include "application/plaza_game_swalot_plop.h"

#pragma force_active on

// clang-format off
const u32 gSwalotPlopIntroNamePositions[120] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x0000000C, 2, 0, 0, 0, 0, 0, 0, 0x00000017, 4, 1, 4, 0, 0, 0, 0,
    0x0000000C, 2, 0x00000017, 6, 1, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0x0000000C, 2, 0, 0, 0, 0, 0, 0, 1, 4, 0, 0,
    0x00000017, 4, 0, 0, 0x0000000C, 2, 0, 0, 1, 6, 0x00000017, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0x00000017, 4, 1, 4, 0, 0, 0, 0, 1, 6, 0x00000017, 6, 0, 0, 0x0000000C, 2, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};
// clang-format on

// clang-format off
const GraphicsBanks gSwalotPlopBanks = {
    GX_VRAM_BG_32_FG, GX_VRAM_BGEXTPLTT_NONE, GX_VRAM_SUB_BG_128_C, GX_VRAM_SUB_BGEXTPLTT_NONE,
    GX_VRAM_OBJ_128_B, GX_VRAM_OBJEXTPLTT_NONE, GX_VRAM_SUB_OBJ_16_I, GX_VRAM_SUB_OBJEXTPLTT_NONE,
    GX_VRAM_TEX_0_A, GX_VRAM_TEXPLTT_0123_E,
};
// clang-format on

const u16 gSwalotPlopStageRotations[4][4] = {
    { 0,      0,      0,      0      },
    { 0x7FFF, 0,      0,      0      },
    { 0x7FFF, 0xD554, 0x2AAA, 0      },
    { 0x7FFF, 0,      0xBFFF, 0x3FFF },
};

const u16 gSwalotPlopCameraAngles[1][4] = {
    { 0, 0x7FFF, 0x3FFF, 0xBFFF }
};
