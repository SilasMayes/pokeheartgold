// Converted from asm/field_tall_grass_data.s by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout. Keep that when editing, or rerun tools/s2c.py.

#include "global.h"

#include "field_tall_grass.h"

#pragma force_active on

extern void TallGrassEffect_Destroy(void);
extern void TallGrassEffect_Draw(void);
extern void TallGrassEffect_Init(void);
extern void TallGrassEffect_Update(void);
extern void TallGrassUnusedEffect_Destroy(void);
extern void TallGrassUnusedEffect_Draw(void);
extern void TallGrassUnusedEffect_Init(void);
extern void TallGrassUnusedEffect_Update(void);

// clang-format off
const FieldEffectBasicTemplate gTallGrassEffectTemplate = {
    0x00000040, (FieldEffectInitFunc)TallGrassEffect_Init, (FieldEffectFunc)TallGrassEffect_Destroy,
    (FieldEffectFunc)TallGrassEffect_Update, (FieldEffectFunc)TallGrassEffect_Draw,
};
// clang-format on

// clang-format off
const FieldEffectBasicTemplate gTallGrassUnusedEffectTemplate = {
    0x00000028, (FieldEffectInitFunc)TallGrassUnusedEffect_Init,
    (FieldEffectFunc)TallGrassUnusedEffect_Destroy, (FieldEffectFunc)TallGrassUnusedEffect_Update,
    (FieldEffectFunc)TallGrassUnusedEffect_Draw,
};
// clang-format on
