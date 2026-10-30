// Converted from asm/frontier_script_commands_data.s (part 10 of 11) by tools/s2c.py.
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

const BattleHallSetRange gBattleHallGoldMatronSetRange = { 0x0178, 0x01DD };
