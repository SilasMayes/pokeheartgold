// Converted from asm/overlay_12_battle_command.s by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout. Keep that when editing, or rerun tools/s2c.py.

// The C declarations of these do not match the data (see the notes at each
// definition): keep them out of the way of the definitions below.
#define sStandardBallCatchRates sStandardBallCatchRates_header_decl
#define sTrumpCardPowerTable    sTrumpCardPowerTable_header_decl
#define sProtectSuccessChance   sProtectSuccessChance_header_decl
#define sFlailDamageTable       sFlailDamageTable_header_decl
#define sLowKickDamageTable     sLowKickDamageTable_header_decl
#define sNaturePowerMoveTable   sNaturePowerMoveTable_header_decl
#define sSafariCatchRateStages  sSafariCatchRateStages_header_decl
#define sMoonBallPokemon        sMoonBallPokemon_header_decl
#define sSecretPowerEffectTable sSecretPowerEffectTable_header_decl

#include "global.h"

#include "constants/items.h"
#include "constants/moves.h"
#include "constants/pokemon.h"
#include "constants/sndseq.h"
#include "constants/species.h"
#include "constants/trainer_class.h"

#pragma force_active on

#undef sStandardBallCatchRates
#undef sTrumpCardPowerTable
#undef sProtectSuccessChance
#undef sFlailDamageTable
#undef sLowKickDamageTable
#undef sNaturePowerMoveTable
#undef sSafariCatchRateStages
#undef sMoonBallPokemon
#undef sSecretPowerEffectTable

