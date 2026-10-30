// Converted from asm/trainer_ai_data.s (part 2 of 2) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

#include "global.h"

#pragma force_active on

extern void AICmd_AddToMoveScore(void);
extern void AICmd_CalcMaxEffectiveness(void);
extern void AICmd_CheckBattlerAbility(void);
extern void AICmd_CheckIfHighestDamageWithPartner(void);
extern void AICmd_CountAlivePartyBattlers(void);
extern void AICmd_DiffStatStages(void);
extern void AICmd_Dummy3E(void);
extern void AICmd_Dummy3F(void);
extern void AICmd_Escape(void);
extern void AICmd_FlagBattlerIsType(void);
extern void AICmd_FlagMoveDamageScore(void);
extern void AICmd_GoTo(void);
extern void AICmd_IfActivatedFlashFire(void);
extern void AICmd_IfAnyPartyMemberMissingHP(void);
extern void AICmd_IfAnyPartyMemberMissingPP(void);
extern void AICmd_IfAttackerHasDamagingMoves(void);
extern void AICmd_IfAttackerHasNoDamagingMoves(void);
extern void AICmd_IfBattlerDealsMoreDamage(void);
extern void AICmd_IfBattlerFainted(void);
extern void AICmd_IfBattlerHasEqualStat(void);
extern void AICmd_IfBattlerHasHigherStat(void);
extern void AICmd_IfBattlerHasLowerStat(void);
extern void AICmd_IfBattlerNotFainted(void);
extern void AICmd_IfBattlerUnderEffect(void);
extern void AICmd_IfCanUseLastResort(void);
extern void AICmd_IfCurrentMoveDoesNotKO(void);
extern void AICmd_IfCurrentMoveEffectEqualTo(void);
extern void AICmd_IfCurrentMoveEffectNotEqualTo(void);
extern void AICmd_IfCurrentMoveKOs(void);
extern void AICmd_IfCurrentMoveMatchesEffect(void);
extern void AICmd_IfFieldConditionActive(void);
extern void AICmd_IfHPPercentEqualTo(void);
extern void AICmd_IfHPPercentGreaterThan(void);
extern void AICmd_IfHPPercentLessThan(void);
extern void AICmd_IfHPPercentNotEqualTo(void);
extern void AICmd_IfHasSuperEffectiveMove(void);
extern void AICmd_IfHeldItemEqualTo(void);
extern void AICmd_IfLevel(void);
extern void AICmd_IfLoadedEqualTo(void);
extern void AICmd_IfLoadedGreaterThan(void);
extern void AICmd_IfLoadedInTable(void);
extern void AICmd_IfLoadedLessThan(void);
extern void AICmd_IfLoadedMask(void);
extern void AICmd_IfLoadedNotEqualTo(void);
extern void AICmd_IfLoadedNotInTable(void);
extern void AICmd_IfLoadedNotMask(void);
extern void AICmd_IfMoveEffect(void);
extern void AICmd_IfMoveEffectKnown(void);
extern void AICmd_IfMoveEffectNotKnown(void);
extern void AICmd_IfMoveEffectivenessEquals(void);
extern void AICmd_IfMoveEqualTo(void);
extern void AICmd_IfMoveKnown(void);
extern void AICmd_IfMoveNotEqualTo(void);
extern void AICmd_IfMoveNotKnown(void);
extern void AICmd_IfNotMoveEffect(void);
extern void AICmd_IfNotSideCondition(void);
extern void AICmd_IfNotStatus(void);
extern void AICmd_IfNotStatus2(void);
extern void AICmd_IfPartyMemberDealsMoreDamage(void);
extern void AICmd_IfPartyMemberNotStatus(void);
extern void AICmd_IfPartyMemberStatus(void);
extern void AICmd_IfRandomEqualTo(void);
extern void AICmd_IfRandomGreaterThan(void);
extern void AICmd_IfRandomLessThan(void);
extern void AICmd_IfRandomNotEqualTo(void);
extern void AICmd_IfSideCondition(void);
extern void AICmd_IfSpeedCompareEqualTo(void);
extern void AICmd_IfSpeedCompareNotEqualTo(void);
extern void AICmd_IfStatStageEqualTo(void);
extern void AICmd_IfStatStageGreaterThan(void);
extern void AICmd_IfStatStageLessThan(void);
extern void AICmd_IfStatStageNotEqualTo(void);
extern void AICmd_IfStatus(void);
extern void AICmd_IfStatus2(void);
extern void AICmd_IfTargetIsNotTaunted(void);
extern void AICmd_IfTargetIsPartner(void);
extern void AICmd_IfTargetIsTaunted(void);
extern void AICmd_IfTempEqualTo(void);
extern void AICmd_IfTempNotEqualTo(void);
extern void AICmd_LoadAbility(void);
extern void AICmd_LoadBattleType(void);
extern void AICmd_LoadBattlerAbility(void);
extern void AICmd_LoadBattlerPreviousMove(void);
extern void AICmd_LoadBattlerSpeedOrderPosition(void);
extern void AICmd_LoadBattlerTurnCount(void);
extern void AICmd_LoadCurrentMove(void);
extern void AICmd_LoadCurrentMoveCategory(void);
extern void AICmd_LoadCurrentMoveEffect(void);
extern void AICmd_LoadCurrentMovePP(void);
extern void AICmd_LoadCurrentWeather(void);
extern void AICmd_LoadDefenderLastUsedMoveCategory(void);
extern void AICmd_LoadEffectOfLoadedMove(void);
extern void AICmd_LoadFlingPower(void);
extern void AICmd_LoadGender(void);
extern void AICmd_LoadHeldItem(void);
extern void AICmd_LoadHeldItemEffect(void);
extern void AICmd_LoadIsFirstTurnInBattle(void);
extern void AICmd_LoadMovePower(void);
extern void AICmd_LoadPowerOfLoadedMove(void);
extern void AICmd_LoadProtectSuccessChain(void);
extern void AICmd_LoadRecycleItem(void);
extern void AICmd_LoadSpikesLayers(void);
extern void AICmd_LoadStockpileCount(void);
extern void AICmd_LoadTurnCount(void);
extern void AICmd_LoadTypeFrom(void);
extern void AICmd_LoadTypeOfLoadedMove(void);
extern void AICmd_PopOrEnd(void);
extern void AICmd_PushAndGoTo(void);
extern void AICmd_SumPositiveStatStages(void);

