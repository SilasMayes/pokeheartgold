// Converted from asm/wifi_setup_data.s (part 3 of 20) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

// The C declarations of these do not match the data (see the notes at each
// definition): keep them out of the way of the definitions below.
#define gWifiSetupSecurityRecords gWifiSetupSecurityRecords_header_decl

#include "global.h"

#include "wifi_setup/wifi_setup.h"
#include "wifi_setup/wifi_setup_internal.h"
#include "wifi_setup/wifi_setup_wcm.h"

#pragma force_active on

#undef gWifiSetupSecurityRecords

// clang-format off
u8 sWifiSetupRateMasks[48] = {
    0x01, 0x00, 0x02, 0x00, 0x02, 0x00, 0x04, 0x00, 0x04, 0x00, 0x0B, 0x00, 0x08, 0x00, 0x0C, 0x00,
    0x10, 0x00, 0x12, 0x00, 0x20, 0x00, 0x16, 0x00, 0x40, 0x00, 0x18, 0x00, 0x80, 0x00, 0x24, 0x00,
    0x00, 0x01, 0x30, 0x00, 0x00, 0x02, 0x48, 0x00, 0x00, 0x04, 0x60, 0x00, 0x00, 0x08, 0x6C, 0x00,
};
// clang-format on

char sStr_MELCO[8] = "MELCO";

// C declares this as `WifiSetupAossKeyRecords gWifiSetupSecurityRecords[2]`, but that type is 0x6a0
// bytes and the label covers only 0x8 (later labels overlap it).
u8 gWifiSetupSecurityRecords[8];

u8 gWifiSetupWep128Record[304];

u8 gWifiSetupWep64Record[304];
