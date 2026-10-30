// Converted from asm/footprint_stamp_data.s (part 1 of 3) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

#include "global.h"

#include "application/footprint_stamp.h"

#pragma force_active on

const FootprintStampEffectFuncs gFootprintStampEffectFuncs[11] = {
    { FootprintStamp_UpdateIdle,    NULL,                       FootprintStamp_HitIdle    },
    { FootprintStamp_UpdateVanish,  FootprintStamp_DrawVanish,  FootprintStamp_HitVanish  },
    { FootprintStamp_UpdateSplit,   FootprintStamp_DrawSplit,   FootprintStamp_HitSplit   },
    { FootprintStamp_UpdateZigzag,  NULL,                       FootprintStamp_HitZigzag  },
    { FootprintStamp_UpdateWave,    NULL,                       FootprintStamp_HitWave    },
    { FootprintStamp_UpdateRise,    FootprintStamp_DrawRise,    FootprintStamp_HitRise    },
    { FootprintStamp_UpdateFall,    NULL,                       FootprintStamp_HitFall    },
    { FootprintStamp_UpdateGrow,    NULL,                       FootprintStamp_HitGrow    },
    { FootprintStamp_UpdateSpreadX, FootprintStamp_DrawSpreadX, FootprintStamp_HitSpreadX },
    { FootprintStamp_UpdateSpreadY, FootprintStamp_DrawSpreadY, FootprintStamp_HitSpreadY },
    { FootprintStamp_UpdateStretch, NULL,                       FootprintStamp_HitStretch },
};

// clang-format off
const fx32 gFootprintStampBoardXs[17] = {
    -238076, -209404, -180732, -150012, -121340, -90620, -61948, -31228, -1020, 28676, 57348, 88068, 116740,
    147460, 176132, 206852, 235524,
};
// clang-format on

const FootprintStampBounds gFootprintStampSizeBounds[3] = {
    { -10922, 10922, 10922, -10922 },
    { -16384, 16384, 16384, -16384 },
    { -21844, 21844, 21844, -21844 },
};

// clang-format off
const fx32 gFootprintStampBoardYs[11] = {
    146191, 117519, 87311, 57615, 27919, -2289, -31985, -61681, -91377, -121073, -149745,
};
// clang-format on

// clang-format off
BOOL (*const gFootprintStampCameraEffectFuncs[11])(FootprintStampBoard *unused, FootprintStampBoard *board, Camera *camera) = {
    NULL, FootprintStampCamera_ZoomIn, FootprintStampCamera_Roll, FootprintStampCamera_TurnLeft,
    FootprintStampCamera_TurnRight, FootprintStampCamera_PitchUp, FootprintStampCamera_Sway,
    FootprintStampCamera_ZoomOut, FootprintStampCamera_ShakeX, FootprintStampCamera_ShakeY,
    FootprintStampCamera_PitchDown,
};
// clang-format on

// clang-format off
const u8 gFootprintStampNatureEffects[28] = {
    0x05, 0x01, 0x05, 0x06, 0x06, 0x04, 0x03, 0x09, 0x07, 0x08, 0x01, 0x05, 0x03, 0x08, 0x02, 0x0A, 0x04,
    0x03, 0x09, 0x07, 0x0A, 0x04, 0x06, 0x01, 0x02, 0x00, 0x00, 0x00,
};
// clang-format on

const s16 gFootprintStampCameraChainLengths[10] = { 255, 10, 10, 10, 10, 10, 10, 10, 10, 0 };

// not labelled in the asm
// clang-format off
static const u8 sRodataUnlabeled_0[16] __attribute__((aligned(4))) = {
    0x00, 0x00, 0xFB, 0xFF, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0xFD, 0xFF,
};
// clang-format on
