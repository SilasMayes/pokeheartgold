// Converted from asm/field_move_effects_data.s (part 6 of 6) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

#include "global.h"

#include "constants/abilities.h"
#include "constants/items.h"
#include "constants/pokemon.h"
#include "constants/sndseq.h"
#include "constants/species.h"
#include "constants/std_script.h"

#include "field/field_move_cut_in.h"
#include "field/field_move_effects.h"
#include "field/fly_landing_effect.h"

#pragma force_active on

const u8 gFollowMonGrowScale[12] = { 0x00, 0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00 };

// clang-format off
const u8 gFollowMonShrinkScale[12] = {
    0x00, 0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00,
};
// clang-format on
