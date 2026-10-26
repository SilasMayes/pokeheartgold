#include <stddef.h>

#include "global.h"

#include "constants/items.h"
#include "constants/pokemon.h"
#include "constants/species.h"

#include "application/pc_box/pc_box_internal.h"

#include "bg_cell_manager.h"
#include "char_tiles.h"
#include "filesystem.h"
#include "font_sprite.h"
#include "gf_gfx_loader.h"
#include "gf_gfx_planes.h"
#include "heap.h"
#include "item.h"
#include "party.h"
#include "pokemon.h"
#include "pokemon_icon_idx.h"
#include "pokemon_storage_system.h"
#include "sprite.h"
#include "sprite_system.h"
#include "type_icon_resources.h"

static void PCBox_SetSpriteDrawPriority(PCBoxView *view, u32 index, u32 priority);
static void PCBox_SetSpriteTranslucent(PCBoxView *view, u32 index, u32 enabled);
static void PCBox_FreeSpriteSystem(PCBoxView *view);
static void PCBox_DeleteSprite(PCBoxView *view, u32 index);
static void PCBox_DeleteAllSprites(PCBoxView *view);
static void PCBox_LoadSpriteCharsSub(PCBoxView *view, int index, void *src, u32 size);
static void PCBox_LoadMonIconResources(PCBoxView *view);
static void PCBox_CreateMonIconSprites(PCBoxView *view);
static void *PCBox_LoadMonIconChars(PCBoxView *view, BoxPokemon *boxMon, NNSG2dCharacterData **charData);
static void PCBox_SetIconImage(PCBoxView *view, void *src, int index, int palette);
static void PCBox_LoadMonIcon(PCBoxWork *work, BoxPokemon *boxMon, int index);
static void PCBox_SetIconRangeTranslucent(PCBoxWork *work, u32 enabled, u32 first, u32 end, u32 check);
static void PCBox_UpdateSlotIconItemTranslucency(PCBoxWork *work, u32 slot);
static void PCBox_LoadMonPicResources(PCBoxView *view);
static void PCBox_CreateMonPicSprites(PCBoxWork *work);
static void PCBox_LoadMonPic(PCBoxView *view, PCBoxMonInfo *monInfo, u32 index);
static void PCBox_LoadItemIconResources(PCBoxView *view);
static void PCBox_CreateItemIconSprites(PCBoxView *view);
static void PCBox_LoadTypeIconResources(PCBoxView *view);
static void PCBox_CreateTypeIconSprites(PCBoxView *view);
static void PCBox_LoadTypeIcon(PCBoxView *view, u32 type, u32 index, u32 resourceId);
static void PCBox_LoadUiSpriteResources(PCBoxView *view);
static void PCBox_CreateUiSprites(PCBoxView *view);
static void PCBox_LoadTrayBoxResources(PCBoxView *view);
static void PCBox_CreateTrayBoxSprites(PCBoxView *view);
static void PCBox_LoadWallpaperListResources(PCBoxView *view);
static void PCBox_CreateWallpaperListSprites(PCBoxView *view);
static void PCBox_PlaceWallpaperMenuTextObj(PCBoxView *view);
static void PCBox_ColorWallpaperThumbnail(PCBoxWork *work, u8 *buf, u32 wallpaper, u32 match, u32 size);

void PCBox_FreeSprites(PCBoxView *view) {
    PCBox_DestroyTrayTextObjs(view);
    PCBox_DeleteAllSprites(view);
    PCBox_FreeSpriteSystem(view);
}

void PCBox_TickSprites(PCBoxView *view) {
    u32 i;

    for (i = 0; i < 15; i++) {
        if (view->sprites[i] != NULL) {
            ManagedSprite_TickFrame(view->sprites[i]);
        }
    }
}

void PCBox_SetSpriteAnim(PCBoxView *view, u32 index, u32 anim) {
    ManagedSprite_SetAnimationFrame(view->sprites[index], 0);
    ManagedSprite_SetAnim(view->sprites[index], anim);
}

u32 PCBox_IsSpriteAnimated(PCBoxView *view, u32 index) {
    return ManagedSprite_IsAnimated(view->sprites[index]);
}

void PCBox_SetSpriteVisible(PCBoxView *view, int index, BOOL visible) {
    if (visible == TRUE) {
        ManagedSprite_SetDrawFlag(view->sprites[index], TRUE);
    } else {
        ManagedSprite_SetDrawFlag(view->sprites[index], FALSE);
    }
}

int PCBox_IsSpriteVisible(PCBoxView *view, int index) {
    if (ManagedSprite_GetDrawFlag(view->sprites[index]) == TRUE) {
        return 1;
    }
    return 0;
}

void PCBox_SetSpritePriority(PCBoxView *view, u32 index, u32 priority) {
    ManagedSprite_SetPriority(view->sprites[index], priority);
}

static void PCBox_SetSpriteDrawPriority(PCBoxView *view, u32 index, u32 priority) {
    view->spriteDrawLock = 1;
    ((void (*)(ManagedSprite *, u32))ManagedSprite_SetDrawPriority)(view->sprites[index], priority);
    view->spriteDrawLock = 0;
}

static void PCBox_SetSpriteTranslucent(PCBoxView *view, u32 index, u32 enabled) {
    if (enabled == 1) {
        ManagedSprite_SetOamMode(view->sprites[index], GX_OAM_MODE_XLU);
    } else {
        ManagedSprite_SetOamMode(view->sprites[index], GX_OAM_MODE_NORMAL);
    }
}

void PCBox_InitSpriteSystem(PCBoxView *view) {
    SpriteResourceCountsListUnion counts;
    OamManagerParam oamManagerParam;
    OamCharTransferParam oamCharTransferParam;

    counts = gPCBoxSpriteResourceCounts;
    view->spriteSystem = SpriteSystem_Alloc(HEAP_ID_10);
    view->spriteManager = SpriteManager_New(view->spriteSystem);
    oamManagerParam = gPCBoxOamManagerParam;
    oamCharTransferParam = gPCBoxOamCharTransferParam;
    SpriteSystem_Init(view->spriteSystem, &oamManagerParam, &oamCharTransferParam, 0x20);
    SpriteSystem_InitSprites(view->spriteSystem, view->spriteManager, 0x67);
    SpriteSystem_InitManagerWithCapacities(view->spriteSystem, view->spriteManager, &counts);
    G2dRenderer_SetSubSurfaceCoords(SpriteSystem_GetRenderer(view->spriteSystem), 0, 2 << 20);
}

static void PCBox_FreeSpriteSystem(PCBoxView *view) {
    SpriteSystem_FreeResourcesAndManager(view->spriteSystem, view->spriteManager);
    SpriteSystem_Free(view->spriteSystem);
}

void PCBox_LoadSpriteResources(PCBoxView *view) {
    PCBox_LoadTrayBoxResources(view);
    PCBox_LoadWallpaperListResources(view);
    PCBox_LoadMonIconResources(view);
    PCBox_LoadUiSpriteResources(view);
    PCBox_LoadItemIconResources(view);
    PCBox_LoadMonPicResources(view);
    PCBox_LoadTypeIconResources(view);
}

void PCBox_CreateSprites(PCBoxWork *work) {
    PCBox_CreateTrayBoxSprites(work->view);
    PCBox_CreateWallpaperListSprites(work->view);
    PCBox_CreateMonIconSprites(work->view);
    PCBox_CreateUiSprites(work->view);
    PCBox_CreateItemIconSprites(work->view);
    PCBox_CreateMonPicSprites(work);
    PCBox_CreateTypeIconSprites(work->view);
}

static void PCBox_DeleteSprite(PCBoxView *view, u32 index) {
    if (view->sprites[index] != NULL) {
        Sprite_DeleteAndFreeResources(view->sprites[index]);
        view->sprites[index] = NULL;
    }
}

static void PCBox_DeleteAllSprites(PCBoxView *view) {
    u32 i;

    for (i = 0; i < 69; i++) {
        PCBox_DeleteSprite(view, i);
    }
}

