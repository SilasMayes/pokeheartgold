#include "wifi_setup/wifi_setup_scroll_bar.h"

#include "global.h"

#include "wifi_setup/wifi_setup_access_points.h"
#include "wifi_setup/wifi_setup_keypad.h"
#include "wifi_setup/wifi_setup_local_wireless.h"
#include "wifi_setup/wifi_setup_ui.h"

#include <nitro/code32.h>

// Vertical scroll bar.

extern s32 FX_DivS32(s32, s32);

static void WifiSetupScrollBar_Drag(void);
static void WifiSetupScrollBar_PlayDragSound(int value);
static void WifiSetupScrollBar_PressArrow(int state);
static void WifiSetupScrollBar_JumpToTouch(void);
static int WifiSetupScrollBar_GetTouchedPart(void);
static int WifiSetupScrollBar_GetHeldArrow(int part);
static void WifiSetupScrollBar_SetThumbPos(int value);
static void WifiSetupScrollBar_GetPartRect(int part, WifiSetupRect *rect);

WifiSetupScrollBar *gWifiSetupScrollBar;

void WifiSetupScrollBar_Destroy(void) {
    WifiSetupTask_Destroy(WIFI_SETUP_TASK_QUEUE_MAIN, gWifiSetupScrollBar->task);
    WifiSetupOamBlock_Free(gWifiSetupScrollBar->thumb);
    WifiSetupHeap_FreeAndClear(&gWifiSetupScrollBar);
}

u8 WifiSetupScrollBar_GetValue(void) {
    return gWifiSetupScrollBar->value;
}

u8 WifiSetupScrollBar_GetEvent(void) {
    return gWifiSetupScrollBar->event;
}

void WifiSetupScrollBar_SetValue(int value) {
    WifiSetupScrollBar_SetThumbPos(value);
}

void WifiSetupScrollBar_Enable(void) {
    gWifiSetupScrollBar->disabled = 0;
}

void WifiSetupScrollBar_Disable(void) {
    gWifiSetupScrollBar->disabled = 1;
}

void WifiSetupScrollBar_Task(WifiSetupTask *task, void *arg) {
    gWifiSetupScrollBar->event = WIFI_SETUP_SCROLL_BAR_EVENT_NONE;
    switch (gWifiSetupScrollBar->state) {
    case WIFI_SETUP_SCROLL_BAR_STATE_IDLE:
        if (gWifiSetupScrollBar->disabled) {
            return;
        }
        switch (WifiSetupScrollBar_GetTouchedPart()) {
        case WIFI_SETUP_SCROLL_BAR_THUMB:
            if (gWifiSetupScrollBar->kind == 0) {
                return;
            }
            WifiSetupSound_Play(0x16);
            WifiSetupSound_SetVolume(0);
            gWifiSetupScrollBar->event = WIFI_SETUP_SCROLL_BAR_EVENT_GRABBED;
            WifiSetupInput_GetTouchPos(&gWifiSetupScrollBar->touchStart);
            gWifiSetupScrollBar->dragStart = gWifiSetupScrollBar->value;
            gWifiSetupScrollBar->state = WIFI_SETUP_SCROLL_BAR_STATE_DRAGGING;
            return;
        case WIFI_SETUP_SCROLL_BAR_UP:
            WifiSetupScrollBar_PressArrow(WIFI_SETUP_SCROLL_BAR_STATE_UP);
            return;
        case WIFI_SETUP_SCROLL_BAR_DOWN:
            WifiSetupScrollBar_PressArrow(WIFI_SETUP_SCROLL_BAR_STATE_DOWN);
            return;
        case WIFI_SETUP_SCROLL_BAR_TRACK:
            WifiSetupScrollBar_JumpToTouch();
            return;
        }
        break;
    case WIFI_SETUP_SCROLL_BAR_STATE_DRAGGING:
        WifiSetupScrollBar_Drag();
        break;
    case WIFI_SETUP_SCROLL_BAR_STATE_UP:
        if (WifiSetupScrollBar_GetHeldArrow(WIFI_SETUP_SCROLL_BAR_UP) != WIFI_SETUP_SCROLL_BAR_UP) {
            gWifiSetupScrollBar->event = WIFI_SETUP_SCROLL_BAR_EVENT_UP_RELEASED;
            gWifiSetupScrollBar->state = WIFI_SETUP_SCROLL_BAR_STATE_IDLE;
            return;
        }
        if (WifiSetupScrollBar_GetTouchedPart() == WIFI_SETUP_SCROLL_BAR_UP) {
            WifiSetupScrollBar_PressArrow(WIFI_SETUP_SCROLL_BAR_STATE_UP);
        }
        break;
    case WIFI_SETUP_SCROLL_BAR_STATE_DOWN:
        if (WifiSetupScrollBar_GetHeldArrow(WIFI_SETUP_SCROLL_BAR_DOWN) != WIFI_SETUP_SCROLL_BAR_DOWN) {
            gWifiSetupScrollBar->event = WIFI_SETUP_SCROLL_BAR_EVENT_DOWN_RELEASED;
            gWifiSetupScrollBar->state = WIFI_SETUP_SCROLL_BAR_STATE_IDLE;
            return;
        }
        if (WifiSetupScrollBar_GetTouchedPart() == WIFI_SETUP_SCROLL_BAR_DOWN) {
            WifiSetupScrollBar_PressArrow(WIFI_SETUP_SCROLL_BAR_STATE_DOWN);
        }
        break;
    }
}

