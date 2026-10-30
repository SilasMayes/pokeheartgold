// Converted from asm/field_move_effects_data.s (part 1 of 6) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

// The C declarations of these do not match the data (see the notes at each
// definition): keep them out of the way of the definitions below.
#define gHallOfFameBallOffsets gHallOfFameBallOffsets_header_decl

#include "global.h"

#include "constants/abilities.h"
#include "constants/items.h"
#include "constants/pokemon.h"
#include "constants/sndseq.h"
#include "constants/species.h"
#include "constants/std_script.h"

#include "field/field_move_cut_in.h"
#include "field/field_move_effects.h"
#include "field/fly_landing_effect.h"

#pragma force_active on

#undef gHallOfFameBallOffsets

extern void CutInFlyer_Hide(void);
extern void CutInFlyer_Idle(void);
extern void CutInFlyer_TakeOff(void);

struct sFlyLandingIdleSteps_Layout {
    void (*unk0)(void);
};
struct sCutInFlyerTakeOffSteps_Layout {
    void (*unk0)(void);
    void (*unk4)(void);
    u32 unk8[2];
    u8 unk10[8];
};
struct sCutInFlyerHideSteps_Layout {
    void (*unk0)(void);
};
extern const struct sFlyLandingIdleSteps_Layout sFlyLandingIdleSteps;
extern void (*const sFlyLandingSteps[8])(void);

// clang-format off
s32 gHealingMachineBallOffsets[18] = {
    -0x4800, 0xC000, -0x4800, 0x4800,
    0xC000, -0x4800, -0x4800, 0xC000,
    0, 0x4800, 0xC000, 0,
    -0x4800, 0xC000, 0x4800, 0x4800,
    0xC000, 0x4800,
};
// clang-format on

// C declares this const, but it lives in .data
VecFx32 gHallOfFameBallOffsets[6] = {
    { -0x4800, 0xC000, -0x4800 },
    { 0x4800,  0xC000, -0x4800 },
    { -0x4800, 0xC000, 0       },
    { 0x4800,  0xC000, 0       },
    { -0x4800, 0xC000, 0x4800  },
    { 0x4800,  0xC000, 0x4800  },
};

const struct sCutInFlyerTakeOffSteps_Layout sCutInFlyerTakeOffSteps = {
    CutInFlyer_TakeOff,
    CutInFlyer_Idle,
    { 0x00, 0x06 },
    { 0x01, 0x00, 0x00, 0x00, 0x0E, 0x00, 0x00, 0x00 },
};

const u16 gCutInTrainerCellFiles[8] = { 0x0012, 0x0015, 0x0018, 0, 0, 0, 0x0010, 0 };

const struct {
    const void *unk0;
    const void *unk4;
    u32 unk8[2];
} gFlyLandingPhases = {
    &sFlyLandingIdleSteps,
    sFlyLandingSteps,
    { 0x01, 0x0F },
};

const u16 gCutInTrainerCharFiles[3] = { 0x0011, 0x0014, 0x0017 };

const u16 gCutInTrainerAnimFiles[3] = { 0x0013, 0x0016, 0x0019 };

const struct sFlyLandingIdleSteps_Layout sFlyLandingIdleSteps = { (void (*)(void))FlyLandingEffect_Idle };

const u16 gCutInTrainerPlttFiles[2] = { 7, 8 };

const struct sCutInFlyerHideSteps_Layout sCutInFlyerHideSteps = { CutInFlyer_Hide };
