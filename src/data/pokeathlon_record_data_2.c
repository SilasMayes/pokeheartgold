// Converted from asm/pokeathlon_record_data.s (part 2 of 4) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

// The C declarations of these do not match the data (see the notes at each
// definition): keep them out of the way of the definitions below.
#define sStr_SeqError_4 sStr_SeqError_4_header_decl

#include "global.h"

#include "pokeathlon/pokeathlon_record_screens.h"

#pragma force_active on

#undef sStr_SeqError_4

const int gPokeathlonEventRecordMonIconResIds[4] = { 2, 2, 2, 2 };

// clang-format off
const GraphicsModes gPokeathlonEventRecordGraphicsModes = {
    GX_DISPMODE_GRAPHICS, GX_BGMODE_0, GX_BGMODE_0, GX_BG0_AS_2D,
};
// clang-format on

// C declares this const, but it lives in .data
char sStr_SeqError_4[11] = "seq error!";

const PokeathlonEventRecordDefaultEntry gPokeathlonEventRecordDefaultEntry = {
    0x003C,
    0x002C,
    { { 0x0098, 0x009B, 0x009E } },
};

const u8 gPokeathlonEventRecordWindowY[5][2] = {
    { 0x04, 0x06 },
    { 0x09, 0x0A },
    { 0x0D, 0x0E },
    { 0x11, 0x12 },
    { 0x15, 0x16 },
};

const u8 gPokeathlonMedalsBgLayers[7] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06 };
