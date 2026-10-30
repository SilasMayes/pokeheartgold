// Converted from asm/wifi_plaza_map_rodata.s (part 3 of 12) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

#include "global.h"

#include "wifi_plaza/wifi_plaza_event.h"
#include "wifi_plaza/wifi_plaza_instrument.h"
#include "wifi_plaza/wifi_plaza_light.h"

#pragma force_active on

// clang-format off
const u32 gWiFiPlazaInstrumentStartSEs[26] = {
    0x0000059C, 0x0000059D, 0x0000059E, 0x000005A2, 0x000005A3, 0x000005A4, 0x0000059F, 0x000005A0,
    0x000005A1, 0x000005AA, 0x000005AB, 0x000005AC, 0x000005B0, 0x000005B1, 0x000005B2, 0x000005A5,
    0x000005A6, 0x000005A7, 0x000005B6, 0x000005B7, 0x000005B8, 0x000005B9, 0x000005BA, 0x000005BB,
    0x000005A9, 0x000005A9,
};
// clang-format on
