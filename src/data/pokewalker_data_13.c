// Converted from asm/pokewalker_data.s (part 13 of 15) by tools/s2c.py.
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
const u8 gPokewalkerUploadBlockSizes[16] = {
    0x08, 0x0A, 0x06, 0x08, 0x0A, 0x14, 0x1C, 0x28, 0x0E, 0x12, 0x46, 0x08, 0x08, 0x08, 0x0A, 0x14,
};
// clang-format on

// clang-format off
const u8 gEventLogTouchBoxes[16] = {
    0x07, 0x08, 0x6F, 0xA0, 0xC0, 0x10, 0x30, 0xA0, 0xC0, 0x40, 0x60, 0xA0, 0xC0, 0xB8, 0xF8, 0x00,
};
// clang-format on
