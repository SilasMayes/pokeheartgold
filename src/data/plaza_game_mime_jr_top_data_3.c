// Converted from asm/plaza_game_mime_jr_top_data.s (part 3 of 9) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

#include "global.h"

#include "application/plaza_game_mime_jr_top.h"

#pragma force_active on

const s16 gMimeJrTopRivalNamePositions[3][3][4] = {
    { { 12, 8, 8, 2 }, { 0, 0, 0, 0 },  { 0, 0, 0, 0 }  },
    { { 5, 8, 8, 2 },  { 19, 8, 8, 2 }, { 0, 0, 0, 0 }  },
    { { 1, 8, 8, 2 },  { 12, 8, 8, 2 }, { 23, 8, 8, 2 } },
};

const MimeJrTopRivalAnims gMimeJrTopRivalSetAnims = {
    { { 0, 2 }, { 0, 3 }, { 0, 4 }, { 1, 2 } }
};
