#ifndef POKEHEARTGOLD_FRONTIER_STAT_IDS_H
#define POKEHEARTGOLD_FRONTIER_STAT_IDS_H

#include "global.h"

u32 BattleFactory_GetWinStreakStat(u8 levelMode, u8 type);
u32 BattleFactory_GetBestStreakStat(u8 levelMode, u8 type);
u32 BattleFactory_GetTradeCountStat(u8 levelMode, u8 type);
u32 BattleFactory_GetBestTradeCountStat(u8 levelMode, u8 type);
u32 BattleHall_GetTypeRankStat(u32 type, u32 cell);
u32 BattleHall_GetWinStreakStat(u8 type);
u32 BattleHall_GetBestStreakStat(u32 type);
u32 BattleHall_GetSpeciesStat(u8 type);
u32 BattleHall_GetSpeciesRecordsType(u8 type);
u32 BattleCastle_GetRankStat(u8 type, u8 index);
u32 BattleCastle_GetWinStreakStat(u8 type);
u32 BattleCastle_GetBestStreakStat(u8 type);
u32 BattleCastle_GetPointsStat(u32 type);
u32 BattleCastle_GetSpentPointsStat(u32 type);
u32 BattleCastle_GetBestStreakPointsStat(u8 type);

#endif // POKEHEARTGOLD_FRONTIER_STAT_IDS_H
