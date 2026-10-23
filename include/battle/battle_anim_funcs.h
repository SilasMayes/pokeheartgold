#ifndef POKEHEARTGOLD_BATTLE_BATTLE_ANIM_FUNCS_H
#define POKEHEARTGOLD_BATTLE_BATTLE_ANIM_FUNCS_H

// Overlay 7: effect functions of the battle move animation scripts (gBattleAnimFuncTable / sprite function table
// entries) and the tasks they start.

#include "battle/battle_anim_util.h"

#include "bg_window.h"
#include "palette.h"
#include "pokepic.h"
#include "spl.h"
#include "sprite_system.h"
#include "sys_task.h"

typedef struct BattleAnimSpritePopWork BattleAnimSpritePopWork;
typedef struct BattleAnimEmitterMotionWork BattleAnimEmitterMotionWork;

// X steps of the sprite of BattleAnimTask_SpriteOrbit (0: switch its priority, 255: end)
extern const s16 gBattleAnimSpriteOrbitStepX[];

void BattleAnimFunc_OneFrameTask(BattleAnimSystem *system);
void BattleAnimFunc_OneFrameSoundTask(BattleAnimSystem *system);
void BattleAnimFunc_OneFrameUncountedTask(BattleAnimSystem *system);
void BattleAnimSpriteFunc_SpreadSpriteCopies(BattleAnimSystem *system, SpriteSystem *spriteSystem, SpriteManager *spriteManager, ManagedSprite *sprite);
void BattleAnimFunc_ShakeTargets(BattleAnimSystem *system);
void BattleAnimFunc_SlidingBg(BattleAnimSystem *system);
void BattleAnimFunc_SlidingBg2(BattleAnimSystem *system);
void BattleAnimFunc_RotateBattler(BattleAnimSystem *system);
void BattleAnimFunc_CircleBattler(BattleAnimSystem *system);
void BattleAnimSpriteFunc_SpritePops(BattleAnimSystem *system, SpriteSystem *spriteSystem, SpriteManager *spriteManager, ManagedSprite *sprite);
void BattleAnimFunc_FadeBgPalette(BattleAnimSystem *system);
void BattleAnimFunc_BattlerPaletteFade(BattleAnimSystem *system);
void BattleAnimFunc_PulseBattlerSprite(BattleAnimSystem *system);
void BattleAnimFunc_StretchBattler(BattleAnimSystem *system);
void BattleAnimFunc_BlendBattlerSprites(BattleAnimSystem *system);
void BattleAnimFunc_SetBattlerVanished(BattleAnimSystem *system);
void BattleAnimFunc_BlinkBattler(BattleAnimSystem *system);
void BattleAnimFunc_SlideBattler(BattleAnimSystem *system);
void BattleAnimFunc_SlideBattler2(BattleAnimSystem *system);
void BattleAnimFunc_ShakeAndScaleBattler(BattleAnimSystem *system);
void BattleAnimFunc_ShakeAndScaleBattlerXY(BattleAnimSystem *system);
void BattleAnimFunc_ShowBattleBgInObjWindow(BattleAnimSystem *system);
void BattleAnimFunc_MoveBattlerBy(BattleAnimSystem *system);
void BattleAnimFunc_MoveBattlerSin(BattleAnimSystem *system);
void BattleAnimFunc_MoveBattlerLinear(BattleAnimSystem *system);
void BattleAnimFunc_MoveBattlerOffscreen(BattleAnimSystem *system);
void BattleAnimFunc_ResetBattlerPosition(BattleAnimSystem *system);
void BattleAnimFunc_BlendSpritePalette(BattleAnimSystem *system);
void BattleAnimFunc_ChangeBattlerHeight(BattleAnimSystem *system);
void BattleAnimFunc_RevealBattler(BattleAnimSystem *system);
void BattleAnimFunc_ShakeBg(BattleAnimSystem *system);
void BattleAnimFunc_SpriteMosaic(BattleAnimSystem *system);
void BattleAnimFunc_MoveEmitter(BattleAnimSystem *system);
void BattleAnimFunc_MoveEmitterVertical(BattleAnimSystem *system);
void BattleAnimFunc_MoveEmitterArc(BattleAnimSystem *system);
void BattleAnimFunc_EmitterSinMotion(BattleAnimSystem *system);
void BattleAnimSpriteFunc_MoveSpriteAndAnimate(BattleAnimSystem *system, SpriteSystem *spriteSystem, SpriteManager *spriteManager, ManagedSprite *sprite);
void BattleAnimSpriteFunc_SpriteOrbit(BattleAnimSystem *system, SpriteSystem *spriteSystem, SpriteManager *spriteManager, ManagedSprite *sprite);
void BattleAnimSpriteFunc_SpriteAboveDefender(BattleAnimSystem *system, SpriteSystem *spriteSystem, SpriteManager *spriteManager, ManagedSprite *sprite);
void BattleAnimSpriteFunc_SpriteArc(BattleAnimSystem *system, SpriteSystem *spriteSystem, SpriteManager *spriteManager, ManagedSprite *sprite);

// Battle animation system tasks and accessors

#endif // POKEHEARTGOLD_BATTLE_BATTLE_ANIM_FUNCS_H
