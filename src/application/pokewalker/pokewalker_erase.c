// Pokewalker connection app, modes 1 and 2: a message that leaves the app, and erasing the Pokewalker's records.

#include "global.h"

#include "application/pokewalker/pokewalker_app.h"
#include "application/pokewalker/pokewalker_app_internal.h"
#include "msgdata/msg/msg_0274.h"

#include "math_util.h"
#include "message_format.h"
#include "pokemon_storage_system.h"
#include "save.h"
#include "save_arrays.h"
#include "screen_fade.h"
#include "sound_playback.h"
#include "system.h"
#include "text.h"
#include "touchscreen.h"

static void PokewalkerApp_ReturnWalkerMonToBox(PokewalkerApp *app);

enum QuitMessageState {
    QUIT_MESSAGE_PRINT,
    QUIT_MESSAGE_WAIT_PRINT,
    QUIT_MESSAGE_WAIT_INPUT,
    QUIT_MESSAGE_END,
    QUIT_MESSAGE_DONE,
};

enum EraseRecordsState {
    ERASE_RECORDS_PRINT_CAUTION,
    ERASE_RECORDS_WAIT_CAUTION,
    ERASE_RECORDS_HANDLE_CAUTION_YES_NO,
    ERASE_RECORDS_PRINT_WILL_ERASE,
    ERASE_RECORDS_SHOW_ERASE_MENU,
    ERASE_RECORDS_HANDLE_ERASE_MENU,
    ERASE_RECORDS_END_ERASE_MENU,
    ERASE_RECORDS_PRINT_CARRY_OVER_STEPS,
    ERASE_RECORDS_WAIT_CARRY_OVER_STEPS,
    ERASE_RECORDS_SHOW_CARRY_OVER_STEPS_MENU,
    ERASE_RECORDS_HANDLE_CARRY_OVER_STEPS_MENU,
    ERASE_RECORDS_PRINT_CONNECT,
    ERASE_RECORDS_WAIT_MESSAGE,
    ERASE_RECORDS_PRINT_POINT_AT_CARD,
    ERASE_RECORDS_WAIT_POINT_AT_CARD,
    ERASE_RECORDS_PREPARE_LINK,
    ERASE_RECORDS_START_LINK,
    ERASE_RECORDS_UPDATE_LINK,
    ERASE_RECORDS_PRINT_CANCELED,
    ERASE_RECORDS_WAIT_CANCELED,
    ERASE_RECORDS_PRINT_INITIALIZED,
    ERASE_RECORDS_WAIT_INITIALIZED,
    ERASE_RECORDS_PRINT_COME_BACK,
    ERASE_RECORDS_WAIT_COME_BACK,
    ERASE_RECORDS_SHOW_RETURNED_MON,
    ERASE_RECORDS_ANIMATE_RETURNED_MON,
    ERASE_RECORDS_AFTER_ANIMATION,
    ERASE_RECORDS_PRINT_ARRIVED,
    ERASE_RECORDS_WAIT_ARRIVED,
    ERASE_RECORDS_PRINT_SAVING,
    ERASE_RECORDS_WAIT_SAVING,
    ERASE_RECORDS_SAVE,
    ERASE_RECORDS_END_SAVE,
    ERASE_RECORDS_WAIT_CURSOR,
    ERASE_RECORDS_END,
    ERASE_RECORDS_DONE,
};

int PokewalkerApp_QuitMessage_Enter(PokewalkerApp *app) {
    BeginNormalPaletteFade(FADE_BOTH_SCREENS, FADE_TYPE_BRIGHTNESS_IN, FADE_TYPE_BRIGHTNESS_IN, RGB_BLACK, 6, 1, HEAP_ID_154);
    return POKEWALKER_APP_STATE_UPDATE;
}

int PokewalkerApp_QuitMessage_Update(PokewalkerApp *app) {
    app->state = gQuitMessageStates[app->state](app);
    if (app->state == QUIT_MESSAGE_DONE) {
        app->nextMode = POKEWALKER_APP_MODE_EXIT;
        app->state = 0;
        return POKEWALKER_APP_STATE_EXIT;
    }
    return POKEWALKER_APP_STATE_UPDATE;
}

