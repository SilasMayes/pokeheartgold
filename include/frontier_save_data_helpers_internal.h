#ifndef POKEHEARTGOLD_FRONTIER_SAVE_DATA_HELPERS_INTERNAL_H
#define POKEHEARTGOLD_FRONTIER_SAVE_DATA_HELPERS_INTERNAL_H

#include "save.h"
#include "scrcmd_9.h"

void BattleTower_GenerateOpponents(FrontierFieldSystem *tower, SaveData *saveData);
u32 BattleTower_GetTrainerSprite(FrontierFieldSystem *tower, u32 index);
void BattleTower_SetPalmerDefeated(FrontierFieldSystem *tower, u32 value);
u32 BattleTower_IncBattleNumber(FrontierFieldSystem *tower);
u32 BattleTower_GetWinStreak(FrontierFieldSystem *tower);

#endif
