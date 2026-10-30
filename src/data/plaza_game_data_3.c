// Converted from asm/plaza_game_data.s (part 3 of 4) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

// The C declarations of these do not match the data (see the notes at each
// definition): keep them out of the way of the definitions below.
#define gPlazaGameSeatRowsByCount   gPlazaGameSeatRowsByCount_header_decl
#define gPlazaGameScreenRowsByCount gPlazaGameScreenRowsByCount_header_decl
#define gPlazaGameSeatAnimsByCount  gPlazaGameSeatAnimsByCount_header_decl
#define gPlazaGameSeatRows          gPlazaGameSeatRows_header_decl
#define gPlazaGameSeatAnims         gPlazaGameSeatAnims_header_decl

#include "global.h"

#include "application/plaza_game.h"

#pragma force_active on

#undef gPlazaGameSeatRowsByCount
#undef gPlazaGameScreenRowsByCount
#undef gPlazaGameSeatAnimsByCount
#undef gPlazaGameSeatRows
#undef gPlazaGameSeatAnims

const PlazaGameBgTemplate gPlazaGameResultsBgTemplates[6] = {
    { 3, { 0, 0, 0x00000800, 0, 0x01, 0x00, 0x1D, 0x00, 0x00, 0x03, 0x00, 0x00, 0 } },
    { 1, { 0, 0, 0x00001000, 0, 0x03, 0x00, 0x1B, 0x00, 0x00, 0x02, 0x00, 0x00, 0 } },
    { 2, { 0, 0, 0x00000800, 0, 0x01, 0x00, 0x1A, 0x04, 0x00, 0x00, 0x00, 0x00, 0 } },
    { 0, { 0, 0, 0x00001000, 0, 0x03, 0x00, 0x18, 0x00, 0x00, 0x01, 0x00, 0x00, 0 } },
    { 4, { 0, 0, 0x00000800, 0, 0x01, 0x00, 0x0F, 0x01, 0x00, 0x00, 0x00, 0x00, 0 } },
    { 5, { 0, 0, 0x00000800, 0, 0x01, 0x00, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x00, 0 } },
};

const PlazaGameBgTemplate gPlazaGameEntryBgTemplates[5] = {
    { 3, { 0, 0, 0x00000800, 0, 0x01, 0x00, 0x1D, 0x04, 0x00, 0x03, 0x00, 0x00, 0 } },
    { 1, { 0, 0, 0x00002000, 0, 0x04, 0x00, 0x19, 0x04, 0x00, 0x01, 0x00, 0x00, 0 } },
    { 2, { 0, 0, 0x00000800, 0, 0x01, 0x00, 0x18, 0x06, 0x00, 0x00, 0x00, 0x00, 0 } },
    { 0, { 0, 0, 0x00002000, 0, 0x04, 0x00, 0x14, 0x00, 0x00, 0x02, 0x00, 0x00, 0 } },
    { 4, { 0, 0, 0x00000800, 0, 0x01, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0 } },
};

const u16 gPlazaGameAltMessages[20][2] = {
    { 0,      0      },
    { 1,      1      },
    { 2,      0x0014 },
    { 3,      3      },
    { 4,      4      },
    { 5,      5      },
    { 6,      6      },
    { 7,      7      },
    { 8,      8      },
    { 9,      9      },
    { 0x000A, 0x0015 },
    { 0x000B, 0x000B },
    { 0x000C, 0x000C },
    { 0x000D, 0x000D },
    { 0x000E, 0x000E },
    { 0x000F, 0x000F },
    { 0x0010, 0x0010 },
    { 0x0011, 0x0016 },
    { 0x0012, 0x0017 },
    { 0x0013, 0x0013 },
};

// C declares this as `const u8 gPlazaGameSeatAnims[][12]`, but the label holds 4 more bytes of data
// after it.
// clang-format off
const u8 gPlazaGameSeatAnims[40] = {
    0x00, 0x00, 0x00, 0x00, 0x0E, 0x04, 0x00, 0x00, 0x12, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00,
    0x0E, 0x08, 0x02, 0x00, 0x12, 0x00, 0x06, 0x00, 0x00, 0x02, 0x01, 0x00, 0x12, 0x0C, 0x00, 0x06,
    0x12, 0x00, 0x06, 0x0C, 0x00, 0x02, 0x03, 0x01,
};
// clang-format on

// C declares this as `const u8 gPlazaGameSeatRows[][12]`, but one element of that type is larger than
// the data under this label.
const u8 gPlazaGameSeatRows[8] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

// C declares this as `const u8 gPlazaGameScreenRowsByCount[][12]`, but one element of that type is
// larger than the data under this label.
const u8 gPlazaGameScreenRowsByCount[4] = { 0x00, 0x00, 0x00, 0x00 };

// C declares this as `const u8 gPlazaGameSeatAnimsByCount[][12]`, but one element of that type is
// larger than the data under this label.
const u8 gPlazaGameSeatAnimsByCount[4] = { 0x00, 0x00, 0x00, 0x00 };

// C declares this as `const u8 gPlazaGameSeatRowsByCount[][12]`, but one element of that type is
// larger than the data under this label.
const u8 gPlazaGameSeatRowsByCount[4] = { 0x00, 0x00, 0x00, 0x00 };
