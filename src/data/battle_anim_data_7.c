// Converted from asm/battle_anim_data.s (part 7 of 17) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

#include "global.h"

#include "battle/battle_anim_ball.h"
#include "battle/battle_anim_battler_util.h"
#include "battle/battle_anim_effects.h"
#include "battle/battle_anim_emitter.h"
#include "battle/battle_anim_funcs.h"
#include "battle/battle_anim_internal.h"
#include "battle/battle_anim_move_effects.h"
#include "battle/battle_anim_util.h"

#pragma force_active on

// clang-format off
const BattleAnimFunc gBattleAnimFuncTable[84] = {
    BattleAnimFunc_None, BattleAnimFunc_OneFrameTask, BattleAnimFunc_OneFrameSoundTask,
    BattleAnimFunc_OneFrameUncountedTask, BattleAnimFunc_RotateBattler, BattleAnimFunc_AttackerGrowFlashRed,
    BattleAnimFunc_AttackerSquashStretch, BattleAnimFunc_AttackerAfterimages, BattleAnimFunc_PicOrbit,
    BattleAnimFunc_AttackerRecoilTilt, BattleAnimFunc_CircleBattler, BattleAnimFunc_ShakeDefenderWithOverlay,
    BattleAnimFunc_SkewSlideAttackerBg, BattleAnimFunc_AttackerPulseWhite,
    BattleAnimFunc_AttackerStretchSteps, BattleAnimFunc_AttackerLeapOffscreen,
    BattleAnimFunc_AttackerSilhouette, BattleAnimFunc_FadeInShrinkSprite,
    BattleAnimFunc_ShakeDefenderBlackFlash, BattleAnimFunc_AttackerHop, BattleAnimFunc_WaveDefenderOnBg,
    BattleAnimFunc_ShowAttackerObjWindowSprites, BattleAnimFunc_AttackerSquashAfterimages,
    BattleAnimFunc_AttackerCircleFade, BattleAnimFunc_ShakeBattlefieldFlashing, BattleAnimFunc_WaddlePic,
    BattleAnimFunc_SpriteDriftFade, BattleAnimFunc_RockOrShakeAttacker,
    BattleAnimFunc_ShakeBattlefieldByPower, BattleAnimFunc_AttackerDip, BattleAnimFunc_AttackerLungeKnockback,
    BattleAnimFunc_AttackerStretchUp, BattleAnimFunc_DarkSpriteJump, BattleAnimFunc_FadeBgPalette,
    BattleAnimFunc_BattlerPaletteFade, BattleAnimFunc_PulseBattlerSprite, BattleAnimFunc_ShakeTargets,
    BattleAnimFunc_WobbleDefenderOnBg, BattleAnimFunc_BlendBattlerSprites, BattleAnimFunc_ShakeSpritePair,
    BattleAnimFunc_SetBattlerVanished, BattleAnimFunc_WindowSweepFlashWhite, BattleAnimFunc_StretchBattler,
    BattleAnimFunc_StretchShakeDefender, BattleAnimFunc_SlidingBg, BattleAnimFunc_SlidingBg2,
    BattleAnimFunc_ShootSpriteFromAttacker, BattleAnimFunc_AttackerShakeLunge,
    BattleAnimFunc_DefenderKnockback, BattleAnimFunc_StretchFadeSprite, BattleAnimFunc_BlinkBattler,
    BattleAnimFunc_SlideBattler, BattleAnimFunc_SlideBattler2, BattleAnimFunc_ShakeAndScaleBattler,
    BattleAnimFunc_ShakeAndScaleBattlerXY, BattleAnimFunc_WaveAttackerOnBg,
    BattleAnimFunc_ShowBattleBgInObjWindow, BattleAnimFunc_MoveBattlerBy,
    BattleAnimFunc_ShrinkSpriteOnDefender, BattleAnimFunc_AttackerDashAfterimages,
    BattleAnimFunc_MoveBattlerSin, BattleAnimFunc_MoveBattlerLinear, BattleAnimFunc_ResetBattlerPosition,
    BattleAnimFunc_BlendSpritePalette, BattleAnimFunc_ChangeBattlerHeight, BattleAnimFunc_MoveEmitter,
    BattleAnimFunc_MoveEmitterArc, BattleAnimFunc_RevealBattler, BattleAnimFunc_ShakeBg,
    BattleAnimFunc_SpriteMosaic, BattleAnimFunc_SquashSprite, BattleAnimFunc_SlideOutAndTransform,
    BattleAnimFunc_EmitterSinMotion, BattleAnimFunc_MoveEmitterVertical, BattleAnimFunc_SetBgPaletteGrayscale,
    BattleAnimFunc_DropSpriteStepwise, BattleAnimFunc_BattleBgWave, BattleAnimFunc_MoveBattlerOffscreen,
    BattleAnimFunc_AnimateSprites, BattleAnimFunc_WipeOutDefender, BattleAnimFunc_ObjWindowBgScrollUp,
    BattleAnimFunc_ObjWindowBgScrollDown, BattleAnimFunc_ObjWindowBgScrollUpAlt,
    BattleAnimFunc_ObjWindowBgScrollDownFast,
};
// clang-format on

// clang-format off
const BattleAnimSpriteFunc gBattleAnimSpriteFuncTable[33] = {
    BattleAnimSpriteFunc_SpreadSpriteCopies, BattleAnimSpriteFunc_BlinkScaleFadeSprites,
    BattleAnimSpriteFunc_OrbitingSpriteTrail, BattleAnimSpriteFunc_CrossingSprites,
    BattleAnimSpriteFunc_GrowRockShrinkSprite, BattleAnimSpriteFunc_StackedSpritesOnDefender,
    BattleAnimSpriteFunc_BoomerangSprite, BattleAnimSpriteFunc_RisingSpriteStretchAttacker,
    BattleAnimSpriteFunc_ZigzagSlash, BattleAnimSpriteFunc_ZigzagFlash, BattleAnimSpriteFunc_SpritePops,
    BattleAnimSpriteFunc_PulseSpriteBrightnessFlash, BattleAnimSpriteFunc_FanSpritesAroundAttacker,
    BattleAnimSpriteFunc_ShrinkAttackerIntoSprite, BattleAnimSpriteFunc_ScaleSpritesOverDefender,
    BattleAnimSpriteFunc_SpritesOrbitAttackerBobbing, BattleAnimSpriteFunc_FloatingSpriteStream,
    BattleAnimSpriteFunc_ThrowSpriteArc, BattleAnimSpriteFunc_FadeSpriteAnim,
    BattleAnimSpriteFunc_BlinkSpritesCenter, BattleAnimSpriteFunc_SlidingSpritePairs,
    BattleAnimSpriteFunc_PopAndScatterSprites, BattleAnimSpriteFunc_SpriteQuad,
    BattleAnimSpriteFunc_FlashingSpritesAroundAttacker, BattleAnimSpriteFunc_SpriteTrailToDefender,
    BattleAnimSpriteFunc_MoveSpriteAndAnimate, BattleAnimSpriteFunc_SpriteOrbit,
    BattleAnimSpriteFunc_SpriteAboveDefender, BattleAnimSpriteFunc_SpriteArc,
    BattleAnimSpriteFunc_RisingShrinkSprites, BattleAnimSpriteFunc_SpriteRowSequence,
    BattleAnimSpriteFunc_PaletteCycleSprite, BattleAnimSpriteFunc_SpritesOrbitAttacker,
};
// clang-format on

// zero bytes after gBattleAnimBattlerScreenPositions in the asm
static const u8 gBattleAnimBattlerScreenPositions_pad[4] = { 0 };
