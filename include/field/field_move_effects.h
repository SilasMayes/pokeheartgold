#ifndef POKEHEARTGOLD_FIELD_FIELD_MOVE_EFFECTS_H
#define POKEHEARTGOLD_FIELD_FIELD_MOVE_EFFECTS_H

#include "field/field_3d_object_task.h"

#include "field_system.h"

// 3D effects of the field moves (overlay 2), each one a Field3dObjectTask. Cut, Rock Smash and Headbutt are started
// by script (ScriptFieldMoveEffect_Start in overlay_02.h), the others by the field move tasks of overlay 1 and 2.

Field3dObjectTask *WaterfallEffect_Create(FieldSystem *fieldSystem);
void WaterfallEffect_Delete(Field3dObjectTask *task);
Field3dObjectTask *WhirlpoolEffect_Create(FieldSystem *fieldSystem);
void WhirlpoolEffect_Delete(Field3dObjectTask *task);
Field3dObjectTask *RockClimbDebris_Create(FieldSystem *fieldSystem);
void RockClimbDebris_Delete(Field3dObjectTask *task);
Field3dObjectTask *RockDebris_Create(FieldSystem *fieldSystem);
Field3dObjectTask *RockDebris_CreateWithFollower(FieldSystem *fieldSystem);
void RockDebris_Delete(Field3dObjectTask *task);

extern const VecFx32 gHallOfFameBallOffsets[];
extern const Field3dObjectTaskTemplate gRockSmashEffectAtPlayerTemplate;
extern const Field3dObjectTaskTemplate gWhirlpoolEffectTemplate;
extern const Field3dObjectTaskTemplate gHeadbuttEffectAtFollowerTemplate;
extern const Field3dObjectTaskTemplate gWaterfallEffectTemplate;
extern const Field3dObjectTaskTemplate gRockClimbDebrisTemplate;
extern const Field3dObjectTaskTemplate gCutEffectAtPlayerTemplate;
extern const Field3dObjectTaskTemplate gRockSmashEffectAtFollowerTemplate;
extern const Field3dObjectTaskTemplate gHeadbuttEffectAtPlayerTemplate;
extern const Field3dObjectTaskTemplate gCutEffectAtFollowerTemplate;
extern const Field3dObjectTaskTemplate gRockDebrisTemplate;
extern const Field3dObjectTaskTemplate gRockDebrisWithFollowerTemplate;
extern void (*const gScriptFieldMoveEffectDeleteFuncs[])(Field3dObjectTask *task);
extern Field3dObjectTask *(*const gScriptFieldMoveEffectCreateFuncs[])(FieldSystem *fieldSystem);
extern BOOL (*const gScriptFieldMoveEffectIsFinishedFuncs[])(Field3dObjectTask *task);

#endif // POKEHEARTGOLD_FIELD_FIELD_MOVE_EFFECTS_H
