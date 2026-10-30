// Converted from asm/pokeathlon_event_data.s (part 2 of 4) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

// The C declarations of these do not match the data (see the notes at each
// definition): keep them out of the way of the definitions below.
#define gPokeathlonResultsAnnouncementSteps gPokeathlonResultsAnnouncementSteps_header_decl
#define gPokeathlonHurdleDashLanePans       gPokeathlonHurdleDashLanePans_header_decl

#include "global.h"

#include "pokeathlon/pokeathlon_block_smash.h"
#include "pokeathlon/pokeathlon_circle_push.h"
#include "pokeathlon/pokeathlon_course_internal.h"
#include "pokeathlon/pokeathlon_event_points.h"
#include "pokeathlon/pokeathlon_hurdle_dash_race.h"
#include "pokeathlon/pokeathlon_lamp_jump.h"

#pragma force_active on

#undef gPokeathlonResultsAnnouncementSteps
#undef gPokeathlonHurdleDashLanePans

extern void PokeathlonResults_Run(void);

// C declares this const, but it lives in .data
s8 gPokeathlonHurdleDashLanePans[4] = { (s8)0x94, 0x00, 0x6B, 0x00 };

// C declares this const, but it lives in .data
// clang-format off
PokeathlonCourseStepFunc gPokeathlonResultsAnnouncementSteps[1] = {
    (PokeathlonCourseStepFunc)PokeathlonResults_Run,
};
// clang-format on

u8 gPokeathlonHurdleDashLaneSoundPlayers[4] = { 0x03, 0x04, 0x05, 0x00 };
