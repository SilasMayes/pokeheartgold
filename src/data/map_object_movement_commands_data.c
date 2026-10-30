// Converted from asm/map_object_movement_commands_data.s by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout. Keep that when editing, or rerun tools/s2c.py.

#include "global.h"

#include "constants/field_move_response.h"
#include "constants/flags.h"
#include "constants/items.h"
#include "constants/maps.h"
#include "constants/pokemon.h"
#include "constants/sndseq.h"
#include "constants/species.h"
#include "constants/std_script.h"
#include "constants/vars.h"

#include "fielddata/script/scr_seq/event_D24R0204.h"

#include "map_object_movement_commands_internal.h"

#pragma force_active on

// clang-format off
const fx32 gJumpHeightTable1[16] = {
    0, 8192, 12288, 16384, 20480, 24576, 24576, 24576, 20480, 20480, 16384, 12288, 8192, 0, 0, 0,
};
// clang-format on

// clang-format off
const fx32 gJumpHeightTable2[16] = {
    8192, 16384, 24576, 32768, 36864, 40960, 40960, 40960, 36864, 32768, 24576, 20480, 12288, 8192, 0, 0,
};
// clang-format on

// clang-format off
const fx32 gJumpHeightTable0[16] = {
    16384, 24576, 32768, 40960, 45056, 49152, 49152, 49152, 45056, 40960, 36864, 32768, 24576, 16384, 0, 0,
};
// clang-format on

// clang-format off
const u32 gVariableSpeedWalk_Cmd098[7] = {
    0x00002500, 0x00002480, 0x00002480, 0x00002480, 0x00002480, 0x00002480, 0x00002480,
};
// clang-format on

void (*const gMovementScriptMachineStateFuncs[6])(void) = {
    (void (*)(void))MovementScriptMachineSub_Init,
    (void (*)(void))MovementScriptMachineSub_WaitReady,
    (void (*)(void))MovementScriptMachineSub_SetMovementCommand,
    (void (*)(void))MovementScriptMachineSub_WaitMovementCommand,
    (void (*)(void))MovementScriptMachineSub_LoopCheck,
    (void (*)(void))MovementScriptMachineSub_Done,
};

// clang-format off
const u32 gVariableSpeedWalk_Cmd076[6] = {
    0x00002000, 0x00003000, 0x00003000, 0x00002000, 0x00003000, 0x00003000,
};
// clang-format on

const MovementList _020FDA28 = {
    { 8, 9, 0x0000000A, 0x0000000B }
};

const u32 gVariableSpeedWalk_Cmd082[3] = { 0x00005000, 0x00006000, 0x00005000 };

// clang-format off
const fx32 *gJumpHeightTables[3] = {
    gJumpHeightTable0, gJumpHeightTable1, gJumpHeightTable2,
};
// clang-format on
