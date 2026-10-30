// Converted from asm/field_move_effects_data.s (part 4 of 6) by tools/s2c.py.
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

extern void CutEffect_CreateAtFollower(void);
extern void CutEffect_CreateAtPlayer(void);
extern void CutEffect_Delete(void);
extern void CutEffect_Destroy(void);
extern void CutEffect_InitAtFollower(void);
extern void CutEffect_InitAtPlayer(void);
extern void CutEffect_IsFinished(void);
extern void CutEffect_Render(void);
extern void CutEffect_Update(void);
extern void HeadbuttEffect_CreateAtFollower(void);
extern void HeadbuttEffect_CreateAtPlayer(void);
extern void HeadbuttEffect_Delete(void);
extern void HeadbuttEffect_Destroy(void);
extern void HeadbuttEffect_InitAtFollower(void);
extern void HeadbuttEffect_InitAtPlayer(void);
extern void HeadbuttEffect_IsFinished(void);
extern void HeadbuttEffect_Render(void);
extern void HeadbuttEffect_Update(void);
extern void RockClimbDebris_Destroy(void);
extern void RockClimbDebris_Init(void);
extern void RockClimbDebris_Render(void);
extern void RockClimbDebris_Update(void);
extern void RockDebris_Destroy(void);
extern void RockDebris_Init(void);
extern void RockDebris_InitWithFollower(void);
extern void RockDebris_Render(void);
extern void RockDebris_Update(void);
extern void RockSmashEffect_CreateAtFollower(void);
extern void RockSmashEffect_CreateAtPlayer(void);
extern void RockSmashEffect_Delete(void);
extern void RockSmashEffect_Destroy(void);
extern void RockSmashEffect_InitAtFollower(void);
extern void RockSmashEffect_InitAtPlayer(void);
extern void RockSmashEffect_IsFinished(void);
extern void RockSmashEffect_Render(void);
extern void RockSmashEffect_Update(void);
extern void WaterfallEffect_Destroy(void);
extern void WaterfallEffect_Init(void);
extern void WaterfallEffect_Render(void);
extern void WaterfallEffect_Update(void);
extern void WhirlpoolEffect_Destroy(void);
extern void WhirlpoolEffect_Init(void);
extern void WhirlpoolEffect_Render(void);
extern void WhirlpoolEffect_Update(void);

// clang-format off
Field3dObjectTask *(*const gScriptFieldMoveEffectCreateFuncs[6])(FieldSystem *fieldSystem) = {
    (Field3dObjectTask *(*)(FieldSystem *))CutEffect_CreateAtPlayer,
    (Field3dObjectTask *(*)(FieldSystem *))RockSmashEffect_CreateAtPlayer,
    (Field3dObjectTask *(*)(FieldSystem *))RockSmashEffect_CreateAtFollower,
    (Field3dObjectTask *(*)(FieldSystem *))CutEffect_CreateAtFollower,
    (Field3dObjectTask *(*)(FieldSystem *))HeadbuttEffect_CreateAtPlayer,
    (Field3dObjectTask *(*)(FieldSystem *))HeadbuttEffect_CreateAtFollower,
};
// clang-format on

// clang-format off
void (*const gScriptFieldMoveEffectDeleteFuncs[6])(Field3dObjectTask *task) = {
    (void (*)(Field3dObjectTask *))CutEffect_Delete, (void (*)(Field3dObjectTask *))RockSmashEffect_Delete,
    (void (*)(Field3dObjectTask *))RockSmashEffect_Delete, (void (*)(Field3dObjectTask *))CutEffect_Delete,
    (void (*)(Field3dObjectTask *))HeadbuttEffect_Delete,
    (void (*)(Field3dObjectTask *))HeadbuttEffect_Delete,
};
// clang-format on

#ifndef SDK_PORT // field_move_effects.c has the port's, sized with sizeof
// clang-format off
const Field3dObjectTaskTemplate gRockDebrisWithFollowerTemplate = {
    1024, 0x0E9C, (Field3dObjectTaskFunc)RockDebris_InitWithFollower,
    (Field3dObjectTaskFunc)RockDebris_Destroy, (Field3dObjectTaskFunc)RockDebris_Update,
    (Field3dObjectTaskFunc)RockDebris_Render,
};
// clang-format on
#endif

#ifndef SDK_PORT // field_move_effects.c has the port's, sized with sizeof
// clang-format off
const Field3dObjectTaskTemplate gRockDebrisTemplate = {
    1024, 0x0E9C, (Field3dObjectTaskFunc)RockDebris_Init, (Field3dObjectTaskFunc)RockDebris_Destroy,
    (Field3dObjectTaskFunc)RockDebris_Update, (Field3dObjectTaskFunc)RockDebris_Render,
};
// clang-format on
#endif

#ifndef SDK_PORT // field_move_effects.c has the port's, sized with sizeof
// clang-format off
const Field3dObjectTaskTemplate gCutEffectAtFollowerTemplate = {
    1024, 0x00F0, (Field3dObjectTaskFunc)CutEffect_InitAtFollower, (Field3dObjectTaskFunc)CutEffect_Destroy,
    (Field3dObjectTaskFunc)CutEffect_Update, (Field3dObjectTaskFunc)CutEffect_Render,
};
// clang-format on
#endif

