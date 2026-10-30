// Converted from asm/pokewalker_data.s (part 7 of 15) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

#include "global.h"

#include "application/pokewalker/pokewalker_app.h"
#include "application/pokewalker/pokewalker_app_internal.h"
#include "application/pokewalker/pokewalker_event_log.h"
#include "application/pokewalker/pokewalker_ir_internal.h"
#include "application/pokewalker/pokewalker_trainer_house.h"

#pragma force_active on

const ManagedSpriteTemplate gPokewalkerAppMainSpriteTemplate = {
    128,
    112,
    0,
    0x0013,
    0,
    0,
    NNS_G2D_VRAM_TYPE_2DMAIN,
    { 49703, 49703, 49703, 49703, 0, 0 },
    0,
    0,
};

const ManagedSpriteTemplate gPokewalkerAppSubSpriteTemplate = {
    128,
    112,
    0,
    4,
    0,
    0,
    NNS_G2D_VRAM_TYPE_2DSUB,
    { 49702, 49702, 49702, 49702, 0, 0 },
    0,
    0,
};
