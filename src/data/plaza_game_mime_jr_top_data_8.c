// Converted from asm/plaza_game_mime_jr_top_data.s (part 8 of 9) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

#include "global.h"

#include "application/plaza_game_mime_jr_top.h"

#pragma force_active on

const MimeJrTopOffsets gMimeJrTopBurstOffsetsX = {
    { -20480, 12288, 16384, -12288, 12288, -8192 }
};

const MimeJrTopOffsets gMimeJrTopBurstOffsetsY = {
    { 16384, 20480, -16384, -20480, -12288, 8192 }
};

const MimeJrTopStarOrigins gMimeJrTopStarOrigins = {
    { 96, 58, 230, 48, 128, 32, 40, 64, 180, 48 }
};

const MimeJrTopDoneFlags gMimeJrTopDance3DoneFlags = {
    { 1, 1, 1, 1 }
};

const MimeJrTopDoneFlags gMimeJrTopDance4DoneFlags = {
    { 1, 1, 1, 1 }
};

const MimeJrTopDoneFlags gMimeJrTopDance2DoneFlags = {
    { 1, 1, 1, 1 }
};

const MimeJrTopDoneFlags gMimeJrTopDance5DoneFlags = {
    { 1, 1, 1, 1 }
};

const MimeJrTopDoneFlags gMimeJrTopPopupDoneFlags = {
    { 1, 1, 1, 1 }
};

const u16 gMimeJrTopPopupLimits[4] = { 0x00BC, 0x00BC, 0x00B4, 0x00B4 };
