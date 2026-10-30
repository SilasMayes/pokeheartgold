// Converted from asm/pokewalker_data.s (part 14 of 15) by tools/s2c.py.
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

const EventLogBgTemplates gEventLogBgTemplates = {
    {
     { 0, 0, 0x00000800, 0, 0x01, 0x00, 0x00, 0x01, 0x00, 0x03, 0x00, 0x00, 0 },
     { 0, 0, 0x00000800, 0, 0x01, 0x00, 0x01, 0x02, 0x00, 0x02, 0x00, 0x00, 0 },
     { 0, 0, 0x00000800, 0, 0x01, 0x00, 0x02, 0x03, 0x00, 0x01, 0x00, 0x00, 0 },
     { 0, 0, 0x00000800, 0, 0x01, 0x00, 0x00, 0x01, 0x00, 0x03, 0x00, 0x00, 0 },
     { 0, 0, 0x00000800, 0, 0x01, 0x00, 0x01, 0x02, 0x00, 0x00, 0x00, 0x00, 0 },
     },
};

const ManagedSpriteTemplate gEventLogSpriteTemplate = {
    0,
    0,
    0,
    0,
    0,
    65535,
    NNS_G2D_VRAM_TYPE_2DMAIN,
    { 0, 0, 0, 0, 0, 0 },
    2,
    0,
};

const ManagedSpriteTemplate gEventLogEffectSpriteTemplate = {
    0,
    0,
    0,
    0,
    0,
    65535,
    NNS_G2D_VRAM_TYPE_2DMAIN,
    { 1, 1, 1, 1, 0, 0 },
    2,
    0,
};

const ManagedSpriteTemplate gEventLogMonSpriteTemplate = {
    0,
    0,
    0,
    0,
    0,
    65535,
    NNS_G2D_VRAM_TYPE_2DMAIN,
    { 0, 0, 0, 0, 0, 0 },
    2,
    0,
};

// clang-format off
const GraphicsBanks gEventLogGraphicsBanks = {
    GX_VRAM_BG_64_E, GX_VRAM_BGEXTPLTT_NONE, GX_VRAM_SUB_BG_128_C, GX_VRAM_SUB_BGEXTPLTT_NONE,
    GX_VRAM_OBJ_256_AB, GX_VRAM_OBJEXTPLTT_NONE, GX_VRAM_SUB_OBJ_16_I, GX_VRAM_SUB_OBJEXTPLTT_NONE,
    GX_VRAM_TEX_NONE, GX_VRAM_TEXPLTT_NONE,
};
// clang-format on

const OamManagerParam gEventLogOamManagerParam = { 0, 128, 0, 32, 0, 128, 0, 32 };

const WindowTemplate gEventLogWindowTemplates[4] = {
    { 0x02, 0x02, 0x01, 0x0D, 0x02, 0x0E, 1      },
    { 0x02, 0x16, 0x01, 0x08, 0x02, 0x0E, 0x001B },
    { 0x02, 0x03, 0x0C, 0x1B, 0x08, 0x0E, 0x002B },
    { 0x02, 0x19, 0x15, 0x06, 0x02, 0x06, 0x0103 },
};

const SpriteResourceCountsListUnion gEventLogSpriteResourceCounts = { 6, 4, 4, 4, 0, 0 };

// clang-format off
const OamCharTransferParam gEventLogOamTransferParam = {
    0, 262144, 16384, GX_OBJVRAMMODE_CHAR_1D_256K, GX_OBJVRAMMODE_CHAR_1D_32K,
};
// clang-format on

const GraphicsModes gEventLogGraphicsModes = { GX_DISPMODE_GRAPHICS, GX_BGMODE_0, GX_BGMODE_0, GX_BG0_AS_2D };

const u16 gEventLogInvalidName[4] = { 0x000C, 0x004B, 0xFFFF, 0 };
