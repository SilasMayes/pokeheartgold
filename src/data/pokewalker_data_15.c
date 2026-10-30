// Converted from asm/pokewalker_data.s (part 15 of 15) by tools/s2c.py.
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

// clang-format off
const u16 gTrainerHouseDailyFlags[MAX_NUM_TRAINER_HOUSE_SETS] = {
    0x0AAA, 0x0AAB, 0x0AAC, 0x0AAD, 0x0AAE, 0x0AAF, 0x0AB0, 0x0AB1, 0x0AB2, 0x0AB3,
};
// clang-format on

// clang-format off
const s8 gEventLogFleeHopHeights[12] __attribute__((aligned(4))) = {
    0x00, 0x08, 0x0E, 0x12, 0x14, 0x12, 0x0E, 0x08, 0x00, 0x6F, 0x00, 0x00,
};
// clang-format on

const u8 gEventLogBgLayers[5] = { 0x00, 0x01, 0x02, 0x04, 0x05 };
