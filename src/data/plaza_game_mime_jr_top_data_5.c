// Converted from asm/plaza_game_mime_jr_top_data.s (part 5 of 9) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

// The C declarations of these do not match the data (see the notes at each
// definition): keep them out of the way of the definitions below.
#define gMimeJrTopWobbleTiltAxis gMimeJrTopWobbleTiltAxis_header_decl

#include "global.h"

#include "application/plaza_game_mime_jr_top.h"

#pragma force_active on

#undef gMimeJrTopWobbleTiltAxis

// C declares this as `const VecFx32 gMimeJrTopWobbleTiltAxis`, but the label holds 56 more bytes of
// data after it.
// clang-format off
const u8 gMimeJrTopWobbleTiltAxis[68] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x27, 0x00, 0x00, 0x00,
    0x28, 0x00, 0x00, 0x00, 0x29, 0x00, 0x00, 0x00, 0x2A, 0x00, 0x00, 0x00, 0x29, 0x00, 0x00, 0x00,
    0x2A, 0x00, 0x00, 0x00, 0xFE, 0xFF, 0xFE, 0xFF, 0xFE, 0xFF, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0x03, 0x00, 0x03, 0x00, 0x04, 0x00, 0x04, 0x00, 0x06, 0x00, 0x06, 0x00, 0x07, 0x00, 0x07, 0x00,
    0x08, 0x00, 0x08, 0x00,
};
// clang-format on

const VecFx32 gMimeJrTopSettleTiltAxis = { 0, 409600, 0 };

const VecFx32 gMimeJrTopTurnTiltAxis = { 0, 409600, 0 };

const VecFx32 gMimeJrTopSettleTouchTiltAxis = { 0, 409600, 0 };

const VecFx32 gMimeJrTopSpinTiltAxis = { 0, 409600, 0 };