void PCBox_LoadSpriteCharsMain(PCBoxView *view, int index, void *src, u32 size) {
    u32 location = NNS_G2dGetImageLocation(Sprite_GetImageProxy(view->sprites[index]->sprite), NNS_G2D_VRAM_TYPE_2DMAIN);

    DC_FlushRange(src, size);
    GX_LoadOBJ(src, location, size);
}

static void PCBox_LoadSpriteCharsSub(PCBoxView *view, int index, void *src, u32 size) {
    u32 location = NNS_G2dGetImageLocation(Sprite_GetImageProxy(view->sprites[index]->sprite), NNS_G2D_VRAM_TYPE_2DSUB);

    DC_FlushRange(src, size);
    GXS_LoadOBJ(src, location, size);
}

static void PCBox_LoadMonIconResources(PCBoxView *view) {
    u32 i;

    for (i = 0; i < PC_BOX_SLOT_COUNT; i++) {
        SpriteSystem_LoadCharResObj(view->spriteSystem, view->spriteManager, NARC_a_0_1_9, 0x4E, TRUE, 1, 0xC0F9 + i);
    }
    SpriteSystem_LoadPlttResObj(view->spriteSystem, view->spriteManager, NARC_poketool_icongra_poke_icon, GetMonIconPlttNaix(), FALSE, 3, 1, 0xC0F9);
    SpriteSystem_LoadCellResObj(view->spriteSystem, view->spriteManager, NARC_poketool_icongra_poke_icon, GetMonIconCell64KNaix(), FALSE, 0xC0F9);
    SpriteSystem_LoadAnimResObj(view->spriteSystem, view->spriteManager, NARC_poketool_icongra_poke_icon, GetMonIconAnim64KNaix(), FALSE, 0xC0F9);
}

static void PCBox_CreateMonIconSprites(PCBoxView *view) {
    ManagedSpriteTemplate template;
    ManagedSpriteTemplate base;
    int priority;
    u32 i;
    u8 *slot;

    i = 0;
    priority = 0;
    slot = (u8 *)view;
    base = gPCBoxMonIconSpriteTemplate;
    for (; i < PC_BOX_SLOT_COUNT; i++) {
        template = base;
        template.x += 24 * (i % 6);
        template.y += 24 * (i / 6);
        template.drawPriority = 0x74 - priority;
        template.resIdList[0] = 0xC0F9 + i;
        *(ManagedSprite **)(slot + offsetof(PCBoxView, sprites[PC_BOX_SPRITE_MON_ICONS])) = SpriteSystem_NewSprite(view->spriteSystem, view->spriteManager, &template);
        view->slotIcons[i] = i + PC_BOX_SPRITE_MON_ICONS;
        priority += 2;
        slot += sizeof(ManagedSprite *);
    }
}

static void *PCBox_LoadMonIconChars(PCBoxView *view, BoxPokemon *boxMon, NNSG2dCharacterData **charData) {
    return GfGfxLoader_GetCharDataFromOpenNarc(view->iconNarc, Boxmon_GetIconNaix(boxMon), FALSE, charData, HEAP_ID_10);
}

// Keeps the icon graphics of a box (for the scroll animation between boxes).
void PCBox_LoadBoxIconImages(PCBoxWork *work, int box) {
    u32 i;
    NNSG2dCharacterData *charData;
    void *allocation;
    BoxPokemon *boxMon;

    for (i = 0; i < MONS_PER_BOX; i++) {
        if (!PCStorage_GetMonDataByIndexPair(work->storage, box, i, MON_DATA_SPECIES_EXISTS, NULL)) {
            work->view->iconDraw[i] = 0;
        } else {
            boxMon = PCBox_GetSlotBoxMon(work, box, i);
            allocation = PCBox_LoadMonIconChars(work->view, boxMon, &charData);
            MI_CpuCopy32(charData->pRawData, work->view->iconChars[i], 0x200);
            Heap_Free(allocation);
            work->view->iconPalettes[i] = Boxmon_GetIconPalette(boxMon);
            work->view->iconDraw[i] = 1;
        }
    }
}

static void PCBox_SetIconImage(PCBoxView *view, void *src, int index, int palette) {
    PCBox_LoadSpriteCharsMain(view, index, src, 0x200);
    ManagedSprite_SetPaletteOverride(view->sprites[index], palette + 3);
}

static void PCBox_LoadMonIcon(PCBoxWork *work, BoxPokemon *boxMon, int index) {
    NNSG2dCharacterData *charData;
    void *allocation = PCBox_LoadMonIconChars(work->view, boxMon, &charData);
    int palette = Boxmon_GetIconPalette(boxMon);

    PCBox_SetIconImage(work->view, charData->pRawData, index, palette);
    Heap_Free(allocation);
}

void PCBox_RefreshSlotIcon(PCBoxWork *work, int box, int slot, int index) {
    ManagedSprite **sprites = work->view->sprites;

    ManagedSprite_SetDrawFlag(sprites[index], FALSE);
    if (PCBox_GetSlotMonData(work, slot, MON_DATA_SPECIES_EXISTS, NULL)) {
        PCBox_LoadMonIcon(work, PCBox_GetSlotBoxMon(work, box, slot), index);
        ManagedSprite_SetDrawFlag(sprites[index], TRUE);
    }
}

void PCBox_LoadBoxIcons(PCBoxWork *work) {
    u32 i;

    for (i = 0; i < MONS_PER_BOX; i++) {
        PCBox_RefreshSlotIcon(work, work->activeBox, i, i + 25);
    }
}

void PCBox_LoadPartyIcons(PCBoxWork *work) {
    u32 count = Party_GetCount(work->party);
    u32 i;

    for (i = 0; i < count; i++) {
        BoxPokemon *boxMon = Mon_GetBoxMon(Party_GetMonByIndex(work->party, i));
        PCBox_LoadMonIcon(work, boxMon, work->view->slotIcons[PC_BOX_SLOT_PARTY_START + i]);
        PCBox_SetSpriteVisible(work->view, work->view->slotIcons[PC_BOX_SLOT_PARTY_START + i], FALSE);
    }
}

void PCBox_GetSlotPosition(u32 slot, s16 *x, s16 *y, int partyLayout) {
    if (slot < PC_BOX_SLOT_PARTY_START) {
        *x = (slot % 6 + 1) * 24;
        *y = (slot / 6) * 24 + 48;
    } else {
        slot -= PC_BOX_SLOT_PARTY_START;
        *x = gPCBoxPartySlotPositions[slot].x;
        *y = gPCBoxPartySlotPositions[slot].y - 144;
        if (partyLayout == 2) {
            *x += 152;
        }
    }
}

void PCBox_PlacePartyIconsLeftHidden(PCBoxWork *work) {
    u32 count;
    u32 i;
    const PCBoxScreenPos *pos;

    count = Party_GetCount(work->party);
    pos = gPCBoxPartySlotPositions;
    for (i = 0; i < PARTY_SIZE; i++, pos++) {
        u8 index = work->view->slotIcons[PC_BOX_SLOT_PARTY_START + i];
        ManagedSprite_SetPositionXY(work->view->sprites[index], pos->x + 0, pos->y + 0);
        PCBox_SetIconLayer(work->view, PC_BOX_SLOT_PARTY_START + i, TRUE);
        if (i < count) {
            PCBox_SetSpriteVisible(work->view, index, TRUE);
        } else {
            PCBox_SetSpriteVisible(work->view, index, FALSE);
        }
    }
}

void PCBox_PlacePartyIconsRightHidden(PCBoxWork *work) {
    u32 count;
    u32 i;
    const PCBoxScreenPos *pos;

    count = Party_GetCount(work->party);
    pos = gPCBoxPartySlotPositions;
    for (i = 0; i < PARTY_SIZE; i++, pos++) {
        u8 index = work->view->slotIcons[PC_BOX_SLOT_PARTY_START + i];
        ManagedSprite_SetPositionXY(work->view->sprites[index], pos->x + 152, pos->y + 0);
        PCBox_SetIconLayer(work->view, PC_BOX_SLOT_PARTY_START + i, TRUE);
        if (i < count) {
            PCBox_SetSpriteVisible(work->view, index, TRUE);
        } else {
            PCBox_SetSpriteVisible(work->view, index, FALSE);
        }
    }
}

