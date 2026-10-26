#ifndef POKEHEARTGOLD_APPLICATION_MAIN_MENU_MYSTERY_GIFT_WFC_H
#define POKEHEARTGOLD_APPLICATION_MAIN_MENU_MYSTERY_GIFT_WFC_H

#include "global.h"

#include "overlay_manager.h"

// Download of a Mystery Gift over Nintendo Wi-Fi Connection.

// results of MysteryGiftWfc_Run
#define MYSTERY_GIFT_WFC_RESULT_RUNNING   0
#define MYSTERY_GIFT_WFC_RESULT_RECEIVED  1
#define MYSTERY_GIFT_WFC_RESULT_NO_GIFT   2
#define MYSTERY_GIFT_WFC_RESULT_CANCELLED 3
#define MYSTERY_GIFT_WFC_RESULT_ERROR     4 // shown and acknowledged

// states of MysteryGiftWfc_Run (*state); a download starts at WFC_STATE_LOAD_OVERLAYS
#define WFC_STATE_LOAD_OVERLAYS  0x1000
#define WFC_STATE_WAIT_OVERLAYS  0x1001
#define WFC_STATE_INIT           0x1002
#define WFC_STATE_CONNECT        0x1003
#define WFC_STATE_LOGIN          0x1004
#define WFC_STATE_WAIT_LOGIN     0x1005
#define WFC_STATE_INIT_DOWNLOAD  0x1006
#define WFC_STATE_SET_ATTRIBUTES 0x1007
#define WFC_STATE_GET_FILE_COUNT 0x1008
#define WFC_STATE_GET_FILE_LIST  0x1009
#define WFC_STATE_GET_FILE       0x100A
#define WFC_STATE_DOWNLOADING    0x100B
#define WFC_STATE_CLEANUP        0x100C
#define WFC_STATE_DISCONNECT     0x100D
#define WFC_STATE_ERROR          0x100F
#define WFC_STATE_WAIT_BUTTON    0x1010
#define WFC_STATE_ERROR_SHOWN    0x1011
#define WFC_STATE_WAIT_REQUEST   0x1012 // until MysteryGiftWfc_OnRequestDone, then wfcNextState
#define WFC_STATE_WAIT_CLEANUP   0x1013 // until MysteryGiftWfc_OnCleanupDone, then wfcNextState

int MysteryGiftWfc_Run(OverlayManager *manager, int *state);

#endif // POKEHEARTGOLD_APPLICATION_MAIN_MENU_MYSTERY_GIFT_WFC_H
