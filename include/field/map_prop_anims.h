#ifndef POKEHEARTGOLD_FIELD_MAP_PROP_ANIMS_H
#define POKEHEARTGOLD_FIELD_MAP_PROP_ANIMS_H

#include "global.h"

// The task environment of the Pokemon Center healing machine animation (PokecenterAnimCreate, PokecenterAnimRun).
typedef struct PokecenterAnim {
    VecFx32 machinePos;
    u8 ballCount;
    u8 ballIndex;
    u8 timer;
    u8 state;
    u8 ballProps[6];
} PokecenterAnim;

#endif // POKEHEARTGOLD_FIELD_MAP_PROP_ANIMS_H