void PCBox_PlacePartyIconsLeft(PCBoxWork *work) {
    u32 count;
    u32 i;
    const PCBoxScreenPos *pos;

    count = Party_GetCount(work->party);
    pos = gPCBoxPartySlotPositions;
    for (i = 0; i < PARTY_SIZE; i++, pos++) {
        u8 index = work->view->slotIcons[PC_BOX_SLOT_PARTY_START + i];
        ManagedSprite_SetPositionXY(work->view->sprites[index], pos->x + 0, pos->y + -144);
        PCBox_SetIconLayer(work->view, PC_BOX_SLOT_PARTY_START + i, TRUE);
        if (i < count) {
            PCBox_SetSpriteVisible(work->view, index, TRUE);
        } else {
            PCBox_SetSpriteVisible(work->view, index, FALSE);
        }
    }
}

void PCBox_PlacePartyIconsRight(PCBoxWork *work) {
    u32 count;
    u32 i;
    const PCBoxScreenPos *pos;

    count = Party_GetCount(work->party);
    pos = gPCBoxPartySlotPositions;
    for (i = 0; i < PARTY_SIZE; i++, pos++) {
        u8 index = work->view->slotIcons[PC_BOX_SLOT_PARTY_START + i];
        ManagedSprite_SetPositionXY(work->view->sprites[index], pos->x + 152, pos->y + -144);
        PCBox_SetIconLayer(work->view, PC_BOX_SLOT_PARTY_START + i, TRUE);
        if (i < count) {
            PCBox_SetSpriteVisible(work->view, index, TRUE);
        } else {
            PCBox_SetSpriteVisible(work->view, index, FALSE);
        }
    }
}

void PCBox_SetIconLayer(PCBoxView *view, u32 slot, BOOL active) {
    int index = view->slotIcons[slot];

    if (!active) {
        PCBox_SetSpritePriority(view, index, 0);
        PCBox_SetSpriteDrawPriority(view, index, 0x14);
        return;
    }
    if (slot < PC_BOX_SLOT_PARTY_START) {
        PCBox_SetSpritePriority(view, index, 3);
    } else {
        PCBox_SetSpritePriority(view, index, 1);
    }
    PCBox_SetSpriteDrawPriority(view, index, 0x74 - 2 * slot);
}

void PCBox_SetMovingIconPriority(PCBoxView *view, int slot, u32 target) {
    int index = view->slotIcons[slot];

    if (target < PC_BOX_SLOT_PARTY_START) {
        PCBox_SetSpritePriority(view, index, 3);
    } else {
        PCBox_SetSpritePriority(view, index, 1);
    }
    PCBox_SetSpriteDrawPriority(view, index, 0x14);
}

// Scrolls the box icons sideways; an icon leaving the box reappears on the other side with the graphics of the box
// being scrolled in (PCBox_LoadBoxIconImages).
void PCBox_ScrollBoxIcons(PCBoxWork *work, s32 amount) {
    s16 wrap;
    s16 stop;
    u16 i;

    struct {
        s16 y, x;
    } position;

    if (amount >= 0) {
        stop = 176;
        wrap = -8;
    } else {
        stop = -8;
        wrap = 176;
    }
    for (i = 0; i < MONS_PER_BOX; i++) {
        int index = work->view->slotIcons[i];
        ManagedSprite_GetPositionXY(work->view->sprites[index], &position.x, &position.y);
        position.x += amount;
        if (position.x == stop) {
            position.x = wrap;
            PCBox_SetIconImage(work->view, work->view->iconChars[i], index, work->view->iconPalettes[i]);
            ManagedSprite_SetDrawFlag(work->view->sprites[index], work->view->iconDraw[i]);
            if (work->args->mode == PC_BOX_MODE_MOVE_ITEMS) {
                PCBox_UpdateSlotIconItemTranslucency(work, i);
            }
        }
        ManagedSprite_SetPositionXY(work->view->sprites[index], position.x, position.y);
    }
}

void PCBox_UpdatePartyIconPositions(PCBoxWork *work) {
    s8 cell[2];
    s16 x, y;
    u16 i;

    BgCellManager_GetCellPosition(work->view->panels, PC_BOX_PANEL_PARTY, &cell[1], &cell[0]);
    y = cell[0] * 8;
    x = cell[1] * 8;
    for (i = 0; i < PARTY_SIZE; i++) {
        ManagedSprite_SetPositionXY(work->view->sprites[work->view->slotIcons[PC_BOX_SLOT_PARTY_START + i]], x + gPCBoxPartyIconOffsets[i][0], y + gPCBoxPartyIconOffsets[i][1]);
    }
}

void PCBox_StartReleaseScale(PCBoxReleaseWork *releaseWork) {
    releaseWork->scale = 1.0f;
    releaseWork->scaleCounter = 0;
    ManagedSprite_SetAffineOverwriteMode(releaseWork->sprite, 1);
    ManagedSprite_SetAffineScale(releaseWork->sprite, releaseWork->scale, releaseWork->scale);
    ManagedSprite_SetAffineTranslation(releaseWork->sprite, 0, 8);
}

BOOL PCBox_UpdateReleaseShrink(PCBoxReleaseWork *releaseWork) {
    releaseWork->scaleCounter++;
    releaseWork->scale -= 0.025f;
    if (releaseWork->scaleCounter == 40) {
        return FALSE;
    }
    ManagedSprite_SetAffineScale(releaseWork->sprite, releaseWork->scale, releaseWork->scale);
    return TRUE;
}

BOOL PCBox_UpdateReleaseGrow(PCBoxReleaseWork *releaseWork) {
    releaseWork->scaleCounter -= 2;
    releaseWork->scale += 0.025f;
    releaseWork->scale += 0.025f;
    if (releaseWork->scaleCounter == 0) {
        return FALSE;
    }
    ManagedSprite_SetAffineScale(releaseWork->sprite, releaseWork->scale, releaseWork->scale);
    return TRUE;
}

void PCBox_EndReleaseShrink(PCBoxReleaseWork *releaseWork) {
    ManagedSprite_SetDrawFlag(releaseWork->sprite, FALSE);
    PCBox_ResetSpriteAffine(releaseWork);
}

void PCBox_ResetSpriteAffine(PCBoxReleaseWork *releaseWork) {
    ManagedSprite_SetAffineTranslation(releaseWork->sprite, 0, 0);
    ManagedSprite_SetAffineScale(releaseWork->sprite, 1.0f, 1.0f);
    ManagedSprite_SetAffineOverwriteMode(releaseWork->sprite, 0);
}

// Item mode: icons of mons without a held item are translucent (check == 1), or all icons get ENABLED.
static void PCBox_SetIconRangeTranslucent(PCBoxWork *work, u32 enabled, u32 first, u32 end, u32 check) {
    if (check == 1) {
        for (; first < end; first++) {
            if (PCBox_GetSlotMonData(work, first, MON_DATA_HELD_ITEM, NULL) == ITEM_NONE) {
                PCBox_SetSpriteTranslucent(work->view, work->view->slotIcons[first], 1);
            } else {
                PCBox_SetSpriteTranslucent(work->view, work->view->slotIcons[first], 0);
            }
        }
    } else {
        for (; first < end; first++) {
            PCBox_SetSpriteTranslucent(work->view, work->view->slotIcons[first], enabled);
        }
    }
}

// FLAGS: 1 box icons, 2 party icons, 0x80 by held item.
void PCBox_SetIconsTranslucent(PCBoxWork *work, u32 flags, u32 enabled) {
    u32 check = (flags & 0x80) != 0;

    if (flags & 1) {
        PCBox_SetIconRangeTranslucent(work, enabled, 0, PC_BOX_SLOT_PARTY_START, check);
    }
    if (flags & 2) {
        PCBox_SetIconRangeTranslucent(work, enabled, PC_BOX_SLOT_PARTY_START, PC_BOX_SLOT_COUNT, check);
    }
}

