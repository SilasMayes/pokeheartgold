#ifndef POKEHEARTGOLD_APPLICATION_MAIN_MENU_MYSTERY_GIFT_APP_H
#define POKEHEARTGOLD_APPLICATION_MAIN_MENU_MYSTERY_GIFT_APP_H

#include "overlay_manager.h"

typedef struct MysteryGiftAppData MysteryGiftAppData;
typedef struct MysteryGiftAnimData MysteryGiftAnimData;
typedef struct MysteryGiftParticle MysteryGiftParticle;

extern const OverlayManagerTemplate gApp_MainMenu_SelectOption_MysteryGift;

typedef int (*MysteryGiftMenuFunc)(OverlayManager *manager);

typedef struct MysteryGiftMenuItem {
    u32 msgId;
    MysteryGiftMenuFunc func;
} MysteryGiftMenuItem;

void thunk_MysteryGiftApp_SetWaitingIconVisible(MysteryGiftAppData *data, BOOL visible);
void MysteryGiftApp_RunWfcDownload(OverlayManager *manager, int *state);
void MysteryGiftApp_ShowWfcError(MysteryGiftAppData *data);
OverlayManager *MysteryGiftApp_GetOverlayManager(void);

#endif // POKEHEARTGOLD_APPLICATION_MAIN_MENU_MYSTERY_GIFT_APP_H
