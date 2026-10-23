#ifndef POKEHEARTGOLD_FIELD_METATILE_QUERY_INTERNAL_H
#define POKEHEARTGOLD_FIELD_METATILE_QUERY_INTERNAL_H
#include "global.h"

#include "field/map_load_manager.h"
#include "field/map_load_manager_internal.h"
#include "field/map_prop.h"

#include "field_system.h"
#include "heap.h"
#include "map_matrix.h"
#include "terrain_attributes.h"
#include "field_terrain.h"
#include "gymmick_collision.h"

// The terrain query functions of the current map kind (FieldSystem.terrainQueries): heights from the loaded maps'
// BDHC data, or none for maps with simple terrain collisions.
typedef struct FieldTerrainQueries {
    int (*getHeight)(FieldSystem *fieldSystem, int objectHeight, fx32 x, fx32 z, u8 *outKind);
    BOOL (*getAttributes)(FieldSystem *fieldSystem, int x, int z, u16 *outAttributes);
} FieldTerrainQueries;

#define FS_TERRAIN_QUERIES(fieldSystem) ((const FieldTerrainQueries *)(fieldSystem)->terrainQueries)

#endif