void PCBox_SetSlotIconTranslucent(PCBoxView *view, u32 slot, u32 enabled) {
    PCBox_SetSpriteTranslucent(view, view->slotIcons[slot], enabled);
}

static void PCBox_UpdateSlotIconItemTranslucency(PCBoxWork *work, u32 slot) {
    PCBox_SetIconRangeTranslucent(work, 1, slot, slot + 1, 1);
}

static void PCBox_LoadMonPicResources(PCBoxView *view) {
    SpriteSystem_LoadCharResObj(view->spriteSystem, view->spriteManager, NARC_a_0_0_8, 0x4c, FALSE, 2, 0xc11d);
    SpriteSystem_LoadCharResObj(view->spriteSystem, view->spriteManager, NARC_a_0_0_8, 0x4c, FALSE, 2, 0xc11e);
    SpriteSystem_LoadPlttResObj(view->spriteSystem, view->spriteManager, NARC_a_0_0_8, 0x4b, FALSE, 1, 2, 0xc0fa);
    SpriteSystem_LoadPlttResObj(view->spriteSystem, view->spriteManager, NARC_a_0_0_8, 0x4b, FALSE, 1, 2, 0xc0fb);
    SpriteSystem_LoadCellResObj(view->spriteSystem, view->spriteManager, NARC_a_0_0_8, 0x4d, FALSE, 0xc0fa);
    SpriteSystem_LoadAnimResObj(view->spriteSystem, view->spriteManager, NARC_a_0_0_8, 0x4e, FALSE, 0xc0fa);
}

static void PCBox_CreateMonPicSprites(PCBoxWork *work) {
    PCBoxView *view = work->view;

    view->sprites[PC_BOX_SPRITE_MON_PIC] = SpriteSystem_NewSpriteWithYOffset(view->spriteSystem, view->spriteManager, &gPCBoxMonPicSprite2Template, 2 << 20);
    view->sprites[PC_BOX_SPRITE_MON_PIC + 1] = SpriteSystem_NewSpriteWithYOffset(view->spriteSystem, view->spriteManager, &gPCBoxMonPicSprite3Template, 2 << 20);
    ManagedSprite_SetDrawFlag(view->sprites[PC_BOX_SPRITE_MON_PIC], FALSE);
    ManagedSprite_SetDrawFlag(view->sprites[PC_BOX_SPRITE_MON_PIC + 1], FALSE);
}

static void PCBox_LoadMonPic(PCBoxView *view, PCBoxMonInfo *monInfo, u32 index) {
    PokepicTemplate pic;
    TileRect dims = gPCBoxMonPicRect;
    void *buf;
    u32 location;
    u16 species;

    buf = Heap_AllocAtEnd(HEAP_ID_10, 0xc80);
    GetBoxmonSpriteCharAndPlttNarcIds(&pic, monInfo->boxMon, 2, FALSE);
    if (monInfo->isEgg == 1 && monInfo->species == SPECIES_SPINDA) {
        species = SPECIES_EGG;
    } else {
        species = monInfo->species;
    }
    CharTiles_LoadMonRectAsObjFromNarc((NarcId)pic.narcID, pic.charDataID, HEAP_ID_10, &dims, buf, monInfo->personality, FALSE, 2, species);
    location = NNS_G2dGetImageLocation(Sprite_GetImageProxy(view->sprites[index]->sprite), NNS_G2D_VRAM_TYPE_2DSUB);
    DC_FlushRange(buf, 0xc80);
    GXS_LoadOBJ(buf, location, 0xc80);
    location = NNS_G2dGetImagePaletteLocation(Sprite_GetPaletteProxy(view->sprites[index]->sprite), NNS_G2D_VRAM_TYPE_2DSUB);
    GfGfxLoader_GXLoadPal((NarcId)pic.narcID, pic.palDataID, GF_PAL_LOCATION_SUB_OBJ, (enum GFPalSlotOffset)location, 0x20, HEAP_ID_10);
    Heap_Free(buf);
}

void PCBox_ShowMonPic(PCBoxWork *work, PCBoxMonInfo *monInfo, u32 index) {
    index += work->view->monPicBuffer;
    PCBox_LoadMonPic(work->view, monInfo, index);
    ManagedSprite_SetDrawFlag(work->view->sprites[index], TRUE);
    work->view->monPicBuffer ^= 1;
}

static void PCBox_LoadItemIconResources(PCBoxView *view) {
    u32 fileId;

    SpriteSystem_LoadCharResObj(view->spriteSystem, view->spriteManager, NARC_a_0_1_9, 0x4f, TRUE, 1, 0xc11f);
    fileId = GetItemIndexMapping(ITEM_NONE, ITEMNARC_NCLR);
    SpriteSystem_LoadPlttResObj(view->spriteSystem, view->spriteManager, NARC_itemtool_itemdata_item_icon, fileId, FALSE, 1, 1, 0xc0fc);
    SpriteSystem_LoadCharResObj(view->spriteSystem, view->spriteManager, NARC_a_0_1_9, 0x4f, TRUE, 2, 0xc120);
    fileId = GetItemIndexMapping(ITEM_NONE, ITEMNARC_NCLR);
    SpriteSystem_LoadPlttResObj(view->spriteSystem, view->spriteManager, NARC_itemtool_itemdata_item_icon, fileId, FALSE, 1, 2, 0xc0fd);
    SpriteSystem_LoadCellResObj(view->spriteSystem, view->spriteManager, NARC_a_0_1_9, 0x50, TRUE, 0xc0fb);
    SpriteSystem_LoadAnimResObj(view->spriteSystem, view->spriteManager, NARC_a_0_1_9, 0x51, TRUE, 0xc0fb);
}

static void PCBox_CreateItemIconSprites(PCBoxView *view) {
    view->sprites[PC_BOX_SPRITE_HELD_ITEM] = SpriteSystem_NewSprite(view->spriteSystem, view->spriteManager, &gPCBoxItemIconSpriteTemplate);
    ManagedSprite_SetDrawFlag(view->sprites[PC_BOX_SPRITE_HELD_ITEM], FALSE);
    view->sprites[PC_BOX_SPRITE_INFO_ITEM] = SpriteSystem_NewSpriteWithYOffset(view->spriteSystem, view->spriteManager, &gPCBoxItemIconSprite12Template, 2 << 20);
    ManagedSprite_SetDrawFlag(view->sprites[PC_BOX_SPRITE_INFO_ITEM], FALSE);
}

void PCBox_LoadHeldItemIcon(PCBoxView *view, u16 item) {
    NNSG2dCharacterData *charData;
    void *buf;
    u32 location;

    buf = GfGfxLoader_GetCharData(NARC_itemtool_itemdata_item_icon, GetItemIndexMapping(item, ITEMNARC_NCGR), FALSE, &charData, HEAP_ID_10);
    PCBox_LoadSpriteCharsMain(view, PC_BOX_SPRITE_HELD_ITEM, charData->pRawData, 0x200);
    Heap_Free(buf);
    location = NNS_G2dGetImagePaletteLocation(Sprite_GetPaletteProxy(view->sprites[PC_BOX_SPRITE_HELD_ITEM]->sprite), NNS_G2D_VRAM_TYPE_2DMAIN);
    GfGfxLoader_GXLoadPal(NARC_itemtool_itemdata_item_icon, GetItemIndexMapping(item, ITEMNARC_NCLR), GF_PAL_LOCATION_MAIN_OBJ, (enum GFPalSlotOffset)location, 0x20, HEAP_ID_10);
}

