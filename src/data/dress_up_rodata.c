// Converted from asm/dress_up_rodata.s by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout. Keep that when editing, or rerun tools/s2c.py.

#include "global.h"

#include "application/dress_up/dress_up_internal.h"

#pragma force_active on

const u8 gDressUpKeyPressTouchStates[2] __attribute__((aligned(4))) = { 0x02, 0x01 };
