// Converted from asm/wifi_plaza_map_rodata.s (part 4 of 12) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

// The C declarations of these do not match the data (see the notes at each
// definition): keep them out of the way of the definitions below.
#define gWiFiPlazaInstrumentSignalSteps gWiFiPlazaInstrumentSignalSteps_header_decl

#include "global.h"

#include "wifi_plaza/wifi_plaza_event.h"
#include "wifi_plaza/wifi_plaza_instrument.h"
#include "wifi_plaza/wifi_plaza_light.h"

#pragma force_active on

#undef gWiFiPlazaInstrumentSignalSteps

const WiFiPlazaInstrumentStep gWiFiPlazaInstrumentSignalNextSteps[3][12] = {
    {
     { 0, 1 },
     { 0, 0 },
     { 0, 2 },
     { 0, 0 },
     { 0, 1 },
     { 0, 0 },
     { 0, 2 },
     { 0, 0 },
     { 0, 1 },
     { 0, 0 },
     { 0, 2 },
     { 0, 0 },
     },
    {
     { 1, 1 },
     { 1, 0 },
     { 0, 2 },
     { 0, 0 },
     { 1, 1 },
     { 1, 0 },
     { 0, 2 },
     { 0, 0 },
     { 1, 1 },
     { 1, 0 },
     { 0, 2 },
     { 0, 0 },
     },
    {
     { 0, 1 },
     { 0, 0 },
     { 1, 2 },
     { 1, 0 },
     { 2, 1 },
     { 2, 0 },
     { 0, 2 },
     { 1, 1 },
     { 2, 2 },
     { 0, 1 },
     { 1, 2 },
     { 2, 1 },
     },
};

#ifdef SDK_PORT
// On the DS this label is one step before gWiFiPlazaInstrumentSignalNextSteps (the code reads
// [kind][step] for the previous step); the port has a complete copy.
// clang-format off
const WiFiPlazaInstrumentStep gWiFiPlazaInstrumentSignalSteps[3][12] = {
    {
        { 0x5A9, 0 },
        { 0, 1 },
        { 0, 0 },
        { 0, 2 },
        { 0, 0 },
        { 0, 1 },
        { 0, 0 },
        { 0, 2 },
        { 0, 0 },
        { 0, 1 },
        { 0, 0 },
        { 0, 2 },
    },
    {
        { 0, 0 },
        { 1, 1 },
        { 1, 0 },
        { 0, 2 },
        { 0, 0 },
        { 1, 1 },
        { 1, 0 },
        { 0, 2 },
        { 0, 0 },
        { 1, 1 },
        { 1, 0 },
        { 0, 2 },
    },
    {
        { 0, 0 },
        { 0, 1 },
        { 0, 0 },
        { 1, 2 },
        { 1, 0 },
        { 2, 1 },
        { 2, 0 },
        { 0, 2 },
        { 1, 1 },
        { 2, 2 },
        { 0, 1 },
        { 1, 2 },
    },
};
// clang-format on
#else
// C declares this as `const WiFiPlazaInstrumentStep gWiFiPlazaInstrumentSignalSteps[][12]`, but one
// element of that type is larger than the data under this label.
const u8 gWiFiPlazaInstrumentSignalSteps[4] = { 0xA9, 0x05, 0x00, 0x00 };
#endif