int PokewalkerApp_QuitMessage_Exit(PokewalkerApp *app) {
    return POKEWALKER_APP_STATE_ENTER;
}

int PokewalkerApp_QuitMessage_Print(PokewalkerApp *app) {
    app->textPrinterId = PokewalkerApp_StartMessageBox(app, 2, msg_0274_00147);
    return QUIT_MESSAGE_WAIT_PRINT;
}

int PokewalkerApp_QuitMessage_WaitPrint(PokewalkerApp *app) {
    if (TextPrinterCheckActive(app->textPrinterId) == FALSE) {
        return QUIT_MESSAGE_WAIT_INPUT;
    }
    return QUIT_MESSAGE_WAIT_PRINT;
}

int PokewalkerApp_QuitMessage_WaitInput(PokewalkerApp *app) {
    if (gSystem.newKeys & PAD_BUTTON_A || gSystem.touchNew) {
        return QUIT_MESSAGE_END;
    }
    return QUIT_MESSAGE_WAIT_INPUT;
}

int PokewalkerApp_QuitMessage_End(PokewalkerApp *app) {
    return QUIT_MESSAGE_DONE;
}

int PokewalkerApp_EraseRecords_Enter(PokewalkerApp *app) {
    FillBgTilemapRect(app->bgConfig, GF_BG_LYR_SUB_0, 0, 0, 0, 32, 24, TILEMAP_FILL_KEEP_PAL);
    FillBgTilemapRect(app->bgConfig, GF_BG_LYR_SUB_1, 0, 0, 0, 32, 24, TILEMAP_FILL_KEEP_PAL);
    FillBgTilemapRect(app->bgConfig, GF_BG_LYR_MAIN_1, 0, 0, 0, 32, 24, TILEMAP_FILL_KEEP_PAL);
    FillBgTilemapRect(app->bgConfig, GF_BG_LYR_MAIN_2, 0, 0, 0, 32, 24, TILEMAP_FILL_KEEP_PAL);
    PokewalkerApp_HideConnectionSprites(app);
    PokewalkerApp_HideSprite(app, 7);
    BgCommitTilemapBufferToVram(app->bgConfig, GF_BG_LYR_SUB_0);
    BgCommitTilemapBufferToVram(app->bgConfig, GF_BG_LYR_SUB_1);
    BgCommitTilemapBufferToVram(app->bgConfig, GF_BG_LYR_MAIN_1);
    BgCommitTilemapBufferToVram(app->bgConfig, GF_BG_LYR_MAIN_2);
    return POKEWALKER_APP_STATE_UPDATE;
}

int PokewalkerApp_EraseRecords_Update(PokewalkerApp *app) {
    app->state = gEraseRecordsStates[app->state](app);
    if (app->state == ERASE_RECORDS_DONE) {
        app->state = 0;
        return POKEWALKER_APP_STATE_EXIT;
    }
    PokewalkerApp_UpdateParticles(app);
    return POKEWALKER_APP_STATE_UPDATE;
}

int PokewalkerApp_EraseRecords_Exit(PokewalkerApp *app) {
    PokewalkerApp_HideSprite(app, 8);
    PokewalkerApp_HideConnectionSprites(app);
    return POKEWALKER_APP_STATE_ENTER;
}

int PokewalkerApp_EraseRecords_PrintCaution(PokewalkerApp *app) {
    app->textPrinterId = PokewalkerApp_StartMessageBox(app, 2, msg_0274_00003);
    return ERASE_RECORDS_WAIT_CAUTION;
}

int PokewalkerApp_EraseRecords_WaitCaution(PokewalkerApp *app) {
    if (!TextPrinterCheckActive(app->textPrinterId)) {
        PokewalkerApp_ShowYesNoMenu(app, 1);
        return ERASE_RECORDS_HANDLE_CAUTION_YES_NO;
    }
    return ERASE_RECORDS_WAIT_CAUTION;
}

