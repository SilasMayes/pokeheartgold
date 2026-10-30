// Converted from asm/battle_anim_data.s (part 15 of 17) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

#include "global.h"

#include "battle/battle_anim_ball.h"
#include "battle/battle_anim_battler_util.h"
#include "battle/battle_anim_effects.h"
#include "battle/battle_anim_emitter.h"
#include "battle/battle_anim_funcs.h"
#include "battle/battle_anim_internal.h"
#include "battle/battle_anim_move_effects.h"
#include "battle/battle_anim_util.h"

#pragma force_active on

const u32 gBallSpriteResources[28][4] = {
    { 0x00000105, 0x00000053, 0x00000104, 0x00000103 },
    { 0x00000108, 0x00000054, 0x00000107, 0x00000106 },
    { 0x0000010B, 0x00000055, 0x0000010A, 0x00000109 },
    { 0x0000010E, 0x00000056, 0x0000010D, 0x0000010C },
    { 0x00000111, 0x00000057, 0x00000110, 0x0000010F },
    { 0x00000114, 0x00000058, 0x00000113, 0x00000112 },
    { 0x00000117, 0x00000059, 0x00000116, 0x00000115 },
    { 0x0000011A, 0x0000005A, 0x00000119, 0x00000118 },
    { 0x0000011D, 0x0000005B, 0x0000011C, 0x0000011B },
    { 0x00000120, 0x0000005C, 0x0000011F, 0x0000011E },
    { 0x00000123, 0x0000005D, 0x00000122, 0x00000121 },
    { 0x00000126, 0x0000005E, 0x00000125, 0x00000124 },
    { 0x00000129, 0x0000005F, 0x00000128, 0x00000127 },
    { 0x0000012C, 0x00000060, 0x0000012B, 0x0000012A },
    { 0x0000012F, 0x00000061, 0x0000012E, 0x0000012D },
    { 0x00000132, 0x00000062, 0x00000131, 0x00000130 },
    { 0x00000135, 0x00000063, 0x00000134, 0x00000133 },
    { 0x00000138, 0x00000064, 0x00000137, 0x00000136 },
    { 0x0000013B, 0x00000065, 0x0000013A, 0x00000139 },
    { 0x0000013E, 0x00000066, 0x0000013D, 0x0000013C },
    { 0x00000141, 0x00000067, 0x00000140, 0x0000013F },
    { 0x00000144, 0x00000068, 0x00000143, 0x00000142 },
    { 0x00000147, 0x00000069, 0x00000146, 0x00000145 },
    { 0x0000014A, 0x0000006A, 0x00000149, 0x00000148 },
    { 0x0000014D, 0x0000006B, 0x0000014C, 0x0000014B },
    { 0x00000150, 0x0000006C, 0x0000014F, 0x0000014E },
    { 0x00000153, 0x0000006D, 0x00000152, 0x00000151 },
    { 0x00000153, 0x0000006D, 0x00000152, 0x00000151 },
};

const BallAnimBurstParticles gBallAnimBurstParticles[28] = {
    { 0x0000001B, 0,          5 },
    { 0x0000001C, 2,          5 },
    { 0x0000001D, 1,          5 },
    { 0x0000001E, 3,          5 },
    { 0x0000001F, 1,          5 },
    { 0x00000020, 1,          6 },
    { 0x00000021, 1,          5 },
    { 0x00000022, 1,          5 },
    { 0x00000023, 2,          5 },
    { 0x00000024, 3,          7 },
    { 0x00000025, 1,          6 },
    { 0x00000026, 0,          5 },
    { 0x00000027, 1,          5 },
    { 0x00000028, 0,          5 },
    { 0x00000029, 1,          6 },
    { 0x0000002A, 1,          6 },
    { 0x0000002B, 3,          5 },
    { 0x0000002C, 3,          5 },
    { 0x0000002D, 3,          5 },
    { 0x0000002E, 3,          5 },
    { 0x0000002F, 3,          5 },
    { 0x00000030, 3,          5 },
    { 0x00000031, 3,          5 },
    { 0x00000032, 3,          5 },
    { 0x00000033, 3,          5 },
    { 0x0000001B, 0,          5 },
    { 0x0000001B, 0,          5 },
    { 0x00000034, 0x000000FF, 2 },
};

const BallAnimSealParticles gBallAnimSealParticles[28] = {
    { 1,          5 },
    { 2,          4 },
    { 3,          3 },
    { 4,          3 },
    { 5,          3 },
    { 6,          4 },
    { 7,          3 },
    { 8,          4 },
    { 9,          3 },
    { 0x0000000A, 5 },
    { 0x0000000B, 4 },
    { 0x0000000C, 3 },
    { 0x0000000D, 3 },
    { 0x0000000E, 3 },
    { 0x0000000F, 4 },
    { 0x00000010, 4 },
    { 0x00000011, 3 },
    { 0x00000012, 3 },
    { 0x00000013, 3 },
    { 0x00000014, 3 },
    { 0x00000015, 3 },
    { 0x00000016, 3 },
    { 0x00000017, 3 },
    { 0x00000018, 3 },
    { 0x00000019, 3 },
    { 1,          5 },
    { 1,          5 },
    { 0x00000034, 2 },
};

const BallThrowBounceStep gBallThrowBounceSteps[21] = {
    { -7,  1, 1      },
    { -5,  0, 0      },
    { -3,  0, 1      },
    { -2,  0, 1      },
    { 2,   0, 1      },
    { 3,   0, 0      },
    { 5,   0, 1      },
    { 7,   1, 0      },
    { -5,  1, 0      },
    { -3,  0, 1      },
    { -2,  0, 1      },
    { 2,   0, 0      },
    { 3,   0, 0      },
    { 5,   1, 0      },
    { -2,  0, 1      },
    { -1,  0, 0      },
    { 1,   0, 0      },
    { 2,   0, 0      },
    { -2,  1, 0      },
    { 2,   1, 0x00FF },
    { 255, 0, 0      },
};

// MWCC gives a char array a section of its own, which the linker starts 4-aligned; to stay at
// offset 0x1f28 next to its neighbours it is written as the only row of a 2-D array, which shares
// their section.
static const u8 ov07_0223730C[1][2] = {
    { 0x00, 0x00 }
};
