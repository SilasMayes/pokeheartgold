#include "global.h"

#include "constants/items.h"
#include "constants/pokemon.h"
#include "constants/species.h"

#include "application/pc_box/pc_box_internal.h"
#include "msgdata/msg.naix"

#include "bag.h"
#include "bg_cell_manager.h"
#include "bg_window.h"
#include "font.h"
#include "gf_gfx_loader.h"
#include "gf_gfx_planes.h"
#include "grid_input_handler.h"
#include "heap.h"
#include "item.h"
#include "menu_input_state.h"
#include "message_format.h"
#include "message_printer.h"
#include "msgdata.h"
#include "options.h"
#include "overlay_manager.h"
#include "palette.h"
#include "party.h"
#include "player_data.h"
#include "pm_string.h"
#include "pokemon.h"
#include "pokemon_storage_system.h"
#include "render_window.h"
#include "save_arrays.h"
#include "sprite_system.h"
#include "touchscreen.h"
#include "yes_no_prompt.h"

static void PCBox_UpdateDetailPanel(PCBoxWork *work);
static void PCBox_SwapBoxAndPartyMon(PCBoxWork *work, PCBoxMoveEntry *boxEntry, PCBoxMoveEntry *partyEntry);
static void PCBox_MoveBoxMonToParty(PCBoxWork *work, PCBoxMoveEntry *entry);
static void PCBox_MovePartyMonToBox(PCBoxWork *work, PCBoxMoveEntry *entry);
static void PCBox_SwapPartyMons(PCBoxWork *work, PCBoxMoveEntry *entry);
static void PCBox_MovePartyMonToEnd(PCBoxWork *work, PCBoxMoveEntry *entry);
static void PCBox_MoveBoxMonToOtherBox(PCBoxWork *work, PCBoxMoveEntry *entry);
static void PCBox_MovePartyMonToOtherBox(PCBoxWork *work, PCBoxMoveEntry *entry);
static u32 PCBox_GetTargetBoxId(PCBoxWork *work, u32 target);
static u32 PCBox_CanMoveMon(PCBoxWork *work, u32 from, u32 to);
static u32 PCBox_CanMovePartyMonToEmptySlot(PCBoxWork *work, u32 from, u32 to);
static void PCBox_SetupMoveEntryToSlot(PCBoxWork *work, PCBoxMoveEntry *entry);
static void PCBox_SetupMoveEntryToSprite(PCBoxWork *work, PCBoxMoveEntry *entry);
static void PCBox_SetupMonSwapEntries(PCBoxWork *work, u32 from, u32 to);
static s32 PCBox_GetReleaseCheckMoveIndex(u16 move);
static void PCBox_FreeMonInfo(PCBoxMonInfo *monInfo);
static void PCBox_DrawMonInfo(PCBoxWork *work, PCBoxMonInfo *monInfo);
static void PCBox_DrawMonItemInfo(PCBoxWork *work, PCBoxMonInfo *monInfo);
static void PCBox_LoadWallpaperChars(PCBoxWork *work, s32 member, u32 unused, u32 offset);
static void PCBox_LoadWallpaperPalette(PCBoxWork *work, s32 member, u32 palette);
static void PCBox_LoadWallpaperTilemap(PCBoxWork *work, s32 unused, u32 tile, u32 addend, u32 palette);
static void PCBox_LoadWallpaper(PCBoxWork *work, s32 member, u32 tile, u32 offset, u32 palette);
static u32 PCBox_IsPointInRect(s32 x, s32 y, const u8 *rect);

BOOL PCBox_Init(OverlayManager *manager, int *state) {
    PCBoxWork *work;

    Heap_Create(HEAP_ID_3, HEAP_ID_9, 1 << 16);
    work = OverlayManager_CreateAndGetData(manager, sizeof(PCBoxWork), HEAP_ID_9);
    MI_CpuFill8(work, 0, sizeof(PCBoxWork));
    work->args = OverlayManager_GetArgs(manager);
    work->storage = SaveArray_PCStorage_Get(work->args->saveData);
    work->activeBox = PCStorage_GetActiveBox(work->storage);
    work->party = SaveArray_Party_Get(work->args->saveData);
    work->bag = Save_Bag_Get(work->args->saveData);
    work->options = Save_PlayerData_GetOptionsAddr(work->args->saveData);
    work->selectedSlot = PC_BOX_SLOT_NONE;
    work->returnCursorPos = 0;
    work->nextState = PC_BOX_STATE_START;
    return TRUE;
}

BOOL PCBox_Main(OverlayManager *manager, int *state) {
    PCBoxWork *work = OverlayManager_GetData(manager);

    if (!PCBox_RunStateMachine(work, state)) {
        return TRUE;
    }
    return FALSE;
}

BOOL PCBox_Exit(OverlayManager *manager, int *state) {
    PCBoxWork *work = OverlayManager_GetData(manager);

    PCStorage_SetActiveBox(work->storage, work->activeBox);
    OverlayManager_FreeData(manager);
    Heap_Destroy(HEAP_ID_9);
    return TRUE;
}

void PCBox_VBlankCallback(SysTask *task, void *data) {
    PCBoxWork *work = data;

    if (work->view->updateFunc != NULL && !work->view->updateFunc(work)) {
        work->view->updateFunc = NULL;
    }
    PCBox_UpdateDetailPanel(work);
    PaletteData_PushTransparentBuffers(work->view->paletteData);
    DoScheduledBgGpuUpdates(work->view->bgConfig);
    PCBox_TickSprites(work->view);
    if (work->view->spriteDrawLock == 0) {
        SpriteSystem_DrawSprites(work->view->spriteManager);
        SpriteSystem_TransferOam();
    }
    OS_SetIrqCheckFlag(OS_IE_V_BLANK);
}

static void PCBox_UpdateDetailPanel(PCBoxWork *work) {
    if (work->args->mode != PC_BOX_MODE_MOVE_ITEMS) {
        BgCellManager_UpdateCellMove(work->view->panels, PC_BOX_PANEL_INFO);
        return;
    }
    BgCellManager_UpdateCellMove(work->view->panels, PC_BOX_PANEL_INFO);
    PCBox_UpdateInfoItemIconPosition(work->view);
}

void PCBox_SetUpdateFunc(PCBoxView *view, void *func) {
    view->subState = 0;
    view->counter = 0;
    view->updateFunc = func;
    view->pendingUpdateFunc = NULL;
}

void PCBox_SetPendingUpdateFunc(PCBoxView *view, void *func) {
    view->pendingUpdateFunc = func;
}

void PCBox_StartPendingUpdateFunc(PCBoxView *view) {
    PCBox_SetUpdateFunc(view, view->pendingUpdateFunc);
}

void PCBox_SetGfxBanks(void) {
    GfGfx_SetBanks(&gPCBoxGfxBanks);
}

void PCBox_InitBgLayers(PCBoxWork *work) {
    GraphicsModes modes;
    BgTemplate bg0;
    BgTemplate bg1;
    BgTemplate bg2;
    BgTemplate bg3;
    BgTemplate bg4;
    BgTemplate bg5;
    BgTemplate bg6;

    work->view->bgConfig = BgConfig_Alloc(HEAP_ID_10);
    modes = gPCBoxGraphicsModes;
    SetBothScreensModesAndDisable(&modes);

    bg0 = gPCBoxBgTemplate0;
    InitBgFromTemplate(work->view->bgConfig, GF_BG_LYR_MAIN_0, &bg0, GF_BG_TYPE_TEXT);
    BgClearTilemapBufferAndCommit(work->view->bgConfig, GF_BG_LYR_MAIN_0);
    BG_ClearCharDataRange(GF_BG_LYR_MAIN_0, 0x20, 0, HEAP_ID_10);

    bg1 = gPCBoxBgTemplate1;
    InitBgFromTemplate(work->view->bgConfig, GF_BG_LYR_MAIN_1, &bg1, GF_BG_TYPE_TEXT);
    BgClearTilemapBufferAndCommit(work->view->bgConfig, GF_BG_LYR_MAIN_1);
    BG_ClearCharDataRange(GF_BG_LYR_MAIN_1, 0x20, 0, HEAP_ID_10);

    bg2 = gPCBoxBgTemplate2;
    InitBgFromTemplate(work->view->bgConfig, GF_BG_LYR_MAIN_2, &bg2, GF_BG_TYPE_TEXT);

    bg3 = gPCBoxBgTemplate3;
    InitBgFromTemplate(work->view->bgConfig, GF_BG_LYR_MAIN_3, &bg3, GF_BG_TYPE_TEXT);

    bg4 = gPCBoxBgTemplate4;
    InitBgFromTemplate(work->view->bgConfig, GF_BG_LYR_SUB_0, &bg4, GF_BG_TYPE_TEXT);
    BgClearTilemapBufferAndCommit(work->view->bgConfig, GF_BG_LYR_SUB_0);
    BG_ClearCharDataRange(GF_BG_LYR_SUB_0, 0x20, 0, HEAP_ID_10);

    bg5 = gPCBoxBgTemplate5;
    InitBgFromTemplate(work->view->bgConfig, GF_BG_LYR_SUB_1, &bg5, GF_BG_TYPE_TEXT);

    bg6 = gPCBoxBgTemplate6;
    InitBgFromTemplate(work->view->bgConfig, GF_BG_LYR_SUB_2, &bg6, GF_BG_TYPE_TEXT);
    BgClearTilemapBufferAndCommit(work->view->bgConfig, GF_BG_LYR_SUB_2);
    BG_ClearCharDataRange(GF_BG_LYR_SUB_2, 0x20, 0, HEAP_ID_10);
}

