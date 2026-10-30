// Converted from asm/pokewalker_data.s (part 12 of 15) by tools/s2c.py.
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

extern const u8 sPokewalkerUploadBlock0[1][8];
extern const u8 sPokewalkerUploadBlock1[1][10];
extern const u8 sPokewalkerUploadBlock2[1][6];
extern const u8 sPokewalkerUploadBlock3[1][8];
extern const u8 sPokewalkerUploadBlock4[1][10];
extern const u8 sPokewalkerUploadBlock5[20];
extern const u8 sPokewalkerUploadBlock6[28];
extern const u8 sPokewalkerUploadBlock7[40];
extern const u8 sPokewalkerUploadBlock8[1][14];
extern const u8 sPokewalkerUploadBlock9[1][18];
extern const u8 sPokewalkerUploadBlock11[1][8];
extern const u8 sPokewalkerUploadBlock12[1][8];
extern const u8 sPokewalkerUploadBlock13[1][8];
extern const u8 sPokewalkerUploadBlock14[1][10];
extern const u8 sPokewalkerUploadBlock15[20];

// not static: used above its definition
// clang-format off
const u8 sPokewalkerUploadBlock10[72] = {
    0xA0, 0x7B, 0x06, 0x1C, 0x06, 0x1D, 0x06, 0x1E, 0x06, 0x1F, 0x06, 0x1C, 0x06, 0x1D, 0x06, 0x1E,
    0x06, 0x1F, 0x06, 0x1C, 0x06, 0x1D, 0x06, 0x1E, 0x06, 0x1F, 0x06, 0x1C, 0x06, 0x1D, 0x06, 0x1E,
    0x06, 0x1F, 0x06, 0x1C, 0x06, 0x1D, 0x06, 0x1E, 0x06, 0x1F, 0x06, 0x1C, 0x06, 0x1D, 0x06, 0x1E,
    0x06, 0x1F, 0x06, 0x1C, 0x06, 0x1D, 0x06, 0x1E, 0x06, 0x1F, 0x06, 0x1C, 0x06, 0x1D, 0x06, 0x1E,
    0x06, 0x1F, 0x18, 0x1F, 0x60, 0x7F, 0x00, 0x00,
};
// clang-format on

// clang-format off
const u8 *const gPokewalkerUploadBlocks[16] = {
    (const u8 *)sPokewalkerUploadBlock0, (const u8 *)sPokewalkerUploadBlock1, (const u8 *)sPokewalkerUploadBlock2,
    (const u8 *)sPokewalkerUploadBlock3, (const u8 *)sPokewalkerUploadBlock4, sPokewalkerUploadBlock5,
    sPokewalkerUploadBlock6, sPokewalkerUploadBlock7, (const u8 *)sPokewalkerUploadBlock8,
    (const u8 *)sPokewalkerUploadBlock9, sPokewalkerUploadBlock10, (const u8 *)sPokewalkerUploadBlock11,
    (const u8 *)sPokewalkerUploadBlock12, (const u8 *)sPokewalkerUploadBlock13, (const u8 *)sPokewalkerUploadBlock14,
    sPokewalkerUploadBlock15,
};
// clang-format on
