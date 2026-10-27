#include "global.h"

#include "dwc/dwc_bm_internal.h"
#include "wifi_setup/wifi_setup_access_points.h"
#include "wifi_setup/wifi_setup_address_entry.h"
#include "wifi_setup/wifi_setup_app.h"
#include "wifi_setup/wifi_setup_connection_screens.h"
#include "wifi_setup/wifi_setup_local_wireless.h"
#include "wifi_setup/wifi_setup_screens.h"
#include "wifi_setup/wifi_setup_scroll_bar.h"
#include "wifi_setup/wifi_setup_settings.h"
#include "wifi_setup/wifi_setup_ui.h"
#include "wifi_setup/wifi_setup_ui_parts.h"

#include <nitro/code32.h>

// Access-point setup: the screen of the three connection slots, the menu of the four setup methods, the connection
// test, and the screens before and after the Wi-Fi USB connector screen.

extern BOOL DWC_AC_Create(WifiSetupConnectionTestParams *params);
extern int DWC_AC_Process(void);
extern int DWC_AC_GetStatus(void);
extern BOOL DWC_AC_Destroy(void);
extern void DWCi_AC_SetUserProfile(int slot, WifiSetupConnection *connection);

static void WifiSetupConnectionList_WaitFadeIn(void);
static void WifiSetupConnectionList_WaitButtonBar(void);
static void WifiSetupConnectionList_Main(void);
static void WifiSetupConnectionList_HandleInput(void);
static void WifiSetupConnectionList_Update(void);
static void WifiSetupConnectionList_CheckButtons(void);
static void WifiSetupConnectionList_Exit(void);
static void WifiSetupConnectionList_WaitFadeOut(void);
static void WifiSetupConnectionList_End(void);
static void WifiSetupConnectionList_MoveCursor(int dir);
static void WifiSetupConnectionList_PressEraseButton(void);
static void WifiSetupConnectionList_WaitEraseDialog(void);
static void WifiSetupConnectionList_WaitEraseDialogClosed(void);
static void WifiSetupConnectionList_HighlightSelection(void);
static void WifiSetupMethodMenu_LoadGraphics(void);
static void WifiSetupMethodMenu_FadeIn(void);
static void WifiSetupMethodMenu_WaitFadeIn(void);
static void WifiSetupMethodMenu_WaitButtonBar(void);
static void WifiSetupMethodMenu_Main(void);
static void WifiSetupMethodMenu_HandleInput(void);
static void WifiSetupMethodMenu_Update(void);
static void WifiSetupMethodMenu_CheckButtons(void);
static void WifiSetupMethodMenu_Exit(void);
static void WifiSetupMethodMenu_WaitFadeOut(void);
static void WifiSetupMethodMenu_End(void);
static void WifiSetupMethodMenu_MoveCursor(int dir);
static void WifiSetupMethodMenu_HighlightSelection(void);
static void WifiSetupConnectionTest_LoadGraphics(void);
static void WifiSetupConnectionTest_Start(void);
static void WifiSetupConnectionTest_FadeIn(void);
static void WifiSetupConnectionTest_WaitFadeIn(void);
static void WifiSetupConnectionTest_Main(void);
static void WifiSetupConnectionTest_HandleInput(void);
static void WifiSetupConnectionTest_Update(void);
static void WifiSetupConnectionTest_CheckButtons(void);
static void WifiSetupConnectionTest_FadeOut(void);
static void WifiSetupConnectionTest_WaitFadeOut(void);
static void WifiSetupConnectionTest_End(void);
static void WifiSetupConnectionTest_PollTask(WifiSetupTask *task, void *arg);
static void WifiSetupConnectionOk_Init(void);
static void WifiSetupConnectionOk_LoadGraphics(void);
static void WifiSetupConnectionOk_FadeIn(void);
static void WifiSetupConnectionOk_WaitFadeIn(void);
static void WifiSetupConnectionOk_Main(void);
static void WifiSetupConnectionOk_Update(void);
static void WifiSetupConnectionOk_FadeOut(void);
static void WifiSetupConnectionOk_End(void);
static void WifiSetupConnectionOk_UpdateTimer(void);
static void WifiSetupTestPrompt_LoadGraphics(void);
static void WifiSetupTestPrompt_FadeIn(void);
static void WifiSetupTestPrompt_WaitFadeIn(void);
static void WifiSetupTestPrompt_Main(void);
static void WifiSetupTestPrompt_HandleInput(void);
static void WifiSetupTestPrompt_Update(void);
static void WifiSetupTestPrompt_WaitDialogClosed(void);
static void WifiSetupTestPrompt_End(void);
static void WifiSetupUsbConnectorDone_LoadGraphics(void);
static void WifiSetupUsbConnectorDone_FadeIn(void);
static void WifiSetupUsbConnectorDone_WaitFadeIn(void);
static void WifiSetupUsbConnectorDone_Main(void);
static void WifiSetupUsbConnectorDone_Update(void);
static void WifiSetupUsbConnectorDone_FadeOut(void);
static void WifiSetupUsbConnectorDone_End(void);
static void WifiSetupUsbConnectorDone_UpdateTimer(void);
static void WifiSetupUsbConnectorIntro_LoadGraphics(void);
static void WifiSetupUsbConnectorIntro_FadeIn(void);
static void WifiSetupUsbConnectorIntro_WaitFadeIn(void);
static void WifiSetupUsbConnectorIntro_WaitButtonBar(void);
static void WifiSetupUsbConnectorIntro_Main(void);
static void WifiSetupUsbConnectorIntro_HandleInput(void);
static void WifiSetupUsbConnectorIntro_Update(void);
static void WifiSetupUsbConnectorIntro_CheckButtons(void);
static void WifiSetupUsbConnectorIntro_Exit(void);
static void WifiSetupUsbConnectorIntro_WaitFadeOut(void);
static void WifiSetupUsbConnectorIntro_End(void);
static void WifiSetupUsbConnector_Init(void);
static void WifiSetupUsbConnector_LoadGraphics(void);

void WifiSetupConnectionList_CreateIcons(void) {
    int k;
    int i;
    int j;
    for (i = 0; i < 3; i++) {
        k = WifiSetupConnections_GetSetupMethod(i);
        if (k == WIFI_SETUP_METHOD_ERASED) {
            k = 3;
        } else {
            gWifiSetupConnectionList.work->eraseButtons[i] = WifiSetupOamTemplate_AllocBlock(0, 0x11, 1);
            j = i + 3;
            WifiSetupOamBlock_SetPosition(gWifiSetupConnectionList.work->eraseButtons[i], -1, gWifiSetupConnectionListIconPositions[j].x, gWifiSetupConnectionListIconPositions[j].y);
            WifiSetupOamBlock_SetPriority(gWifiSetupConnectionList.work->eraseButtons[i], -1, 3);
        }
        gWifiSetupConnectionList.work->slotIcons[i] = WifiSetupOamTemplate_AllocBlock(0, gWifiSetupConnectionListSlotIconTemplates[k], 1);
        WifiSetupOamBlock_SetPosition(gWifiSetupConnectionList.work->slotIcons[i], -1, gWifiSetupConnectionListIconPositions[i].x, gWifiSetupConnectionListIconPositions[i].y);
        WifiSetupOamBlock_SetPriority(gWifiSetupConnectionList.work->slotIcons[i], -1, 3);
    }
}

void WifiSetupConnectionList_FadeIn(void) {
    WifiSetupFade_Start(WIFI_SETUP_FADE_IN_FROM_WHITE, WIFI_SETUP_SCREEN_SUB, GX_BLEND_PLANEMASK_BG0, 8);
    WifiSetupFade_Start(WIFI_SETUP_FADE_IN_FROM_WHITE, WIFI_SETUP_SCREEN_MAIN, GX_BLEND_PLANEMASK_BG2 | GX_BLEND_PLANEMASK_OBJ, 8);
    WifiSetupDisplay_ShowPlanes(WIFI_SETUP_SCREEN_SUB, GX_PLANEMASK_BG0);
    WifiSetupDisplay_ShowPlanes(WIFI_SETUP_SCREEN_MAIN, GX_PLANEMASK_BG2 | GX_PLANEMASK_OBJ);
    WifiSetupApp_SetStateFunc(WifiSetupConnectionList_WaitFadeIn);
}

static void WifiSetupConnectionList_WaitFadeIn(void) {
    if (WifiSetupFade_IsActive(WIFI_SETUP_SCREEN_SUB)) {
        return;
    }
    if (WifiSetupFade_IsActive(WIFI_SETUP_SCREEN_MAIN)) {
        return;
    }
    WifiSetupButtonBar_Show(0);
    WifiSetupApp_SetStateFunc(WifiSetupConnectionList_WaitButtonBar);
}

