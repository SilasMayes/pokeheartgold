// Converted from asm/plaza_game_swalot_plop_data.s (part 1 of 6) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

#include "global.h"

#include "application/plaza_game_swalot_plop.h"

#pragma force_active on

const u32 gSwalotPlopHitPoints[4] = { 0x00000064, 0x000000C8, 0x0000012C, 0 };

const u16 gSwalotPlopSceneAnimFiles[6] = { 0x001A, 0x001B, 0x001C, 0x001D, 0x001E, 0x001F };

const VecFx32 gSwalotPlopBodyOffset = { 0, -368640, 0 };

const SwalotPlopAnimRange gSwalotPlopSpecialAnimRanges[5] = {
    { 0x00, 0x00 },
    { 0x01, 0x0A },
    { 0x0B, 0x14 },
    { 0x15, 0x1E },
    { 0x1F, 0x28 },
};

const u16 gSwalotPlopStageFiles[4] = { 0x0023, 0x0023, 0x0022, 0x0021 };

const u16 gSwalotPlopSceneModelFiles[3] = { 0x0017, 0x0018, 0x0019 };

const u16 gSwalotPlopStageAnimModels[3] = { 0, 1, 1 };

const u16 gSwalotPlopStageAnimFiles[3] __attribute__((aligned(4))) = { 0x0026, 0x0027, 0x0028 };
