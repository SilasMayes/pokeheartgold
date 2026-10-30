// Converted from asm/plaza_game_data.s (part 1 of 4) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

#include "global.h"

#include "application/plaza_game.h"

#pragma force_active on

// clang-format off
const GraphicsModes gPlazaGameResultsGraphicsModes = {
    GX_DISPMODE_GRAPHICS, GX_BGMODE_0, GX_BGMODE_0, GX_BG0_AS_2D,
};
// clang-format on

const fx32 gPlazaGameTitleSlideOutEndX[3] = { 819200, -819200, -655360 };

const fx32 gPlazaGameTitleBounceOutVelocity[3] = { -36864, 36864, 32768 };

const fx32 gPlazaGameTitleSlideOutVelocity[3] = { 0, 0, 0 };

const fx32 gPlazaGameTitleSlideInVelocity[3] = { 0, 0, 0 };

const fx32 gPlazaGameTitleRestX[3] = { 0, 0, 0 };

const fx32 gPlazaGameTitleBounceX[3] = { -73728, 73728, 65536 };

const fx32 gPlazaGameTitleBounceBackVelocity[3] = { 0, 0, 0 };

const fx32 gPlazaGameTitleSlideInStartX[3] = { -819200, 819200, 655360 };

const u32 gPlazaGameTitleColors[3] = { 0x00070809, 0x00040506, 0x00010203 };

const s16 gPlazaGameResultsRankOffsets[4] = { 0, -10, -16, -24 };

const u8 gPlazaGameWobbuffetPopSelectionWeights[4] = { 0x55, 0x0F, 0x00, 0x00 };

const u8 gPlazaGameSwalotPlopSelectionWeights[4] = { 0x4B, 0x0F, 0x0A, 0x00 };

const u8 gPlazaGameMimeJrTopSelectionWeights[4] __attribute__((aligned(4))) = { 0x55, 0x0F, 0x00, 0x00 };

const u8 gPlazaGameResultsFlashSlots[4] = { 0x00, 0x01, 0x03, 0x02 };
