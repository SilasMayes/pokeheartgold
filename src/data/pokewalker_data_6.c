// Converted from asm/pokewalker_data.s (part 6 of 15) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

// The C declarations of these do not match the data (see the notes at each
// definition): keep them out of the way of the definitions below.
#define gEventLogCourseBgm           gEventLogCourseBgm_header_decl
#define gPokewalkerAppCursorX        gPokewalkerAppCursorX_header_decl
#define gPokewalkerAppCursorY        gPokewalkerAppCursorY_header_decl
#define gPokewalkerAppCursorAnims    gPokewalkerAppCursorAnims_header_decl
#define gPokewalkerAppCursorPalettes gPokewalkerAppCursorPalettes_header_decl

#include "global.h"

#include "application/pokewalker/pokewalker_app.h"
#include "application/pokewalker/pokewalker_app_internal.h"
#include "application/pokewalker/pokewalker_event_log.h"
#include "application/pokewalker/pokewalker_ir_internal.h"
#include "application/pokewalker/pokewalker_trainer_house.h"

#pragma force_active on

#undef gEventLogCourseBgm
#undef gPokewalkerAppCursorX
#undef gPokewalkerAppCursorY
#undef gPokewalkerAppCursorAnims
#undef gPokewalkerAppCursorPalettes

const ManagedSpriteTemplate gPokewalkerAppSpriteTemplates[15] = {
    { 22,  59,  0, 8,      0, 65536, NNS_G2D_VRAM_TYPE_2DMAIN, { 49703, 49703, 49703, 49703, 0, 0 }, 1, 0 },
    { 128, 59,  0, 0,      0, 0,     NNS_G2D_VRAM_TYPE_2DSUB,  { 49702, 49702, 49702, 49702, 0, 0 }, 1, 0 },
    { 128, 59,  0, 2,      0, 0,     NNS_G2D_VRAM_TYPE_2DSUB,  { 49702, 49702, 49702, 49702, 0, 0 }, 1, 0 },
    { 17,  173, 0, 0,      0, 0,     NNS_G2D_VRAM_TYPE_2DMAIN, { 49703, 49703, 49703, 49703, 0, 0 }, 1, 0 },
    { 55,  173, 0, 1,      0, 0,     NNS_G2D_VRAM_TYPE_2DMAIN, { 49703, 49703, 49703, 49703, 0, 0 }, 1, 0 },
    { 50,  128, 0, 6,      0, 65537, NNS_G2D_VRAM_TYPE_2DMAIN, { 49703, 49703, 49703, 49703, 0, 0 }, 1, 0 },
    { 128, 100, 0, 7,      0, 65538, NNS_G2D_VRAM_TYPE_2DMAIN, { 49703, 49703, 49703, 49703, 0, 0 }, 1, 0 },
    { 64,  54,  0, 3,      0, 65536, NNS_G2D_VRAM_TYPE_2DSUB,  { 49702, 49702, 49702, 49702, 0, 0 }, 0, 0 },
    { 128, 100, 0, 0x000E, 0, 65539, NNS_G2D_VRAM_TYPE_2DMAIN, { 49703, 49703, 49703, 49703, 0, 0 }, 0, 0 },
    { 136, 112, 0, 0x000F, 0, 65540, NNS_G2D_VRAM_TYPE_2DMAIN, { 49703, 49703, 49703, 49703, 0, 0 }, 0, 0 },
    { 136, 112, 0, 0x0010, 0, 65540, NNS_G2D_VRAM_TYPE_2DMAIN, { 49703, 49703, 49703, 49703, 0, 0 }, 0, 0 },
    { 136, 112, 0, 0x0011, 0, 65540, NNS_G2D_VRAM_TYPE_2DMAIN, { 49703, 49703, 49703, 49703, 0, 0 }, 0, 0 },
    { 136, 112, 0, 0x0012, 0, 65540, NNS_G2D_VRAM_TYPE_2DMAIN, { 49703, 49703, 49703, 49703, 0, 0 }, 0, 0 },
    { 128, 112, 0, 0x0018, 0, 0,     NNS_G2D_VRAM_TYPE_2DMAIN, { 49703, 49703, 49703, 49703, 0, 0 }, 0, 0 },
    { 128, 112, 0, 0x000A, 0, 0,     NNS_G2D_VRAM_TYPE_2DSUB,  { 49702, 49702, 49702, 49702, 0, 0 }, 0, 0 },
};

