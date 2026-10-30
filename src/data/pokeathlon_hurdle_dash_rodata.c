// Converted from asm/pokeathlon_hurdle_dash_rodata.s by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout. Keep that when editing, or rerun tools/s2c.py.

#include "global.h"

#include "pokeathlon/pokeathlon_hurdle_dash.h"
#include "pokeathlon/pokeathlon_hurdle_dash_race.h"

#pragma force_active on

const s8 gHurdleDashRisingJumpHeights[5][9] = {
    { (s8)0xFC, (s8)0xFC, (s8)0xFC, (s8)0xFC, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { (s8)0xFE, (s8)0xFD, 0x06,     0x0C,     0x10, 0x11, 0x12, 0x12, 0x12 },
    { (s8)0xFE, (s8)0xFD, 0x06,     0x0B,     0x0F, 0x11, 0x12, 0x13, 0x14 },
    { (s8)0xFE, (s8)0xFD, 0x06,     0x0B,     0x0F, 0x11, 0x12, 0x13, 0x14 },
    { (s8)0xFE, (s8)0xFD, 0x06,     0x0A,     0x0E, 0x11, 0x12, 0x13, 0x14 },
};

const s8 gHurdleDashFallingJumpHeights[5][9] = {
    { 0x04, 0x04, 0x04, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x12, 0x12, 0x11, 0x10, 0x0D, 0x0A, 0x06, 0x00, 0x00 },
    { 0x14, 0x14, 0x13, 0x12, 0x11, 0x0F, 0x0B, 0x06, 0x00 },
    { 0x14, 0x14, 0x13, 0x12, 0x11, 0x0F, 0x0B, 0x06, 0x00 },
    { 0x14, 0x14, 0x13, 0x12, 0x11, 0x0F, 0x0B, 0x06, 0x00 },
};

// clang-format off
const GraphicsBanks gHurdleDashGraphicsBanks = {
    GX_VRAM_BG_64_E, GX_VRAM_BGEXTPLTT_NONE, GX_VRAM_SUB_BG_128_C, GX_VRAM_SUB_BGEXTPLTT_NONE,
    GX_VRAM_OBJ_256_AB, GX_VRAM_OBJEXTPLTT_NONE, GX_VRAM_SUB_OBJ_16_I, GX_VRAM_SUB_OBJEXTPLTT_NONE,
    GX_VRAM_TEX_NONE, GX_VRAM_TEXPLTT_NONE,
};
// clang-format on

// clang-format off
const BgTemplate gHurdleDashBgTemplate_Sub3 = {
    0, 0, 0x00000800, 0, 0x01, 0x00, 0x19, 0x00, 0x00, 0x00, 0x00, 0x00, 0,
};
// clang-format on

// clang-format off
const BgTemplate gHurdleDashBgTemplate_Sub2 = {
    0, 0, 0x00001000, 0, 0x02, 0x00, 0x1E, 0x00, 0x00, 0x03, 0x00, 0x00, 0,
};
// clang-format on

// clang-format off
const BgTemplate gHurdleDashBgTemplate_Main2 = {
    0, 0, 0x00001000, 0, 0x02, 0x00, 0x1E, 0x00, 0x00, 0x03, 0x00, 0x00, 0,
};
// clang-format on

// clang-format off
const BgTemplate gHurdleDashBgTemplate_Sub0 = {
    0, 0, 0x00001000, 0, 0x02, 0x00, 0x1A, 0x00, 0x00, 0x01, 0x00, 0x00, 0,
};
// clang-format on

// clang-format off
const BgTemplate gHurdleDashBgTemplate_Sub1 = {
    0, 0, 0x00001000, 0, 0x02, 0x00, 0x1C, 0x00, 0x00, 0x02, 0x00, 0x00, 0,
};
// clang-format on

// clang-format off
const BgTemplate gHurdleDashBgTemplate_Main0 = {
    0, 0, 0x00001000, 0, 0x02, 0x00, 0x1A, 0x00, 0x00, 0x01, 0x00, 0x00, 0,
};
// clang-format on

// clang-format off
const BgTemplate gHurdleDashBgTemplate_Main1 = {
    0, 0, 0x00001000, 0, 0x02, 0x00, 0x1C, 0x00, 0x00, 0x02, 0x00, 0x00, 0,
};
// clang-format on

// clang-format off
const BgTemplate gHurdleDashBgTemplate_Main3 = {
    0, 0, 0x00000800, 0, 0x01, 0x00, 0x19, 0x01, 0x00, 0x00, 0x00, 0x00, 0,
};
// clang-format on

// clang-format off
const GraphicsModes gHurdleDashGraphicsModes = {
    GX_DISPMODE_GRAPHICS, GX_BGMODE_0, GX_BGMODE_0, GX_BG0_AS_2D,
};
// clang-format on

const f32 gHurdleDashBoostSpeeds[4] = { 1.0f, 1.0f, 1.0f, 1.0f };

const PokeathlonHurdleDashLaneX gHurdleDashDustLaneX = {
    { 48, 128, 208 }
};

const PokeathlonCourseSpritePoolTemplate gHurdleDashSceneConfig = {
    107,
    6,
    { 0x06, 0x06, 0x06, 0x06 },
};

const PokeathlonHurdleDashNumberX gHurdleDashNumberX = {
    { 0x00000030, 0x00000080, 0x000000D0 }
};

const PokeathlonHurdleDashLaneX gHurdleDashTouchLaneX = {
    { 48, 128, 208 }
};

const u8 gHurdleDashTimerDigitX[8] = { 0xB0, 0xB8, 0xC8, 0xD8, 0xE0, 0xF0, 0x00, 0x00 };

const WindowTemplate gHurdleDashTimeWindowTemplate = { 0x03, 0x00, 0x14, 0x20, 0x02, 0x0F, 1 };

// clang-format off
const u8 gHurdleDashTimerDigitAnims[8] __attribute__((aligned(4))) = {
    0x01, 0x0C, 0x01, 0x01, 0x0B, 0x01, 0x00, 0x00,
};
// clang-format on
