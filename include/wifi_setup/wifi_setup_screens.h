#ifndef POKEHEARTGOLD_WIFI_SETUP_SCREENS_H
#define POKEHEARTGOLD_WIFI_SETUP_SCREENS_H

#include "global.h"

#include "wifi_setup/wifi_setup_access_points.h"
#include "wifi_setup/wifi_setup_ui.h"

// Access-point setup screens: the list screen and the text entry screen shared with the screens that
// follow them.

// Work of the list screen (allocated by the screen, gWifiSetupListScreen.work).
typedef struct WifiSetupListWork {
    WifiSetupScanEntry *entries;

    void *bgScreenFile;
    void *paletteFile;
    WifiSetupCanvas *canvas;
    GXOamAttr *rowOams[5];
    GXOamAttr *iconOams[5];
    WifiSetupTask *task;
    WifiSetupTask *scrollBgTask;
    u16 total;           // scroll range
    u16 rowKindChars[3]; // character numbers per row kind
    u16 iconChars[4];
    s8 selected;
    u8 count;
    u8 index;
    u8 scrollBarRange;
    u8 confirmed;
    u8 delay;
    u8 bgScrollDirty;
    u8 draggingScrollBar;
    u8 scrollLimitSoundPlayed;
    u8 cursorLimitSoundPlayed;
} WifiSetupListWork;

typedef struct WifiSetupListScreen {
    u8 selected;
    u8 unk_01;
    u16 position; // scroll position
    WifiSetupListWork *work;
} WifiSetupListScreen;

#define WIFI_SETUP_TEXT_ENTRY_MAX_LENGTH 32

// Text entry screen: the text typed and its length.
typedef struct WifiSetupTextEntry {
    WifiSetupCanvas *canvas;
    GXOamAttr *cursor;
    u8 text[WIFI_SETUP_TEXT_ENTRY_MAX_LENGTH + 1];
    u8 length;
    u8 flag;
} WifiSetupTextEntry;

// Status copied from the setup client's status callback.
typedef struct WifiSetupClientStatus {
    int state; // 0 idle .. 7, see WifiSetupClient_GetResult
    int timeLeft;
    int error;
} WifiSetupClientStatus;

typedef struct WifiSetupBytePair {
    u8 values[2];
} WifiSetupBytePair;

// Top menu: two choices, the screen's graphics file.
typedef struct WifiSetupTopMenu {
    u8 selected;
    void *graphics;
} WifiSetupTopMenu;

typedef struct WifiSetupMenu3 {
    u8 selected;
    u8 confirmed;
    void *graphics;
    GXOamAttr *oam;
} WifiSetupMenu3;

typedef struct WifiSetupWaitScreen {
    u8 flag;
    u16 counter;
    WifiSetupTask *task;
} WifiSetupWaitScreen;

typedef struct WifiSetupPaletteRow {
    u8 row;
} WifiSetupPaletteRow;

// Messages and store functions of the text entry screen, indexed by its screen arguments
typedef struct WifiSetupTextEntryParams {
    WifiSetupBytePair messages; // per field (SSID, WEP key)
    u16 unk_02;
    u32 unk_04;
    u32 confirmMessages[2];          // per second screen argument
    void (*storeFuncs[2])(u8 *text); // per field
} WifiSetupTextEntryParams;

extern WifiSetupClientStatus *gWifiSetupClientStatus;
extern WifiSetupTopMenu gWifiSetupTopMenu;
extern u8 gWifiSetupEraseConfirmed;
extern WifiSetupMenu3 gWifiSetupOptions;
extern u8 gWifiSetupTransferResult;
extern u8 gWifiSetupTransferIntroProceed;
extern u8 gWifiSetupTransferCancelledTimer;
extern u8 gWifiSetupTransferFailed[];
extern u8 gWifiSetupTransferConfirm[];
extern u8 gWifiSetupTransferWaitResult;
extern WifiSetupWaitScreen gWifiSetupAoss;
extern u8 gWifiSetupAossDoneTimer;
extern u8 ov13_0224F53C[];