void PCBox_FreeBgLayers(PCBoxWork *work) {
    FreeBgTilemapBuffer(work->view->bgConfig, GF_BG_LYR_SUB_2);
    FreeBgTilemapBuffer(work->view->bgConfig, GF_BG_LYR_SUB_1);
    FreeBgTilemapBuffer(work->view->bgConfig, GF_BG_LYR_SUB_0);
    FreeBgTilemapBuffer(work->view->bgConfig, GF_BG_LYR_MAIN_3);
    FreeBgTilemapBuffer(work->view->bgConfig, GF_BG_LYR_MAIN_2);
    FreeBgTilemapBuffer(work->view->bgConfig, GF_BG_LYR_MAIN_1);
    FreeBgTilemapBuffer(work->view->bgConfig, GF_BG_LYR_MAIN_0);
    Heap_Free(work->view->bgConfig);
}

void PCBox_LoadBgGraphics(PCBoxWork *work) {
    GfGfxLoader_LoadCharData(NARC_a_0_1_9, 0xe, work->view->bgConfig, GF_BG_LYR_MAIN_0, 0, 0, TRUE, HEAP_ID_10);
    GfGfxLoader_LoadCharData(NARC_a_0_1_9, 0xe, work->view->bgConfig, GF_BG_LYR_MAIN_1, 0, 0, TRUE, HEAP_ID_10);
    GfGfxLoader_LoadCharData(NARC_a_0_1_9, 3, work->view->bgConfig, GF_BG_LYR_MAIN_2, 0, 0, TRUE, HEAP_ID_10);
    GfGfxLoader_LoadScrnData(NARC_a_0_1_9, 2, work->view->bgConfig, GF_BG_LYR_MAIN_2, 0, 0, TRUE, HEAP_ID_10);
    GfGfxLoader_LoadCharData(NARC_a_0_1_9, 1, work->view->bgConfig, GF_BG_LYR_MAIN_3, 0, 0, TRUE, HEAP_ID_10);
    GfGfxLoader_LoadScrnData(NARC_a_0_1_9, 0, work->view->bgConfig, GF_BG_LYR_MAIN_3, 0, 0, TRUE, HEAP_ID_10);
    GfGfxLoader_GXLoadPal(NARC_a_0_1_9, 4, GF_PAL_LOCATION_MAIN_BG, GF_PAL_SLOT_0_OFFSET, 0x80, HEAP_ID_10);
    GfGfxLoader_LoadCharData(NARC_a_0_1_9, 6, work->view->bgConfig, GF_BG_LYR_SUB_1, 0, 0, TRUE, HEAP_ID_10);
    GfGfxLoader_LoadScrnData(NARC_a_0_1_9, 5, work->view->bgConfig, GF_BG_LYR_SUB_1, 0, 0, TRUE, HEAP_ID_10);
    GfGfxLoader_GXLoadPal(NARC_a_0_1_9, 7, GF_PAL_LOCATION_SUB_BG, GF_PAL_SLOT_0_OFFSET, 0, HEAP_ID_10);
    GfGfxLoader_LoadCharData(NARC_a_0_1_9, 6, work->view->bgConfig, GF_BG_LYR_SUB_2, 0, 0, TRUE, HEAP_ID_10);
}

void PCBox_CreateMsgResources(PCBoxWork *work) {
    work->view->msgData = NewMsgDataFromNarc(MSGDATA_LOAD_DIRECT, NARC_msgdata_msg, NARC_msg_msg_0024_bin, HEAP_ID_10);
    work->view->msgPrinter = MessagePrinter_New(1, 2, 0, HEAP_ID_10);
    work->view->msgFormat = MessageFormat_New(HEAP_ID_10);
    work->view->string = String_New(0x400, HEAP_ID_10);
}

void PCBox_DestroyMsgResources(PCBoxWork *work) {
    String_Delete(work->view->string);
    MessageFormat_Delete(work->view->msgFormat);
    MessagePrinter_Delete(work->view->msgPrinter);
    DestroyMsgData(work->view->msgData);
}

void PCBox_LoadWindowGraphics(PCBoxWork *work) {
    PCBoxView *view = work->view;
    GfGfxLoader_LoadCharData(NARC_a_0_1_9, 0x40, view->bgConfig, GF_BG_LYR_MAIN_0, 0x3e8, 0x300, TRUE, HEAP_ID_10);
    GfGfxLoader_LoadCharData(NARC_a_0_1_9, 0x40, view->bgConfig, GF_BG_LYR_MAIN_1, 0x3e8, 0x300, TRUE, HEAP_ID_10);
    GfGfxLoader_GXLoadPal(NARC_a_0_1_9, 0x41, GF_PAL_LOCATION_MAIN_BG, GF_PAL_SLOT_12_OFFSET, 0x40, HEAP_ID_10);
    LoadUserFrameGfx2(view->bgConfig, GF_BG_LYR_MAIN_0, 0x38e, 0xa, (u8)Options_GetFrame(work->options), HEAP_ID_10);
    LoadFontPal1(GF_PAL_LOCATION_MAIN_BG, GF_PAL_SLOT_11_OFFSET, HEAP_ID_10);
    LoadFontPal0(GF_PAL_LOCATION_SUB_BG, GF_PAL_SLOT_15_OFFSET, HEAP_ID_10);
}

void PCBox_CreatePaletteData(PCBoxWork *work) {
    PaletteData *palette = PaletteData_Init(HEAP_ID_10);
    work->view->paletteData = palette;
    PaletteData_AllocBuffers(work->view->paletteData, PLTTBUF_MAIN_BG, 0x200, HEAP_ID_10);
}

void PCBox_FreePaletteData(PCBoxWork *work) {
    PaletteData_FreeBuffers(work->view->paletteData, PLTTBUF_MAIN_BG);
    PaletteData_Free(work->view->paletteData);
}

void PCBox_SetBlendEnabled(int enabled) {
    if (enabled == 1) {
        G2_SetBlendAlpha(GX_BLEND_PLANEMASK_NONE, GX_BLEND_PLANEMASK_BG1 | GX_BLEND_PLANEMASK_BG3 | GX_BLEND_PLANEMASK_BD, 6, 10);
    } else {
        reg_G2_BLDCNT = 0;
    }
}

void PCBox_CreateYesNoPrompt(PCBoxWork *work) {
    work->view->yesNoPrompt = YesNoPrompt_Create(HEAP_ID_10);
}

void PCBox_DestroyYesNoPrompt(PCBoxWork *work) {
    YesNoPrompt_Destroy(work->view->yesNoPrompt);
}

void PCBox_ShowYesNoPrompt(PCBoxWork *work, u32 cursorPos) {
    YesNoPromptTemplate tmpl;
    tmpl.bgConfig = work->view->bgConfig;
    tmpl.bgId = GF_BG_LYR_MAIN_0;
    tmpl.tileStart = 0x3AC;
    tmpl.plttSlot = 8;
    tmpl.x = 0x19;
    tmpl.y = 0xC;
    tmpl.ignoreTouchFlag = 0;
    tmpl.initialCursorPos = (u8)cursorPos;
    tmpl.shapeParam = 0;
    YesNoPrompt_InitFromTemplate(work->view->yesNoPrompt, &tmpl);
}