int PokewalkerApp_EraseRecords_HandleCautionYesNo(PokewalkerApp *app) {
    switch (PokewalkerApp_HandleTwoChoiceMenu(app)) {
    case 0:
        PokewalkerApp_HideCursor(app);
        FillBgTilemapRect(app->bgConfig, GF_BG_LYR_MAIN_1, 0, 0, 16, 32, 8, TILEMAP_FILL_KEEP_PAL);
        ClearWindowTilemapAndCopyToVram(&app->windows[3]);
        ClearWindowTilemapAndCopyToVram(&app->windows[4]);
        return ERASE_RECORDS_PRINT_WILL_ERASE;
    case 1:
        app->nextMode = POKEWALKER_APP_MODE_EXIT;
        return ERASE_RECORDS_END;
    default:
        return ERASE_RECORDS_HANDLE_CAUTION_YES_NO;
    }
}

int PokewalkerApp_EraseRecords_PrintWillErase(PokewalkerApp *app) {
    app->textPrinterId = PokewalkerApp_StartMessageBox(app, 0, msg_0274_00004);
    FillBgTilemapRect(app->bgConfig, GF_BG_LYR_MAIN_2, 0, 0, 0, 32, 24, TILEMAP_FILL_KEEP_PAL);
    BgCommitTilemapBufferToVram(app->bgConfig, GF_BG_LYR_MAIN_2);
    return ERASE_RECORDS_SHOW_ERASE_MENU;
}

int PokewalkerApp_EraseRecords_ShowEraseMenu(PokewalkerApp *app) {
    if (!TextPrinterCheckActive(app->textPrinterId)) {
        PokewalkerApp_PrintString(app, 5, app->eraseRecordsText, 4, MAKE_TEXT_COLOR(15, 1, 0));
        PokewalkerApp_LoadTilemap(app, GF_BG_LYR_MAIN_2, 10);
        PokewalkerApp_PrintExit(app, 1);
        PokewalkerApp_SetCursorPosition(app, 2);
        return ERASE_RECORDS_HANDLE_ERASE_MENU;
    }
    return ERASE_RECORDS_SHOW_ERASE_MENU;
}

int PokewalkerApp_EraseRecords_HandleEraseMenu(PokewalkerApp *app) {
    int selection = PokewalkerApp_GetTouchedButton(1);
    if (selection != TOUCH_MENU_NO_INPUT) {
        PokewalkerApp_SelectMenuItem(app, selection, selection + 2, 6);
        PlaySE(SEQ_SE_DP_DECIDE);
        return ERASE_RECORDS_WAIT_CURSOR;
    }
    if (gSystem.newKeys & PAD_KEY_UP) {
        if (app->menuSelection != 0) {
            PlaySE(SEQ_SE_DP_SELECT);
        }
        PokewalkerApp_SetCursorPosition(app, 2);
        app->menuSelection = 0;
    } else if (gSystem.newKeys & PAD_KEY_DOWN) {
        if (app->menuSelection != 1) {
            PlaySE(SEQ_SE_DP_SELECT);
        }
        PokewalkerApp_SetCursorPosition(app, 3);
        app->menuSelection = 1;
    } else if (gSystem.newKeys & PAD_BUTTON_A) {
        PlaySE(SEQ_SE_DP_DECIDE);
        selection = app->menuSelection;
        PokewalkerApp_SelectMenuItem(app, selection, selection + 2, 6);
        return ERASE_RECORDS_WAIT_CURSOR;
    } else if (gSystem.newKeys & PAD_BUTTON_B) {
        PlaySE(SEQ_SE_DP_SELECT);
        PokewalkerApp_SelectMenuItem(app, 1, 3, 6);
        return ERASE_RECORDS_WAIT_CURSOR;
    }
    return ERASE_RECORDS_HANDLE_ERASE_MENU;
}

