// Converted from asm/battle_castle_data.s (part 2 of 7) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

// The C declarations of these do not match the data (see the notes at each
// definition): keep them out of the way of the definitions below.
#define gBattleCastlePartyAppRankUpCosts gBattleCastlePartyAppRankUpCosts_header_decl

#include "global.h"

#include "frontier/battle_castle.h"

#pragma force_active on

#undef gBattleCastlePartyAppRankUpCosts

// Also holds the asm labels gBattleCastlePartyAppRankUpMessages (+0x12). MWCC sorts a file's
// objects by size and the linker starts every section 4-aligned, so no arrangement of separate
// objects puts them where the asm has them; the code has to reach them through
// gBattleCastlePartyAppRankUpCosts.
// C declares this as `const u16 gBattleCastlePartyAppRankUpCosts[2][3]`, but that type does not
// describe the data.
// clang-format off
const u8 gBattleCastlePartyAppRankUpCosts[36] = {
    0x00, 0x00, 0x64, 0x00, 0x64, 0x00, 0x00, 0x00, 0x64, 0x00, 0x96, 0x00, 0x00, 0x00, 0x32, 0x00,
    0x32, 0x00, 0x00, 0x00, 0x2A, 0x00, 0x2B, 0x00, 0x00, 0x00, 0x44, 0x00, 0x45, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
};
// clang-format on

// clang-format off
const GraphicsModes gBattleCastlePartyAppGraphicsModes = {
    GX_DISPMODE_GRAPHICS, GX_BGMODE_0, GX_BGMODE_0, GX_BG0_AS_2D,
};
// clang-format on