u32 PCBox_AnimatePaletteFlash(PCBoxWork *work) {
    PCBoxView *view = work->view;
    PCBoxPaletteFlash *flash = &view->paletteFlash;
    switch (flash->state) {
    case 0:
        if (flash->isBg == 0) {
            ManagedSprite_SetPaletteOverride(view->sprites[flash->index], flash->palA);
        } else {
            BgTilemapRectChangePalette(view->bgConfig, flash->index, flash->x, flash->y, flash->w, flash->h, flash->palA);
            ScheduleBgTilemapBufferTransfer(work->view->bgConfig, flash->index);
        }
        flash->state++;
        break;
    case 1:
        flash->timer++;
        if (flash->timer == 4) {
            if (flash->isBg == 0) {
                ManagedSprite_SetPaletteOverride(work->view->sprites[flash->index], flash->palB);
            } else {
                BgTilemapRectChangePalette(work->view->bgConfig, flash->index, flash->x, flash->y, flash->w, flash->h, flash->palB);
                ScheduleBgTilemapBufferTransfer(work->view->bgConfig, flash->index);
            }
            flash->timer = 0;
            flash->state++;
        }
        break;
    case 2:
        flash->timer++;
        if (flash->timer == 2) {
            return 0;
        }
        break;
    }
    return 1;
}

void PCBox_SaveMenuInputState(PCBoxWork *work) {
    if (GridInputHandler_IsButtonInputMode(work->view->gridInput) == TRUE) {
        MenuInputStateMgr_SetState(work->args->menuInputStatePtr, MENU_INPUT_STATE_BUTTONS);
    } else {
        MenuInputStateMgr_SetState(work->args->menuInputStatePtr, MENU_INPUT_STATE_TOUCH);
    }
}

u32 PCBox_GetSlotMonData(PCBoxWork *work, u32 idx, u32 field, void *dest) {
    BoxPokemon *boxmon = PCBox_GetSlotBoxMon(work, work->activeBox, idx);
    if (boxmon == NULL) {
        return 0;
    }
    return GetBoxMonData(boxmon, field, dest);
}

void PCBox_SetSlotMonData(PCBoxWork *work, u32 idx, u32 field, void *src) {
    BoxPokemon *boxmon = PCBox_GetSlotBoxMon(work, work->activeBox, idx);
    if (boxmon != NULL) {
        SetBoxMonData(boxmon, field, src);
        if (idx < PC_BOX_SLOT_PARTY_START) {
            PCStorage_SetBoxModified(work->storage, work->activeBox);
        }
    }
}

BoxPokemon *PCBox_GetSlotBoxMon(PCBoxWork *work, u32 boxId, u32 idx) {
    if (boxId == 0xFF || idx >= PC_BOX_SLOT_PARTY_START) {
        if (idx >= PC_BOX_SLOT_PARTY_START) {
            idx -= PC_BOX_SLOT_PARTY_START;
        }
        if (Party_GetCount(work->party) > idx) {
            return Mon_GetBoxMon(Party_GetMonByIndex(work->party, idx));
        }
        return NULL;
    }
    if (idx == 0xFF) {
        return NULL;
    }
    return PCStorage_GetMonByIndexPair(work->storage, boxId, idx);
}

void PCBox_DeleteSlotMon(PCBoxWork *work, u32 boxId, u32 idx) {
    if (idx < PC_BOX_SLOT_PARTY_START) {
        PCStorage_DeleteBoxMonByIndexPair(work->storage, boxId, idx);
    } else {
        Party_RemoveMon(work->party, idx - PC_BOX_SLOT_PARTY_START);
    }
}

static void PCBox_SwapBoxAndPartyMon(PCBoxWork *work, PCBoxMoveEntry *boxEntry, PCBoxMoveEntry *partyEntry) {
    u8 mood;
    u32 slot;
    CopyBoxPokemonToPokemon(PCBox_GetSlotBoxMon(work, work->activeBox, boxEntry->from), boxEntry->mon);
    slot = partyEntry->from - PC_BOX_SLOT_PARTY_START;
    CopyPokemonToPokemon(Party_GetMonByIndex(work->party, slot), partyEntry->mon);
    mood = 0;
    SetMonData(partyEntry->mon, MON_DATA_MOOD, &mood);
    Party_SafeCopyMonToSlot_ResetAprijuiceModifiers(work->party, slot, boxEntry->mon);
    PCStorage_PlaceMonInBoxByIndexPair(work->storage, work->activeBox, partyEntry->to, Mon_GetBoxMon(partyEntry->mon));
    PCBox_DrawBoxThumbnail(work, work->activeBox);
    PCBox_RefreshTrayBoxThumbnail(work, work->activeBox);
}

static void PCBox_MoveBoxMonToParty(PCBoxWork *work, PCBoxMoveEntry *entry) {
    CopyBoxPokemonToPokemon(PCBox_GetSlotBoxMon(work, work->activeBox, entry->from), entry->mon);
    Party_AddMon(work->party, entry->mon);
    PCBox_DeleteSlotMon(work, work->activeBox, entry->from);
    PCBox_DrawBoxThumbnail(work, work->activeBox);
    PCBox_RefreshTrayBoxThumbnail(work, work->activeBox);
}

static void PCBox_MovePartyMonToBox(PCBoxWork *work, PCBoxMoveEntry *entry) {
    u8 mood;
    Pokemon *mon;
    mon = Party_GetMonByIndex(work->party, entry->from - PC_BOX_SLOT_PARTY_START);
    mood = 0;
    SetMonData(mon, MON_DATA_MOOD, &mood);
    PCStorage_PlaceMonInBoxByIndexPair(work->storage, work->activeBox, entry->to, Mon_GetBoxMon(mon));
    PCBox_DeleteSlotMon(work, work->activeBox, entry->from);
    PCBox_DrawBoxThumbnail(work, work->activeBox);
    PCBox_RefreshTrayBoxThumbnail(work, work->activeBox);
}

static void PCBox_SwapPartyMons(PCBoxWork *work, PCBoxMoveEntry *entry) {
    PartyExtraSub subA;
    PartyExtraSub subB;
    u32 slotA;
    u32 slotB;
    slotB = entry->to - PC_BOX_SLOT_PARTY_START;
    slotA = entry->from - PC_BOX_SLOT_PARTY_START;
    CopyPokemonToPokemon(Party_GetMonByIndex(work->party, slotA), entry->mon);
    Party_GetMonAprijuiceModifiers(work->party, &subA, slotA);
    Party_GetMonAprijuiceModifiers(work->party, &subB, slotB);
    Party_SafeCopyMonToSlot_ResetAprijuiceModifiers(work->party, slotA, Party_GetMonByIndex(work->party, slotB));
    Party_SafeCopyMonToSlot_ResetAprijuiceModifiers(work->party, slotB, entry->mon);
    Party_SetMonAprijuiceModifiers(work->party, &subB, slotA);
    Party_SetMonAprijuiceModifiers(work->party, &subA, slotB);
}

static void PCBox_MovePartyMonToEnd(PCBoxWork *work, PCBoxMoveEntry *entry) {
    PartyExtraSub sub;
    u32 slot = entry->from - PC_BOX_SLOT_PARTY_START;
    u32 last;
    CopyPokemonToPokemon(Party_GetMonByIndex(work->party, slot), entry->mon);
    Party_GetMonAprijuiceModifiers(work->party, &sub, slot);
    PCBox_DeleteSlotMon(work, work->activeBox, entry->from);
    Party_AddMon(work->party, entry->mon);
    last = Party_GetCount(work->party) - 1;
    Party_SetMonAprijuiceModifiers(work->party, &sub, last);
}

static void PCBox_MoveBoxMonToOtherBox(PCBoxWork *work, PCBoxMoveEntry *entry) {
    BoxPokemon *mon = PCBox_GetSlotBoxMon(work, work->activeBox, entry->from);
    u32 box = PCBox_GetTargetBoxId(work, entry->to);
    PCStorage_PlaceMonInBoxFirstEmptySlot(work->storage, box, mon);
    PCStorage_DeleteBoxMonByIndexPair(work->storage, work->activeBox, entry->from);
    PCBox_DrawBoxThumbnail(work, work->activeBox);
    PCBox_RefreshTrayBoxThumbnail(work, work->activeBox);
    PCBox_DrawBoxThumbnail(work, box);
    PCBox_RefreshTrayBoxThumbnail(work, box);
}

static void PCBox_MovePartyMonToOtherBox(PCBoxWork *work, PCBoxMoveEntry *entry) {
    u32 box = PCBox_GetTargetBoxId(work, entry->to);
    CopyPokemonToPokemon(Party_GetMonByIndex(work->party, entry->from - PC_BOX_SLOT_PARTY_START), entry->mon);
    if (GetMonData(entry->mon, MON_DATA_SPECIES, NULL) == SPECIES_SHAYMIN) {
        Mon_UpdateShayminForm(entry->mon, 0);
    }
    PCStorage_PlaceMonInBoxFirstEmptySlot(work->storage, box, Mon_GetBoxMon(entry->mon));
    PCBox_DeleteSlotMon(work, work->activeBox, entry->from);
    PCBox_DrawBoxThumbnail(work, box);
    PCBox_RefreshTrayBoxThumbnail(work, box);
}

