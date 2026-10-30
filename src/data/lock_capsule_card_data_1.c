// Converted from asm/lock_capsule_card_data.s (part 1 of 2) by tools/s2c.py.
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

// page, x, y, width, height, font, colour, fill, message, print function, text x, text y
// 16 zero bytes nothing references
// C declares this const, but it lives in .data
WonderCardTextBox gLockCapsuleCardTextBoxes[11] = {
    {
     0,
     2,
     2,
     0xC,
     2,
     1,
     0x00010200,
     0xFFFFFFFF,
     0x25,
     (WonderCardTextBoxFunc)LockCapsuleCard_PrintMessageOnly,
     0,
     0,
     },
    {
     0,
     6,
     0x11,
     0xB,
     2,
     1,
     0x000F0200,
     0xFFFFFFFF,
     0x29,
     (WonderCardTextBoxFunc)LockCapsuleCard_PrintMessageOnly,
     0,
     0,
     },
    {
     0,
     2,
     9,
     0x1C,
     4,
     1,
     0x00010200,
     0xFFFFFFFF,
     0,
     (WonderCardTextBoxFunc)LockCapsuleCard_PrintStatus,
     0,
     0,
     },
    {
     0,
     2,
     6,
     0x1C,
     2,
     1,
     0x000F0200,
     0xFFFFFFFF,
     0,
     (WonderCardTextBoxFunc)LockCapsuleCard_PrintCardTitle,
     0,
     0,
     },
    {
     0,
     0x12,
     0x11,
     0xB,
     2,
     1,
     0x00010200,
     0xFFFFFFFF,
     0x32,
     (WonderCardTextBoxFunc)LockCapsuleCard_BufferReceiveDate,
     0,
     0,
     },
    {
     1,
     2,
     3,
     0x1C,
     0xA,
     1,
     0x00010200,
     0xFFFFFFFF,
     0,
     (WonderCardTextBoxFunc)LockCapsuleCard_PrintCardText,
     0,
     0,
     },
    {
     1,
     2,
     0xE,
     0x1C,
     4,
     1,
     0x00010200,
     0xFFFFFFFF,
     0x2A,
     (WonderCardTextBoxFunc)LockCapsuleCard_PrintNothing,
     0,
     0,
     },
    {
     2,
     2,
     0x13,
     0x1B,
     4,
     1,
     0x00010200,
     0xF,
     0x25,
     (WonderCardTextBoxFunc)LockCapsuleCard_PrintMessageOnly,
     0,
     0,
     },
    { 2, 0x12, 9, 0xC, 4, 1, 0x00010200, 5, 0, (WonderCardTextBoxFunc)LockCapsuleCard_ShowCardMenu, 0, 0 },
    { 2, 0x18, 0xD, 6, 4, 1, 0x00010200, 5, 0, NULL, 0, 0 },
    { 2, 0x18, 0xD, 6, 4, 1, 0x00010200, 5, 0, NULL, 0, 0 },
};
