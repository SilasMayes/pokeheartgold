// Converted from asm/pokewalker_data.s (part 5 of 15) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

// The C declarations of these do not match the data (see the notes at each
// definition): keep them out of the way of the definitions below.
#define gEventLogCourseBgm gEventLogCourseBgm_header_decl

#include "global.h"

#include "application/pokewalker/pokewalker_app.h"
#include "application/pokewalker/pokewalker_app_internal.h"
#include "application/pokewalker/pokewalker_event_log.h"
#include "application/pokewalker/pokewalker_ir_internal.h"
#include "application/pokewalker/pokewalker_trainer_house.h"

#pragma force_active on

#undef gEventLogCourseBgm

// C declares this const, but it lives in .data
// clang-format off
u32 gEventLogCourseBgm[8] = {
    0x00000499, 0x00000499, 0x0000049A, 0x0000049A, 0x0000049B, 0x0000049D, 0x00000499, 0x0000049C,
};
// clang-format on

const OamManagerParam gPokewalkerAppOamManagerParam = { 0, 128, 0, 32, 0, 128, 0, 32 };

const SpriteResourceCountsListUnion gPokewalkerAppSpriteResourceCounts = { 10, 2, 2, 2, 0, 0 };

// clang-format off
const OamCharTransferParam gPokewalkerAppOamCharTransferParam = {
    17, 65536, 16384, GX_OBJVRAMMODE_CHAR_1D_32K, GX_OBJVRAMMODE_CHAR_1D_32K,
};
// clang-format on