#ifndef SDK_PORT // field_move_effects.c has the port's, sized with sizeof
// clang-format off
const Field3dObjectTaskTemplate gHeadbuttEffectAtPlayerTemplate = {
    1024, 0x0114, (Field3dObjectTaskFunc)HeadbuttEffect_InitAtPlayer,
    (Field3dObjectTaskFunc)HeadbuttEffect_Destroy, (Field3dObjectTaskFunc)HeadbuttEffect_Update,
    (Field3dObjectTaskFunc)HeadbuttEffect_Render,
};
// clang-format on
#endif

#ifndef SDK_PORT // field_move_effects.c has the port's, sized with sizeof
// clang-format off
const Field3dObjectTaskTemplate gRockSmashEffectAtFollowerTemplate = {
    1024, 0x00F0, (Field3dObjectTaskFunc)RockSmashEffect_InitAtFollower,
    (Field3dObjectTaskFunc)RockSmashEffect_Destroy, (Field3dObjectTaskFunc)RockSmashEffect_Update,
    (Field3dObjectTaskFunc)RockSmashEffect_Render,
};
// clang-format on
#endif

#ifndef SDK_PORT // field_move_effects.c has the port's, sized with sizeof
// clang-format off
const Field3dObjectTaskTemplate gWhirlpoolEffectTemplate = {
    1024, 0x00F0, (Field3dObjectTaskFunc)WhirlpoolEffect_Init, (Field3dObjectTaskFunc)WhirlpoolEffect_Destroy,
    (Field3dObjectTaskFunc)WhirlpoolEffect_Update, (Field3dObjectTaskFunc)WhirlpoolEffect_Render,
};
// clang-format on
#endif

#ifndef SDK_PORT // field_move_effects.c has the port's, sized with sizeof
// clang-format off
const Field3dObjectTaskTemplate gRockClimbDebrisTemplate = {
    1024, 0x0D10, (Field3dObjectTaskFunc)RockClimbDebris_Init, (Field3dObjectTaskFunc)RockClimbDebris_Destroy,
    (Field3dObjectTaskFunc)RockClimbDebris_Update, (Field3dObjectTaskFunc)RockClimbDebris_Render,
};
// clang-format on
#endif

#ifndef SDK_PORT // field_move_effects.c has the port's, sized with sizeof
// clang-format off
const Field3dObjectTaskTemplate gWaterfallEffectTemplate = {
    1024, 0x01CC, (Field3dObjectTaskFunc)WaterfallEffect_Init, (Field3dObjectTaskFunc)WaterfallEffect_Destroy,
    (Field3dObjectTaskFunc)WaterfallEffect_Update, (Field3dObjectTaskFunc)WaterfallEffect_Render,
};
// clang-format on
#endif

#ifndef SDK_PORT // field_move_effects.c has the port's, sized with sizeof
// clang-format off
const Field3dObjectTaskTemplate gHeadbuttEffectAtFollowerTemplate = {
    1024, 0x0114, (Field3dObjectTaskFunc)HeadbuttEffect_InitAtFollower,
    (Field3dObjectTaskFunc)HeadbuttEffect_Destroy, (Field3dObjectTaskFunc)HeadbuttEffect_Update,
    (Field3dObjectTaskFunc)HeadbuttEffect_Render,
};
// clang-format on
#endif

#ifndef SDK_PORT // field_move_effects.c has the port's, sized with sizeof
// clang-format off
const Field3dObjectTaskTemplate gCutEffectAtPlayerTemplate = {
    1024, 0x00F0, (Field3dObjectTaskFunc)CutEffect_InitAtPlayer, (Field3dObjectTaskFunc)CutEffect_Destroy,
    (Field3dObjectTaskFunc)CutEffect_Update, (Field3dObjectTaskFunc)CutEffect_Render,
};
// clang-format on
#endif

#ifndef SDK_PORT // field_move_effects.c has the port's, sized with sizeof
// clang-format off
const Field3dObjectTaskTemplate gRockSmashEffectAtPlayerTemplate = {
    1024, 0x00F0, (Field3dObjectTaskFunc)RockSmashEffect_InitAtPlayer,
    (Field3dObjectTaskFunc)RockSmashEffect_Destroy, (Field3dObjectTaskFunc)RockSmashEffect_Update,
    (Field3dObjectTaskFunc)RockSmashEffect_Render,
};
// clang-format on
#endif

// clang-format off
BOOL (*const gScriptFieldMoveEffectIsFinishedFuncs[6])(Field3dObjectTask *task) = {
    (BOOL (*)(Field3dObjectTask *))CutEffect_IsFinished,
    (BOOL (*)(Field3dObjectTask *))RockSmashEffect_IsFinished,
    (BOOL (*)(Field3dObjectTask *))RockSmashEffect_IsFinished,
    (BOOL (*)(Field3dObjectTask *))CutEffect_IsFinished,
    (BOOL (*)(Field3dObjectTask *))HeadbuttEffect_IsFinished,
    (BOOL (*)(Field3dObjectTask *))HeadbuttEffect_IsFinished,
};
// clang-format on

// clang-format off
const u8 gRideEffectFileIds[16] = {
    0x10, 0x0F, 0x0E, 0x0B, 0x0C, 0x09, 0xB4, 0x00, 0x00, 0x00, 0x0E, 0x01, 0x5A, 0x00, 0x00, 0x00,
};
// clang-format on
