// Converted from asm/battle_menu_data.s (part 3 of 7) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

#include "global.h"

#include "constants/moves.h"

#include "battle/battle_bag_menu.h"
#include "battle/battle_party_menu.h"

#pragma force_active on

extern const u8 gBattlePartyButton0Windows[4];
extern const u8 gBattlePartyButton1Windows[4];
extern const u8 gBattlePartyButton2Windows[4];
extern const u8 gBattlePartyButton3Windows[4];
extern const u8 gBattlePartyButton4Windows[4];
extern const u8 gBattlePartyButton5Windows[4];
extern const u8 gBattlePartyButton7Windows[4];
extern const u8 gBattlePartyButton8Windows[4];
extern const u8 gBattlePartyButton9Windows[4];
extern const u8 gBattlePartyButton10Windows[4];
extern const u8 gBattlePartyButton11Windows[4];
extern const u8 gBattlePartyButton14Windows[4];
extern const u8 gBattlePartyButton15Windows[4];
extern const u8 gBattlePartyButton16Windows[4];
extern const u8 gBattlePartyButton17Windows[4];
extern const u8 gBattlePartyButton19Windows[4];
extern const u8 gBattlePartyButton20Windows[4];
extern const u8 gBattlePartyButton21Windows[4];
extern const u8 gBattlePartyButton22Windows[4];
extern const u8 gBattlePartyButton23Windows[4];
extern const u8 gBattlePartyButton24Windows[4];
extern const u8 gBattlePartyButton25Windows[4];
extern const u8 gBattlePartyButton26Windows[4];
extern const u8 gBattlePartyButton27Windows[4];
extern const u8 gBattlePartyButton28Windows[4];
extern const u8 gBattlePartyButton29Windows[4];

const u8 gBattlePartyButtonRects[34][4] = {
    { 0x00, 0x00, 0x10, 0x06 },
    { 0x10, 0x01, 0x10, 0x06 },
    { 0x00, 0x06, 0x10, 0x06 },
    { 0x10, 0x07, 0x10, 0x06 },
    { 0x00, 0x0C, 0x10, 0x06 },
    { 0x10, 0x0D, 0x10, 0x06 },
    { 0x1B, 0x13, 0x05, 0x05 },
    { 0x01, 0x01, 0x1E, 0x11 },
    { 0x00, 0x13, 0x0D, 0x05 },
    { 0x0C, 0x13, 0x0D, 0x05 },
    { 0x0D, 0x13, 0x0D, 0x05 },
    { 0x0C, 0x13, 0x0D, 0x05 },
    { 0x00, 0x13, 0x05, 0x05 },
    { 0x05, 0x13, 0x05, 0x05 },
    { 0x00, 0x06, 0x10, 0x06 },
    { 0x10, 0x06, 0x10, 0x06 },
    { 0x00, 0x0C, 0x10, 0x06 },
    { 0x10, 0x0C, 0x10, 0x06 },
    { 0x17, 0x00, 0x09, 0x04 },
    { 0x00, 0x06, 0x10, 0x06 },
    { 0x10, 0x06, 0x10, 0x06 },
    { 0x00, 0x0C, 0x10, 0x06 },
    { 0x10, 0x0C, 0x10, 0x06 },
    { 0x00, 0x06, 0x10, 0x06 },
    { 0x10, 0x06, 0x10, 0x06 },
    { 0x00, 0x0C, 0x10, 0x06 },
    { 0x10, 0x0C, 0x10, 0x06 },
    { 0x08, 0x12, 0x10, 0x06 },
    { 0x00, 0x13, 0x1A, 0x05 },
    { 0x00, 0x13, 0x1A, 0x05 },
    { 0x0B, 0x13, 0x05, 0x02 },
    { 0x10, 0x13, 0x05, 0x02 },
    { 0x0B, 0x15, 0x05, 0x02 },
    { 0x10, 0x15, 0x05, 0x02 },
};

// clang-format off
const u8 *const gBattlePartyButtonWindowLists[34] = {
    gBattlePartyButton0Windows, gBattlePartyButton1Windows,
    gBattlePartyButton2Windows, gBattlePartyButton3Windows,
    gBattlePartyButton4Windows, gBattlePartyButton5Windows, NULL,
    gBattlePartyButton7Windows, gBattlePartyButton8Windows,
    gBattlePartyButton9Windows, gBattlePartyButton10Windows,
    gBattlePartyButton11Windows, NULL, NULL, gBattlePartyButton14Windows,
    gBattlePartyButton15Windows, gBattlePartyButton16Windows,
    gBattlePartyButton17Windows, NULL, gBattlePartyButton19Windows,
    gBattlePartyButton20Windows, gBattlePartyButton21Windows,
    gBattlePartyButton22Windows, gBattlePartyButton23Windows,
    gBattlePartyButton24Windows, gBattlePartyButton25Windows,
    gBattlePartyButton26Windows, gBattlePartyButton27Windows,
    gBattlePartyButton28Windows, gBattlePartyButton29Windows, NULL, NULL, NULL, NULL,
};
// clang-format on

