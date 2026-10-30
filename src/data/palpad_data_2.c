// Converted from asm/palpad_data.s (part 2 of 5) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

// The C declarations of these do not match the data (see the notes at each
// definition): keep them out of the way of the definitions below.
#define gPalPadDetailsPageWindowSpecs      gPalPadDetailsPageWindowSpecs_header_decl
#define gPalPadDetailsFrontierPagePrinters gPalPadDetailsFrontierPagePrinters_header_decl

#include "global.h"

#include "application/palpad/palpad_internal.h"

#pragma force_active on

#undef gPalPadDetailsPageWindowSpecs
#undef gPalPadDetailsFrontierPagePrinters

extern const PalPadWindowSpec sPalPadDetailsPage0WindowSpecs[4];
extern const PalPadWindowSpec sPalPadDetailsPage1WindowSpecs[1];
extern const PalPadWindowSpec sPalPadDetailsPage2WindowSpecs[4];
extern const PalPadWindowSpec sPalPadDetailsPage3WindowSpecs[5];
extern const PalPadWindowSpec sPalPadDetailsPage4WindowSpecs;
extern const PalPadWindowSpec sPalPadDetailsPage5WindowSpecs;
extern const PalPadWindowSpec sPalPadDetailsPage6WindowSpecs;
extern const PalPadWindowSpec sPalPadDetailsPage7WindowSpecs;

const PalPadListMenuEntry gPalPadRosterFriendMenus[2][4] = {
    { { 8, 7 },   { 9, 10 }, { 10, 15 }, { 11, 2 } },
    { { 61, 21 }, { 9, 10 }, { 10, 15 }, { 11, 2 } },
};

const WindowTemplate gPalPadDetailsProfileWindowTemplates[8] = {
    { 0x04, 0x19, 0x01, 0x06, 0x02, 0x0E, 1      },
    { 0x04, 0x01, 0x00, 0x18, 0x03, 0x0E, 0x000D },
    { 0x04, 0x16, 0x06, 0x09, 0x02, 0x0E, 0x0055 },
    { 0x04, 0x09, 0x11, 0x08, 0x02, 0x0E, 0x0073 },
    { 0x04, 0x13, 0x15, 0x0B, 0x02, 0x0E, 0x00A5 },
    { 0x04, 0x04, 0x04, 0x0A, 0x0A, 0x0F, 0x00BB },
    { 0x04, 0x01, 0x11, 0x06, 0x02, 0x0E, 0x0067 },
    { 0x04, 0x01, 0x15, 0x11, 0x02, 0x0E, 0x0083 },
};

const TouchscreenHitbox gPalPadRosterHitboxes[16] = {
    { 0x20, 0x40, 0x10, 0x80 },
    { 0x40, 0x60, 0x10, 0x80 },
    { 0x60, 0x80, 0x10, 0x80 },
    { 0x80, 0xA0, 0x10, 0x80 },
    { 0x20, 0x40, 0x80, 0xF0 },
    { 0x40, 0x60, 0x80, 0xF0 },
    { 0x60, 0x80, 0x80, 0xF0 },
    { 0x80, 0xA0, 0x80, 0xF0 },
    { 0xA0, 0xC0, 0x88, 0xF8 },
    { 0x58, 0x68, 0x00, 0x10 },
    { 0x58, 0x68, 0xF0, 0x00 },
    { 0x00, 0x20, 0x80, 0xA0 },
    { 0x00, 0x20, 0xA0, 0xC0 },
    { 0x00, 0x20, 0xC0, 0xE0 },
    { 0x00, 0x20, 0xE0, 0x00 },
    { 0xFF, 0x00, 0x00, 0x00 },
};

const SpriteTemplate gPalPadDeleteEffectSpriteTemplate = {
    NULL,
    NULL,
    { 0,    0,    0    },
    { 4096, 4096, 4096 },
    0,
    0,
    NNS_G2D_VRAM_TYPE_2DMAIN,
    HEAP_ID_DEFAULT,
};

const TouchscreenHitbox gPalPadDetailsFrontierHitboxes[11] = {
    { 0x08, 0x28, 0xEC, 0x0C },
    { 0x78, 0x98, 0xEC, 0x0C },
    { 0xA0, 0xC0, 0x00, 0x20 },
    { 0xA0, 0xC0, 0x20, 0x40 },
    { 0xA0, 0xC0, 0x40, 0x60 },
    { 0xA0, 0xC0, 0x60, 0x80 },
    { 0xA0, 0xC0, 0x80, 0xA0 },
    { 0xA0, 0xC0, 0xA0, 0xC0 },
    { 0xA0, 0xC0, 0xC0, 0xE0 },
    { 0xA0, 0xC0, 0xE0, 0x00 },
    { 0xFF, 0x00, 0x00, 0x00 },
};

