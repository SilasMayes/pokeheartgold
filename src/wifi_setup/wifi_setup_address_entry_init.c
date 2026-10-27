#include "global.h"

#include "wifi_setup/wifi_setup_access_points.h"
#include "wifi_setup/wifi_setup_address_entry.h"
#include "wifi_setup/wifi_setup_app.h"
#include "wifi_setup/wifi_setup_ui.h"
#include "wifi_setup/wifi_setup_ui_parts.h"

#include <nitro/code32.h>

// Start of the address entry screen: fills the digits with the stored address of the kind given by the screen
// arguments (an unset address is cleared and the cursor starts on the first field, else on the last).

typedef struct WifiSetupAddressMessages {
    u8 messages[5];
} WifiSetupAddressMessages;

// Screen layout shared with the address entry screen: field limit "255", digit positions and the
// message shown per address kind
typedef struct WifiSetupAddressLayout {
    u8 unk_00[8];
    WifiSetupAddressMessages messages;
    u8 unk_0D[11];
} WifiSetupAddressLayout;

extern const WifiSetupAddressLayout gWifiSetupAddressLayout;

void WifiSetupAddressEntry_Init(void) {
    WifiSetupAddressLoadFuncs funcs = gWifiSetupAddressFormatFuncs;
    WifiSetupAddressMessages messages = gWifiSetupAddressLayout.messages;
    int kind;
    WifiSetupAddressEntry *work;
    gWifiSetupAddressEntry = WifiSetupHeap_AllocZeroed(sizeof(WifiSetupAddressEntry), 4);
    WifiSetupApp_GetScreenArgs(&kind, NULL);
    funcs.funcs[kind]((char *)gWifiSetupAddressEntry->digits);
    work = gWifiSetupAddressEntry;
    if (memcmp(work->digits, gWifiSetupAddressEntryUnsetAddress, WIFI_SETUP_ADDRESS_FIELD_LEN) != 0) {
        work->field = WIFI_SETUP_ADDRESS_NUM_FIELDS - 1;
    } else {
        MI_CpuFill8(work->digits, 0, sizeof(work->digits));
        gWifiSetupAddressEntry->field = 0;
    }
    WifiSetupAddressEntry_LoadGraphics();
    WifiSetupBackground_LoadHeader(kind + 11);
    WifiSetupMessage_Show(messages.messages[kind], -1, 0);
    WifiSetupBanner_Show(2);
    gWifiSetupAddressEntry->canvas = WifiSetupText_InitBgCanvas(WIFI_SETUP_SCREEN_MAIN, 0);
    gWifiSetupAddressEntry->cursor = WifiSetupOamTemplate_AllocOam(WIFI_SETUP_SCREEN_MAIN, 0x3f);
    gWifiSetupAddressEntry->cursor->attr2 = (gWifiSetupAddressEntry->cursor->attr2 & ~0xc00) | 0xc00;
    WifiSetupAddressEntry_UpdateCursor();
    WifiSetupAddressEntry_DrawDigits();
    WifiSetupApp_SetStateFunc(WifiSetupAddressEntry_FadeIn);
}

const WifiSetupAddressLayout gWifiSetupAddressLayout = {
    { 0x32, 0x35, 0x35, 0, 0xb, 0, 0x10, 0 },
    { { 0x3F, 0x40, 0x41, 0x42, 0x43 } },
    { 0, 0, 0, 0x29 }
};
const WifiSetupAddressLoadFuncs gWifiSetupAddressFormatFuncs = {
    { WifiSetupConnections_FormatIpAddress, WifiSetupConnections_FormatSubnetMask, WifiSetupConnections_FormatGateway, WifiSetupConnections_FormatPrimaryDns, WifiSetupConnections_FormatSecondaryDns }
};