int PokewalkerApp_EraseRecords_EndEraseMenu(PokewalkerApp *app) {
    PokewalkerApp_HideCursor(app);
    ClearWindowTilemapAndCopyToVram(&app->windows[5]);
    FillBgTilemapRect(app->bgConfig, GF_BG_LYR_MAIN_1, 0, 0, 16, 32, 8, TILEMAP_FILL_KEEP_PAL);
    if (app->menuSelection == 0) {
        return ERASE_RECORDS_PRINT_CONNECT;
    }
    app->nextMode = POKEWALKER_APP_MODE_EXIT;
    return ERASE_RECORDS_END;
}

int PokewalkerApp_EraseRecords_PrintCarryOverSteps(PokewalkerApp *app) {
    FillBgTilemapRect(app->bgConfig, GF_BG_LYR_MAIN_2, 0, 0, 0, 32, 24, TILEMAP_FILL_KEEP_PAL);
    FillBgTilemapRect(app->bgConfig, GF_BG_LYR_MAIN_1, 0, 0, 0, 32, 24, TILEMAP_FILL_KEEP_PAL);
    BgCommitTilemapBufferToVram(app->bgConfig, GF_BG_LYR_MAIN_1);
    BgCommitTilemapBufferToVram(app->bgConfig, GF_BG_LYR_MAIN_2);
    app->textPrinterId = PokewalkerApp_StartMessageBox(app, 2, msg_0274_00009);
    return ERASE_RECORDS_WAIT_CARRY_OVER_STEPS;
}

int PokewalkerApp_EraseRecords_WaitCarryOverSteps(PokewalkerApp *app) {
    if (TextPrinterCheckActive(app->textPrinterId) == FALSE) {
        return ERASE_RECORDS_SHOW_CARRY_OVER_STEPS_MENU;
    } else {
        return ERASE_RECORDS_WAIT_CARRY_OVER_STEPS;
    }
}

int PokewalkerApp_EraseRecords_ShowCarryOverStepsMenu(PokewalkerApp *app) {
    PokewalkerApp_ShowSaveEraseStepsMenu(app, 1);
    return ERASE_RECORDS_HANDLE_CARRY_OVER_STEPS_MENU;
}

int PokewalkerApp_EraseRecords_HandleCarryOverStepsMenu(PokewalkerApp *app) {
    switch (PokewalkerApp_HandleTwoChoiceMenu(app)) {
    case 0:
        PokewalkerApp_HideCursor(app);
        FillBgTilemapRect(app->bgConfig, GF_BG_LYR_MAIN_1, 0, 0, 16, 32, 8, TILEMAP_FILL_KEEP_PAL);
        ClearWindowTilemapAndCopyToVram(&app->windows[3]);
        ClearWindowTilemapAndCopyToVram(&app->windows[4]);
        app->eraseSteps = FALSE;
        return ERASE_RECORDS_PRINT_CONNECT;
    case 1:
        FillBgTilemapRect(app->bgConfig, GF_BG_LYR_MAIN_1, 0, 0, 16, 32, 8, TILEMAP_FILL_KEEP_PAL);
        ClearWindowTilemapAndCopyToVram(&app->windows[3]);
        ClearWindowTilemapAndCopyToVram(&app->windows[4]);
        PokewalkerApp_HideCursor(app);
        app->eraseSteps = TRUE;
        return ERASE_RECORDS_PRINT_CONNECT;
    }
    return ERASE_RECORDS_HANDLE_CARRY_OVER_STEPS_MENU;
}

int PokewalkerApp_EraseRecords_PrintConnect(PokewalkerApp *app) {
    BgClearTilemapBufferAndCommit(app->bgConfig, GF_BG_LYR_SUB_0);
    BgClearTilemapBufferAndCommit(app->bgConfig, GF_BG_LYR_SUB_1);
    BgClearTilemapBufferAndCommit(app->bgConfig, GF_BG_LYR_MAIN_1);
    BgClearTilemapBufferAndCommit(app->bgConfig, GF_BG_LYR_MAIN_2);
    PokewalkerApp_StartMessage(app, 2, msg_0274_00016, 13);
    return ERASE_RECORDS_WAIT_MESSAGE;
}