extern void BtlCmd_222(void);
extern void BtlCmd_223(void);
extern void BtlCmd_AddPayDayMoney(void);
extern void BtlCmd_ApplyTypeEffectiveness(void);
extern void BtlCmd_BackgroundSlideIn(void);
extern void BtlCmd_BeatUp(void);
extern void BtlCmd_BoostRandomStatBy2(void);
extern void BtlCmd_BufferLocalMessage(void);
extern void BtlCmd_BufferMessage(void);
extern void BtlCmd_CalcCrit(void);
extern void BtlCmd_CalcDamage(void);
extern void BtlCmd_CalcDamageRaw(void);
extern void BtlCmd_CalcExpGain(void);
extern void BtlCmd_CalcFlailPower(void);
extern void BtlCmd_CalcFuryCutterPower(void);
extern void BtlCmd_CalcGyroBallPower(void);
extern void BtlCmd_CalcHPFalloffPower(void);
extern void BtlCmd_CalcHiddenPowerParams(void);
extern void BtlCmd_CalcMagnitudePower(void);
extern void BtlCmd_CalcNaturalGiftParams(void);
extern void BtlCmd_CalcPaybackPower(void);
extern void BtlCmd_CalcPunishmentPower(void);
extern void BtlCmd_CalcRevengeDamageMul(void);
extern void BtlCmd_CalcRolloutPower(void);
extern void BtlCmd_CalcTrumpCardPower(void);
extern void BtlCmd_CalcWeatherBallParams(void);
extern void BtlCmd_CalcWeightBasedPower(void);
extern void BtlCmd_CalcWringOutPower(void);
extern void BtlCmd_Call(void);
extern void BtlCmd_CallFromVar(void);
extern void BtlCmd_ChangeForm(void);
extern void BtlCmd_ChangeStatStage(void);
extern void BtlCmd_CheckAbility(void);
extern void BtlCmd_CheckChatterActivation(void);
extern void BtlCmd_CheckCurMoveIsType(void);
extern void BtlCmd_CheckEffectActivation(void);
extern void BtlCmd_CheckHoldOnWith1HP(void);
extern void BtlCmd_CheckIgnorableAbility(void);
extern void BtlCmd_CheckIgnoreWeather(void);
extern void BtlCmd_CheckItemHoldEffect(void);
extern void BtlCmd_CheckItemHoldEffectOnHit(void);
extern void BtlCmd_CheckItemHoldEffectOnUTurn(void);
extern void BtlCmd_CheckMoveHit(void);
extern void BtlCmd_CheckSafariGameDone(void);
extern void BtlCmd_CheckSideCondition(void);
extern void BtlCmd_CheckSpikes(void);
extern void BtlCmd_CheckStealthRock(void);
extern void BtlCmd_CheckSubstitute(void);
extern void BtlCmd_CheckToxicSpikes(void);
extern void BtlCmd_CheckWhiteout(void);
extern void BtlCmd_ChoosePokemonMenu(void);
extern void BtlCmd_ClearVolatileStatus(void);
extern void BtlCmd_CompareMonDataToValue(void);
extern void BtlCmd_CompareMonDataToVar(void);
extern void BtlCmd_CompareVarToValue(void);
extern void BtlCmd_CompareVarToVar(void);
extern void BtlCmd_CopyStatStages(void);
extern void BtlCmd_Counter(void);
extern void BtlCmd_DeletePokemon(void);
extern void BtlCmd_DivideVarByValue(void);
extern void BtlCmd_DivideVarByVar(void);
extern void BtlCmd_EndOfTurnWeatherEffect(void);
extern void BtlCmd_EndScript(void);
extern void BtlCmd_FadeOutBattle(void);
extern void BtlCmd_FlickerMon(void);
extern void BtlCmd_FollowMe(void);
extern void BtlCmd_FreePartyGaugeGraphics(void);
extern void BtlCmd_GenerateEndOfBattleItem(void);
extern void BtlCmd_GetCurrentMoveData(void);
extern void BtlCmd_GetItemEffectParam(void);
extern void BtlCmd_GetItemHoldEffect(void);
extern void BtlCmd_GetTerrainMove(void);
extern void BtlCmd_GetTerrainSecondaryEffect(void);
extern void BtlCmd_GetTurnOrderBySpeed(void);
extern void BtlCmd_GoToEffectScript(void);
extern void BtlCmd_GoToIfAnySwitches(void);
extern void BtlCmd_GoToIfValidMon(void);
extern void BtlCmd_GoToMoveScript(void);
extern void BtlCmd_GoToSubscript(void);
extern void BtlCmd_Goto(void);
extern void BtlCmd_HealthbarSlideIn(void);
extern void BtlCmd_HealthbarSlideInDelay(void);
extern void BtlCmd_HealthbarSlideOut(void);
extern void BtlCmd_HideBattleStartPartyGauge(void);
extern void BtlCmd_HidePartyGauge(void);
extern void BtlCmd_IfMovedThisTurn(void);
extern void BtlCmd_IfSameSide(void);
extern void BtlCmd_IfTurnFlag(void);
extern void BtlCmd_IncrementGameStat(void);
extern void BtlCmd_LoadArchivedMonData(void);
extern void BtlCmd_LoadPartyGaugeGraphics(void);
extern void BtlCmd_LockMoveChoice(void);
extern void BtlCmd_MagicCoat(void);
extern void BtlCmd_Metronome(void);
extern void BtlCmd_MirrorCoat(void);
extern void BtlCmd_OAMToSprite(void);
extern void BtlCmd_PayPrizeMoney(void);
extern void BtlCmd_PlayBGM(void);
extern void BtlCmd_PlayBattleAnimation(void);
extern void BtlCmd_PlayBattleAnimationFromVar(void);
extern void BtlCmd_PlayBattleAnimationOnMons(void);
extern void BtlCmd_PlayEncounterAnimation(void);
extern void BtlCmd_PlayFaintAnimation(void);
extern void BtlCmd_PlayMoveAnimation(void);
extern void BtlCmd_PlayMoveAnimationOnMons(void);
extern void BtlCmd_PlayMoveHitSound(void);
extern void BtlCmd_PlaySound(void);
extern void BtlCmd_PokemonSendOut(void);
extern void BtlCmd_PokemonSlideIn(void);
extern void BtlCmd_Present(void);
extern void BtlCmd_PrintAttackMessage(void);
extern void BtlCmd_PrintBattleResultMessage(void);
extern void BtlCmd_PrintBufferedMessage(void);
extern void BtlCmd_PrintBufferedTrainerMessage(void);
extern void BtlCmd_PrintEncounterMessage(void);
extern void BtlCmd_PrintEscapeMessage(void);
extern void BtlCmd_PrintFirstSendOutMessage(void);
extern void BtlCmd_PrintForfeitMessage(void);
extern void BtlCmd_PrintGlobalMessage(void);
extern void BtlCmd_PrintMessage(void);
extern void BtlCmd_PrintRecallMessage(void);
extern void BtlCmd_PrintSendOutMessage(void);
extern void BtlCmd_PrintTrainerMessage(void);
extern void BtlCmd_Random(void);
extern void BtlCmd_RapidSpin(void);
extern void BtlCmd_RecallPokemon(void);
extern void BtlCmd_RefreshMonData(void);
extern void BtlCmd_RefreshSprite(void);
extern void BtlCmd_RemoveItem(void);
extern void BtlCmd_ResetAllStatChanges(void);
extern void BtlCmd_RestoreSprite(void);
extern void BtlCmd_SetBattleBackground(void);
extern void BtlCmd_SetHealthbarStatus(void);
extern void BtlCmd_SetLinkBattleResult(void);
extern void BtlCmd_SetMirrorMove(void);
extern void BtlCmd_SetMosaic(void);
extern void BtlCmd_SetMultiHit(void);
extern void BtlCmd_SetPokemonEncounter(void);
extern void BtlCmd_SetRandomTarget(void);
extern void BtlCmd_SetTrainerEncounter(void);
extern void BtlCmd_SetTurnFlag(void);
extern void BtlCmd_ShowBattleStartPartyGauge(void);
extern void BtlCmd_ShowParty(void);
extern void BtlCmd_ShowPartyGauge(void);
extern void BtlCmd_SpriteToOAM(void);
extern void BtlCmd_StartCatchMonTask(void);
extern void BtlCmd_StartGetExpTask(void);
extern void BtlCmd_SwitchAndUpdateMon(void);
extern void BtlCmd_ThrowPokeball(void);
extern void BtlCmd_ToggleVanish(void);
extern void BtlCmd_TrainerSlideIn(void);
extern void BtlCmd_TrainerSlideOut(void);
extern void BtlCmd_Transform(void);
extern void BtlCmd_TrickRoom(void);
extern void BtlCmd_TriggerAbilityOnHit(void);
extern void BtlCmd_TryAssist(void);
extern void BtlCmd_TryAttract(void);
extern void BtlCmd_TryBreakScreens(void);
extern void BtlCmd_TryCamouflage(void);
extern void BtlCmd_TryConversion(void);
extern void BtlCmd_TryConversion2(void);
extern void BtlCmd_TryCopycat(void);
extern void BtlCmd_TryDisable(void);
extern void BtlCmd_TryEncore(void);
extern void BtlCmd_TryEscape(void);
extern void BtlCmd_TryFaintMon(void);
extern void BtlCmd_TryFeint(void);
extern void BtlCmd_TryFling(void);
extern void BtlCmd_TryFutureSight(void);
extern void BtlCmd_TryGrudge(void);
extern void BtlCmd_TryHelpingHand(void);
extern void BtlCmd_TryImprison(void);
extern void BtlCmd_TryKnockOff(void);
extern void BtlCmd_TryLastResort(void);
extern void BtlCmd_TryLightScreen(void);
extern void BtlCmd_TryMeFirst(void);
extern void BtlCmd_TryMetalBurst(void);
extern void BtlCmd_TryMimic(void);
extern void BtlCmd_TryMist(void);
extern void BtlCmd_TryOHKOMove(void);
extern void BtlCmd_TryPartyStatusRefresh(void);
extern void BtlCmd_TryPerishSong(void);
extern void BtlCmd_TryPluck(void);
extern void BtlCmd_TryProtection(void);
extern void BtlCmd_TryPursuit(void);
extern void BtlCmd_TryPyschoShift(void);
extern void BtlCmd_TryRecycle(void);
extern void BtlCmd_TryReflect(void);
extern void BtlCmd_TryReplaceFaintedMon(void);
extern void BtlCmd_TryRestoreStatusOnSwitch(void);
extern void BtlCmd_TrySafeguard(void);
extern void BtlCmd_TrySetMagicCoat(void);
extern void BtlCmd_TrySketch(void);
extern void BtlCmd_TrySleepTalk(void);
extern void BtlCmd_TrySnatch(void);
extern void BtlCmd_TrySpikes(void);
extern void BtlCmd_TrySpite(void);
extern void BtlCmd_TryStealItem(void);
extern void BtlCmd_TrySubstitute(void);
extern void BtlCmd_TrySuckerPunch(void);
extern void BtlCmd_TrySwapItems(void);
extern void BtlCmd_TryTeleport(void);
extern void BtlCmd_TryToxicSpikes(void);
extern void BtlCmd_TryWhirlwind(void);
extern void BtlCmd_TryWish(void);
extern void BtlCmd_TryYawn(void);
extern void BtlCmd_UnlockMoveChoice(void);
extern void BtlCmd_UpdateHealthbar(void);
extern void BtlCmd_UpdateHealthbarValue(void);
extern void BtlCmd_UpdateMonData(void);
extern void BtlCmd_UpdateMonDataFromVar(void);
extern void BtlCmd_UpdateVar(void);
extern void BtlCmd_UpdateVar2(void);
extern void BtlCmd_UseBagItem(void);
extern void BtlCmd_Wait(void);
extern void BtlCmd_WaitButtonABTime(void);
extern void BtlCmd_WaitCatchMonTask(void);
extern void BtlCmd_WaitGetExpTask(void);
extern void BtlCmd_WaitGetExpTaskLoop(void);
extern void BtlCmd_WaitMonSelection(void);
extern void BtlCmd_WaitPokemonMenuResult(void);
extern void BtlCmd_WaitTime(void);
extern void BtlCmd_WaitYesNoResult(void);
extern void BtlCmd_WeatherHPRecovery(void);
extern void BtlCmd_YesNoMenu(void);