extern const WifiSetupBytePair gWifiSetupTopMenuPaletteRows;
extern WifiSetupRect gWifiSetupTopMenuTouchRects[];
extern u16 gWifiSetupTopMenuCursorLeft[];
extern u16 gWifiSetupTopMenuCursorTop[];
extern u16 gWifiSetupTopMenuCursorRight[];
extern u16 gWifiSetupTopMenuCursorBottom[];
extern const WifiSetupPath22 gWifiSetupTopMenuYbBgStep11NclPath;
extern u8 gWifiSetupOptionsPaletteRows[];
extern const WifiSetupPath22 gWifiSetupOptionsYbBgOptionNclPath;
extern const WifiSetupPath23 gWifiSetupOptionsYbBgOption1NclPath;
extern WifiSetupRect gWifiSetupOptionsTouchRects[];
extern u16 gWifiSetupOptionsCursorLeft[];
extern u16 gWifiSetupOptionsCursorTop[];
extern u16 gWifiSetupOptionsCursorRight[];
extern u16 gWifiSetupOptionsCursorBottom[];
extern const WifiSetupPath22 gWifiSetupListScreenYbBgStep31NclPath;
extern const WifiSetupPath25 gWifiSetupListScreenXb4ApListBackNscPath;
extern WifiSetupRect gWifiSetupListScreenTouchRects[];
extern u16 gWifiSetupListScreenCursorLeft[];
extern u16 gWifiSetupListScreenCursorTop[];
extern u16 gWifiSetupListScreenCursorRight[];
extern const WifiSetupTextEntryParams gWifiSetupTextEntryParams;
extern char *gWifiSetupMessageBankPaths[];

// graphics and text bank paths
extern char gWifiSetupListScreenJb4ApListNscPath[];
extern u8 gWifiSetupListScreenRowTemplates[];
extern u8 gWifiSetupListScreenIconTemplates[];
extern char gWifiSetupAossJbBgStep3NcgPath[];
extern char gWifiSetupAossYbBgStep3NclPath[];
extern char gWifiSetupAossXb4MultiNscPath[];
extern char gWifiSetupAossDoneXb4MultiNscPath[];
extern char gWifiSetupTransferConfirmJb5MoveNscPath[];
extern char gWifiSetupTransferWaitYb5MultiNscPath[];
extern char gWifiSetupTransferIntroYb5MultiNscPath[];
extern char gWifiSetupTransferCancelledYb5MultiNscPath[];
extern char gWifiSetupTransferFailedYb5MultiNscPath[];
extern char sStr_MsgUsaBmgL[];
extern char sStr_CharJtMainNceL[];
extern char sStr_CharJbMainNceL[];
extern char sStr_CharJtBgMainNcgL[];
extern char sStr_CharJtBgMainNclL[];
extern char sStr_CharJtObjMainNcgL[];
extern char sStr_CharXtObjMainNclL[];
extern char sStr_CharJbBgStep1_NcgL[];
extern char sStr_CharJbBgStep1_NclL[];
extern char sStr_CharJbObjMainNcgL[];
extern char sStr_CharYbObjMainNclL[];
extern char sStr_CharJtTopNscL[];
extern char sStr_CharJtStep1_NscL[];
extern char sStr_CharJbBgStep1_NcgL_2[];
extern char sStr_CharJbBgStep1_NclL_2[];
extern char sStr_CharJb2MenuNscL[];
extern char sStr_CharYb5MultiNscL[];
extern char sStr_CharYb5MultiNscL_2[];
extern char sStr_CharJb5InfoNscL[];
extern char gWifiSetupOptionsJbBgOptionNcgPath[];
extern char gWifiSetupOptionsJb5OptMenuNscPath[];
extern char gWifiSetupTransferringYb5MultiNscPath[];

extern const WifiSetupPaletteRow gWifiSetupListScreenRescanPaletteRow;
extern u8 gWifiSetupTextEntryCursorRowY[];
extern u8 gWifiSetupTextEntryColumnX[];
extern char gWifiSetupTextEntryYbObjKbNclPath[];
extern char gWifiSetupTextEntryJbBgStep3NcgPath[];
extern char gWifiSetupTextEntryYbBgStep3NclPath[];
extern char gWifiSetupTextEntryXb4EditNscPath[];
extern char gWifiSetupTextEntryYbObjMainNclPath[];

extern u16 gWifiSetupSystemInfoMacFormat[];
extern u16 gWifiSetupSystemInfoIdFormat[];
extern u16 gWifiSetupSystemInfoNoIdText[];

extern WifiSetupListScreen gWifiSetupListScreen;
extern WifiSetupTextEntry *gWifiSetupTextEntry;

void WifiSetupClient_Start(void);
void WifiSetupClient_Stop(void);
int WifiSetupClient_GetResult(void);
void WifiSetupClient_StoreResult(void);
void WifiSetupScreens_StartQuit(void);
void WifiSetupScreens_Init(void);
void WifiSetupTopMenu_Init(void);
void WifiSetupAoss_Init(void);
void WifiSetupListScreen_Init(void);
void WifiSetupTextEntry_Init(void);

#endif // POKEHEARTGOLD_WIFI_SETUP_SCREENS_H