static void WifiSetupScrollBar_Drag(void) {
    WifiSetupPoint touch;
    WifiSetupScrollBar *bar;
    int pos;
    int max;

    if (WifiSetupInput_IsTouchHeld(&gWifiSetupInputPanelRect)) {
        WifiSetupInput_GetTouchPos(&touch);
        bar = gWifiSetupScrollBar;
        if (touch.x >= bar->pos.x - 0x1e) {
            pos = bar->dragStart + (touch.y - bar->touchStart.y);
            if (pos < 0) {
                pos = 0;
            } else {
                max = bar->length - gWifiSetupScrollBarThumbLengths[bar->kind];
                if (pos >= max) {
                    pos = max;
                }
            }
            WifiSetupScrollBar_PlayDragSound(pos);
            WifiSetupScrollBar_SetThumbPos(pos);
            gWifiSetupScrollBar->event = WIFI_SETUP_SCROLL_BAR_EVENT_DRAGGED;
            return;
        }
    }
    WifiSetupSound_Stop();
    gWifiSetupScrollBar->state = WIFI_SETUP_SCROLL_BAR_STATE_IDLE;
    gWifiSetupScrollBar->event = WIFI_SETUP_SCROLL_BAR_EVENT_RELEASED;
}

static void WifiSetupScrollBar_PlayDragSound(int value) {
    int delta = gWifiSetupScrollBar->value - value;
    int level;
    if (delta < 0) {
        delta = -delta;
    }
    if (delta < 2) {
        level = 0;
    } else if (delta >= 6) {
        level = 0x7f;
    } else {
        level = FX_DivS32(0x7f, 6 - delta);
    }
    WifiSetupSound_SetVolume(level);
    if (delta < 2) {
        level = -0x100;
    } else if (delta >= 6) {
        level = 0x100;
    } else {
        level = FX_DivS32(0x200, 6 - delta) - 0x100;
    }
    WifiSetupSound_SetTrackPitch(0xFFFF, level);
}

static void WifiSetupScrollBar_PressArrow(int state) {
    gWifiSetupScrollBar->state = state;
    gWifiSetupScrollBar->event = (state == WIFI_SETUP_SCROLL_BAR_STATE_UP) ? WIFI_SETUP_SCROLL_BAR_EVENT_UP_PRESSED : WIFI_SETUP_SCROLL_BAR_EVENT_DOWN_PRESSED;
}