void (*const sBattleScriptCommandTable[225])(void) = {
    BtlCmd_PlayEncounterAnimation,
    BtlCmd_SetPokemonEncounter,
    BtlCmd_PokemonSlideIn,
    BtlCmd_PokemonSendOut,
    BtlCmd_RecallPokemon,
    BtlCmd_DeletePokemon,
    BtlCmd_SetTrainerEncounter,
    BtlCmd_ThrowPokeball,
    BtlCmd_TrainerSlideOut,
    BtlCmd_TrainerSlideIn,
    BtlCmd_BackgroundSlideIn,
    BtlCmd_HealthbarSlideIn,
    BtlCmd_HealthbarSlideInDelay,
    BtlCmd_HealthbarSlideOut,
    BtlCmd_Wait,
    BtlCmd_CalcDamage,
    BtlCmd_CalcDamageRaw,
    BtlCmd_PrintAttackMessage,
    BtlCmd_PrintMessage,
    BtlCmd_PrintGlobalMessage,
    BtlCmd_PrintBufferedMessage,
    BtlCmd_BufferMessage,
    BtlCmd_BufferLocalMessage,
    BtlCmd_PlayMoveAnimation,
    BtlCmd_PlayMoveAnimationOnMons,
    BtlCmd_FlickerMon,
    BtlCmd_UpdateHealthbarValue,
    BtlCmd_UpdateHealthbar,
    BtlCmd_TryFaintMon,
    BtlCmd_PlayFaintAnimation,
    BtlCmd_WaitButtonABTime,
    BtlCmd_PlaySound,
    BtlCmd_CompareVarToValue,
    BtlCmd_CompareMonDataToValue,
    BtlCmd_FadeOutBattle,
    BtlCmd_GoToSubscript,
    BtlCmd_GoToEffectScript,
    BtlCmd_GoToMoveScript,
    BtlCmd_CalcCrit,
    BtlCmd_CalcExpGain,
    BtlCmd_StartGetExpTask,
    BtlCmd_WaitGetExpTask,
    BtlCmd_WaitGetExpTaskLoop,
    BtlCmd_ShowParty,
    BtlCmd_WaitMonSelection,
    BtlCmd_SwitchAndUpdateMon,
    BtlCmd_GoToIfAnySwitches,
    BtlCmd_StartCatchMonTask,
    BtlCmd_WaitCatchMonTask,
    BtlCmd_SetMultiHit,
    BtlCmd_UpdateVar,
    BtlCmd_ChangeStatStage,
    BtlCmd_UpdateMonData,
    BtlCmd_ClearVolatileStatus,
    BtlCmd_ToggleVanish,
    BtlCmd_CheckAbility,
    BtlCmd_Random,
    BtlCmd_UpdateVar2,
    BtlCmd_UpdateMonDataFromVar,
    BtlCmd_Goto,
    BtlCmd_Call,
    BtlCmd_CallFromVar,
    BtlCmd_SetMirrorMove,
    BtlCmd_ResetAllStatChanges,
    BtlCmd_LockMoveChoice,
    BtlCmd_UnlockMoveChoice,
    BtlCmd_SetHealthbarStatus,
    BtlCmd_PrintTrainerMessage,
    BtlCmd_PayPrizeMoney,
    BtlCmd_PlayBattleAnimation,
    BtlCmd_PlayBattleAnimationOnMons,
    BtlCmd_PlayBattleAnimationFromVar,
    BtlCmd_PrintRecallMessage,
    BtlCmd_PrintSendOutMessage,
    BtlCmd_PrintEncounterMessage,
    BtlCmd_PrintFirstSendOutMessage,
    BtlCmd_PrintBufferedTrainerMessage,
    BtlCmd_TryConversion,
    BtlCmd_CompareVarToVar,
    BtlCmd_CompareMonDataToVar,
    BtlCmd_AddPayDayMoney,
    BtlCmd_TryLightScreen,
    BtlCmd_TryReflect,
    BtlCmd_TryMist,
    BtlCmd_TryOHKOMove,
    BtlCmd_DivideVarByValue,
    BtlCmd_DivideVarByVar,
    BtlCmd_TryMimic,
    BtlCmd_Metronome,
    BtlCmd_TryDisable,
    BtlCmd_Counter,
    BtlCmd_MirrorCoat,
    BtlCmd_TryEncore,
    BtlCmd_TryConversion2,
    BtlCmd_TrySketch,
    BtlCmd_TrySleepTalk,
    BtlCmd_CalcFlailPower,
    BtlCmd_TrySpite,
    BtlCmd_TryPartyStatusRefresh,
    BtlCmd_TryStealItem,
    BtlCmd_TryProtection,
    BtlCmd_TrySubstitute,
    BtlCmd_TryWhirlwind,
    BtlCmd_Transform,
    BtlCmd_TrySpikes,
    BtlCmd_CheckSpikes,
    BtlCmd_TryPerishSong,
    BtlCmd_GetTurnOrderBySpeed,
    BtlCmd_GoToIfValidMon,
    BtlCmd_EndOfTurnWeatherEffect,
    BtlCmd_CalcRolloutPower,
    BtlCmd_CalcFuryCutterPower,
    BtlCmd_TryAttract,
    BtlCmd_TrySafeguard,
    BtlCmd_Present,
    BtlCmd_CalcMagnitudePower,
    BtlCmd_TryReplaceFaintedMon,
    BtlCmd_RapidSpin,
    BtlCmd_WeatherHPRecovery,
    BtlCmd_CalcHiddenPowerParams,
    BtlCmd_CopyStatStages,
    BtlCmd_TryFutureSight,
    BtlCmd_CheckMoveHit,
    BtlCmd_TryTeleport,
    BtlCmd_BeatUp,
    BtlCmd_FollowMe,
    BtlCmd_TryHelpingHand,
    BtlCmd_TrySwapItems,
    BtlCmd_TryWish,
    BtlCmd_TryAssist,
    BtlCmd_TrySetMagicCoat,
    BtlCmd_MagicCoat,
    BtlCmd_CalcRevengeDamageMul,
    BtlCmd_TryBreakScreens,
    BtlCmd_TryYawn,
    BtlCmd_TryKnockOff,
    BtlCmd_CalcHPFalloffPower,
    BtlCmd_TryImprison,
    BtlCmd_TryGrudge,
    BtlCmd_TrySnatch,
    BtlCmd_CalcWeightBasedPower,
    BtlCmd_CalcWeatherBallParams,
    BtlCmd_TryPursuit,
    BtlCmd_ApplyTypeEffectiveness,
    BtlCmd_IfTurnFlag,
    BtlCmd_SetTurnFlag,
    BtlCmd_CalcGyroBallPower,
    BtlCmd_TryMetalBurst,
    BtlCmd_CalcPaybackPower,
    BtlCmd_CalcTrumpCardPower,
    BtlCmd_CalcWringOutPower,
    BtlCmd_TryMeFirst,
    BtlCmd_TryCopycat,
    BtlCmd_CalcPunishmentPower,
    BtlCmd_TrySuckerPunch,
    BtlCmd_CheckSideCondition,
    BtlCmd_TryFeint,
    BtlCmd_TryPyschoShift,
    BtlCmd_TryLastResort,
    BtlCmd_TryToxicSpikes,
    BtlCmd_CheckToxicSpikes,
    BtlCmd_CheckIgnorableAbility,
    BtlCmd_IfSameSide,
    BtlCmd_GenerateEndOfBattleItem,
    BtlCmd_TrickRoom,
    BtlCmd_IfMovedThisTurn,
    BtlCmd_CheckItemHoldEffect,
    BtlCmd_GetItemHoldEffect,
    BtlCmd_GetItemEffectParam,
    BtlCmd_TryCamouflage,
    BtlCmd_GetTerrainMove,
    BtlCmd_GetTerrainSecondaryEffect,
    BtlCmd_CalcNaturalGiftParams,
    BtlCmd_TryPluck,
    BtlCmd_TryFling,
    BtlCmd_YesNoMenu,
    BtlCmd_WaitYesNoResult,
    BtlCmd_ChoosePokemonMenu,
    BtlCmd_WaitPokemonMenuResult,
    BtlCmd_SetLinkBattleResult,
    BtlCmd_CheckStealthRock,
    BtlCmd_CheckEffectActivation,
    BtlCmd_CheckChatterActivation,
    BtlCmd_GetCurrentMoveData,
    BtlCmd_SetMosaic,
    BtlCmd_ChangeForm,
    BtlCmd_SetBattleBackground,
    BtlCmd_UseBagItem,
    BtlCmd_TryEscape,
    BtlCmd_ShowBattleStartPartyGauge,
    BtlCmd_HideBattleStartPartyGauge,
    BtlCmd_ShowPartyGauge,
    BtlCmd_HidePartyGauge,
    BtlCmd_LoadPartyGaugeGraphics,
    BtlCmd_FreePartyGaugeGraphics,
    BtlCmd_IncrementGameStat,
    BtlCmd_RestoreSprite,
    BtlCmd_TriggerAbilityOnHit,
    BtlCmd_SpriteToOAM,
    BtlCmd_OAMToSprite,
    BtlCmd_CheckWhiteout,
    BtlCmd_BoostRandomStatBy2,
    BtlCmd_RemoveItem,
    BtlCmd_TryRecycle,
    BtlCmd_CheckItemHoldEffectOnHit,
    BtlCmd_PrintBattleResultMessage,
    BtlCmd_PrintEscapeMessage,
    BtlCmd_PrintForfeitMessage,
    BtlCmd_CheckHoldOnWith1HP,
    BtlCmd_TryRestoreStatusOnSwitch,
    BtlCmd_CheckSubstitute,
    BtlCmd_CheckIgnoreWeather,
    BtlCmd_SetRandomTarget,
    BtlCmd_CheckItemHoldEffectOnUTurn,
    BtlCmd_RefreshSprite,
    BtlCmd_PlayMoveHitSound,
    BtlCmd_PlayBGM,
    BtlCmd_CheckSafariGameDone,
    BtlCmd_WaitTime,
    BtlCmd_CheckCurMoveIsType,
    BtlCmd_LoadArchivedMonData,
    BtlCmd_RefreshMonData,
    BtlCmd_222,
    BtlCmd_223,
    BtlCmd_EndScript,
};

