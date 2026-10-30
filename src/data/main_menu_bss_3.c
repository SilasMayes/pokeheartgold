// Converted from asm/main_menu_bss.s (part 3 of 3) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

#include "global.h"

#include "application/main_menu/main_menu_util.h"
#include "application/main_menu/migrate_from_agb.h"

#pragma force_active on

enum HeapID gMainMenuUtilCryptoHeapId;
