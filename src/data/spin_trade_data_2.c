// Converted from asm/spin_trade_data.s (part 2 of 6) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

#include "global.h"

#pragma force_active on

extern void SpinTradeEggDrop_Fall(void);
extern void SpinTradeEggDrop_Init(void);
extern void SpinTradeEggDrop_Land(void);

// 0x021EA538
// clang-format off
const u8 gSpinTradeGraphicsModes[16] = {
    0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
};
// clang-format on

// clang-format off
const u8 gSpinTradeNameWindowTemplates2P[16] = {
    0x01, 0x0C, 0x12, 0x08, 0x02, 0x0F, 0x94, 0x00, 0x01, 0x0C, 0x06, 0x08, 0x02, 0x0F, 0xBC, 0x00,
};
// clang-format on

// 0x021EA528
// clang-format off
const u8 gSpinTradeCountdownSounds[16] = {
    0xDD, 0x05, 0x00, 0x00, 0xDD, 0x05, 0x00, 0x00, 0xDD, 0x05, 0x00, 0x00, 0x42, 0x06, 0x00, 0x00,
};
// clang-format on

// 0x021EA51C
void (*const gSpinTradeEggDropStateFuncs[3])(void) = {
    SpinTradeEggDrop_Init,
    SpinTradeEggDrop_Fall,
    SpinTradeEggDrop_Land,
};

const u8 gSpinTradeBonusRanges4P[8] = { 0x25, 0x00, 0x8E, 0x00, 0xD7, 0x00, 0x43, 0x01 };
