#ifndef POKEHEARTGOLD_WIFI_SETUP_SETTINGS_H
#define POKEHEARTGOLD_WIFI_SETUP_SETTINGS_H

#include "global.h"

#include "wifi_setup/wifi_setup_ui.h"

// Connection settings screen of the access-point setup: a scrolling list of 12 items with a scroll bar on the top
// screen. Items are 29 pixels apart; five are visible at a time.

#define WIFI_SETUP_SETTINGS_NUM_ITEMS  12
#define WIFI_SETUP_SETTINGS_ROW_HEIGHT 29
#define WIFI_SETUP_SETTINGS_MAX_SCROLL 145 // 5 rows
#define WIFI_SETUP_SETTINGS_NUM_ROWS   5   // rows drawn at a time

// item codes returned by WifiSetupSettings_GetTouchedItem besides the list items
#define WIFI_SETUP_SETTINGS_ITEM_AUTO_ADDRESS_ON  2
#define WIFI_SETUP_SETTINGS_ITEM_AUTO_ADDRESS_OFF 3
#define WIFI_SETUP_SETTINGS_ITEM_AUTO_DNS_ON      7
#define WIFI_SETUP_SETTINGS_ITEM_AUTO_DNS_OFF     8
#define WIFI_SETUP_SETTINGS_ITEM_BACK             13
#define WIFI_SETUP_SETTINGS_ITEM_NONE             14

// items of the two switch rows, in order: address on/off, DNS on/off
typedef struct WifiSetupSettingsSwitchItems {
    u8 items[4];
} WifiSetupSettingsSwitchItems;

// rect index in gWifiSetupSettingsCursorPairRects per cursor item
typedef struct WifiSetupSettingsCursorRects {
    u8 rects[14];
} WifiSetupSettingsCursorRects;

typedef struct WifiSetupSettingsWork {
    void *task;         // queue 0
    u8 buttonStates[4]; // press timers of the switch buttons
    u16 *screenData;    // top screen BG tiles of all items
    void *paletteData;
    void *charData;
    WifiSetupCanvas *canvas;  // text of the visible rows
    GXOamAttr *rows[5];       // one object per visible row
    GXOamAttr *addressSwitch; // buttons of the "obtain address automatically" item
    GXOamAttr *dnsSwitch;     // buttons of the "obtain DNS automatically" item
    GXOamAttr *ssidIcon;      // the setup method icon next to the first item, NULL for none
    void *scrollTask;         // row scroll in progress
    void *task2;              // queue 1
    u8 selection;             // item chosen to leave the screen with
    u8 scrollBarTimer;
    u8 lastButton; // bottom button (12/13) the cursor returns to
    u8 autoDns;    // DNS switch kept while the address is set by hand
    u8 objectsDirty;
    u8 scrollBarHeld;
    u8 scrollBarAtEnd;
    u8 keyAtEnd;
} WifiSetupSettingsWork;

typedef struct WifiSetupSettings {
    u8 cursorItem;
    u8 fromMenu;
    u8 cursorRow; // visible row (0-3) of the cursor
    u8 unk_03;
    u16 scroll; // 0 - WIFI_SETUP_SETTINGS_MAX_SCROLL
    u16 unk_06;
    WifiSetupSettingsWork *work;
} WifiSetupSettings;

extern WifiSetupSettings gWifiSetupSettings;
extern const WifiSetupSettingsSwitchItems gWifiSetupSettingsSwitchItems;

extern const WifiSetupPath21 gWifiSetupSettingsYbBgStep2NclPath;
extern const WifiSetupPath22 gWifiSetupSettingsYbBgStep21NclPath;
extern const WifiSetupPath23 gWifiSetupSettingsJb3ListBackNscPath;
extern u8 gWifiSetupSettingsButtonTemplates[][3]; // OAM template per button type and option
extern u16 gWifiSetupSettingsRowTileOffsets[];    // top screen tile offset per first visible item
extern WifiSetupRect gWifiSetupSettingsTouchRects[];
extern s8 gWifiSetupSettingsDigitPositions[];
extern u8 gWifiSetupSettingsRowItems[]; // item per list row
extern u8 gWifiSetupSettingsItemRows[]; // list row per item
extern char gWifiSetupSettingsYbObjKbNclPath[];
extern char gWifiSetupSettingsJbBgStep2NcgPath[];
extern char gWifiSetupSettingsJbBgStep21NcgPath[];
extern char gWifiSetupSettingsJb3ListNscPath[];
extern char gWifiSetupSettingsYbObjMainNclPath[];
extern u16 gWifiSetupSettingsAddressFormat[];
extern u32 ov13_0224F554[];
extern u8 gWifiSetupSettingsButtonPaletteRows[]; // palette row per button item 11-13
extern u8 gWifiSetupSettingsScrollOffsets[];     // BG 2 offset per first visible item
extern WifiSetupRect gWifiSetupSettingsCursorPairRects[];
extern WifiSetupSettingsCursorRects gWifiSetupSettingsCursorRects;

void WifiSetupSettings_Init(void);
void WifiSetupSettings_Main(void);
void WifiSetupSettings_DrawRows(void);
void WifiSetupSettings_UpdateObjects(void);
int WifiSetupSettings_GetTouchedItem(void);

#endif // POKEHEARTGOLD_WIFI_SETUP_SETTINGS_H
