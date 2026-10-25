#ifndef POKEHEARTGOLD_BATTLE_BATTLE_ANIM_MOVE_EFFECTS_H
#define POKEHEARTGOLD_BATTLE_BATTLE_ANIM_MOVE_EFFECTS_H

#include "battle/battle_anim_internal.h"

// A sprite circling a point: the angle step of its orbit oscillates (speed), then it runs a second circle
typedef struct BattleAnimMotionSprite {
    ManagedSprite *sprite;
    BattleAnimSinMotion orbit;
    BattleAnimCosMotion speed; // added to baseAngleStep
    s16 baseAngleStep;
    s16 x; // center of the orbit
    s16 y;
    u16 unk_42;
    int state;
    BOOL active;
} BattleAnimMotionSprite;

typedef struct BattleAnimShakeDefenderWithOverlayWork BattleAnimShakeDefenderWithOverlayWork;
typedef struct BattleAnimDropSpriteStepwiseWork BattleAnimDropSpriteStepwiseWork;

typedef struct BattleAnimScatterArea {
    s16 y;
    s16 x;
    s16 yRange;
    s16 xRange;
} BattleAnimScatterArea;

typedef struct BattleAnimAfterimagePass {
    s16 startX;
    s16 endX;
    s16 duration;
} BattleAnimAfterimagePass;

typedef struct BattleAnimScaleStep {
    u8 start;
    u8 end;
    u8 duration;
} BattleAnimScaleStep;

typedef struct BattleAnimScaleStepXY {
    u8 startX;
    u8 endX;
    u8 startY;
    u8 endY;
    u8 duration;
} BattleAnimScaleStepXY;

typedef struct BattleAnimHopStep {
    u8 startY;
    u8 endY;
    u8 duration;
} BattleAnimHopStep;

typedef struct BattleAnimRockStep {
    int angle;
    int duration;
} BattleAnimRockStep;

// Per sprite: frame from which it blinks, frames per blink toggle
extern const u8 gBattleAnimBlinkScaleFadeTimings[][2];
// Afterimage passes (two rows per pass parity)
extern const BattleAnimAfterimagePass gBattleAnimAttackerAfterimagePasses[];
// Pulses (dim / back)
extern const BattleAnimScaleStep gBattleAnimPulseWhiteSteps[];
extern const BattleAnimScaleStepXY gBattleAnimAttackerStretchSteps[];
extern const BattleAnimScaleStepXY gBattleAnimLeapOffscreenSteps[];
// Draw priority of the four effect sprites
extern const int gBattleAnimSpriteDrawPriorities[4];
extern const BattleAnimScaleStepXY gBattleAnimAttackerHopScales[];
extern const BattleAnimHopStep gBattleAnimAttackerHopOffsets[];
extern const u8 gBattleAnimSquashAfterimageDelays[];
extern const s16 gBattleAnimShakeBattlefieldAmplitudes[];
extern const BattleAnimRockStep gBattleAnimRockAttackerSteps[];
extern const BattleAnimScaleStepXY gBattleAnimCrossingSpritesScales[];
extern const s8 gBattleAnimCrossingSpritesArcSigns[5][2];
extern const u8 gBattleAnimSlidingSpritePairDurations[];
// {start frame, blink interval} per sprite
extern const u8 gBattleAnimBlinkCenterTimings[][2];
extern const BattleAnimPosition gBattleAnimScatterTargets[];
extern const s16 gBattleAnimSlidingSpritePairPositions[][2];
// Targets of the two sprites of each pair
extern const BattleAnimPosition gBattleAnimSlidingSpritePairTargets[][2];
extern const BattleAnimScatterArea gBattleAnimScatterAreas[];

