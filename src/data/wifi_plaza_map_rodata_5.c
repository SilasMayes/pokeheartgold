// Converted from asm/wifi_plaza_map_rodata.s (part 5 of 12) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

#include "global.h"

#include "wifi_plaza/wifi_plaza_event.h"
#include "wifi_plaza/wifi_plaza_instrument.h"
#include "wifi_plaza/wifi_plaza_light.h"

#pragma force_active on

const WiFiPlazaInstrumentModelDesc gWiFiPlazaInstrumentModelDescs[9] = {
    { 0x00, 0x00, { 0x00, 0x11 } },
    { 0x00, 0x01, { 0x00, 0x11 } },
    { 0x00, 0x02, { 0x00, 0x11 } },
    { 0x01, 0x03, { 0x01, 0x02 } },
    { 0x01, 0x04, { 0x01, 0x02 } },
    { 0x01, 0x05, { 0x01, 0x02 } },
    { 0x01, 0x06, { 0x03, 0x11 } },
    { 0x01, 0x07, { 0x03, 0x11 } },
    { 0x01, 0x08, { 0x03, 0x11 } },
};
