#ifndef POKEHEARTGOLD_POKEATHLON_POKEATHLON_EVENT_POINTS_H
#define POKEHEARTGOLD_POKEATHLON_POKEATHLON_EVENT_POINTS_H

#include "global.h"

#include "pokeathlon/pokeathlon_course_types_def.h"

// The course points of an event.

typedef u32 (*PokeathlonEventPointsFunc)(u32 score);

void PokeathlonEvent_CalcPoints(PokeathlonCourseScoreList *list, int event);
void PokeathlonEvent_CalcPointsFromScores(PokeathlonCourseScoreList *list, int event);
void PokeathlonEvent_CalcPointsFromRanks(PokeathlonCourseScoreList *list, int event);
u8 PokeathlonEvent_HurdleDashPoints(u32 frames);
u8 PokeathlonEvent_PennantCapturePoints(int score);
u8 PokeathlonEvent_CirclePushPoints(int score);
u8 PokeathlonEvent_BlockSmashPoints(u32 score);
u8 PokeathlonEvent_DiscCatchPoints(u32 score);
u8 PokeathlonEvent_LampJumpPoints(u32 score);
u8 PokeathlonEvent_RelayRunPoints(u32 score);
u8 PokeathlonEvent_RingDropPoints(u32 score);
u8 PokeathlonEvent_SnowThrowPoints(int score);

void PokeathlonEvent_CalcRankPoints(PokeathlonCourseScoreList *list);

extern void (*const gPokeathlonEventPointsCalcFuncs[])(PokeathlonCourseScoreList *list, int event);
extern const PokeathlonEventPointsFunc gPokeathlonEventScorePointsFuncs[];
extern const u8 gPokeathlonEventRankPoints[4];

#endif // POKEHEARTGOLD_POKEATHLON_POKEATHLON_EVENT_POINTS_H