void PCBox_LoadInfoItemIcon(PCBoxView *view, u16 item) {
    NNSG2dCharacterData *charData;
    void *buf;
    u32 location;

    buf = GfGfxLoader_GetCharData(NARC_itemtool_itemdata_item_icon, GetItemIndexMapping(item, ITEMNARC_NCGR), FALSE, &charData, HEAP_ID_10);
    PCBox_LoadSpriteCharsSub(view, PC_BOX_SPRITE_INFO_ITEM, charData->pRawData, 0x200);
    Heap_Free(buf);
    location = NNS_G2dGetImagePaletteLocation(Sprite_GetPaletteProxy(view->sprites[PC_BOX_SPRITE_INFO_ITEM]->sprite), NNS_G2D_VRAM_TYPE_2DSUB);
    GfGfxLoader_GXLoadPal(NARC_itemtool_itemdata_item_icon, GetItemIndexMapping(item, ITEMNARC_NCLR), GF_PAL_LOCATION_SUB_OBJ, (enum GFPalSlotOffset)location, 0x20, HEAP_ID_10);
}

void PCBox_SetHeldItemIconAffine(PCBoxView *view, u32 on) {
    if (on == 1) {
        ManagedSprite_SetAffineOverwriteMode(view->sprites[PC_BOX_SPRITE_HELD_ITEM], 1);
        ManagedSprite_SetAffineTranslation(view->sprites[PC_BOX_SPRITE_HELD_ITEM], 12, 12);
    } else {
        ManagedSprite_SetAffineTranslation(view->sprites[PC_BOX_SPRITE_HELD_ITEM], 0, 0);
        ManagedSprite_SetAffineOverwriteMode(view->sprites[PC_BOX_SPRITE_HELD_ITEM], 0);
    }
}

void PCBox_SetHeldItemIconPosition(PCBoxView *view, s16 x, s16 y) {
    ManagedSprite_SetPositionXY(view->sprites[PC_BOX_SPRITE_HELD_ITEM], x, y);
}

void PCBox_MoveHeldItemIconToSlot(PCBoxView *view, u32 slot, u32 partyLayout) {
    s16 pos[2];

    PCBox_GetSlotPosition(slot, &pos[1], &pos[0], partyLayout);
    PCBox_SetHeldItemIconPosition(view, (s16)(pos[1] + 8), (s16)(pos[0] + 8));
}

void PCBox_PlaceHeldItemIconAtSlot(PCBoxView *view, u32 slot, u32 partyLayout) {
    s16 pos[2];

    PCBox_GetSlotPosition(slot, &pos[1], &pos[0], partyLayout);
    PCBox_SetHeldItemIconPosition(view, pos[1], (s16)(pos[0] + 4));
}

void PCBox_CreateHeldItemIconOutline(PCBoxView *view) {
    ManagedSpriteTemplate template;
    s16 x, y;
    u32 i, priority, drawPriority;

    if (view->heldItem == ITEM_NONE) {
        return;
    }
    ManagedSprite_GetPositionXY(view->sprites[PC_BOX_SPRITE_HELD_ITEM], &x, &y);
    if (view->sprites[PC_BOX_SPRITE_OUTLINE] == NULL) {
        template = gPCBoxItemIconSpriteTemplate;
        template.drawPriority = ManagedSprite_GetDrawPriority(view->sprites[PC_BOX_SPRITE_HELD_ITEM]) + 1;
        template.bgPriority = ManagedSprite_GetPriority(view->sprites[PC_BOX_SPRITE_HELD_ITEM]);
        template.resIdList[0] = 0xc11f;
        view->spriteDrawLock = 1;
        for (i = 0; i < 8; i++) {
            template.x = x + gPCBoxOutlineOffsetsX[i];
            template.y = y + gPCBoxOutlineOffsetsY[i];
            view->sprites[PC_BOX_SPRITE_OUTLINE + i] = SpriteSystem_NewSprite(view->spriteSystem, view->spriteManager, &template);
            ManagedSprite_SetPaletteOverride(view->sprites[PC_BOX_SPRITE_OUTLINE + i], 8);
            ManagedSprite_SetDrawFlag(view->sprites[PC_BOX_SPRITE_OUTLINE + i], FALSE);
        }
        view->spriteDrawLock = 0;
    } else {
        drawPriority = ManagedSprite_GetDrawPriority(view->sprites[PC_BOX_SPRITE_HELD_ITEM]);
        priority = ManagedSprite_GetPriority(view->sprites[PC_BOX_SPRITE_HELD_ITEM]);
        for (i = 0; i < 8; i++) {
            ManagedSprite_SetPositionXY(view->sprites[PC_BOX_SPRITE_OUTLINE + i], x + gPCBoxOutlineOffsetsX[i], y + gPCBoxOutlineOffsetsY[i]);
            PCBox_SetSpriteDrawPriority(view, PC_BOX_SPRITE_OUTLINE + i, drawPriority + 1);
            ManagedSprite_SetPriority(view->sprites[PC_BOX_SPRITE_OUTLINE + i], priority);
            ManagedSprite_SetDrawFlag(view->sprites[PC_BOX_SPRITE_OUTLINE + i], FALSE);
        }
    }
}

void PCBox_ShowHeldItemIconOutline(PCBoxView *view) {
    u32 i;

    for (i = 0; i < 8; i++) {
        ManagedSprite_SetDrawFlag(view->sprites[PC_BOX_SPRITE_OUTLINE + i], TRUE);
    }
}

void PCBox_UpdateHeldItemIconOutline(PCBoxView *view) {
    s16 pos[2];
    u32 i;

    ManagedSprite_GetPositionXY(view->sprites[PC_BOX_SPRITE_HELD_ITEM], &pos[1], &pos[0]);
    if (view->sprites[PC_BOX_SPRITE_OUTLINE] != NULL) {
        for (i = 0; i < 8; i++) {
            ManagedSprite_SetPositionXY(view->sprites[PC_BOX_SPRITE_OUTLINE + i], pos[1] + gPCBoxOutlineOffsetsX[i], pos[0] + gPCBoxOutlineOffsetsY[i]);
        }
    }
}

void PCBox_UpdateInfoItemIconPosition(PCBoxView *view) {
    s8 cell[2];

    BgCellManager_GetCellPosition(view->panels, PC_BOX_PANEL_INFO, &cell[1], &cell[0]);
    ManagedSprite_SetPositionXY(view->sprites[PC_BOX_SPRITE_INFO_ITEM], 18, cell[0] * 8 + 360);
    ManagedSprite_SetDrawFlag(view->sprites[PC_BOX_SPRITE_INFO_ITEM], TRUE);
}

static void PCBox_LoadTypeIconResources(PCBoxView *view) {
    SpriteSystem_LoadCharResObj(view->spriteSystem, view->spriteManager, NARC_a_0_1_9, 0x52, TRUE, 2, 0xc121);
    SpriteSystem_LoadCharResObj(view->spriteSystem, view->spriteManager, NARC_a_0_1_9, 0x52, TRUE, 2, 0xc122);
    SpriteSystem_LoadPlttResObj(view->spriteSystem, view->spriteManager, NARC_a_0_0_8, 0x4a, FALSE, 3, 2, 0xc0fe);
    SpriteSystem_LoadCellResObj(view->spriteSystem, view->spriteManager, NARC_a_0_1_9, 0x53, TRUE, 0xc0fc);
    SpriteSystem_LoadAnimResObj(view->spriteSystem, view->spriteManager, NARC_a_0_1_9, 0x54, TRUE, 0xc0fc);
}

static void PCBox_CreateTypeIconSprites(PCBoxView *view) {
    view->sprites[PC_BOX_SPRITE_TYPE_ICONS] = SpriteSystem_NewSpriteWithYOffset(view->spriteSystem, view->spriteManager, &gPCBoxTypeIconSprite13Template, 2 << 20);
    view->sprites[PC_BOX_SPRITE_TYPE_ICONS + 1] = SpriteSystem_NewSpriteWithYOffset(view->spriteSystem, view->spriteManager, &gPCBoxTypeIconSprite14Template, 2 << 20);
    ManagedSprite_SetDrawFlag(view->sprites[PC_BOX_SPRITE_TYPE_ICONS], FALSE);
    ManagedSprite_SetDrawFlag(view->sprites[PC_BOX_SPRITE_TYPE_ICONS + 1], FALSE);
}

