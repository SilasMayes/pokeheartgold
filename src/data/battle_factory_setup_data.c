// Converted from asm/battle_factory_setup_data.s by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout. Keep that when editing, or rerun tools/s2c.py.

#include "global.h"

#include "frontier/battle_factory_setup.h"

#pragma force_active on

#pragma explicit_zero_data on
const BattleFactorySetRange *gBattleFactoryTrainerSetRanges = NULL;
#pragma explicit_zero_data reset

#pragma explicit_zero_data on
// zero bytes after gBattleFactoryTrainerSetRanges in the asm
static u8 gBattleFactoryTrainerSetRanges_pad[4] = { 0 };
#pragma explicit_zero_data reset
