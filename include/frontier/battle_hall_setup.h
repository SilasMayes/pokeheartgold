#ifndef POKEHEARTGOLD_FRONTIER_BATTLE_HALL_SETUP_H
#define POKEHEARTGOLD_FRONTIER_BATTLE_HALL_SETUP_H

#include "frontier/battle_hall_data.h"
#include "frontier/frontier.h"

#define HALL_MATRON_SILVER        307 // trainer ids of the Hall Matron, battles 50 and 170 of the single battle streak
#define HALL_MATRON_GOLD          308
#define HALL_MATRON_BATTLE_SILVER 50
#define HALL_MATRON_BATTLE_GOLD   170
#define IS_HALL_MATRON(trainerId) ((trainerId) == HALL_MATRON_SILVER || (trainerId) == HALL_MATRON_GOLD)

typedef struct BattleHallSetRange {
    u16 min;
    u16 max;
} BattleHallSetRange;

typedef struct BattleHallSetTypes {
    u16 type1;
    u16 type2;
} BattleHallSetTypes;

extern const BattleHallSetRange gBattleHallMatronSetRanges[];
extern const BattleHallSetRange gBattleHallGoldMatronSetRange;
extern const u8 gBattleHallRankIVs[];
extern const BattleHallSetRange gBattleHallRankSetRanges[];
extern const u16 gBattleHallCellTrainerClasses[];
extern const u16 gBattleHallRankTrainerClasses[];
extern const u16 gBattleHallTrainerClasses[];
extern const u16 gBattleHallSetSpecies[];
extern const BattleHallSetTypes gBattleHallSetTypes[];

void BattleHall_PickTrainerClasses(u32 cell, int count, u32 rank, u32 battleNo, u16 *trainerIds);
void BattleHall_PickTrainerIds(int type, int count, int round, u32 rank, u8 battleNo, u16 *trainerIds);
void BattleHall_PickSetIds(u16 count, u16 cellType, int rank, u8 battleNo, u16 playerSpecies, u16 *setIds, int matron);
BattleSetup *BattleHall_NewBattleSetup(BattleHallData *data, FrontierLaunchArgs *args);
u8 BattleHall_GetPartySize(u8 type);
u8 BattleHall_GetCellType(u8 cell);
BOOL BattleHall_IsMultiType(int type);
u16 BattleHall_GetPartyLevel(BattleHallData *data);
u32 BattleHall_SqrtFx(u32 value);

#endif // POKEHEARTGOLD_FRONTIER_BATTLE_HALL_SETUP_H