static void WifiSetupScrollBar_JumpToTouch(void) {
    WifiSetupPoint touch;
    WifiSetupScrollBar *bar;
    u32 thumbLength;
    int pos;
    int max;

    WifiSetupInput_GetTouchPos(&touch);
    bar = gWifiSetupScrollBar;
    thumbLength = gWifiSetupScrollBarThumbLengths[bar->kind];
    pos = touch.y - bar->pos.y - (thumbLength >> 1);
    if (pos < 0) {
        pos = 0;
    } else {
        max = bar->length - thumbLength;
        if (pos >= max) {
            pos = max;
        }
    }
    WifiSetupScrollBar_SetThumbPos(pos);
    gWifiSetupScrollBar->event = WIFI_SETUP_SCROLL_BAR_EVENT_RELEASED;
}

static int WifiSetupScrollBar_GetTouchedPart(void) {
    WifiSetupRect rect;
    int i;
    WifiSetupScrollBar_GetPartRect(WIFI_SETUP_SCROLL_BAR_THUMB, &rect);
    if (WifiSetupInput_IsTouchRepeated(&rect)) {
        return WIFI_SETUP_SCROLL_BAR_THUMB;
    }
    for (i = WIFI_SETUP_SCROLL_BAR_UP; i <= WIFI_SETUP_SCROLL_BAR_DOWN; i++) {
        WifiSetupScrollBar_GetPartRect(i, &rect);
        if (WifiSetupInput_IsTouchRepeated(&rect)) {
            return i;
        }
    }
    WifiSetupScrollBar_GetPartRect(WIFI_SETUP_SCROLL_BAR_TRACK, &rect);
    if (WifiSetupInput_IsTouchPressed(&rect)) {
        return WIFI_SETUP_SCROLL_BAR_TRACK;
    }
    return 0;
}

static int WifiSetupScrollBar_GetHeldArrow(int part) {
    WifiSetupRect rect;
    int i;
    for (i = WIFI_SETUP_SCROLL_BAR_UP; i <= WIFI_SETUP_SCROLL_BAR_DOWN; i++) {
        WifiSetupScrollBar_GetPartRect(i, &rect);
        if (WifiSetupInput_IsTouchHeld(&rect)) {
            return i;
        }
    }
    return 0;
}

static void WifiSetupScrollBar_GetPartRect(int part, WifiSetupRect *rect) {
    u16 x = gWifiSetupScrollBar->pos.x;
    u16 y;
    rect->left = x;
    rect->right = x + 12;
    switch (part) {
    case WIFI_SETUP_SCROLL_BAR_THUMB:
        rect->top = gWifiSetupScrollBar->pos.y + gWifiSetupScrollBar->value;
        rect->bottom = rect->top + gWifiSetupScrollBarThumbLengths[gWifiSetupScrollBar->kind];
        break;
    case WIFI_SETUP_SCROLL_BAR_UP:
        rect->top = gWifiSetupScrollBar->pos.y - 13;
        rect->bottom = gWifiSetupScrollBar->pos.y;
        break;
    case WIFI_SETUP_SCROLL_BAR_DOWN:
        rect->top = gWifiSetupScrollBar->pos.y + gWifiSetupScrollBar->length;
        rect->bottom = rect->top + 13;
        break;
    case WIFI_SETUP_SCROLL_BAR_TRACK:
        y = gWifiSetupScrollBar->pos.y;
        rect->top = y;
        rect->bottom = y + gWifiSetupScrollBar->length;
        break;
    }
}

static void WifiSetupScrollBar_SetThumbPos(int value) {
    WifiSetupOamBlock_SetPosition(gWifiSetupScrollBar->thumb, -1, gWifiSetupScrollBar->pos.x, value + gWifiSetupScrollBar->pos.y);
    gWifiSetupScrollBar->value = value;
}
