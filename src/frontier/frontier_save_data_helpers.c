#include "frontier_save_data_helpers_internal.h"

#include "global.h"

#include "frontier/battle_tower_setup.h"
#include "frontier/frontier_trainers.h"

#include "frontier_field_support.h"

void BattleTower_GenerateOpponents(FrontierFieldSystem *tower, SaveData *saveData) {
    int i;
    u16 species[2];
    u16 items[2];

    switch (tower->towerMode) {
    case TOWER_MODE_WIFI:
    case TOWER_MODE_WIFI_PRACTICE:
        BattleTower_GetRoomTrainer(saveData, &tower->opponents[0], (u8)(tower->currentBattleNumber - 1));
        return;
    case TOWER_MODE_MULTI:
    case TOWER_MODE_LINK:
    case TOWER_MODE_6:
        BattleTower_GenerateTrainerMons(tower, &tower->opponents[0], tower->trainersInCurrentRound[(tower->currentBattleNumber - 1) * 2], tower->numMons, NULL, NULL, 0, tower->heapID);
        for (i = 0; i < tower->numMons; i++) {
            species[i] = tower->opponents[0].frontierMons[i].species;
            items[i] = tower->opponents[0].frontierMons[i].item;
        }
        BattleTower_GenerateTrainerMons(tower, &tower->opponents[1], tower->trainersInCurrentRound[(tower->currentBattleNumber - 1) * 2 + 1], tower->numMons, species, items, 0, tower->heapID);
        return;
    default:
        BattleTower_GenerateTrainerMons(tower, &tower->opponents[0], tower->trainersInCurrentRound[tower->currentBattleNumber - 1], tower->numMons, NULL, NULL, 0, tower->heapID);
        return;
    }
}

u32 BattleTower_GetTrainerSprite(FrontierFieldSystem *tower, u32 index) {
    return FrontierTrainer_GetClassSprite((u8)tower->opponents[index].trainerClass);
}

void BattleTower_SetPalmerDefeated(FrontierFieldSystem *tower, u32 value) {
    tower->palmerDefeated = (u8)value;
}

u32 BattleTower_IncBattleNumber(FrontierFieldSystem *tower) {
    tower->curWinStreak++;
    if (tower->towerMode != TOWER_MODE_6) {
        tower->randomState = BattleTower_NextRandom(tower->randomState);
    }
    tower->currentBattleNumber++;
    return tower->currentBattleNumber;
}

u32 BattleTower_GetWinStreak(FrontierFieldSystem *tower) {
    u32 streak = *(volatile u8 *)&tower->curWinStreak;
    u32 result = tower->currentBattleInSession + streak;
    u32 ret = 0xFFFF;
    if (result <= ret) {
        ret = (u16)result;
    }
    return ret;
}
