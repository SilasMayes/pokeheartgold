// Converted from asm/battle_controller_opponent_data.s (part 1 of 2) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

// The C declarations of these do not match the data (see the notes at each
// definition): keep them out of the way of the definitions below.
#define gSafariFleeRates gSafariFleeRates_header_decl

#include "global.h"

#include "constants/pokemon.h"
#include "constants/sndseq.h"

#pragma force_active on

#undef gSafariFleeRates

// 0x0226D1E8
const s16 gBallThrowOffsets[15][6][2] = {
    { { 0, 128 }, { -34, 4 },  { -28, -11 }, { 50, -12 }, { 32767, 32767 }, { 32767, 32767 } },
    { { 0, 128 }, { -34, 4 },  { -28, -11 }, { 50, -12 }, { 50, -12 },      { 32767, 32767 } },
    { { 0, 128 }, { -34, 4 },  { -28, -11 }, { 50, -12 }, { 32767, 32767 }, { 32767, 32767 } },
    { { 0, 128 }, { -34, 4 },  { -28, -11 }, { 50, -12 }, { 32767, 32767 }, { 32767, 32767 } },
    { { 0, 128 }, { -33, -6 }, { -28, -18 }, { 50, -36 }, { 32767, 32767 }, { 0, 0 }         },
    { { 0, 128 }, { -33, -2 }, { -28, -18 }, { 50, -28 }, { 32767, 32767 }, { 32767, 32767 } },
    { { 0, 128 }, { -34, 4 },  { -28, -11 }, { 50, -12 }, { 32767, 32767 }, { 32767, 32767 } },
    { { 0, 128 }, { -34, 4 },  { -28, -11 }, { 50, -12 }, { 32767, 32767 }, { 32767, 32767 } },
    { { 0, 128 }, { -34, 4 },  { -23, -1 },  { 50, -2 },  { 32767, 32767 }, { 32767, 32767 } },
    { { 0, 128 }, { -34, 4 },  { -28, -11 }, { 50, -12 }, { 50, -12 },      { 32767, 32767 } },
    { { 0, 128 }, { -34, 4 },  { -28, -11 }, { 50, -12 }, { 50, -12 },      { 32767, 32767 } },
    { { 0, 128 }, { -34, 4 },  { -28, -11 }, { 50, -12 }, { 32767, 32767 }, { 32767, 32767 } },
    { { 0, 128 }, { -34, 4 },  { -28, -11 }, { 50, -12 }, { 50, -12 },      { 32767, 32767 } },
    { { 0, 128 }, { -34, 4 },  { -28, -11 }, { 50, -12 }, { 50, -12 },      { 32767, 32767 } },
    { { 0, 128 }, { -34, 4 },  { -28, -11 }, { 50, -12 }, { 32767, 32767 }, { 32767, 32767 } },
};

// 0x0226D18C
// clang-format off
const u32 gBattleEncounterFadeColors[23] = {
    0x00007FFF, 0x00007FFF, 0x00007FFF, 0x00007FFF, 0x00007FFF, 0x00007FFF, 0x00007FFF, 0x00007FFF,
    0x00007FFF, 0, 0, 0, 0x00007FFF, 0x00007FFF, 0x00007FFF, 0x00007FFF, 0x00007FFF, 0x00007FFF, 0x00007FFF,
    0x00007FFF, 0x00007FFF, 0x00007FFF, 0x00007FFF,
};
// clang-format on

// 0x0226D15A
// clang-format off
const u16 gBallColors[25] = {
    0, 0x7297, 0x3FFF, 0x7AF0, 0x7ADF, 0x53D7, 0x67F5, 0x7B2C, 0x2B7E, 0x431F, 0x7BDD, 0x2A3F, 0x293F, 0x45CE,
    0x731F, 0x7F51, 0x151E, 0x7ADF, 0x7ADF, 0x7ADF, 0x7ADF, 0x7ADF, 0x7ADF, 0x7ADF, 0x7ADF,
};
// clang-format on

// 0x0226D140
// C declares this non-const, but it lives in .rodata
const u8 gSafariFleeRates[13][2] = {
    { 0x0A, 0x28 },
    { 0x0A, 0x23 },
    { 0x0A, 0x1E },
    { 0x0A, 0x19 },
    { 0x0A, 0x14 },
    { 0x0A, 0x0F },
    { 0x0A, 0x0A },
    { 0x0F, 0x0A },
    { 0x14, 0x0A },
    { 0x19, 0x0A },
    { 0x1E, 0x0A },
    { 0x23, 0x0A },
    { 0x28, 0x0A },
};

// 0x0226D128
// clang-format off
const u8 gOpponentRecallBallKinds[24] = {
    0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00,
    0x04, 0x00, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00,
};
// clang-format on

// 0x0226D120
// clang-format off
const u8 gOpponentBallKinds[8] __attribute__((aligned(4))) = {
    0x06, 0x01, 0x08, 0x03, 0x07, 0x05, 0x00, 0x00,
};
// clang-format on
