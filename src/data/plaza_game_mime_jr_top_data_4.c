// Converted from asm/plaza_game_mime_jr_top_data.s (part 4 of 9) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

#include "global.h"

#include "application/plaza_game_mime_jr_top.h"

#pragma force_active on

// One object: in the asm gMimeJrTopTouchData labelled only its first 8 bytes and the rest was
// gMimeJrTopSelectionHitboxes, now a macro for gMimeJrTopTouchData.selectionHitboxes.
const MimeJrTopTouchData gMimeJrTopTouchData = {
    .hitboxes = {
        { .circle = { 0xFE, 0x80, 0x80, 0x30 } },
        { .rect = { 0xFF, 0x00, 0x00, 0x00 } },
    },
    .selectionHitboxes = {
        { .circle = { 0xFE, 0x80, 0x80, 0x40 } },
        { .rect = { 0xFF, 0x00, 0x00, 0x00 } },
    },
    .tierScores = { { 1, 2, 3, 4 } },
    .tierBonus = { { 700, 1400, 2100, 2800 } },
    .wobbleIntervals = { { 120, 90, 60, 45 } },
};
