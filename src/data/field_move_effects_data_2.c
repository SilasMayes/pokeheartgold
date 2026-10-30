// Converted from asm/field_move_effects_data.s (part 2 of 6) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

#include "global.h"

#include "constants/abilities.h"
#include "constants/items.h"
#include "constants/pokemon.h"
#include "constants/sndseq.h"
#include "constants/species.h"
#include "constants/std_script.h"

#include "field/field_move_cut_in.h"
#include "field/field_move_effects.h"
#include "field/fly_landing_effect.h"

#pragma force_active on

extern void CutInFlyer_Destroy(void);
extern void CutInFlyer_Done(void);
extern void CutInFlyer_Draw(void);
extern void CutInFlyer_FlyAway(void);
extern void CutInFlyer_Init(void);
extern void CutInFlyer_PickUpTrainer(void);
extern void CutInFlyer_SwoopDown(void);
extern void CutInFlyer_Update(void);
extern void CutInModelEffect_Destroy(void);
extern void CutInModelEffect_Draw(void);
extern void CutInModelEffect_Init(void);
extern void CutInModelEffect_Update(void);
extern void CutInScrollSprite_Destroy(void);
extern void CutInScrollSprite_Draw(void);
extern void CutInScrollSprite_Init(void);
extern void CutInScrollSprite_Update(void);
extern void FieldMoveCutIn_StepShowOtherObject(void);
extern void FieldMoveCutIn_StepWaitModelEffect(void);
extern void FlyLanding_CreateSprites(void);
extern void FlyLanding_FreeGraphics(void);
extern void FlyLanding_Idle(void);
extern void FlyLanding_LoadGraphics(void);
extern void FlyLanding_SetPlayerVisible(void);
extern void FlyLanding_WaitLanding(void);
extern void TrainerClipEffect_Init(void);
extern void TrainerClipEffect_Update(void);
extern void TrainerJumpEffect_Init(void);
extern void TrainerJumpEffect_Update(void);

struct sCutInFlyerHideSteps_Layout {
    void (*unk0)(void);
};
struct sCutInFlyerTakeOffSteps_Layout {
    void (*unk0)(void);
    void (*unk4)(void);
    u32 unk8[2];
    u8 unk10[8];
};
extern const struct sCutInFlyerHideSteps_Layout sCutInFlyerHideSteps;
extern const struct sCutInFlyerTakeOffSteps_Layout sCutInFlyerTakeOffSteps;

// clang-format off
const u8 gCutInScrollSpriteTemplates[260] = {
    0x00, 0xF0, 0x00, 0x00, 0x00, 0xF0, 0x03, 0x00, 0x00, 0x00, 0x01, 0x00, 0x85, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x04, 0x00, 0x00, 0x30, 0x04, 0x00, 0x00, 0x00, 0x01, 0x00,
    0x85, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0xD0, 0x03, 0x00,
    0x00, 0x80, 0x01, 0x00, 0x80, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x00,
    0x00, 0x50, 0x04, 0x00, 0x00, 0x00, 0x01, 0x00, 0x85, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x80, 0x02, 0x00, 0x00, 0xE0, 0x04, 0x00, 0x00, 0x80, 0x01, 0x00, 0x80, 0x00, 0x00, 0x00,
    0x01, 0x00, 0x00, 0x00, 0x00, 0x80, 0x04, 0x00, 0x00, 0xB0, 0x05, 0x00, 0x00, 0x00, 0x01, 0x00,
    0x85, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0D, 0x00, 0x00, 0x60, 0x05, 0x00,
    0x00, 0x80, 0x01, 0x00, 0x80, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x80, 0x03, 0x00,
    0x00, 0x40, 0x07, 0x00, 0x00, 0x00, 0x01, 0x00, 0x85, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0xF0, 0x05, 0x00, 0x00, 0xD0, 0x06, 0x00, 0x00, 0x80, 0x01, 0x00, 0x80, 0x00, 0x00, 0x00,
    0x01, 0x00, 0x00, 0x00, 0x00, 0xF0, 0x09, 0x00, 0x00, 0x40, 0x06, 0x00, 0x00, 0x00, 0x01, 0x00,
    0x85, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x01, 0x00, 0x00, 0xE0, 0x07, 0x00,
    0x00, 0x80, 0x01, 0x00, 0x80, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x08, 0x00,
    0x00, 0xD0, 0x07, 0x00, 0x00, 0x80, 0x01, 0x00, 0x80, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
    0x00, 0xD0, 0x0D, 0x00, 0x00, 0xC0, 0x07, 0x00, 0x00, 0x80, 0x01, 0x00, 0x80, 0x00, 0x00, 0x00,
    0x01, 0x00, 0x00, 0x00,
};
// clang-format on