static void WifiSetupConnectionList_WaitButtonBar(void) {
    if (WifiSetupButtonBar_GetSelected() == WIFI_SETUP_SELECTED_NOT_SHOWN) {
        return;
    }
    if (WifiSetupBanner_IsMoving() == 1) {
        return;
    }
    WifiSetupButtonBar_Unlock();
    WifiSetupApp_SetStateFunc(WifiSetupConnectionList_Main);
}

static void WifiSetupConnectionList_Main(void) {
    WifiSetupConnectionList_HandleInput();
    WifiSetupConnectionList_Update();
    WifiSetupConnectionList_CheckButtons();
}

static void WifiSetupConnectionList_HandleInput(void) {
    u32 i;
    for (i = 0; i < 7; i++) {
        if (WifiSetupInput_IsTouchPressed(&gWifiSetupConnectionListTouchRects[i])) {
            WifiSetupButtonBar_SelectIfNone(1);
            gWifiSetupConnectionList.selected = i;
            WifiSetupConnectionList_ShowCursor();
            return;
        }
    }
    if (WifiSetupInput_IsKeyPressed(PAD_BUTTON_A)) {
        WifiSetupButtonBar_SelectIfNone(1);
        return;
    }
    if (WifiSetupInput_IsKeyPressed(PAD_BUTTON_B)) {
        WifiSetupButtonBar_SelectIfNone(0);
        return;
    }
    if (WifiSetupInput_IsKeyRepeated(PAD_KEY_UP)) {
        WifiSetupConnectionList_MoveCursor(WIFI_SETUP_CURSOR_UP);
        return;
    }
    if (WifiSetupInput_IsKeyRepeated(PAD_KEY_DOWN)) {
        WifiSetupConnectionList_MoveCursor(WIFI_SETUP_CURSOR_DOWN);
        return;
    }
    if (WifiSetupInput_IsKeyRepeated(PAD_KEY_LEFT)) {
        WifiSetupConnectionList_MoveCursor(WIFI_SETUP_CURSOR_LEFT);
        return;
    }
    if (WifiSetupInput_IsKeyRepeated(PAD_KEY_RIGHT)) {
        WifiSetupConnectionList_MoveCursor(WIFI_SETUP_CURSOR_RIGHT);
    }
}

static void WifiSetupConnectionList_Update(void) {
}

static void WifiSetupConnectionList_CheckButtons(void) {
    u8 sel;
    int idx;
    int k;
    switch (WifiSetupButtonBar_GetSelected()) {
    case 0:
        switch (WifiSetupApp_GetKind()) {
        case WIFI_SETUP_KIND_TOP_MENU:
            WifiSetupSound_Play(7);
            gWifiSetupConnectionList.work->exit = WIFI_SETUP_CONNECTION_LIST_BACK;
            break;
        case WIFI_SETUP_KIND_CONNECTION_LIST:
            WifiSetupButtonBar_Lock();
            WifiSetupApp_SetStateFunc(WifiSetupScreens_StartQuit);
            return;
        }
        break;
    case 1:
        gWifiSetupConnectionList.work->exit = WIFI_SETUP_CONNECTION_LIST_NEXT;
        sel = gWifiSetupConnectionList.selected;
        if (sel >= WIFI_SETUP_CONNECTION_LIST_FIRST_ERASE) {
            idx = sel - WIFI_SETUP_CONNECTION_LIST_FIRST_ERASE;
            if (WifiSetupConnections_GetSetupMethod(idx) == WIFI_SETUP_METHOD_ERASED) {
                WifiSetupSound_Play(9);
                WifiSetupButtonBar_SetSelected(WIFI_SETUP_SELECTED_NONE);
                return;
            }
            WifiSetupSound_Play(6);
            k = gWifiSetupConnectionListEraseDigitPositions[WifiSetupApp_GetLanguage()];
            WifiSetupDialog_Open(0x46, 0, 1, k, idx + 1);
            WifiSetupConnectionList_PressEraseButton();
            WifiSetupButtonBar_Lock();
            WifiSetupApp_SetStateFunc(WifiSetupConnectionList_WaitEraseDialog);
            return;
        }
        if (sel <= 2) {
            WifiSetupConnections_Edit(sel);
        }
        WifiSetupSound_Play(6);
        WifiSetupConnectionList_HighlightSelection();
        break;
    default:
        return;
    }
    WifiSetupApp_SetStateFunc(WifiSetupConnectionList_Exit);
}

static void WifiSetupConnectionList_Exit(void) {
    if (gWifiSetupConnectionList.work->exit == WIFI_SETUP_CONNECTION_LIST_BACK) {
        WifiSetupBanner_Close();
    }
    WifiSetupButtonBar_Lock();
    WifiSetupFade_StartDelay(8);
    WifiSetupApp_SetStateFunc(WifiSetupConnectionList_WaitFadeOut);
}

static void WifiSetupConnectionList_WaitFadeOut(void) {
    if (WifiSetupFade_IsActive(WIFI_SETUP_SCREEN_SUB)) {
        return;
    }
    if (gWifiSetupConnectionList.work->exit == WIFI_SETUP_CONNECTION_LIST_NEXT) {
        if (gWifiSetupConnectionList.selected == WIFI_SETUP_CONNECTION_LIST_USB || WifiSetupConnections_GetEdit()->settings.setupMethod != WIFI_SETUP_METHOD_ERASED) {
            WifiSetupButtonBar_Close();
        }
    }
    WifiSetupFade_Start(WIFI_SETUP_FADE_OUT_TO_WHITE, WIFI_SETUP_SCREEN_SUB, GX_BLEND_PLANEMASK_BG0, 8);
    WifiSetupFade_Start(WIFI_SETUP_FADE_OUT_TO_WHITE, WIFI_SETUP_SCREEN_MAIN, GX_BLEND_PLANEMASK_BG2 | GX_BLEND_PLANEMASK_OBJ, 8);
    WifiSetupApp_SetStateFunc(WifiSetupConnectionList_End);
}

static void WifiSetupConnectionList_End(void) {
    u32 i;
    if (WifiSetupFade_IsActive(WIFI_SETUP_SCREEN_SUB)) {
        return;
    }
    if (WifiSetupFade_IsActive(WIFI_SETUP_SCREEN_MAIN)) {
        return;
    }
    if (!WifiSetupBanner_IsNotClosing()) {
        return;
    }
    if (!WifiSetupButtonBar_IsNotClosing()) {
        return;
    }
    for (i = 0; i < 3; i++) {
        if (gWifiSetupConnectionList.work->slotIcons[i] != NULL) {
            WifiSetupOamBlock_Free(gWifiSetupConnectionList.work->slotIcons[i]);
        }
    }
    for (i = 0; i < 3; i++) {
        if (gWifiSetupConnectionList.work->eraseButtons[i] != NULL) {
            WifiSetupOamBlock_Free(gWifiSetupConnectionList.work->eraseButtons[i]);
        }
    }
    WifiSetupCursor_Hide();
    WifiSetupMessage_Hide();
    WifiSetupFile_Free(gWifiSetupConnectionList.work->graphics);
    WifiSetup_LoadGraphics(gWifiSetupConnectionListYbObjMainNclPath, GX_LoadOBJPltt);
    WifiSetupDisplay_HidePlanes(WIFI_SETUP_SCREEN_SUB, GX_PLANEMASK_BG0);
    WifiSetupDisplay_HidePlanes(WIFI_SETUP_SCREEN_MAIN, GX_PLANEMASK_BG2 | GX_PLANEMASK_OBJ);
    if (gWifiSetupConnectionList.work->exit == WIFI_SETUP_CONNECTION_LIST_BACK) {
        WifiSetupApp_SetTransition(WIFI_SETUP_BANNER_KEEP, WIFI_SETUP_BUTTON_BAR_KEEP);
        WifiSetupApp_SetStateFunc(WifiSetupTopMenu_Init);
    } else {
        switch (gWifiSetupConnectionList.selected) {
        case 0:
        case 1:
        case 2:
            WifiSetupApp_SetTransition(WIFI_SETUP_BANNER_CHANGE, WIFI_SETUP_BUTTON_BAR_KEEP);
            if (WifiSetupConnections_GetEdit()->settings.setupMethod == WIFI_SETUP_METHOD_ERASED) {
                WifiSetupApp_SetStateFunc(WifiSetupMethodMenu_Init);
            } else {
                WifiSetupApp_SetScreenArgs(0, 0);
                WifiSetupSettings_SetFromMenu(FALSE);
                WifiSetupApp_SetStateFunc(WifiSetupSettings_Init);
            }
            break;
        case WIFI_SETUP_CONNECTION_LIST_USB:
            WifiSetupApp_SetTransition(WIFI_SETUP_BANNER_CHANGE, WIFI_SETUP_BUTTON_BAR_CREATE);
            WifiSetupApp_SetStateFunc(WifiSetupUsbConnectorIntro_Init);
            break;
        }
    }
    WifiSetupHeap_FreeAndClear(&ov13_0224F570);
}

