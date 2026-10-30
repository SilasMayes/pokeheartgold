// Converted from asm/wifi_plaza_map_rodata.s (part 8 of 12) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

#include "global.h"

#include "wifi_plaza/wifi_plaza_event.h"
#include "wifi_plaza/wifi_plaza_instrument.h"
#include "wifi_plaza/wifi_plaza_light.h"

#pragma force_active on

const u16 gWiFiPlazaLightColorSets[6][5] = {
    { 0x66F7, 0x4210, 0x39CE, 0x5294, 0x4210 },
    { 0x414A, 0x4210, 0x39CE, 0x5294, 0x4210 },
    { 0x3108, 0x4210, 0x39CE, 0x5294, 0x4210 },
    { 0x20A5, 0x4210, 0x39AD, 0x5294, 0x4210 },
    { 0x1C63, 0x4210, 0x314A, 0x5294, 0x41CE },
    { 0x1800, 0x4210, 0x2908, 0x5294, 0x418C },
};

const u16 gWiFiPlazaLight1Colors[4] = { 0x39CE, 0x5294, 0x7FFF, 0x2108 };
