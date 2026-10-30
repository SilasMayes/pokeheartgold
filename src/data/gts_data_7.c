// Converted from asm/gts_data.s (part 7 of 7) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

#include "global.h"

#include "constants/pokemon.h"

#include "gts/gts_internal.h"

#pragma force_active on

// clang-format off
const BgTemplate gGtsConnectionBg0Template = {
    0, 0, 0x00000800, 0, 0x01, 0x00, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0,
};
// clang-format on

// clang-format off
const BgTemplate gGtsConnectionBg1Template = {
    0, 0, 0x00000800, 0, 0x01, 0x00, 0x1E, 0x02, 0x00, 0x01, 0x00, 0x00, 0,
};
// clang-format on

// clang-format off
const BgTemplate gGtsConnectionSubBg0Template = {
    0, 0, 0x00000800, 0, 0x01, 0x00, 0x1E, 0x04, 0x00, 0x00, 0x00, 0x00, 0,
};
// clang-format on

// clang-format off
const BgTemplate gGtsConnectionSubBg1Template = {
    0, 0, 0x00000800, 0, 0x01, 0x00, 0x1B, 0x02, 0x00, 0x02, 0x00, 0x00, 0,
};
// clang-format on

const u32 gGtsPanelCaptionMsgIds[5] = { 0x000000E9, 0x000000EA, 0x000000EB, 0x000000EC, 0x000000ED };
