// Converted from asm/overlay_14_state_dispatch_rodata_67.s (part 2 of 6) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

#include "global.h"

#include "constants/pokemon.h"

#include "application/pc_box/pc_box_internal.h"

#pragma force_active on

// clang-format off
const GraphicsBanks gPCBoxGfxBanks = {
    GX_VRAM_BG_128_B, GX_VRAM_BGEXTPLTT_NONE, GX_VRAM_SUB_BG_128_C, GX_VRAM_SUB_BGEXTPLTT_NONE,
    GX_VRAM_OBJ_64_E, GX_VRAM_OBJEXTPLTT_NONE, GX_VRAM_SUB_OBJ_16_I, GX_VRAM_SUB_OBJEXTPLTT_NONE,
    GX_VRAM_TEX_0_A, GX_VRAM_TEXPLTT_01_FG,
};
// clang-format on

// clang-format off
const BgTemplate gPCBoxBgTemplate5 = {
    0, 0, 0x00000800, 0, 0x01, 0x00, 0x1E, 0x00, 0x00, 0x02, 0x00, 0x00, 0,
};
// clang-format on

// clang-format off
const BgTemplate gPCBoxBgTemplate3 = {
    0, 0, 0x00001000, 0, 0x03, 0x00, 0x1B, 0x00, 0x00, 0x03, 0x00, 0x00, 0,
};
// clang-format on

// clang-format off
const BgTemplate gPCBoxBgTemplate2 = {
    0, 0, 0x00000800, 0, 0x01, 0x00, 0x1D, 0x02, 0x00, 0x02, 0x00, 0x00, 0,
};
// clang-format on

// clang-format off
const BgTemplate gPCBoxBgTemplate6 = {
    0, 0, 0x00000800, 0, 0x01, 0x00, 0x1D, 0x06, 0x00, 0x00, 0x00, 0x00, 0,
};
// clang-format on

// clang-format off
const BgTemplate gPCBoxBgTemplate1 = {
    0, 0, 0x00000800, 0, 0x01, 0x00, 0x1E, 0x04, 0x00, 0x01, 0x00, 0x00, 0,
};
// clang-format on

// clang-format off
const BgTemplate gPCBoxBgTemplate4 = {
    0, 0, 0x00000800, 0, 0x01, 0x00, 0x1F, 0x04, 0x00, 0x01, 0x00, 0x00, 0,
};
// clang-format on

// clang-format off
const BgTemplate gPCBoxBgTemplate0 = {
    0, 0, 0x00000800, 0, 0x01, 0x00, 0x1F, 0x06, 0x00, 0x00, 0x00, 0x00, 0,
};
// clang-format on