int PokewalkerApp_EraseRecords_WaitMessage(PokewalkerApp *app) {
    if (!TextPrinterCheckActive(app->textPrinterId)) {
        app->state = app->nextState;
        return app->state;
    }
    return ERASE_RECORDS_WAIT_MESSAGE;
}

int PokewalkerApp_EraseRecords_PrintPointAtCard(PokewalkerApp *app) {
    BgClearTilemapBufferAndCommit(app->bgConfig, GF_BG_LYR_MAIN_1);
    FillBgTilemapRect(app->bgConfig, GF_BG_LYR_MAIN_2, 0, 0, 0, 32, 24, TILEMAP_FILL_KEEP_PAL);
    PokewalkerApp_LoadTilemap(app, GF_BG_LYR_MAIN_2, 14);
    PokewalkerApp_PrintExit(app, 1);
    PokewalkerApp_StartSubBgScroll(app);
    app->textPrinterId = PokewalkerApp_StartMessageBox(app, 0, msg_0274_00005);
    return ERASE_RECORDS_WAIT_POINT_AT_CARD;
}

int PokewalkerApp_EraseRecords_WaitPointAtCard(PokewalkerApp *app) {
    if (!TextPrinterCheckActive(app->textPrinterId) && app->subBgScrollX == 0x100) {
        PokewalkerApp_ShowConnectionSprites(app, 2);
        return ERASE_RECORDS_PREPARE_LINK;
    }
    return ERASE_RECORDS_WAIT_POINT_AT_CARD;
}

int PokewalkerApp_EraseRecords_PrepareLink(PokewalkerApp *app) {
    PokewalkerIr_RequestEraseRecords(TRUE);
    MIi_CpuClearFast(0, (u32 *)&app->irBlocks, sizeof(PokewalkerIrBlocks));
    MIi_CpuClearFast(0, (u32 *)&app->irStatus, sizeof(PokewalkerIrStatus));
    return ERASE_RECORDS_START_LINK;
}

int PokewalkerApp_EraseRecords_StartLink(PokewalkerApp *app) {
    PokewalkerApp_StartLink(app);
    return ERASE_RECORDS_UPDATE_LINK;
}

int PokewalkerApp_EraseRecords_UpdateLink(PokewalkerApp *app) {
    int nextState = ERASE_RECORDS_UPDATE_LINK;
    switch (PokewalkerIr_GetAndClearError()) {
    case 2:
        nextState = ERASE_RECORDS_PRINT_CANCELED;
        break;
    case 4:
        nextState = ERASE_RECORDS_PRINT_CANCELED;
        break;
    case 5:
        nextState = ERASE_RECORDS_PRINT_CANCELED;
        break;
    case 7:
        nextState = ERASE_RECORDS_PRINT_CANCELED;
        break;
    case 8:
        nextState = ERASE_RECORDS_PRINT_CANCELED;
        break;
    case 9:
        nextState = ERASE_RECORDS_PRINT_CANCELED;
        break;
    case 11:
        nextState = ERASE_RECORDS_PRINT_CANCELED;
        break;
    case 12:
        nextState = ERASE_RECORDS_PRINT_CANCELED;
        break;
    case 15:
        ManagedSprite_SetDrawFlag(app->sprites[2], FALSE);
        PokewalkerApp_ReturnWalkerMonToBox(app);
        Pokewalker_Reset(app->pokewalker);
        app->walkerSteps = 0;
        app->walkerWatts = 0;
        PokewalkerIr_Stop();
        return ERASE_RECORDS_PRINT_INITIALIZED;
    }
    if (nextState != 17) {
        PokewalkerIr_Stop();
    }
    if (!PokewalkerIrStatus_IsConnected()) {
        PokewalkerApp_ShowSubBg1(app, TRUE);
        if (PokewalkerApp_GetTouchedButton(5) == 0 || (gSystem.newKeys & PAD_BUTTON_A) || (gSystem.newKeys & PAD_BUTTON_B)) {
            PokewalkerIr_Stop();
            PokewalkerApp_SelectMenuItem(app, 1, 3, 18);
            PlaySE(SEQ_SE_DP_SELECT);
            return ERASE_RECORDS_WAIT_CURSOR;
        }
    } else {
        PokewalkerApp_ShowSubBg1(app, FALSE);
    }
    return nextState;
}

