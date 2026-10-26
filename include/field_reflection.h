#ifndef POKEHEARTGOLD_FIELD_REFLECTION_H
#define POKEHEARTGOLD_FIELD_REFLECTION_H

#include "field/field_effect_manager.h"

#include "billboard_internal.h"

// Map object reflections on water and ice.

// What a reflection is drawn on; the large kinds are for a large following Pokemon.
enum ReflectionKind {
    REFLECTION_KIND_PUDDLE,
    REFLECTION_KIND_WATER,
    REFLECTION_KIND_FLOOR,
    REFLECTION_KIND_LARGE_PUDDLE,
    REFLECTION_KIND_LARGE_WATER,
    REFLECTION_KIND_LARGE_FLOOR,
    REFLECTION_KIND_COUNT,
};

typedef struct Reflection Reflection;

Reflection *Reflection_New(FieldEffectManager *manager);
void Reflection_Free(Reflection *reflection);
void Reflection_Spawn(LocalMapObject *mapObject, int kind);
FieldEffect *Reflection_SpawnForBillboard(FieldEffectManager *manager, const BillboardResource *record, BillboardObject *source, const VecFx32 *position, int kind, u32 priority);
void Reflection_SpawnForFollower(LocalMapObject *mapObject, int kind);

#endif // POKEHEARTGOLD_FIELD_REFLECTION_H
