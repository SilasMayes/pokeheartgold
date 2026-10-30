// Converted from asm/wifi_setup_data.s (part 12 of 20) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

// The C declarations of these do not match the data (see the notes at each
// definition): keep them out of the way of the definitions below.
#define gWifiSetupThread gWifiSetupThread_header_decl

#include "global.h"

#include "wifi_setup/wifi_setup.h"
#include "wifi_setup/wifi_setup_internal.h"
#include "wifi_setup/wifi_setup_wcm.h"

#pragma force_active on

#undef gWifiSetupThread

void (*gWifiSetupLinkEventCallback)(u32 event, int arg);

u32 gWifiSetupLinkEventQueue[4];

OSMutex gWifiSetupLinkMutex;

// C declares this as `OSThread gWifiSetupThread`, but it has 64-bit members, whose layout MWCC and GCC
// may not agree on.
u8 gWifiSetupThread[192];
