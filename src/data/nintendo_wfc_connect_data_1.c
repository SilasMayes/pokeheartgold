// Converted from asm/nintendo_wfc_connect_data.s (part 1 of 5) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

// The C declarations of these do not match the data (see the notes at each
// definition): keep them out of the way of the definitions below.
#define gNintendoWfcRoomNumUrl  gNintendoWfcRoomNumUrl_header_decl
#define gNintendoWfcDownloadUrl gNintendoWfcDownloadUrl_header_decl
#define gNintendoWfcUploadUrl   gNintendoWfcUploadUrl_header_decl
#define gNintendoWfcHttp        gNintendoWfcHttp_header_decl

#include "global.h"

#include "nintendo_wfc_connect_internal.h"

#pragma force_active on

#undef gNintendoWfcRoomNumUrl
#undef gNintendoWfcDownloadUrl
#undef gNintendoWfcUploadUrl
#undef gNintendoWfcHttp

// C declares this const, but it lives in .data
char gNintendoWfcRoomNumUrl[76] __attribute__((aligned(4))) = "http://gamestats2.gs.nintendowifi.net/pokemondpds/battletower/roomnum.asp";

// C declares this const, but it lives in .data
char gNintendoWfcDownloadUrl[76] = "http://gamestats2.gs.nintendowifi.net/pokemondpds/battletower/download.asp";

// C declares this const, but it lives in .data
char gNintendoWfcUploadUrl[76] = "http://gamestats2.gs.nintendowifi.net/pokemondpds/battletower/upload.asp";

const u16 gNintendoWfcPadCursorPositions[13][2] = {
    { 0x0020, 0x0051 },
    { 0x0050, 0x0051 },
    { 0x0080, 0x0051 },
    { 0x00AE, 0x0051 },
    { 0x00E0, 0x0051 },
    { 0x0020, 0x0080 },
    { 0x0050, 0x0080 },
    { 0x0080, 0x0080 },
    { 0x00AE, 0x0080 },
    { 0x00E0, 0x0080 },
    { 0x0028, 0x00B0 },
    { 0x0080, 0x00B0 },
    { 0x00D8, 0x00B0 },
};

// clang-format off
const GraphicsBanks gNintendoWfcGraphicsBanks = {
    GX_VRAM_BG_128_A, GX_VRAM_BGEXTPLTT_NONE, GX_VRAM_SUB_BG_128_C, GX_VRAM_SUB_BGEXTPLTT_NONE,
    GX_VRAM_OBJ_64_E, GX_VRAM_OBJEXTPLTT_NONE, GX_VRAM_SUB_OBJ_16_I, GX_VRAM_SUB_OBJEXTPLTT_NONE,
    GX_VRAM_TEX_0_B, GX_VRAM_TEXPLTT_01_FG,
};
// clang-format on

const u16 gNintendoWfcDigitSpritePositions[2][3][2] = {
    { { 0x0060, 0x001D }, { 0x0080, 0x001D }, { 0x00A0, 0x001D } },
    { { 0x0050, 0x001D }, { 0x0070, 0x001D }, { 0x0090, 0x001D } },
};

const ObjCharTransferTemplate gNintendoWfcObjCharTransferTemplate = { 20, 2048, 2048, HEAP_ID_67 };

// clang-format off
const GraphicsModes gNintendoWfcGraphicsModes = {
    GX_DISPMODE_GRAPHICS, GX_BGMODE_0, GX_BGMODE_0, GX_BG0_AS_2D,
};
// clang-format on

const u16 gNintendoWfcButtonSpritePositions[3][2] = {
    { 0x0028, 0x00B0 },
    { 0x0080, 0x00B0 },
    { 0x00D8, 0x00B0 },
};

// clang-format off
static const u8 gNintendoWfcUnusedWindowTemplate[8] __attribute__((aligned(4))) = {
    0x00, 0x17, 0x0D, 0x07, 0x04, 0x0D, 0x00, 0x00,
};
// clang-format on

// C declares this as `NintendoWfcHttp gNintendoWfcHttp`, but it has 64-bit members, whose layout MWCC
// and GCC may not agree on.
u8 gNintendoWfcHttp[12] __attribute__((aligned(4)));
