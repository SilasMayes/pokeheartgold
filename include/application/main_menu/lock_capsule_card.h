#ifndef POKEHEARTGOLD_APPLICATION_MAIN_MENU_LOCK_CAPSULE_CARD_H
#define POKEHEARTGOLD_APPLICATION_MAIN_MENU_LOCK_CAPSULE_CARD_H

#include "application/main_menu/wonder_card_album.h"

#include "bg_window.h"
#include "mystery_gift.h"
#include "overlay_manager.h"
#include "save.h"

typedef struct LockCapsuleCardView LockCapsuleCardView;

extern const OverlayManagerTemplate sWonderCardAlbumOverlayTemplate;
extern const OverlayManagerTemplate sLockCapsuleCardOverlayTemplate;
extern const WonderCardTextBox gLockCapsuleCardTextBoxes[11];

BOOL LockCapsuleCard_PrintMessageOnly(void);
BOOL LockCapsuleCard_PrintCardTitle(LockCapsuleCardView *view, Window *window, u32 color);
BOOL LockCapsuleCard_PrintStatus(LockCapsuleCardView *view, Window *window, u32 color);
BOOL LockCapsuleCard_BufferReceiveDate(LockCapsuleCardView *view);
BOOL LockCapsuleCard_PrintCardText(LockCapsuleCardView *view, Window *window, u32 color);
BOOL LockCapsuleCard_PrintNothing(void);
BOOL LockCapsuleCard_ShowCardMenu(LockCapsuleCardView *view, Window *window, u32 color);
void LockCapsuleCard_DrawCardOnBg(BgConfig *bgConfig, WonderCard *card, enum HeapID heapID);
void WonderCard_SetGraphicsBanks(void);
void WonderCard_InitBgLayers(BgConfig *bgConfig);
// MysteryGift_CheckCanReceive
enum MysteryGiftCheckResult {
    MYSTERY_GIFT_CHECK_OK,
    MYSTERY_GIFT_CHECK_WRONG_GAME,
    MYSTERY_GIFT_CHECK_ALREADY_RECEIVED, // unique gift
    MYSTERY_GIFT_CHECK_NO_GIFT_SLOT,
    MYSTERY_GIFT_CHECK_NO_CARD_SLOT,
    MYSTERY_GIFT_CHECK_OTHER_ROUTE, // delivered by another route
};

int MysteryGift_CheckCanReceive(SaveData *saveData, WonderCardInfo *header);

#endif // POKEHEARTGOLD_APPLICATION_MAIN_MENU_LOCK_CAPSULE_CARD_H