void (*const gFieldMoveCutInFlySteps[23])(void) = {
    (void (*)(void))FieldMoveCutIn_StepLoadBannerGraphics,
    (void (*)(void))FieldMoveCutIn_StepCreateFlySprites,
    (void (*)(void))FieldMoveCutIn_StepInitWindow,
    (void (*)(void))FieldMoveCutIn_StepWidenWindow,
    (void (*)(void))FieldMoveCutIn_StepOpenWindow,
    (void (*)(void))FieldMoveCutIn_StepWaitBeforeMon,
    (void (*)(void))FieldMoveCutIn_StepMonSlideIn,
    (void (*)(void))FieldMoveCutIn_StepMonSlowDown,
    (void (*)(void))FieldMoveCutIn_StepWaitBeforeMonExit,
    (void (*)(void))FieldMoveCutIn_StepMonSlideOut,
    (void (*)(void))FieldMoveCutIn_StepFreeMonGraphics,
    (void (*)(void))FieldMoveCutIn_StepLoadFlyGraphics,
    (void (*)(void))FieldMoveCutIn_StepWaitFlyGraphics,
    (void (*)(void))FieldMoveCutIn_StepStartFly,
    (void (*)(void))FieldMoveCutIn_StepWaitTakeOff,
    (void (*)(void))FieldMoveCutIn_StepWaitBeforeFlyAway,
    (void (*)(void))FieldMoveCutIn_StepWaitFlyAway,
    (void (*)(void))FieldMoveCutIn_StepCloseFlyWindow,
    (void (*)(void))FieldMoveCutIn_StepWaitFlyEnd,
    (void (*)(void))FieldMoveCutIn_StepWaitPaletteFade,
    (void (*)(void))FieldMoveCutIn_StepFreeBannerGraphics,
    (void (*)(void))FieldMoveCutIn_StepEndWindow,
    (void (*)(void))FieldMoveCutIn_StepFinish,
};

void (*const gFieldMoveCutInSteps[14])(void) = {
    (void (*)(void))FieldMoveCutIn_StepLoadBannerGraphics,
    (void (*)(void))FieldMoveCutIn_StepCreateSprites,
    (void (*)(void))FieldMoveCutIn_StepInitWindow,
    (void (*)(void))FieldMoveCutIn_StepWidenWindow,
    (void (*)(void))FieldMoveCutIn_StepOpenWindow,
    (void (*)(void))FieldMoveCutIn_StepWaitBeforeMon,
    (void (*)(void))FieldMoveCutIn_StepMonSlideIn,
    (void (*)(void))FieldMoveCutIn_StepMonSlowDown,
    (void (*)(void))FieldMoveCutIn_StepWaitBeforeMonExit,
    (void (*)(void))FieldMoveCutIn_StepMonSlideOut,
    (void (*)(void))FieldMoveCutIn_StepCloseWindow,
    (void (*)(void))FieldMoveCutIn_StepFreeBannerGraphics,
    (void (*)(void))FieldMoveCutIn_StepEndWindow,
    (void (*)(void))FieldMoveCutIn_StepFinish,
};

void (*const gFieldMoveCutInFlyWithObjectSteps[12])(void) = {
    (void (*)(void))FieldMoveCutIn_StepLoadSpriteGraphics,
    (void (*)(void))FieldMoveCutIn_StepCreateFlyTrainerSprite,
    FieldMoveCutIn_StepShowOtherObject,
    FieldMoveCutIn_StepWaitModelEffect,
    (void (*)(void))FieldMoveCutIn_StepLoadFlyGraphics,
    (void (*)(void))FieldMoveCutIn_StepWaitFlyGraphics,
    (void (*)(void))FieldMoveCutIn_StepWaitBeforePickUp,
    (void (*)(void))FieldMoveCutIn_StepWaitFlyAway,
    (void (*)(void))FieldMoveCutIn_StepWaitFlyEnd,
    (void (*)(void))FieldMoveCutIn_StepWaitPaletteFade,
    (void (*)(void))FieldMoveCutIn_StepFreeSpriteGraphics,
    (void (*)(void))FieldMoveCutIn_StepFinish,
};

// clang-format off
const fx32 gTrainerJumpOffsets[12] = {
    -49152, -65536, -81920, -98304, -106496, -114688, -114688, -114688, -106496, -98304, -90112, -81920,
};
// clang-format on

// clang-format off
void (*const sFlyLandingSteps[8])(void) = {
    (void (*)(void))FlyLandingEffect_SwoopIn, (void (*)(void))FlyLandingEffect_StartClimb,
    (void (*)(void))FlyLandingEffect_Climb, (void (*)(void))FlyLandingEffect_HideFlyer,
    (void (*)(void))FlyLandingEffect_StartFlyAway, (void (*)(void))FlyLandingEffect_FlyAway,
    (void (*)(void))FlyLandingEffect_ShowPlayer, (void (*)(void))FlyLandingEffect_Done,
};
// clang-format on