void WifiSetupConnectionList_ShowCursor(void) {
    u8 sel = gWifiSetupConnectionList.selected;
    if (sel < WIFI_SETUP_CONNECTION_LIST_FIRST_ERASE) {
        WifiSetupCursor_ShowCorners(gWifiSetupConnectionListCursorRects[sel].left, gWifiSetupConnectionListCursorRects[sel].right, gWifiSetupConnectionListCursorRects[sel].top, gWifiSetupConnectionListCursorRects[sel].bottom);
    } else {
        WifiSetupCursor_ShowPair(0, gWifiSetupConnectionListCursorRects[sel].left, gWifiSetupConnectionListCursorRects[sel].right, gWifiSetupConnectionListCursorRects[sel].top);
    }
}

static void WifiSetupConnectionList_MoveCursor(int dir) {
    BOOL changed = TRUE;
    u8 column;
    int columnBelow;
    switch (gWifiSetupConnectionList.selected) {
    case 0:
        gWifiSetupConnectionList.work->column = 0;
        if (dir == WIFI_SETUP_CURSOR_LEFT) {
            gWifiSetupConnectionList.selected = 2;
        } else if (dir == WIFI_SETUP_CURSOR_RIGHT) {
            gWifiSetupConnectionList.selected = 1;
        } else if (dir == WIFI_SETUP_CURSOR_UP) {
            gWifiSetupConnectionList.selected = WIFI_SETUP_CONNECTION_LIST_USB;
        } else {
            gWifiSetupConnectionList.selected = 4;
        }
        break;
    case 1:
        gWifiSetupConnectionList.work->column = 1;
        if (dir == WIFI_SETUP_CURSOR_LEFT) {
            gWifiSetupConnectionList.selected = 0;
        } else if (dir == WIFI_SETUP_CURSOR_RIGHT) {
            gWifiSetupConnectionList.selected = 2;
        } else if (dir == WIFI_SETUP_CURSOR_UP) {
            gWifiSetupConnectionList.selected = WIFI_SETUP_CONNECTION_LIST_USB;
        } else {
            gWifiSetupConnectionList.selected = 5;
        }
        break;
    case 2:
        gWifiSetupConnectionList.work->column = 2;
        if (dir == WIFI_SETUP_CURSOR_LEFT) {
            gWifiSetupConnectionList.selected = 1;
        } else if (dir == WIFI_SETUP_CURSOR_RIGHT) {
            gWifiSetupConnectionList.selected = 0;
        } else if (dir == WIFI_SETUP_CURSOR_UP) {
            gWifiSetupConnectionList.selected = WIFI_SETUP_CONNECTION_LIST_USB;
        } else {
            gWifiSetupConnectionList.selected = 6;
        }
        break;
    case WIFI_SETUP_CONNECTION_LIST_USB:
        column = gWifiSetupConnectionList.work->column;
        columnBelow = column + WIFI_SETUP_CONNECTION_LIST_FIRST_ERASE;
        if (dir == WIFI_SETUP_CURSOR_UP) {
            gWifiSetupConnectionList.selected = columnBelow;
        } else if (dir == WIFI_SETUP_CURSOR_DOWN) {
            gWifiSetupConnectionList.selected = column;
        } else {
            changed = FALSE;
        }
        break;
    case 4:
        gWifiSetupConnectionList.work->column = 0;
        if (dir == WIFI_SETUP_CURSOR_LEFT) {
            gWifiSetupConnectionList.selected = 6;
        } else if (dir == WIFI_SETUP_CURSOR_RIGHT) {
            gWifiSetupConnectionList.selected = 5;
        } else if (dir == WIFI_SETUP_CURSOR_UP) {
            gWifiSetupConnectionList.selected = 0;
        } else {
            gWifiSetupConnectionList.selected = WIFI_SETUP_CONNECTION_LIST_USB;
        }
        break;
    case 5:
        gWifiSetupConnectionList.work->column = 1;
        if (dir == WIFI_SETUP_CURSOR_LEFT) {
            gWifiSetupConnectionList.selected = 4;
        } else if (dir == WIFI_SETUP_CURSOR_RIGHT) {
            gWifiSetupConnectionList.selected = 6;
        } else if (dir == WIFI_SETUP_CURSOR_UP) {
            gWifiSetupConnectionList.selected = 1;
        } else {
            gWifiSetupConnectionList.selected = WIFI_SETUP_CONNECTION_LIST_USB;
        }
        break;
    case 6:
        gWifiSetupConnectionList.work->column = 2;
        if (dir == WIFI_SETUP_CURSOR_LEFT) {
            gWifiSetupConnectionList.selected = 5;
        } else if (dir == WIFI_SETUP_CURSOR_RIGHT) {
            gWifiSetupConnectionList.selected = 4;
        } else if (dir == WIFI_SETUP_CURSOR_UP) {
            gWifiSetupConnectionList.selected = 2;
        } else {
            gWifiSetupConnectionList.selected = WIFI_SETUP_CONNECTION_LIST_USB;
        }
        break;
    }
    if (changed) {
        WifiSetupSound_Play(8);
        WifiSetupConnectionList_ShowCursor();
    }
}

static void WifiSetupConnectionList_PressEraseButton(void) {
    int idx = gWifiSetupConnectionList.selected - WIFI_SETUP_CONNECTION_LIST_FIRST_ERASE;
    WifiSetupOamTemplate_Copy(0, 0x32, WifiSetupOamBlock_GetOam(gWifiSetupConnectionList.work->eraseButtons[idx], 0));
    WifiSetupOamBlock_SetPosition(gWifiSetupConnectionList.work->eraseButtons[idx], -1, gWifiSetupConnectionListIconPositions[idx + 3].x, gWifiSetupConnectionListIconPositions[idx + 3].y);
    WifiSetupOamBlock_SetPriority(gWifiSetupConnectionList.work->eraseButtons[idx], -1, 3);
}

static void WifiSetupConnectionList_WaitEraseDialog(void) {
    int idx = gWifiSetupConnectionList.selected - WIFI_SETUP_CONNECTION_LIST_FIRST_ERASE;
    switch (WifiSetupDialog_GetSelected()) {
    case 1:
        WifiSetupSound_Play(0xE);
        WifiSetupConnections_Erase(idx);
        WifiSetupOamTemplate_Copy(0, 0x56, WifiSetupOamBlock_GetOam(gWifiSetupConnectionList.work->slotIcons[idx], 0));
        WifiSetupOamBlock_SetPosition(gWifiSetupConnectionList.work->slotIcons[idx], -1, gWifiSetupConnectionListIconPositions[idx].x, gWifiSetupConnectionListIconPositions[idx].y);
        WifiSetupOamBlock_SetPriority(gWifiSetupConnectionList.work->slotIcons[idx], -1, 3);
        WifiSetupOamBlock_Free(gWifiSetupConnectionList.work->eraseButtons[idx]);
        gWifiSetupConnectionList.work->eraseButtons[idx] = NULL;
        break;
    case 0:
        WifiSetupSound_Play(7);
        WifiSetupOamTemplate_Copy(0, 0x11, WifiSetupOamBlock_GetOam(gWifiSetupConnectionList.work->eraseButtons[idx], 0));
        WifiSetupOamBlock_SetPosition(gWifiSetupConnectionList.work->eraseButtons[idx], -1, gWifiSetupConnectionListIconPositions[idx + 3].x, gWifiSetupConnectionListIconPositions[idx + 3].y);
        WifiSetupOamBlock_SetPriority(gWifiSetupConnectionList.work->eraseButtons[idx], -1, 3);
        break;
    default:
        return;
    }
    WifiSetupDialog_Close();
    WifiSetupApp_SetStateFunc(WifiSetupConnectionList_WaitEraseDialogClosed);
}

static void WifiSetupConnectionList_WaitEraseDialogClosed(void) {
    if (WifiSetupDialog_IsOpen()) {
        return;
    }
    WifiSetupButtonBar_Unlock();
    WifiSetupApp_SetStateFunc(WifiSetupConnectionList_Main);
}