static void PCBox_LoadTypeIcon(PCBoxView *view, u32 type, u32 index, u32 resourceId) {
    NNSG2dCharacterData *charData;
    void *buf;
    u32 palette;

    buf = GfGfxLoader_GetCharData(TypeIcon_GetNarc(), TypeIcon_GetCharFile(type), TRUE, &charData, HEAP_ID_10);
    PCBox_LoadSpriteCharsSub(view, index, charData->pRawData, 0x100);
    Heap_Free(buf);
    palette = ManagedSprite_GetPaletteOverrideOffset(view->sprites[index]);
    ManagedSprite_SetPaletteOverride(view->sprites[index], palette + TypeIcon_GetPalette(type));
}

void PCBox_DrawTypeIcons(PCBoxView *view, PCBoxMonInfo *monInfo) {
    if (monInfo->isEgg != 0) {
        ManagedSprite_SetDrawFlag(view->sprites[PC_BOX_SPRITE_TYPE_ICONS], FALSE);
        ManagedSprite_SetDrawFlag(view->sprites[PC_BOX_SPRITE_TYPE_ICONS + 1], FALSE);
        return;
    }
    PCBox_LoadTypeIcon(view, monInfo->type1, 13, 0xc121);
    ManagedSprite_SetDrawFlag(view->sprites[PC_BOX_SPRITE_TYPE_ICONS], TRUE);
    if (monInfo->type2 != 0 && monInfo->type1 != monInfo->type2) {
        PCBox_LoadTypeIcon(view, monInfo->type2, 14, 0xc122);
        ManagedSprite_SetDrawFlag(view->sprites[PC_BOX_SPRITE_TYPE_ICONS + 1], TRUE);
    } else {
        ManagedSprite_SetDrawFlag(view->sprites[PC_BOX_SPRITE_TYPE_ICONS + 1], FALSE);
    }
}

static void PCBox_LoadUiSpriteResources(PCBoxView *view) {
    SpriteSystem_LoadCharResObj(view->spriteSystem, view->spriteManager, NARC_a_0_1_9, 0x42, TRUE, 1, 0xc12d);
    SpriteSystem_LoadPlttResObj(view->spriteSystem, view->spriteManager, NARC_a_0_1_9, 0x45, FALSE, 3, 1, 0xc101);
    SpriteSystem_LoadCellResObj(view->spriteSystem, view->spriteManager, NARC_a_0_1_9, 0x43, TRUE, 0xc0ff);
    SpriteSystem_LoadAnimResObj(view->spriteSystem, view->spriteManager, NARC_a_0_1_9, 0x44, TRUE, 0xc0ff);
}

static void PCBox_CreateUiSprites(PCBoxView *view) {
    view->sprites[PC_BOX_SPRITE_PREV_BOX_ARROW] = SpriteSystem_NewSprite(view->spriteSystem, view->spriteManager, &gPCBoxUiSprite0Template);
    view->sprites[PC_BOX_SPRITE_NEXT_BOX_ARROW] = SpriteSystem_NewSprite(view->spriteSystem, view->spriteManager, &gPCBoxUiSprite1Template);
    view->sprites[PC_BOX_SPRITE_TRAY_PREV_ARROW] = SpriteSystem_NewSprite(view->spriteSystem, view->spriteManager, &gPCBoxUiSprite4Template);
    view->sprites[PC_BOX_SPRITE_TRAY_NEXT_ARROW] = SpriteSystem_NewSprite(view->spriteSystem, view->spriteManager, &gPCBoxUiSprite5Template);
    view->sprites[PC_BOX_SPRITE_TRAY_MARKER] = SpriteSystem_NewSprite(view->spriteSystem, view->spriteManager, &gPCBoxUiSprite6Template);
    view->sprites[PC_BOX_SPRITE_TRAY_CURSOR] = SpriteSystem_NewSprite(view->spriteSystem, view->spriteManager, &gPCBoxUiSprite7Template);
    view->sprites[PC_BOX_SPRITE_TRAY_LABEL] = SpriteSystem_NewSprite(view->spriteSystem, view->spriteManager, &gPCBoxUiSprite8Template);
    view->sprites[PC_BOX_SPRITE_CURSOR] = SpriteSystem_NewSprite(view->spriteSystem, view->spriteManager, &gPCBoxUiSprite9Template);
    view->sprites[PC_BOX_SPRITE_UNUSED] = SpriteSystem_NewSprite(view->spriteSystem, view->spriteManager, &gPCBoxUiSprite10Template);
    PCBox_SetSpriteVisible(view, PC_BOX_SPRITE_UNUSED, FALSE);
}

void PCBox_CreateSelectedIconOutline(PCBoxWork *work) {
    ManagedSpriteTemplate template;
    s16 x, y;
    PCBoxView *view;
    u32 index;
    u16 i;
    u32 drawPriority, priority;
    NNSG2dImageProxy *proxy;

    if (work->selectedSlot == PC_BOX_SLOT_NONE) {
        return;
    }
    view = work->view;
    index = view->slotIcons[work->selectedSlot];
    ManagedSprite_GetPositionXY(view->sprites[index], &x, &y);
    if (view->sprites[PC_BOX_SPRITE_OUTLINE] == NULL) {
        template = gPCBoxMonIconSpriteTemplate;
        template.drawPriority = ManagedSprite_GetDrawPriority(view->sprites[index]) + 1;
        template.bgPriority = ManagedSprite_GetPriority(view->sprites[index]);
        template.resIdList[0] = 0xc0e0 + index;
        view->spriteDrawLock = 1;
        for (i = 0; i < 8; i++) {
            template.x = x + gPCBoxOutlineOffsetsX[i];
            template.y = y + gPCBoxOutlineOffsetsY[i];
            view->sprites[PC_BOX_SPRITE_OUTLINE + i] = SpriteSystem_NewSprite(view->spriteSystem, view->spriteManager, &template);
            ManagedSprite_SetPaletteOverride(view->sprites[PC_BOX_SPRITE_OUTLINE + i], 8);
        }
        view->spriteDrawLock = 0;
    } else {
        proxy = Sprite_GetImageProxy(view->sprites[index]->sprite);
        drawPriority = ManagedSprite_GetDrawPriority(view->sprites[index]);
        priority = ManagedSprite_GetPriority(view->sprites[index]);
        for (i = 0; i < 8; i++) {
            Sprite_SetImageProxy(view->sprites[PC_BOX_SPRITE_OUTLINE + i]->sprite, proxy);
            ManagedSprite_SetPositionXY(view->sprites[PC_BOX_SPRITE_OUTLINE + i], x + gPCBoxOutlineOffsetsX[i], y + gPCBoxOutlineOffsetsY[i]);
            PCBox_SetSpriteDrawPriority(work->view, PC_BOX_SPRITE_OUTLINE + i, drawPriority + 1);
            ManagedSprite_SetPriority(work->view->sprites[PC_BOX_SPRITE_OUTLINE + i], priority);
            ManagedSprite_SetDrawFlag(work->view->sprites[PC_BOX_SPRITE_OUTLINE + i], TRUE);
        }
    }
}

void PCBox_HideSelectedIconOutline(PCBoxWork *work) {
    PCBox_SetSelectedIconOutlineVisible(work, 0);
}

void PCBox_SetSelectedIconOutlineVisible(PCBoxWork *work, u32 visible) {
    u32 i;

    if (visible == 1) {
        visible = 1;
    } else {
        visible = 0;
    }
    for (i = 0; i < 8; i++) {
        ManagedSprite *piece = work->view->sprites[PC_BOX_SPRITE_OUTLINE + i];
        if (piece != NULL) {
            ManagedSprite_SetDrawFlag(piece, visible);
            if (visible == 1) {
                u32 slot = work->selectedSlot;
                if (slot != PC_BOX_SLOT_NONE) {
                    u32 index = work->view->slotIcons[slot];
                    u32 drawPriority = ManagedSprite_GetDrawPriority(work->view->sprites[index]);
                    PCBox_SetSpriteDrawPriority(work->view, PC_BOX_SPRITE_OUTLINE + i, drawPriority + 1);
                    ManagedSprite_SetPriority(work->view->sprites[PC_BOX_SPRITE_OUTLINE + i], ManagedSprite_GetPriority(work->view->sprites[index]));
                }
            }
        }
    }
}

