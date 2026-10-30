// Converted from asm/plaza_game_mime_jr_top_data.s (part 6 of 9) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

// The C declarations of these do not match the data (see the notes at each
// definition): keep them out of the way of the definitions below.
#define gMimeJrTopTierModels gMimeJrTopTierModels_header_decl

#include "global.h"

#include "application/plaza_game_mime_jr_top.h"

#pragma force_active on

#undef gMimeJrTopTierModels

const int gMimeJrTopTierChangeModels[22][2] = {
    { 32,       33      },
    { 34,       35      },
    { 36,       37      },
    { 38,       37      },
    { 38,       -65538  },
    { -1,       -1      },
    { 131310,   131074  },
    { 262146,   262148  },
    { 393220,   393222  },
    { 16711686, 0       },
    { 0,        0       },
    { 238,      262144  },
    { 262148,   262148  },
    { 0,        0       },
    { 16711680, -131075 },
    { -65538,   -1      },
    { 65774,    131073  },
    { 196610,   3       },
    { 0,        0       },
    { 0,        0       },
    { 0,        0       },
    { 0,        255     },
};

#ifdef SDK_PORT
// On the DS the tier models are pairs {model, change model}, this label the first column; the
// port has a complete copy.
// clang-format off
const int gMimeJrTopTierModels[5][2] = { { 0x1F, 0x20 }, { 0x21, 0x22 }, { 0x23, 0x24 }, { 0x25, 0x26 }, { 0x25, 0x26 } };
// clang-format on
#else
// C declares this as `const int gMimeJrTopTierModels[][2]`, but one element of that type is larger
// than the data under this label.
const u8 gMimeJrTopTierModels[4] = { 0x1F, 0x00, 0x00, 0x00 };
#endif
