// Converted from asm/battle_castle_data.s (part 3 of 7) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

#include "global.h"

#include "frontier/battle_castle.h"

#pragma force_active on

// clang-format off
const u16 gBattleCastleRentalBerries[32] = {
    0x0095, 0x0096, 0x0097, 0x0098, 0x0099, 0x009C, 0x009D, 0x009E, 0x00C9, 0x00CA, 0x00CB, 0x00CC, 0x00CD,
    0x00CE, 0x00CF, 0x00B8, 0x00B9, 0x00BA, 0x00BB, 0x00BC, 0x00BD, 0x00BE, 0x00BF, 0x00C0, 0x00C1, 0x00C2,
    0x00C3, 0x00C4, 0x00C5, 0x00C6, 0x00C7, 0x00C8,
};
// clang-format on

// clang-format off
const u16 gBattleCastleRentalBerryCosts[32] = {
    2, 2, 2, 2, 2, 2, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
};
// clang-format on

const BattleCastleMenuOption gBattleCastlePartyAppHealMenuOptions[5] = {
    { 1, 19, 1  },
    { 2, 20, 2  },
    { 3, 21, 3  },
    { 1, 22, 4  },
    { 1, 23, -2 },
};

// clang-format off
const u16 gBattleCastleRentalItems[27] = {
    0x00DD, 0x00D9, 0x010F, 0x00FD, 0x0115, 0x010D, 0x011E, 0x0128, 0x0110, 0x0111, 0x00EC, 0x0102, 0x00D6,
    0x00E6, 0x0113, 0x00EA, 0x00D5, 0x00E8, 0x0109, 0x0114, 0x00DC, 0x0129, 0x011F, 0x010A, 0x010B, 0x010C,
    0x010E,
};
// clang-format on

// clang-format off
const u16 gBattleCastleRentalItemCosts[27] = {
    0x000A, 0x000F, 5, 0x000F, 0x000A, 0x000A, 0x000A, 0x000A, 0x000A, 0x000A, 0x000F, 0x000F, 5, 0x000F,
    0x000A, 0x0014, 0x0014, 0x0014, 0x0014, 0x0014, 0x0014, 0x0014, 0x0014, 0x0014, 0x0014, 0x0014, 0x0014,
};
// clang-format on

const BattleCastleMenuOption gBattleCastlePartyAppRentalMenuOptions[4] = {
    { 1, 44, 6  },
    { 2, 45, 7  },
    { 1, 46, 8  },
    { 1, 47, -2 },
};

// clang-format off
const GraphicsBanks gBattleCastlePartyAppGraphicsBanks = {
    GX_VRAM_BG_128_B, GX_VRAM_BGEXTPLTT_NONE, GX_VRAM_SUB_BG_128_C, GX_VRAM_SUB_BGEXTPLTT_NONE,
    GX_VRAM_OBJ_64_E, GX_VRAM_OBJEXTPLTT_NONE, GX_VRAM_SUB_OBJ_16_I, GX_VRAM_SUB_OBJEXTPLTT_NONE,
    GX_VRAM_TEX_0_A, GX_VRAM_TEXPLTT_01_FG,
};
// clang-format on

const u8 gBattleCastlePartyAppButtonRects[9][4] = {
    { 0x00, 0x04, 0x10, 0x05 },
    { 0x10, 0x04, 0x10, 0x05 },
    { 0x00, 0x09, 0x10, 0x05 },
    { 0x10, 0x09, 0x10, 0x05 },
    { 0x00, 0x0E, 0x10, 0x05 },
    { 0x10, 0x0E, 0x10, 0x05 },
    { 0x00, 0x14, 0x04, 0x04 },
    { 0x06, 0x14, 0x04, 0x04 },
    { 0x19, 0x14, 0x07, 0x04 },
};

// clang-format off
const BgTemplate gBattleCastlePartyAppBgTemplate_Sub0 = {
    0, 0, 0x00000800, 0, 0x01, 0x00, 0x1F, 0x00, 0x00, 0x03, 0x00, 0x00, 0,
};
// clang-format on

// clang-format off
const BgTemplate gBattleCastlePartyAppBgTemplate_Main1 = {
    0, 0, 0x00000800, 0, 0x01, 0x00, 0x1F, 0x04, 0x00, 0x02, 0x00, 0x00, 0,
};
// clang-format on

// clang-format off
const BgTemplate gBattleCastlePartyAppBgTemplate_Main2 = {
    0, 0, 0x00000800, 0, 0x01, 0x00, 0x1D, 0x00, 0x00, 0x01, 0x00, 0x00, 0,
};
// clang-format on

// clang-format off
const BgTemplate gBattleCastlePartyAppBgTemplate_Sub2 = {
    0, 0, 0x00000800, 0, 0x01, 0x00, 0x1D, 0x01, 0x00, 0x01, 0x00, 0x00, 0,
};
// clang-format on

// clang-format off
const BgTemplate gBattleCastlePartyAppBgTemplate_Sub1 = {
    0, 0, 0x00000800, 0, 0x01, 0x00, 0x1E, 0x04, 0x00, 0x02, 0x00, 0x00, 0,
};
// clang-format on

// clang-format off
const BgTemplate gBattleCastlePartyAppBgTemplate_Main0 = {
    0, 0, 0x00000800, 0, 0x01, 0x00, 0x1E, 0x06, 0x00, 0x00, 0x00, 0x00, 0,
};
// clang-format on

// clang-format off
const BgTemplate gBattleCastlePartyAppBgTemplate_Sub3 = {
    0, 0, 0x00000800, 0, 0x01, 0x00, 0x1C, 0x06, 0x00, 0x00, 0x00, 0x00, 0,
};
// clang-format on

// clang-format off
const BgTemplate gBattleCastlePartyAppBgTemplate_Main3 = {
    0, 0, 0x00000800, 0, 0x01, 0x00, 0x1C, 0x02, 0x00, 0x03, 0x00, 0x00, 0,
};
// clang-format on

const BattleCastleMenuItem gBattleCastlePartyAppMainMenuItems[3] = {
    { 9,  0  },
    { 10, 5  },
    { 13, -2 }
};
