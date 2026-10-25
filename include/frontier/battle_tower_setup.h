#ifndef POKEHEARTGOLD_FRONTIER_BATTLE_TOWER_SETUP_H
#define POKEHEARTGOLD_FRONTIER_BATTLE_TOWER_SETUP_H

#include "frontier/frontier.h"

typedef struct BattleTowerTrainerSets BattleTowerTrainerSets;

// A sample room trainer: a FrontierTrainer field and the indexes of its four Pokemon.
typedef struct BattleTowerSampleTrainer {
    u16 unk_00;
    u8 monIndexes[4];
} BattleTowerSampleTrainer;

extern const u16 gBattleTowerReplacementItems[];
extern const BattleTowerSampleTrainer gBattleTowerSampleTrainers[];
extern const u8 gBattleTowerSampleTrainerHeaders[];
extern const FrontierMon gBattleTowerSampleMons[];

u32 BattleTower_GenerateTrainerMons(FrontierFieldSystem *tower, FrontierTrainer *trainer, u16 trainerId, u32 count, u16 *partySpecies, u16 *partyItems, FrontierMultiBattleAllyData *allyData, enum HeapID heapID);
void BattleTower_GetRoomTrainer(SaveData *saveData, FrontierTrainer *trainer, int index);
BattleSetup *BattleTower_NewBattleSetup(FrontierFieldSystem *tower, FrontierLaunchArgs *args);
void BattleTowerSetup_SetLinkFlag(FrontierFieldSystem *tower, u32 value);
BOOL BattleTowerSetup_IsLinkFlagSetByEither(FrontierFieldSystem *tower, const u16 *remote);
u32 BattleTower_GetTrainerMessageBank(u32 towerMode);

#endif // POKEHEARTGOLD_FRONTIER_BATTLE_TOWER_SETUP_H
