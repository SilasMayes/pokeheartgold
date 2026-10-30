// Converted from asm/main_menu_data.s (part 4 of 8) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

#include "global.h"

#include "application/main_menu/agb_cartridge.h"
#include "application/main_menu/main_menu_util.h"

#pragma force_active on

extern char sStr_mywh_SYSSTATE_STOP[20];
extern char sStr_mywh_SYSSTATE_IDLE[20];
extern char sStr_mywh_SYSSTATE_SCANNING[24];
extern char sStr_mywh_SYSSTATE_BUSY[20];
extern char sStr_mywh_SYSSTATE_CONNECTED[24];
extern char sStr_mywh_SYSSTATE_DATASHARING[28];
extern char sStr_mywh_SYSSTATE_KEYSHARING[28];
extern char sStr_mywh_SYSSTATE_MEASURECHANNEL[32];
extern char sStr_mywh_SYSSTATE_CONNECT_FAIL[28];
extern char sStr_mywh_SYSSTATE_ERROR[20];

// clang-format off
const char *gMysteryGiftBeaconStateNames[10] = {
    sStr_mywh_SYSSTATE_STOP, sStr_mywh_SYSSTATE_IDLE, sStr_mywh_SYSSTATE_SCANNING,
    sStr_mywh_SYSSTATE_BUSY, sStr_mywh_SYSSTATE_CONNECTED,
    sStr_mywh_SYSSTATE_DATASHARING, sStr_mywh_SYSSTATE_KEYSHARING,
    sStr_mywh_SYSSTATE_MEASURECHANNEL, sStr_mywh_SYSSTATE_CONNECT_FAIL,
    sStr_mywh_SYSSTATE_ERROR,
};
// clang-format on

char sStr_mywh_SYSSTATE_MEASURECHANNEL[32] = "mywh_SYSSTATE_MEASURECHANNEL";

char sStr_mywh_SYSSTATE_DATASHARING[28] = "mywh_SYSSTATE_DATASHARING";

char sStr_mywh_SYSSTATE_CONNECT_FAIL[28] = "mywh_SYSSTATE_CONNECT_FAIL";

char sStr_mywh_SYSSTATE_KEYSHARING[28] = "mywh_SYSSTATE_KEYSHARING";

char sStr_mywh_SYSSTATE_SCANNING[24] = "mywh_SYSSTATE_SCANNING";

char sStr_mywh_SYSSTATE_CONNECTED[24] = "mywh_SYSSTATE_CONNECTED";

char sStr_mywh_SYSSTATE_BUSY[20] = "mywh_SYSSTATE_BUSY";

char sStr_mywh_SYSSTATE_IDLE[20] = "mywh_SYSSTATE_IDLE";

char sStr_mywh_SYSSTATE_STOP[20] = "mywh_SYSSTATE_STOP";

char sStr_mywh_SYSSTATE_ERROR[20] = "mywh_SYSSTATE_ERROR";
