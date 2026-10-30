// Converted from asm/global_terminal_data.s (part 2 of 2) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

#include "global.h"

#pragma force_active on

// not referenced by any code
// clang-format off
static const u32 sGlobalTerminalUnusedTable[12] = {
    5, 3, 2, 4,
    1, 6, 9, 2,
    7, 8, 6, 3,
};
// clang-format on