// Puts the Pokemon on the Pokewalker back into a PC box (preferably the one it came from); remembers the box,
// or -1 if there was no Pokemon.
static void PokewalkerApp_ReturnWalkerMonToBox(PokewalkerApp *app) {
    u16 strollState;
    u16 box2;
    int box = -1;
    int slot = 0;
    PCStorage *storage = SaveArray_PCStorage_Get(app->saveData);
    BoxPokemon *boxMon = &app->returnedMon;
    Pokewalker_GetStrollState(app->pokewalker, &strollState, &box2);
    if (Pokewalker_TryGetBoxMon(app->pokewalker, boxMon)) {
        box = box2;
        PCStorage_FindFirstEmptySlot(storage, &box, &slot);
        PCStorage_PlaceMonInBoxByIndexPair(storage, box, slot, boxMon);
        app->returnedMonBox = box;
    } else {
        app->returnedMonBox = -1;
    }
}

int PokewalkerApp_EraseRecords_PrintCanceled(PokewalkerApp *app) {
    app->textPrinterId = PokewalkerApp_StartMessageBox(app, 0, msg_0274_00033);
    PokewalkerApp_HideCursor(app);
    FillBgTilemapRect(app->bgConfig, GF_BG_LYR_MAIN_2, 0, 0, 0, 32, 24, TILEMAP_FILL_KEEP_PAL);
    return ERASE_RECORDS_WAIT_CANCELED;
}

int PokewalkerApp_EraseRecords_WaitCanceled(PokewalkerApp *app) {
    if (!TextPrinterCheckActive(app->textPrinterId)) {
        app->nextMode = POKEWALKER_APP_MODE_EXIT;
        return ERASE_RECORDS_END;
    }
    return ERASE_RECORDS_WAIT_CANCELED;
}

int PokewalkerApp_EraseRecords_PrintInitialized(PokewalkerApp *app) {
    FillBgTilemapRect(app->bgConfig, GF_BG_LYR_MAIN_2, 0, 0, 0, 32, 24, TILEMAP_FILL_KEEP_PAL);
    FillBgTilemapRect(app->bgConfig, GF_BG_LYR_SUB_1, 0, 0, 0, 64, 24, TILEMAP_FILL_KEEP_PAL);
    BgCommitTilemapBufferToVram(app->bgConfig, GF_BG_LYR_MAIN_2);
    BgCommitTilemapBufferToVram(app->bgConfig, GF_BG_LYR_SUB_1);
    app->textPrinterId = PokewalkerApp_StartMessageBox(app, 2, msg_0274_00031);
    FillBgTilemapRect(app->bgConfig, GF_BG_LYR_MAIN_2, 0, 0, 0, 32, 24, TILEMAP_FILL_KEEP_PAL);
    return ERASE_RECORDS_WAIT_INITIALIZED;
}

int PokewalkerApp_EraseRecords_WaitInitialized(PokewalkerApp *app) {
    if (!TextPrinterCheckActive(app->textPrinterId)) {
        app->nextMode = POKEWALKER_APP_MODE_MAIN_MENU;
        return ERASE_RECORDS_PRINT_COME_BACK;
    }
    return ERASE_RECORDS_WAIT_INITIALIZED;
}

int PokewalkerApp_EraseRecords_PrintComeBack(PokewalkerApp *app) {
    if (app->returnedMonBox >= 0) {
        BufferBoxMonNickname(app->msgFormat, 1, &app->returnedMon);
        app->textPrinterId = PokewalkerApp_StartMessageBox(app, 2, msg_0274_00026);
        return ERASE_RECORDS_WAIT_COME_BACK;
    }
    return ERASE_RECORDS_PRINT_SAVING;
}

