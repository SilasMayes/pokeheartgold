// Converted from asm/plaza_game_swalot_plop_data.s (part 3 of 6) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

#include "global.h"

#include "application/plaza_game_swalot_plop.h"

#pragma force_active on

const u16 gSwalotPlopSeatAngles[4][4] = {
    { 0x0300, 0,      0,      0 },
    { 0,      0,      0,      0 },
    { 0,      0x7FFF, 0,      0 },
    { 0,      0x5555, 0xAAAA, 0 },
};
