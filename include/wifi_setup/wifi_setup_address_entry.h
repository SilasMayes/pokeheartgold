#ifndef POKEHEARTGOLD_WIFI_SETUP_ADDRESS_ENTRY_H
#define POKEHEARTGOLD_WIFI_SETUP_ADDRESS_ENTRY_H

#include "global.h"

#include "wifi_setup/wifi_setup_ui.h"

// Address entry screen of the access-point setup (an IPv4 address or subnet mask typed on the numeric keypad), and
// the error screen that shows a connection error code with its message.

#define WIFI_SETUP_ADDRESS_NUM_FIELDS 4
#define WIFI_SETUP_ADDRESS_FIELD_LEN  3

// result of the address entry
#define WIFI_SETUP_ADDRESS_CANCELLED 0
#define WIFI_SETUP_ADDRESS_VALID     1
#define WIFI_SETUP_ADDRESS_INVALID   2

typedef struct WifiSetupAddressEntry {
    WifiSetupCanvas *canvas; // text of the digits
    GXOamAttr *cursor;       // marks the field being typed
    u8 digits[12];           // four fields of three characters ('0'-'9', ' ' or 0)
    u8 field;                // field being typed (0-3)
    u8 result;               // WIFI_SETUP_ADDRESS_*; answer of the confirmation dialog
} WifiSetupAddressEntry;

// formats the stored address of one kind (IP address, subnet mask, gateway, primary/secondary DNS)
typedef void (*WifiSetupAddressLoadFunc)(char *buf);

typedef struct WifiSetupAddressLoadFuncs {
    WifiSetupAddressLoadFunc funcs[5];
} WifiSetupAddressLoadFuncs;

// stores the typed address of one kind
typedef void (*WifiSetupAddressFunc)(u8 *digits);

// indexed by the first value of WifiSetupApp_GetScreenArgs
typedef struct WifiSetupAddressFuncs {
    WifiSetupAddressFunc funcs[5];
} WifiSetupAddressFuncs;

extern WifiSetupAddressEntry *gWifiSetupAddressEntry;
extern int gWifiSetupErrorCode;

extern const u8 gWifiSetupAddressEntryUnsetAddress[]; // stored address of an unset entry
extern const WifiSetupAddressLoadFuncs gWifiSetupAddressFormatFuncs;
extern WifiSetupAddressFuncs gWifiSetupAddressEntryFuncs;
extern const u8 gWifiSetupAddressEntryDigitX[]; // x of every digit
extern char gWifiSetupAddressEntryYbObjKbNclPath[];
extern char gWifiSetupAddressEntryJbBgStep3NcgPath[];
extern char gWifiSetupAddressEntryYbBgStep3NclPath[];
extern char gWifiSetupAddressEntryXb4EditAddrNscPath[];
extern char gWifiSetupAddressEntryYbObjMainNclPath[];

extern const u8 gWifiSetupErrorScreenFonts[]; // font per language
extern const u16 gWifiSetupErrorCodeX[];      // x, y of the code per language
extern const u16 gWifiSetupErrorCodeY[];
extern char gWifiSetupErrorScreenJb4ErrorNscPath[];
extern const u16 gWifiSetupErrorCodeFormat[];

void WifiSetupAddressEntry_Init(void);
void WifiSetupAddressEntry_LoadGraphics(void);
void WifiSetupAddressEntry_FadeIn(void);
void WifiSetupAddressEntry_OpenKeypad(void);
void WifiSetupAddressEntry_DrawDigits(void);
void WifiSetupAddressEntry_UpdateCursor(void);

// Invalid address message
void WifiSetupAddressEntry_WaitInvalidMessage(void);
void WifiSetupErrorScreen_Init(void);
void WifiSetupErrorScreen_SetCode(int code);

#endif // POKEHEARTGOLD_WIFI_SETUP_ADDRESS_ENTRY_H