static void WifiSetupConnectionList_HighlightSelection(void) {
    WifiSetupPaletteRows rows = gWifiSetupConnectionListPaletteRows[0];
    WifiSetupPaletteRows palettes = gWifiSetupConnectionListPaletteRows[1];
    int k;
    if (gWifiSetupConnectionList.selected > WIFI_SETUP_CONNECTION_LIST_USB) {
        return;
    }
    WifiSetupPalette_LoadRow(gWifiSetupConnectionList.work->graphics, rows.rows[gWifiSetupConnectionList.selected], rows.rows[gWifiSetupConnectionList.selected]);
    if (gWifiSetupConnectionList.selected == WIFI_SETUP_CONNECTION_LIST_USB) {
        return;
    }
    k = WifiSetupConnections_GetSetupMethod(gWifiSetupConnectionList.selected);
    if (k > 2) {
        k = 3;
    }
    WifiSetupOamBlock_SetModeAndPalette(gWifiSetupConnectionList.work->slotIcons[gWifiSetupConnectionList.selected], -1, 0, palettes.rows[k]);
}

void WifiSetupMethodMenu_Init(void) {
    WifiSetupConnection *connection = WifiSetupConnections_GetEdit();
    int k;
    gWifiSetupMethodMenu.confirmed = FALSE;
    if (gWifiSetupMethodMenu.lastOption == 0) {
        gWifiSetupMethodMenu.lastOption = 1;
    }
    if (WifiSetupApp_GetLanguage()) {
        if (gWifiSetupMethodMenu.selected == WIFI_SETUP_METHOD_MENU_AUTO) {
            gWifiSetupMethodMenu.selected = WIFI_SETUP_METHOD_MENU_AP_SCAN;
        }
        if (gWifiSetupMethodMenu.lastOption == 2) {
            gWifiSetupMethodMenu.lastOption = 1;
        }
    }
    WifiSetupMethodMenu_LoadGraphics();
    WifiSetupBackground_LoadSlotHeader();
    k = WifiSetupApp_GetLanguage();
    WifiSetupMessage_Show(0x32, gWifiSetupMethodMenuDigitPositions[k], connection->index + 1);
    WifiSetupBanner_Show(1);
    WifiSetupCursor_ShowCorners(gWifiSetupMethodMenuCursorRects[WifiSetupApp_HasOption(1)][gWifiSetupMethodMenu.selected].left, gWifiSetupMethodMenuCursorRects[WifiSetupApp_HasOption(1)][gWifiSetupMethodMenu.selected].right, gWifiSetupMethodMenuCursorRects[WifiSetupApp_HasOption(1)][gWifiSetupMethodMenu.selected].top, gWifiSetupMethodMenuCursorRects[WifiSetupApp_HasOption(1)][gWifiSetupMethodMenu.selected].bottom);
    WifiSetupApp_SetStateFunc(WifiSetupMethodMenu_FadeIn);
}

static void WifiSetupMethodMenu_LoadGraphics(void) {
    WifiSetupPath22 path = gWifiSetupMethodMenuYbBgStep21NclPath;
    WifiSetup_LoadGraphics(gWifiSetupMethodMenuJbBgStep2NcgPath, GX_LoadBG2Char);
    WifiSetup_LoadGraphics(gWifiSetupMethodMenuYbBgStep2NclPath, GX_LoadBGPltt);
    WifiSetup_LoadGraphics(gWifiSetupMethodMenuJb3WayNscPath, GX_LoadBG2Scr);
    gWifiSetupMethodMenu.graphics = WifiSetupFile_Load(WifiSetup_LocalizePath(path.text), NULL, 4);
    G2S_SetBG0Priority(3);
    G2S_SetBG1Priority(3);
    G2_SetBG1Priority(3);
    G2_SetBG2Priority(3);
}

static void WifiSetupMethodMenu_FadeIn(void) {
    WifiSetupFade_Start(WIFI_SETUP_FADE_IN_FROM_WHITE, WIFI_SETUP_SCREEN_SUB, GX_BLEND_PLANEMASK_BG0, 8);
    WifiSetupFade_Start(WIFI_SETUP_FADE_IN_FROM_WHITE, WIFI_SETUP_SCREEN_MAIN, GX_BLEND_PLANEMASK_BG2 | GX_BLEND_PLANEMASK_OBJ, 8);
    WifiSetupDisplay_ShowPlanes(WIFI_SETUP_SCREEN_SUB, GX_PLANEMASK_BG0);
    WifiSetupDisplay_ShowPlanes(WIFI_SETUP_SCREEN_MAIN, GX_PLANEMASK_BG2 | GX_PLANEMASK_OBJ);
    WifiSetupApp_SetStateFunc(WifiSetupMethodMenu_WaitFadeIn);
}

static void WifiSetupMethodMenu_WaitFadeIn(void) {
    if (WifiSetupFade_IsActive(WIFI_SETUP_SCREEN_SUB)) {
        return;
    }
    if (WifiSetupFade_IsActive(WIFI_SETUP_SCREEN_MAIN)) {
        return;
    }
    WifiSetupButtonBar_Show(0);
    WifiSetupApp_SetStateFunc(WifiSetupMethodMenu_WaitButtonBar);
}

static void WifiSetupMethodMenu_WaitButtonBar(void) {
    if (WifiSetupButtonBar_GetSelected() == WIFI_SETUP_SELECTED_NOT_SHOWN) {
        return;
    }
    WifiSetupButtonBar_Unlock();
    WifiSetupApp_SetStateFunc(WifiSetupMethodMenu_Main);
}

static void WifiSetupMethodMenu_Main(void) {
    WifiSetupMethodMenu_HandleInput();
    WifiSetupMethodMenu_Update();
    WifiSetupMethodMenu_CheckButtons();
}

static void WifiSetupMethodMenu_HandleInput(void) {
    u32 i;
    for (i = 0; i < 4; i++) {
        if (WifiSetupInput_IsTouchPressed(&gWifiSetupMethodMenuTouchRects[WifiSetupApp_HasOption(1)][i])) {
            WifiSetupButtonBar_SelectIfNone(1);
            gWifiSetupMethodMenu.selected = i;
            WifiSetupCursor_ShowCorners(gWifiSetupMethodMenuCursorRects[WifiSetupApp_HasOption(1)][gWifiSetupMethodMenu.selected].left, gWifiSetupMethodMenuCursorRects[WifiSetupApp_HasOption(1)][gWifiSetupMethodMenu.selected].right, gWifiSetupMethodMenuCursorRects[WifiSetupApp_HasOption(1)][gWifiSetupMethodMenu.selected].top, gWifiSetupMethodMenuCursorRects[WifiSetupApp_HasOption(1)][gWifiSetupMethodMenu.selected].bottom);
            return;
        }
    }
    if (WifiSetupInput_IsKeyPressed(PAD_BUTTON_A)) {
        WifiSetupButtonBar_SelectIfNone(1);
        return;
    }
    if (WifiSetupInput_IsKeyPressed(PAD_BUTTON_B)) {
        WifiSetupButtonBar_SelectIfNone(0);
        return;
    }
    if (WifiSetupInput_IsKeyRepeated(PAD_KEY_UP)) {
        WifiSetupMethodMenu_MoveCursor(WIFI_SETUP_CURSOR_UP);
        return;
    }
    if (WifiSetupInput_IsKeyRepeated(PAD_KEY_DOWN)) {
        WifiSetupMethodMenu_MoveCursor(WIFI_SETUP_CURSOR_DOWN);
        return;
    }
    if (WifiSetupInput_IsKeyRepeated(PAD_KEY_LEFT)) {
        WifiSetupMethodMenu_MoveCursor(WIFI_SETUP_CURSOR_LEFT);
        return;
    }
    if (WifiSetupInput_IsKeyRepeated(PAD_KEY_RIGHT)) {
        WifiSetupMethodMenu_MoveCursor(WIFI_SETUP_CURSOR_RIGHT);
    }
}

static void WifiSetupMethodMenu_Update(void) {
}

static void WifiSetupMethodMenu_CheckButtons(void) {
    switch (WifiSetupButtonBar_GetSelected()) {
    case 0:
        WifiSetupSound_Play(7);
        break;
    case 1:
        WifiSetupSound_Play(6);
        WifiSetupMethodMenu_HighlightSelection();
        gWifiSetupMethodMenu.confirmed = TRUE;
        break;
    default:
        return;
    }
    WifiSetupApp_SetStateFunc(WifiSetupMethodMenu_Exit);
}

static void WifiSetupMethodMenu_Exit(void) {
    WifiSetupButtonBar_Lock();
    WifiSetupFade_StartDelay(8);
    WifiSetupApp_SetStateFunc(WifiSetupMethodMenu_WaitFadeOut);
}

