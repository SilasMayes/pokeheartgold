// Converted from asm/wifi_setup_data.s (part 1 of 20) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

// The C declarations of these do not match the data (see the notes at each
// definition): keep them out of the way of the definitions below.
#define gWifiSetupSocket gWifiSetupSocket_header_decl
#define gWifiSetupState  gWifiSetupState_header_decl

#include "global.h"

#include "wifi_setup/wifi_setup.h"
#include "wifi_setup/wifi_setup_internal.h"
#include "wifi_setup/wifi_setup_wcm.h"

#pragma force_active on

#undef gWifiSetupSocket
#undef gWifiSetupState

struct {
    u8 unk0[4];
    void (*unk4)(void);
    void (*unk8)(void);
    u8 unkC[32];
} sWifiSetupSocConfig[2] = {
    {
     { 0x00, 0x00, 0x00, 0x01 },
     (void (*)(void))WifiSetup_SocketAlloc,
     (void (*)(void))WifiSetup_SocketFree,
     {
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
            0x10,
            0x00,
            0x00,
            0x00,
            0x10,
            0x00,
            0x00,
        },
     },
    { { 0 }, NULL, NULL, { 0 } },
};

// C declares this as `WifiSetupSocketState gWifiSetupSocket`, but that type is 0x3c bytes and the
// label covers only 0x8 (later labels overlap it).
u8 gWifiSetupSocket[8] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };

u8 sWifiSetupSecurityRecordTypes[4] __attribute__((aligned(4))) = { 0x09, 0x08, 0x00, 0x00 };

WifiSetupAossApList *ov13_0224CF9C;

// C declares this as `WifiSetupState gWifiSetupState`, but that type is 0x3c bytes and the label
// covers only 0x4 (later labels overlap it).
u8 gWifiSetupState[4] __attribute__((aligned(4)));

// zero bytes after ov13_0224CF9C in the asm
static u8 ov13_0224CF9C_pad[24];
