// Converted from asm/pokeathlon_goal_roll_cpu_rodata.s by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout. Keep that when editing, or rerun tools/s2c.py.

// The C declarations of these do not match the data (see the notes at each
// definition): keep them out of the way of the definitions below.
#define gPokeathlonGoalRollCpuGuardPoints  gPokeathlonGoalRollCpuGuardPoints_header_decl
#define gPokeathlonGoalRollCpuGuardPointsY gPokeathlonGoalRollCpuGuardPointsY_header_decl
#define gPokeathlonGoalRollCpuGuardPoints1 gPokeathlonGoalRollCpuGuardPoints1_header_decl
#define gPokeathlonGoalRollCpuGuardPoints2 gPokeathlonGoalRollCpuGuardPoints2_header_decl

#include "global.h"

#include "pokeathlon/pokeathlon_goal_roll.h"

#pragma force_active on

#undef gPokeathlonGoalRollCpuGuardPoints
#undef gPokeathlonGoalRollCpuGuardPointsY
#undef gPokeathlonGoalRollCpuGuardPoints1
#undef gPokeathlonGoalRollCpuGuardPoints2

// C declares this as `const u16 gPokeathlonGoalRollCpuGuardPoints2[][3][2]`, but the label holds 4
// more bytes of data after it.
// clang-format off
const u8 gPokeathlonGoalRollCpuGuardPoints2[28] = {
    0xE0, 0x00, 0x58, 0x00, 0x30, 0x00, 0x90, 0x00, 0x48, 0x00, 0xA0, 0x00, 0x20, 0x00, 0x78, 0x00,
    0xD0, 0x00, 0x90, 0x00, 0xB8, 0x00, 0xA0, 0x00, 0xE0, 0x00, 0x78, 0x00,
};
// clang-format on

// C declares this as `const u16 gPokeathlonGoalRollCpuGuardPoints1[][3][2]`, but one element of that
// type is larger than the data under this label.
const u8 gPokeathlonGoalRollCpuGuardPoints1[4] = { 0xB8, 0x00, 0x30, 0x00 };

// C declares this as `const u16 gPokeathlonGoalRollCpuGuardPointsY[][3][2]`, but MWCC gives a char
// array a section of its own, which the linker starts 4-aligned; to stay at offset 0x2 next to its
// neighbours it is written as the only row of a 2-D array, which shares their section.
const u8 gPokeathlonGoalRollCpuGuardPointsY[1][2] = {
    { 0x40, 0x00 }
};

// C declares this as `const u16 gPokeathlonGoalRollCpuGuardPoints[][3][2]`, but MWCC gives a char
// array a section of its own, which the linker starts 4-aligned; to stay at offset 0x0 next to its
// neighbours it is written as the only row of a 2-D array, which shares their section.
const u8 gPokeathlonGoalRollCpuGuardPoints[1][2] __attribute__((aligned(4))) = {
    { 0xD0, 0x00 }
};
