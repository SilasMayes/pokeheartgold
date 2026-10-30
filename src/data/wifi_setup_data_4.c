// Converted from asm/wifi_setup_data.s (part 4 of 20) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

#include "global.h"

#include "wifi_setup/wifi_setup.h"
#include "wifi_setup/wifi_setup_internal.h"
#include "wifi_setup/wifi_setup_wcm.h"

#pragma force_active on

extern char sStr_NINTENDO_DS_2[12];
extern u8 gWifiSetupRecordBuffer[2048];

struct {
    u8 unk0[4];
    void (*unk4)(void);
    void (*unk8)(void);
    u8 unkC[60];
    const void *unk48;
    u8 unk4C[12];
} sWifiSetupLinkSocConfig = {
    { 0x00, 0x00, 0x00, 0x01 },
    (void (*)(void))WifiSetupLink_Alloc,
    (void (*)(void))WifiSetupLink_Free,
    {
     0x00,
     0x00,
     0x00,
     0x00,
     0xC0,
     0xA8,
     0x00,
     0xB0,
     0xFF,
     0xFF,
     0xFF,
     0x00,
     0xC0,
     0xA8,
     0x00,
     0xC8,
     0xC0,
     0xA8,
     0x00,
     0x20,
     0x00,
     0x00,
     0x00,
     0x00,
     0x00,
     0x10,
     0x00,
     0x00,
     0x00,
     0x10,
     0x00,
     0x00,
     0x00,
     0x00,
     0x00,
     0x00,
     0x00,
     0x00,
     0x00,
     0x00,
     0x00,
     0x00,
     0x00,
     0x00,
     0x00,
     0x00,
     0x00,
     0x00,
     0x00,
     0x00,
     0x00,
     0x00,
     0x00,
     0x00,
     0x00,
     0x00,
     0x00,
     0x00,
     0x00,
     0x00,
     },
    sStr_NINTENDO_DS_2,
    { 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
};

WifiSetupConfig gWifiSetupConfig = { &gWifiSetupRecordBuffer[8], 1, 0x00000800, -1, 0x00000040 };

u8 ov13_0224D8C0[112];

u8 ov13_0224D930[968];