// clang-format off
const u16 sPrizeMoneyTbl[258] = {
    TRAINERCLASS_PKMN_TRAINER_ETHAN, 0, TRAINERCLASS_PKMN_TRAINER_LYRA, 0,
    TRAINERCLASS_YOUNGSTER, 4, TRAINERCLASS_LASS, 4,
    TRAINERCLASS_CAMPER, 4, TRAINERCLASS_PICNICKER, 4,
    TRAINERCLASS_BUG_CATCHER, 4, TRAINERCLASS_AROMA_LADY, 8,
    TRAINERCLASS_TWINS, 4, TRAINERCLASS_HIKER, 8,
    TRAINERCLASS_BATTLE_GIRL, 4, TRAINERCLASS_FISHERMAN, 8,
    TRAINERCLASS_CYCLIST_M, 8, TRAINERCLASS_CYCLIST_F, 8,
    TRAINERCLASS_BLACK_BELT, 6, TRAINERCLASS_ARTIST, 12,
    TRAINERCLASS_PKMN_BREEDER_M, 12, TRAINERCLASS_PKMN_BREEDER_F, 12,
    TRAINERCLASS_COWGIRL, 4, TRAINERCLASS_JOGGER, 8,
    TRAINERCLASS_POKEFAN_M, 16, TRAINERCLASS_POKEFAN, 16,
    TRAINERCLASS_POKE_KID, 2, TRAINERCLASS_RIVAL, 16,
    TRAINERCLASS_ACE_TRAINER_M, 15, TRAINERCLASS_ACE_TRAINER_F, 15,
    TRAINERCLASS_WAITRESS, 8, TRAINERCLASS_VETERAN, 20,
    TRAINERCLASS_NINJA_BOY, 2, TRAINERCLASS_DRAGON_TAMER, 8,
    TRAINERCLASS_BIRD_KEEPER_GS, 8, TRAINERCLASS_JUGGLER, 8,
    TRAINERCLASS_RICH_BOY, 40, TRAINERCLASS_LADY, 40,
    TRAINERCLASS_GENTLEMAN, 50, TRAINERCLASS_SOCIALITE, 50,
    TRAINERCLASS_BEAUTY, 14, TRAINERCLASS_COLLECTOR, 16,
    TRAINERCLASS_POLICEMAN, 10, TRAINERCLASS_PKMN_RANGER_M, 15,
    TRAINERCLASS_PKMN_RANGER_F, 15, TRAINERCLASS_SCIENTIST, 12,
    TRAINERCLASS_SWIMMER_M, 4, TRAINERCLASS_SWIMMER_F, 4,
    TRAINERCLASS_TUBER_M, 1, TRAINERCLASS_TUBER_F, 1,
    TRAINERCLASS_SAILOR, 8, TRAINERCLASS_KIMONO_GIRL, 30,
    TRAINERCLASS_RUIN_MANIAC, 12, TRAINERCLASS_PSYCHIC_M, 8,
    TRAINERCLASS_PSYCHIC_F, 8, TRAINERCLASS_PI, 30,
    TRAINERCLASS_GUITARIST, 6, TRAINERCLASS_ACE_TRAINER_M_GS, 15,
    TRAINERCLASS_ACE_TRAINER_F_GS, 15, TRAINERCLASS_TEAM_ROCKET, 10,
    TRAINERCLASS_SKIER, 8, TRAINERCLASS_ROUGHNECK, 6,
    TRAINERCLASS_CLOWN, 6, TRAINERCLASS_WORKER, 10,
    TRAINERCLASS_SCHOOL_KID_M, 5, TRAINERCLASS_SCHOOL_KID_F, 5,
    TRAINERCLASS_TEAM_ROCKET_F, 10, TRAINERCLASS_BURGLAR, 4,
    TRAINERCLASS_FIREBREATHER, 8, TRAINERCLASS_BIKER, 4,
    TRAINERCLASS_LEADER_FALKNER, 30, TRAINERCLASS_LEADER_BUGSY, 30,
    TRAINERCLASS_POKE_MANIAC, 16, TRAINERCLASS_LEADER_WHITNEY, 30,
    TRAINERCLASS_LEADER_MORTY, 30, TRAINERCLASS_RANCHER, 10,
    TRAINERCLASS_LEADER_PRYCE, 30, TRAINERCLASS_LEADER_JASMINE, 30,
    TRAINERCLASS_LEADER_CHUCK, 30, TRAINERCLASS_LEADER_CLAIR, 30,
    TRAINERCLASS_TEACHER, 12, TRAINERCLASS_SUPER_NERD, 12,
    TRAINERCLASS_SAGE, 12, TRAINERCLASS_MEDIUM, 12,
    TRAINERCLASS_PARASOL_LADY, 8, TRAINERCLASS_WAITER, 8,
    TRAINERCLASS_CHAMPION, 50, TRAINERCLASS_CAMERAMAN, 8,
    TRAINERCLASS_REPORTER, 10, TRAINERCLASS_IDOL, 18,
    TRAINERCLASS_ELITE_FOUR_WILL, 30, TRAINERCLASS_ELITE_FOUR_KAREN, 30,
    TRAINERCLASS_ELITE_FOUR_KOGA, 30, TRAINERCLASS_LEADER_BROCK, 30,
    TRAINERCLASS_PKMN_TRAINER_CHERYL, 30, TRAINERCLASS_PKMN_TRAINER_RILEY, 30,
    TRAINERCLASS_PKMN_TRAINER_BUCK, 30, TRAINERCLASS_PKMN_TRAINER_MIRA, 30,
    TRAINERCLASS_PKMN_TRAINER_MARLEY, 30, TRAINERCLASS_PKMN_TRAINER_FTR_LUCAS, 25,
    TRAINERCLASS_PKMN_TRAINER_FTR_DAWN, 25, TRAINERCLASS_TOWER_TYCOON, 0,
    TRAINERCLASS_LEADER_MISTY, 30, TRAINERCLASS_HALL_MATRON, 0,
    TRAINERCLASS_FACTORY_HEAD, 0, TRAINERCLASS_ARCADE_STAR, 0,
    TRAINERCLASS_CASTLE_VALET, 0, TRAINERCLASS_LEADER_LT_SURGE, 30,
    TRAINERCLASS_LEADER_ERIKA, 30, TRAINERCLASS_LEADER_JANINE, 30,
    TRAINERCLASS_LEADER_SABRINA, 30, TRAINERCLASS_LEADER_BLAINE, 30,
    TRAINERCLASS_PKMN_TRAINER_RED, 50, TRAINERCLASS_LEADER_BLUE, 40,
    TRAINERCLASS_ELDER, 30, TRAINERCLASS_ELITE_FOUR_BRUNO, 30,
    TRAINERCLASS_SCIENTIST_GS, 8, TRAINERCLASS_EXECUTIVE_ARIANA, 20,
    TRAINERCLASS_BOARDER, 8, TRAINERCLASS_EXECUTIVE_ARCHER, 20,
    TRAINERCLASS_EXECUTIVE_PROTON, 10, TRAINERCLASS_EXECUTIVE_PETREL, 10,
    TRAINERCLASS_PASSERBY, 25, TRAINERCLASS_MYSTERY_MAN, 30,
    TRAINERCLASS_DOUBLE_TEAM, 30, TRAINERCLASS_YOUNG_COUPLE, 16,
    TRAINERCLASS_PKMN_TRAINER_LANCE, 0, TRAINERCLASS_ROCKET_BOSS, 45,
    TRAINERCLASS_PKMN_TRAINER_LUCAS_DP, 0, TRAINERCLASS_PKMN_TRAINER_DAWN_DP, 0,
    TRAINERCLASS_PKMN_TRAINER_LUCAS_PT, 0, TRAINERCLASS_PKMN_TRAINER_DAWN_PT, 0,
    TRAINERCLASS_BIRD_KEEPER, 8,
};
// clang-format on

