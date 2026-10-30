// Converted from asm/wifi_setup_data.s (part 20 of 20) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

#include "global.h"

#include "wifi_setup/wifi_setup.h"
#include "wifi_setup/wifi_setup_internal.h"
#include "wifi_setup/wifi_setup_wcm.h"

#pragma force_active on

u8 gWifiSetupSettingsKey[8];

u8 gWifiSetupTimestampDigest[24];

u8 gWifiSetupLinkSearchSsid[32];

char gWifiSetupApSsid[36];

u8 gWifiSetupPacketBuffer[2048];

u8 gWifiSetupRecordBuffer[2048];
