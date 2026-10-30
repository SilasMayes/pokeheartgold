// Converted from asm/lock_capsule_card_data.s (part 2 of 2) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

// The C declarations of these do not match the data (see the notes at each
// definition): keep them out of the way of the definitions below.
#define gLockCapsuleCardTextBoxes gLockCapsuleCardTextBoxes_header_decl

#include "global.h"

#include "application/main_menu/lock_capsule_card.h"

#pragma force_active on

#undef gLockCapsuleCardTextBoxes

#pragma explicit_zero_data on
// zero bytes after gLockCapsuleCardTextBoxes in the asm
static u8 gLockCapsuleCardTextBoxes_pad[16] = { 0 };
#pragma explicit_zero_data reset
