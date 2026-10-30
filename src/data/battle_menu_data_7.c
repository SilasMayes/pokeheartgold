// Converted from asm/battle_menu_data.s (part 7 of 7) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

#include "global.h"

#include "constants/moves.h"

#include "battle/battle_bag_menu.h"
#include "battle/battle_party_menu.h"

#pragma force_active on

extern const u8 gBattleBagButton0Windows[4];
extern const u8 gBattleBagButton1Windows[4];
extern const u8 gBattleBagButton2Windows[4];
extern const u8 gBattleBagButton3Windows[4];
extern const u8 gBattleBagButton4Windows[4];
extern const u8 gBattleBagButton6Windows[4];
extern const u8 gBattleBagButton7Windows[4];
extern const u8 gBattleBagButton8Windows[4];
extern const u8 gBattleBagButton9Windows[4];
extern const u8 gBattleBagButton10Windows[4];
extern const u8 gBattleBagButton11Windows[4];
extern const u8 gBattleBagButton15Windows[4];
extern const u8 gBattleBagButton17Windows[4];
extern const u8 gBattleBagButton18Windows[4];
extern const u8 gBattleBagButton19Windows[4];
extern const u8 gBattleBagButton20Windows[4];
extern const u8 gBattleBagButton21Windows[4];
extern const u8 gBattleBagButton22Windows[4];

// clang-format off
const u8 *const gBattleBagButtonWindowLists[23] = {
    gBattleBagButton0Windows, gBattleBagButton1Windows, gBattleBagButton2Windows,
    gBattleBagButton3Windows, gBattleBagButton4Windows, NULL,
    gBattleBagButton6Windows, gBattleBagButton7Windows, gBattleBagButton8Windows,
    gBattleBagButton9Windows, gBattleBagButton10Windows, gBattleBagButton11Windows,
    NULL, NULL, NULL, gBattleBagButton15Windows, NULL, gBattleBagButton17Windows,
    gBattleBagButton18Windows, gBattleBagButton19Windows,
    gBattleBagButton20Windows, gBattleBagButton21Windows,
    gBattleBagButton22Windows,
};
// clang-format on

const BattleBagButtonRect gBattleBagButtonRects[17] = {
    { 0x00, 0x01, 0x10, 0x09 },
    { 0x00, 0x0A, 0x10, 0x09 },
    { 0x10, 0x01, 0x10, 0x09 },
    { 0x10, 0x0A, 0x10, 0x09 },
    { 0x00, 0x13, 0x1A, 0x05 },
    { 0x1B, 0x13, 0x05, 0x05 },
    { 0x20, 0x01, 0x10, 0x06 },
    { 0x30, 0x01, 0x10, 0x06 },
    { 0x20, 0x07, 0x10, 0x06 },
    { 0x30, 0x07, 0x10, 0x06 },
    { 0x20, 0x0D, 0x10, 0x06 },
    { 0x30, 0x0D, 0x10, 0x06 },
    { 0x20, 0x13, 0x05, 0x05 },
    { 0x25, 0x13, 0x05, 0x05 },
    { 0x3B, 0x13, 0x05, 0x05 },
    { 0x00, 0x33, 0x1A, 0x05 },
    { 0x1B, 0x33, 0x05, 0x05 },
};

// global: C declares it extern although the asm label was local
const u8 gBattleBagButton17Windows[4] = { 0x0C, 0x0D, 0xFF, 0x00 };

// global: C declares it extern although the asm label was local
const u8 gBattleBagButton11Windows[4] = { 0x0A, 0x0B, 0xFF, 0x00 };

// global: C declares it extern although the asm label was local
const u8 gBattleBagButton20Windows[4] = { 0x12, 0x13, 0xFF, 0x00 };

// global: C declares it extern although the asm label was local
const u8 gBattleBagButton10Windows[4] = { 0x08, 0x09, 0xFF, 0x00 };

// global: C declares it extern although the asm label was local
const u8 gBattleBagButton6Windows[4] = { 0x00, 0x01, 0xFF, 0x00 };

// global: C declares it extern although the asm label was local
const u8 gBattleBagButton7Windows[4] = { 0x02, 0x03, 0xFF, 0x00 };

// global: C declares it extern although the asm label was local
const u8 gBattleBagButton8Windows[4] = { 0x04, 0x05, 0xFF, 0x00 };

// global: C declares it extern although the asm label was local
const u8 gBattleBagButton9Windows[4] = { 0x06, 0x07, 0xFF, 0x00 };

// global: C declares it extern although the asm label was local
const u8 gBattleBagButton3Windows[4] = { 0x03, 0xFF, 0x00, 0x00 };

// global: C declares it extern although the asm label was local
const u8 gBattleBagButton21Windows[4] = { 0x14, 0x15, 0xFF, 0x00 };

// global: C declares it extern although the asm label was local
const u8 gBattleBagButton18Windows[4] = { 0x0E, 0x0F, 0xFF, 0x00 };

// global: C declares it extern although the asm label was local
const u8 gBattleBagButton0Windows[4] = { 0x00, 0xFF, 0x00, 0x00 };

// global: C declares it extern although the asm label was local
const u8 gBattleBagButton2Windows[4] = { 0x02, 0xFF, 0x00, 0x00 };

// global: C declares it extern although the asm label was local
const u8 gBattleBagButton22Windows[4] = { 0x16, 0x17, 0xFF, 0x00 };

// global: C declares it extern although the asm label was local
const u8 gBattleBagButton19Windows[4] = { 0x10, 0x11, 0xFF, 0x00 };

// global: C declares it extern although the asm label was local
const u8 gBattleBagButton15Windows[4] = { 0x03, 0xFF, 0x00, 0x00 };

// global: C declares it extern although the asm label was local
const u8 gBattleBagButton4Windows[4] = { 0x04, 0xFF, 0x00, 0x00 };

// global: C declares it extern although the asm label was local
const u8 gBattleBagButton1Windows[4] = { 0x01, 0xFF, 0x00, 0x00 };