// 0x0222B0B4
void (*const sAICommandTable[109])(void) = {
    AICmd_IfRandomLessThan,
    AICmd_IfRandomGreaterThan,
    AICmd_IfRandomEqualTo,
    AICmd_IfRandomNotEqualTo,
    AICmd_AddToMoveScore,
    AICmd_IfHPPercentLessThan,
    AICmd_IfHPPercentGreaterThan,
    AICmd_IfHPPercentEqualTo,
    AICmd_IfHPPercentNotEqualTo,
    AICmd_IfStatus,
    AICmd_IfNotStatus,
    AICmd_IfStatus2,
    AICmd_IfNotStatus2,
    AICmd_IfMoveEffect,
    AICmd_IfNotMoveEffect,
    AICmd_IfSideCondition,
    AICmd_IfNotSideCondition,
    AICmd_IfLoadedLessThan,
    AICmd_IfLoadedGreaterThan,
    AICmd_IfLoadedEqualTo,
    AICmd_IfLoadedNotEqualTo,
    AICmd_IfLoadedMask,
    AICmd_IfLoadedNotMask,
    AICmd_IfMoveEqualTo,
    AICmd_IfMoveNotEqualTo,
    AICmd_IfLoadedInTable,
    AICmd_IfLoadedNotInTable,
    AICmd_IfAttackerHasDamagingMoves,
    AICmd_IfAttackerHasNoDamagingMoves,
    AICmd_LoadTurnCount,
    AICmd_LoadTypeFrom,
    AICmd_LoadMovePower,
    AICmd_FlagMoveDamageScore,
    AICmd_LoadBattlerPreviousMove,
    AICmd_IfTempEqualTo,
    AICmd_IfTempNotEqualTo,
    AICmd_IfSpeedCompareEqualTo,
    AICmd_IfSpeedCompareNotEqualTo,
    AICmd_CountAlivePartyBattlers,
    AICmd_LoadCurrentMove,
    AICmd_LoadCurrentMoveEffect,
    AICmd_LoadBattlerAbility,
    AICmd_CalcMaxEffectiveness,
    AICmd_IfMoveEffectivenessEquals,
    AICmd_IfPartyMemberStatus,
    AICmd_IfPartyMemberNotStatus,
    AICmd_LoadCurrentWeather,
    AICmd_IfCurrentMoveEffectEqualTo,
    AICmd_IfCurrentMoveEffectNotEqualTo,
    AICmd_IfStatStageLessThan,
    AICmd_IfStatStageGreaterThan,
    AICmd_IfStatStageEqualTo,
    AICmd_IfStatStageNotEqualTo,
    AICmd_IfCurrentMoveKOs,
    AICmd_IfCurrentMoveDoesNotKO,
    AICmd_IfMoveKnown,
    AICmd_IfMoveNotKnown,
    AICmd_IfMoveEffectKnown,
    AICmd_IfMoveEffectNotKnown,
    AICmd_IfBattlerUnderEffect,
    AICmd_IfCurrentMoveMatchesEffect,
    AICmd_Escape,
    AICmd_Dummy3E,
    AICmd_Dummy3F,
    AICmd_LoadHeldItem,
    AICmd_LoadHeldItemEffect,
    AICmd_LoadGender,
    AICmd_LoadIsFirstTurnInBattle,
    AICmd_LoadStockpileCount,
    AICmd_LoadBattleType,
    AICmd_LoadRecycleItem,
    AICmd_LoadTypeOfLoadedMove,
    AICmd_LoadPowerOfLoadedMove,
    AICmd_LoadEffectOfLoadedMove,
    AICmd_LoadProtectSuccessChain,
    AICmd_PushAndGoTo,
    AICmd_GoTo,
    AICmd_PopOrEnd,
    AICmd_IfLevel,
    AICmd_IfTargetIsTaunted,
    AICmd_IfTargetIsNotTaunted,
    AICmd_IfTargetIsPartner,
    AICmd_FlagBattlerIsType,
    AICmd_CheckBattlerAbility,
    AICmd_IfActivatedFlashFire,
    AICmd_IfHeldItemEqualTo,
    AICmd_IfFieldConditionActive,
    AICmd_LoadSpikesLayers,
    AICmd_IfAnyPartyMemberMissingHP,
    AICmd_IfAnyPartyMemberMissingPP,
    AICmd_LoadFlingPower,
    AICmd_LoadCurrentMovePP,
    AICmd_IfCanUseLastResort,
    AICmd_LoadCurrentMoveCategory,
    AICmd_LoadDefenderLastUsedMoveCategory,
    AICmd_LoadBattlerSpeedOrderPosition,
    AICmd_LoadBattlerTurnCount,
    AICmd_IfPartyMemberDealsMoreDamage,
    AICmd_IfHasSuperEffectiveMove,
    AICmd_IfBattlerDealsMoreDamage,
    AICmd_SumPositiveStatStages,
    AICmd_DiffStatStages,
    AICmd_IfBattlerHasHigherStat,
    AICmd_IfBattlerHasLowerStat,
    AICmd_IfBattlerHasEqualStat,
    AICmd_CheckIfHighestDamageWithPartner,
    AICmd_IfBattlerFainted,
    AICmd_IfBattlerNotFainted,
    AICmd_LoadAbility,
};

// 0x0222B098
// clang-format off
const u16 sNoDamageCalcMoveEffects[14] = {
    7, 8, 0x0027, 0x004B, 0x0050, 0x0091, 0x0097, 0x00A1, 0x00AA, 0x00B6, 0x00BE, 0x00F8, 0x010D, 0xFFFF,
};
// clang-format on

// 0x0222B080
// clang-format off
const u16 sAltPowerMoveEffects[12] = {
    0x0087, 0x00DB, 0x00DE, 0x010C, 0x0029, 0x0057, 0x0058, 0x0079, 0x007B, 0x0082, 0x00C4, 0xFFFF,
};
// clang-format on

// 0x0222B068
// clang-format off
const u8 sWeightToPower[24] = {
    0x64, 0x00, 0x14, 0x00, 0xFA, 0x00, 0x28, 0x00, 0xF4, 0x01, 0x3C, 0x00, 0xE8, 0x03, 0x50, 0x00,
    0xD0, 0x07, 0x64, 0x00, 0xFF, 0xFF, 0xFF, 0xFF,
};
// clang-format on
