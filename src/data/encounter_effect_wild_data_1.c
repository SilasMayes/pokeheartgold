// Converted from asm/encounter_effect_wild_data.s (part 1 of 3) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

#include "global.h"

#include "field/encounter_effect.h"

#pragma force_active on

// clang-format off
static const u8 _0226019C[32] __attribute__((aligned(4))) = {
    0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00,
    0x75, 0x31, 0x4C, 0x4D, 0x47, 0x82, 0x7B, 0x9F, 0x9D, 0x81, 0x9B, 0x4A, 0x75, 0x31, 0xFF, 0xFF,
};
// clang-format on
