#ifndef POKEHEARTGOLD_MAP_OBJECT_BEHAVIOR_H
#define POKEHEARTGOLD_MAP_OBJECT_BEHAVIOR_H

#include "script.h"

BOOL TryGetSeenByNpcTrainers(FieldSystem *fieldSystem, BOOL doublesEligible);
intptr_t TrainerApproach_Start(FieldSystem *fieldSystem, LocalMapObject *localMapObject, PlayerAvatar *playerAvatar, int movement, int remaining, int unk10, int encounterType, u16 trainerNum);
BOOL TrainerApproach_IsDone(PORT_R0_PARAM(intptr_t task));
void TrainerApproach_Delete(intptr_t task);

#endif // POKEHEARTGOLD_MAP_OBJECT_BEHAVIOR_H
