// Converted from asm/battle_castle_data.s (part 1 of 7) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

#include "global.h"

#include "frontier/battle_castle.h"

#pragma force_active on

const u16 gBattleCastlePartyAppItemCounts[10] = { 0x000C, 0x000C, 0x001B, 3, 0x0B00, 0, 0, 0, 0, 0 };

const u16 gBattleCastlePartyAppHealCosts[3] = { 0x000A, 8, 0x000C };

const u16 gBattleCastlePartyAppBerryCounts[3] = { 8, 8, 0x0020 };

const u16 gBattleCastlePartyAppMainMenuHelpMessages[3] = { 0x000E, 0x000F, 0x0012 };

const u16 gBattleCastlePartyAppHealMessages[3] __attribute__((aligned(4))) = { 0x0022, 0x0023, 0x0024 };
