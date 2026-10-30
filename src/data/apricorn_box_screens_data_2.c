// Converted from asm/apricorn_box_screens_data.s (part 2 of 3) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

#include "global.h"

#include "application/apricorn_box/apricorn_box_screen_internal.h"

#pragma force_active on

// the first 12 bytes are never read
const TouchscreenListMenuTemplate gApricornBoxListMenuTemplates[2] = {
    { 0, 0, 0x02, 0x01, 0x00, 0x00, 0x04, 3,      0x0600, 5      },
    { 1, 1, 0x04, 0x00, 0x0B, 0x00, 0x00, 0x003A, 0x001F, 0x0030 },
};

const u8 gApricornBoxListMenu0Messages[3] __attribute__((aligned(4))) = { 0x02, 0x03, 0x04 };

const u8 gApricornBoxListMenu1Messages[2] = { 0x05, 0x06 };
