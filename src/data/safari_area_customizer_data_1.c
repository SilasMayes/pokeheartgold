// Converted from asm/safari_area_customizer_data.s (part 1 of 3) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

// The C declarations of these do not match the data (see the notes at each
// definition): keep them out of the way of the definitions below.
#define gSafariAreaCustomizerLabelColors gSafariAreaCustomizerLabelColors_header_decl

#include "global.h"

#pragma force_active on

#undef gSafariAreaCustomizerLabelColors

// The label holds 12 more bytes of data after it.
// clang-format off
const u8 gSafariAreaCustomizerLabelColors[20] = {
    0x08, 0x0A, 0x0B, 0x00, 0x09, 0x0A, 0x0B, 0x00, 0x03, 0x00, 0x00, 0x0F, 0x00, 0x00, 0xB5, 0x03,
    0xE5, 0x03, 0x30, 0x00,
};
// clang-format on

const u8 gSafariAreaCustomizerConsts[4] __attribute__((aligned(4))) = { 0xFF, 0x01, 0x01, 0xFF };