static void WifiSetupMethodMenu_WaitFadeOut(void) {
    if (WifiSetupFade_IsActive(WIFI_SETUP_SCREEN_SUB)) {
        return;
    }
    if (gWifiSetupMethodMenu.confirmed) {
        WifiSetupButtonBar_Close();
    }
    WifiSetupFade_Start(WIFI_SETUP_FADE_OUT_TO_WHITE, WIFI_SETUP_SCREEN_SUB, GX_BLEND_PLANEMASK_BG0, 8);
    WifiSetupFade_Start(WIFI_SETUP_FADE_OUT_TO_WHITE, WIFI_SETUP_SCREEN_MAIN, GX_BLEND_PLANEMASK_BG2 | GX_BLEND_PLANEMASK_OBJ, 8);
    WifiSetupApp_SetStateFunc(WifiSetupMethodMenu_End);
}

static void WifiSetupMethodMenu_End(void) {
    if (WifiSetupFade_IsActive(WIFI_SETUP_SCREEN_SUB)) {
        return;
    }
    if (WifiSetupFade_IsActive(WIFI_SETUP_SCREEN_MAIN)) {
        return;
    }
    if (!WifiSetupButtonBar_IsNotClosing()) {
        return;
    }
    WifiSetupCursor_Hide();
    WifiSetupMessage_Hide();
    WifiSetupFile_Free(gWifiSetupMethodMenu.graphics);
    WifiSetupDisplay_HidePlanes(WIFI_SETUP_SCREEN_SUB, GX_PLANEMASK_BG0);
    WifiSetupDisplay_HidePlanes(WIFI_SETUP_SCREEN_MAIN, GX_PLANEMASK_BG2 | GX_PLANEMASK_OBJ);
    if (!gWifiSetupMethodMenu.confirmed) {
        WifiSetupApp_SetTransition(WIFI_SETUP_BANNER_CHANGE, WIFI_SETUP_BUTTON_BAR_KEEP);
        WifiSetupApp_SetStateFunc(WifiSetupConnectionList_Init);
        return;
    }
    switch (gWifiSetupMethodMenu.selected) {
    case WIFI_SETUP_METHOD_MENU_AP_SCAN:
        WifiSetupApp_SetTransition(WIFI_SETUP_BANNER_CHANGE, WIFI_SETUP_BUTTON_BAR_CREATE);
        WifiSetupApp_SetStateFunc(WifiSetupApScanScreen_Init);
        break;
    case WIFI_SETUP_METHOD_MENU_CLIENT:
        WifiSetupApp_SetTransition(WIFI_SETUP_BANNER_CHANGE, WIFI_SETUP_BUTTON_BAR_CREATE);
        WifiSetupApp_SetStateFunc(WifiSetupAoss_Init);
        break;
    case WIFI_SETUP_METHOD_MENU_AUTO:
        WifiSetupApp_SetTransition(WIFI_SETUP_BANNER_CHANGE, WIFI_SETUP_BUTTON_BAR_CREATE);
        WifiSetupApp_SetStateFunc(WifiSetupAutoSearch_Init);
        break;
    case WIFI_SETUP_METHOD_MENU_MANUAL:
        WifiSetupApp_SetTransition(WIFI_SETUP_BANNER_CHANGE, WIFI_SETUP_BUTTON_BAR_KEEP);
        WifiSetupApp_SetScreenArgs(0, 0);
        WifiSetupSettings_SetFromMenu(TRUE);
        WifiSetupApp_SetStateFunc(WifiSetupSettings_Init);
        break;
    }
}

static void WifiSetupMethodMenu_MoveCursor(int dir) {
    s8 cur = gWifiSetupMethodMenu.selected;
    s8 next = gWifiSetupMethodMenuCursorMoves[WifiSetupApp_HasOption(1)][cur][dir];
    if (next == -1) {
        return;
    }
    if (next == 0) {
        gWifiSetupMethodMenu.lastOption = cur;
    }
    if (next == -2) {
        gWifiSetupMethodMenu.selected = gWifiSetupMethodMenu.lastOption;
    } else {
        gWifiSetupMethodMenu.selected = next;
    }
    WifiSetupSound_Play(8);
    WifiSetupCursor_ShowCorners(gWifiSetupMethodMenuCursorRects[WifiSetupApp_HasOption(1)][gWifiSetupMethodMenu.selected].left, gWifiSetupMethodMenuCursorRects[WifiSetupApp_HasOption(1)][gWifiSetupMethodMenu.selected].right, gWifiSetupMethodMenuCursorRects[WifiSetupApp_HasOption(1)][gWifiSetupMethodMenu.selected].top, gWifiSetupMethodMenuCursorRects[WifiSetupApp_HasOption(1)][gWifiSetupMethodMenu.selected].bottom);
}

static void WifiSetupMethodMenu_HighlightSelection(void) {
    WifiSetupPaletteRows rows = gWifiSetupMethodMenuPaletteRows;
    WifiSetupPalette_LoadRow(gWifiSetupMethodMenu.graphics, rows.rows[gWifiSetupMethodMenu.selected], rows.rows[gWifiSetupMethodMenu.selected]);
}

void WifiSetupConnectionTest_Init(void) {
    int mode;
    gWifiSetupConnectionTestPassed = FALSE;
    WifiSetupConnectionTest_LoadGraphics();
    WifiSetupApp_GetScreenArgs(0, &mode);
    if (mode == WIFI_SETUP_TEST_FROM_SETTINGS) {
        WifiSetupMessage_Show(0x31, -1, 0);
    }
    WifiSetupBanner_Show(2);
    if (mode == WIFI_SETUP_TEST_FROM_SETTINGS) {
        WifiSetupBackground_LoadSlotHeader();
    }
    WifiSetup_PrintMessage(0x2C);
    WifiSetupBusyIcon_Create(0);
    WifiSetupConnectionTest_Start();
    WifiSetupSignalIcon_Create(0);
    WifiSetupSound_Play(0xC);
    WifiSetupApp_SetStateFunc(WifiSetupConnectionTest_FadeIn);
}

static void WifiSetupConnectionTest_LoadGraphics(void) {
    WifiSetup_LoadGraphics(gWifiSetupConnectionTestJbBgStep3NcgPath, GX_LoadBG2Char);
    WifiSetup_LoadGraphics(gWifiSetupConnectionTestYbBgStep3NclPath, GX_LoadBGPltt);
    WifiSetup_LoadGraphics(gWifiSetupConnectionTestXb4MultiNscPath, GX_LoadBG2Scr);
    G2S_SetBG0Priority(3);
    G2S_SetBG1Priority(3);
    G2_SetBG0Priority(3);
    G2_SetBG1Priority(3);
    G2_SetBG2Priority(3);
}

static void WifiSetupConnectionTest_Start(void) {
    int mode;
    WifiSetupConnectionTestParams param;
    WifiSetupConnection *connection = WifiSetupConnections_GetEdit();
    MI_CpuCopy32(&gWifiSetupConnectionTestParams, &param, sizeof(param));
    WifiSetupApp_GetScreenArgs(0, &mode);
    if (mode == WIFI_SETUP_TEST_USB_CONNECTOR) {
        param.slot = 4;
    } else {
        param.slot = connection->index + 1;
    }
    if (!DWC_AC_Create(&param)) {
        OS_Terminate();
    }
    if (mode == WIFI_SETUP_TEST_FROM_SETTINGS) {
        DWCi_AC_SetUserProfile(connection->index, connection);
    }
    WifiSetupTask_Create(WIFI_SETUP_TASK_QUEUE_MAIN, WifiSetupConnectionTest_PollTask, NULL, 120);
}

static void WifiSetupConnectionTest_FadeIn(void) {
    int mode;
    WifiSetupFade_Start(WIFI_SETUP_FADE_IN_FROM_WHITE, WIFI_SETUP_SCREEN_MAIN, GX_BLEND_PLANEMASK_BG0 | GX_BLEND_PLANEMASK_BG2 | GX_BLEND_PLANEMASK_OBJ, 8);
    WifiSetupDisplay_ShowPlanes(WIFI_SETUP_SCREEN_MAIN, GX_PLANEMASK_BG0 | GX_PLANEMASK_BG2 | GX_PLANEMASK_OBJ);
    WifiSetupApp_GetScreenArgs(0, &mode);
    if (mode == WIFI_SETUP_TEST_FROM_SETTINGS) {
        WifiSetupFade_Start(WIFI_SETUP_FADE_IN_FROM_WHITE, WIFI_SETUP_SCREEN_SUB, GX_BLEND_PLANEMASK_BG0, 8);
        WifiSetupDisplay_ShowPlanes(WIFI_SETUP_SCREEN_SUB, GX_PLANEMASK_BG0);
    }
    WifiSetupApp_SetStateFunc(WifiSetupConnectionTest_WaitFadeIn);
}

static void WifiSetupConnectionTest_WaitFadeIn(void) {
    if (WifiSetupFade_IsActive(WIFI_SETUP_SCREEN_SUB)) {
        return;
    }
    if (WifiSetupFade_IsActive(WIFI_SETUP_SCREEN_MAIN)) {
        return;
    }
    WifiSetupApp_SetStateFunc(WifiSetupConnectionTest_Main);
}

