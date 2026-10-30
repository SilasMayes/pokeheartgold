// Converted from asm/pokedex_rodata.s (part 1 of 5) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

#include "global.h"

#include "application/pokedex/pokedex_internal.h"

#pragma force_active on

// clang-format off
const u8 gPokedexScrollbarLengths[24] = {
    0x56, 0x4E, 0x46, 0x3E, 0x36, 0x2E, 0x26, 0x1E, 0x16, 0x00, 0x00, 0x00, 0x6E, 0x66, 0x5E, 0x56, 0x4E,
    0x46, 0x3E, 0x36, 0x2E, 0x26, 0x1E, 0x16,
};
// clang-format on

// clang-format off
const u8 gPokedexAreaScrollbarLengths[12] __attribute__((aligned(4))) = {
    0x56, 0x4E, 0x46, 0x3E, 0x36, 0x2E, 0x26, 0x1E, 0x16, 0x00, 0x00, 0x00,
};
// clang-format on
