// Converted from asm/palpad_data.s (part 4 of 5) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

#include "global.h"

#include "application/palpad/palpad_internal.h"

#pragma force_active on

SpriteTemplate gPalPadCursorSpriteTemplate = {
    NULL,
    NULL,
    { 0,    0,    0    },
    { 4096, 4096, 4096 },
    0,
    9,
    NNS_G2D_VRAM_TYPE_2DMAIN,
    HEAP_ID_DEFAULT,
};
