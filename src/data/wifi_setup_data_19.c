// Converted from asm/wifi_setup_data.s (part 19 of 20) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

#include "global.h"

#include "wifi_setup/wifi_setup.h"
#include "wifi_setup/wifi_setup_internal.h"
#include "wifi_setup/wifi_setup_wcm.h"

#pragma force_active on

u8 gWifiSetupOwnMacAddress[6];

u8 gWifiSetupLinkSearchBssid[6] __attribute__((aligned(4)));

u8 gWifiSetupApBssid[6] __attribute__((aligned(4)));

u8 gWifiSetupSessionKey[16] __attribute__((aligned(4)));
