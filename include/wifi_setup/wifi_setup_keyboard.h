#ifndef POKEHEARTGOLD_WIFI_SETUP_KEYBOARD_H
#define POKEHEARTGOLD_WIFI_SETUP_KEYBOARD_H

#include "wifi_setup/wifi_setup_ui.h"

// Software keyboard of the access-point setup screens. Keys 0-46 are the character keys, 47-50 the extra keys on
// the right (47 alternate page, 48 shift, 49 space, 50 delete) and 51-52 the two buttons below the keyboard.

#define WIFI_SETUP_KEYBOARD_NUM_CHAR_KEYS  47
#define WIFI_SETUP_KEYBOARD_NUM_EXTRA_KEYS 4
#define WIFI_SETUP_KEYBOARD_NUM_BUTTONS    2

#define WIFI_SETUP_KEY_ALT_PAGE 47
#define WIFI_SETUP_KEY_SHIFT    48
#define WIFI_SETUP_KEY_SPACE    49
#define WIFI_SETUP_KEY_DELETE   50
#define WIFI_SETUP_KEY_BUTTON_0 51
#define WIFI_SETUP_KEY_BUTTON_1 52

// key pages (WifiSetupKeyboard.page)
#define WIFI_SETUP_KEYBOARD_PAGE_NORMAL  0
#define WIFI_SETUP_KEYBOARD_PAGE_SHIFTED 1 // for one character
#define WIFI_SETUP_KEYBOARD_PAGE_ALT     2
#define WIFI_SETUP_KEYBOARD_NUM_PAGES    3

// input codes besides the characters
#define WIFI_SETUP_KEYBOARD_INPUT_NONE   0
#define WIFI_SETUP_KEYBOARD_INPUT_DELETE 128 // the delete key and the B button
#define WIFI_SETUP_KEYBOARD_INPUT_BACK   130
#define WIFI_SETUP_KEYBOARD_INPUT_OK     131
#define WIFI_SETUP_KEYBOARD_INPUT_BUSY   255 // opening, or a page key the keyboard handles itself

typedef struct WifiSetupKeyboard {
    WifiSetupCanvas *rows[WIFI_SETUP_KEYBOARD_NUM_PAGES][4]; // text of the four key rows of each page
    GXOamAttr *keys[WIFI_SETUP_KEYBOARD_NUM_CHAR_KEYS];
    GXOamAttr *extraKeys[WIFI_SETUP_KEYBOARD_NUM_EXTRA_KEYS];
    WifiSetupOamBlock *buttons[WIFI_SETUP_KEYBOARD_NUM_BUTTONS];
    WifiSetupOamBlock *rowBlocks[4]; // objects showing the current page's rows
    WifiSetupOamBlock *cursor;
    WifiSetupTask *task;
    u8 input;      // WIFI_SETUP_KEYBOARD_INPUT_* or the character typed this frame
    u8 page;       // WIFI_SETUP_KEYBOARD_PAGE_*
    s8 pressedKey; // key the stylus went down on, -1 if none
    s8 hoveredKey; // key drawn highlighted, -1 if none
    s8 returnKey;  // key the cursor came from before entering a wide key
    s8 cursorKey;
    u8 repeatTimer; // frames the delete key has been held
    u8 canDelete;
    u8 canType;
    u8 deleteErrorPlayed; // B held with nothing to delete: error sound played once
} WifiSetupKeyboard;

extern WifiSetupKeyboard *gWifiSetupKeyboard;

// layout (positions and sizes in pixels on the touch screen)
extern const WifiSetupPoint gWifiSetupKeyboardKeyPositions[WIFI_SETUP_KEYBOARD_NUM_CHAR_KEYS];
extern const WifiSetupPoint ov13_02244F60;
extern const WifiSetupPoint gWifiSetupKeyboardButtonSize;
extern const WifiSetupPoint gWifiSetupKeyboardKeySize;
extern const WifiSetupPoint gWifiSetupKeyboardButtonPositions[WIFI_SETUP_KEYBOARD_NUM_BUTTONS];
extern const WifiSetupPoint gWifiSetupKeyboardExtraKeyPositions[];
extern const WifiSetupPoint gWifiSetupKeyboardShiftKeyPosition[];
extern const WifiSetupPoint gWifiSetupKeyboardSpaceDeleteKeyPositions[];
extern const WifiSetupPoint gWifiSetupKeyboardExtraKeySizes[];
extern const WifiSetupPoint gWifiSetupKeyboardShiftKeySize[];
extern const WifiSetupPoint gWifiSetupKeyboardSpaceDeleteKeySizes[];
extern WifiSetupRect gWifiSetupInputPanelRect;
extern u16 gWifiSetupKeyboardCursorX[];
extern u16 gWifiSetupKeyboardCursorY[];
extern const s8 gWifiSetupKeyboardCursorMoves[][4]; // next key for left, up, right, down

// input codes
extern u8 *gWifiSetupKeyboardPageKeyCodes[WIFI_SETUP_KEYBOARD_NUM_PAGES];
extern u8 gWifiSetupKeyboardExtraKeyCodes[];
extern u8 gWifiSetupKeyboardButtonCodes[];
extern int gWifiSetupKeyboardExtraKeySounds[];
extern const u8 gWifiSetupKeyboardKeyPalettes[4];    // normal, highlighted
extern const u8 gWifiSetupKeyboardButtonPalettes[4]; // normal, highlighted

void WifiSetupKeyboard_Create(void);
void WifiSetupKeyboard_Close(void);
int WifiSetupKeyboard_GetInput(void);
void WifiSetupKeyboard_SetCanDelete(int canDelete);
void WifiSetupKeyboard_SetCanType(int canType);
BOOL WifiSetupKeyboard_Exists(void);

void WifiSetupKeyboard_SlideInRow0Task(WifiSetupTask *task, void *arg);
void WifiSetupKeyboard_SlideInRow3Task(WifiSetupTask *task, void *arg);
// Moves row `row` (4: the buttons) of page `page` to height y.
void WifiSetupKeyboard_SetRowY();
void WifiSetupKeyboard_SetPage(int page);
void WifiSetupKeyboard_SetKeyHighlight(int key, int highlighted);
void WifiSetupKeyboard_UpdateCursor(void);
void WifiSetupKeyboard_MoveCursor(int direction);
void WifiSetupKeyboard_SlideOutButtonsTask(WifiSetupTask *task, void *arg);

void WifiSetupSound_Play(int seq);

#endif // POKEHEARTGOLD_WIFI_SETUP_KEYBOARD_H
