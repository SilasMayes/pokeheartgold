#ifndef POKEHEARTGOLD_WIFI_SETUP_CONNECTION_SCREENS_H
#define POKEHEARTGOLD_WIFI_SETUP_CONNECTION_SCREENS_H

#include "global.h"

#include "wifi_setup/wifi_setup_ui.h"

// Connection screens of the access-point setup. Every screen is a chain of state functions set with
// WifiSetupApp_SetStateFunc, from Init to End, which picks the next screen.

// gWifiSetupApScanScreen.result
#define WIFI_SETUP_AP_SCAN_RUNNING  0
#define WIFI_SETUP_AP_SCAN_FOUND    1
#define WIFI_SETUP_AP_SCAN_NONE     2
#define WIFI_SETUP_AP_SCAN_ONLY_WPA 3 // every access point found uses WPA

// WifiSetupConnectionListWork.exit
#define WIFI_SETUP_CONNECTION_LIST_STAY 0
#define WIFI_SETUP_CONNECTION_LIST_NEXT 1 // A on a slot
#define WIFI_SETUP_CONNECTION_LIST_BACK 2

// gWifiSetupConnectionList.selected: 0-2 the connection slots, 3 the Wi-Fi USB connector,
// 4-6 the erase buttons of slots 0-2
#define WIFI_SETUP_CONNECTION_LIST_USB         3
#define WIFI_SETUP_CONNECTION_LIST_FIRST_ERASE 4

// gWifiSetupMethodMenu.selected
#define WIFI_SETUP_METHOD_MENU_AP_SCAN 0
#define WIFI_SETUP_METHOD_MENU_CLIENT  1 // WifiSetupAoss_Init
#define WIFI_SETUP_METHOD_MENU_AUTO    2 // WifiSetupAutoSearch_Init
#define WIFI_SETUP_METHOD_MENU_MANUAL  3

// Second screen argument of the connection test screens (WifiSetupTestPrompt_Init, WifiSetupConnectionTest_Init)
#define WIFI_SETUP_TEST_FROM_SETTINGS 0 // the settings screen of a slot
#define WIFI_SETUP_TEST_NEW_SETTINGS  1 // settings just found or typed, saved to the slot first
#define WIFI_SETUP_TEST_USB_CONNECTOR 2

typedef struct WifiSetupApScanScreen {
    u8 result; // WIFI_SETUP_AP_SCAN_*
    u16 timer;
} WifiSetupApScanScreen;

typedef struct WifiSetupConnectionListWork {
    u8 *graphics;                       // palette rows of the slots
    WifiSetupOamBlock *slotIcons[3];    // one per setup method, or the empty slot icon
    WifiSetupOamBlock *eraseButtons[3]; // NULL for an empty slot
    u8 column;                          // slot the cursor left from, for the erase row
    u8 exit;                            // WIFI_SETUP_CONNECTION_LIST_*
} WifiSetupConnectionListWork;

typedef struct WifiSetupConnectionList {
    u8 selected;
    WifiSetupConnectionListWork *work;
} WifiSetupConnectionList;

typedef struct WifiSetupMethodMenu {
    s8 lastOption; // option the cursor returns to (move table value -2)
    s8 selected;   // WIFI_SETUP_METHOD_MENU_*
    u8 confirmed;
    u8 *graphics; // palette rows of the options
} WifiSetupMethodMenu;

typedef struct WifiSetupPaletteRows {
    u8 rows[4];
} WifiSetupPaletteRows;

// dialog message per connection test mode
typedef struct WifiSetupTestPromptMessages {
    u32 messages[3];
} WifiSetupTestPromptMessages;

// parameters of the connection test (DWC_AC_Create)
typedef struct WifiSetupConnectionTestParams {
    void *(*alloc)(int heap, int size);
    void (*free)(int heap, void *ptr, int size);
    u8 dmaNo;
    u8 powerMode;
    u8 slot; // 1-3, 4 for the Wi-Fi USB connector
    u8 skipNetCheck;
} WifiSetupConnectionTestParams;

extern u8 gWifiSetupAutoConnectDone;
extern u8 gWifiSetupAutoReceiveDone;
extern u8 gWifiSetupAutoDoneTimer;
extern u8 gWifiSetupAutoSearchDone;
extern WifiSetupApScanScreen gWifiSetupApScanScreen;
extern WifiSetupConnectionList gWifiSetupConnectionList;
extern void *ov13_0224F570;
extern WifiSetupMethodMenu gWifiSetupMethodMenu;
extern u8 gWifiSetupConnectionTestPassed;
extern u8 gWifiSetupConnectionOkTimer;
extern u8 gWifiSetupUsbConnectorDoneTimer;
extern u8 gWifiSetupUsbConnectorIntroNext;
extern u8 gWifiSetupUsbConnectorExit;

