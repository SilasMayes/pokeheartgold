// Converted from asm/pokeathlon_event_data.s (part 4 of 4) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

// The C declarations of these do not match the data (see the notes at each
// definition): keep them out of the way of the definitions below.
#define gPokeathlonSnowThrowStates      gPokeathlonSnowThrowStates_header_decl
#define gPokeathlonPennantCaptureStates gPokeathlonPennantCaptureStates_header_decl
#define gPokeathlonBlockSmashStates     gPokeathlonBlockSmashStates_header_decl
#define gPokeathlonDiscCatchStates      gPokeathlonDiscCatchStates_header_decl

#include "global.h"

#include "pokeathlon/pokeathlon_block_smash.h"
#include "pokeathlon/pokeathlon_circle_push.h"
#include "pokeathlon/pokeathlon_course_internal.h"
#include "pokeathlon/pokeathlon_event_points.h"
#include "pokeathlon/pokeathlon_hurdle_dash_race.h"
#include "pokeathlon/pokeathlon_lamp_jump.h"

#pragma force_active on

#undef gPokeathlonSnowThrowStates
#undef gPokeathlonPennantCaptureStates
#undef gPokeathlonBlockSmashStates
#undef gPokeathlonDiscCatchStates

extern void PokeathlonDiscCatch_Finish(void);
extern void PokeathlonDiscCatch_Intro(void);
extern void PokeathlonDiscCatch_Play(void);
extern void PokeathlonPennantCapture_State_End(void);
extern void PokeathlonPennantCapture_State_Play(void);
extern void PokeathlonPennantCapture_State_Setup(void);
extern void PokeathlonSnowThrow_Play(void);
extern void PokeathlonSnowThrow_SaveScores(void);
extern const u8 gPokeathlonBlockSmashSpotHitboxes_Kind0[];
extern const u8 gPokeathlonBlockSmashSpotHitboxes_Kind1[];
extern const u8 gPokeathlonBlockSmashSpotHitboxes_Kind2[];

// clang-format off
const TouchscreenHitbox *gPokeathlonBlockSmashSpotHitboxes[3] = {
    (const TouchscreenHitbox *)gPokeathlonBlockSmashSpotHitboxes_Kind0,
    (const TouchscreenHitbox *)gPokeathlonBlockSmashSpotHitboxes_Kind1,
    (const TouchscreenHitbox *)gPokeathlonBlockSmashSpotHitboxes_Kind2,
};
// clang-format on

// C declares this const, but it lives in .data
// An address sits where that type has a 1-byte field.
void (*gPokeathlonBlockSmashStates[3])(void) = {
    (void (*)(void))PokeathlonBlockSmash_Intro,
    (void (*)(void))PokeathlonBlockSmash_Play,
    (void (*)(void))PokeathlonBlockSmash_Finish,
};

// C declares this const, but it lives in .data
// An address sits where that type has a 1-byte field.
void (*gPokeathlonPennantCaptureStates[3])(void) = {
    PokeathlonPennantCapture_State_Setup,
    PokeathlonPennantCapture_State_Play,
    PokeathlonPennantCapture_State_End,
};

// C declares this const, but it lives in .data
// An address sits where that type has a 1-byte field.
void (*gPokeathlonDiscCatchStates[3])(void) = {
    PokeathlonDiscCatch_Intro,
    PokeathlonDiscCatch_Play,
    PokeathlonDiscCatch_Finish,
};

// C declares this const, but it lives in .data
// An address sits where that type has a 1-byte field.
void (*gPokeathlonSnowThrowStates[2])(void) = {
    PokeathlonSnowThrow_Play,
    PokeathlonSnowThrow_SaveScores,
};
