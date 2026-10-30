// Converted from asm/wireless_trade_select_mon_data.s (part 2 of 4) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

// The C declarations of these do not match the data (see the notes at each
// definition): keep them out of the way of the definitions below.
#define sWirelessTradeSelectMonDetailSpritePos  sWirelessTradeSelectMonDetailSpritePos_header_decl
#define sWirelessTradeSelectMonDetailSpritePosY sWirelessTradeSelectMonDetailSpritePosY_header_decl

#include "global.h"

#include "wireless_trade_select_mon_internal.h"

#pragma force_active on

#undef sWirelessTradeSelectMonDetailSpritePos
#undef sWirelessTradeSelectMonDetailSpritePosY

// clang-format off
const u32 sWirelessTradeSelectMonBallPalettes[24] = {
    0x00000031, 0x00000033, 0x00000033, 0x00000031, 0x00000032, 0x00000032, 0x00000032, 0x00000032,
    0x00000033, 0x00000033, 0x00000033, 0x00000033, 0x00000034, 0x00000034, 0x00000033, 0x00000031,
    0x00000035, 0x00000036, 0x00000037, 0x00000038, 0x00000039, 0x0000003A, 0x0000003B, 0x0000003C,
};
// clang-format on

#ifdef SDK_PORT
// clang-format off
const WirelessTradeDetailSpritePos sWirelessTradeSelectMonDetailSpritePosY[2] = { { 0x58, 0, 0xC0 }, { 0x58, 1, 0x10 } };
// clang-format on
#else
// C declares this as `const WirelessTradeDetailSpritePos sWirelessTradeSelectMonDetailSpritePosY[]`,
// but the label holds 8 more bytes of data after it.
// clang-format off
const u8 sWirelessTradeSelectMonDetailSpritePosY[68] = {
    0x58, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x00, 0x00, 0x00, 0x58, 0x00, 0x00, 0x00,
    0x01, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00,
    0x90, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x63, 0x00, 0x00, 0x00,
    0x08, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0xE3, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00,
    0x06, 0x00, 0x00, 0x00,
};
// clang-format on
#endif

#ifdef SDK_PORT
// On the DS sWirelessTradeSelectMonDetailSpritePosY is the same table read from its y member;
// the port has a complete copy for each label.
// clang-format off
const WirelessTradeDetailSpritePos sWirelessTradeSelectMonDetailSpritePos[6] = {
    { 0x3F, 0x58, 0 },
    { 0xC0, 0x58, 1 },
    { 0x10, 8, 8 },
    { 0x90, 8, 8 },
    { 0x63, 8, 6 },
    { 0xE3, 8, 6 },
};
// clang-format on
#else
// C declares this as `const WirelessTradeDetailSpritePos sWirelessTradeSelectMonDetailSpritePos[]`,
// but one element of that type is larger than the data under this label.
const u8 sWirelessTradeSelectMonDetailSpritePos[4] = { 0x3F, 0x00, 0x00, 0x00 };
#endif
