#ifndef POKEHEARTGOLD_FRONTIER_FIELD_SUPPORT_H
#define POKEHEARTGOLD_FRONTIER_FIELD_SUPPORT_H

#include "script.h"

struct BattleSetupSub_138;

void TaskManager_CallFrontierPartySelect(TaskManager *taskManager, void **runningApp, u8 context, u8 summaryMode, u8 minMons, u8 maxMons, u8 maxLevel, u8 partySlot);
void TaskManager_CallFrontierWifiConnection(TaskManager *taskManager, u16 mode, u16 outputVar, u16 connectNow);
void TaskManager_CallFrontierLinkPartnerCheck(TaskManager *taskManager, u16 kind, u16 outputVar);
u32 BattleTower_ClaimRecordMilestone(SaveData *saveData);
u32 BattleTower_GetRecordMilestone(SaveData *saveData);
void FrontierFieldSystem_AddBattleTotals(FieldSystem *fieldSystem, struct BattleSetupSub_138 *totals);
u32 BattleTower_NextRandom(u32 value);
u32 BattleTower_InitSeed(SaveData *saveData);
u32 BattleTower_AdvanceSeed(SaveData *saveData);
u32 BattleTower_RestoreRandom(SaveData *saveData);
BOOL FieldSystem_MapIsBattleTowerMultiPartnerSelectRoom(FieldSystem *fieldSystem);
void Save_DullBadges(SaveData *saveData, int days);

#endif // POKEHEARTGOLD_FRONTIER_FIELD_SUPPORT_H