const struct {
    u16 unk0[4];
    s32 unk8[11];
} sLevelUpNameplateTemplate = {
    { 0x80, 0x00, 0x00, 0 },
    { 200, 0, 1, 20021, 20016, 20013, 20013, -1, -1, 1, 0 },
};

const struct {
    u16 unk0[4];
    s32 unk8[11];
} sPokeIconTemplate = {
    { 0x98, 0x18, 0x00, 0 },
    { 100, 0, 1, 20022, 20017, 20014, 20014, -1, -1, 1, 0 }
};

// C declares this non-const, but it lives in .rodata
// clang-format off
const u32 sSecretPowerEffectTable[13] = {
    0x8000001B, 0x8000001B, 0x80000001, 0x80000001, 0x80000008, 0x80000008, 0x80000004, 0x80000016,
    0x80000004, 0x80000005, 0x80000018, 0x8000001C, 0x80000005,
};
// clang-format on

// clang-format off
const u16 sPickupTable1[18] = {
    ITEM_POTION, ITEM_ANTIDOTE, ITEM_SUPER_POTION, ITEM_GREAT_BALL, ITEM_REPEL, ITEM_ESCAPE_ROPE,
    ITEM_FULL_HEAL, ITEM_HYPER_POTION, ITEM_ULTRA_BALL, ITEM_REVIVE, ITEM_RARE_CANDY, ITEM_SUN_STONE,
    ITEM_MOON_STONE, ITEM_HEART_SCALE, ITEM_FULL_RESTORE, ITEM_MAX_REVIVE, ITEM_PP_UP, ITEM_MAX_ELIXIR,
};
// clang-format on

