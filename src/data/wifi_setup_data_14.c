// Converted from asm/wifi_setup_data.s (part 14 of 20) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

// The C declarations of these do not match the data (see the notes at each
// definition): keep them out of the way of the definitions below.
#define gWifiSetupResultWpaKey gWifiSetupResultWpaKey_header_decl

#include "global.h"

#include "wifi_setup/wifi_setup.h"
#include "wifi_setup/wifi_setup_internal.h"
#include "wifi_setup/wifi_setup_wcm.h"

#pragma force_active on

#undef gWifiSetupResultWpaKey

// C declares this as `WifiSetupSettings64 gWifiSetupResultWpaKey`, but that type needs 8-byte
// alignment and the data sits at offset 0x11ac.
u8 gWifiSetupResultWpaKey[64];

u8 gWifiSetupReply[236];