void BattleAnimFunc_SetBgPaletteGrayscale(BattleAnimSystem *system);
void BattleAnimFunc_DropSpriteStepwise(BattleAnimSystem *system);
void BattleAnimFunc_AnimateSprites(BattleAnimSystem *system);
void BattleAnimFunc_BattleBgWave(BattleAnimSystem *system);
void BattleAnimSpriteFunc_BlinkScaleFadeSprites(BattleAnimSystem *system, SpriteSystem *spriteSystem, SpriteManager *spriteManager, ManagedSprite *sprite);
void BattleAnimFunc_AttackerGrowFlashRed(BattleAnimSystem *system);
void BattleAnimFunc_AttackerSquashStretch(BattleAnimSystem *system);
void BattleAnimFunc_AttackerAfterimages(BattleAnimSystem *system);
void BattleAnimFunc_AttackerPulseWhite(BattleAnimSystem *system);
void BattleAnimFunc_AttackerStretchSteps(BattleAnimSystem *system);
void BattleAnimFunc_AttackerLeapOffscreen(BattleAnimSystem *system);
void BattleAnimFunc_AttackerSilhouette(BattleAnimSystem *system);
void BattleAnimFunc_AttackerHop(BattleAnimSystem *system);
void BattleAnimFunc_ShowAttackerObjWindowSprites(BattleAnimSystem *system);
void BattleAnimFunc_AttackerSquashAfterimages(BattleAnimSystem *system);
void BattleAnimFunc_ShakeBattlefieldFlashing(BattleAnimSystem *system);
void BattleAnimFunc_SpriteDriftFade(BattleAnimSystem *system);
void BattleAnimFunc_RockOrShakeAttacker(BattleAnimSystem *system);
void BattleAnimFunc_ShakeBattlefieldByPower(BattleAnimSystem *system);
void BattleAnimFunc_ShakeSpritePair(BattleAnimSystem *system);
void BattleAnimSpriteFunc_ThrowSpriteArc(BattleAnimSystem *system, SpriteSystem *spriteSystem, SpriteManager *spriteManager, ManagedSprite *sprite);
void BattleAnimFunc_StretchFadeSprite(BattleAnimSystem *system);
void BattleAnimSpriteFunc_CrossingSprites(BattleAnimSystem *system, SpriteSystem *spriteSystem, SpriteManager *spriteManager, ManagedSprite *sprite);
void BattleAnimSpriteFunc_BlinkSpritesCenter(BattleAnimSystem *system, SpriteSystem *spriteSystem, SpriteManager *spriteManager, ManagedSprite *sprite);
void BattleAnimSpriteFunc_SlidingSpritePairs(BattleAnimSystem *system, SpriteSystem *spriteSystem, SpriteManager *spriteManager, ManagedSprite *sprite);
void BattleAnimSpriteFunc_PopAndScatterSprites(BattleAnimSystem *system, SpriteSystem *spriteSystem, SpriteManager *spriteManager, ManagedSprite *sprite);
void BattleAnimFunc_WaveAttackerOnBg(BattleAnimSystem *system);
void BattleAnimSpriteFunc_SpriteQuad(BattleAnimSystem *system, SpriteSystem *spriteSystem, SpriteManager *spriteManager, ManagedSprite *sprite);
void BattleAnimSpriteFunc_FlashingSpritesAroundAttacker(BattleAnimSystem *system, SpriteSystem *spriteSystem, SpriteManager *spriteManager, ManagedSprite *sprite);
void BattleAnimFunc_ShrinkSpriteOnDefender(BattleAnimSystem *system);
void BattleAnimFunc_AttackerDashAfterimages(BattleAnimSystem *system);
void BattleAnimSpriteFunc_SpriteTrailToDefender(BattleAnimSystem *system, SpriteSystem *spriteSystem, SpriteManager *spriteManager, ManagedSprite *sprite);
void BattleAnimFunc_SquashSprite(BattleAnimSystem *system);
void BattleAnimFunc_SlideOutAndTransform(BattleAnimSystem *system);
void BattleAnimFunc_WipeOutDefender(BattleAnimSystem *system);
void BattleAnimFunc_PicOrbit(BattleAnimSystem *system);
void BattleAnimFunc_AttackerRecoilTilt(BattleAnimSystem *system);
void BattleAnimSpriteFunc_OrbitingSpriteTrail(BattleAnimSystem *system, SpriteSystem *spriteSystem, SpriteManager *spriteManager, ManagedSprite *sprite);
void BattleAnimFunc_ShakeDefenderWithOverlay(BattleAnimSystem *system);

#endif // POKEHEARTGOLD_BATTLE_BATTLE_ANIM_MOVE_EFFECTS_H