// C declares this non-const, but it lives in .rodata
// clang-format off
const u16 sMoonBallPokemon[14] = {
    SPECIES_NIDORAN_F, SPECIES_NIDORINA, SPECIES_NIDOQUEEN, SPECIES_NIDORAN_M, SPECIES_NIDORINO,
    SPECIES_NIDOKING, SPECIES_CLEFFA, SPECIES_CLEFAIRY, SPECIES_CLEFABLE, SPECIES_IGGLYBUFF,
    SPECIES_JIGGLYPUFF, SPECIES_WIGGLYTUFF, SPECIES_SKITTY, SPECIES_DELCATTY,
};
// clang-format on

// Numerator, Denominator
// C declares this non-const, but it lives in .rodata
const u8 sSafariCatchRateStages[13][2] = {
    { 10, 40 },
    { 10, 35 },
    { 10, 30 },
    { 10, 25 },
    { 10, 20 },
    { 10, 15 },
    { 10, 10 },
    { 15, 10 },
    { 20, 10 },
    { 25, 10 },
    { 30, 10 },
    { 35, 10 },
    { 40, 10 },
};

// C declares this non-const, but it lives in .rodata
// clang-format off
const u16 sNaturePowerMoveTable[13] = {
    MOVE_EARTHQUAKE, MOVE_EARTHQUAKE, MOVE_SEED_BOMB, MOVE_SEED_BOMB, MOVE_ROCK_SLIDE, MOVE_ROCK_SLIDE,
    MOVE_BLIZZARD, MOVE_HYDRO_PUMP, MOVE_ICE_BEAM, MOVE_TRI_ATTACK, MOVE_MUD_BOMB, MOVE_AIR_SLASH,
    MOVE_TRI_ATTACK,
};
// clang-format on

