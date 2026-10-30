// Converted from asm/plaza_game_data.s (part 2 of 4) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

// The C declarations of these do not match the data (see the notes at each
// definition): keep them out of the way of the definitions below.
#define gPlazaGameResultsBanks gPlazaGameResultsBanks_header_decl

#include "global.h"

#include "application/plaza_game.h"

#pragma force_active on

#undef gPlazaGameResultsBanks

// clang-format off
const GraphicsBanks gPlazaGameEntryBanks = {
    GX_VRAM_BG_256_AB, GX_VRAM_BGEXTPLTT_NONE, GX_VRAM_SUB_BG_32_H, GX_VRAM_SUB_BGEXTPLTT_NONE,
    GX_VRAM_OBJ_16_G, GX_VRAM_OBJEXTPLTT_NONE, GX_VRAM_SUB_OBJ_16_I, GX_VRAM_SUB_OBJEXTPLTT_NONE,
    GX_VRAM_TEX_NONE, GX_VRAM_TEXPLTT_NONE,
};
// clang-format on

// C declares this as `const GraphicsBanks gPlazaGameResultsBanks`, but that type is 0x28 bytes and the
// label covers only 0x1c (later labels overlap it).
// clang-format off
const u8 gPlazaGameResultsBanks[28] = {
    0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00,
};
// clang-format on

const VecFx32 gPlazaGameSignWindowSpritePositions[2] = {
    { 524288, 393216, 0 },
    { 524288, 401408, 0 }
};

const ObjCharTransferTemplate gPlazaGameObjCharTransfer = { 0, 16384, 16384, HEAP_ID_DEFAULT };

// clang-format off
const GraphicsModes gPlazaGameEntryGraphicsModes = {
    GX_DISPMODE_GRAPHICS, GX_BGMODE_0, GX_BGMODE_0, GX_BG0_AS_2D,
};
// clang-format on

const u8 gPlazaGameSeatOrders[4][4] = {
    { 0x00, 0x00, 0x00, 0x00 },
    { 0x00, 0x01, 0x00, 0x00 },
    { 0x00, 0x02, 0x01, 0x00 },
    { 0x00, 0x03, 0x01, 0x02 },
};

const s16 gPlazaGamePlayerSpriteY[7] = { 44, 236, 24, 4, 24, 128, 4 };

const s16 gPlazaGamePlayerSpritePositions[1] = { 128 };
