// Converted from asm/wifi_plaza_map_rodata.s (part 11 of 12) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

#include "global.h"

#include "wifi_plaza/wifi_plaza_event.h"
#include "wifi_plaza/wifi_plaza_instrument.h"
#include "wifi_plaza/wifi_plaza_light.h"

#pragma force_active on

const u32 gWiFiPlazaEventPhase3PropGroups[4][2] = {
    { 0, 2 },
    { 1, 3 },
    { 2, 0 },
    { 3, 1 }
};

// clang-format off
void (*const gWiFiPlazaEventEffectPhaseStarts[6])(WiFiPlazaEventEffect *effect, u32 arg) = {
    (void (*)(WiFiPlazaEventEffect *, u32))WiFiPlazaEventEffect_StartHideProps,
    (void (*)(WiFiPlazaEventEffect *, u32))WiFiPlazaEventEffect_StartHideProps,
    (void (*)(WiFiPlazaEventEffect *, u32))WiFiPlazaEventEffect_StartPhase2,
    (void (*)(WiFiPlazaEventEffect *, u32))WiFiPlazaEventEffect_StartPhase3,
    (void (*)(WiFiPlazaEventEffect *, u32))WiFiPlazaEventEffect_StartPhase4,
    (void (*)(WiFiPlazaEventEffect *, u32))WiFiPlazaEventEffect_StartPhase5,
};
// clang-format on

const u32 gWiFiPlazaEventPhase5AnimSpeeds[5] = { 0x00001000, 0x0000002D, 0x00001000, 0x00000050, 0x00000800 };

// clang-format off
const u8 gWiFiPlazaEventPhase3PropIds[20] = {
    0x06, 0x0D, 0x05, 0x0B, 0x07, 0x0E, 0x08, 0x0C, 0x01, 0x00, 0x02, 0x0A, 0x10, 0x09, 0x04, 0x03, 0x0F,
    0x00, 0x00, 0x00,
};
// clang-format on

const u32 gWiFiPlazaEventPhase5Thresholds[1] = { 0x0000000A };
