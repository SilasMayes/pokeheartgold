#include "wifi_setup/wifi_setup_address_entry.h"

#include "global.h"

#include "dwc/dwc_bm_internal.h"
#include "wifi_setup/wifi_setup_access_points.h"
#include "wifi_setup/wifi_setup_app.h"
#include "wifi_setup/wifi_setup_keypad.h"
#include "wifi_setup/wifi_setup_local_wireless.h"
#include "wifi_setup/wifi_setup_settings.h"
#include "wifi_setup/wifi_setup_ui.h"
#include "wifi_setup/wifi_setup_ui_parts.h"

#include <nitro/code32.h>

// Address entry screen: the digits are typed on the numeric keypad; OK checks the address and asks for
// confirmation before it is stored.

// largest value of a field ("255")
typedef struct WifiSetupFieldLimit {
    u8 digits[4];
} WifiSetupFieldLimit;

extern void *gWifiSetupTextEntry[];

// Screen layout: starts with the field limit; the u16 at index 7 and 8 are the position of the digits.
extern const WifiSetupFieldLimit gWifiSetupAddressLayout;

extern long atol(const char *);

static void WifiSetupAddressEntry_WaitKeypad(void);
static void WifiSetupAddressEntry_Main(void);
static void WifiSetupAddressEntry_HandleInput(void);
static int WifiSetupAddressEntry_IsFieldAtLeast(int limit);
static void WifiSetupAddressEntry_Update(void);
static void WifiSetupAddressEntry_StartClose(void);
static void WifiSetupAddressEntry_CloseKeypad(void);
static void WifiSetupAddressEntry_WaitKeypadClosed(void);
static void WifiSetupAddressEntry_Exit(void);
static inline void DrawDigit(WifiSetupCanvas *canvas, u16 x, volatile WifiSetupTextBox *rect, u16 *text);
static inline void SetOamPos(u32 *attr01, int x, int y);
static void WifiSetupAddressEntry_WaitConfirm(void);
static void WifiSetupAddressEntry_FinishConfirm(void);
static void WifiSetupAddressEntry_PadFields(void);
static int WifiSetupAddressEntry_IsValid(void);

void WifiSetupAddressEntry_LoadGraphics(void) {
    WifiSetup_LoadGraphics(gWifiSetupAddressEntryYbObjKbNclPath, GX_LoadOBJPltt);
    WifiSetup_LoadGraphics(gWifiSetupAddressEntryJbBgStep3NcgPath, GX_LoadBG2Char);
    WifiSetup_LoadGraphics(gWifiSetupAddressEntryYbBgStep3NclPath, GX_LoadBGPltt);
    WifiSetup_LoadGraphics(gWifiSetupAddressEntryXb4EditAddrNscPath, GX_LoadBG2Scr);
    G2S_SetBG0Priority(3);
    G2S_SetBG1Priority(3);
    G2_SetBG0Priority(2);
    G2_SetBG1Priority(3);
    G2_SetBG2Priority(3);
}

void WifiSetupAddressEntry_FadeIn(void) {
    WifiSetupFade_Start(WIFI_SETUP_FADE_IN_FROM_WHITE, WIFI_SETUP_SCREEN_SUB, GX_BLEND_PLANEMASK_BG0, 8);
    WifiSetupFade_Start(WIFI_SETUP_FADE_IN_FROM_WHITE, WIFI_SETUP_SCREEN_MAIN, GX_BLEND_PLANEMASK_BG0 | GX_BLEND_PLANEMASK_BG2 | GX_BLEND_PLANEMASK_OBJ, 8);
    WifiSetupDisplay_ShowPlanes(WIFI_SETUP_SCREEN_SUB, GX_PLANEMASK_BG0);
    WifiSetupDisplay_ShowPlanes(WIFI_SETUP_SCREEN_MAIN, GX_PLANEMASK_BG0 | GX_PLANEMASK_BG2 | GX_PLANEMASK_OBJ);
    WifiSetupApp_SetStateFunc(WifiSetupAddressEntry_OpenKeypad);
}

