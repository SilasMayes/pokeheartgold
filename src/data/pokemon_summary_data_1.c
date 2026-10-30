// Converted from asm/pokemon_summary_data.s (part 1 of 2) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

#include "global.h"

#include "constants/field_move_response.h"
#include "constants/items.h"
#include "constants/moves.h"
#include "constants/pokemon.h"
#include "constants/ribbon.h"

#include "msgdata/msg/msg_0300.h"

#include "pokemon_summary.h"
#include "pokemon_summary_internal.h"

#pragma force_active on

const TouchscreenHitbox gPokemonSummaryRibbonHitboxes[13] = {
    { 0x08, 0x27, 0x10, 0x2F },
    { 0x08, 0x27, 0x30, 0x4F },
    { 0x08, 0x27, 0x50, 0x70 },
    { 0x30, 0x4F, 0x10, 0x2F },
    { 0x30, 0x4F, 0x30, 0x4F },
    { 0x30, 0x4F, 0x50, 0x70 },
    { 0x58, 0x77, 0x10, 0x2F },
    { 0x58, 0x77, 0x30, 0x4F },
    { 0x58, 0x77, 0x50, 0x70 },
    { 0x0C, 0x33, 0x74, 0x8B },
    { 0x4C, 0x73, 0x74, 0x8B },
    { 0xB0, 0xBF, 0xD0, 0xFF },
    { 0xFF, 0x00, 0x00, 0x00 },
};

const u32 gPokemonSummaryPageScreens[4][3] = {
    { 13, 12, 14 },
    { 19, 17, 18 },
    { 10, 9,  9  },
    { 13, 12, 12 }
};

// clang-format off
const GraphicsBanks gPokemonSummaryGraphicsBanks = {
    GX_VRAM_BG_128_A, GX_VRAM_BGEXTPLTT_NONE, GX_VRAM_SUB_BG_128_C, GX_VRAM_SUB_BGEXTPLTT_NONE,
    GX_VRAM_OBJ_64_E, GX_VRAM_OBJEXTPLTT_NONE, GX_VRAM_SUB_OBJ_16_I, GX_VRAM_SUB_OBJEXTPLTT_NONE,
    GX_VRAM_TEX_0_B, GX_VRAM_TEXPLTT_01_FG,
};
// clang-format on

// clang-format off
const BgTemplate gPokemonSummaryBgTemplate2 = {
    0, 0, 0x00002000, 0, 0x04, 0x00, 0x1B, 0x00, 0x00, 0x01, 0x00, 0x00, 0,
};
// clang-format on

// clang-format off
const BgTemplate gPokemonSummaryBgTemplate3 = {
    0, 0, 0x00000800, 0, 0x01, 0x00, 0x1A, 0x00, 0x00, 0x03, 0x00, 0x00, 0,
};
// clang-format on

// clang-format off
const BgTemplate gPokemonSummaryBgTemplate4 = {
    0, 0, 0x00000800, 0, 0x01, 0x00, 0x1F, 0x04, 0x00, 0x00, 0x00, 0x00, 0,
};
// clang-format on

// clang-format off
const BgTemplate gPokemonSummaryBgTemplate5 = {
    0, 0, 0x00002000, 0, 0x04, 0x00, 0x1B, 0x02, 0x00, 0x02, 0x00, 0x00, 0,
};
// clang-format on

// clang-format off
const BgTemplate gPokemonSummaryBgTemplate6 = {
    0, 0, 0x00000800, 0, 0x01, 0x00, 0x1A, 0x00, 0x00, 0x03, 0x00, 0x00, 0,
};
// clang-format on

// clang-format off
const BgTemplate gPokemonSummaryBgTemplate1 = {
    0, 0, 0x00000800, 0, 0x01, 0x00, 0x1F, 0x04, 0x00, 0x00, 0x00, 0x00, 0,
};
// clang-format on

const TouchscreenHitbox gPokemonSummaryMoveHitboxes[5] = {
    { 0x08, 0x27, 0x08, 0x7F },
    { 0x28, 0x47, 0x08, 0x7F },
    { 0x48, 0x67, 0x08, 0x7F },
    { 0x68, 0x87, 0x08, 0x7F },
    { 0xFF, 0x00, 0x00, 0x00 },
};

// clang-format off
const GraphicsModes gPokemonSummaryGraphicsModes = {
    GX_DISPMODE_GRAPHICS, GX_BGMODE_0, GX_BGMODE_0, GX_BG0_AS_3D,
};
// clang-format on

const TouchscreenHitbox gPokemonSummaryMonButtonHitboxes[3] = {
    { 0x28, 0x3F, 0xC0, 0xEF },
    { 0x68, 0x7F, 0xC0, 0xEF },
    { 0xFF, 0x00, 0x00, 0x00 },
};

const TouchscreenHitbox gPokemonSummaryConfirmButtonHitbox[1] = {
    { 0x98, 0xB7, 0x08, 0x7F }
};

const TouchscreenHitbox gPokemonSummarySwapButtonHitbox[1] = {
    { 0x88, 0x97, 0x08, 0x57 }
};

const TouchscreenHitbox gPokemonSummaryCancelButtonHitbox[1] __attribute__((aligned(4))) = {
    { 0xA5, 0xBC, 0xBE, 0xF9 },
};