// clang-format off
static const u32 ov12_0226C324[6] = {
    NUM_BATTLE_STATS, STAT_ATK,
    STAT_DEF, STAT_SPATK,
    STAT_SPDEF, STAT_SPEED,
};
// clang-format on

// clang-format off
const u32 sLevelUpNewStatParams[6] = {
    MON_DATA_MAX_HP, MON_DATA_ATK,
    MON_DATA_DEF, MON_DATA_SP_ATK,
    MON_DATA_SP_DEF, MON_DATA_SPEED,
};
// clang-format on

// clang-format off
const u32 sLevelUpOldStatParams[6] = {
    MON_DATA_MAX_HP, MON_DATA_ATK,
    MON_DATA_DEF, MON_DATA_SP_ATK,
    MON_DATA_SP_DEF, MON_DATA_SPEED,
};
// clang-format on

// clang-format off
const u32 sLevelUpStatNameParams[6] = {
    NUM_BATTLE_STATS, STAT_ATK,
    STAT_DEF, STAT_SPATK,
    STAT_SPDEF, STAT_SPEED,
};
// clang-format on

// clang-format off
const u32 sLevelUpDiffStatParams[6] = {
    MON_DATA_MAX_HP, MON_DATA_ATK,
    MON_DATA_DEF, MON_DATA_SP_ATK,
    MON_DATA_SP_DEF, MON_DATA_SPEED,
};
// clang-format on