void WifiSetupAddressEntry_OpenKeypad(void) {
    if (WifiSetupFade_IsActive(WIFI_SETUP_SCREEN_SUB)) {
        return;
    }
    if (WifiSetupFade_IsActive(WIFI_SETUP_SCREEN_MAIN)) {
        return;
    }
    WifiSetupKeypad_Create();
    WifiSetupSound_Play(20);
    if (gWifiSetupAddressEntry->field == 0) {
        WifiSetupKeypad_SetCanDelete(0);
        WifiSetupKeypad_SetCanAdvance(0);
    } else {
        if (WifiSetupAddressEntry_IsFieldAtLeast(26)) {
            WifiSetupKeypad_SetCanType(0);
        }
        WifiSetupKeypad_SetCanAdvance(0);
    }
    WifiSetupApp_SetStateFunc(WifiSetupAddressEntry_WaitKeypad);
}

static void WifiSetupAddressEntry_WaitKeypad(void) {
    if (WifiSetupKeypad_GetInput() == WIFI_SETUP_KEYPAD_INPUT_BUSY) {
        return;
    }
    WifiSetupApp_SetStateFunc(WifiSetupAddressEntry_Main);
}

static void WifiSetupAddressEntry_Main(void) {
    WifiSetupAddressEntry_HandleInput();
    WifiSetupAddressEntry_Update();
}

static void WifiSetupAddressEntry_HandleInput(void) {
    int key = WifiSetupKeypad_GetInput();
    switch (key) {
    case WIFI_SETUP_KEYPAD_INPUT_NONE:
        return;
    case WIFI_SETUP_KEYPAD_INPUT_DELETE:
        if (gWifiSetupAddressEntry->field != 0 || gWifiSetupAddressEntry->digits[2] != 0) {
            WifiSetupSound_Play(3);
            if (gWifiSetupAddressEntry->digits[gWifiSetupAddressEntry->field * WIFI_SETUP_ADDRESS_FIELD_LEN + 2] == 0) {
                gWifiSetupAddressEntry->field--;
            }
            MI_CpuFill8(gWifiSetupAddressEntry->digits + gWifiSetupAddressEntry->field * WIFI_SETUP_ADDRESS_FIELD_LEN, 0, 3);
            if (gWifiSetupAddressEntry->field == 0 && gWifiSetupAddressEntry->digits[2] == 0) {
                WifiSetupKeypad_SetCanDelete(0);
            }
            WifiSetupKeypad_SetCanType(1);
            WifiSetupKeypad_SetCanAdvance(0);
        }
        break;
    case WIFI_SETUP_KEYPAD_INPUT_NEXT:
        if (gWifiSetupAddressEntry->field < (WIFI_SETUP_ADDRESS_NUM_FIELDS - 1) && gWifiSetupAddressEntry->digits[gWifiSetupAddressEntry->field * WIFI_SETUP_ADDRESS_FIELD_LEN + 2] != 0) {
            WifiSetupSound_Play(1);
            gWifiSetupAddressEntry->field++;
            WifiSetupKeypad_SetCanAdvance(0);
        }
        break;
    case WIFI_SETUP_KEYPAD_INPUT_BACK:
        gWifiSetupAddressEntry->result = WIFI_SETUP_ADDRESS_CANCELLED;
        WifiSetupSound_Play(7);
        WifiSetupApp_SetStateFunc(WifiSetupAddressEntry_StartClose);
        return;
    case WIFI_SETUP_KEYPAD_INPUT_OK:
        if (WifiSetupAddressEntry_IsValid()) {
            WifiSetupSound_Play(6);
            gWifiSetupAddressEntry->result = WIFI_SETUP_ADDRESS_VALID;
        } else {
            gWifiSetupAddressEntry->result = WIFI_SETUP_ADDRESS_INVALID;
            WifiSetupSound_Play(9);
        }
        gWifiSetupAddressEntry->field = 3;
        gWifiSetupAddressEntry->cursor->attr01 = (gWifiSetupAddressEntry->cursor->attr01 & 0xc1fffcff) | 0x200; // hide
        WifiSetupAddressEntry_UpdateCursor();
        WifiSetupAddressEntry_PadFields();
        WifiSetupApp_SetStateFunc(WifiSetupAddressEntry_StartClose);
        return;
    default: // digit
        if (gWifiSetupAddressEntry->field == (WIFI_SETUP_ADDRESS_NUM_FIELDS - 1) && WifiSetupAddressEntry_IsFieldAtLeast(26)) {
            break;
        }
        WifiSetupSound_Play(1);
        {
            u8 *entry = gWifiSetupAddressEntry->digits;
            int index = gWifiSetupAddressEntry->field * WIFI_SETUP_ADDRESS_FIELD_LEN;
            // the digits of a field shift in from the right
            if (entry[index + 2] == 0) {
                entry[index + 2] = key;
            } else if (entry[index + 1] == 0) {
                entry[index + 1] = entry[index + 2];
                entry[index + 2] = key;
                if (WifiSetupAddressEntry_IsFieldAtLeast(26) && gWifiSetupAddressEntry->field < (WIFI_SETUP_ADDRESS_NUM_FIELDS - 1)) {
                    gWifiSetupAddressEntry->field++;
                }
            } else {
                entry[index] = entry[index + 1];
                entry[index + 1] = entry[index + 2];
                entry[index + 2] = key;
                if (gWifiSetupAddressEntry->field < (WIFI_SETUP_ADDRESS_NUM_FIELDS - 1)) {
                    gWifiSetupAddressEntry->field++;
                }
            }
        }
        WifiSetupKeypad_SetCanDelete(1);
        if (gWifiSetupAddressEntry->field < (WIFI_SETUP_ADDRESS_NUM_FIELDS - 1)) {
            WifiSetupKeypad_SetCanAdvance(1);
        } else {
            WifiSetupKeypad_SetCanAdvance(0);
        }
        if (gWifiSetupAddressEntry->field == (WIFI_SETUP_ADDRESS_NUM_FIELDS - 1) && WifiSetupAddressEntry_IsFieldAtLeast(26)) {
            WifiSetupKeypad_SetCanType(0);
        }
        break;
    }
    WifiSetupAddressEntry_DrawDigits();
    WifiSetupAddressEntry_UpdateCursor();
}

