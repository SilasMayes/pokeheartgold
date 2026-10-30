// Converted from asm/frontier_script_commands_data.s (part 1 of 11) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

#include "global.h"

#include "frontier/battle_factory_setup.h"
#include "frontier/battle_hall_setup.h"
#include "frontier/battle_tower_setup.h"
#include "frontier/frontier_link_lobby.h"

#include "frontier_script_commands_misc_internal.h"

#pragma force_active on

FS_EXTERN_OVERLAY(OVY_84);

extern void BattleArcadeGameBoard_Exit(void);
extern void BattleArcadeGameBoard_InitOverlay(void);
extern void BattleArcadeGameBoard_Main(void);

const struct {
    void (*unk0)(void);
    void (*unk4)(void);
    void (*unk8)(void);
    u32 unkC;
} gOverlayTemplate_BattleArcadeGameBoard = {
    BattleArcadeGameBoard_InitOverlay,
    BattleArcadeGameBoard_Main,
    BattleArcadeGameBoard_Exit,
    FS_OVERLAY_ID(OVY_84),
};

// clang-format off
const u8 gBattleArcadeParticlePosition[12] __attribute__((aligned(4))) = {
    0x00, 0xF0, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
// clang-format on