void PCBox_UpdateSelectedIconOutline(PCBoxWork *work) {
    PCBoxView *view;
    u16 i;
    s16 x;
    s16 y;
    u32 slot = work->selectedSlot;

    if (slot == PC_BOX_SLOT_NONE) {
        return;
    }
    view = work->view;
    ManagedSprite_GetPositionXY(view->sprites[view->slotIcons[slot]], &x, &y);
    for (i = 0; i < 8; i++) {
        ManagedSprite_SetPositionXY(view->sprites[PC_BOX_SPRITE_OUTLINE + i], x + gPCBoxOutlineOffsetsX[i], y + gPCBoxOutlineOffsetsY[i]);
    }
}

static void PCBox_LoadTrayBoxResources(PCBoxView *view) {
    u32 i;

    for (i = 0; i < PC_BOX_TRAY_BOX_COUNT; i++) {
        SpriteSystem_LoadCharResObj(view->spriteSystem, view->spriteManager, NARC_a_0_1_9, 0x46, FALSE, 1, 0xc123 + i);
    }
    SpriteSystem_LoadPlttResObj(view->spriteSystem, view->spriteManager, NARC_a_0_1_9, 0x47, FALSE, 1, 1, 0xc0ff);
    SpriteSystem_LoadCellResObj(view->spriteSystem, view->spriteManager, NARC_a_0_1_9, 0x48, TRUE, 0xc0fd);
    SpriteSystem_LoadAnimResObj(view->spriteSystem, view->spriteManager, NARC_a_0_1_9, 0x49, TRUE, 0xc0fd);
}

static void PCBox_CreateTrayBoxSprites(PCBoxView *view) {
    ManagedSpriteTemplate template[2];
    u32 i = 0;
    s32 dx = 0;
    u8 *slot = (u8 *)view;

    template[0] = gPCBoxTrayBoxSpriteTemplate;
    for (; i < PC_BOX_TRAY_BOX_COUNT; dx += 34, slot += sizeof(ManagedSprite *), i++) {
        template[1] = template[0];
        template[1].x += dx;
        template[1].resIdList[0] = 0xc123 + i;
        *(ManagedSprite **)(slot + offsetof(PCBoxView, sprites[PC_BOX_SPRITE_TRAY_BOXES])) = SpriteSystem_NewSprite(view->spriteSystem, view->spriteManager, &template[1]);
    }
}

static void PCBox_LoadWallpaperListResources(PCBoxView *view) {
    u32 i;

    for (i = 0; i < 4; i++) {
        SpriteSystem_LoadCharResObj(view->spriteSystem, view->spriteManager, NARC_a_0_1_9, 0x4a, FALSE, 1, 0xc129 + i);
    }
    SpriteSystem_LoadPlttResObj(view->spriteSystem, view->spriteManager, NARC_a_0_1_9, 0x4b, FALSE, 2, 1, 0xc100);
    SpriteSystem_LoadCellResObj(view->spriteSystem, view->spriteManager, NARC_a_0_1_9, 0x4c, TRUE, 0xc0fe);
    SpriteSystem_LoadAnimResObj(view->spriteSystem, view->spriteManager, NARC_a_0_1_9, 0x4d, TRUE, 0xc0fe);
}

static void PCBox_CreateWallpaperListSprites(PCBoxView *view) {
    ManagedSpriteTemplate template[2];
    u32 i = 0;
    s32 dx = 0;
    u8 *slot = (u8 *)view;

    template[0] = gPCBoxWallpaperListSpriteTemplate;
    for (; i < 4; dx += 46, slot += sizeof(ManagedSprite *), i++) {
        template[1] = template[0];
        template[1].x += dx;
        template[1].resIdList[0] = 0xc129 + i;
        *(ManagedSprite **)(slot + offsetof(PCBoxView, sprites[PC_BOX_SPRITE_WALLPAPERS])) = SpriteSystem_NewSprite(view->spriteSystem, view->spriteManager, &template[1]);
    }
}

void PCBox_SetBoxArrowsVisible(PCBoxView *view, u32 visible) {
    PCBox_SetSpriteVisible(view, PC_BOX_SPRITE_PREV_BOX_ARROW, visible);
    PCBox_SetSpriteVisible(view, PC_BOX_SPRITE_NEXT_BOX_ARROW, visible);
}

static void PCBox_PlaceWallpaperMenuTextObj(PCBoxView *view) {
    TextOBJ_SetPosition(view->textObjs[0].textObj, -48, -8);
}

void PCBox_SetupWallpaperMenuSprites(PCBoxWork *work) {
    PCBoxView *view = work->view;

    ManagedSprite_SetPositionXY(view->sprites[PC_BOX_SPRITE_TRAY_PREV_ARROW], 12, -21);
    ManagedSprite_SetPositionXY(view->sprites[PC_BOX_SPRITE_TRAY_NEXT_ARROW], 244, -21);
    ManagedSprite_SetPositionXY(view->sprites[PC_BOX_SPRITE_TRAY_MARKER], 43, -21);
    ManagedSprite_SetPositionXY(view->sprites[PC_BOX_SPRITE_TRAY_CURSOR], 128, -40);
    ManagedSprite_SetPositionXY(view->sprites[PC_BOX_SPRITE_TRAY_LABEL], 128, -28);
    PCBox_LoadWallpaperThumbnails(work);
    PCBox_SetSpriteAnim(view, PC_BOX_SPRITE_TRAY_CURSOR, 7);
    PCBox_PlaceWallpaperMenuTextObj(view);
    TextOBJ_SetSpritesDrawFlag(view->textObjs[0].textObj, TRUE);
    TextOBJ_SetSpritesDrawFlag(view->textObjs[1].textObj, FALSE);
}

void PCBox_MoveWallpaperMenuSprites(PCBoxView *view, s32 dy) {
    s16 x;
    s16 y;
    u32 i;

    for (i = PC_BOX_SPRITE_TRAY_PREV_ARROW; i <= PC_BOX_SPRITE_TRAY_LABEL; i++) {
        ManagedSprite_GetPositionXY(view->sprites[i], &x, &y);
        ManagedSprite_SetPositionXY(view->sprites[i], x, y + dy);
    }
    PCBox_PlaceWallpaperMenuTextObj(view);
    for (i = 0; i < 4; i++) {
        ManagedSprite_GetPositionXY(view->sprites[PC_BOX_SPRITE_WALLPAPERS + i], &x, &y);
        ManagedSprite_SetPositionXY(view->sprites[PC_BOX_SPRITE_WALLPAPERS + i], x, y + dy);
    }
}

void PCBox_UpdateCurrentWallpaperMarker(PCBoxWork *work) {
    s16 x;
    s16 y;
    u32 wallpaper = PCBox_GetWallpaperGfxIndex(work, work->trayBox);

    if ((u32)work->view->wallpaperSelection >> 2 == wallpaper >> 2) {
        PCBox_SetSpriteVisible(work->view, PC_BOX_SPRITE_TRAY_MARKER, TRUE);
    } else {
        PCBox_SetSpriteVisible(work->view, PC_BOX_SPRITE_TRAY_MARKER, FALSE);
    }
    ManagedSprite_GetPositionXY(work->view->sprites[PC_BOX_SPRITE_TRAY_MARKER], &x, &y);
    ManagedSprite_SetPositionXY(work->view->sprites[PC_BOX_SPRITE_TRAY_MARKER], 46 * (wallpaper & 3) + 59, y);
}