// Whether the current field is full (three digits) or its value is at least limit, so that no
// further digit can be typed into it.
static int WifiSetupAddressEntry_IsFieldAtLeast(int limit) {
    u8 buf[WIFI_SETUP_ADDRESS_FIELD_LEN + 1], *p;
    int i;
    u8 *text = gWifiSetupAddressEntry->digits + gWifiSetupAddressEntry->field * WIFI_SETUP_ADDRESS_FIELD_LEN;
    if (text[0] != 0 && text[0] != ' ') {
        return 1;
    }
    MI_CpuCopy8(text, buf, WIFI_SETUP_ADDRESS_FIELD_LEN);
    buf[WIFI_SETUP_ADDRESS_FIELD_LEN] = 0;
    p = buf;
    for (i = 0; i < WIFI_SETUP_ADDRESS_FIELD_LEN; i++) {
        if (*p != 0) {
            break;
        }
        *p++ = ' ';
    }
    return atol((char *)buf) >= limit;
}

static void WifiSetupAddressEntry_Update(void) {
}

static void WifiSetupAddressEntry_StartClose(void) {
    WifiSetupFade_StartDelay(8);
    WifiSetupApp_SetStateFunc(WifiSetupAddressEntry_CloseKeypad);
}

static void WifiSetupAddressEntry_CloseKeypad(void) {
    if (WifiSetupFade_IsActive(WIFI_SETUP_SCREEN_SUB)) {
        return;
    }
    WifiSetupKeypad_Close();
    WifiSetupSound_Play(21);
    WifiSetupApp_SetStateFunc(WifiSetupAddressEntry_WaitKeypadClosed);
}

