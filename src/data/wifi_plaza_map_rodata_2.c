// Converted from asm/wifi_plaza_map_rodata.s (part 2 of 12) by tools/s2c.py.
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
const WiFiPlazaInstrumentUpdateFunc gWiFiPlazaInstrumentUpdateFuncs[27] = {
    WiFiPlazaInstrument_UpdateBellDrum, WiFiPlazaInstrument_UpdateBellDrum,
    WiFiPlazaInstrument_UpdateBellDrum, WiFiPlazaInstrument_UpdateBellDrum,
    WiFiPlazaInstrument_UpdateBellDrum, WiFiPlazaInstrument_UpdateBellDrum, WiFiPlazaInstrument_UpdateCymbal,
    WiFiPlazaInstrument_UpdateCymbal, WiFiPlazaInstrument_UpdateCymbal, WiFiPlazaInstrument_UpdateRipple,
    WiFiPlazaInstrument_UpdateRipple, WiFiPlazaInstrument_UpdateRipple, WiFiPlazaInstrument_UpdateSignal01,
    WiFiPlazaInstrument_UpdateSignal02, WiFiPlazaInstrument_UpdateSignal03, WiFiPlazaInstrument_UpdateWhirl,
    WiFiPlazaInstrument_UpdateWhirl, WiFiPlazaInstrument_UpdateWhirl, WiFiPlazaInstrument_UpdatePop,
    WiFiPlazaInstrument_UpdatePop, WiFiPlazaInstrument_UpdatePop, WiFiPlazaInstrument_UpdateSparkle,
    WiFiPlazaInstrument_UpdateSparkle, WiFiPlazaInstrument_UpdateSparkle, WiFiPlazaInstrument_UpdateBalloon,
    WiFiPlazaInstrument_UpdateBalloon, WiFiPlazaInstrument_UpdateBalloon,
};
// clang-format on

// clang-format off
const WiFiPlazaInstrumentInitFunc gWiFiPlazaInstrumentInitFuncs[27] = {
    WiFiPlazaInstrument_InitBell01, WiFiPlazaInstrument_InitBell02, WiFiPlazaInstrument_InitBell03,
    WiFiPlazaInstrument_InitDrum01, WiFiPlazaInstrument_InitDrum02, WiFiPlazaInstrument_InitDrum03,
    WiFiPlazaInstrument_InitCymbal01, WiFiPlazaInstrument_InitCymbal02, WiFiPlazaInstrument_InitCymbal03,
    WiFiPlazaInstrument_InitRipple01, WiFiPlazaInstrument_InitRipple02, WiFiPlazaInstrument_InitRipple03,
    WiFiPlazaInstrument_InitSignal, WiFiPlazaInstrument_InitSignal, WiFiPlazaInstrument_InitSignal,
    WiFiPlazaInstrument_InitWhirl01, WiFiPlazaInstrument_InitWhirl02, WiFiPlazaInstrument_InitWhirl03,
    WiFiPlazaInstrument_InitPop01, WiFiPlazaInstrument_InitPop02, WiFiPlazaInstrument_InitPop03,
    WiFiPlazaInstrument_InitSparkle01, WiFiPlazaInstrument_InitSparkle02, WiFiPlazaInstrument_InitSparkle03,
    WiFiPlazaInstrument_InitBalloon01, WiFiPlazaInstrument_InitBalloon02, WiFiPlazaInstrument_InitBalloon03,
};
// clang-format on

const VecFx32 gWiFiPlazaInstrumentSparkleStarts[4] = {
    { 32768, 65536, 8192   },
    { 73728, 65536, -32768 },
    { 32768, 65536, -73728 },
    { -8192, 65536, -32768 },
};

const VecFx32 gWiFiPlazaInstrumentSparkleFalls[4] = {
    { 0,      -32768, 32768  },
    { 32768,  -32768, 0      },
    { 0,      -32768, -32768 },
    { -32768, -32768, 0      },
};

const WiFiPlazaInstrumentBurstEvent gWiFiPlazaInstrumentBursts_Bell03[3] = {
    { 0,      0x00, 0x04 },
    { 0x0010, 0x02, 0x04 },
    { 0x0020, 0x00, 0x04 },
};

// clang-format off
const WiFiPlazaInstrumentBurstStartFunc gWiFiPlazaInstrumentBurstStartFuncs[3] = {
    WiFiPlazaInstrumentBurst_StartBell, WiFiPlazaInstrumentBurst_StartDrum,
    WiFiPlazaInstrumentBurst_StartCymbal,
};
// clang-format on

const WiFiPlazaInstrumentBurstEvent gWiFiPlazaInstrumentBursts_Drum03[3] = {
    { 0,      0x00, 0x04 },
    { 0x0010, 0x02, 0x04 },
    { 0x0023, 0x00, 0x04 },
};
