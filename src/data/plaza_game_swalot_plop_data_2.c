// Converted from asm/plaza_game_swalot_plop_data.s (part 2 of 6) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

// The C declarations of these do not match the data (see the notes at each
// definition): keep them out of the way of the definitions below.
#define gSwalotPlopSub3BgTemplate gSwalotPlopSub3BgTemplate_header_decl

#include "global.h"

#include "application/plaza_game_swalot_plop.h"

#pragma force_active on

#undef gSwalotPlopSub3BgTemplate

// clang-format off
const BgTemplate gSwalotPlopMain1BgTemplate = {
    0, 0, 0x00000800, 0, 0x01, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0,
};
// clang-format on

// clang-format off
const BgTemplate gSwalotPlopMain2BgTemplate = {
    0, 0, 0x00000800, 0, 0x01, 0x00, 0x0E, 0x01, 0x00, 0x01, 0x00, 0x00, 0,
};
// clang-format on

// clang-format off
const BgTemplate gSwalotPlopSub0BgTemplate = {
    0, 0, 0x00000800, 0, 0x01, 0x00, 0x1A, 0x00, 0x00, 0x00, 0x00, 0x00, 0,
};
// clang-format on

// clang-format off
const BgTemplate gSwalotPlopSub1BgTemplate = {
    0, 0, 0x00000800, 0, 0x01, 0x00, 0x1B, 0x00, 0x00, 0x01, 0x00, 0x00, 0,
};
// clang-format on

// clang-format off
const BgTemplate gSwalotPlopSub2BgTemplate = {
    0, 0, 0x00000800, 0, 0x01, 0x00, 0x1C, 0x00, 0x00, 0x02, 0x00, 0x00, 0,
};
// clang-format on

const s16 gSwalotPlopDemoCursorYs[12] = { 177, 167, 147, 137, 127, 117, 107, 97, 87, 77, 77, 77 };

// C declares this as `const BgTemplate gSwalotPlopSub3BgTemplate`, but that type is 0x1c bytes and the
// label covers only 0x14 (later labels overlap it).
// clang-format off
const u8 gSwalotPlopSub3BgTemplate[20] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x01, 0x00, 0x1D, 0x00,
};
// clang-format on

const ObjCharTransferTemplate gSwalotPlopObjCharTransfer = { 16, 131072, 16384, HEAP_ID_DEFAULT };

// clang-format off
const GraphicsModes gSwalotPlopGraphicsModes = {
    GX_DISPMODE_GRAPHICS, GX_BGMODE_0, GX_BGMODE_0, GX_BG0_AS_3D,
};
// clang-format on

// clang-format off
int (*const gSwalotPlopTiltFuncs[3])(SwalotPlopBody *body, u32 frame, u32 duration) = {
    (int (*)(SwalotPlopBody *, u32, u32))SwalotPlopBody_GetTiltNormal,
    (int (*)(SwalotPlopBody *, u32, u32))SwalotPlopBody_GetTiltFast,
    (int (*)(SwalotPlopBody *, u32, u32))SwalotPlopBody_GetTiltFastest,
};
// clang-format on

const VecFx32 gSwalotPlopBodyBaseNormal = { 0, 10240000, 0 };

const u32 gSwalotPlopPhaseFrames[2] = { 0x00000294, 0x000002EE };