static void WifiSetupConnectionTest_Main(void) {
    WifiSetupConnectionTest_HandleInput();
    WifiSetupConnectionTest_Update();
    WifiSetupConnectionTest_CheckButtons();
}

static void WifiSetupConnectionTest_HandleInput(void) {
}

static void WifiSetupConnectionTest_Update(void) {
}

static void WifiSetupConnectionTest_CheckButtons(void) {
}

static void WifiSetupConnectionTest_FadeOut(void) {
    WifiSetupFade_Start(WIFI_SETUP_FADE_OUT_TO_WHITE, WIFI_SETUP_SCREEN_MAIN, GX_BLEND_PLANEMASK_BG0 | GX_BLEND_PLANEMASK_BG2 | GX_BLEND_PLANEMASK_OBJ, 8);
    WifiSetupApp_SetStateFunc(WifiSetupConnectionTest_WaitFadeOut);
}

static void WifiSetupConnectionTest_WaitFadeOut(void) {
    if (WifiSetupFade_IsActive(WIFI_SETUP_SCREEN_MAIN)) {
        return;
    }
    WifiSetupApp_SetStateFunc(WifiSetupConnectionTest_End);
}

static void WifiSetupConnectionTest_End(void) {
    WifiSetupConnections *connections = WifiSetupConnections_Get();
    if (!DWC_AC_Destroy()) {
        return;
    }
    MI_CpuCopy8(DWCi_BACKUPlGetWifi(), connections->pages[0].tail.page.info, sizeof(connections->pages[0].tail.page.info));
    MI_CpuCopy8(DWCi_BACKUPlGetWifi(), connections->pages[1].tail.page.info, sizeof(connections->pages[1].tail.page.info));
    WifiSetupBusyIcon_Destroy();
    WifiSetupText_FreeBgCanvas(WIFI_SETUP_SCREEN_MAIN);
    WifiSetupDisplay_HidePlanes(WIFI_SETUP_SCREEN_MAIN, GX_PLANEMASK_BG0 | GX_PLANEMASK_BG2 | GX_PLANEMASK_OBJ);
    if (!gWifiSetupConnectionTestPassed) {
        WifiSetupApp_SetTransition(WIFI_SETUP_BANNER_KEEP, WIFI_SETUP_BUTTON_BAR_CREATE);
        WifiSetupApp_SetStateFunc(WifiSetupErrorScreen_Init);
    } else {
        WifiSetupApp_SetTransition(WIFI_SETUP_BANNER_KEEP, WIFI_SETUP_BUTTON_BAR_CREATE);
        WifiSetupApp_SetStateFunc(WifiSetupConnectionOk_Init);
    }
}

static void WifiSetupConnectionTest_PollTask(WifiSetupTask *task, void *arg) {
    int result = DWC_AC_Process();
    if (result == 0) {
        return;
    }
    WifiSetupSignalIcon_Destroy();
    WifiSetupSound_Stop();
    if (result > 0) {
        gWifiSetupConnectionTestPassed = TRUE;
        WifiSetupSound_Play(0x11);
    } else {
        WifiSetupErrorScreen_SetCode(DWC_AC_GetStatus());
        WifiSetupSound_Play(0x12);
    }
    WifiSetupApp_SetStateFunc(WifiSetupConnectionTest_FadeOut);
    WifiSetupTask_DestroyLater(WIFI_SETUP_TASK_QUEUE_MAIN, task);
}

#pragma force_active on

void *WifiSetupConnectionTest_Alloc(void *arg, u32 size) {
    return WifiSetupHeap_AllocZeroed(size, 0x20);
}

void WifiSetupConnectionTest_Free(void *arg, void *ptr) {
    WifiSetupHeap_Free(ptr);
}

#pragma force_active reset

static void WifiSetupConnectionOk_Init(void) {
    gWifiSetupConnectionOkTimer = 0;
    WifiSetupConnectionOk_LoadGraphics();
    WifiSetup_PrintMessage(0x2D);
    WifiSetupApp_SetStateFunc(WifiSetupConnectionOk_FadeIn);
}

static void WifiSetupConnectionOk_LoadGraphics(void) {
    WifiSetup_LoadGraphics(gWifiSetupConnectionOkXb4MultiNscPath, GX_LoadBG2Scr);
    G2S_SetBG0Priority(3);
    G2S_SetBG1Priority(3);
    G2_SetBG1Priority(3);
    G2_SetBG2Priority(3);
}

static void WifiSetupConnectionOk_FadeIn(void) {
    WifiSetupFade_Start(WIFI_SETUP_FADE_IN_FROM_WHITE, WIFI_SETUP_SCREEN_MAIN, GX_BLEND_PLANEMASK_BG0 | GX_BLEND_PLANEMASK_BG2 | GX_BLEND_PLANEMASK_OBJ, 8);
    WifiSetupDisplay_ShowPlanes(WIFI_SETUP_SCREEN_MAIN, GX_PLANEMASK_BG0 | GX_PLANEMASK_BG2 | GX_PLANEMASK_OBJ);
    WifiSetupApp_SetStateFunc(WifiSetupConnectionOk_WaitFadeIn);
}

static void WifiSetupConnectionOk_WaitFadeIn(void) {
    if (WifiSetupFade_IsActive(WIFI_SETUP_SCREEN_MAIN)) {
        return;
    }
    WifiSetupApp_SetStateFunc(WifiSetupConnectionOk_Main);
}

static void WifiSetupConnectionOk_Main(void) {
    WifiSetupConnectionOk_UpdateTimer();
    WifiSetupConnectionOk_Update();
}

static void WifiSetupConnectionOk_Update(void) {
}

static void WifiSetupConnectionOk_FadeOut(void) {
    int mode;
    WifiSetupApp_GetScreenArgs(0, &mode);
    if (mode != WIFI_SETUP_TEST_FROM_SETTINGS) {
        WifiSetupBanner_Close();
    }
    WifiSetupFade_Start(WIFI_SETUP_FADE_OUT_TO_WHITE, WIFI_SETUP_SCREEN_SUB, GX_BLEND_PLANEMASK_BG0, 8);
    WifiSetupFade_Start(WIFI_SETUP_FADE_OUT_TO_WHITE, WIFI_SETUP_SCREEN_MAIN, GX_BLEND_PLANEMASK_BG0 | GX_BLEND_PLANEMASK_BG2 | GX_BLEND_PLANEMASK_OBJ, 8);
    WifiSetupApp_SetStateFunc(WifiSetupConnectionOk_End);
}

static void WifiSetupConnectionOk_End(void) {
    int mode;
    if (WifiSetupFade_IsActive(WIFI_SETUP_SCREEN_SUB)) {
        return;
    }
    if (WifiSetupFade_IsActive(WIFI_SETUP_SCREEN_MAIN)) {
        return;
    }
    if (!WifiSetupBanner_IsNotClosing()) {
        return;
    }
    WifiSetupText_FreeBgCanvas(WIFI_SETUP_SCREEN_MAIN);
    WifiSetupMessage_Hide();
    WifiSetupDisplay_HidePlanes(WIFI_SETUP_SCREEN_SUB, GX_PLANEMASK_BG0);
    WifiSetupDisplay_HidePlanes(WIFI_SETUP_SCREEN_MAIN, GX_PLANEMASK_BG0 | GX_PLANEMASK_BG2 | GX_PLANEMASK_OBJ);
    WifiSetupApp_SetTransition(WIFI_SETUP_BANNER_CHANGE, WIFI_SETUP_BUTTON_BAR_CREATE);
    WifiSetupApp_GetScreenArgs(0, &mode);
    if (mode == WIFI_SETUP_TEST_FROM_SETTINGS) {
        WifiSetupApp_SetScreenArgs(0, 0);
        WifiSetupApp_SetStateFunc(WifiSetupSettings_Init);
        return;
    }
    WifiSetupApp_SetStateFunc(WifiSetupTopMenu_Init);
}

static void WifiSetupConnectionOk_UpdateTimer(void) {
    int mode;
    if (++gWifiSetupConnectionOkTimer < 0xB4) {
        return;
    }
    WifiSetupApp_GetScreenArgs(0, &mode);
    switch (WifiSetupApp_GetKind()) {
    case WIFI_SETUP_KIND_TOP_MENU:
        break;
    case WIFI_SETUP_KIND_CONNECTION_LIST:
        if (mode != WIFI_SETUP_TEST_FROM_SETTINGS) {
            WifiSetupApp_SetStateFunc(WifiSetupScreens_StartQuit);
            return;
        }
        break;
    }
    WifiSetupApp_SetStateFunc(WifiSetupConnectionOk_FadeOut);
}

