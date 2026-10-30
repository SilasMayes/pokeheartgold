#ifndef POKEHEARTGOLD_FIELD_VERY_TALL_GRASS_H
#define POKEHEARTGOLD_FIELD_VERY_TALL_GRASS_H

#include "field/field_effect_manager.h"

// Very tall grass around map objects.

typedef struct VeryTallGrass VeryTallGrass;

VeryTallGrass *VeryTallGrass_New(FieldEffectManager *manager);
void VeryTallGrass_Free(VeryTallGrass *grass);
void VeryTallGrass_Spawn(LocalMapObject *mapObject, BOOL animate);

#ifdef SDK_PORT // C needs the element type of an array declaration to be complete
#include "billboard_internal.h"
#endif
extern const struct BillboardSequenceRange gVeryTallGrassRecordParams[2];

#endif // POKEHEARTGOLD_FIELD_VERY_TALL_GRASS_H