void PCBox_UpdateWallpaperCursor(PCBoxWork *work) {
    s16 cursorX;
    s16 y;
    s16 x;
    u16 column = work->view->wallpaperSelection % 4;

    ManagedSprite_GetPositionXY(work->view->sprites[PC_BOX_SPRITE_WALLPAPERS + column], &x, &y);
    ManagedSprite_GetPositionXY(work->view->sprites[PC_BOX_SPRITE_TRAY_CURSOR], &cursorX, &y);
    ManagedSprite_SetPositionXY(work->view->sprites[PC_BOX_SPRITE_TRAY_CURSOR], x, y);
    ManagedSprite_GetPositionXY(work->view->sprites[PC_BOX_SPRITE_TRAY_LABEL], &cursorX, &y);
    ManagedSprite_SetPositionXY(work->view->sprites[PC_BOX_SPRITE_TRAY_LABEL], x, y);
    PCBox_PlaceWallpaperMenuTextObj(work->view);
}

void PCBox_LoadWallpaperThumbnails(PCBoxWork *work) {
    NNSG2dCharacterData *charData;
    void *narcBuf;
    u32 i;
    void *buf;
    u32 index = 21;
    u32 wallpaper = (u32)work->view->wallpaperSelection >> 2;

    wallpaper = wallpaper * 4;
    buf = Heap_AllocAtEnd(HEAP_ID_10, 0x240);
    narcBuf = AllocAtEndAndReadWholeNarcMemberByIdPair(NARC_a_0_1_9, 0x4a, HEAP_ID_10);
    NNS_G2dGetUnpackedCharacterData(narcBuf, &charData);
    for (i = 0; i < 4; i++) {
        MI_CpuCopy8(charData->pRawData, buf, 0x240);
        PCBox_ColorWallpaperThumbnail(work, buf, wallpaper, 30, 0x240);
        PCBox_LoadSpriteCharsMain(work->view, index, buf, 0x240);
        index++;
        wallpaper++;
    }
    Heap_Free(narcBuf);
    Heap_Free(buf);
}

// Recolors pixels MATCH of a thumbnail to the palette color of WALLPAPER (locked bonus wallpapers are gray).
static void PCBox_ColorWallpaperThumbnail(PCBoxWork *work, u8 *buf, u32 wallpaper, u32 match, u32 size) {
    u32 i;
    u8 color;

    if (wallpaper >= 16) {
        if (!PCStorage_IsBonusWallpaperUnlocked(work->storage, wallpaper - 16)) {
            color = 0x28;
        } else {
            color = wallpaper + 16;
        }
    } else {
        color = wallpaper + 16;
    }
    for (i = 0; i < size; i++) {
        if (match == buf[i]) {
            buf[i] = color;
        }
    }
}

void PCBox_PlaceTrayTextObjs(PCBoxView *view) {
    TextOBJ_SetPosition(view->textObjs[0].textObj, -72, -8);
    TextOBJ_SetPosition(view->textObjs[1].textObj, 32, -8);
}

void PCBox_SetupBoxTraySprites(PCBoxWork *work) {
    ManagedSprite_SetPositionXY(work->view->sprites[PC_BOX_SPRITE_TRAY_PREV_ARROW], 12, -21);
    ManagedSprite_SetPositionXY(work->view->sprites[PC_BOX_SPRITE_TRAY_NEXT_ARROW], 244, -21);
    ManagedSprite_SetPositionXY(work->view->sprites[PC_BOX_SPRITE_TRAY_MARKER], 43, -21);
    ManagedSprite_SetPositionXY(work->view->sprites[PC_BOX_SPRITE_TRAY_CURSOR], 128, -40);
    ManagedSprite_SetPositionXY(work->view->sprites[PC_BOX_SPRITE_TRAY_LABEL], 128, -28);
    PCBox_LoadTrayPageThumbnails(work);
    PCBox_SetSpriteAnim(work->view, PC_BOX_SPRITE_TRAY_CURSOR, 5);
    PCBox_PlaceTrayTextObjs(work->view);
    TextOBJ_SetSpritesDrawFlag(work->view->textObjs[0].textObj, TRUE);
    TextOBJ_SetSpritesDrawFlag(work->view->textObjs[1].textObj, TRUE);
}

void PCBox_MoveBoxTraySprites(PCBoxWork *work, s32 dy) {
    s16 x;
    s16 y;
    u32 i;

    for (i = PC_BOX_SPRITE_TRAY_PREV_ARROW; i <= PC_BOX_SPRITE_TRAY_LABEL; i++) {
        ManagedSprite_GetPositionXY(work->view->sprites[i], &x, &y);
        ManagedSprite_SetPositionXY(work->view->sprites[i], x, y + dy);
    }
    PCBox_PlaceTrayTextObjs(work->view);
    for (i = 0; i < PC_BOX_TRAY_BOX_COUNT; i++) {
        ManagedSprite_GetPositionXY(work->view->sprites[PC_BOX_SPRITE_TRAY_BOXES + i], &x, &y);
        ManagedSprite_SetPositionXY(work->view->sprites[PC_BOX_SPRITE_TRAY_BOXES + i], x, y + dy);
    }
}

void PCBox_UpdateCurrentBoxMarker(PCBoxWork *work) {
    s16 x;
    s16 y;
    s32 page = work->trayBox / 6;
    s32 column;

    if (page == work->activeBox / 6) {
        PCBox_SetSpriteVisible(work->view, PC_BOX_SPRITE_TRAY_MARKER, TRUE);
    } else {
        PCBox_SetSpriteVisible(work->view, PC_BOX_SPRITE_TRAY_MARKER, FALSE);
    }
    column = work->activeBox % 6;
    ManagedSprite_GetPositionXY(work->view->sprites[PC_BOX_SPRITE_TRAY_MARKER], &x, &y);
    ManagedSprite_SetPositionXY(work->view->sprites[PC_BOX_SPRITE_TRAY_MARKER], 34 * column + 43, y);
}

void PCBox_UpdateTrayCursor(PCBoxWork *work) {
    s16 cursorX;
    s16 y;
    s16 x;
    u16 column = work->trayBox % 6;

    ManagedSprite_GetPositionXY(work->view->sprites[PC_BOX_SPRITE_TRAY_CURSOR], &cursorX, &y);
    ManagedSprite_SetPositionXY(work->view->sprites[PC_BOX_SPRITE_TRAY_CURSOR], gPCBoxTrayCursorX[column], y);
    ManagedSprite_GetPositionXY(work->view->sprites[PC_BOX_SPRITE_TRAY_BOXES + column], &x, &y);
    ManagedSprite_GetPositionXY(work->view->sprites[PC_BOX_SPRITE_TRAY_LABEL], &cursorX, &y);
    ManagedSprite_SetPositionXY(work->view->sprites[PC_BOX_SPRITE_TRAY_LABEL], x, y);
    PCBox_PlaceTrayTextObjs(work->view);
}

void PCBox_GetTrayBoxPosition(PCBoxView *view, u32 box, s16 *x, s16 *y) {
    ManagedSprite_GetPositionXY(view->sprites[PC_BOX_SPRITE_TRAY_BOXES + box], x, y);
}

void PCBox_DrawBoxThumbnail(PCBoxWork *work, int box) {
    NNSG2dCharacterData *charData;
    void *allocation = AllocAtEndAndReadWholeNarcMemberByIdPair(NARC_a_0_1_9, 70, HEAP_ID_10);

    NNS_G2dGetUnpackedCharacterData(allocation, &charData);
    MI_CpuCopy8(charData->pRawData, work->view->boxThumbnails[box], 0x400);
    Heap_Free(allocation);
    PCBox_ColorWallpaperThumbnail(work, work->view->boxThumbnails[box], PCBox_GetWallpaperGfxIndex(work, box), 8, 0x400);
    PCBox_DrawBoxThumbnailMons(work, box, work->view->boxThumbnails[box]);
}

void PCBox_DrawAllBoxThumbnails(PCBoxWork *work) {
    u32 i;

    for (i = 0; i < 18; i++) {
        PCBox_DrawBoxThumbnail(work, i);
    }
}