void WifiSetupTestPrompt_Init(void) {
    int mode;
    WifiSetupApScan_FreeWork();
    WifiSetupApp_GetScreenArgs(0, &mode);
    WifiSetupTestPrompt_LoadGraphics();
    WifiSetupMessage_Show(0x31, -1, 0);
    if (mode != WIFI_SETUP_TEST_USB_CONNECTOR) {
        WifiSetupBackground_LoadSlotHeader();
    }
    if (mode == WIFI_SETUP_TEST_NEW_SETTINGS) {
        WifiSetupConnections_SaveEdit();
    }
    WifiSetupApp_SetStateFunc(WifiSetupTestPrompt_FadeIn);
}

static void WifiSetupTestPrompt_LoadGraphics(void) {
    WifiSetup_LoadGraphics(gWifiSetupTestPromptXb4NoneNscPath, GX_LoadBG2Scr);
    G2S_SetBG0Priority(3);
    G2S_SetBG1Priority(3);
    G2_SetBG1Priority(3);
    G2_SetBG2Priority(3);
}

static void WifiSetupTestPrompt_FadeIn(void) {
    WifiSetupFade_Start(WIFI_SETUP_FADE_IN_FROM_WHITE, WIFI_SETUP_SCREEN_SUB, GX_BLEND_PLANEMASK_BG0, 8);
    WifiSetupFade_Start(WIFI_SETUP_FADE_IN_FROM_WHITE, WIFI_SETUP_SCREEN_MAIN, GX_BLEND_PLANEMASK_BG2 | GX_BLEND_PLANEMASK_OBJ, 8);
    WifiSetupDisplay_ShowPlanes(WIFI_SETUP_SCREEN_SUB, GX_PLANEMASK_BG0);
    WifiSetupDisplay_ShowPlanes(WIFI_SETUP_SCREEN_MAIN, GX_PLANEMASK_BG2 | GX_PLANEMASK_OBJ);
    WifiSetupApp_SetStateFunc(WifiSetupTestPrompt_WaitFadeIn);
}

static void WifiSetupTestPrompt_WaitFadeIn(void) {
    WifiSetupTestPromptMessages prompts = gWifiSetupTestPromptMessages;
    int mode;
    if (WifiSetupFade_IsActive(WIFI_SETUP_SCREEN_SUB)) {
        return;
    }
    if (WifiSetupFade_IsActive(WIFI_SETUP_SCREEN_MAIN)) {
        return;
    }
    WifiSetupApp_GetScreenArgs(0, &mode);
    WifiSetupDialog_Open(prompts.messages[mode], 1, 1, -1, 0);
    WifiSetupApp_SetStateFunc(WifiSetupTestPrompt_Main);
}

static void WifiSetupTestPrompt_Main(void) {
    WifiSetupTestPrompt_HandleInput();
    WifiSetupTestPrompt_Update();
    if (WifiSetupDialog_GetSelected()) {
        return;
    }
    WifiSetupSound_Play(6);
    WifiSetupDialog_Close();
    WifiSetupSound_Play(6);
    WifiSetupApp_SetStateFunc(WifiSetupTestPrompt_WaitDialogClosed);
}

static void WifiSetupTestPrompt_HandleInput(void) {
}

static void WifiSetupTestPrompt_Update(void) {
}

static void WifiSetupTestPrompt_WaitDialogClosed(void) {
    if (WifiSetupDialog_IsOpen()) {
        return;
    }
    WifiSetupFade_Start(WIFI_SETUP_FADE_OUT_TO_WHITE, WIFI_SETUP_SCREEN_MAIN, GX_BLEND_PLANEMASK_BG2 | GX_BLEND_PLANEMASK_OBJ, 8);
    WifiSetupApp_SetStateFunc(WifiSetupTestPrompt_End);
}

static void WifiSetupTestPrompt_End(void) {
    if (WifiSetupFade_IsActive(WIFI_SETUP_SCREEN_MAIN)) {
        return;
    }
    WifiSetupDisplay_HidePlanes(WIFI_SETUP_SCREEN_MAIN, GX_PLANEMASK_BG2 | GX_PLANEMASK_OBJ);
    WifiSetupApp_SetTransition(WIFI_SETUP_BANNER_KEEP, WIFI_SETUP_BUTTON_BAR_CREATE);
    WifiSetupApp_SetStateFunc(WifiSetupConnectionTest_Init);
}

void WifiSetupUsbConnectorDone_Init(void) {
    gWifiSetupUsbConnectorDoneTimer = 0;
    WifiSetupUsbConnectorDone_LoadGraphics();
    WifiSetupBackground_LoadHeader(8);
    WifiSetup_PrintMessage(0x29);
    WifiSetupSound_Play(0x10);
    WifiSetupApp_SetStateFunc(WifiSetupUsbConnectorDone_FadeIn);
}

static void WifiSetupUsbConnectorDone_LoadGraphics(void) {
    WifiSetup_LoadGraphics(gWifiSetupUsbConnectorDoneXb4MultiNscPath, GX_LoadBG2Scr);
    G2S_SetBG0Priority(3);
    G2S_SetBG1Priority(3);
    G2_SetBG0Priority(3);
    G2_SetBG1Priority(3);
    G2_SetBG2Priority(3);
}

static void WifiSetupUsbConnectorDone_FadeIn(void) {
    WifiSetupFade_Start(WIFI_SETUP_FADE_IN_FROM_WHITE, WIFI_SETUP_SCREEN_MAIN, GX_BLEND_PLANEMASK_BG0 | GX_BLEND_PLANEMASK_BG2 | GX_BLEND_PLANEMASK_OBJ, 8);
    WifiSetupDisplay_ShowPlanes(WIFI_SETUP_SCREEN_MAIN, GX_PLANEMASK_BG0 | GX_PLANEMASK_BG2 | GX_PLANEMASK_OBJ);
    WifiSetupApp_SetStateFunc(WifiSetupUsbConnectorDone_WaitFadeIn);
}

static void WifiSetupUsbConnectorDone_WaitFadeIn(void) {
    if (WifiSetupFade_IsActive(WIFI_SETUP_SCREEN_MAIN)) {
        return;
    }
    WifiSetupApp_SetStateFunc(WifiSetupUsbConnectorDone_Main);
}

static void WifiSetupUsbConnectorDone_Main(void) {
    WifiSetupUsbConnectorDone_UpdateTimer();
    WifiSetupUsbConnectorDone_Update();
}

static void WifiSetupUsbConnectorDone_Update(void) {
}

static void WifiSetupUsbConnectorDone_FadeOut(void) {
    WifiSetupFade_Start(WIFI_SETUP_FADE_OUT_TO_WHITE, WIFI_SETUP_SCREEN_SUB, GX_BLEND_PLANEMASK_BG0, 8);
    WifiSetupFade_Start(WIFI_SETUP_FADE_OUT_TO_WHITE, WIFI_SETUP_SCREEN_MAIN, GX_BLEND_PLANEMASK_BG0 | GX_BLEND_PLANEMASK_BG2 | GX_BLEND_PLANEMASK_OBJ, 8);
    WifiSetupApp_SetStateFunc(WifiSetupUsbConnectorDone_End);
}

static void WifiSetupUsbConnectorDone_End(void) {
    if (WifiSetupFade_IsActive(WIFI_SETUP_SCREEN_SUB)) {
        return;
    }
    if (WifiSetupFade_IsActive(WIFI_SETUP_SCREEN_MAIN)) {
        return;
    }
    WifiSetupText_FreeBgCanvas(WIFI_SETUP_SCREEN_MAIN);
    WifiSetupMessage_Hide();
    WifiSetupDisplay_HidePlanes(WIFI_SETUP_SCREEN_SUB, GX_PLANEMASK_BG0);
    WifiSetupDisplay_HidePlanes(WIFI_SETUP_SCREEN_MAIN, GX_PLANEMASK_BG0 | GX_PLANEMASK_BG2 | GX_PLANEMASK_OBJ);
    WifiSetupApp_SetTransition(WIFI_SETUP_BANNER_KEEP, WIFI_SETUP_BUTTON_BAR_KEEP);
    WifiSetupApp_SetScreenArgs(0, WIFI_SETUP_TEST_USB_CONNECTOR);
    WifiSetupApp_SetStateFunc(WifiSetupTestPrompt_Init);
}

static void WifiSetupUsbConnectorDone_UpdateTimer(void) {
    if (++gWifiSetupUsbConnectorDoneTimer < 0x78) {
        return;
    }
    WifiSetupApp_SetStateFunc(WifiSetupUsbConnectorDone_FadeOut);
}

