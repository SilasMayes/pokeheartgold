#ifndef POKEHEARTGOLD_OVERLAY_TRAINER_CARD_H
#define POKEHEARTGOLD_OVERLAY_TRAINER_CARD_H

#include "menu_input_state.h"
#include "overlay_manager.h"
#include "save.h"

#define HEAP_ID_TRAINER_CARD ((enum HeapID)94)

typedef struct TrainerCardAppSettings {
    MenuInputStateMgr *menuInputStatePtr;
    SaveData *saveData;
    int showBack;
    BOOL gameCleared;
} TrainerCardAppSettings;

typedef struct TrainerCardAppArgs {
#ifdef SDK_PORT
    u8 card[0x66c + 4]; // a TrainerCardData: its IGT pointer is 8 bytes here (checked in trainer_card_data.c)
#else
    u8 card[0x66c];
#endif
    TrainerCardAppSettings settings;
} TrainerCardAppArgs;

// The trainer card overlay's view of TrainerCardAppArgs
#ifdef SDK_PORT
// The same fields at the port's offsets: the card's signature after the 8-byte IGT pointer, then the settings
// 8-aligned (checked in overlay_trainer_card.c).
typedef struct {
    u8 unk0[4];
    u8 unk4a : 4;
    u8 signatureExists : 1;
    u8 unk5[0x67];
    u8 signature[0x600];
    u8 unk66c[4];
    MenuInputStateMgr *menuInputStatePtr;
    SaveData *saveData;
    u32 reqUpdateSignature; // settings.showBack
} Ov50_021E5A3C;
#else
typedef struct {
    u8 unk0[4];
    u8 unk4a : 4;
    u8 signatureExists : 1;
    u8 unk5[0x63];
    u8 signature[0x600];
    u8 unk668[6];
    SaveData *saveData;
    u32 reqUpdateSignature;
} Ov50_021E5A3C;
#endif

typedef struct {
    enum HeapID heapID;
    u8 unk4[4];
    OverlayManager *ov_mgr;
    Ov50_021E5A3C *parentData;
    void *unk10;
} TrainerCardAppState;

BOOL TrainerCard_Init(OverlayManager *man, int *state);
BOOL TrainerCard_Main(OverlayManager *man, int *state);
BOOL TrainerCard_Exit(OverlayManager *man, int *state);

#endif // POKEHEARTGOLD_OVERLAY_TRAINER_CARD_H
