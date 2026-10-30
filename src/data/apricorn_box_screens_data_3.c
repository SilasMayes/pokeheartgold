// Converted from asm/apricorn_box_screens_data.s (part 3 of 3) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

#include "global.h"

#include "application/apricorn_box/apricorn_box_screen_internal.h"

#pragma force_active on

extern const u8 gApricornBoxListMenu0Messages[3];
extern const u8 gApricornBoxListMenu1Messages[2];

const UnmanagedSpriteTemplate gApricornBoxSpriteTemplates[7] = {
    { 0, 224, 176, 0, 0,      4, 0, NNS_G2D_VRAM_TYPE_2DMAIN, 1, 0, 0, 0 },
    { 0, 27,  96,  0, 3,      0, 0, NNS_G2D_VRAM_TYPE_2DMAIN, 1, 0, 0, 0 },
    { 0, 27,  49,  0, 9,      3, 0, NNS_G2D_VRAM_TYPE_2DMAIN, 1, 0, 0, 0 },
    { 0, 192, 152, 0, 0x0010, 6, 0, NNS_G2D_VRAM_TYPE_2DMAIN, 1, 0, 0, 0 },
    { 0, 192, 96,  0, 0x0014, 5, 0, NNS_G2D_VRAM_TYPE_2DMAIN, 1, 0, 0, 0 },
    { 0, 160, 112, 0, 0x001C, 7, 0, NNS_G2D_VRAM_TYPE_2DMAIN, 1, 0, 0, 0 },
    { 0, 103, 96,  0, 0x0018, 8, 0, NNS_G2D_VRAM_TYPE_2DMAIN, 1, 0, 0, 0 },
};

const WindowTemplate gApricornBoxWindowTemplates[11] = {
    { 0x00, 0x05, 0x09, 0x16, 0x06, 0x0C, 0x00A6 },
    { 0x02, 0x03, 0x01, 0x1C, 0x02, 0x0C, 0x012A },
    { 0x02, 0x19, 0x15, 0x06, 0x02, 0x09, 0x0162 },
    { 0x02, 0x02, 0x15, 0x0A, 0x02, 0x0C, 0x016E },
    { 0x07, 0x02, 0x11, 0x1C, 0x06, 0x0C, 0x0358 },
    { 0x00, 0x09, 0x07, 0x09, 0x02, 0x0C, 0x0182 },
    { 0x00, 0x11, 0x0D, 0x06, 0x02, 0x0C, 0x0194 },
    { 0x00, 0x11, 0x10, 0x06, 0x02, 0x0C, 0x01A0 },
    { 0x00, 0x0C, 0x0D, 0x02, 0x03, 0x0C, 0x01AC },
    { 0x00, 0x09, 0x0D, 0x02, 0x03, 0x0C, 0x01B2 },
    { 0x00, 0x0E, 0x0E, 0x02, 0x02, 0x0C, 0x01B8 },
};

// clang-format off
const GraphicsBanks gApricornBoxGraphicsBanks = {
    GX_VRAM_BG_128_A, GX_VRAM_BGEXTPLTT_NONE, GX_VRAM_SUB_BG_128_C, GX_VRAM_SUB_BGEXTPLTT_NONE,
    GX_VRAM_OBJ_64_E, GX_VRAM_OBJEXTPLTT_NONE, GX_VRAM_SUB_OBJ_16_I, GX_VRAM_SUB_OBJEXTPLTT_NONE,
    GX_VRAM_TEX_NONE, GX_VRAM_TEXPLTT_NONE,
};
// clang-format on

const OamManagerParam gApricornBoxOamManagerParam = { 0, 128, 0, 32, 0, 128, 0, 32 };

// clang-format off
const BgTemplate gApricornBoxBgTemplate_Sub0 = {
    0, 0, 0x00000800, 0, 0x01, 0x00, 0x1F, 0x04, 0x00, 0x00, 0x00, 0x00, 0,
};
// clang-format on

// clang-format off
const BgTemplate gApricornBoxBgTemplate_Main1 = {
    0, 0, 0x00000800, 0, 0x01, 0x00, 0x1E, 0x00, 0x00, 0x01, 0x00, 0x00, 0,
};
// clang-format on

// clang-format off
const BgTemplate gApricornBoxBgTemplate_Main3 = {
    0, 0, 0x00000800, 0, 0x01, 0x00, 0x1C, 0x00, 0x00, 0x03, 0x00, 0x00, 0,
};
// clang-format on

// clang-format off
const BgTemplate gApricornBoxBgTemplate_Main2 = {
    0, 0, 0x00000800, 0, 0x01, 0x00, 0x1D, 0x04, 0x00, 0x02, 0x00, 0x00, 0,
};
// clang-format on

// clang-format off
const BgTemplate gApricornBoxBgTemplate_Main0 = {
    0, 0, 0x00000800, 0, 0x01, 0x00, 0x1F, 0x04, 0x00, 0x00, 0x00, 0x00, 0,
};
// clang-format on

// clang-format off
const BgTemplate gApricornBoxBgTemplate_Sub3 = {
    0, 0, 0x00000800, 0, 0x01, 0x00, 0x1E, 0x00, 0x00, 0x03, 0x00, 0x00, 0,
};
// clang-format on

// x, y
const u16 gApricornBoxApricornPositions[7][2] = {
    { 27, 49  },
    { 75, 65  },
    { 27, 81  },
    { 75, 97  },
    { 27, 113 },
    { 75, 129 },
    { 27, 145 },
};

// clang-format off
const OamCharTransferParam gApricornBoxOamCharTransferParam = {
    3, 65536, 16384, GX_OBJVRAMMODE_CHAR_1D_32K, GX_OBJVRAMMODE_CHAR_1D_32K,
};
// clang-format on

// clang-format off
const GraphicsModes gApricornBoxGraphicsModes = {
    GX_DISPMODE_GRAPHICS, GX_BGMODE_0, GX_BGMODE_0, GX_BG0_AS_2D,
};
// clang-format on

// count, x, y, messages
const ApricornBoxListDesc gApricornBoxListMenus[2] = {
    { 3, 0x16, 0x0E, gApricornBoxListMenu0Messages },
    { 2, 0x11, 0x0C, gApricornBoxListMenu1Messages },
};

const ResdatIdList gApricornBoxSpriteResources = { 0x0012, 0x0013, 0x0011, 0x0010, 0xFFFF, 0xFFFF, 0x004C };
