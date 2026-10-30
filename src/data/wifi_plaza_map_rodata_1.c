// Converted from asm/wifi_plaza_map_rodata.s (part 1 of 12) by tools/s2c.py.
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
const WiFiPlazaInstrumentBurstUpdateFunc gWiFiPlazaInstrumentBurstUpdateFuncs[6] = {
    WiFiPlazaInstrumentBurst_UpdateBell, WiFiPlazaInstrumentBurst_UpdateDrum,
    WiFiPlazaInstrumentBurst_UpdateCymbal, (WiFiPlazaInstrumentBurstUpdateFunc)0x00380002,
    (WiFiPlazaInstrumentBurstUpdateFunc)0x0038000E, (WiFiPlazaInstrumentBurstUpdateFunc)0x003C0008,
};
// clang-format on

const WiFiPlazaInstrumentBurstEvent gWiFiPlazaInstrumentBursts_Drum02[6] = {
    { 0,      0x00, 0x03 },
    { 0x0010, 0x02, 0x03 },
    { 0x0028, 0x00, 0x03 },
    { 2,      0x2C, 0x00 },
    { 0x000E, 0x2C, 0x00 },
    { 8,      0x30, 0x00 },
};

const WiFiPlazaInstrumentBurstEvent gWiFiPlazaInstrumentBursts_Cymbal03[2] = {
    { 0,      0x00, 0x04 },
    { 0x0014, 0x02, 0x04 },
};

const WiFiPlazaInstrumentBurstEvent gWiFiPlazaInstrumentBursts_Bell02[2] = {
    { 0,      0x00, 0x03 },
    { 0x0018, 0x02, 0x03 },
};

const WiFiPlazaInstrumentBurstEvent gWiFiPlazaInstrumentBursts_Drum01[2] = {
    { 0,      0x00, 0x02 },
    { 0x0018, 0x02, 0x02 },
};

const WiFiPlazaInstrumentBurstEvent gWiFiPlazaInstrumentBursts_Cymbal02[2] = {
    { 0,      0x00, 0x02 },
    { 0x0018, 0x02, 0x02 },
};

const WiFiPlazaInstrumentBurstEvent gWiFiPlazaInstrumentBursts_Bell01[2] = {
    { 0,      0x00, 0x02 },
    { 0x0018, 0x02, 0x02 },
};

const WiFiPlazaInstrumentBurstEvent gWiFiPlazaInstrumentBursts_Cymbal01[2] = {
    { 0,      0x00, 0x02 },
    { 0x0018, 0x01, 0x02 },
};

const u8 gWiFiPlazaInstrumentBalloonHeights[4] __attribute__((aligned(4))) = { 0x30, 0x54, 0x80, 0x00 };
