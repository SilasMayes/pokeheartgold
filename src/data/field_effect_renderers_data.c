// Converted from asm/field_effect_renderers_data.s by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout. Keep that when editing, or rerun tools/s2c.py.

// The C declarations of these do not match the data (see the notes at each
// definition): keep them out of the way of the definitions below.
#define defaultFieldEffectRenderers defaultFieldEffectRenderers_header_decl

#include "global.h"

#include "constants/items.h"
#include "constants/maps.h"
#include "constants/mmodel.h"
#include "constants/moves.h"
#include "constants/sndseq.h"
#include "constants/species.h"
#include "constants/sprites.h"
#include "constants/std_script.h"

#include "field/field_effect_manager_internal.h"
#include "msgdata/msg/msg_0066_D23R0102.h"
#include "msgdata/msg/msg_0096_D31R0201.h"

#pragma force_active on

#undef defaultFieldEffectRenderers

extern void ApricornRegrowth_Free(void);
extern void ApricornRegrowth_New(void);
extern void EmoteBubble_Free(void);
extern void EmoteBubble_New(void);
extern void EmoteMark_Free(void);
extern void EmoteMark_New(void);
extern void FieldShadow_Free(void);
extern void FieldShadow_New(void);
extern void FlashDarkness_Free(void);
extern void FlashDarkness_New(void);
extern void FollowMonBall_Free(void);
extern void FollowMonBall_New(void);
extern void Footprints_Free(void);
extern void Footprints_New(void);
extern void GroundDust_Free(void);
extern void GroundDust_New(void);
extern void HiddenObjectCover_Free(void);
extern void HiddenObjectCover_New(void);
extern void MapObjectModelList_Free(void);
extern void MapObjectModelList_New(void);
extern void MudSplash_Free(void);
extern void MudSplash_New(void);
extern void PuddleSplash_Free(void);
extern void PuddleSplash_New(void);
extern void Reflection_Free(void);
extern void Reflection_New(void);
extern void RockClimb_Free(void);
extern void RockClimb_New(void);
extern void ShallowWaterRipple_Free(void);
extern void ShallowWaterRipple_New(void);
extern void ShayminFormChange_Free(void);
extern void ShayminFormChange_New(void);
extern void SurfMount_Free(void);
extern void SurfMount_New(void);
extern void TallGrass_Free(void);
extern void TallGrass_New(void);
extern void TrainerReveal_Free(void);
extern void TrainerReveal_New(void);
extern void UnionChatMarker_Free(void);
extern void UnionChatMarker_New(void);
extern void UnusedBillboard_Free(void);
extern void UnusedBillboard_New(void);
extern void VeryTallGrass_Free(void);
extern void VeryTallGrass_New(void);
extern void WarpArrow_Free(void);
extern void WarpArrow_New(void);

const FieldEffectRendererTemplate gFieldEffectRenderers[24] = {
    { 0x00000000, (void *(*)(FieldEffectManager *))FieldShadow_New, (void (*)(void *))FieldShadow_Free },
    { 0x00000001, (void *(*)(FieldEffectManager *))Reflection_New, (void (*)(void *))Reflection_Free },
    { 0x00000002, (void *(*)(FieldEffectManager *))Footprints_New, (void (*)(void *))Footprints_Free },
    { 0x00000003, (void *(*)(FieldEffectManager *))WarpArrow_New, (void (*)(void *))WarpArrow_Free },
    { 0x00000004, (void *(*)(FieldEffectManager *))SurfMount_New, (void (*)(void *))SurfMount_Free },
    { 0x00000005, (void *(*)(FieldEffectManager *))RockClimb_New, (void (*)(void *))RockClimb_Free },
    { 0x00000006, (void *(*)(FieldEffectManager *))PuddleSplash_New, (void (*)(void *))PuddleSplash_Free },
    { 0x00000007, (void *(*)(FieldEffectManager *))MudSplash_New, (void (*)(void *))MudSplash_Free },
    { 0x00000008, (void *(*)(FieldEffectManager *))TallGrass_New, (void (*)(void *))TallGrass_Free },
    { 0x00000009, (void *(*)(FieldEffectManager *))EmoteMark_New, (void (*)(void *))EmoteMark_Free },
    {
     0x0000000A,
     (void *(*)(FieldEffectManager *))ShallowWaterRipple_New,
     (void (*)(void *))ShallowWaterRipple_Free,
     },
    { 0x0000000B, (void *(*)(FieldEffectManager *))GroundDust_New, (void (*)(void *))GroundDust_Free },
    { 0x0000000C, (void *(*)(FieldEffectManager *))VeryTallGrass_New, (void (*)(void *))VeryTallGrass_Free },
    {
     0x0000000D,
     (void *(*)(FieldEffectManager *))UnusedBillboard_New,
     (void (*)(void *))UnusedBillboard_Free,
     },
    {
     0x0000000E,
     (void *(*)(FieldEffectManager *))HiddenObjectCover_New,
     (void (*)(void *))HiddenObjectCover_Free,
     },
    { 0x0000000F, (void *(*)(FieldEffectManager *))TrainerReveal_New, (void (*)(void *))TrainerReveal_Free },
    {
     0x00000010,
     (void *(*)(FieldEffectManager *))ApricornRegrowth_New,
     (void (*)(void *))ApricornRegrowth_Free,
     },
    { 0x00000011, (void *(*)(FieldEffectManager *))FollowMonBall_New, (void (*)(void *))FollowMonBall_Free },
    { 0x00000012, (void *(*)(FieldEffectManager *))EmoteBubble_New, (void (*)(void *))EmoteBubble_Free },
    { 0x00000013, (void *(*)(FieldEffectManager *))FlashDarkness_New, (void (*)(void *))FlashDarkness_Free },
    {
     0x00000014,
     (void *(*)(FieldEffectManager *))MapObjectModelList_New,
     (void (*)(void *))MapObjectModelList_Free,
     },
    {
     0x00000015,
     (void *(*)(FieldEffectManager *))UnionChatMarker_New,
     (void (*)(void *))UnionChatMarker_Free,
     },
    {
     0x00000016,
     (void *(*)(FieldEffectManager *))ShayminFormChange_New,
     (void (*)(void *))ShayminFormChange_Free,
     },
    { 0x00000017, NULL, NULL },
};

// C declares this non-const, but it lives in .rodata
// clang-format off
const int defaultFieldEffectRenderers[24] = {
    0x14, 0x13, 0x11, 0x01, 0x10, 0x05, 0x16, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0F, 0x12, 0x00, 0x02,
    0x03, 0x04, 0x0E, 0x06, 0x07, 0x15, 0x17,
};
// clang-format on
