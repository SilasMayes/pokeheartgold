// Converted from asm/plaza_game_mime_jr_top_data.s (part 2 of 9) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

// The C declarations of these do not match the data (see the notes at each
// definition): keep them out of the way of the definitions below.
#define gMimeJrTopRivalAnims gMimeJrTopRivalAnims_header_decl

#include "global.h"

#include "application/plaza_game_mime_jr_top.h"

#pragma force_active on

#undef gMimeJrTopRivalAnims

// C declares this as `const MimeJrTopRivalAnims gMimeJrTopRivalAnims`, but the label holds 32 more
// bytes of data after it.
// clang-format off
const u8 gMimeJrTopRivalAnims[64] = {
    0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
};
// clang-format on

const s16 gMimeJrTopRivalSpriteX[4][3] = {
    { 0,   0,   0   },
    { 128, 0,   0   },
    { 85,  170, 0   },
    { 64,  128, 192 }
};

const VecFx32 gMimeJrTopCameraPosition = { 0, 0, 655360 };

const VecFx32 gMimeJrTopLightVector = { 0, -4096, -4096 };

const u16 gMimeJrTopPopupPositions[4] = { 0x0048, 0x00B4, 0x0018, 0x00E8 };
