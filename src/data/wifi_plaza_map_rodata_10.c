// Converted from asm/wifi_plaza_map_rodata.s (part 10 of 12) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

// The C declarations of these do not match the data (see the notes at each
// definition): keep them out of the way of the definitions below.
#define gWiFiPlazaEventPhase4Steps     gWiFiPlazaEventPhase4Steps_header_decl
#define gWiFiPlazaEventPhase4HideSteps gWiFiPlazaEventPhase4HideSteps_header_decl

#include "global.h"

#include "wifi_plaza/wifi_plaza_event.h"
#include "wifi_plaza/wifi_plaza_instrument.h"
#include "wifi_plaza/wifi_plaza_light.h"

#pragma force_active on

#undef gWiFiPlazaEventPhase4Steps
#undef gWiFiPlazaEventPhase4HideSteps

// clang-format off
void (*const gWiFiPlazaEventEffectPhaseUpdates[6])(WiFiPlazaEventEffect *effect, int arg) = {
    (void (*)(WiFiPlazaEventEffect *, int))WiFiPlazaEventEffect_UpdateNone,
    (void (*)(WiFiPlazaEventEffect *, int))WiFiPlazaEventEffect_UpdateNone,
    (void (*)(WiFiPlazaEventEffect *, int))WiFiPlazaEventEffect_UpdatePhase2,
    (void (*)(WiFiPlazaEventEffect *, int))WiFiPlazaEventEffect_UpdatePhase3,
    (void (*)(WiFiPlazaEventEffect *, int))WiFiPlazaEventEffect_UpdatePhase4,
    (void (*)(WiFiPlazaEventEffect *, int))WiFiPlazaEventEffect_UpdatePhase5,
};
// clang-format on

// C declares this as `const u8 gWiFiPlazaEventPhase4HideSteps[]`, but MWCC gives a char array a
// section of its own, which the linker starts 4-aligned; to stay at offset 0x3ed next to its
// neighbours it is written as the only row of a 2-D array, which shares their section.
// clang-format off
const u8 gWiFiPlazaEventPhase4HideSteps[1][15] = {
{
    0x05, 0x01, 0x06, 0x02, 0x00, 0x03, 0x01, 0x04, 0x02, 0x05, 0x03, 0x06, 0x04, 0x00, 0x00,
}
};
// clang-format on

#ifdef SDK_PORT
// On the DS this label is the first column of pairs read at [step * 2], the second
// gWiFiPlazaEventPhase4HideSteps; the port has a complete copy.
// clang-format off
const u8 gWiFiPlazaEventPhase4Steps[16] = { 0, 5, 1, 6, 2, 0, 3, 1, 4, 2, 5, 3, 6, 4, 0, 0 };
// clang-format on
#else
// C declares this as `const u8 gWiFiPlazaEventPhase4Steps[]`, but MWCC gives a char array a section of
// its own, which the linker starts 4-aligned; to stay at offset 0x3ec next to its neighbours it is
// written as the only row of a 2-D array, which shares their section.
const u8 gWiFiPlazaEventPhase4Steps[1][1] = { { 0x00 } };
#endif
