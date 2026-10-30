// Converted from asm/dowsing_mchn_data.s (part 4 of 4) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

#include "global.h"

#pragma force_active on

const u8 gDowsingMchnActionTypeToWindow[8] = { 0x00, 0x01, 0x00, 0x02, 0x03, 0x00, 0x00, 0x00 };

const u8 gDowsingMchnLevelSignalGains[8] = { 0x01, 0x02, 0x02, 0x02, 0x04, 0x00, 0x00, 0x00 };
