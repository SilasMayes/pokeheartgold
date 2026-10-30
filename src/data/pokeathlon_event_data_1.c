// Converted from asm/pokeathlon_event_data.s (part 1 of 4) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

// The C declarations of these do not match the data (see the notes at each
// definition): keep them out of the way of the definitions below.
#define gPokeathlonLampJumpStates gPokeathlonLampJumpStates_header_decl

#include "global.h"

#include "pokeathlon/pokeathlon_block_smash.h"
#include "pokeathlon/pokeathlon_circle_push.h"
#include "pokeathlon/pokeathlon_course_internal.h"
#include "pokeathlon/pokeathlon_event_points.h"
#include "pokeathlon/pokeathlon_hurdle_dash_race.h"
#include "pokeathlon/pokeathlon_lamp_jump.h"

#pragma force_active on

#undef gPokeathlonLampJumpStates

// clang-format off
void (*const gPokeathlonEventPointsCalcFuncs[10])(PokeathlonCourseScoreList *list, int event) = {
    PokeathlonEvent_CalcPointsFromScores, PokeathlonEvent_CalcPointsFromScores,
    PokeathlonEvent_CalcPointsFromScores, PokeathlonEvent_CalcPointsFromScores,
    PokeathlonEvent_CalcPointsFromScores, PokeathlonEvent_CalcPointsFromScores,
    PokeathlonEvent_CalcPointsFromScores, PokeathlonEvent_CalcPointsFromScores,
    PokeathlonEvent_CalcPointsFromScores, PokeathlonEvent_CalcPointsFromRanks,
};
// clang-format on

// clang-format off
const PokeathlonEventPointsFunc gPokeathlonEventScorePointsFuncs[10] = {
    (PokeathlonEventPointsFunc)PokeathlonEvent_HurdleDashPoints,
    (PokeathlonEventPointsFunc)PokeathlonEvent_PennantCapturePoints,
    (PokeathlonEventPointsFunc)PokeathlonEvent_CirclePushPoints,
    (PokeathlonEventPointsFunc)PokeathlonEvent_BlockSmashPoints,
    (PokeathlonEventPointsFunc)PokeathlonEvent_DiscCatchPoints,
    (PokeathlonEventPointsFunc)PokeathlonEvent_LampJumpPoints,
    (PokeathlonEventPointsFunc)PokeathlonEvent_RelayRunPoints,
    (PokeathlonEventPointsFunc)PokeathlonEvent_RingDropPoints,
    (PokeathlonEventPointsFunc)PokeathlonEvent_SnowThrowPoints, NULL,
};
// clang-format on

// C declares this const, but it lives in .data
// An address sits where that type has a 1-byte field.
void (*gPokeathlonLampJumpStates[2])(void) = {
    (void (*)(void))PokeathlonLampJump_Play,
    (void (*)(void))PokeathlonLampJump_CalcScores,
};

const u8 gPokeathlonEventRankPoints[4] __attribute__((aligned(4))) = "dPF<";

u8 gPokeathlonLampJumpSoundPlayers[4] __attribute__((aligned(4))) = { 0x03, 0x04, 0x05, 0x06 };

PokeathlonCirclePushContact gPokeathlonCirclePushContacts[POKEATHLON_MONS][POKEATHLON_MONS];
