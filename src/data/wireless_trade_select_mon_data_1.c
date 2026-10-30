// Converted from asm/wireless_trade_select_mon_data.s (part 1 of 4) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

// The C declarations of these do not match the data (see the notes at each
// definition): keep them out of the way of the definitions below.
#define sWirelessTradeSelectMonCursorAnims        sWirelessTradeSelectMonCursorAnims_header_decl
#define sWirelessTradeSelectMonPartnerCursorAnims sWirelessTradeSelectMonPartnerCursorAnims_header_decl
#define sWirelessTradeSelectMonQuitCursorAnims    sWirelessTradeSelectMonQuitCursorAnims_header_decl

#include "global.h"

#include "wireless_trade_select_mon_internal.h"

#pragma force_active on

#undef sWirelessTradeSelectMonCursorAnims
#undef sWirelessTradeSelectMonPartnerCursorAnims
#undef sWirelessTradeSelectMonQuitCursorAnims

const TouchscreenHitbox sWirelessTradeSelectMonSlotHitboxes[14] = {
    { 0x20, 0x47, 0x00, 0x3F },
    { 0x20, 0x47, 0x40, 0x7F },
    { 0x48, 0x6F, 0x00, 0x3F },
    { 0x48, 0x6F, 0x40, 0x7F },
    { 0x70, 0x97, 0x00, 0x3F },
    { 0x70, 0x97, 0x40, 0x7F },
    { 0x20, 0x47, 0x80, 0xBF },
    { 0x20, 0x47, 0xC0, 0xFF },
    { 0x48, 0x6F, 0x80, 0xBF },
    { 0x48, 0x6F, 0xC0, 0xFF },
    { 0x70, 0x97, 0x80, 0xBF },
    { 0x70, 0x97, 0xC0, 0xFF },
    { 0xA0, 0xC0, 0xC8, 0x00 },
    { 0xFF, 0x00, 0x00, 0x00 },
};

// clang-format off
const GraphicsBanks sWirelessTradeSelectMonGraphicsBanks = {
    GX_VRAM_BG_128_A, GX_VRAM_BGEXTPLTT_NONE, GX_VRAM_SUB_BG_128_C, GX_VRAM_SUB_BGEXTPLTT_NONE,
    GX_VRAM_OBJ_128_B, GX_VRAM_OBJEXTPLTT_NONE, GX_VRAM_SUB_OBJ_16_I, GX_VRAM_SUB_OBJEXTPLTT_NONE,
    GX_VRAM_TEX_NONE, GX_VRAM_TEXPLTT_NONE,
};
// clang-format on

// clang-format off
const BgTemplate sWirelessTradeSelectMonBgTemplate_Sub1 = {
    0, 0, 0x00000800, 0, 0x01, 0x00, 0x1E, 0x00, 0x00, 0x01, 0x00, 0x00, 0,
};
// clang-format on

// clang-format off
const BgTemplate sWirelessTradeSelectMonBgTemplate_Sub2 = {
    0, 0, 0x00000800, 0, 0x01, 0x00, 0x1B, 0x00, 0x00, 0x01, 0x00, 0x00, 0,
};
// clang-format on

// clang-format off
const BgTemplate sWirelessTradeSelectMonBgTemplate_Main0 = {
    0, 0, 0x00000800, 0, 0x01, 0x00, 0x1E, 0x00, 0x00, 0x00, 0x00, 0x00, 0,
};
// clang-format on

// clang-format off
const BgTemplate sWirelessTradeSelectMonBgTemplate_Main1 = {
    0, 0, 0x00000800, 0, 0x01, 0x00, 0x1F, 0x02, 0x00, 0x01, 0x00, 0x00, 0,
};
// clang-format on

// clang-format off
const BgTemplate sWirelessTradeSelectMonBgTemplate_Sub0 = {
    0, 0, 0x00000800, 0, 0x01, 0x00, 0x1F, 0x04, 0x00, 0x00, 0x00, 0x00, 0,
};
// clang-format on

// clang-format off
const BgTemplate sWirelessTradeSelectMonBgTemplate_Main3 = {
    0, 0, 0x00000800, 0, 0x01, 0x00, 0x1D, 0x04, 0x00, 0x03, 0x00, 0x00, 0,
};
// clang-format on

// clang-format off
const BgTemplate sWirelessTradeSelectMonBgTemplate_Main2 = {
    0, 0, 0x00000800, 0, 0x01, 0x00, 0x1C, 0x04, 0x00, 0x02, 0x00, 0x00, 0,
};
// clang-format on

#ifdef SDK_PORT
// clang-format off
const u32 sWirelessTradeSelectMonQuitCursorAnims[2][3] = { { 2, 0x11, 0x12 }, { 0x13, 0, 0 } };
// clang-format on
#else
// C declares this as `const u32 sWirelessTradeSelectMonQuitCursorAnims[][3]`, but the label holds 4
// more bytes of data after it.
// clang-format off
const u8 sWirelessTradeSelectMonQuitCursorAnims[16] = {
    0x02, 0x00, 0x00, 0x00, 0x11, 0x00, 0x00, 0x00, 0x12, 0x00, 0x00, 0x00, 0x13, 0x00, 0x00, 0x00,
};
// clang-format on
#endif

#ifdef SDK_PORT
// On the DS the three cursor tables are views into one u32[2][3] table ([side][cursor kind]);
// the port has a complete copy for each.
// clang-format off
const u32 sWirelessTradeSelectMonCursorAnims[2][3] = { { 0, 1, 2 }, { 0x11, 0x12, 0x13 } };
// clang-format on
#else
// C declares this as `const u32 sWirelessTradeSelectMonCursorAnims[][3]`, but one element of that type
// is larger than the data under this label.
const u8 sWirelessTradeSelectMonCursorAnims[4] __attribute__((aligned(4))) = {
    0x00, 0x00, 0x00, 0x00,
};
#endif

#ifdef SDK_PORT
// clang-format off
const u32 sWirelessTradeSelectMonPartnerCursorAnims[2][3] = { { 1, 2, 0x11 }, { 0x12, 0x13, 0 } };
// clang-format on
#else
// C declares this as `const u32 sWirelessTradeSelectMonPartnerCursorAnims[][3]`, but one element of
// that type is larger than the data under this label.
const u8 sWirelessTradeSelectMonPartnerCursorAnims[4] = { 0x01, 0x00, 0x00, 0x00 };
#endif
