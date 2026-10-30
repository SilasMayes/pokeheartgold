// Converted from asm/frontier_script_commands_data.s (part 2 of 11) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

#include "global.h"

#include "frontier/battle_factory_setup.h"
#include "frontier/battle_hall_setup.h"
#include "frontier/battle_tower_setup.h"
#include "frontier/frontier_link_lobby.h"

#include "frontier_script_commands_misc_internal.h"

#pragma force_active on

const u8 gBattleArcadeFaintedMonPoints[8] = { 0x06, 0x04, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00 };

const u8 gBattleArcadeStatusedMonPoints[8] = { 0x08, 0x06, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00 };
