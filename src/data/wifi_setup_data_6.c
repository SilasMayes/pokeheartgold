// Converted from asm/wifi_setup_data.s (part 6 of 20) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

// The C declarations of these do not match the data (see the notes at each
// definition): keep them out of the way of the definitions below.
#define gWifiSetupCipherSeed gWifiSetupCipherSeed_header_decl
#define gWifiSetupCipherKey  gWifiSetupCipherKey_header_decl
#define gWifiSetupRuntime    gWifiSetupRuntime_header_decl

#include "global.h"

#include "wifi_setup/wifi_setup.h"
#include "wifi_setup/wifi_setup_internal.h"
#include "wifi_setup/wifi_setup_wcm.h"

#pragma force_active on

#undef gWifiSetupCipherSeed
#undef gWifiSetupCipherKey
#undef gWifiSetupRuntime

u8 sStr_WARP[4] = "WARP";

#pragma explicit_zero_data on
// zero bytes after sStr_WARP in the asm
static u8 sStr_WARP_pad[4] = { 0 };
#pragma explicit_zero_data reset

// C declares this as `u8 gWifiSetupCipherSeed[]`, but MWCC gives a char array a section of its own,
// which the linker starts 4-aligned; to stay at offset 0xd68 next to its neighbours it is written as
// the only row of a 2-D array, which shares their section.
u8 gWifiSetupCipherSeed[1][2];

// C declares this as `WifiSetupRuntime gWifiSetupRuntime`, but that type is 0x10 bytes and the label
// covers only 0xc (later labels overlap it).
u8 gWifiSetupRuntime[12];

// C declares this as `u8 gWifiSetupCipherKey[]`, but MWCC gives a char array a section of its own,
// which the linker starts 4-aligned; to stay at offset 0xd6a next to its neighbours it is written as
// the only row of a 2-D array, which shares their section.
u8 gWifiSetupCipherKey[1][126];