void PCBox_ApplyMonMove(PCBoxWork *work) {
    PCBoxMoveWork *moveWork = work->view->temp;
    u32 count;
    if (moveWork->from == 0xFF) {
        return;
    }
    count = Party_GetCount(work->party);
    if ((moveWork->to & 0x80) != 0) {
        PCBox_GetTargetBoxId(work, moveWork->to);
        if (moveWork->from < PC_BOX_SLOT_PARTY_START) {
            PCBox_MoveBoxMonToOtherBox(work, &moveWork->entries[0]);
        } else {
            PCBox_MovePartyMonToOtherBox(work, &moveWork->entries[moveWork->from - PC_BOX_SLOT_PARTY_START]);
        }
    } else if (moveWork->from < PC_BOX_SLOT_PARTY_START) {
        if (moveWork->to < PC_BOX_SLOT_PARTY_START) {
            PCStorage_SwapMonsInBoxByIndexPair(work->storage, work->activeBox, moveWork->from, moveWork->to);
            PCBox_DrawBoxThumbnail(work, work->activeBox);
            PCBox_RefreshTrayBoxThumbnail(work, work->activeBox);
        } else if (moveWork->to - PC_BOX_SLOT_PARTY_START < count) {
            PCBox_SwapBoxAndPartyMon(work, &moveWork->entries[0], &moveWork->entries[1]);
        } else {
            PCBox_MoveBoxMonToParty(work, &moveWork->entries[0]);
        }
    } else if (moveWork->to < PC_BOX_SLOT_PARTY_START) {
        if (PCBox_GetSlotMonData(work, moveWork->to, MON_DATA_SPECIES_EXISTS, NULL) != 0) {
            PCBox_SwapBoxAndPartyMon(work, &moveWork->entries[1], &moveWork->entries[0]);
        } else {
            PCBox_MovePartyMonToBox(work, &moveWork->entries[moveWork->from - PC_BOX_SLOT_PARTY_START]);
        }
    } else if (moveWork->to - PC_BOX_SLOT_PARTY_START < count) {
        PCBox_SwapPartyMons(work, &moveWork->entries[0]);
    } else {
        PCBox_MovePartyMonToEnd(work, &moveWork->entries[moveWork->from - PC_BOX_SLOT_PARTY_START]);
    }
}

static u32 PCBox_GetTargetBoxId(PCBoxWork *work, u32 target) {
    return (target & 0x7F) + work->trayBox / 6 * 6;
}

u32 PCBox_PartyHasOtherUsableMon(PCBoxWork *work, u32 skip) {
    u32 i;
    Pokemon *mon;
    for (i = 0; i < Party_GetCount(work->party); i++) {
        if (i == skip) {
            continue;
        }
        mon = Party_GetMonByIndex(work->party, i);
        if (GetMonData(mon, MON_DATA_IS_EGG, NULL) != 0) {
            continue;
        }
        if (GetMonData(mon, MON_DATA_HP, NULL) == 0) {
            continue;
        }
        return 1;
    }
    return 0;
}

u32 PCBox_UpdateArceusGiratinaForm(BoxPokemon *boxmon) {
    u16 species = GetBoxMonData(boxmon, MON_DATA_SPECIES, NULL);
    u16 form;
    if (species == SPECIES_ARCEUS) {
        form = GetBoxMonData(boxmon, MON_DATA_FORM, NULL);
        BoxMon_UpdateArceusForm(boxmon);
        if (form != (u16)GetBoxMonData(boxmon, MON_DATA_FORM, NULL)) {
            return 1;
        }
    } else if (species == SPECIES_GIRATINA) {
        form = GetBoxMonData(boxmon, MON_DATA_FORM, NULL);
        BoxMon_UpdateGiratinaForm(boxmon);
        if (form != (u16)GetBoxMonData(boxmon, MON_DATA_FORM, NULL)) {
            return 1;
        }
    }
    return 0;
}

void PCBox_RevertShayminFormOnMove(PCBoxWork *work, u32 from, u32 to) {
    PCBoxView *view;
    if (from < PC_BOX_SLOT_PARTY_START && to < PC_BOX_SLOT_PARTY_START) {
        return;
    }
    if (from >= PC_BOX_SLOT_PARTY_START && to >= PC_BOX_SLOT_PARTY_START) {
        return;
    }
    if (from >= PC_BOX_SLOT_PARTY_START) {
        from = to;
    }
    if (PCBox_GetSlotMonData(work, from, MON_DATA_SPECIES, NULL) != SPECIES_SHAYMIN) {
        return;
    }
    if (PCBox_GetSlotMonData(work, from, MON_DATA_FORM, NULL) == 0) {
        return;
    }
    BoxMon_UpdateShayminForm(PCBox_GetSlotBoxMon(work, work->activeBox, from), 0);
    view = work->view;
    PCBox_RefreshSlotIcon(work, work->activeBox, from, view->slotIcons[from]);
    if (work->selectedSlot == from) {
        PCBox_ShowSlotMonInfo(work, from);
    }
}

u32 PCBox_AnimateMonMove(PCBoxWork *work) {
    s16 pos[2];
    u32 j;
    u32 i;
    u32 icon;
    PCBoxMoveWork *moveWork = work->view->temp;
    if (moveWork->timer == 8) {
        for (i = 0; i < 7; i++) {
            if (moveWork->entries[i].active != 0) {
                icon = work->view->slotIcons[moveWork->entries[i].from];
                if ((moveWork->entries[i].to & 0x80) == 0) {
                    PCBox_GetSlotPosition(moveWork->entries[i].to, &pos[1], &pos[0], work->partyLayout);
                } else {
                    if (moveWork->entries[i].from >= PC_BOX_SLOT_PARTY_START) {
                        PCBox_GetSlotPosition(0x23, &pos[1], &pos[0], work->partyLayout);
                    } else {
                        PCBox_GetSlotPosition(moveWork->entries[i].from, &pos[1], &pos[0], work->partyLayout);
                    }
                    PCBox_SetSpriteVisible(work->view, icon, 0);
                }
                ManagedSprite_SetPositionXY(work->view->sprites[icon], pos[1], pos[0]);
            }
        }
        return 0;
    }
    moveWork->timer++;
    for (j = 0; j < 7; j++) {
        if (moveWork->entries[j].active != 0) {
            icon = work->view->slotIcons[moveWork->entries[j].from];
            pos[1] = moveWork->entries[j].px + (moveWork->entries[j].dx * moveWork->timer >> 16) * moveWork->entries[j].sx;
            pos[0] = moveWork->entries[j].py + (moveWork->entries[j].dy * moveWork->timer >> 16) * moveWork->entries[j].sy;
            ManagedSprite_SetPositionXY(work->view->sprites[icon], pos[1], pos[0]);
            PCBox_SetIconLayer(work->view, moveWork->entries[j].from, 0);
        }
    }
    return 1;
}

u32 PCBox_AnimateSelectedSlotMoveEntry(PCBoxWork *work) {
    s16 pos[2];
    u32 i;
    u32 icon;
    PCBoxMoveWork *moveWork = work->view->temp;
    if (moveWork->timer == 8) {
        for (i = 0; i < 7; i++) {
            if (moveWork->entries[i].active != 0) {
                icon = work->view->slotIcons[moveWork->entries[i].from];
                PCBox_GetSlotPosition(moveWork->entries[i].to, &pos[1], &pos[0], work->partyLayout);
                if (work->selectedSlot != moveWork->entries[i].to) {
                    pos[0] += 0x90;
                }
                ManagedSprite_SetPositionXY(work->view->sprites[icon], pos[1], pos[0]);
            }
        }
        return 0;
    }
    moveWork->timer++;
    for (i = 0; i < 7; i++) {
        if (moveWork->entries[i].active != 0 && work->selectedSlot == moveWork->entries[i].to) {
            icon = work->view->slotIcons[moveWork->entries[i].from];
            pos[1] = moveWork->entries[i].px + (moveWork->entries[i].dx * moveWork->timer >> 16) * moveWork->entries[i].sx;
            pos[0] = moveWork->entries[i].py + (moveWork->entries[i].dy * moveWork->timer >> 16) * moveWork->entries[i].sy;
            ManagedSprite_SetPositionXY(work->view->sprites[icon], pos[1], pos[0]);
            PCBox_SetIconLayer(work->view, moveWork->entries[i].from, 0);
            break;
        }
    }
    return 1;
}

