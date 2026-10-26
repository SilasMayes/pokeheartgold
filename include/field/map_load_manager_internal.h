#ifndef POKEHEARTGOLD_FIELD_MAP_LOAD_MANAGER_INTERNAL_H
#define POKEHEARTGOLD_FIELD_MAP_LOAD_MANAGER_INTERNAL_H

#include "field/bdhc.h"
#include "field/field_control.h"
#include "field/map_load_manager.h"

// The map slots of the map load manager, for the terrain and collision queries.

// The quarter of its map a tile is in (TileIndex_GetQuadrant).
enum MapQuadrant {
    MAP_QUADRANT_TOP_LEFT,
    MAP_QUADRANT_TOP_RIGHT,
    MAP_QUADRANT_BOTTOM_LEFT,
    MAP_QUADRANT_BOTTOM_RIGHT,
};

// The 2x2 window of loaded maps; MapLoadManager_GetMapSlotOfMatrixIndex returns this for a map that is not loaded.
#define MAP_LOAD_NUM_SLOTS 4

int TileIndex_GetQuadrant(int tile, int stride);
u8 MapLoadManager_GetMapSlotOfMatrixIndex(int matrixIndex, int unused, MapLoadManager *mapLoadManager);
int MapLoadManager_GetMapMatrixIndex(MapLoadManager *mapLoadManager, u8 mapSlot);
BOOL MapLoadManager_GetMapSlotAt(MapLoadManager *mapLoadManager, int x, int z, u8 *mapSlot);
Bdhc *MapLoadManager_GetBdhc(MapLoadManager *mapLoadManager, u8 mapSlot);
SoundplateStruct *MapLoadManager_GetSoundplates(MapLoadManager *mapLoadManager, u8 mapSlot);

#endif // POKEHEARTGOLD_FIELD_MAP_LOAD_MANAGER_INTERNAL_H
