// Converted from asm/wireless_trade_select_mon_data.s (part 4 of 4) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

// The C declarations of these do not match the data (see the notes at each
// definition): keep them out of the way of the definitions below.
#define sWirelessTradeSelectMonRosterListTemplate sWirelessTradeSelectMonRosterListTemplate_header_decl

#include "global.h"

#include "wireless_trade_select_mon_internal.h"

#pragma force_active on

#undef sWirelessTradeSelectMonRosterListTemplate

const WirelessTradeWindowTemplate sWirelessTradeSelectMonDetailWindows[8] = {
    { 4,      1,      9,      2, 1      },
    { 0x0014, 1,      9,      2, 0x0013 },
    { 4,      3,      8,      2, 0x0025 },
    { 0x0014, 3,      8,      2, 0x0035 },
    { 2,      0x0013, 7,      2, 0x0045 },
    { 0x0012, 0x0013, 7,      2, 0x0053 },
    { 2,      0x0015, 0x000C, 2, 0x0061 },
    { 0x0012, 0x0015, 0x000C, 2, 0x0079 },
};

const WirelessTradeWindowPos sWirelessTradeSelectMonNameWindowPos[14] = {
    { 0,      7      },
    { 8,      7      },
    { 0,      0x000C },
    { 8,      0x000C },
    { 0,      0x0011 },
    { 8,      0x0011 },
    { 0x0010, 7      },
    { 0x0018, 7      },
    { 0x0010, 0x000C },
    { 0x0018, 0x000C },
    { 0x0010, 0x0011 },
    { 0x0018, 0x0011 },
    { 4,      8      },
    { 0x0014, 8      },
};

// C declares this as `const ListMenuTemplate sWirelessTradeSelectMonRosterListTemplate`, but that type
// does not describe the data.
// clang-format off
const u8 sWirelessTradeSelectMonRosterListTemplate[32] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x20, 0x00, 0x20, 0x00, 0x00, 0x08, 0x00, 0x10, 0x2F, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
};
// clang-format on