const s16 gBattlePartyButtonSpriteOffsets[3] = { 2, -4, 2 };

const s16 gBattlePartySlotButtonSpriteOffsets[3] = { 2, -3, 1 };

// global: C declares it extern although the asm label was local
const u8 gBattlePartyButton17Windows[4] = { 0x0A, 0x04, 0xFF, 0x00 };

// global: C declares it extern although the asm label was local
const u8 gBattlePartyButton16Windows[4] = { 0x09, 0x03, 0xFF, 0x00 };

// global: C declares it extern although the asm label was local
const u8 gBattlePartyButton15Windows[4] = { 0x08, 0x02, 0xFF, 0x00 };

const u8 gBattlePartyButtonScrollAmounts[4] = { 0x02, 0x04, 0x02, 0x00 };

// global: C declares it extern although the asm label was local
const u8 gBattlePartyButton14Windows[4] = { 0x07, 0x01, 0xFF, 0x00 };

// global: C declares it extern although the asm label was local
const u8 gBattlePartyButton7Windows[4] = { 0x00, 0x01, 0xFF, 0x00 };

// global: C declares it extern although the asm label was local
const u8 gBattlePartyButton11Windows[4] = { 0x15, 0xFF, 0x00, 0x00 };

// global: C declares it extern although the asm label was local
const u8 gBattlePartyButton9Windows[4] = { 0x05, 0xFF, 0x00, 0x00 };

// global: C declares it extern although the asm label was local
const u8 gBattlePartyButton25Windows[4] = { 0x03, 0xFF, 0x00, 0x00 };

// global: C declares it extern although the asm label was local
const u8 gBattlePartyButton2Windows[4] = { 0x02, 0xFF, 0x00, 0x00 };

// global: C declares it extern although the asm label was local
const u8 gBattlePartyButton26Windows[4] = { 0x04, 0xFF, 0x00, 0x00 };

// global: C declares it extern although the asm label was local
const u8 gBattlePartyButton19Windows[4] = { 0x01, 0xFF, 0x00, 0x00 };

// global: C declares it extern although the asm label was local
const u8 gBattlePartyButton20Windows[4] = { 0x02, 0xFF, 0x00, 0x00 };

// global: C declares it extern although the asm label was local
const u8 gBattlePartyButton28Windows[4] = { 0x0B, 0xFF, 0x00, 0x00 };

const u8 gBattlePartySlotButtonScrollAmounts[4] = { 0x02, 0x03, 0x01, 0x00 };

// global: C declares it extern although the asm label was local
const u8 gBattlePartyButton22Windows[4] = { 0x04, 0xFF, 0x00, 0x00 };

// global: C declares it extern although the asm label was local
const u8 gBattlePartyButton29Windows[4] = { 0x06, 0xFF, 0x00, 0x00 };

// global: C declares it extern although the asm label was local
const u8 gBattlePartyButton24Windows[4] = { 0x02, 0xFF, 0x00, 0x00 };

// global: C declares it extern although the asm label was local
const u8 gBattlePartyButton5Windows[4] = { 0x05, 0xFF, 0x00, 0x00 };

// global: C declares it extern although the asm label was local
const u8 gBattlePartyButton3Windows[4] = { 0x03, 0xFF, 0x00, 0x00 };

// global: C declares it extern although the asm label was local
const u8 gBattlePartyButton27Windows[4] = { 0x05, 0xFF, 0x00, 0x00 };

// global: C declares it extern although the asm label was local
const u8 gBattlePartyButton10Windows[4] = { 0x03, 0xFF, 0x00, 0x00 };

// global: C declares it extern although the asm label was local
const u8 gBattlePartyButton1Windows[4] = { 0x01, 0xFF, 0x00, 0x00 };

// global: C declares it extern although the asm label was local
const u8 gBattlePartyButton23Windows[4] = { 0x01, 0xFF, 0x00, 0x00 };

// global: C declares it extern although the asm label was local
const u8 gBattlePartyButton0Windows[4] = { 0x00, 0xFF, 0x00, 0x00 };

// global: C declares it extern although the asm label was local
const u8 gBattlePartyButton21Windows[4] = { 0x03, 0xFF, 0x00, 0x00 };

// global: C declares it extern although the asm label was local
const u8 gBattlePartyButton4Windows[4] = { 0x04, 0xFF, 0x00, 0x00 };

// global: C declares it extern although the asm label was local
const u8 gBattlePartyButton8Windows[4] = { 0x02, 0xFF, 0x00, 0x00 };
