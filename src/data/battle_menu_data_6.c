// Converted from asm/battle_menu_data.s (part 6 of 7) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

#include "global.h"

#include "constants/moves.h"

#include "battle/battle_bag_menu.h"
#include "battle/battle_party_menu.h"

#pragma force_active on

const int gBattleBagSpriteTemplates[6][5] = {
    { 46263, 46263, 46263, 46263, 1 },
    { 46264, 46264, 46263, 46263, 1 },
    { 46265, 46265, 46263, 46263, 1 },
    { 46266, 46266, 46263, 46263, 1 },
    { 46267, 46267, 46263, 46263, 1 },
    { 46268, 46268, 46263, 46263, 1 },
};

// not static: used above its definition
const DpadMenuBox gBattleBagPage1CursorBoxes[7] = {
    { 0x08, 0x10, 0x78, 0x30, 0x00, 0x02, 0x00, 0x01 },
    { 0x88, 0x10, 0xF8, 0x30, 0x01, 0x03, 0x00, 0x01 },
    { 0x08, 0x40, 0x78, 0x60, 0x00, 0x04, 0x02, 0x03 },
    { 0x88, 0x40, 0xF8, 0x60, 0x01, 0x05, 0x02, 0x03 },
    { 0x08, 0x70, 0x78, 0x90, 0x02, 0x06, 0x04, 0x05 },
    { 0x88, 0x70, 0xF8, 0x90, 0x03, 0x06, 0x04, 0x05 },
    { 0xE0, 0xA0, 0xF8, 0xB8, 0x85, 0x06, 0x06, 0x06 },
};

// not static: used above its definition
const DpadMenuBox gBattleBagPage0CursorBoxes[6] = {
    { 0x08, 0x10, 0x78, 0x48, 0x00, 0x01, 0x00, 0x02 },
    { 0x08, 0x58, 0x78, 0x90, 0x00, 0x04, 0x01, 0x03 },
    { 0x88, 0x10, 0xF8, 0x48, 0x02, 0x03, 0x00, 0x02 },
    { 0x88, 0x58, 0xF8, 0x90, 0x02, 0x05, 0x01, 0x03 },
    { 0x08, 0xA0, 0xC8, 0xB8, 0x01, 0x04, 0x04, 0x05 },
    { 0xE0, 0xA0, 0xF8, 0xB8, 0x83, 0x05, 0x04, 0x05 },
};

const s32 gBattleBagItemListIconPos[6][2] = {
    { 44,  45  },
    { 172, 45  },
    { 44,  93  },
    { 172, 93  },
    { 44,  141 },
    { 172, 141 },
};

const SpriteResourceCountsListUnion gBattleBagSpriteCapacities = { 8, 8, 3, 3, 0, 0 };

const s32 gBattleBagTutorialFingerPos[3][2] = {
    { 192, 24  },
    { 64,  16  },
    { 104, 152 }
};

// not static: used above its definition
const DpadMenuBox gBattleBagPage2CursorBoxes[2] = {
    { 0x08, 0xA0, 0xC8, 0xB8, 0x00, 0x00, 0x00, 0x01 },
    { 0xE0, 0xA0, 0xF8, 0xB8, 0x01, 0x01, 0x00, 0x01 },
};

// clang-format off
const DpadMenuBox *const gBattleBagPageCursorBoxes[3] = {
    gBattleBagPage0CursorBoxes, gBattleBagPage1CursorBoxes,
    gBattleBagPage2CursorBoxes,
};
// clang-format on