// clang-format off
const GraphicsBanks gPalPadGraphicsBanks = {
    GX_VRAM_BG_256_AB, GX_VRAM_BGEXTPLTT_NONE, GX_VRAM_SUB_BG_128_C, GX_VRAM_SUB_BGEXTPLTT_NONE,
    GX_VRAM_OBJ_80_EF, GX_VRAM_OBJEXTPLTT_NONE, GX_VRAM_SUB_OBJ_16_I, GX_VRAM_SUB_OBJEXTPLTT_NONE,
    GX_VRAM_TEX_NONE, GX_VRAM_TEXPLTT_NONE,
};
// clang-format on

// C declares this const, but it lives in .data
// clang-format off
const PalPadWindowSpec *gPalPadDetailsPageWindowSpecs[8] = {
    sPalPadDetailsPage0WindowSpecs, sPalPadDetailsPage1WindowSpecs,
    sPalPadDetailsPage2WindowSpecs, sPalPadDetailsPage3WindowSpecs,
    &sPalPadDetailsPage4WindowSpecs, &sPalPadDetailsPage5WindowSpecs,
    &sPalPadDetailsPage6WindowSpecs, &sPalPadDetailsPage7WindowSpecs,
};
// clang-format on

// C declares this const, but it lives in .data
// clang-format off
PalPadDetailsPagePrinter gPalPadDetailsFrontierPagePrinters[8] = {
    (PalPadDetailsPagePrinter)PalPadDetails_PrintUnionRoomPage,
    (PalPadDetailsPagePrinter)PalPadDetails_PrintWiFiPlazaPage,
    (PalPadDetailsPagePrinter)PalPadDetails_PrintBattleTowerPage,
    (PalPadDetailsPagePrinter)PalPadDetails_PrintBattleFactoryPage,
    (PalPadDetailsPagePrinter)PalPadDetails_PrintBattleCastlePage,
    (PalPadDetailsPagePrinter)PalPadDetails_PrintBattleHallPage,
    (PalPadDetailsPagePrinter)PalPadDetails_PrintBattleArcadePage,
    (PalPadDetailsPagePrinter)PalPadDetails_PrintReturnPage,
};
// clang-format on

const TouchscreenHitbox gPalPadDetailsHitboxes[6] = {
    { 0x08, 0x28, 0xEC, 0x0C },
    { 0x78, 0x98, 0xEC, 0x0C },
    { 0xA0, 0xC0, 0x00, 0x70 },
    { 0xA0, 0xC0, 0x70, 0xE0 },
    { 0xA0, 0xC0, 0xE0, 0x00 },
    { 0xFF, 0x00, 0x00, 0x00 },
};

const TouchscreenHitbox gPalPadMenuHitboxes[5] = {
    { 0x22, 0x3E, 0x12, 0xEE },
    { 0x4A, 0x66, 0x12, 0xEE },
    { 0x72, 0x8E, 0x12, 0xEE },
    { 0x9A, 0xB6, 0x12, 0xEE },
    { 0xFF, 0x00, 0x00, 0x00 },
};

// not static: used above its definition
const PalPadWindowSpec sPalPadDetailsPage3WindowSpecs[5] = {
    { 0x02, 0x01, 0x0E, 0x02 },
    { 0x02, 0x04, 0x1A, 0x02 },
    { 0x02, 0x07, 0x1A, 0x04 },
    { 0x02, 0x0C, 0x1A, 0x02 },
    { 0x02, 0x0F, 0x1A, 0x04 },
};

const PalPadPanelLayout gPalPadPanelLayouts[3] = {
    { 0,   0, 0x20, 0x18 },
    { 32,  0, 0x20, 0x18 },
    { -32, 0, 0x20, 0x18 },
};

const ObjCharTransferTemplate gPalPadObjCharTransferTemplate = { 64, 81920, 0, HEAP_ID_DEFAULT };

const u8 gPalPadDetailsTabWidths[2][8] = {
    { 0x0E, 0x0E, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04 },
};

const GraphicsModes gPalPadGraphicsModes = { GX_DISPMODE_GRAPHICS, GX_BGMODE_0, GX_BGMODE_0, GX_BG0_AS_2D };

// not static: used above its definition
const PalPadWindowSpec sPalPadDetailsPage0WindowSpecs[4] = {
    { 0x02, 0x05, 0x10, 0x02 },
    { 0x02, 0x0C, 0x10, 0x02 },
    { 0x13, 0x05, 0x08, 0x05 },
    { 0x17, 0x0C, 0x04, 0x02 },
};

const u8 gPalPadDetailsTabX[2][8] = {
    { 0x00, 0x0E, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x00 },
    { 0x00, 0x04, 0x08, 0x0C, 0x10, 0x14, 0x18, 0x1C },
};

const u32 gPalPadDetailsSlotBaseTiles[3] = { 1, 0x000001F5, 0x000001F5 };
