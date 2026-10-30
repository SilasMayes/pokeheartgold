// Converted from asm/pokeathlon_disc_catch_cpu_rodata.s by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout. Keep that when editing, or rerun tools/s2c.py.

// The C declarations of these do not match the data (see the notes at each
// definition): keep them out of the way of the definitions below.
#define gPokeathlonDiscCatchCpuHomeRowStarts gPokeathlonDiscCatchCpuHomeRowStarts_header_decl
#define gPokeathlonDiscCatchCpuHomeRowCounts gPokeathlonDiscCatchCpuHomeRowCounts_header_decl

#include "global.h"

#include "pokeathlon/pokeathlon_disc_catch.h"

#pragma force_active on

#undef gPokeathlonDiscCatchCpuHomeRowStarts
#undef gPokeathlonDiscCatchCpuHomeRowCounts

const s16 gPokeathlonDiscCatchCpuHomePositions[POKEATHLON_PARTICIPANTS][POKEATHLON_TEAM_SIZE][2] = {
    { { 40, 40 },  { 40, 88 },  { 40, 152 }  },
    { { 96, 40 },  { 96, 88 },  { 96, 152 }  },
    { { 160, 40 }, { 160, 88 }, { 160, 152 } },
    { { 216, 40 }, { 216, 88 }, { 216, 152 } },
};

const int gPokeathlonDiscCatchCpuJumpChances[POKEATHLON_TEAM_SIZE] = { 3, 6, 36 };

// C declares this as `const u8 gPokeathlonDiscCatchCpuHomeRowCounts[]`, but MWCC gives a char array a
// section of its own, which the linker starts 4-aligned; to stay at offset 0x1 next to its neighbours
// it is written as the only row of a 2-D array, which shares their section.
const u8 gPokeathlonDiscCatchCpuHomeRowCounts[1][7] = {
    { 0x05, 0x07, 0x06, 0x0F, 0x06, 0x00, 0x00 }
};

#ifdef SDK_PORT
// On the DS this label is the first column of {start, count} pairs read at [member * 2], the
// second gPokeathlonDiscCatchCpuHomeRowCounts; the port has a complete copy.
// clang-format off
const u8 gPokeathlonDiscCatchCpuHomeRowStarts[8] = { 3, 5, 7, 6, 0xF, 6, 0, 0 };
// clang-format on
#else
// C declares this as `const u8 gPokeathlonDiscCatchCpuHomeRowStarts[]`, but MWCC gives a char array a
// section of its own, which the linker starts 4-aligned; to stay at offset 0x0 next to its neighbours
// it is written as the only row of a 2-D array, which shares their section.
const u8 gPokeathlonDiscCatchCpuHomeRowStarts[1][1] __attribute__((aligned(4))) = { { 0x03 } };
#endif
