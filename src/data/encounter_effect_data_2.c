// Converted from asm/encounter_effect_data.s (part 2 of 3) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

#include <nitro/fs/overlay.h>

#include "global.h"

#include "field/encounter_effect.h"

#pragma force_active on

extern void EncounterEffect_HoOh(void);
extern void EncounterEffect_Legendary(void);
extern void EncounterEffect_Lugia(void);

// clang-format off
void (*const gEncounterEffectFuncs[47])(SysTask *task, EncounterEffectTask *effect) = {
    EncounterEffect_WildRowsWhite, EncounterEffect_WildRowsBlack, EncounterEffect_WildWaveWhite,
    EncounterEffect_WildWaveBlack, EncounterEffect_WildDiagonalsWhite, EncounterEffect_WildDiagonalsBlack,
    EncounterEffect_TrainerSpinApart, EncounterEffect_TrainerSpinZoom, EncounterEffect_TrainerBallDrop,
    EncounterEffect_TrainerFadeSpin, EncounterEffect_TrainerBallFall, EncounterEffect_TrainerRisingBall,
    EncounterEffect_LeaderFalkner, EncounterEffect_LeaderBugsy, EncounterEffect_LeaderWhitney,
    EncounterEffect_LeaderMorty, EncounterEffect_LeaderJasmine, EncounterEffect_LeaderChuck,
    EncounterEffect_LeaderPryce, EncounterEffect_LeaderClair, EncounterEffect_LeaderBrock,
    EncounterEffect_LeaderMisty, EncounterEffect_LeaderLtSurge, EncounterEffect_LeaderErika,
    EncounterEffect_LeaderJanine, EncounterEffect_LeaderSabrina, EncounterEffect_LeaderBlaine,
    EncounterEffect_LeaderBlue, EncounterEffect_Rival, EncounterEffect_EliteFourWill,
    EncounterEffect_EliteFourKoga, EncounterEffect_EliteFourBruno, EncounterEffect_EliteFourKaren,
    EncounterEffect_Champion, (void (*)(SysTask *, EncounterEffectTask *))EncounterEffect_Legendary,
    (void (*)(SysTask *, EncounterEffectTask *))EncounterEffect_HoOh,
    (void (*)(SysTask *, EncounterEffectTask *))EncounterEffect_Lugia, EncounterEffect_FrontierOrLinkSingle,
    EncounterEffect_Double, EncounterEffect_TeamRocket, EncounterEffect_ExecutivePetrel,
    EncounterEffect_ExecutiveProton, EncounterEffect_ExecutiveArcher, EncounterEffect_ExecutiveAriana,
    EncounterEffect_RocketBoss, EncounterEffect_KimonoGirl, EncounterEffect_PkmnTrainerRed,
};
// clang-format on

// clang-format off
const GraphicsBanks gParticleGraphicsBanks = {
    GX_VRAM_BG_256_BC, GX_VRAM_BGEXTPLTT_NONE, GX_VRAM_SUB_BG_32_H, GX_VRAM_SUB_BGEXTPLTT_NONE,
    GX_VRAM_OBJ_16_F, GX_VRAM_OBJEXTPLTT_NONE, GX_VRAM_SUB_OBJ_16_I, GX_VRAM_SUB_OBJEXTPLTT_NONE,
    GX_VRAM_TEX_0_A, GX_VRAM_TEXPLTT_0123_E,
};
// clang-format on
