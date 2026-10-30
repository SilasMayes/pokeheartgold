// Converted from asm/wifi_setup_data.s (part 13 of 20) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

// The C declarations of these do not match the data (see the notes at each
// definition): keep them out of the way of the definitions below.
#define gWifiSetupResult gWifiSetupResult_header_decl

#include "global.h"

#include "wifi_setup/wifi_setup.h"
#include "wifi_setup/wifi_setup_internal.h"
#include "wifi_setup/wifi_setup_wcm.h"

#pragma force_active on

#undef gWifiSetupResult

u8 ov13_0224E0B0[20];

// C declares this as `WifiSetupResult gWifiSetupResult`, but that type is 0xe8 bytes and the label
// covers only 0x14 (later labels overlap it).
u8 gWifiSetupResult[20];

u8 gWifiSetupResultWepKeys[128];
