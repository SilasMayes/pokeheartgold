// Converted from asm/encounter_effect_wild_data.s (part 2 of 3) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

#include "global.h"

#include "field/encounter_effect.h"

#pragma force_active on

// clang-format off
const BgTemplate gWildEffectWaveBgTemplate_Main1 = {
    0, 0, 0x00001000, 0, 0x02, 0x00, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00, 0,
};
// clang-format on

// clang-format off
const BgTemplate gWildEffectWaveBgTemplate_Main3 = {
    0, 0, 0x00001000, 0, 0x02, 0x00, 0x04, 0x02, 0x01, 0x00, 0x00, 0x00, 0,
};
// clang-format on