void (*const gFlyLandingTaskSteps[6])(void) = {
    FlyLanding_SetPlayerVisible,
    FlyLanding_LoadGraphics,
    FlyLanding_CreateSprites,
    FlyLanding_WaitLanding,
    FlyLanding_FreeGraphics,
    FlyLanding_Idle,
};

// clang-format off
const FieldEffectBasicTemplate gTrainerClipEffectTemplate = {
    8, (FieldEffectInitFunc)TrainerClipEffect_Init, FieldEffect_DefaultDestroy,
    (FieldEffectFunc)TrainerClipEffect_Update, FieldEffect_DefaultDraw,
};
// clang-format on

// clang-format off
const FieldEffectBasicTemplate gFlyLandingEffectTemplate = {
    0x00000074, (FieldEffectInitFunc)FlyLandingEffect_Init, (FieldEffectFunc)FlyLandingEffect_Destroy,
    (FieldEffectFunc)FlyLandingEffect_Update, (FieldEffectFunc)FieldEffect_DefaultDraw,
};
// clang-format on

// clang-format off
const FieldEffectBasicTemplate gCutInScrollSpriteEffectTemplate = {
    0x00000024, (FieldEffectInitFunc)CutInScrollSprite_Init, (FieldEffectFunc)CutInScrollSprite_Destroy,
    (FieldEffectFunc)CutInScrollSprite_Update, (FieldEffectFunc)CutInScrollSprite_Draw,
};
// clang-format on

// clang-format off
const FieldEffectBasicTemplate gCutInFlyerEffectTemplate = {
    0x00000068, (FieldEffectInitFunc)CutInFlyer_Init, (FieldEffectFunc)CutInFlyer_Destroy,
    (FieldEffectFunc)CutInFlyer_Update, (FieldEffectFunc)CutInFlyer_Draw,
};
// clang-format on

// clang-format off
const FieldEffectBasicTemplate gCutInModelEffectTemplate = {
    0x0000000C, (FieldEffectInitFunc)CutInModelEffect_Init, (FieldEffectFunc)CutInModelEffect_Destroy,
    (FieldEffectFunc)CutInModelEffect_Update, (FieldEffectFunc)CutInModelEffect_Draw,
};
// clang-format on

// clang-format off
const FieldEffectBasicTemplate gTrainerJumpEffectTemplate = {
    0x00000024, (FieldEffectInitFunc)TrainerJumpEffect_Init, FieldEffect_DefaultDestroy,
    (FieldEffectFunc)TrainerJumpEffect_Update, FieldEffect_DefaultDraw,
};
// clang-format on

void (*const sCutInFlyerPickUpSteps[4])(void) = {
    CutInFlyer_SwoopDown,
    CutInFlyer_PickUpTrainer,
    CutInFlyer_FlyAway,
    CutInFlyer_Done,
};

const fx32 gTrainerHopOffsets[4] = { -16384, -24576, -28672, -32768 };

const VecFx32 gCutInTrainerPos = { 524288, 393216, 0 };

const VecFx32 gCutInFlyTrainerPos = { 524288, 393216, 0 };

const VecFx32 gCutInFlyerTrainerScale = { 4096, 4096, 0 };

const VecFx32 gFlyLandingFlyAwayCenter = { 557056, 323584, 0 };

const VecFx32 gFlyLandingFlyerScale = { 4096, 4096, 0 };

const VecFx32 gFlyLandingFlyAwayScale = { 4096, 4096, 0 };

const VecFx32 gFlyLandingSwoopScale = { 8192, 8192, 0 };

const VecFx32 gCutInFlyerPickUpPos = { 524288, 425984, 0 };

const VecFx32 gCutInFlyerPickUpScale = { 5120, 5120, 0 };

const VecFx32 gCutInFlyMonPos = { 1212416, 393216, 0 };

const VecFx32 gCutInFlyerTakeOffOrigin = { 557056, 360448, 0 };

const VecFx32 gCutInMonPos = { 1212416, 393216, 0 };

const VecFx32 gFlyLandingTrainerScale = { 8192, 8192, 0 };

const VecFx32 gCutInFlyWithObjectTrainerPos = { 524288, 344064, 0 };

const VecFx32 gCutInFlyerTakeOffScale = { 1024, 1024, 0 };

const void *const gCutInFlyerModeSteps[3] = {
    &sCutInFlyerHideSteps,
    &sCutInFlyerTakeOffSteps,
    sCutInFlyerPickUpSteps,
};

const VecFx32 gCutInFlyerScale = { 4096, 4096, 0 };

const VecFx32 gFlyLandingSwoopCenter = { 524288, 454656, 0 };