// C declares this non-const, but it lives in .rodata
const u16 sLowKickDamageTable[6][2] = {
    { 100,    20     },
    { 250,    40     },
    { 500,    60     },
    { 1000,   80     },
    { 2000,   100    },
    { 0xFFFF, 0xFFFF },
};

// clang-format off
const u16 sPickupTable2[11] = {
    ITEM_HYPER_POTION, ITEM_NUGGET, ITEM_KINGS_ROCK, ITEM_FULL_RESTORE, ITEM_ETHER, ITEM_IRON_BALL, ITEM_TM56,
    ITEM_ELIXIR, ITEM_TM86, ITEM_LEFTOVERS, ITEM_TM26,
};
// clang-format on

// clang-format off
const u8 sCamouflageTypeTable[13] __attribute__((aligned(4))) = {
    TYPE_GROUND, TYPE_GROUND, TYPE_GRASS, TYPE_GRASS, TYPE_ROCK, TYPE_ROCK, TYPE_ICE, TYPE_WATER, TYPE_ICE,
    TYPE_NORMAL, TYPE_GROUND, TYPE_FLYING, TYPE_NORMAL,
};
// clang-format on

// First byte: HP threshold as 64ths of max
// Second byte: Damage value
// C declares this non-const, but it lives in .rodata
const u8 sFlailDamageTable[6][2] = {
    { 1,  200 },
    { 5,  150 },
    { 12, 100 },
    { 21, 80  },
    "*(",
    { 64, 20  },
};

const u8 sHoneyGatherChanceTable[10] __attribute__((aligned(4))) = { 5, 10, 15, 20, 25, 30, 35, 40, 45, 50 };

const u8 sPickupWeightTable[9] = { 30, 40, 50, 60, 70, 80, 90, 94, 98 };

// C declares this non-const, but it lives in .rodata
const u8 sTrumpCardPowerTable[8] = { 200, 80, 60, 50, 40, 0, 0, 0 };

// C declares this non-const, but it lives in .rodata
const u16 sProtectSuccessChance[4] = { 0xFFFF, 0x7FFF, 0x3FFF, 0x1FFF };

// C declares this non-const, but it lives in .rodata
const u8 sStandardBallCatchRates[4] __attribute__((aligned(4))) = { 20, 15, 10, 15 };
