// Converted from asm/plaza_game_swalot_plop_data.s (part 6 of 6) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

#include "global.h"

#include "application/plaza_game_swalot_plop.h"

#pragma force_active on

const SwalotPlopCommand gSwalotPlopCommands[8] = {
    { SwalotPlop_HandleStart,       SwalotPlop_GetNoDataSize, NULL },
    { SwalotPlop_HandleFinish,      SwalotPlop_GetNoDataSize, NULL },
    { SwalotPlop_HandleShot,        SwalotPlop_GetShotSize,   NULL },
    { SwalotPlop_HandleFinalScore,  SwalotPlop_GetScoreSize,  NULL },
    { SwalotPlop_HandleScores,      SwalotPlop_GetScoresSize, NULL },
    { SwalotPlop_HandleLevel,       SwalotPlop_GetLevelSize,  NULL },
    { SwalotPlop_HandleScoreReport, SwalotPlop_GetScoreSize,  NULL },
    { SwalotPlop_HandleSync,        SwalotPlop_GetNoDataSize, NULL },
};

const u8 gSwalotPlopSceneAnimModels[6] = { 0x00, 0x00, 0x00, 0x02, 0x01, 0x00 };
