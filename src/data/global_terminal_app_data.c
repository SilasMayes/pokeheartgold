// Converted from asm/global_terminal_app_data.s by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout. Keep that when editing, or rerun tools/s2c.py.

#include "global.h"

// Nothing uses these: the linker drops them, as it dropped their asm section.

u8 _021D1108[4] __attribute__((aligned(4)));
