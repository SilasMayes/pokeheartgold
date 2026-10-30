// Converted from asm/wifi_setup_data.s (part 10 of 20) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

// The C declarations of these do not match the data (see the notes at each
// definition): keep them out of the way of the definitions below.
#define gWifiSetupWork gWifiSetupWork_header_decl

#include "global.h"

#include "wifi_setup/wifi_setup.h"
#include "wifi_setup/wifi_setup_internal.h"
#include "wifi_setup/wifi_setup_wcm.h"

#pragma force_active on

#undef gWifiSetupWork

u8 gWifiSetupWcmSearchBssid[6];

u8 gWifiSetupWcmSearchSsid[32] __attribute__((aligned(4)));

// C declares this as `WifiSetupWork gWifiSetupWork`, but that type is 0x80 bytes and the label covers
// only 0x50 (later labels overlap it).
u8 gWifiSetupWork[80];