extern u8 gWifiSetupConnectionListSlotIconTemplates[];              // slot icon template per setup method (3 = empty)
extern WifiSetupPaletteRows gWifiSetupConnectionListPaletteRows[2]; // palette row per slot, icon palette per setup method
extern WifiSetupPoint gWifiSetupConnectionListIconPositions[];      // slot icons 0-2, erase buttons 3-5
extern WifiSetupRect gWifiSetupConnectionListTouchRects[];          // touch rects of the 7 selections
extern WifiSetupRect gWifiSetupConnectionListCursorRects[];         // cursor rects of the 7 selections
extern s8 gWifiSetupConnectionListEraseDigitPositions[];            // digit position of the erase dialog per language
extern WifiSetupPaletteRows gWifiSetupMethodMenuPaletteRows;        // palette row per setup method
extern WifiSetupPath22 gWifiSetupMethodMenuYbBgStep21NclPath;
extern s8 gWifiSetupMethodMenuCursorMoves[][4][4];         // next method per method and direction, -1 none, -2 last
extern WifiSetupRect gWifiSetupMethodMenuTouchRects[][4];  // touch rects of the methods
extern WifiSetupRect gWifiSetupMethodMenuCursorRects[][4]; // cursor rects of the methods
extern s8 gWifiSetupMethodMenuDigitPositions[];            // digit position of the method menu message per language
extern WifiSetupConnectionTestParams gWifiSetupConnectionTestParams;
extern WifiSetupTestPromptMessages gWifiSetupTestPromptMessages;
extern char gWifiSetupConnectionListYbObjMainNclPath[];
extern char gWifiSetupMethodMenuJbBgStep2NcgPath[];
extern char gWifiSetupMethodMenuYbBgStep2NclPath[];
extern char gWifiSetupMethodMenuJb3WayNscPath[];
extern char gWifiSetupConnectionTestJbBgStep3NcgPath[];
extern char gWifiSetupConnectionTestYbBgStep3NclPath[];
extern char gWifiSetupConnectionTestXb4MultiNscPath[];
extern char gWifiSetupConnectionOkXb4MultiNscPath[];
extern char gWifiSetupTestPromptXb4NoneNscPath[];
extern char gWifiSetupUsbConnectorDoneXb4MultiNscPath[];
extern char gWifiSetupUsbConnectorIntroJbBgStep2NcgPath[];
extern char gWifiSetupUsbConnectorIntroYbBgStep2NclPath[];
extern char gWifiSetupUsbConnectorIntroXb3MultiNscPath[];
extern char gWifiSetupUsbConnectorJbBgStep3NcgPath[];
extern char gWifiSetupUsbConnectorYbBgStep3NclPath[];
extern char gWifiSetupUsbConnectorJb4UsbNscPath[];

extern WifiSetupPath22 gWifiSetupConnectionListYbBgStep11NclPath;
extern char gWifiSetupSaveScreenJbBgStep3NcgPath[];
extern char gWifiSetupSaveScreenYbBgStep3NclPath[];
extern char gWifiSetupSaveScreenXb4NoneNscPath[];
extern char gWifiSetupAutoConnectXb4MultiNscPath[];
extern char gWifiSetupAutoReceiveXb4MultiNscPath[];
extern char gWifiSetupAutoDoneXb4MultiNscPath[];
extern char gWifiSetupAutoSearchJbBgStep3NcgPath[];
extern char gWifiSetupAutoSearchYbBgStep3NclPath[];
extern char gWifiSetupAutoSearchXb4MultiNscPath[];
extern char gWifiSetupApScanScreenJbBgStep3NcgPath[];
extern char gWifiSetupApScanScreenYbBgStep3NclPath[];
extern char gWifiSetupApScanScreenXb4MultiNscPath[];
extern char gWifiSetupConnectionListYbObjWayNclPath[];
extern char gWifiSetupConnectionListJbBgStep1NcgPath[];
extern char gWifiSetupConnectionListJbBgStep1NclPath[];
extern char gWifiSetupConnectionListJb2ApNscPath[];

int WifiSetupSettings_GetItemRow(int item);
int WifiSetupSettings_GetRowItem(int row);
void WifiSetupSettings_ScrollUpTask(WifiSetupTask *task, void *arg);
void WifiSetupSettings_ScrollDownTask(WifiSetupTask *task, void *arg);
void WifiSetupSettings_ScrollTask(WifiSetupTask *task, void *arg);
void WifiSetupSettings_ShowCursor(void);
void WifiSetupSettings_UpdateCursorItem(void);
void WifiSetupSettings_SetCursorItem(int item);
void WifiSetupSettings_MoveCursor(enum WifiSetupCursorDirection dir);
void WifiSetupSettings_HighlightButton(void);
void WifiSetupSettings_ButtonTask(WifiSetupTask *task, void *arg);
void WifiSetupSettings_PressButton(void);
BOOL WifiSetupSettings_IsComplete(void);
void WifiSetupSettings_WaitIncompleteDialog(void);
void WifiSetupSettings_SetFromMenu(BOOL fromMenu);

void WifiSetupSaveScreen_Init(void);

void WifiSetupAutoSearch_Init(void);

void WifiSetupApScanScreen_Init(void);

void WifiSetupConnectionList_Init(void);
void WifiSetupConnectionList_CreateIcons(void);
void WifiSetupConnectionList_FadeIn(void);
void WifiSetupConnectionList_ShowCursor(void);

void WifiSetupMethodMenu_Init(void);

void WifiSetupConnectionTest_Init(void);
void *WifiSetupConnectionTest_Alloc(void *arg, u32 size);
void WifiSetupConnectionTest_Free(void *arg, void *ptr);

void WifiSetupTestPrompt_Init(void);

void WifiSetupUsbConnectorDone_Init(void);

void WifiSetupUsbConnectorIntro_Init(void);

// Wi-Fi USB connector screen
void WifiSetupUsbConnector_Start(void);
void WifiSetupUsbConnector_ScanCallback(int result);
BOOL WifiSetupUsbConnector_IsLidClosed(void);

#endif // POKEHEARTGOLD_WIFI_SETUP_CONNECTION_SCREENS_H
