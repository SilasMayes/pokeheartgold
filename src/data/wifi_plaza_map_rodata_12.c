// Converted from asm/wifi_plaza_map_rodata.s (part 12 of 12) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

#include "global.h"

#include "wifi_plaza/wifi_plaza_event.h"
#include "wifi_plaza/wifi_plaza_instrument.h"
#include "wifi_plaza/wifi_plaza_light.h"

#pragma force_active on

const u16 gWiFiPlazaMoverSounds[5][6] = {
    { 0x00FF, 6,      0xFFFE, 0x05CB, 0x05CE, 0x05C5 },
    { 0x0189, 0x0082, 0x05CB, 0x05CD, 0x05CF, 0x05CB },
    { 0x0019, 0x01CE, 0xFFFE, 0x05CB, 0xFFFE, 0x05D0 },
    { 1,      0x01C7, 0x05D1, 0x05CC, 0x05C5, 0x05CB },
    { 0x0097, 0x0097, 0xFFFE, 0x05CB, 0x05D2, 0x05CB },
};

// clang-format off
BOOL (*const gWiFiPlazaEventWobbleSteps[2])(WiFiPlazaEventWobble *wobble, WiFiPlazaModels *models, int index) = {
    WiFiPlazaEventWobble_Step, WiFiPlazaEventWobble_Step,
};
// clang-format on

// clang-format off
BOOL (*const gWiFiPlazaEventWobbleInits[2])(WiFiPlazaEventWobble *wobble, WiFiPlazaModels *models, int index) = {
    (BOOL (*)(WiFiPlazaEventWobble *, WiFiPlazaModels *, int))WiFiPlazaEventWobble_InitSmall,
    (BOOL (*)(WiFiPlazaEventWobble *, WiFiPlazaModels *, int))WiFiPlazaEventWobble_InitLarge,
};
// clang-format on

const u8 gWiFiPlazaMoverMarkerTags[4] = "?>=";