int PokewalkerApp_EraseRecords_WaitComeBack(PokewalkerApp *app) {
    if (TextPrinterCheckActive(app->textPrinterId) == FALSE) {
        return ERASE_RECORDS_SHOW_RETURNED_MON;
    }
    return ERASE_RECORDS_WAIT_COME_BACK;
}

int PokewalkerApp_EraseRecords_ShowReturnedMon(PokewalkerApp *app) {
    app->timer = 0;
    PokewalkerApp_HideSprite(app, 8);
    PokewalkerApp_LoadMonPicture(&app->returnedMon, app->monSpriteBuffer, &app->monPicTemplate, 0);
    return ERASE_RECORDS_ANIMATE_RETURNED_MON;
}

int PokewalkerApp_EraseRecords_AnimateReturnedMon(PokewalkerApp *app) {
    app->timer++;
    if (app->timer > 180) {
        PokewalkerApp_ShowSprite(app, 8);
        return ERASE_RECORDS_AFTER_ANIMATION;
    }
    if ((u32)app->timer > MTRandom() % 180) {
        PokewalkerApp_SpawnFallingParticle(app);
    }
    return ERASE_RECORDS_ANIMATE_RETURNED_MON;
}

int PokewalkerApp_EraseRecords_AfterAnimation(PokewalkerApp *app) {
    return ERASE_RECORDS_PRINT_ARRIVED;
}

int PokewalkerApp_EraseRecords_PrintArrived(PokewalkerApp *app) {
    app->textPrinterId = PokewalkerApp_StartMessageBox(app, 2, msg_0274_00027);
    return ERASE_RECORDS_WAIT_ARRIVED;
}

int PokewalkerApp_EraseRecords_WaitArrived(PokewalkerApp *app) {
    if (TextPrinterCheckActive(app->textPrinterId) == FALSE) {
        return ERASE_RECORDS_PRINT_SAVING;
    }
    return ERASE_RECORDS_WAIT_ARRIVED;
}

int PokewalkerApp_EraseRecords_PrintSaving(PokewalkerApp *app) {
    app->textPrinterId = PokewalkerApp_StartMessageBox(app, 2, msg_0274_00013);
    return ERASE_RECORDS_WAIT_SAVING;
}

int PokewalkerApp_EraseRecords_WaitSaving(PokewalkerApp *app) {
    if (!TextPrinterCheckActive(app->textPrinterId)) {
        PokewalkerApp_CreateWaitingIcon(app);
        return ERASE_RECORDS_SAVE;
    }
    return ERASE_RECORDS_WAIT_SAVING;
}

int PokewalkerApp_EraseRecords_Save(PokewalkerApp *app) {
    SaveGameNormal(app->saveData);
    Save_ClearStatusFlags(app->saveData);
    return ERASE_RECORDS_END_SAVE;
}

int PokewalkerApp_EraseRecords_EndSave(PokewalkerApp *app) {
    PokewalkerApp_DeleteWaitingIcon(app);
    app->nextMode = POKEWALKER_APP_MODE_MAIN_MENU;
    return ERASE_RECORDS_END;
}

int PokewalkerApp_EraseRecords_WaitCursor(PokewalkerApp *app) {
    if (!ManagedSprite_IsAnimated(app->sprites[0])) {
        app->state = app->nextState;
        return app->state;
    }
    return ERASE_RECORDS_WAIT_CURSOR;
}

int PokewalkerApp_EraseRecords_End(PokewalkerApp *app) {
    PokewalkerApp_HideCursor(app);
    return ERASE_RECORDS_DONE;
}

void PokewalkerApp_SelectMenuItem(PokewalkerApp *app, int selection, int cursorPosition, int nextState) {
    app->menuSelection = selection;
    PokewalkerApp_SetCursorPosition(app, cursorPosition);
    PokewalkerApp_PressCursor(app);
    app->nextState = nextState;
}

void PokewalkerApp_StartMessage(PokewalkerApp *app, int window, int msgId, int nextState) {
    app->textPrinterId = PokewalkerApp_StartMessageBox(app, window, msgId);
    app->nextState = nextState;
}
