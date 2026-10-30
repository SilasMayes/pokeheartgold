// Converted from asm/wifi_plaza_map_rodata.s (part 6 of 12) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

#include "global.h"

#include "wifi_plaza/wifi_plaza_event.h"
#include "wifi_plaza/wifi_plaza_instrument.h"
#include "wifi_plaza/wifi_plaza_light.h"

#pragma force_active on

const WiFiPlazaInstrumentModelDesc gWiFiPlazaInstrumentPopModel0[4] = {
    { 0x06, 0x0C, { 0x07, 0x11 } },
    { 0x07, 0x0D, { 0x08, 0x11 } },
    { 0x08, 0x0E, { 0x09, 0x11 } },
    { 0x09, 0x0F, { 0x0A, 0x11 } },
};

const WiFiPlazaInstrumentModelDesc gWiFiPlazaInstrumentPopModel2[1] = {
    { 0x03, 0x09, { 0x04, 0x11 } }
};

const WiFiPlazaInstrumentModelDesc gWiFiPlazaInstrumentPopModel3[1] = {
    { 0x04, 0x0A, { 0x05, 0x11 } }
};

const WiFiPlazaInstrumentModelDesc gWiFiPlazaInstrumentPopModel1[1] = {
    { 0x05, 0x0B, { 0x06, 0x11 } }
};
