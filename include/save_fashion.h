#ifndef POKEHEARTGOLD_SAVE_FASHION_H
#define POKEHEARTGOLD_SAVE_FASHION_H

#include "constants/accessories.h"

#include "application/dress_up/dress_up_internal.h"

#include "fashion_case.h"
#include "heap.h"
#include "pm_string.h"
#include "pokemon.h"

#define FASHION_ENTRY_COUNT       11
#define FASHION_LARGE_ENTRY_COUNT 5
#define FASHION_ENTRY_ITEM_MAX    10

// Accessories below ACCESSORY_COLORED_PARASOL are kept in counts of up to 9, the others as owned flags.
#define FASHION_ACCESSORY_COUNT            (ACCESSORY_COMET + 1)
#define FASHION_STACKABLE_ACCESSORY_COUNT  ACCESSORY_COLORED_PARASOL
#define FASHION_STACKABLE_ACCESSORY_MAX    9

// Wallpapers are kept as their order of receipt; FASHION_WALLPAPER_NOT_OWNED marks one not received yet.
#define FASHION_WALLPAPER_COUNT     18
#define FASHION_WALLPAPER_NOT_OWNED FASHION_WALLPAPER_COUNT

typedef struct SaveFashionMon SaveFashionMon;

void Save_FashionData_Init(SaveFashionData *fashionData);
u32 Save_FashionData_sizeof(void);
u32 FashionEntry_sizeof(void);
SaveFashionDataSub *FashionEntry_New(enum HeapID heapId);
BOOL FashionEntry_IsSaved(SaveFashionDataSub *entry_);
int FashionCase_GetWallpaperOrder(FashionCase *fashionCase, int index);
void FashionEntry_MarkSaved(SaveFashionDataSub *entry_);
void FashionEntry_Clear(SaveFashionDataSub *entry_);
void FashionEntry_SetMon(SaveFashionDataSub *entry_, Pokemon *mon, DressUpMonPic *monPic);
void FashionEntry_PlaceItem(SaveFashionDataSub *entry_, DressUpSlot *source, int index);
void FashionEntry_SetBackdrop(SaveFashionDataSub *entry_, int value);
void FashionEntry_SetMonSecondText(SaveFashionDataSub *entry_, String *string, u32 gender);
BOOL FashionEntry_IsItemPlaced(SaveFashionDataSub *entry_, int index);
SaveFashionMon *FashionEntry_GetMon(SaveFashionDataSub *entry_);
u8 *FashionEntry_GetItem(SaveFashionDataSub *entry_, int index);
void FashionEntry_GetMonSecondText(SaveFashionDataSub *entry_, String *string);
u8 FashionEntry_GetBackdrop(SaveFashionDataSub *entry_);
u16 FashionEntry_GetMailMessageWord(SaveFashionDataSub *entry_);
s8 FashionMon_GetZ(SaveFashionMon *mon);
u8 FashionMon_GetX(SaveFashionMon *mon);
u8 FashionMon_GetY(SaveFashionMon *mon);
void FashionMon_ToPokemon(SaveFashionMon *mon, Pokemon *pokemon);
u8 FashionItem_GetId(u8 *data);
u8 FashionItem_GetX(u8 *data);
u8 FashionItem_GetY(u8 *data);
s8 FashionItem_GetZ(s8 *data);
void Save_FashionData_InsertEntries(u8 count, int skip, SaveFashionData *fashionData, SaveFashionDataSub **entries);

#endif // POKEHEARTGOLD_SAVE_FASHION_H