u32 PCBox_AnimateMoveEntries(PCBoxWork *work) {
    s16 pos[2];
    u32 j;
    u32 i;
    u32 icon;
    PCBoxMoveWork *moveWork = work->view->temp;
    if (moveWork->timer == 8) {
        for (i = 0; i < 7; i++) {
            if (moveWork->entries[i].active != 0) {
                icon = work->view->slotIcons[moveWork->entries[i].from];
                PCBox_GetSlotPosition(moveWork->entries[i].to, &pos[1], &pos[0], work->partyLayout);
                ManagedSprite_SetPositionXY(work->view->sprites[icon], pos[1], pos[0]);
            }
        }
        return 0;
    }
    moveWork->timer++;
    for (j = 0; j < 7; j++) {
        if (moveWork->entries[j].active != 0) {
            icon = work->view->slotIcons[moveWork->entries[j].from];
            pos[1] = moveWork->entries[j].px + (moveWork->entries[j].dx * moveWork->timer >> 16) * moveWork->entries[j].sx;
            pos[0] = moveWork->entries[j].py + (moveWork->entries[j].dy * moveWork->timer >> 16) * moveWork->entries[j].sy;
            ManagedSprite_SetPositionXY(work->view->sprites[icon], pos[1], pos[0]);
            PCBox_SetMovingIconPriority(work->view, moveWork->entries[j].from, moveWork->entries[j].to);
        }
    }
    return 1;
}

static u32 PCBox_CanMoveMon(PCBoxWork *work, u32 from, u32 to) {
    u32 box;
    u32 targetExists;
    Pokemon *mon;
    PCBox_GetSlotMonData(work, to, MON_DATA_SPECIES_EXISTS, NULL);
    if ((to & 0x80) != 0) {
        box = PCBox_GetTargetBoxId(work, to);
        if (box == work->activeBox || PCStorage_CountMonsAndEggsInBox(work->storage, box) == MONS_PER_BOX) {
            return 0;
        }
        to ^= 0x80;
        targetExists = 0;
    } else {
        box = work->activeBox;
        targetExists = PCBox_GetSlotMonData(work, to, MON_DATA_SPECIES_EXISTS, NULL);
    }
    if (from >= PC_BOX_SLOT_PARTY_START) {
        if (PCBox_PartyHasOtherUsableMon(work, from - PC_BOX_SLOT_PARTY_START) == 0) {
            if (targetExists == 0) {
                if (to < PC_BOX_SLOT_PARTY_START || box != work->activeBox) {
                    return 0;
                }
            } else if (PCBox_GetSlotMonData(work, to, MON_DATA_IS_EGG, NULL) != 0 && to < PC_BOX_SLOT_PARTY_START) {
                return 0;
            }
        }
        if (to < PC_BOX_SLOT_PARTY_START) {
            mon = Party_GetMonByIndex(work->party, from - PC_BOX_SLOT_PARTY_START);
            if (ItemIdIsMail((u16)GetMonData(mon, MON_DATA_HELD_ITEM, NULL)) == TRUE) {
                return 0;
            }
            if (GetMonData(mon, MON_DATA_BALL_CAPSULE_ID, NULL) != 0) {
                return 0;
            }
        }
    } else if (to >= PC_BOX_SLOT_PARTY_START && targetExists != 0) {
        mon = Party_GetMonByIndex(work->party, to - PC_BOX_SLOT_PARTY_START);
        if (ItemIdIsMail((u16)GetMonData(mon, MON_DATA_HELD_ITEM, NULL)) == TRUE) {
            return 0;
        }
        if (GetMonData(mon, MON_DATA_BALL_CAPSULE_ID, NULL) != 0) {
            return 0;
        }
        if (PCBox_GetSlotMonData(work, from, MON_DATA_IS_EGG, NULL) != 0 && PCBox_PartyHasOtherUsableMon(work, to - PC_BOX_SLOT_PARTY_START) == 0) {
            return 0;
        }
    }
    return 1;
}

static u32 PCBox_CanMovePartyMonToEmptySlot(PCBoxWork *work, u32 from, u32 to) {
    Pokemon *mon;
    if (PCBox_GetSlotMonData(work, to, MON_DATA_SPECIES_EXISTS, NULL) != 0) {
        return 0;
    }
    if (PCBox_PartyHasOtherUsableMon(work, from - PC_BOX_SLOT_PARTY_START) == 0) {
        return 0;
    }
    mon = Party_GetMonByIndex(work->party, from - PC_BOX_SLOT_PARTY_START);
    if (ItemIdIsMail((u16)GetMonData(mon, MON_DATA_HELD_ITEM, NULL)) == TRUE) {
        return 0;
    }
    if (GetMonData(mon, MON_DATA_BALL_CAPSULE_ID, NULL) != 0) {
        return 0;
    }
    return 1;
}

u32 PCBox_CanSwapHeldItems(PCBoxWork *work, u32 from, u32 to) {
    u16 itemA;
    u16 itemB;
    if (PCBox_GetSlotMonData(work, to, MON_DATA_SPECIES_EXISTS, NULL) == 0) {
        return 0;
    }
    if (PCBox_GetSlotMonData(work, to, MON_DATA_IS_EGG, NULL) != 0) {
        return 0;
    }
    itemA = PCBox_GetSlotMonData(work, from, MON_DATA_HELD_ITEM, NULL);
    if (ItemIdIsMail(itemA) == TRUE) {
        return 0;
    }
    itemB = PCBox_GetSlotMonData(work, to, MON_DATA_HELD_ITEM, NULL);
    if (ItemIdIsMail(itemB) == TRUE) {
        return 0;
    }
    if (itemA == ITEM_GRISEOUS_ORB && PCBox_GetSlotMonData(work, to, MON_DATA_SPECIES, NULL) != SPECIES_GIRATINA) {
        return 0;
    }
    if (itemB == ITEM_GRISEOUS_ORB && PCBox_GetSlotMonData(work, from, MON_DATA_SPECIES, NULL) != SPECIES_GIRATINA) {
        return 0;
    }
    return 1;
}

static void PCBox_SetupMoveEntryToSlot(PCBoxWork *work, PCBoxMoveEntry *entry) {
    s16 pos[2];
    PCBoxView *view = work->view;
    ManagedSprite_GetPositionXY(view->sprites[view->slotIcons[entry->from]], &entry->px, &entry->py);
    if ((entry->to & 0x80) == 0) {
        PCBox_GetSlotPosition(entry->to, &pos[1], &pos[0], work->partyLayout);
    } else {
        PCBox_GetTrayBoxPosition(work->view, entry->to & 0x7F, &pos[1], &pos[0]);
    }
    if (entry->px <= pos[1]) {
        entry->sx = 1;
        entry->dx = ((pos[1] - entry->px) << 16) / 8;
    } else {
        entry->sx = -1;
        entry->dx = ((entry->px - pos[1]) << 16) / 8;
    }
    if (entry->py <= pos[0]) {
        entry->sy = 1;
        entry->dy = ((pos[0] - entry->py) << 16) / 8;
    } else {
        entry->sy = -1;
        entry->dy = ((entry->py - pos[0]) << 16) / 8;
    }
}

static void PCBox_SetupMoveEntryToSprite(PCBoxWork *work, PCBoxMoveEntry *entry) {
    s16 pos[2];
    PCBoxView *view = work->view;
    u32 j = view->slotIcons[entry->to];
    ManagedSprite_GetPositionXY(view->sprites[view->slotIcons[entry->from]], &entry->px, &entry->py);
    ManagedSprite_GetPositionXY(work->view->sprites[j], &pos[1], &pos[0]);
    if (entry->px <= pos[1]) {
        entry->sx = 1;
        entry->dx = ((pos[1] - entry->px) << 16) / 8;
    } else {
        entry->sx = -1;
        entry->dx = ((entry->px - pos[1]) << 16) / 8;
    }
    if (entry->py <= pos[0]) {
        entry->sy = 1;
        entry->dy = ((pos[0] - entry->py) << 16) / 8;
    } else {
        entry->sy = -1;
        entry->dy = ((entry->py - pos[0]) << 16) / 8;
    }
}

static void PCBox_SetupMonSwapEntries(PCBoxWork *work, u32 from, u32 to) {
    PCBoxMoveWork *moveWork = work->view->temp;
    moveWork->entries[0].from = from;
    moveWork->entries[0].to = to;
    moveWork->entries[0].active = 1;
    PCBox_SetupMoveEntryToSlot(work, &moveWork->entries[0]);
    moveWork->entries[1].from = to;
    moveWork->entries[1].to = from;
    moveWork->entries[1].active = 1;
    PCBox_SetupMoveEntryToSlot(work, &moveWork->entries[1]);
}

