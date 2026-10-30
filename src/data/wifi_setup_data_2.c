// Converted from asm/wifi_setup_data.s (part 2 of 20) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

#include "global.h"

#include "wifi_setup/wifi_setup.h"
#include "wifi_setup/wifi_setup_internal.h"
#include "wifi_setup/wifi_setup_wcm.h"

#pragma force_active on

char sStr_ESSID_AOSS[12] = "ESSID-AOSS";

s8 ov13_0224CFB8[4];

u8 ov13_0224CFBC[28];

u8 gWifiSetupJoinReply[640];

u32 gWifiSetupCrc32Table[256];
