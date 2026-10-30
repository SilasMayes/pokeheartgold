// Converted from asm/pokeathlon_pennant_capture_rodata.s (part 1 of 2) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

#include "global.h"

#include "pokeathlon/pokeathlon_pennant_capture.h"

#pragma force_active on

// clang-format off
const GraphicsBanks gPennantCaptureGraphicsBanks = {
    GX_VRAM_BG_64_E, GX_VRAM_BGEXTPLTT_NONE, GX_VRAM_SUB_BG_128_C, GX_VRAM_SUB_BGEXTPLTT_NONE,
    GX_VRAM_OBJ_256_AB, GX_VRAM_OBJEXTPLTT_NONE, GX_VRAM_SUB_OBJ_16_I, GX_VRAM_SUB_OBJEXTPLTT_NONE,
    GX_VRAM_TEX_NONE, GX_VRAM_TEXPLTT_NONE,
};
// clang-format on

// clang-format off
const BgTemplate gPennantCaptureBgTemplate_Main0 = {
    0, 0, 0x00002000, 0, 0x04, 0x00, 0x1A, 0x00, 0x00, 0x03, 0x00, 0x00, 0,
};
// clang-format on

// clang-format off
const BgTemplate gPennantCaptureBgTemplate_Sub1 = {
    0, 0, 0x00000800, 0, 0x01, 0x00, 0x1E, 0x00, 0x00, 0x02, 0x00, 0x00, 0,
};
// clang-format on

// clang-format off
const BgTemplate gPennantCaptureBgTemplate_Sub2 = {
    0, 0, 0x00000800, 0, 0x01, 0x00, 0x1C, 0x01, 0x00, 0x03, 0x00, 0x00, 0,
};
// clang-format on

// clang-format off
const BgTemplate gPennantCaptureBgTemplate_Main3 = {
    0, 0, 0x00000800, 0, 0x01, 0x00, 0x10, 0x01, 0x00, 0x00, 0x00, 0x00, 0,
};
// clang-format on

// clang-format off
const BgTemplate gPennantCaptureBgTemplate_Sub0 = {
    0, 0, 0x00000800, 0, 0x01, 0x00, 0x1F, 0x03, 0x00, 0x00, 0x00, 0x00, 0,
};
// clang-format on

const PokeathlonPennantCaptureHitCodes gPennantCaptureCornerHits = {
    { 5, 6, 7, 8 }
};

// clang-format off
const GraphicsModes gPennantCaptureGraphicsModes = {
    GX_DISPMODE_GRAPHICS, GX_BGMODE_0, GX_BGMODE_0, GX_BG0_AS_2D,
};
// clang-format on

const PokeathlonPennantCaptureHitCodes gPennantCaptureEdgeHits = {
    { 1, 2, 3, 4 }
};

const VecFx32 gPennantCaptureReferenceVector = { 0, 0, 4096 };

const PokeathlonCourseSpritePoolTemplate gPennantCaptureSpritePoolTemplate = {
    190,
    4,
    { 0x04, 0x04, 0x04, 0x04 },
};

// clang-format off
const WindowTemplate gPennantCaptureScoreWindowTemplate __attribute__((aligned(4))) = {
    0x03, 0x00, 0x14, 0x20, 0x02, 0x0F, 1,
};
// clang-format on
