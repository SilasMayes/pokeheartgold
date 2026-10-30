// Converted from asm/battle_castle_data.s (part 4 of 7) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

#include "global.h"

#include "frontier/battle_castle.h"

#pragma force_active on

// clang-format off
const TouchscreenListMenuTemplate gBattleCastleOpponentAppListMenuTemplate = {
    1, 1, 0x00, 0x00, 0x0B, 0x00, 0x00, 0, 0, 0,
};
// clang-format on

const u8 gBattleCastlePartyAppListMenuY[8] = { 0x12, 0x0E, 0x0B, 0x08, 0x05, 0x02, 0x00, 0x00 };

const u8 gBattleCastleOpponentAppListMenuY[8] = { 0x12, 0x0E, 0x0B, 0x08, 0x05, 0x02, 0x00, 0x00 };
