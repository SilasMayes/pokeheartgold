// Converted from asm/pokewalker_data.s (part 10 of 15) by tools/s2c.py.
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
const BgTemplate gBoxDisplayBgTemplateSub1 = {
    0, 0, 0x00000800, 0, 0x01, 0x00, 0x1D, 0x00, 0x00, 0x01, 0x00, 0x00, 0,
};
// clang-format on

// clang-format off
const BgTemplate gBoxDisplayBgTemplateSub3 = {
    0, 0, 0x00000800, 0, 0x01, 0x00, 0x1F, 0x02, 0x01, 0x03, 0x00, 0x00, 0,
};
// clang-format on

// clang-format off
const OverlayManagerTemplate gEventLogAppTemplate = {
    PokewalkerEventLog_Init, PokewalkerEventLog_Main, PokewalkerEventLog_Exit, 0xFFFFFFFF,
};
// clang-format on