static void WifiSetupAddressEntry_WaitKeypadClosed(void) {
    if (WifiSetupKeypad_Exists()) {
        return;
    }
    if (gWifiSetupAddressEntry->result == WIFI_SETUP_ADDRESS_CANCELLED) {
        WifiSetupApp_SetStateFunc(WifiSetupAddressEntry_Exit);
        return;
    }
    if (gWifiSetupAddressEntry->result == WIFI_SETUP_ADDRESS_INVALID) {
        WifiSetupDialog_Open(6, 3, 1, -1, 0);
        WifiSetupApp_SetStateFunc(WifiSetupAddressEntry_WaitInvalidMessage);
        return;
    }
    WifiSetupDialog_Open(71, 2, 1, -1, 0);
    WifiSetupApp_SetStateFunc(WifiSetupAddressEntry_WaitConfirm);
}

static void WifiSetupAddressEntry_Exit(void) {
    int kind;
    WifiSetupMessage_Hide();
    WifiSetupOam_Release(gWifiSetupAddressEntry->cursor);
    WifiSetupText_FreeBgCanvas(WIFI_SETUP_SCREEN_MAIN);
    WifiSetup_LoadGraphics(gWifiSetupAddressEntryYbObjMainNclPath, GX_LoadOBJPltt);
    WifiSetupDisplay_HidePlanes(WIFI_SETUP_SCREEN_SUB, GX_PLANEMASK_BG0);
    WifiSetupDisplay_HidePlanes(WIFI_SETUP_SCREEN_MAIN, GX_PLANEMASK_BG0 | GX_PLANEMASK_BG2 | GX_PLANEMASK_OBJ);
    WifiSetupApp_GetScreenArgs(&kind, 0);
    if (kind >= 3) {
        kind++;
    }
    WifiSetupApp_SetTransition(WIFI_SETUP_BANNER_CHANGE, WIFI_SETUP_BUTTON_BAR_CREATE);
    WifiSetupApp_SetScreenArgs(0, kind + 3);
    WifiSetupApp_SetStateFunc(WifiSetupSettings_Init);
    WifiSetupHeap_FreeAndClear(&gWifiSetupTextEntry[1]); // &gWifiSetupAddressEntry
}

static inline void DrawDigit(WifiSetupCanvas *canvas, u16 x, volatile WifiSetupTextBox *rect, u16 *text) {
    WifiSetupText_DrawInRect(canvas, x, rect->y, rect->width, rect->height, 2, 0x480, text);
}

void WifiSetupAddressEntry_DrawDigits(void) {
    WifiSetupAddressEntry *entry = gWifiSetupAddressEntry;
    WifiSetupTextBox rect;
    u16 text[2];
    int i;
    rect.x = ((const u16 *)&gWifiSetupAddressLayout)[7];
    rect.y = ((const u16 *)&gWifiSetupAddressLayout)[8];
    rect.width = 11;
    rect.height = 16;
    WifiSetupText_Clear(entry->canvas, 0);
    text[1] = 0;
    for (i = 0; i < WIFI_SETUP_ADDRESS_NUM_FIELDS * WIFI_SETUP_ADDRESS_FIELD_LEN; i++) {
        u16 x = gWifiSetupAddressEntryDigitX[i];
        text[0] = gWifiSetupAddressEntry->digits[i];
        rect.x = x;
        DrawDigit(gWifiSetupAddressEntry->canvas, x, &rect, text);
    }
    WifiSetupText_MarkDirty(gWifiSetupAddressEntry->canvas);
}

static inline void SetOamPos(u32 *attr01, int x, int y) {
    *attr01 = (*attr01 & 0xFE00FF00) | ((u32)(y & 0xff)) | ((u32)(x & 0x1ff) << 16);
}