void PCBox_SetupMonMove(PCBoxWork *work, u32 from, u32 to) {
    PCBoxMoveWork *moveWork;
    u32 sA;
    u32 sC;
    u32 sB;
    u32 i;
    u32 count;
    moveWork = work->view->temp;
    work->view->showOutlineAfterMove = 1;
    for (i = 0; i < 7; i++) {
        moveWork->entries[i].from = 0;
        moveWork->entries[i].to = 0;
        moveWork->entries[i].active = 0;
    }
    moveWork->sel = to;
    if (to == 0xFF || from == to || PCBox_CanMoveMon(work, from, to) == 0) {
        moveWork->from = 0xFF;
        moveWork->to = 0xFF;
        moveWork->entries[0].from = from;
        moveWork->entries[0].to = from;
        moveWork->entries[0].active = 1;
        PCBox_SetupMoveEntryToSlot(work, &moveWork->entries[0]);
        return;
    }
    moveWork->from = from;
    moveWork->to = to;
    count = Party_GetCount(work->party);
    if ((to & 0x80) != 0) {
        if (from < PC_BOX_SLOT_PARTY_START) {
            moveWork->entries[0].from = from;
            moveWork->entries[0].to = to;
            moveWork->entries[0].active = 1;
            PCBox_SetupMoveEntryToSlot(work, &moveWork->entries[0]);
            work->view->showOutlineAfterMove = 0;
            return;
        }
        sA = from - PC_BOX_SLOT_PARTY_START;
        for (i = sA + 1; i < PARTY_SIZE; i++) {
            moveWork->entries[i].from = i + PC_BOX_SLOT_PARTY_START;
            moveWork->entries[i].to = i + 29;
            moveWork->entries[i].active = 1;
            PCBox_SetupMoveEntryToSlot(work, &moveWork->entries[i]);
        }
        moveWork->entries[sA].from = from;
        moveWork->entries[sA].to = to;
        moveWork->entries[sA].active = 1;
        PCBox_SetupMoveEntryToSlot(work, &moveWork->entries[sA]);
        work->view->showOutlineAfterMove = 0;
        return;
    }
    if (from < PC_BOX_SLOT_PARTY_START) {
        if (to < PC_BOX_SLOT_PARTY_START) {
            PCBox_SetupMonSwapEntries(work, from, to);
            return;
        }
        if (to - PC_BOX_SLOT_PARTY_START < count) {
            PCBox_SetupMonSwapEntries(work, from, to);
            return;
        }
        PCBox_SetupMonSwapEntries(work, from, count + PC_BOX_SLOT_PARTY_START);
        return;
    }
    if (to < PC_BOX_SLOT_PARTY_START) {
        if (PCBox_GetSlotMonData(work, to, MON_DATA_SPECIES_EXISTS, NULL) != 0) {
            PCBox_SetupMonSwapEntries(work, from, to);
            return;
        }
        sB = from - PC_BOX_SLOT_PARTY_START;
        for (i = sB + 1; i < count; i++) {
            moveWork->entries[i].from = i + PC_BOX_SLOT_PARTY_START;
            moveWork->entries[i].to = i + 29;
            moveWork->entries[i].active = 1;
            PCBox_SetupMoveEntryToSlot(work, &moveWork->entries[i]);
        }
        moveWork->entries[sB].from = from;
        moveWork->entries[sB].to = to;
        moveWork->entries[sB].active = 1;
        PCBox_SetupMoveEntryToSlot(work, &moveWork->entries[sB]);
        moveWork->entries[count].from = to;
        moveWork->entries[count].to = count + 29;
        moveWork->entries[count].active = 1;
        PCBox_SetupMoveEntryToSlot(work, &moveWork->entries[count]);
        return;
    }
    if (to - PC_BOX_SLOT_PARTY_START < count) {
        PCBox_SetupMonSwapEntries(work, from, to);
        return;
    }
    sC = from - PC_BOX_SLOT_PARTY_START;
    for (i = sC + 1; i < count; i++) {
        moveWork->entries[i].from = i + PC_BOX_SLOT_PARTY_START;
        moveWork->entries[i].to = i + 29;
        moveWork->entries[i].active = 1;
        PCBox_SetupMoveEntryToSlot(work, &moveWork->entries[i]);
    }
    moveWork->entries[sC].from = from;
    moveWork->entries[sC].to = count + 29;
    moveWork->entries[sC].active = 1;
    PCBox_SetupMoveEntryToSlot(work, &moveWork->entries[sC]);
}

void PCBox_SetupDepositMoveEntries(PCBoxWork *work, u32 from, u32 to) {
    PCBoxMoveWork *moveWork;
    u32 slot;
    u32 i;
    u32 count;
    moveWork = work->view->temp;
    work->view->showOutlineAfterMove = 1;
    for (i = 0; i < 7; i++) {
        moveWork->entries[i].from = 0;
        moveWork->entries[i].to = 0;
        moveWork->entries[i].active = 0;
    }
    if (to == 0xFF || PCBox_CanMovePartyMonToEmptySlot(work, from, to) == 0) {
        moveWork->from = 0xFF;
        moveWork->to = 0xFF;
        moveWork->entries[0].from = from;
        moveWork->entries[0].to = from;
        moveWork->entries[0].active = 1;
        PCBox_SetupMoveEntryToSlot(work, &moveWork->entries[0]);
        return;
    }
    moveWork->from = from;
    moveWork->to = to;
    count = Party_GetCount(work->party);
    if (to < PC_BOX_SLOT_PARTY_START) {
        slot = from - PC_BOX_SLOT_PARTY_START;
        for (i = slot + 1; i < count; i++) {
            moveWork->entries[i].from = i + PC_BOX_SLOT_PARTY_START;
            moveWork->entries[i].to = i + 29;
            moveWork->entries[i].active = 1;
            PCBox_SetupMoveEntryToSprite(work, &moveWork->entries[i]);
        }
        moveWork->entries[slot].from = from;
        moveWork->entries[slot].to = to;
        moveWork->entries[slot].active = 1;
        PCBox_SetupMoveEntryToSprite(work, &moveWork->entries[slot]);
        moveWork->entries[count].from = to;
        moveWork->entries[count].to = count + 29;
        moveWork->entries[count].active = 1;
        PCBox_SetupMoveEntryToSprite(work, &moveWork->entries[count]);
        work->view->showOutlineAfterMove = 0;
    }
}

void PCBox_SetupMonMoveToPartyEnd(PCBoxWork *work, u32 from, u32 to) {
    PCBoxView *view = work->view;
    PCBoxMoveWork *moveWork = view->temp;
    u32 i;
    view->showOutlineAfterMove = 1;
    for (i = 0; i < 7; i++) {
        moveWork->entries[i].from = 0;
        moveWork->entries[i].to = 0;
        moveWork->entries[i].active = 0;
    }
    if (to == 0xFF || PCBox_GetSlotMonData(work, to, MON_DATA_SPECIES_EXISTS, NULL) != 0) {
        moveWork->from = 0xFF;
        moveWork->to = 0xFF;
        moveWork->entries[0].from = from;
        moveWork->entries[0].to = from;
        moveWork->entries[0].active = 1;
        PCBox_SetupMoveEntryToSlot(work, &moveWork->entries[0]);
    } else {
        moveWork->from = from;
        moveWork->to = to;
        PCBox_SetupMonSwapEntries(work, from, Party_GetCount(work->party) + PC_BOX_SLOT_PARTY_START);
    }
}

u32 PCBox_GetMoveEntryTarget(PCBoxWork *work, u32 from) {
    PCBoxMoveWork *moveWork = work->view->temp;
    u32 i;
    for (i = 0; i < 7; i++) {
        if (moveWork->entries[i].active == 1 && moveWork->entries[i].from == from) {
            return moveWork->entries[i].to;
        }
    }
    return 0xFF;
}

void PCBox_SetupPartyShiftAfterRelease(PCBoxWork *work, u32 releasedSlot) {
    PCBoxMoveWork *moveWork = work->view->temp;
    u32 i;
    u32 slot = releasedSlot - PC_BOX_SLOT_PARTY_START;
    for (i = 0; i < PARTY_SIZE; i++) {
        moveWork->entries[i].from = i + PC_BOX_SLOT_PARTY_START;
        moveWork->entries[i].to = i + PC_BOX_SLOT_PARTY_START;
        moveWork->entries[i].active = 0;
    }
    moveWork->entries[i].active = 0;
    for (i = slot + 1; i < PARTY_SIZE; i++) {
        moveWork->entries[i].to = i + 29;
        moveWork->entries[i].active = 1;
        PCBox_SetupMoveEntryToSlot(work, &moveWork->entries[i]);
    }
    moveWork->entries[slot].to = 0x23;
    moveWork->entries[slot].active = 1;
    PCBox_SetupMoveEntryToSlot(work, &moveWork->entries[slot]);
}