void WifiSetupUsbConnectorIntro_Init(void) {
    gWifiSetupUsbConnectorIntroNext = FALSE;
    WifiSetupUsbConnectorIntro_LoadGraphics();
    WifiSetupBackground_LoadHeader(8);
    WifiSetupMessage_Show(0x38, -1, 0);
    WifiSetupBanner_Show(1);
    WifiSetup_PrintMessage(0x27);
    WifiSetupApp_SetStateFunc(WifiSetupUsbConnectorIntro_FadeIn);
}

static void WifiSetupUsbConnectorIntro_LoadGraphics(void) {
    WifiSetup_LoadGraphics(gWifiSetupUsbConnectorIntroJbBgStep2NcgPath, GX_LoadBG2Char);
    WifiSetup_LoadGraphics(gWifiSetupUsbConnectorIntroYbBgStep2NclPath, GX_LoadBGPltt);
    WifiSetup_LoadGraphics(gWifiSetupUsbConnectorIntroXb3MultiNscPath, GX_LoadBG2Scr);
    G2S_SetBG0Priority(3);
    G2S_SetBG1Priority(3);
    G2_SetBG0Priority(3);
    G2_SetBG1Priority(3);
    G2_SetBG2Priority(3);
}

static void WifiSetupUsbConnectorIntro_FadeIn(void) {
    WifiSetupFade_Start(WIFI_SETUP_FADE_IN_FROM_WHITE, WIFI_SETUP_SCREEN_SUB, GX_BLEND_PLANEMASK_BG0, 8);
    WifiSetupFade_Start(WIFI_SETUP_FADE_IN_FROM_WHITE, WIFI_SETUP_SCREEN_MAIN, GX_BLEND_PLANEMASK_BG0 | GX_BLEND_PLANEMASK_BG2 | GX_BLEND_PLANEMASK_OBJ, 8);
    WifiSetupDisplay_ShowPlanes(WIFI_SETUP_SCREEN_SUB, GX_PLANEMASK_BG0);
    WifiSetupDisplay_ShowPlanes(WIFI_SETUP_SCREEN_MAIN, GX_PLANEMASK_BG0 | GX_PLANEMASK_BG2 | GX_PLANEMASK_OBJ);
    WifiSetupApp_SetStateFunc(WifiSetupUsbConnectorIntro_WaitFadeIn);
}

static void WifiSetupUsbConnectorIntro_WaitFadeIn(void) {
    if (WifiSetupFade_IsActive(WIFI_SETUP_SCREEN_SUB)) {
        return;
    }
    if (WifiSetupFade_IsActive(WIFI_SETUP_SCREEN_MAIN)) {
        return;
    }
    WifiSetupButtonBar_Show(6);
    WifiSetupApp_SetStateFunc(WifiSetupUsbConnectorIntro_WaitButtonBar);
}

static void WifiSetupUsbConnectorIntro_WaitButtonBar(void) {
    if (WifiSetupButtonBar_GetSelected() == WIFI_SETUP_SELECTED_NOT_SHOWN) {
        return;
    }
    WifiSetupButtonBar_Unlock();
    WifiSetupApp_SetStateFunc(WifiSetupUsbConnectorIntro_Main);
}

static void WifiSetupUsbConnectorIntro_Main(void) {
    WifiSetupUsbConnectorIntro_HandleInput();
    WifiSetupUsbConnectorIntro_Update();
    WifiSetupUsbConnectorIntro_CheckButtons();
}

static void WifiSetupUsbConnectorIntro_HandleInput(void) {
    if (WifiSetupInput_IsKeyPressed(PAD_BUTTON_A)) {
        WifiSetupButtonBar_SelectIfNone(1);
    }
    if (WifiSetupInput_IsKeyPressed(PAD_BUTTON_B)) {
        WifiSetupButtonBar_SelectIfNone(0);
    }
}

static void WifiSetupUsbConnectorIntro_Update(void) {
}

static void WifiSetupUsbConnectorIntro_CheckButtons(void) {
    switch (WifiSetupButtonBar_GetSelected()) {
    case 0:
        WifiSetupSound_Play(7);
        break;
    case 1:
        WifiSetupSound_Play(6);
        gWifiSetupUsbConnectorIntroNext = TRUE;
        break;
    default:
        return;
    }
    WifiSetupApp_SetStateFunc(WifiSetupUsbConnectorIntro_Exit);
}

static void WifiSetupUsbConnectorIntro_Exit(void) {
    WifiSetupButtonBar_Lock();
    WifiSetupFade_StartDelay(8);
    WifiSetupApp_SetStateFunc(WifiSetupUsbConnectorIntro_WaitFadeOut);
}

static void WifiSetupUsbConnectorIntro_WaitFadeOut(void) {
    if (WifiSetupFade_IsActive(WIFI_SETUP_SCREEN_SUB)) {
        return;
    }
    WifiSetupButtonBar_Close();
    if (!gWifiSetupUsbConnectorIntroNext) {
        WifiSetupFade_Start(WIFI_SETUP_FADE_OUT_TO_WHITE, WIFI_SETUP_SCREEN_SUB, GX_BLEND_PLANEMASK_BG0, 8);
    }
    WifiSetupFade_Start(WIFI_SETUP_FADE_OUT_TO_WHITE, WIFI_SETUP_SCREEN_MAIN, GX_BLEND_PLANEMASK_BG0 | GX_BLEND_PLANEMASK_BG2 | GX_BLEND_PLANEMASK_OBJ, 8);
    WifiSetupApp_SetStateFunc(WifiSetupUsbConnectorIntro_End);
}

static void WifiSetupUsbConnectorIntro_End(void) {
    if (WifiSetupFade_IsActive(WIFI_SETUP_SCREEN_MAIN)) {
        return;
    }
    if (!gWifiSetupUsbConnectorIntroNext && WifiSetupFade_IsActive(WIFI_SETUP_SCREEN_SUB)) {
        return;
    }
    if (!WifiSetupButtonBar_IsNotClosing()) {
        return;
    }
    WifiSetupText_FreeBgCanvas(WIFI_SETUP_SCREEN_MAIN);
    if (!gWifiSetupUsbConnectorIntroNext) {
        WifiSetupMessage_Hide();
        WifiSetupDisplay_HidePlanes(WIFI_SETUP_SCREEN_SUB, GX_PLANEMASK_BG0);
    }
    WifiSetupDisplay_HidePlanes(WIFI_SETUP_SCREEN_MAIN, GX_PLANEMASK_BG0 | GX_PLANEMASK_BG2 | GX_PLANEMASK_OBJ);
    if (!gWifiSetupUsbConnectorIntroNext) {
        WifiSetupApp_SetTransition(WIFI_SETUP_BANNER_CHANGE, WIFI_SETUP_BUTTON_BAR_CREATE);
        WifiSetupApp_SetStateFunc(WifiSetupConnectionList_Init);
    } else {
        WifiSetupApp_SetTransition(WIFI_SETUP_BANNER_CHANGE, WIFI_SETUP_BUTTON_BAR_CREATE);
        WifiSetupApp_SetStateFunc(WifiSetupUsbConnector_Init);
    }
}

BOOL WifiSetupUsbConnector_IsLidClosed(void) {
    return PAD_DetectFold() ? TRUE : FALSE;
}

static void WifiSetupUsbConnector_Init(void) {
    u16 name[11];
    OSOwnerInfo info;
    gWifiSetupUsbConnectorExit = 0;
    WifiSetupUsbConnector_LoadGraphics();
    WifiSetupBackground_LoadHeader(8);
    WifiSetupBanner_Show(2);
    OS_GetOwnerInfo(&info);
    MIi_CpuClear16(0, name, sizeof(name));
    MIi_CpuCopy16(info.nickName, name, info.nickNameLength * 2);
    WifiSetup_PrintMessageWithText(name, 0x28);
    WifiSetupBusyIcon_Create(0);
    WifiSetupUsbScan_Start(WifiSetupUsbConnector_ScanCallback);
    WifiSetupSound_Play(0xB);
    WifiSetupApp_SetStateFunc(WifiSetupUsbConnector_Start);
}

static void WifiSetupUsbConnector_LoadGraphics(void) {
    WifiSetup_LoadGraphics(gWifiSetupUsbConnectorJbBgStep3NcgPath, GX_LoadBG2Char);
    WifiSetup_LoadGraphics(gWifiSetupUsbConnectorYbBgStep3NclPath, GX_LoadBGPltt);
    WifiSetup_LoadGraphics(gWifiSetupUsbConnectorJb4UsbNscPath, GX_LoadBG2Scr);
    G2S_SetBG0Priority(3);
    G2S_SetBG1Priority(3);
    G2_SetBG0Priority(3);
    G2_SetBG1Priority(3);
    G2_SetBG2Priority(3);
}
