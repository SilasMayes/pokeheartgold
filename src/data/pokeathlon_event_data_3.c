// Converted from asm/pokeathlon_event_data.s (part 3 of 4) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

// The C declarations of these do not match the data (see the notes at each
// definition): keep them out of the way of the definitions below.
#define gPokeathlonHurdleDashStates gPokeathlonHurdleDashStates_header_decl
#define gPokeathlonRelayRunStates   gPokeathlonRelayRunStates_header_decl

#include "global.h"

#include "pokeathlon/pokeathlon_block_smash.h"
#include "pokeathlon/pokeathlon_circle_push.h"
#include "pokeathlon/pokeathlon_course_internal.h"
#include "pokeathlon/pokeathlon_event_points.h"
#include "pokeathlon/pokeathlon_hurdle_dash_race.h"
#include "pokeathlon/pokeathlon_lamp_jump.h"

#pragma force_active on

#undef gPokeathlonHurdleDashStates
#undef gPokeathlonRelayRunStates

extern void PokeathlonRelayRun_Play(void);
extern void PokeathlonRelayRun_SaveScores(void);
extern void PokeathlonRelayRun_Start(void);

// C declares this const, but it lives in .data
// An address sits where that type has a 1-byte field.
void (*gPokeathlonHurdleDashStates[3])(void) = {
    (void (*)(void))PokeathlonHurdleDash_Start,
    (void (*)(void))PokeathlonHurdleDash_Play,
    (void (*)(void))PokeathlonHurdleDash_CalcScores,
};

// C declares this const, but it lives in .data
// An address sits where that type has a 1-byte field.
void (*gPokeathlonRelayRunStates[3])(void) = {
    PokeathlonRelayRun_Start,
    PokeathlonRelayRun_Play,
    PokeathlonRelayRun_SaveScores,
};