void PCBox_ApplyMoveEntryIcons(PCBoxWork *work, PCBoxMoveEntry *entry) {
    u8 tmp[7];
    u32 i;
    for (i = 0; i < 7; i++) {
        if (entry[i].active != 0) {
            tmp[i] = work->view->slotIcons[entry[i].from];
        }
    }
    for (i = 0; i < 7; i++) {
        if (entry[i].active != 0) {
            if ((entry[i].to & 0x80) == 0) {
                work->view->slotIcons[entry[i].to] = tmp[i];
                PCBox_SetIconLayer(work->view, entry[i].to, 1);
            } else {
                if (entry[i].from >= PC_BOX_SLOT_PARTY_START) {
                    work->view->slotIcons[35] = tmp[i];
                }
                PCBox_SetIconLayer(work->view, entry[i].from, 1);
            }
        }
    }
}

static s32 PCBox_GetReleaseCheckMoveIndex(u16 move) {
    u32 i;
    for (i = 0; i < 4; i++) {
        if (move == gPCBoxReleaseCheckMoves[i]) {
            return i;
        }
    }
    return -1;
}

void PCBox_StartReleaseMoveCheck(PCBoxWork *work) {
    PCBoxView *view;
    PCBoxReleaseWork *releaseWork;
    BoxPokemon *boxmon;
    u32 i;
    s32 idx;
    work->view->releaseWork = Heap_AllocAtEnd(HEAP_ID_10, sizeof(PCBoxReleaseWork));
    view = work->view;
    releaseWork = view->releaseWork;
    releaseWork->sprite = view->sprites[view->slotIcons[work->selectedSlot]];
    releaseWork->scanIndex = 0;
    releaseWork->moveFlags = 0;
    boxmon = PCBox_GetSlotBoxMon(work, work->activeBox, work->selectedSlot);
    for (i = 0; i < MAX_MON_MOVES; i++) {
        idx = PCBox_GetReleaseCheckMoveIndex((u16)GetBoxMonData(boxmon, MON_DATA_MOVE1 + i, NULL));
        if (idx != -1) {
            releaseWork->moveFlags |= 1 << idx;
            return;
        }
    }
}

void PCBox_FreeReleaseMoveCheck(PCBoxWork *work) {
    Heap_Free(work->view->releaseWork);
}

u32 PCBox_RunReleaseMoveCheck(PCBoxWork *work) {
    PCBoxReleaseWork *releaseWork;
    u16 idx;
    u32 count;
    BoxPokemon *boxmon;
    u32 i;
    s32 bit;
    u32 boxId;
    u32 slot;

    releaseWork = work->view->releaseWork;
    idx = releaseWork->scanIndex;
    if (idx == NUM_BOXES * MONS_PER_BOX + PARTY_SIZE) {
        return 0;
    }
    for (count = 0; count < 15; count++) {
        if (idx < NUM_BOXES * MONS_PER_BOX) {
            boxId = idx / MONS_PER_BOX;
            slot = idx % MONS_PER_BOX;
            if (boxId == work->activeBox && slot == work->selectedSlot) {
                boxmon = NULL;
            } else {
                boxmon = PCBox_GetSlotBoxMon(work, boxId, slot);
            }
        } else {
            slot = idx - NUM_BOXES * MONS_PER_BOX;
            if (slot == work->selectedSlot - PC_BOX_SLOT_PARTY_START) {
                boxmon = NULL;
            } else {
                boxmon = PCBox_GetSlotBoxMon(work, 0xFF, slot);
            }
        }
        if (boxmon != NULL && GetBoxMonData(boxmon, MON_DATA_SPECIES_EXISTS, NULL) != 0) {
            for (i = 0; i < MAX_MON_MOVES; i++) {
                bit = PCBox_GetReleaseCheckMoveIndex((u16)GetBoxMonData(boxmon, MON_DATA_MOVE1 + i, NULL));
                if (bit != -1) {
                    releaseWork->moveFlags &= 0xFF ^ (1 << bit);
                }
            }
        }
        releaseWork->scanIndex++;
        idx = releaseWork->scanIndex;
        if (idx == NUM_BOXES * MONS_PER_BOX + PARTY_SIZE) {
            return 0;
        }
    }
    return 1;
}

static PCBoxMonInfo *PCBox_CreateMonInfo(BoxPokemon *boxMon) {
    PCBoxMonInfo *monInfo;
    u32 i;

    if (GetBoxMonData(boxMon, MON_DATA_SPECIES_EXISTS, NULL) != 0) {
        monInfo = Heap_Alloc(HEAP_ID_10, sizeof(PCBoxMonInfo));
        monInfo->boxMon = boxMon;
        monInfo->species = GetBoxMonData(boxMon, MON_DATA_SPECIES, NULL);
        monInfo->heldItem = GetBoxMonData(boxMon, MON_DATA_HELD_ITEM, NULL);
        monInfo->personality = GetBoxMonData(boxMon, MON_DATA_PERSONALITY, NULL);
        monInfo->type1 = GetBoxMonData(boxMon, MON_DATA_TYPE_1, NULL);
        monInfo->type2 = GetBoxMonData(boxMon, MON_DATA_TYPE_2, NULL);
        monInfo->ability = GetBoxMonData(boxMon, MON_DATA_ABILITY, NULL);
        monInfo->nature = GetBoxMonNature(boxMon);
        monInfo->markings = GetBoxMonData(boxMon, MON_DATA_MARKINGS, NULL);
        monInfo->level = GetBoxMonData(boxMon, MON_DATA_LEVEL, NULL);
        monInfo->isEgg = GetBoxMonData(boxMon, MON_DATA_IS_EGG, NULL);
        monInfo->gender = GetBoxMonGender(boxMon);
        if (monInfo->species != SPECIES_NIDORAN_F && monInfo->species != SPECIES_NIDORAN_M && monInfo->isEgg == 0) {
            monInfo->showGender = 1;
        } else {
            monInfo->showGender = 0;
        }
        for (i = 0; i < MAX_MON_MOVES; i++) {
            monInfo->moves[i] = GetBoxMonData(boxMon, MON_DATA_MOVE1 + i, NULL);
        }
    } else {
        monInfo = NULL;
    }
    return monInfo;
}

static void PCBox_FreeMonInfo(PCBoxMonInfo *monInfo) {
    Heap_Free(monInfo);
}

static void PCBox_DrawMonInfo(PCBoxWork *work, PCBoxMonInfo *monInfo) {
    u32 base = PCBox_DrawMoveWindows(work, monInfo);
    u32 i;

    for (i = 0; i < 4; i++) {
        BgCellManager_PutWindowTiles(work->view->panels, PC_BOX_PANEL_INFO, &work->view->windows[base + i]);
    }
    PCBox_HideMovesPanel(work->view->panels);
    PCBox_ShowMonPic(work, monInfo, 2);
    PCBox_SetSpriteVisible(work->view, (work->view->monPicBuffer ^ 1) + 2, 1);
    PCBox_SetSpriteVisible(work->view, work->view->monPicBuffer + 2, 0);
    PCBox_DrawTypeIcons(work->view, monInfo);
    PCBox_PrintMonInfo(work, monInfo);
    PCBox_DrawMarkings(work, monInfo->markings);
}

static void PCBox_DrawMonItemInfo(PCBoxWork *work, PCBoxMonInfo *monInfo) {
    u32 base;

    if (monInfo->heldItem != ITEM_NONE) {
        base = PCBox_PrintItemNameAndDesc(work, monInfo->heldItem);
        BgCellManager_PutWindowTiles(work->view->panels, PC_BOX_PANEL_INFO, &work->view->windows[base]);
        BgCellManager_PutWindowTiles(work->view->panels, PC_BOX_PANEL_INFO, &work->view->windows[base + 1]);
        PCBox_LoadInfoItemIcon(work->view, monInfo->heldItem);
    }
    PCBox_HideItemInfoPanel(work->view->panels);
    PCBox_ShowMonPic(work, monInfo, 2);
    PCBox_SetSpriteVisible(work->view, (work->view->monPicBuffer ^ 1) + 2, 1);
    PCBox_SetSpriteVisible(work->view, work->view->monPicBuffer + 2, 0);
    PCBox_DrawTypeIcons(work->view, monInfo);
    PCBox_PrintMonInfo(work, monInfo);
    PCBox_DrawMarkings(work, monInfo->markings);
}

