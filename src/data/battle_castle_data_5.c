// Converted from asm/battle_castle_data.s (part 5 of 7) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

// The C declarations of these do not match the data (see the notes at each
// definition): keep them out of the way of the definitions below.
#define gBattleCastleOpponentAppCancelHelpMessages gBattleCastleOpponentAppCancelHelpMessages_header_decl

#include "global.h"

#include "frontier/battle_castle.h"

#pragma force_active on

#undef gBattleCastleOpponentAppCancelHelpMessages

// C declares this as `const u16 gBattleCastleOpponentAppCancelHelpMessages[2]`, but the label holds 16
// more bytes of data after it.
// clang-format off
const u8 gBattleCastleOpponentAppCancelHelpMessages[20] = {
    0x29, 0x00, 0x29, 0x00, 0x0C, 0x00, 0x00, 0x00, 0x0D, 0x00, 0x00, 0x00, 0x0E, 0x00, 0x00, 0x00,
    0x0F, 0x00, 0x00, 0x00,
};
// clang-format on

const u16 gBattleCastleOpponentAppMovesHelpMessages[2] = { 0x0026, 0x0026 };

const u16 gBattleCastleOpponentAppRankUpHelpMessages[2] = { 0x0027, 0x0028 };

const u16 gBattleCastleOpponentAppStatsHelpMessages[2] = { 0x0025, 0x0025 };
