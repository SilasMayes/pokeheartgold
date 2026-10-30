// Converted from asm/pokeathlon_ring_drop_rodata.s (part 1 of 2) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

// The C declarations of these do not match the data (see the notes at each
// definition): keep them out of the way of the definitions below.
#define gPokeathlonRingDropScoreWindowTemplate gPokeathlonRingDropScoreWindowTemplate_header_decl

#include "global.h"

#include "pokeathlon/pokeathlon_ring_drop.h"

#pragma force_active on

#undef gPokeathlonRingDropScoreWindowTemplate

// C declares this as `const WindowTemplate gPokeathlonRingDropScoreWindowTemplate`, but the label
// holds 12 more bytes of data after it.
// clang-format off
const u8 gPokeathlonRingDropScoreWindowTemplate[20] = {
    0x03, 0x00, 0x14, 0x20, 0x02, 0x0F, 0x01, 0x00, 0x33, 0x0B, 0x00, 0x00, 0x33, 0x0B, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
};
// clang-format on

// clang-format off
const u8 gPokeathlonRingDropFallSpeeds[8] __attribute__((aligned(4))) = {
    0x00, 0x08, 0x08, 0x08, 0x08, 0x00, 0x00, 0x00,
};
// clang-format on
