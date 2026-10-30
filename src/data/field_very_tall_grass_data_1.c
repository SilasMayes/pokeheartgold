// Converted from asm/field_very_tall_grass_data.s (part 1 of 2) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

// The C declarations of these do not match the data (see the notes at each
// definition): keep them out of the way of the definitions below.
#define gVeryTallGrassRecordParams gVeryTallGrassRecordParams_header_decl

#include "global.h"

#pragma force_active on

#undef gVeryTallGrassRecordParams

// C declares this as `const struct BillboardSequenceRange gVeryTallGrassRecordParams[2]`, but s2c
// could not read that type (its header needs generated files).
// clang-format off
const u8 gVeryTallGrassRecordParams[24] __attribute__((aligned(4))) = {
    0x00, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
};
// clang-format on