void WifiSetupAddressEntry_UpdateCursor(void) {
    int field = gWifiSetupAddressEntry->field;
    if (field > 3) {
        field = 3;
    }
    SetOamPos(&gWifiSetupAddressEntry->cursor->attr01, gWifiSetupAddressEntryDigitX[field * WIFI_SETUP_ADDRESS_FIELD_LEN + 2], 0x28);
}

static void WifiSetupAddressEntry_WaitConfirm(void) {
    gWifiSetupAddressEntry->result = WifiSetupDialog_GetSelected();
    switch (gWifiSetupAddressEntry->result) {
    case 0:
        WifiSetupSound_Play(7);
        break;
    case 1:
        WifiSetupSound_Play(14);
        break;
    default:
        return;
    }
    WifiSetupDialog_Close();
    WifiSetupApp_SetStateFunc(WifiSetupAddressEntry_FinishConfirm);
}

static void WifiSetupAddressEntry_FinishConfirm(void) {
    WifiSetupAddressFuncs store = gWifiSetupAddressEntryFuncs;
    int kind;
    if (WifiSetupDialog_IsOpen()) {
        return;
    }
    if (!gWifiSetupAddressEntry->result) {
        gWifiSetupAddressEntry->cursor->attr01 &= 0xc1fffcff; // show again
        WifiSetupApp_SetStateFunc(WifiSetupAddressEntry_OpenKeypad);
        return;
    }
    WifiSetupApp_GetScreenArgs(&kind, 0);
    store.funcs[kind](gWifiSetupAddressEntry->digits);
    WifiSetupApp_SetStateFunc(WifiSetupAddressEntry_Exit);
}

// Pads every field to three characters: empty or zero digits before the last one become spaces,
// an empty last digit becomes '0'.
static void WifiSetupAddressEntry_PadFields(void) {
    u8 *field;
    int i = 0;
    int j;
    int offset = i;
    int space = ' ', digit = '0', zero = i;
    do {
        field = &gWifiSetupAddressEntry->digits[offset];
        j = zero;
        do {
            u8 ch = field[j];
            if (ch != digit && ch != space && ch != zero) {
                break;
            }
            field[j] = j == 2 ? digit : space;
            j++;
        } while (j < WIFI_SETUP_ADDRESS_FIELD_LEN);
        i++;
        offset += WIFI_SETUP_ADDRESS_FIELD_LEN;
    } while (i < WIFI_SETUP_ADDRESS_NUM_FIELDS);
    WifiSetupAddressEntry_DrawDigits();
}

// Every field must be at most 255. A subnet mask (kind 1) must be contiguous ones followed by
// zeros; other addresses are checked by DWC_BACKUPlCheckAddress.
static int WifiSetupAddressEntry_IsValid(void) {
    WifiSetupFieldLimit limit = gWifiSetupAddressLayout;
    int i;
    int kind;
    u8 address[4];
    u8 *field;
    int j;
    int zero;
    for (i = 0; i < WIFI_SETUP_ADDRESS_NUM_FIELDS; i++) {
        field = &gWifiSetupAddressEntry->digits[i * WIFI_SETUP_ADDRESS_FIELD_LEN];
        if (field[0] == ' ') {
            continue;
        }
        for (j = 0; j < WIFI_SETUP_ADDRESS_FIELD_LEN; j++) {
            if (field[j] > limit.digits[j]) {
                return 0;
            }
            if (field[j] < limit.digits[j]) {
                break;
            }
        }
    }
    WifiSetup_ParseAddress((const char *)gWifiSetupAddressEntry->digits, address);
    WifiSetupApp_GetScreenArgs(&kind, 0);
    if (kind == 1) {
        zero = 0;
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 8; j++) {
                if (zero) {
                    if (address[i] & (1 << (7 - j))) {
                        return 0;
                    }
                } else if (!(address[i] & (1 << (7 - j)))) {
                    zero = 1;
                }
            }
        }
        return 1;
    }
    return DWC_BACKUPlCheckAddress(address) != 0;
}
