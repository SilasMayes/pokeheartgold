// Converted from asm/battle_menu_data.s (part 2 of 7) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

#include "global.h"

#include "constants/moves.h"

#include "battle/battle_bag_menu.h"
#include "battle/battle_party_menu.h"

#pragma force_active on

extern const DpadMenuBox gBattlePartyPage1CursorBoxes[4];
extern const DpadMenuBox gBattlePartyPage2CursorBoxes[4];
extern const DpadMenuBox gBattlePartyPage5CursorBoxes[5];
extern const DpadMenuBox gBattlePartyPage7CursorBoxes[3];

const int gBattlePartySpriteTemplates[39][5] = {
    { 45078, 45066, 45066, 45066, 0 },
    { 45078, 45066, 45066, 45066, 0 },
    { 45078, 45066, 45066, 45066, 0 },
    { 45078, 45066, 45066, 45066, 0 },
    { 45078, 45066, 45066, 45066, 0 },
    { 45078, 45066, 45066, 45066, 0 },
    { 45078, 45066, 45066, 45066, 0 },
    { 45063, 45063, 45063, 45063, 1 },
    { 45064, 45063, 45063, 45063, 1 },
    { 45065, 45063, 45063, 45063, 1 },
    { 45066, 45063, 45063, 45063, 1 },
    { 45067, 45063, 45063, 45063, 1 },
    { 45068, 45063, 45063, 45063, 1 },
    { 45069, 45064, 45064, 45064, 1 },
    { 45069, 45064, 45064, 45064, 1 },
    { 45069, 45064, 45064, 45064, 1 },
    { 45069, 45064, 45064, 45064, 1 },
    { 45069, 45064, 45064, 45064, 1 },
    { 45069, 45064, 45064, 45064, 1 },
    { 45070, 45065, 45065, 45065, 0 },
    { 45071, 45065, 45065, 45065, 0 },
    { 45072, 45065, 45065, 45065, 0 },
    { 45073, 45065, 45065, 45065, 0 },
    { 45074, 45065, 45065, 45065, 0 },
    { 45075, 45065, 45065, 45065, 0 },
    { 45076, 45065, 45065, 45065, 0 },
    { 45077, 45065, 45065, 45065, 0 },
    { 45079, 45067, 45067, 45067, 0 },
    { 45079, 45067, 45067, 45067, 0 },
    { 45079, 45067, 45067, 45067, 0 },
    { 45079, 45067, 45067, 45067, 0 },
    { 45079, 45067, 45067, 45067, 0 },
    { 45078, 45066, 45066, 45066, 0 },
    { 45078, 45066, 45066, 45066, 0 },
    { 45078, 45066, 45066, 45066, 0 },
    { 45078, 45066, 45066, 45066, 0 },
    { 45078, 45066, 45066, 45066, 0 },
    { 45078, 45066, 45066, 45066, 0 },
    { 45078, 45066, 45066, 45066, 0 },
};

// not static: used above its definition
const DpadMenuBox gBattlePartyPage3CursorBoxes[8] = {
    { 0x08, 0x38, 0x78, 0x58, 0x00, 0x02, 0x00, 0x01 },
    { 0x88, 0x38, 0xF8, 0x58, 0x01, 0x03, 0x00, 0x01 },
    { 0x08, 0x68, 0x78, 0x88, 0x00, 0x84, 0x02, 0x03 },
    { 0x88, 0x68, 0xF8, 0x88, 0x01, 0x87, 0x02, 0x03 },
    { 0x08, 0xA0, 0x20, 0xB8, 0x02, 0x04, 0x04, 0x05 },
    { 0x30, 0xA0, 0x48, 0xB8, 0x02, 0x05, 0x04, 0x06 },
    { 0x68, 0xA0, 0xC0, 0xB8, 0x03, 0x06, 0x05, 0x07 },
    { 0xE0, 0xA0, 0xF8, 0xB8, 0x03, 0x07, 0x06, 0x07 },
};

// not static: used above its definition
const DpadMenuBox gBattlePartyPage0CursorBoxes[7] = {
    { 0x08, 0x08, 0x78, 0x28, 0x06, 0x02, 0x06, 0x01 },
    { 0x88, 0x10, 0xF8, 0x30, 0x04, 0x03, 0x00, 0x02 },
    { 0x08, 0x38, 0x78, 0x58, 0x00, 0x04, 0x01, 0x03 },
    { 0x88, 0x40, 0xF8, 0x60, 0x01, 0x05, 0x02, 0x04 },
    { 0x08, 0x68, 0x78, 0x88, 0x02, 0x01, 0x03, 0x05 },
    { 0x88, 0x70, 0xF8, 0x90, 0x03, 0x06, 0x04, 0x06 },
    { 0xE0, 0xA0, 0xF8, 0xB8, 0x05, 0x00, 0x05, 0x00 },
};

// not static: used above its definition
const DpadMenuBox gBattlePartyPage6CursorBoxes[7] = {
    { 0x08, 0x38, 0x78, 0x58, 0x05, 0x02, 0x00, 0x01 },
    { 0x88, 0x38, 0xF8, 0x58, 0x05, 0x03, 0x00, 0x01 },
    { 0x08, 0x68, 0x78, 0x88, 0x00, 0x04, 0x02, 0x03 },
    { 0x88, 0x68, 0xF8, 0x88, 0x01, 0x06, 0x02, 0x03 },
    { 0x48, 0x98, 0xB8, 0xB8, 0x02, 0x04, 0x04, 0x06 },
    { 0xC0, 0x08, 0xF8, 0x18, 0x05, 0x81, 0x00, 0x05 },
    { 0xE0, 0xA0, 0xF8, 0xB8, 0x03, 0x06, 0x04, 0x06 },
};

