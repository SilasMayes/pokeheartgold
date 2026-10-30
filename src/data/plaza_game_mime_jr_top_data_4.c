// Converted from asm/plaza_game_mime_jr_top_data.s (part 4 of 9) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

// The C declarations of these do not match the data (see the notes at each
// definition): keep them out of the way of the definitions below.
#define gMimeJrTopTouchData gMimeJrTopTouchData_header_decl

#include "global.h"

#include "application/plaza_game_mime_jr_top.h"

#pragma force_active on

#undef gMimeJrTopTouchData

const TouchscreenHitbox gMimeJrTopSelectionHitboxes[8] = {
    { 0xFE, 0x80, 0x80, 0x40 },
    { 0xFF, 0x00, 0x00, 0x00 },
    { 0x01, 0x00, 0x02, 0x00 },
    { 0x03, 0x00, 0x04, 0x00 },
    { 0xBC, 0x02, 0x78, 0x05 },
    { 0x34, 0x08, 0xF0, 0x0A },
    { 0x78, 0x00, 0x5A, 0x00 },
    { 0x3C, 0x00, 0x2D, 0x00 },
};

// C declares this as `const MimeJrTopTouchData gMimeJrTopTouchData`, but that type is 0x28 bytes and
// the label covers only 0x8 (later labels overlap it).
const u8 gMimeJrTopTouchData[8] = { 0xFE, 0x80, 0x80, 0x30, 0xFF, 0x00, 0x00, 0x00 };
