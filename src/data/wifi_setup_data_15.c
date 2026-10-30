// Converted from asm/wifi_setup_data.s (part 15 of 20) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

// The C declarations of these do not match the data (see the notes at each
// definition): keep them out of the way of the definitions below.
#define gWifiSetupClientSettings gWifiSetupClientSettings_header_decl

#include "global.h"

#include "wifi_setup/wifi_setup.h"
#include "wifi_setup/wifi_setup_internal.h"
#include "wifi_setup/wifi_setup_wcm.h"

#pragma force_active on

#undef gWifiSetupClientSettings

// C declares this as `WifiSetupClientSettings gWifiSetupClientSettings`, but that type is 0x34 bytes
// and the label covers only 0x14 (later labels overlap it).
u8 gWifiSetupClientSettings[20];

u32 gWifiSetupRecvSsid[8];
