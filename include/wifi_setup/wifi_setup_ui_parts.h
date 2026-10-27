#ifndef POKEHEARTGOLD_WIFI_SETUP_UI_PARTS_H
#define POKEHEARTGOLD_WIFI_SETUP_UI_PARTS_H

#include "wifi_setup/wifi_setup_ui.h"

// Screen parts shared by the access-point setup screens: busy icon, sliding button bar, message window, cursors,
// BG1 frame, signal-strength icon and the software keyboard.

// Animated busy icon in the bottom-right corner of the touch screen.
typedef struct WifiSetupBusyIcon {
    WifiSetupTask *task;
    GXOamAttr *oam;
    u8 style; // index into the palette table
    u8 frameCounter;
} WifiSetupBusyIcon;

// Bar with up to two touch buttons that slides in from the bottom of the touch screen.
typedef struct WifiSetupButtonBar {
    WifiSetupOamBlock *buttons[2];
    WifiSetupOamBlock *bar;
    WifiSetupTask *task;
    WifiSetupTask *pressTask;
    u16 timer;
    s8 selected; // button index or WIFI_SETUP_SELECTED_*
    u8 type;
    u8 locked;
    u8 closing;
} WifiSetupButtonBar;

// Wireless signal strength icon in the top-right corner of the top screen.
typedef struct WifiSetupSignalIcon {
    GXOamAttr *oam;
    WifiSetupTask *task;
    s8 type;
} WifiSetupSignalIcon;

extern WifiSetupBusyIcon *gWifiSetupBusyIcon;
extern WifiSetupSignalIcon *gWifiSetupSignalIcon;
extern const u8 gWifiSetupBusyIconPalettes[];

extern WifiSetupButtonBar *gWifiSetupButtonBar;
extern u8 gWifiSetupMessageShown;
extern char gWifiSetupLocalizedPath[];
extern WifiSetupOamBlock **gWifiSetupCursorBlocks;
extern void *gWifiSetupBackgroundScreen;
extern WifiSetupPoint gWifiSetupButtonBarButtonSize;
extern u16 gWifiSetupButtonBarButtonX[];
extern u16 gWifiSetupButtonBarButtonY[];
extern u8 gWifiSetupButtonBarTemplates[][2]; // per button bar type
extern u8 gWifiSetupButtonBarPositions[][2]; // per button bar type
extern u8 gWifiSetupButtonBarButtonCounts[];
extern u32 gWifiSetupTextFlagsByLanguage[];
extern u16 gWifiSetupMessageTextX[];
extern u16 gWifiSetupMessageTextY[];
extern u8 gWifiSetupLanguageLetters[];
extern u8 gWifiSetupCursorPairTemplates[];
extern const u8 gWifiSetupSignalIconTemplates[][4];
extern u8 gWifiSetupKeyboardButtonTemplates[];
extern u8 gWifiSetupKeyboardExtraKeyTemplates[];
extern char sStr_CharJtNullNscL[];
extern char *gWifiSetupBackgroundScreenPaths[];
extern char sStr_CharJbBgHlNcgL[];
extern u16 *gWifiSetupKeyboardPageLabels[];

void WifiSetupBusyIcon_Create(u8 style);
void WifiSetupBusyIcon_Destroy(void);
void WifiSetupBusyIcon_Task(WifiSetupTask *task, void *arg);
void WifiSetupButtonBar_Close(void);
int WifiSetupButtonBar_GetSelected(void);
void WifiSetupButtonBar_SelectIfNone(int button);
void WifiSetupButtonBar_SetSelected(int button);
BOOL WifiSetupButtonBar_IsNotClosing(void);
void WifiSetupButtonBar_Unlock(void);
void WifiSetupButtonBar_Lock(void);
void WifiSetupMessage_Reset(void);
BOOL WifiSetupMessage_Show(int index, int pos, int digit);
BOOL WifiSetupMessage_Hide(void);
char *WifiSetup_LocalizePath(char *path);
void WifiSetup_LoadGraphics(char *path, void (*load)(const void *, u32, u32));
void WifiSetupBanner_Show(int kind);
void WifiSetupButtonBar_Show(int type);
void WifiSetup_PrintMessage(int message);
void WifiSetup_PrintMessageWithText(const u16 *str, int message);
u32 WifiSetup_GetTextFlags(void);
void WifiSetupCursor_Init(void);
void WifiSetupCursor_Free(void);
void WifiSetupCursor_ShowPair(int kind, int x1, int x2, int y);
void WifiSetupCursor_ShowCorners(int left, int right, int top, int bottom);
void WifiSetupCursor_Hide(void);
void WifiSetupBackground_Init(void);
void WifiSetupBackground_Free(void);
void WifiSetupBackground_LoadHeader(int index);
void WifiSetupBackground_LoadSlotHeader(void);
void WifiSetupBackground_LoadSlotListHeader(void);
void WifiSetupSignalIcon_Create(int type);
void WifiSetupSignalIcon_Destroy(void);

#endif // POKEHEARTGOLD_WIFI_SETUP_UI_PARTS_H