const BattlePartyMenuPos gBattlePartyListStatusIconPos[6] = {
    { 28,  40  },
    { 156, 48  },
    { 28,  88  },
    { 156, 96  },
    { 28,  136 },
    { 156, 144 },
};

const BattlePartyMenuPos gBattlePartyListIconPos[6] = {
    { 16,  16  },
    { 144, 24  },
    { 16,  64  },
    { 144, 72  },
    { 16,  112 },
    { 144, 120 },
};

static const DpadMenuBox gBattlePartyPage4CursorBoxes[5] = {
    { 0x5C, 0x9D, 0x7C, 0xA5, 0x00, 0x02, 0x00, 0x01 },
    { 0x84, 0x9D, 0xA4, 0xA5, 0x01, 0x03, 0x00, 0x04 },
    { 0x5C, 0xAD, 0x7C, 0xB5, 0x00, 0x02, 0x02, 0x03 },
    { 0x84, 0xAD, 0xA4, 0xB5, 0x01, 0x03, 0x02, 0x04 },
    { 0xE0, 0xA0, 0xF8, 0xB8, 0x04, 0x04, 0x83, 0x04 },
};

// clang-format off
const DpadMenuBox *const gBattlePartyPageCursorBoxes[10] = {
    gBattlePartyPage0CursorBoxes, gBattlePartyPage1CursorBoxes,
    gBattlePartyPage2CursorBoxes, gBattlePartyPage3CursorBoxes,
    gBattlePartyPage4CursorBoxes, gBattlePartyPage5CursorBoxes,
    gBattlePartyPage6CursorBoxes, gBattlePartyPage7CursorBoxes,
    gBattlePartyPage6CursorBoxes, gBattlePartyPage7CursorBoxes,
};
// clang-format on

// not static: used above its definition
const DpadMenuBox gBattlePartyPage5CursorBoxes[5] = {
    { 0x08, 0x38, 0x78, 0x58, 0x00, 0x02, 0x00, 0x01 },
    { 0x88, 0x38, 0xF8, 0x58, 0x01, 0x03, 0x00, 0x01 },
    { 0x08, 0x68, 0x78, 0x88, 0x00, 0x04, 0x02, 0x03 },
    { 0x88, 0x68, 0xF8, 0x88, 0x01, 0x04, 0x02, 0x03 },
    { 0xE0, 0xA0, 0xF8, 0xB8, 0x83, 0x04, 0x04, 0x04 },
};

const BattlePartyMenuPos gBattlePartyLearnMoveMoveIconPos[5] = {
    { 24,  80  },
    { 152, 80  },
    { 24,  128 },
    { 152, 128 },
    { 88,  176 },
};

// not static: used above its definition
const DpadMenuBox gBattlePartyPage2CursorBoxes[4] = {
    { 0x08, 0xA0, 0x20, 0xB8, 0x00, 0x00, 0x00, 0x01 },
    { 0x30, 0xA0, 0x48, 0xB8, 0x01, 0x01, 0x00, 0x02 },
    { 0x68, 0xA0, 0xC0, 0xB8, 0x02, 0x02, 0x01, 0x03 },
    { 0xE0, 0xA0, 0xF8, 0xB8, 0x03, 0x03, 0x02, 0x03 },
};

const BattlePartyMenuPos gBattlePartyCheckMovesMoveIconPos[4] = {
    { 24,  80  },
    { 152, 80  },
    { 24,  128 },
    { 152, 128 },
};

// not static: used above its definition
const DpadMenuBox gBattlePartyPage1CursorBoxes[4] = {
    { 0x10, 0x10, 0xF0, 0x88, 0x00, 0x81, 0x00, 0x00 },
    { 0x08, 0xA0, 0x60, 0xB8, 0x00, 0x01, 0x01, 0x02 },
    { 0x70, 0xA0, 0xC8, 0xB8, 0x00, 0x02, 0x01, 0x03 },
    { 0xE0, 0xA0, 0xF8, 0xB8, 0x00, 0x03, 0x02, 0x03 },
};

const SpriteResourceCountsListUnion gBattlePartySpriteCapacities = { 18, 6, 6, 6, 0, 0 };

// not static: used above its definition
const DpadMenuBox gBattlePartyPage7CursorBoxes[3] = {
    { 0x08, 0xA0, 0xC8, 0xB8, 0x01, 0x00, 0x00, 0x02 },
    { 0xC0, 0x08, 0xF8, 0x18, 0x01, 0x82, 0x00, 0x01 },
    { 0xE0, 0xA0, 0xF8, 0xB8, 0x01, 0x02, 0x00, 0x02 },
};

const BattlePartyMenuPos gBattlePartyMoveDetailTypeIconPos[2] = {
    { 130, 16 },
    { 164, 16 }
};

const BattlePartyMenuPos gBattlePartyForgetMoveTypeIconPos[2] = {
    { 130, 16 },
    { 164, 16 }
};

const BattlePartyMenuPos gBattlePartySummaryTypeIconPos[2] = {
    { 130, 16 },
    { 164, 16 }
};

const BattlePartyMenuPos gBattlePartyCheckMovesTypeIconPos[2] = {
    { 130, 16 },
    { 164, 16 }
};

const BattlePartyMenuPos gBattlePartyLearnMoveTypeIconPos[2] = {
    { 130, 16 },
    { 164, 16 }
};