// C declares this as `const u8 gPokewalkerAppCursorPalettes[]`, but MWCC gives a char array a section
// of its own, which the linker starts 4-aligned; to stay at offset 0xb683 next to its neighbours it is
// written as the only row of a 2-D array, which shares their section.
// clang-format off
const u8 gPokewalkerAppCursorPalettes[1][53] = {
{
    0x01, 0x80, 0x5F, 0x08, 0x01, 0x80, 0x50, 0x08, 0x01, 0xE0, 0xB0, 0x0A, 0x01, 0x98, 0xB0, 0x09,
    0x01, 0x50, 0x10, 0x08, 0x09, 0x80, 0x10, 0x08, 0x01, 0x80, 0x30, 0x08, 0x01, 0x80, 0x50, 0x08,
    0x01, 0x80, 0x70, 0x08, 0x01, 0x80, 0x90, 0x08, 0x01, 0x80, 0x20, 0x08, 0x01, 0x80, 0x48, 0x08,
    0x01, 0x80, 0x70, 0x08, 0x01,
}
};
// clang-format on

#pragma explicit_zero_data on
// zero bytes after gEventLogCourseBgm in the asm
static u8 gEventLogCourseBgm_pad[8] = { 0 };
#pragma explicit_zero_data reset

#ifdef SDK_PORT
// clang-format off
const u8 gPokewalkerAppCursorAnims[53] = {
    8, 1, 0x80, 0x5F, 8, 1, 0x80, 0x50, 8, 1, 0xE0, 0xB0, 0xA, 1, 0x98, 0xB0,
    9, 1, 0x50, 0x10, 8, 9, 0x80, 0x10, 8, 1, 0x80, 0x30, 8, 1, 0x80, 0x50,
    8, 1, 0x80, 0x70, 8, 1, 0x80, 0x90, 8, 1, 0x80, 0x20, 8, 1, 0x80, 0x48,
    8, 1, 0x80, 0x70, 8,
};
// clang-format on
#else
// C declares this as `const u8 gPokewalkerAppCursorAnims[]`, but MWCC gives a char array a section of
// its own, which the linker starts 4-aligned; to stay at offset 0xb682 next to its neighbours it is
// written as the only row of a 2-D array, which shares their section.
const u8 gPokewalkerAppCursorAnims[1][1] = { { 0x08 } };
#endif

#ifdef SDK_PORT
// On the DS the four cursor labels are the columns of one table of {x, y, anim, palette} by
// position (read at [position * 4]); the port has a complete copy for each.
// clang-format off
const u8 gPokewalkerAppCursorX[53] = {
    0x80, 0x38, 8, 1, 0x80, 0x5F, 8, 1, 0x80, 0x50, 8, 1, 0xE0, 0xB0, 0xA, 1,
    0x98, 0xB0, 9, 1, 0x50, 0x10, 8, 9, 0x80, 0x10, 8, 1, 0x80, 0x30, 8, 1,
    0x80, 0x50, 8, 1, 0x80, 0x70, 8, 1, 0x80, 0x90, 8, 1, 0x80, 0x20, 8, 1,
    0x80, 0x48, 8, 1, 0x80,
};
// clang-format on
#else
// C declares this as `const u8 gPokewalkerAppCursorX[]`, but MWCC gives a char array a section of its
// own, which the linker starts 4-aligned; to stay at offset 0xb680 next to its neighbours it is
// written as the only row of a 2-D array, which shares their section.
const u8 gPokewalkerAppCursorX[1][1] = { { 0x80 } };
#endif

#ifdef SDK_PORT
// clang-format off
const u8 gPokewalkerAppCursorY[53] = {
    0x38, 8, 1, 0x80, 0x5F, 8, 1, 0x80, 0x50, 8, 1, 0xE0, 0xB0, 0xA, 1, 0x98,
    0xB0, 9, 1, 0x50, 0x10, 8, 9, 0x80, 0x10, 8, 1, 0x80, 0x30, 8, 1, 0x80,
    0x50, 8, 1, 0x80, 0x70, 8, 1, 0x80, 0x90, 8, 1, 0x80, 0x20, 8, 1, 0x80,
    0x48, 8, 1, 0x80, 0x70,
};
// clang-format on
#else
// C declares this as `const u8 gPokewalkerAppCursorY[]`, but MWCC gives a char array a section of its
// own, which the linker starts 4-aligned; to stay at offset 0xb681 next to its neighbours it is
// written as the only row of a 2-D array, which shares their section.
const u8 gPokewalkerAppCursorY[1][1] = { { 0x38 } };
#endif
