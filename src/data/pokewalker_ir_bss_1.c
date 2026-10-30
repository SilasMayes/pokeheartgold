// Converted from asm/pokewalker_ir_bss.s (part 1 of 2) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

#include "global.h"

#include "application/pokewalker/pokewalker_ir_internal.h"

#pragma force_active on

PokewalkerIrLink gPokewalkerIrLink;
