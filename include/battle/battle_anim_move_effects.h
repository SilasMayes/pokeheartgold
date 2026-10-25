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

// Per sprite: frame from which it blinks, frames per blink toggle
extern const u8 gBattleAnimBlinkScaleFadeTimings[][2];
// Afterimage passes: start offset, end offset, duration (two rows per pass parity)
extern const s16 gBattleAnimAttackerAfterimageMotions[][3];
extern const s16 gBattleAnimAttackerAfterimageEndX[][3];
extern const s16 gBattleAnimAttackerAfterimageDurations[][3];
// Pulses (dim / back): start scale, end scale, duration
extern const u8 gBattleAnimPulseWhiteScales[][3];
extern const u8 gBattleAnimPulseWhiteScaleEnds[][3];
extern const u8 gBattleAnimPulseWhiteDurations[][3];
// Stretch steps: start x scale, end x scale, start y scale, end y scale, duration
extern const u8 gBattleAnimAttackerStretchSteps[][5];
extern const u8 gBattleAnimAttackerStretchEndX[][5];
extern const u8 gBattleAnimAttackerStretchStartY[][5];
extern const u8 gBattleAnimAttackerStretchEndY[][5];
extern const u8 gBattleAnimAttackerStretchDurations[][5];
// Leap steps: start x scale, end x scale, start y scale, end y scale, duration
extern const u8 gBattleAnimLeapOffscreenScales[][5];
extern const u8 gBattleAnimLeapOffscreenEndX[][5];
extern const u8 gBattleAnimLeapOffscreenStartY[][5];
extern const u8 gBattleAnimLeapOffscreenEndY[][5];
extern const u8 gBattleAnimLeapOffscreenDurations[][5];
// Draw priority of the four effect sprites
extern const int gBattleAnimSpriteDrawPriorities[4];
// [row][0]: x scale, y scale, ... (5 per row)
extern const u8 gBattleAnimAttackerHopScales[];
extern const u8 gBattleAnimAttackerHopScaleEndX[];
extern const u8 gBattleAnimAttackerHopScaleStartY[];
extern const u8 gBattleAnimAttackerHopScaleEndY[];
extern const u8 gBattleAnimAttackerHopScaleDurations[];
// [row * 3]: hop start y, end y, duration
extern const u8 gBattleAnimAttackerHopOffsets[];
extern const u8 gBattleAnimAttackerHopOffsetEnds[];
extern const u8 gBattleAnimAttackerHopOffsetDurations[];
extern const u8 gBattleAnimSquashAfterimageDelays[];
extern const s16 gBattleAnimShakeBattlefieldAmplitudes[];
// {angle, duration} pairs
extern const int gBattleAnimRockAttackerSteps[][2];
extern const int gBattleAnimRockAttackerDurations[][2];
extern const u8 gBattleAnimCrossingSpritesScales[];
extern const u8 gBattleAnimCrossingSpritesEndX[];
extern const u8 gBattleAnimCrossingSpritesStartY[];
extern const u8 gBattleAnimCrossingSpritesEndY[];
extern const u8 gBattleAnimCrossingSpritesDurations[];
extern const s8 gBattleAnimCrossingSpritesArcSigns[5][2];
extern const u8 gBattleAnimSlidingSpritePairDurations[];
// {start frame, blink interval} per sprite
extern const u8 gBattleAnimBlinkCenterTimings[][2];
extern const s16 gBattleAnimScatterTargets[][2];
extern const s16 gBattleAnimScatterTargetsY[][2];
extern const s16 gBattleAnimSlidingSpritePairPositions[][2];
// {x, y, x2, y2} per pair
extern const s16 gBattleAnimSlidingSpritePairTargets[][4];
extern const s16 gBattleAnimSlidingSpritePairFirstY[][4];
extern const s16 gBattleAnimSlidingSpritePairSecondX[][4];
extern const s16 gBattleAnimSlidingSpritePairSecondY[][4];
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