BOOL PCBox_ShowSlotMonInfo(PCBoxWork *work, u32 index) {
    PCBoxMonInfo *monInfo;
    u32 lock;
    BoxPokemon *boxMon = PCBox_GetSlotBoxMon(work, work->activeBox, index);

    if (boxMon != NULL) {
        lock = AcquireBoxMonLock(boxMon);
        monInfo = PCBox_CreateMonInfo(boxMon);
        if (monInfo != NULL) {
            if (work->args->mode == PC_BOX_MODE_MOVE_ITEMS) {
                PCBox_DrawMonItemInfo(work, monInfo);
            } else {
                PCBox_DrawMonInfo(work, monInfo);
            }
            PCBox_FreeMonInfo(monInfo);
        } else {
            PCBox_ClearMonInfo(work);
            ReleaseBoxMonLock(boxMon, lock);
            return FALSE;
        }
        ReleaseBoxMonLock(boxMon, lock);
    } else {
        PCBox_ClearMonInfo(work);
        return FALSE;
    }
    return TRUE;
}

void PCBox_RedrawSlotMonInfo(PCBoxWork *work, u32 index) {
    BoxPokemon *boxMon = PCBox_GetSlotBoxMon(work, work->activeBox, index);
    u32 lock = AcquireBoxMonLock(boxMon);
    PCBoxMonInfo *monInfo = PCBox_CreateMonInfo(boxMon);

    PCBox_ShowMonPic(work, monInfo, 2);
    PCBox_SetSpriteVisible(work->view, (work->view->monPicBuffer ^ 1) + 2, 1);
    PCBox_SetSpriteVisible(work->view, work->view->monPicBuffer + 2, 0);
    PCBox_DrawTypeIcons(work->view, monInfo);
    PCBox_PrintMonInfo(work, monInfo);
    PCBox_FreeMonInfo(monInfo);
    ReleaseBoxMonLock(boxMon, lock);
}

void PCBox_ClearMonInfo(PCBoxWork *work) {
    PCBox_SetSpriteVisible(work->view, 2, 0);
    PCBox_SetSpriteVisible(work->view, 3, 0);
    PCBox_SetSpriteVisible(work->view, 0xd, 0);
    PCBox_SetSpriteVisible(work->view, 0xe, 0);
    PCBox_ClearMonInfoWindows(work->view);
    PCBox_DrawMarkings(work, 0);
    if (work->args->mode == PC_BOX_MODE_MOVE_ITEMS) {
        PCBox_HideItemInfoPanel(work->view->panels);
    } else {
        PCBox_HideMovesPanel(work->view->panels);
    }
}

void PCBox_ClearMonInfoAndSelection(PCBoxWork *work) {
    PCBox_ClearMonInfo(work);
    PCBox_SetSelectedIconOutlineVisible(work, 0);
    work->selectedSlot = PC_BOX_SLOT_NONE;
}

static void PCBox_LoadWallpaperChars(PCBoxWork *work, s32 member, u32 unused, u32 offset) {
    NNSG2dCharacterData *data;
    void *allocation = GfGfxLoader_GetCharData(NARC_a_0_1_9, member + 0x10, TRUE, &data, HEAP_ID_10);

    BG_LoadCharTilesData(work->view->bgConfig, GF_BG_LYR_MAIN_3, data->pRawData, data->szByte, offset);
    PCBox_DrawBoxNameOnWallpaper(work, (u8 *)data->pRawData + 0x2a0, offset + 0x15, 0x15, 3);
    Heap_Free(allocation);
}

static void PCBox_LoadWallpaperPalette(PCBoxWork *work, s32 member, u32 palette) {
    GfGfxLoader_GXLoadPal(NARC_a_0_1_9, member + 0x28, GF_PAL_LOCATION_MAIN_BG, (enum GFPalSlotOffset)(palette << 5), 0x20, HEAP_ID_10);
}

static void PCBox_LoadWallpaperTilemap(PCBoxWork *work, s32 unused, u32 tile, u32 addend, u32 palette) {
    NNSG2dScreenData *screen;
    void *allocation;
    u16 *raw;
    u8 row;
    u32 x;
    u8 column;
    u16 *src;
    u16 value;

    allocation = GfGfxLoader_GetScrnData(NARC_a_0_1_9, 0xf, TRUE, &screen, HEAP_ID_10);
    raw = (u16 *)screen->rawData;
    for (row = 0; row < 0x14; row++) {
        src = raw + row * 0x15;
        x = tile;
        for (column = 0; column < 0x15; column++) {
            value = (src[column] & 0xfff) + (palette << 12) + addend;
            LoadRectToBgTilemapRect(work->view->bgConfig, GF_BG_LYR_MAIN_3, &value, x, row + 1, 1, 1);
            x++;
            if (x >= 0x40) {
                x = 0;
            }
        }
    }
    Heap_Free(allocation);
    FillBgTilemapRect(work->view->bgConfig, GF_BG_LYR_MAIN_3, 0x1001, x, 0, 2, 0x14, 0x11);
}

static void PCBox_LoadWallpaper(PCBoxWork *work, s32 member, u32 tile, u32 offset, u32 palette) {
    PCBox_LoadWallpaperChars(work, member, tile, offset);
    PCBox_LoadWallpaperPalette(work, member, palette);
    PCBox_LoadWallpaperTilemap(work, member, tile, offset, palette);
    ScheduleBgTilemapBufferTransfer(work->view->bgConfig, GF_BG_LYR_MAIN_3);
}

void PCBox_LoadScrolledWallpaper(PCBoxWork *work, s32 member, u32 direction) {
    u32 x;
    u32 tile;

    if (direction == 0) {
        work->view->wallpaperScroll -= 0x17;
        if (work->view->wallpaperScroll < 0) {
            work->view->wallpaperScroll += 0x40;
        }
    } else if (direction == 1) {
        work->view->wallpaperScroll += 0x17;
        if (work->view->wallpaperScroll >= 0x40) {
            work->view->wallpaperScroll -= 0x40;
        }
    }
    if (work->view->wallpaperBuffer == 0) {
        x = 0x25c;
        tile = 0xe;
    } else {
        x = 0xb8;
        tile = 0xf;
    }
    work->view->wallpaperBuffer ^= 1;
    PCBox_LoadWallpaper(work, member, work->view->wallpaperScroll, x, tile);
}

void PCBox_SwapWallpaper(PCBoxWork *work, s32 member) {
    u32 x;
    u32 tile;

    if (work->view->wallpaperBuffer == 0) {
        x = 0x25c;
        tile = 0xe;
    } else {
        x = 0xb8;
        tile = 0xf;
    }
    work->view->wallpaperBuffer ^= 1;
    PCBox_LoadWallpaperChars(work, member, work->view->wallpaperScroll, x);
    PaletteData_LoadNarc(work->view->paletteData, NARC_a_0_1_9, member + 0x28, HEAP_ID_10, PLTTBUF_MAIN_BG, 0x20, tile << 4);
    PCBox_LoadWallpaperTilemap(work, member, work->view->wallpaperScroll, x, tile);
    ScheduleBgTilemapBufferTransfer(work->view->bgConfig, GF_BG_LYR_MAIN_3);
}

u32 PCBox_GetWallpaperGfxIndex(PCBoxWork *work, u32 box) {
    u32 wallpaper = PCStorage_GetBoxWallpaper(work->storage, box);
    if (wallpaper >= 0x10) {
        wallpaper -= 0x10;
    }
    return wallpaper;
}

static u32 PCBox_IsPointInRect(s32 x, s32 y, const u8 *rect) {
    if (x >= rect[0] && x <= rect[1] && y >= rect[2] && y < rect[3]) {
        return 1;
    }
    return 0;
}

u32 PCBox_GetTouchedBoxSlot(s16 x, s16 y) {
    if (PCBox_IsPointInRect(x, y, gPCBoxSlotGridRect) == 1) {
        if (x < 12) {
            x = 0;
        } else if (x >= 156) {
            x = 5;
        } else {
            x = (s16)((x - 12) / 24);
        }
        return x + (s16)((y - 40) / 24) * 6;
    }
    return 0xff;
}

u32 PCBox_GetTouchedPartySlot(s16 x, s16 y, const u8 *rect) {
    u32 i;
    for (i = 0; i < PARTY_SIZE; i++, rect += 4) {
        if (PCBox_IsPointInRect(x, y, rect) == 1) {
            return i + PC_BOX_SLOT_PARTY_START;
        }
    }
    return 0xff;
}

u32 PCBox_GetTouchedTrayBox(s16 x, s16 y) {
    u32 i;
    const u8 *rect = gPCBoxTrayRects;
    for (i = 0; i < 6; i++, rect += 4) {
        if (PCBox_IsPointInRect(x, y, rect) == 1) {
            return i + 0x80;
        }
    }
    return 0xff;
}
