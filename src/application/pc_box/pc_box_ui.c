#include "global.h"

#include "constants/items.h"
#include "constants/pokemon.h"
#include "constants/sndseq.h"

#include "application/bag/bag_app.h"
#include "application/pc_box/pc_box_internal.h"

#include "bag.h"
#include "bag_view.h"
#include "bg_cell_manager.h"
#include "bg_window.h"
#include "filesystem.h"
#include "gf_gfx_planes.h"
#include "grid_input_handler.h"
#include "heap.h"
#include "msgdata.h"
#include "naming_screen.h"
#include "overlay_manager.h"
#include "palette.h"
#include "party.h"
#include "player_data.h"
#include "poke_overlay.h"
#include "pokedex_util.h"
#include "pokemon_storage_system.h"
#include "pokemon_summary.h"
#include "render_window.h"
#include "save_special_ribbons.h"
#include "screen_fade.h"
#include "sound_playback.h"
#include "sprite_system.h"
#include "sys_task_api.h"
#include "touchpad.h"
#include "touchscreen.h"
#include "yes_no_prompt.h"

FS_EXTERN_OVERLAY(OVY_15);

static void PCBox_StartHeldItemMoveWithIcon(PCBoxWork *work, u32 fromSlot, u32 toSlot, u32 partyLayout);
static void PCBox_StartHeldItemMoveFromDropTarget(PCBoxWork *work, int toSlot, int partyLayout);
static BOOL PCBox_UpdateHeldItemMove(PCBoxWork *work, int toItemIcon);
static u32 PCBox_UpdateHeldItemMoveWithIcon(PCBoxWork *work);
static u32 PCBox_UpdateHeldItemMoveNoIcon(PCBoxWork *work);
static void PCBox_LoadPanelTilemap(BgCellManager *panels, u32 index, u32 fileId);
static void PCBox_DrawMarkingMenuEntry(PCBoxWork *work, u32 index);
static void PCBox_LowerPartyPanel(BgCellManager *panels);
static void PCBox_RaisePartyPanel(BgCellManager *panels);
static u32 PCBox_UpdatePartyPanelSlide(PCBoxWork *work);
static u32 PCBox_UpdatePartyPanelMove(PCBoxWork *work);
static void PCBox_HidePartyButton(PCBoxWork *work);
static void PCBox_HideTrayTab(PCBoxWork *work);
static void PCBox_HideActionMenu(BgCellManager *panels);
static u32 PCBox_UpdateActionMenuSlide(BgCellManager *panels);
static void PCBox_HideChangeBoxButton(BgCellManager *panels);
static void PCBox_SlideInChangeBoxButton(BgCellManager *panels);
static void PCBox_HideSummaryButton(BgCellManager *panels);
static void PCBox_ShowBoxMenuPanels(BgCellManager *panels);

static void PCBox_StartHeldItemMove(PCBoxWork *work, int fromSlot, int toSlot, int partyLayout, int toItemIcon) {
    struct {
        s16 y, x;
    } old;

    struct {
        s16 y, x;
    } dest;

    PCBoxHeldItemMove *move = work->view->temp;
    int x, y, delta, destX, destY;

    ManagedSprite_GetPositionXY(work->view->sprites[PC_BOX_SPRITE_HELD_ITEM], &old.x, &old.y);
    PCBox_GetSlotPosition(toSlot, &dest.x, &dest.y, partyLayout);
    if (toItemIcon == 1) {
        dest.x += 8;
        dest.y += 8;
    } else {
        dest.y += 4;
    }
    move->toSlot = toSlot;
    move->fromSlot = fromSlot;
    move->frames = 0;
    move->partyLayout = partyLayout;
    destX = dest.x;
    x = old.x;
    if (x > destX) {
        move->xNegative = 1;
        delta = x - destX;
    } else {
        move->xNegative = 0;
        delta = destX - x;
    }
    move->dx = (delta << 8) / 8;
    destY = dest.y;
    y = old.y;
    if (y > destY) {
        move->yNegative = 1;
        delta = y - destY;
    } else {
        move->yNegative = 0;
        delta = destY - y;
    }
    move->dy = (delta << 8) / 8;
    move->x = x << 8;
    move->y = y << 8;
}

static void PCBox_StartHeldItemMoveWithIcon(PCBoxWork *work, u32 fromSlot, u32 toSlot, u32 partyLayout) {
    PCBox_StartHeldItemMove(work, fromSlot, toSlot, partyLayout, 1);
}

static void PCBox_StartHeldItemMoveFromDropTarget(PCBoxWork *work, int toSlot, int partyLayout) {
    PCBox_StartHeldItemMove(work, work->view->dropTarget, toSlot, partyLayout, 0);
}

static BOOL PCBox_UpdateHeldItemMove(PCBoxWork *work, int toItemIcon) {
    PCBoxView *view = work->view;
    PCBoxHeldItemMove *move = view->temp;

    if (move->frames == 8) {
        if (toItemIcon == 1) {
            PCBox_MoveHeldItemIconToSlot(view, move->toSlot, move->partyLayout);
        } else {
            PCBox_PlaceHeldItemIconAtSlot(view, move->toSlot, move->partyLayout);
        }
        PCBox_UpdateHeldItemIconOutline(work->view);
        return FALSE;
    }
    if (move->xNegative == 0) {
        move->x += move->dx;
    } else {
        move->x -= move->dx;
    }
    if (move->yNegative == 0) {
        move->y += move->dy;
    } else {
        move->y -= move->dy;
    }
    PCBox_SetHeldItemIconPosition(work->view, move->x >> 8, move->y >> 8);
    PCBox_UpdateHeldItemIconOutline(work->view);
    move->frames++;
    return TRUE;
}

static u32 PCBox_UpdateHeldItemMoveWithIcon(PCBoxWork *work) {
    return PCBox_UpdateHeldItemMove(work, 1);
}

static u32 PCBox_UpdateHeldItemMoveNoIcon(PCBoxWork *work) {
    return PCBox_UpdateHeldItemMove(work, 0);
}

void PCBox_InitPanels(PCBoxWork *work) {
    work->view->panels = BgCellManager_New(work->view->bgConfig, 2, PC_BOX_PANEL_COUNT, HEAP_ID_10);
    BgCellManager_InitCell(work->view->panels, PC_BOX_PANEL_WALLPAPER_LIST, 1, 32, 7);
    BgCellManager_InitCell(work->view->panels, PC_BOX_PANEL_PARTY, 1, 11, 18);
    BgCellManager_InitCell(work->view->panels, PC_BOX_PANEL_MARKING_MENU, 0, 11, 18);
    BgCellManager_InitCell(work->view->panels, PC_BOX_PANEL_TITLE, 0, 11, 6);
    PCBox_AttachPanelWindows(work->view);
    PCBox_AttachPartyButtonWindow(work->view);
    PCBox_AttachTrayTabWindow(work->view);
    PCBox_AttachReturnButtonWindow(work->view);
    PCBox_AttachMenuExitButtonWindow(work);
    if (work->args->mode == PC_BOX_MODE_DEPOSIT) {
        BgCellManager_InitCell(work->view->panels, PC_BOX_PANEL_BOX_TRAY, 0, 32, 7);
        PCBox_LoadPanelTilemap(work->view->panels, PC_BOX_PANEL_BOX_TRAY, 12);
    } else {
        BgCellManager_InitCell(work->view->panels, PC_BOX_PANEL_BOX_TRAY, 1, 32, 6);
        PCBox_LoadPanelTilemap(work->view->panels, PC_BOX_PANEL_BOX_TRAY, 11);
    }
    PCBox_LoadPanelTilemap(work->view->panels, PC_BOX_PANEL_WALLPAPER_LIST, 13);
    if ((u32)work->args->mode <= 1) {
        PCBox_LoadPanelTilemap(work->view->panels, PC_BOX_PANEL_PARTY, 9);
    } else {
        PCBox_LoadPartyPanelTilemap(work->view->panels, 1);
        PCBox_AttachPartyPanelLabelWindow(work->view);
    }
    if (work->args->mode == PC_BOX_MODE_MOVE_ITEMS) {
        BgCellManager_InitCell(work->view->panels, PC_BOX_PANEL_INFO, 6, 32, 9);
        BgCellManager_DrawCellAt(work->view->panels, PC_BOX_PANEL_INFO, 0, 24);
        PCBox_LoadPanelTilemap(work->view->panels, PC_BOX_PANEL_INFO, 85);
    } else {
        BgCellManager_InitCell(work->view->panels, PC_BOX_PANEL_INFO, 6, 12, 10);
        BgCellManager_DrawCellAt(work->view->panels, PC_BOX_PANEL_INFO, 32, 12);
        PCBox_LoadPanelTilemap(work->view->panels, PC_BOX_PANEL_INFO, 86);
    }
    PCBox_LoadPanelTilemap(work->view->panels, PC_BOX_PANEL_MARKING_MENU, 10);
    PCBox_AttachMarkingMenuWindows(work->view);
    PCBox_HideActionMenu(work->view->panels);
    PCBox_HideChangeBoxButton(work->view->panels);
    PCBox_HideSummaryButton(work->view->panels);
}

void PCBox_FreePanels(PCBoxView *view) {
    BgCellManager_Delete(view->panels);
}

static void PCBox_LoadPanelTilemap(BgCellManager *panels, u32 index, u32 fileId) {
    BgCellManager_LoadCellTilemap(panels, index, 0x13, fileId, 1);
}

static void PCBox_DrawMarkingMenuEntry(PCBoxWork *work, u32 index) {
    u16 *map = BgCellManager_GetCellTilemap(work->view->panels, PC_BOX_PANEL_MARKING_MENU);
    u8 row = (index / 2) * 3 + 2;
    u8 col = (index % 2) * 4 + 3;
    u16 *rowTiles = map + row * 11;
    u16 *tile = rowTiles + col;
    if (!(work->view->markings & (1 << index))) {
        index += 11;
    } else {
        index += 43;
    }
    index = (u16)index;
    *tile = (*tile & 0xF000) + index;
}

void PCBox_DrawMarkingMenu(PCBoxWork *work) {
    u32 i;
    for (i = 0; i < 6; i++) {
        PCBox_DrawMarkingMenuEntry(work, i);
    }
}

void PCBox_ToggleMarking(PCBoxWork *work, int bit) {
    PCBoxView *view = work->view;
    view->markings ^= 1 << bit;
    PCBox_DrawMarkingMenuEntry(work, bit);
    BgCellManager_DrawCellAt(work->view->panels, PC_BOX_PANEL_MARKING_MENU, 21, 6);
}

void PCBox_SlideInMarkingMenu(BgCellManager *panels) {
    BgCellManager_DrawCellAt(panels, PC_BOX_PANEL_MARKING_MENU, 0x15, 0x18);
    BgCellManager_StartCellMove(panels, PC_BOX_PANEL_MARKING_MENU, 0, -1, 0x12);
}

void PCBox_SlideOutMarkingMenu(BgCellManager *panels) {
    BgCellManager_StartCellMove(panels, PC_BOX_PANEL_MARKING_MENU, 0, 1, 0x12);
}

void PCBox_PlacePartyPanelLeft(BgCellManager *panels) {
    BgCellManager_DrawCellAt(panels, PC_BOX_PANEL_PARTY, 2, 6);
}

void PCBox_PlacePartyPanelRight(BgCellManager *panels) {
    BgCellManager_DrawCellAt(panels, PC_BOX_PANEL_PARTY, 0x15, 6);
}

void PCBox_ClearPartyPanelTiles(PCBoxWork *work) {
    PCBoxView *view = work->view;
    FillBgTilemapRect(view->bgConfig, GF_BG_LYR_MAIN_1, 0, 2, 0x15, 0x0B, 0x12, 0x10);
}

void PCBox_PlacePartyPanelLeftHidden(BgCellManager *panels) {
    BgCellManager_DrawCellAt(panels, PC_BOX_PANEL_PARTY, 2, 0x18);
}

void PCBox_PlacePartyPanelRightHidden(BgCellManager *panels) {
    BgCellManager_DrawCellAt(panels, PC_BOX_PANEL_PARTY, 0x15, 0x18);
}

void PCBox_SlideInPartyPanel(BgCellManager *panels) {
    s8 xy[2];
    BgCellManager_GetCellPosition(panels, PC_BOX_PANEL_PARTY, &xy[1], &xy[0]);
    if (xy[0] != 6) {
        BgCellManager_StartCellMove(panels, PC_BOX_PANEL_PARTY, 0, -1, (u8)(xy[0] - 6));
        if (xy[1] == 2) {
            BgCellManager_DrawCellAt(panels, PC_BOX_PANEL_RETURN_BUTTON, 0x18, (s8)(xy[0] + 15));
            BgCellManager_StartCellMove(panels, PC_BOX_PANEL_RETURN_BUTTON, 0, -1, (u8)(xy[0] - 6));
        }
    }
}

void PCBox_SlideOutPartyPanel(BgCellManager *panels) {
    s8 xy[2];
    BgCellManager_GetCellPosition(panels, PC_BOX_PANEL_PARTY, &xy[1], &xy[0]);
    if (xy[0] != 0x18) {
        BgCellManager_StartCellMove(panels, PC_BOX_PANEL_PARTY, 0, 1, (u8)(0x18 - xy[0]));
        if (xy[1] == 2) {
            BgCellManager_DrawCellAt(panels, PC_BOX_PANEL_RETURN_BUTTON, 0x18, (s8)(xy[0] + 15));
            BgCellManager_StartCellMove(panels, PC_BOX_PANEL_RETURN_BUTTON, 0, 1, (u8)(0x18 - xy[0]));
        }
    }
}

static void PCBox_LowerPartyPanel(BgCellManager *panels) {
    struct {
        s8 y, x;
    } v;

    BgCellManager_GetCellPosition(panels, PC_BOX_PANEL_PARTY, &v.x, &v.y);
    if (v.y != 24) {
        BgCellManager_StartCellMove(panels, PC_BOX_PANEL_PARTY, 0, 1, (u8)(24 - v.y));
    }
}

static void PCBox_RaisePartyPanel(BgCellManager *panels) {
    struct {
        s8 y, x;
    } v;

    BgCellManager_GetCellPosition(panels, PC_BOX_PANEL_PARTY, &v.x, &v.y);
    if (v.y != 6) {
        BgCellManager_StartCellMove(panels, PC_BOX_PANEL_PARTY, 0, -1, (u8)(v.y - 6));
    }
}

void PCBox_ShiftPartyPanelAndReturnButtonRight(BgCellManager *panels) {
    BgCellManager_StartCellMove(panels, PC_BOX_PANEL_PARTY, 1, 0, 0x13);
    BgCellManager_StartCellMove(panels, PC_BOX_PANEL_RETURN_BUTTON, 1, 0, 0x13);
}

void PCBox_ShiftPartyPanelRight(BgCellManager *panels) {
    BgCellManager_StartCellMove(panels, PC_BOX_PANEL_PARTY, 1, 0, 0x13);
}

void PCBox_ShiftPartyPanelAndReturnButtonLeft(BgCellManager *panels) {
    BgCellManager_StartCellMove(panels, PC_BOX_PANEL_PARTY, -1, 0, 0x13);
    BgCellManager_DrawCellAt(panels, PC_BOX_PANEL_RETURN_BUTTON, 0x2B, 0x15);
    BgCellManager_StartCellMove(panels, PC_BOX_PANEL_RETURN_BUTTON, -1, 0, 0x13);
}

void PCBox_ShiftPartyPanelLeft(BgCellManager *panels) {
    BgCellManager_StartCellMove(panels, PC_BOX_PANEL_PARTY, -1, 0, 0x13);
}

static u32 PCBox_UpdatePartyPanelSlide(PCBoxWork *work) {
    s8 pos[4];
    u32 panelMoving, returnButtonMoving;
    BgCellManager_GetCellPosition(work->view->panels, PC_BOX_PANEL_PARTY, &pos[3], &pos[2]);
    panelMoving = BgCellManager_UpdateCellMove(work->view->panels, PC_BOX_PANEL_PARTY);
    returnButtonMoving = BgCellManager_UpdateCellMove(work->view->panels, PC_BOX_PANEL_RETURN_BUTTON);
    BgCellManager_UpdateCellMove(work->view->panels, PC_BOX_PANEL_SUMMARY_BUTTON);
    BgCellManager_GetCellPosition(work->view->panels, PC_BOX_PANEL_PARTY, &pos[1], &pos[0]);
    if (pos[3] != pos[1] || pos[2] != pos[0]) {
        PCBox_UpdatePartyIconPositions(work);
    }
    if (panelMoving == 0 && returnButtonMoving == 0) {
        return 0;
    }
    return 1;
}

static u32 PCBox_UpdatePartyPanelMove(PCBoxWork *work) {
    s8 pos[4];
    u32 panelMoving;
    BgCellManager_GetCellPosition(work->view->panels, PC_BOX_PANEL_PARTY, &pos[3], &pos[2]);
    panelMoving = BgCellManager_UpdateCellMove(work->view->panels, PC_BOX_PANEL_PARTY);
    BgCellManager_GetCellPosition(work->view->panels, PC_BOX_PANEL_PARTY, &pos[1], &pos[0]);
    if (pos[3] != pos[1] || pos[2] != pos[0]) {
        PCBox_UpdatePartyIconPositions(work);
    }
    if (panelMoving != 0) {
        return 1;
    }
    return 0;
}

void PCBox_LoadPartyPanelTilemap(BgCellManager *panels, u32 index) {
    PCBox_LoadPanelTilemap(panels, index, 8);
}

void PCBox_SlideInWallpaperList(BgCellManager *panels) {
    BgCellManager_DrawCellAt(panels, PC_BOX_PANEL_WALLPAPER_LIST, 0, -7);
    BgCellManager_StartCellMove(panels, PC_BOX_PANEL_WALLPAPER_LIST, 0, 1, 7);
}

void PCBox_SlideOutWallpaperList(BgCellManager *panels) {
    BgCellManager_DrawCellAt(panels, PC_BOX_PANEL_WALLPAPER_LIST, 0, 0);
    BgCellManager_StartCellMove(panels, PC_BOX_PANEL_WALLPAPER_LIST, 0, -1, 7);
}

void PCBox_ShowPartyButton(PCBoxWork *work) {
    PCBox_DrawPartyButton(work, 0);
    BgCellManager_DrawCellAt(work->view->panels, PC_BOX_PANEL_PARTY_BUTTON, 0, 21);
}

static void PCBox_HidePartyButton(PCBoxWork *work) {
    BgCellManager_DrawCellAt(work->view->panels, PC_BOX_PANEL_PARTY_BUTTON, 0, 0x18);
}

void PCBox_SlideOutPartyButton(BgCellManager *panels) {
    BgCellManager_StartCellMove(panels, PC_BOX_PANEL_PARTY_BUTTON, 0, 1, 3);
}

void PCBox_SlideInPartyButton(BgCellManager *panels) {
    BgCellManager_StartCellMove(panels, PC_BOX_PANEL_PARTY_BUTTON, 0, -1, 3);
}

void PCBox_ShowTrayTab(PCBoxWork *work) {
    PCBox_DrawTrayTab(work, 0);
    BgCellManager_DrawCellAt(work->view->panels, PC_BOX_PANEL_TRAY_TAB, 12, 21);
}

static void PCBox_HideTrayTab(PCBoxWork *work) {
    BgCellManager_DrawCellAt(work->view->panels, PC_BOX_PANEL_TRAY_TAB, 0xc, 0x18);
}

void PCBox_SlideOutTrayTab(BgCellManager *panels) {
    BgCellManager_StartCellMove(panels, PC_BOX_PANEL_TRAY_TAB, 0, 1, 3);
}

void PCBox_SlideInTrayTab(BgCellManager *panels) {
    BgCellManager_StartCellMove(panels, PC_BOX_PANEL_TRAY_TAB, 0, -1, 3);
}

void PCBox_ShowReturnButton(PCBoxWork *work) {
    PCBox_DrawReturnButton(work, 0);
    BgCellManager_DrawCellAt(work->view->panels, PC_BOX_PANEL_RETURN_BUTTON, 0x18, 0x15);
}

void PCBox_ShowExitButton(PCBoxWork *work) {
    PCBox_DrawExitButton(work, 0);
    BgCellManager_DrawCellAt(work->view->panels, PC_BOX_PANEL_RETURN_BUTTON, 0x18, 0x15);
}

void PCBox_HideReturnButton(BgCellManager *panels) {
    BgCellManager_EraseCell(panels, PC_BOX_PANEL_RETURN_BUTTON);
    BgCellManager_DrawCellAt(panels, PC_BOX_PANEL_RETURN_BUTTON, 0x18, 0x18);
}

void PCBox_SlideOutReturnButton(BgCellManager *panels) {
    BgCellManager_StartCellMove(panels, PC_BOX_PANEL_RETURN_BUTTON, 0, 1, 3);
}

void PCBox_SlideInReturnButton(BgCellManager *panels) {
    BgCellManager_DrawCellAt(panels, PC_BOX_PANEL_RETURN_BUTTON, 0x18, 0x18);
    BgCellManager_StartCellMove(panels, PC_BOX_PANEL_RETURN_BUTTON, 0, -1, 3);
}

BOOL PCBox_IsMenuExitButtonShown(BgCellManager *panels) {
    s8 x;
    s8 y;
    BgCellManager_GetCellPosition(panels, PC_BOX_PANEL_MENU_EXIT_BUTTON, &x, &y);
    return y == 0x15;
}

void PCBox_HidePartyButtonAndTrayTab(BgCellManager *panels) {
    BgCellManager_EraseCell(panels, PC_BOX_PANEL_PARTY_BUTTON);
    BgCellManager_EraseCell(panels, PC_BOX_PANEL_TRAY_TAB);
    BgCellManager_DrawCellAt(panels, PC_BOX_PANEL_PARTY_BUTTON, 0, 0x18);
    BgCellManager_DrawCellAt(panels, PC_BOX_PANEL_TRAY_TAB, 0xc, 0x18);
}

static void PCBox_HideActionMenu(BgCellManager *panels) {
    u32 i;
    s32 y;
    for (i = 0, y = 5; i < 5; i++, y += 3) {
        BgCellManager_DrawCellAt(panels, i + PC_BOX_PANEL_MENU_ROW_0, 0x20, (s8)y);
    }
    BgCellManager_DrawCellAt(panels, PC_BOX_PANEL_MENU_EXIT_BUTTON, 0x18, 0x18);
}

void PCBox_ShowActionMenu(BgCellManager *panels) {
    u32 i;
    s32 y;
    for (i = 0, y = 5; i < 5; i++, y += 3) {
        BgCellManager_DrawCellAt(panels, i + PC_BOX_PANEL_MENU_ROW_0, 0x15, (s8)y);
    }
    BgCellManager_DrawCellAt(panels, PC_BOX_PANEL_MENU_EXIT_BUTTON, 0x18, 0x15);
}

void PCBox_ResetActionMenu(BgCellManager *panels) {
    u32 i;
    s32 y;
    for (i = 0, y = 5; i < 5; i++, y += 3) {
        BgCellManager_EraseCell(panels, i + PC_BOX_PANEL_MENU_ROW_0);
        BgCellManager_DrawCellAt(panels, i + PC_BOX_PANEL_MENU_ROW_0, 0x20, (s8)y);
    }
    BgCellManager_EraseCell(panels, PC_BOX_PANEL_MENU_EXIT_BUTTON);
    BgCellManager_DrawCellAt(panels, PC_BOX_PANEL_MENU_EXIT_BUTTON, 0x18, 0x18);
}

void PCBox_SlideInActionMenu(BgCellManager *panels) {
    u16 i;
    s8 x;
    s8 y;
    BgCellManager_GetCellPosition(panels, PC_BOX_PANEL_MENU_ROW_0, &x, &y);
    if (x == 0x15) {
        return;
    }
    for (i = 0; i < 5; i++) {
        BgCellManager_StartCellMove(panels, i + PC_BOX_PANEL_MENU_ROW_0, -1, 0, (u8)(x - 0x15));
    }
    BgCellManager_GetCellPosition(panels, PC_BOX_PANEL_MENU_EXIT_BUTTON, &x, &y);
    BgCellManager_StartCellMove(panels, PC_BOX_PANEL_MENU_EXIT_BUTTON, 0, -1, (u8)(y - 0x15));
}

void PCBox_SlideOutActionMenu(BgCellManager *panels) {
    u16 i;
    s8 x;
    s8 y;
    BgCellManager_GetCellPosition(panels, PC_BOX_PANEL_MENU_ROW_0, &x, &y);
    if (x == 0x20) {
        return;
    }
    for (i = 0; i < 5; i++) {
        BgCellManager_StartCellMove(panels, i + PC_BOX_PANEL_MENU_ROW_0, 1, 0, (u8)(0x20 - x));
    }
    BgCellManager_GetCellPosition(panels, PC_BOX_PANEL_MENU_EXIT_BUTTON, &x, &y);
    BgCellManager_StartCellMove(panels, PC_BOX_PANEL_MENU_EXIT_BUTTON, 0, 1, (u8)(0x18 - y));
}

static u32 PCBox_UpdateActionMenuSlide(BgCellManager *panels) {
    u32 i;
    u32 ret = FALSE;
    for (i = 0; i < 5; i++) {
        if (BgCellManager_UpdateCellMove(panels, i + PC_BOX_PANEL_MENU_ROW_0) == TRUE) {
            ret = TRUE;
        }
    }
    if (BgCellManager_UpdateCellMove(panels, PC_BOX_PANEL_MENU_EXIT_BUTTON) == TRUE) {
        ret = TRUE;
    }
    return ret;
}

BOOL PCBox_IsActionMenuOpen(BgCellManager *panels) {
    s8 x;
    s8 y;
    BgCellManager_GetCellPosition(panels, PC_BOX_PANEL_MENU_ROW_0, &x, &y);
    return x != 0x20;
}

void PCBox_SlideInTitlePanel(BgCellManager *panels) {
    BgCellManager_DrawCellAt(panels, PC_BOX_PANEL_TITLE, 0x20, 0xe);
    BgCellManager_StartCellMove(panels, PC_BOX_PANEL_TITLE, -1, 0, 0xb);
}

void PCBox_SlideOutTitlePanel(BgCellManager *panels) {
    BgCellManager_DrawCellAt(panels, PC_BOX_PANEL_TITLE, 0x15, 0xe);
    BgCellManager_StartCellMove(panels, PC_BOX_PANEL_TITLE, 1, 0, 0xb);
}

static void PCBox_HideChangeBoxButton(BgCellManager *panels) {
    BgCellManager_DrawCellAt(panels, PC_BOX_PANEL_CHANGE_BOX_BUTTON, 0, 0x18);
}

static void PCBox_SlideInChangeBoxButton(BgCellManager *panels) {
    BgCellManager_StartCellMove(panels, PC_BOX_PANEL_CHANGE_BOX_BUTTON, 0, -1, 3);
}

void PCBox_SlideOutChangeBoxButton(BgCellManager *panels) {
    BgCellManager_StartCellMove(panels, PC_BOX_PANEL_CHANGE_BOX_BUTTON, 0, 1, 3);
}

BOOL PCBox_IsChangeBoxButtonShown(BgCellManager *panels) {
    s8 x;
    s8 y;
    BgCellManager_GetCellPosition(panels, PC_BOX_PANEL_CHANGE_BOX_BUTTON, &x, &y);
    return y == 0x15;
}

static void PCBox_HideSummaryButton(BgCellManager *panels) {
    BgCellManager_DrawCellAt(panels, PC_BOX_PANEL_SUMMARY_BUTTON, 0, 0x18);
}

void PCBox_ShowSummaryButton(BgCellManager *panels) {
    BgCellManager_DrawCellAt(panels, PC_BOX_PANEL_SUMMARY_BUTTON, 0, 0x15);
}

void PCBox_SlideInSummaryButton(BgCellManager *panels) {
    BgCellManager_StartCellMove(panels, PC_BOX_PANEL_SUMMARY_BUTTON, 0, -1, 3);
}

void PCBox_SlideOutSummaryButton(BgCellManager *panels) {
    BgCellManager_StartCellMove(panels, PC_BOX_PANEL_SUMMARY_BUTTON, 0, 1, 3);
}

BOOL PCBox_IsSummaryButtonShown(BgCellManager *panels) {
    s8 x;
    s8 y;
    BgCellManager_GetCellPosition(panels, PC_BOX_PANEL_SUMMARY_BUTTON, &x, &y);
    return y == 0x15;
}

void PCBox_ShowBoxTray(PCBoxWork *work) {
    PCBox_ShowExitButton(work);
    BgCellManager_EraseCell(work->view->panels, PC_BOX_PANEL_PARTY_BUTTON);
    BgCellManager_EraseCell(work->view->panels, PC_BOX_PANEL_TRAY_TAB);
    BgCellManager_DrawCellAt(work->view->panels, PC_BOX_PANEL_PARTY_BUTTON, 0, 0x18);
    BgCellManager_DrawCellAt(work->view->panels, PC_BOX_PANEL_TRAY_TAB, 0xc, 0x18);
    BgCellManager_DrawCellAt(work->view->panels, PC_BOX_PANEL_BOX_TRAY, 0, 0);
    PCBox_DrawTrayBoxNameAndCount(work);
    PCBox_SetupBoxTraySprites(work);
    PCBox_UpdateCurrentBoxMarker(work);
    PCBox_UpdateTrayCursor(work);
    PCBox_MoveBoxTraySprites(work, 0x30);
}

void PCBox_SlideInBoxTray(BgCellManager *panels) {
    BgCellManager_DrawCellAt(panels, PC_BOX_PANEL_BOX_TRAY, 0, -6);
    BgCellManager_StartCellMove(panels, PC_BOX_PANEL_BOX_TRAY, 0, 1, 6);
}

void PCBox_SlideOutBoxTray(BgCellManager *panels) {
    BgCellManager_StartCellMove(panels, PC_BOX_PANEL_BOX_TRAY, 0, -1, 6);
}

static void PCBox_ShowBoxMenuPanels(BgCellManager *panels) {
    BgCellManager_DrawCellAt(panels, PC_BOX_PANEL_TITLE, 0x15, 8);
    BgCellManager_DrawCellAt(panels, PC_BOX_PANEL_MENU_ROW_3, 0x15, 0xe);
    BgCellManager_DrawCellAt(panels, PC_BOX_PANEL_MENU_ROW_4, 0x15, 0x11);
}

void PCBox_ShowBoxTrayAndMenu(PCBoxWork *work) {
    PCBox_ShowBoxTray(work);
    PCBox_DrawBoxMenu(work);
    PCBox_ShowBoxMenuPanels(work->view->panels);
}

void PCBox_SlideInBoxMenu(BgCellManager *panels) {
    BgCellManager_DrawCellAt(panels, PC_BOX_PANEL_TITLE, 0x20, 8);
    BgCellManager_DrawCellAt(panels, PC_BOX_PANEL_MENU_ROW_3, 0x20, 0xe);
    BgCellManager_DrawCellAt(panels, PC_BOX_PANEL_MENU_ROW_4, 0x20, 0x11);
    BgCellManager_StartCellMove(panels, PC_BOX_PANEL_TITLE, -1, 0, 0xb);
    BgCellManager_StartCellMove(panels, PC_BOX_PANEL_MENU_ROW_3, -1, 0, 0xb);
    BgCellManager_StartCellMove(panels, PC_BOX_PANEL_MENU_ROW_4, -1, 0, 0xb);
}

void PCBox_SlideOutBoxMenu(BgCellManager *panels) {
    BgCellManager_StartCellMove(panels, PC_BOX_PANEL_TITLE, 1, 0, 0xb);
    BgCellManager_StartCellMove(panels, PC_BOX_PANEL_MENU_ROW_3, 1, 0, 0xb);
    BgCellManager_StartCellMove(panels, PC_BOX_PANEL_MENU_ROW_4, 1, 0, 0xb);
}

void PCBox_HideBottomButtons(PCBoxWork *work) {
    BgCellManager_EraseCell(work->view->panels, PC_BOX_PANEL_PARTY_BUTTON);
    BgCellManager_EraseCell(work->view->panels, PC_BOX_PANEL_TRAY_TAB);
    PCBox_HidePartyButton(work);
    PCBox_HideTrayTab(work);
}

void PCBox_SlideInMovesPanel(PCBoxView *view) {
    if (view->movesDrawn) {
        BgCellManager_StartCellMove(view->panels, PC_BOX_PANEL_INFO, -1, 0, 0xc);
    }
}

void PCBox_SlideOutMovesPanel(PCBoxView *view) {
    if (view->movesDrawn) {
        BgCellManager_StartCellMove(view->panels, PC_BOX_PANEL_INFO, 1, 0, 0xc);
    }
}

void PCBox_ShowMovesPanel(PCBoxView *view) {
    if (view->movesDrawn) {
        BgCellManager_EraseCell(view->panels, PC_BOX_PANEL_INFO);
        BgCellManager_DrawCellAt(view->panels, PC_BOX_PANEL_INFO, 0x14, 0xc);
    }
}

void PCBox_HideMovesPanel(BgCellManager *panels) {
    BgCellManager_EraseCell(panels, PC_BOX_PANEL_INFO);
    BgCellManager_DrawCellAt(panels, PC_BOX_PANEL_INFO, 0x20, 0xc);
}

void PCBox_SlideInItemInfoPanel(BgCellManager *panels) {
    s8 x;
    s8 y;
    BgCellManager_GetCellPosition(panels, PC_BOX_PANEL_INFO, &x, &y);
    if (y != 0xf) {
        BgCellManager_StartCellMove(panels, PC_BOX_PANEL_INFO, 0, -1, (u8)(9 - (0x18 - y)));
    }
}

void PCBox_SlideOutItemInfoPanel(BgCellManager *panels) {
    s8 x;
    s8 y;
    BgCellManager_GetCellPosition(panels, PC_BOX_PANEL_INFO, &x, &y);
    if (y != 0x18) {
        BgCellManager_StartCellMove(panels, PC_BOX_PANEL_INFO, 0, 1, (u8)(0x18 - y));
    }
}

void PCBox_ShowItemInfoPanel(BgCellManager *panels) {
    BgCellManager_EraseCell(panels, PC_BOX_PANEL_INFO);
    BgCellManager_DrawCellAt(panels, PC_BOX_PANEL_INFO, 0, 0xf);
}

void PCBox_HideItemInfoPanel(BgCellManager *panels) {
    BgCellManager_EraseCell(panels, PC_BOX_PANEL_INFO);
    BgCellManager_DrawCellAt(panels, PC_BOX_PANEL_INFO, 0, 0x18);
}

void PCBox_DrawMarkings(PCBoxWork *work, u32 mask) {
    u16 i;
    u16 tile;
    for (i = 0; i < 6; i++) {
        if ((1 << i) & mask) {
            tile = i + 0x3a;
        } else {
            tile = i + 0x1a;
        }
        FillBgTilemapRect(work->view->bgConfig, GF_BG_LYR_SUB_1, tile, (u8)(i + 0xf), 0x12, 1, 1, 0);
    }
    ScheduleBgTilemapBufferTransfer(work->view->bgConfig, GF_BG_LYR_SUB_1);
}

u32 PCBox_StartSummaryApp(PCBoxWork *work) {
    PokemonSummaryArgs *args;

    work->subAppArgs = Heap_Alloc(HEAP_ID_9, sizeof(PokemonSummaryArgs));
    args = work->subAppArgs;
    if (work->selectedSlot < PC_BOX_SLOT_PARTY_START) {
        args->party = (Party *)PCBox_GetSlotBoxMon(work, work->activeBox, 0);
        args->monDataType = 2;
        args->partyCount = 30;
        args->partySlot = work->selectedSlot;
    } else {
        args->party = work->party;
        args->monDataType = 1;
        args->partyCount = Party_GetCount(work->party);
        args->partySlot = work->selectedSlot - PC_BOX_SLOT_PARTY_START;
    }
    args->options = work->options;
    PokemonSummaryArgs_SetPlayer(args, Save_PlayerData_GetProfile(work->args->saveData));
    args->mode = 0;
    PokemonSummary_SetPages(args, gPCBoxSummaryPages);
    args->selectedMoveSlot = 0;
    args->exitedWithB = 0;
    args->moveToLearn = 0;
    args->natDexEnabled = SaveArray_IsNatDexEnabled(work->args->saveData);
    args->ribbons = Save_SpecialRibbons_Get(work->args->saveData);
    *(u32 *)args->unk24 = 0;
    args->chatot = 0;
    args->unk2C = PokemonSummary_GetDefaultUnk2C(work->args->saveData);
    args->isFlag982Set = PokemonSummary_IsPokeathlonUnlocked(work->args->saveData);
    args->menuInputStatePtr = work->args->menuInputStatePtr;
    work->subApp = OverlayManager_New(&gOverlayTemplate_PokemonSummary, args, HEAP_ID_9);
    return 0;
}

u32 PCBox_EndSummaryApp(PCBoxWork *work) {
    PokemonSummaryArgs *args = work->subAppArgs;

    if (work->summaryFromHolding == 0) {
        if (work->selectedSlot < PC_BOX_SLOT_PARTY_START) {
            work->selectedSlot = args->partySlot;
        } else {
            work->selectedSlot = args->partySlot + PC_BOX_SLOT_PARTY_START;
        }
    }
    if (work->selectedSlot < PC_BOX_SLOT_PARTY_START && *(u32 *)args->monModified == 1) {
        PCStorage_SetBoxModified(work->storage, work->activeBox);
    }
    Heap_Free(work->subAppArgs);
    return 0;
}

u32 PCBox_StartBagApp(PCBoxWork *work) {
    work->subAppArgs = Bag_CreateView(Save_Bag_Get(work->args->saveData), gPCBoxBagPockets, HEAP_ID_9);
    BagView_Init(work->subAppArgs, work->args->saveData, 1, NULL, work->args->menuInputStatePtr);
    HandleLoadOverlay(FS_OVERLAY_ID(OVY_15), OVY_LOAD_ASYNC);
    work->subApp = OverlayManager_New(&gOverlayTemplate_Bag, work->subAppArgs, HEAP_ID_9);
    return 0;
}

u32 PCBox_EndBagApp(PCBoxWork *work) {
    UnloadOverlayByID(FS_OVERLAY_ID(OVY_15));
    work->itemId = BagView_GetItemId(work->subAppArgs);
    Heap_Free(work->subAppArgs);
    return 0;
}

u32 PCBox_StartNamingScreenApp(PCBoxWork *work) {
    NamingScreenArgs *args;
    work->subAppArgs = NamingScreen_CreateArgs(HEAP_ID_9, NAME_SCREEN_BOX, 0, 8, work->options, work->args->menuInputStatePtr);
    args = work->subAppArgs;
    PCStorage_GetBoxName(work->storage, work->trayBox, args->nameInputString);
    work->subApp = OverlayManager_New(&gOverlayTemplate_NamingScreen, work->subAppArgs, HEAP_ID_9);
    return 0;
}

u32 PCBox_EndNamingScreenApp(PCBoxWork *work) {
    NamingScreenArgs *namingArgs = work->subAppArgs;
    PCStorage_SetBoxName(work->storage, work->trayBox, namingArgs->nameInputString);
    work->itemId = namingArgs->noInput;
    NamingScreen_DeleteArgs(work->subAppArgs);
    return 0;
}

u32 PCBox_UpdateMoveModeBoxDrag(PCBoxWork *work) {
    u32 x;
    u32 y;
    u32 trayTabMoving;
    u32 returnButtonMoving;
    PCBoxView *view = work->view;
    u32 a = PCBox_UpdateActionMenuSlide(view->panels);
    u32 partyButtonMoving = BgCellManager_UpdateCellMove(work->view->panels, PC_BOX_PANEL_PARTY_BUTTON);
    trayTabMoving = BgCellManager_UpdateCellMove(work->view->panels, PC_BOX_PANEL_TRAY_TAB);
    returnButtonMoving = BgCellManager_UpdateCellMove(work->view->panels, PC_BOX_PANEL_RETURN_BUTTON);
    switch (view->subState) {
    case 0:
        if (!System_GetTouchHeldCoords(&x, &y)) {
            a = PC_BOX_SLOT_NONE;
            if (work->trayOpen != 0) {
                a = PCBox_GetTouchedTrayBox(work->view->touchX, work->view->touchY);
            }
            if (a == PC_BOX_SLOT_NONE) {
                a = PCBox_GetTouchedBoxSlot(work->view->touchX, work->view->touchY);
            }
            PCBox_SetupMonMove(work, work->selectedSlot, a);
            PCBox_SetSelectedIconOutlineVisible(work, 0);
            if (!(a & PC_BOX_TARGET_TRAY_BOX)) {
                work->selectedSlot = PCBox_GetMoveEntryTarget(work, work->selectedSlot);
            }
            PCBox_SlideInActionMenu(work->view->panels);
            PCBox_SlideInMovesPanel(work->view);
            view->subState = 1;
        } else {
            ManagedSprite_SetPositionXY(work->view->sprites[work->view->slotIcons[work->selectedSlot]], x, (s16)y - 8);
            PCBox_UpdateSelectedIconOutline(work);
            work->view->touchX = x;
            work->view->touchY = y;
        }
        break;
    case 1:
        if (PCBox_AnimateMonMove(work) == 0 && a == 0 && partyButtonMoving == 0 && trayTabMoving == 0 && returnButtonMoving == 0) {
            PCBox_ApplyMoveEntryIcons(work, view->temp);
            PCBox_UpdateSelectedIconOutline(work);
            PCBox_SetSelectedIconOutlineVisible(work, work->view->showOutlineAfterMove);
            view->subState = 0;
            return 0;
        }
        break;
    }
    return 1;
}

u32 PCBox_UpdateMoveModePartyDrag(PCBoxWork *work) {
    s16 sx;
    s16 sy;
    u32 x;
    u32 y;
    PCBoxView *view = work->view;
    u32 actionMenuMoving = PCBox_UpdateActionMenuSlide(view->panels);
    u32 partyPanelMoving;
    if (view->subState == 0) {
        ManagedSprite_GetPositionXY(work->view->sprites[work->view->slotIcons[work->selectedSlot]], &sx, &sy);
    }
    partyPanelMoving = PCBox_UpdatePartyPanelSlide(work);
    switch (view->subState) {
    case 0:
        if (work->view->partyPanelLowered == 1 && partyPanelMoving == 0) {
            work->view->partyPanelLowered = 2;
            PCBox_DrawWindowFrame(work, 0x28);
            PCBox_SetIconsTranslucent(work, 1, 0);
        }
        if (!System_GetTouchHeldCoords(&x, &y)) {
            u32 target;
            ManagedSprite_SetPositionXY(work->view->sprites[work->view->slotIcons[work->selectedSlot]], sx, sy);
            if (work->view->partyPanelLowered == 2) {
                target = PCBox_GetTouchedBoxSlot(work->view->touchX, work->view->touchY);
            } else {
                target = PCBox_GetTouchedPartySlot(work->view->touchX, work->view->touchY, gPCBoxPartyDropRects);
            }
            PCBox_SetupMonMove(work, work->selectedSlot, target);
            PCBox_SetSelectedIconOutlineVisible(work, 0);
            work->selectedSlot = PCBox_GetMoveEntryTarget(work, work->selectedSlot);
            if (work->selectedSlot < PC_BOX_SLOT_PARTY_START) {
                work->view->showOutlineAfterMove = 0;
            } else {
                work->view->showOutlineAfterMove = 1;
            }
            if (work->selectedSlot < PC_BOX_SLOT_PARTY_START) {
                if (PCBox_GetSlotMonData(work, work->selectedSlot, MON_DATA_SPECIES_EXISTS, NULL) == 0) {
                    view->subState = 3;
                    break;
                }
                PCBox_SlideInPartyPanel(work->view->panels);
                PCBox_ShowSlotMonInfo(work, PC_BOX_SLOT_NONE);
                view->subState = 1;
                break;
            }
            PCBox_RaisePartyPanel(work->view->panels);
            PCBox_SlideInActionMenu(work->view->panels);
            PCBox_SlideInMovesPanel(work->view);
            view->subState = 1;
            break;
        }
        if (actionMenuMoving == 0 && work->view->partyPanelLowered == 0 && (x < 0x10 || y < 0x30 || x >= 0x68)) {
            work->view->partyPanelLowered = 1;
            PCBox_LowerPartyPanel(work->view->panels);
        }
        ManagedSprite_SetPositionXY(work->view->sprites[work->view->slotIcons[work->selectedSlot]], x, (s16)y - 8);
        PCBox_UpdateSelectedIconOutline(work);
        work->view->touchX = x;
        work->view->touchY = y;
        break;
    case 1:
    case 2:
        if (PCBox_AnimateMoveEntries(work) == 0 && actionMenuMoving == 0 && partyPanelMoving == 0) {
            PCBox_ApplyMoveEntryIcons(work, view->temp);
            if (work->selectedSlot < PC_BOX_SLOT_PARTY_START) {
                work->selectedSlot = PC_BOX_SLOT_NONE;
            }
            PCBox_UpdateSelectedIconOutline(work);
            PCBox_SetSelectedIconOutlineVisible(work, work->view->showOutlineAfterMove);
            view->subState = 5;
        }
        break;
    case 3:
        if (PCBox_AnimateSelectedSlotMoveEntry(work) == 0) {
            PCBox_ApplyMoveEntryIcons(work, view->temp);
            PCBox_SlideInPartyPanel(work->view->panels);
            PCBox_ShowSlotMonInfo(work, PC_BOX_SLOT_NONE);
            work->selectedSlot = PC_BOX_SLOT_NONE;
            view->subState++;
        }
        break;
    case 4:
        if (partyPanelMoving == 0) {
            view->subState = 5;
        }
        break;
    case 5:
        PCBox_SetIconsTranslucent(work, 1, 1);
        work->view->partyPanelLowered = 0;
        view->subState = 0;
        return 0;
    }
    return 1;
}

u32 PCBox_UpdateBoxTrayDrag(PCBoxWork *work) {
    u32 x;
    u32 y;
    PCBoxView *view = work->view;
    u32 a = BgCellManager_UpdateCellMove(view->panels, PC_BOX_PANEL_CHANGE_BOX_BUTTON);
    u32 summaryButtonMoving = BgCellManager_UpdateCellMove(work->view->panels, PC_BOX_PANEL_SUMMARY_BUTTON);
    switch (view->subState) {
    case 0:
        if (!System_GetTouchHeldCoords(&x, &y)) {
            a = PC_BOX_SLOT_NONE;
            if (work->trayOpen != 0) {
                a = PCBox_GetTouchedTrayBox(work->view->touchX, work->view->touchY);
            }
            if (a == PC_BOX_SLOT_NONE) {
                a = PCBox_GetTouchedBoxSlot(work->view->touchX, work->view->touchY);
            }
            if (a == PC_BOX_SLOT_NONE) {
                a = PCBox_GetTouchedPartySlot(work->view->touchX, work->view->touchY, gPCBoxTrayPartyDropRects);
            }
            PCBox_SetupMonMove(work, work->selectedSlot, a);
            PCBox_SetSelectedIconOutlineVisible(work, 0);
            if (!(a & PC_BOX_TARGET_TRAY_BOX)) {
                work->selectedSlot = PCBox_GetMoveEntryTarget(work, work->selectedSlot);
            }
            PCBox_SlideOutMovesPanel(work->view);
            view->subState++;
        } else {
            ManagedSprite_SetPositionXY(work->view->sprites[work->view->slotIcons[work->selectedSlot]], x, (s16)y - 8);
            PCBox_UpdateSelectedIconOutline(work);
            work->view->touchX = x;
            work->view->touchY = y;
        }
        break;
    case 1:
        if (a == 0 && summaryButtonMoving == 0) {
            PCBoxMoveWork *moveWork = view->temp;
            if (moveWork->to != PC_BOX_SLOT_NONE && (moveWork->to & PC_BOX_TARGET_TRAY_BOX)) {
                if (moveWork->from >= PC_BOX_SLOT_PARTY_START && moveWork->from - PC_BOX_SLOT_PARTY_START < (u32)(Party_GetCount(work->party) - 1)) {
                    PCBox_SlideInSummaryButton(work->view->panels);
                }
            } else {
                PCBox_SlideInSummaryButton(work->view->panels);
            }
            view->subState++;
        }

    case 2:
        if (PCBox_AnimateMonMove(work) == 0 && summaryButtonMoving == 0 && view->subState == 2) {
            PCBox_ApplyMoveEntryIcons(work, view->temp);
            PCBox_UpdateSelectedIconOutline(work);
            PCBox_SetSelectedIconOutlineVisible(work, 0);
            view->subState = 0;
            return 0;
        }
        break;
    }
    return 1;
}

u32 PCBox_AnimatePartyShiftAfterRelease(PCBoxWork *work) {
    PCBoxView *view = work->view;
    BgCellManager_UpdateCellMove(view->panels, PC_BOX_PANEL_RETURN_BUTTON);
    switch (view->subState) {
    case 0:
        PCBox_SetupPartyShiftAfterRelease(work, work->selectedSlot);
        view->subState++;

    case 1:
        if (PCBox_AnimateMonMove(work) == 0) {
            PCBox_ApplyMoveEntryIcons(work, view->temp);
            view->subState = 0;
            return 0;
        }
        break;
    }
    return 1;
}

u32 PCBox_AnimateMoveToPartyEnd(PCBoxWork *work) {
    PCBoxView *view = work->view;
    switch (view->subState) {
    case 0: {
        u32 target = Party_GetCount(work->party) + PC_BOX_SLOT_PARTY_START;
        PCBox_SetupMonMove(work, work->selectedSlot, target);
        PCBox_SetSelectedIconOutlineVisible(work, 0);
        view->subState++;
        break;
    }
    case 1:
        if (PCBox_AnimateMonMove(work) == 0) {
            PCBox_ApplyMoveEntryIcons(work, view->temp);
            view->subState = 0;
            return 0;
        }
        break;
    }
    return 1;
}

u32 PCBox_AnimateMoveToFirstEmptySlot(PCBoxWork *work) {
    int slotno;
    int boxno;
    PCBoxView *view = work->view;
    switch (view->subState) {
    case 0:
        boxno = work->activeBox;
        slotno = 0;
        PCStorage_FindFirstEmptySlot(work->storage, &boxno, &slotno);
        PCBox_SetupMonMove(work, work->selectedSlot, slotno);
        PCBox_SetSelectedIconOutlineVisible(work, 0);
        work->selectedSlot = PC_BOX_SLOT_NONE;
        view->subState++;
        break;
    case 1:
        if (PCBox_AnimateMonMove(work) == 0) {
            PCBoxMoveWork *moveWork = view->temp;
            PCBox_SetSlotIconTranslucent(work->view, moveWork->from, 1);
            PCBox_ApplyMoveEntryIcons(work, moveWork->entries);
            view->subState = 0;
            return 0;
        }
        break;
    }
    return 1;
}

u32 PCBox_UpdateScrollToPrevBox(PCBoxWork *work) {
    u32 exitButtonWasMoving;
    u32 exitButtonMoving;
    if (work->view->counter == 0x17) {
        if (GridInputHandler_IsButtonInputMode(work->view->gridInput) == TRUE) {
            GridInputHandler_SetButtonInputMode(work->view->gridInput, TRUE);
        }
        work->view->counter = 0;
        work->view->subState = 0;
        return 0;
    }
    ScheduleSetBgPosText(work->view->bgConfig, GF_BG_LYR_MAIN_3, BG_POS_OP_SUB_X, 8);
    PCBox_ScrollBoxIcons(work, 8);
    BgCellManager_UpdateCellMove(work->view->panels, PC_BOX_PANEL_CHANGE_BOX_BUTTON);
    BgCellManager_UpdateCellMove(work->view->panels, PC_BOX_PANEL_RETURN_BUTTON);
    BgCellManager_UpdateCellMove(work->view->panels, PC_BOX_PANEL_PARTY_BUTTON);
    BgCellManager_UpdateCellMove(work->view->panels, PC_BOX_PANEL_TRAY_TAB);
    exitButtonWasMoving = BgCellManager_IsCellMoving(work->view->panels, PC_BOX_PANEL_MENU_EXIT_BUTTON);
    PCBox_UpdateActionMenuSlide(work->view->panels);
    exitButtonMoving = BgCellManager_IsCellMoving(work->view->panels, PC_BOX_PANEL_MENU_EXIT_BUTTON);
    if (exitButtonWasMoving == 1 && exitButtonMoving == 0) {
        PCBox_SlideInReturnButton(work->view->panels);
    }
    work->view->counter++;
    return 1;
}

u32 PCBox_UpdateScrollToNextBox(PCBoxWork *work) {
    u32 exitButtonWasMoving;
    u32 exitButtonMoving;
    if (work->view->counter == 0x17) {
        if (GridInputHandler_IsButtonInputMode(work->view->gridInput) == TRUE) {
            GridInputHandler_SetButtonInputMode(work->view->gridInput, TRUE);
        }
        work->view->counter = 0;
        work->view->subState = 0;
        return 0;
    }
    ScheduleSetBgPosText(work->view->bgConfig, GF_BG_LYR_MAIN_3, BG_POS_OP_ADD_X, 8);
    PCBox_ScrollBoxIcons(work, -8);
    BgCellManager_UpdateCellMove(work->view->panels, PC_BOX_PANEL_CHANGE_BOX_BUTTON);
    BgCellManager_UpdateCellMove(work->view->panels, PC_BOX_PANEL_RETURN_BUTTON);
    BgCellManager_UpdateCellMove(work->view->panels, PC_BOX_PANEL_PARTY_BUTTON);
    BgCellManager_UpdateCellMove(work->view->panels, PC_BOX_PANEL_TRAY_TAB);
    exitButtonWasMoving = BgCellManager_IsCellMoving(work->view->panels, PC_BOX_PANEL_MENU_EXIT_BUTTON);
    PCBox_UpdateActionMenuSlide(work->view->panels);
    exitButtonMoving = BgCellManager_IsCellMoving(work->view->panels, PC_BOX_PANEL_MENU_EXIT_BUTTON);
    if (exitButtonWasMoving == 1 && exitButtonMoving == 0) {
        PCBox_SlideInReturnButton(work->view->panels);
    }
    work->view->counter++;
    return 1;
}

u32 PCBox_WaitActionMenuSlide(PCBoxWork *work) {
    if (PCBox_UpdateActionMenuSlide(work->view->panels)) {
        return 1;
    }
    return 0;
}

u32 PCBox_WaitActionMenuAndButtonsSlide(PCBoxWork *work) {
    u32 actionMenuMoving = PCBox_UpdateActionMenuSlide(work->view->panels);
    u32 partyButtonMoving = BgCellManager_UpdateCellMove(work->view->panels, PC_BOX_PANEL_PARTY_BUTTON);
    u32 trayTabMoving = BgCellManager_UpdateCellMove(work->view->panels, PC_BOX_PANEL_TRAY_TAB);
    u32 returnButtonMoving = BgCellManager_UpdateCellMove(work->view->panels, PC_BOX_PANEL_RETURN_BUTTON);
    if (actionMenuMoving == 0 && partyButtonMoving == 0 && trayTabMoving == 0 && returnButtonMoving == 0) {
        return 0;
    }
    return 1;
}

void PCBox_UpdateMarkingMenuSlide(PCBoxWork *work) {
    BgCellManager_UpdateCellMove(work->view->panels, PC_BOX_PANEL_MARKING_MENU);
}

BOOL PCBox_WaitBottomButtonsSlide(PCBoxWork *work) {
    int partyButtonMoving = BgCellManager_UpdateCellMove(work->view->panels, PC_BOX_PANEL_PARTY_BUTTON);
    int trayTabMoving = BgCellManager_UpdateCellMove(work->view->panels, PC_BOX_PANEL_TRAY_TAB);
    int returnButtonMoving = BgCellManager_UpdateCellMove(work->view->panels, PC_BOX_PANEL_RETURN_BUTTON);
    int menuExitButtonMoving = BgCellManager_UpdateCellMove(work->view->panels, PC_BOX_PANEL_MENU_EXIT_BUTTON);
    if (partyButtonMoving == 0 && trayTabMoving == 0 && returnButtonMoving == 0 && menuExitButtonMoving == 0) {
        return FALSE;
    }
    return TRUE;
}

u32 PCBox_WaitPartyPanelSlide(PCBoxWork *work) {
    return PCBox_UpdatePartyPanelSlide(work) != 0;
}

int PCBox_WaitPartyPanelAndActionMenuSlide(PCBoxWork *work) {
    if (!PCBox_UpdatePartyPanelSlide(work)) {
        return 0;
    }
    PCBox_UpdateActionMenuSlide(work->view->panels);
    return 1;
}

void PCBox_WaitPartyPanelSlideFunc(PCBoxWork *work) {
    PCBox_WaitPartyPanelSlide(work);
}

int PCBox_UpdateBoxTraySlideIn(PCBoxWork *work) {
    int boxTrayMoving = BgCellManager_UpdateCellMove(work->view->panels, PC_BOX_PANEL_BOX_TRAY);
    int summaryButtonMoving = BgCellManager_UpdateCellMove(work->view->panels, PC_BOX_PANEL_SUMMARY_BUTTON);
    PCBox_MoveBoxTraySprites(work, 8);
    if (boxTrayMoving == 0 && summaryButtonMoving == 0) {
        return 0;
    }
    return 1;
}

int PCBox_UpdateBoxTraySlideOut(PCBoxWork *work) {
    int boxTrayMoving = BgCellManager_UpdateCellMove(work->view->panels, PC_BOX_PANEL_BOX_TRAY);
    PCBox_MoveBoxTraySprites(work, -8);
    return boxTrayMoving;
}

void PCBox_WaitReturnButtonSlide(PCBoxWork *work) {
    BgCellManager_UpdateCellMove(work->view->panels, PC_BOX_PANEL_RETURN_BUTTON);
}

int PCBox_WaitActionMenuThenTitleSlide(PCBoxWork *work) {
    PCBoxView *view = work->view;
    switch (view->subState) {
    case 0:
        if (PCBox_WaitActionMenuSlide(work) == 0) {
            view->subState++;
        }
        break;
    case 1:
        if (!BgCellManager_UpdateCellMove(view->panels, PC_BOX_PANEL_TITLE)) {
            view->subState = 0;
            return 0;
        }
        break;
    }
    return 1;
}

void PCBox_WaitTitlePanelSlide(PCBoxWork *work) {
    BgCellManager_UpdateCellMove(work->view->panels, PC_BOX_PANEL_TITLE);
}

u32 PCBox_UpdateBoxMenuSlide(PCBoxWork *work) {
    u32 titleMoving = BgCellManager_UpdateCellMove(work->view->panels, PC_BOX_PANEL_TITLE);
    u32 menuRow3Moving = BgCellManager_UpdateCellMove(work->view->panels, PC_BOX_PANEL_MENU_ROW_3);
    u32 menuRow4Moving = BgCellManager_UpdateCellMove(work->view->panels, PC_BOX_PANEL_MENU_ROW_4);
    if (titleMoving == 0 && menuRow3Moving == 0 && menuRow4Moving == 0) {
        return 0;
    }
    return 1;
}

u32 PCBox_WaitBoxMenuThenWallpaperList(PCBoxWork *work) {
    PCBoxView *view = work->view;
    switch (view->subState) {
    case 0:
        if (PCBox_UpdateBoxMenuSlide(work) == 0) {
            view->subState++;
        }
        break;
    case 1:
        PCBox_MoveWallpaperMenuSprites(view, 8);
        if (!BgCellManager_UpdateCellMove(work->view->panels, PC_BOX_PANEL_WALLPAPER_LIST)) {
            view->subState = 0;
            return 0;
        }
        break;
    }
    return 1;
}

void PCBox_WaitWallpaperListSlideOut(PCBoxWork *work) {
    PCBox_MoveWallpaperMenuSprites(work->view, ~7);
    BgCellManager_UpdateCellMove(work->view->panels, PC_BOX_PANEL_WALLPAPER_LIST);
}

BOOL PCBox_AnimateDepositBoxSelectOpen(PCBoxWork *work) {
    PCBoxView *view = work->view;
    void *tiles = BgCellManager_GetCellTilemap(view->panels, PC_BOX_PANEL_BOX_TRAY);
    switch (view->subState) {
    case 0:
        CopyToBgTilemapRect(work->view->bgConfig, GF_BG_LYR_MAIN_0, 0, 9, 32, 1, tiles, 0, 3, 32, 7);
        break;
    case 1:
        CopyToBgTilemapRect(work->view->bgConfig, GF_BG_LYR_MAIN_0, 0, 8, 32, 1, tiles, 0, 0, 32, 7);
        CopyToBgTilemapRect(work->view->bgConfig, GF_BG_LYR_MAIN_0, 0, 10, 32, 1, tiles, 0, 6, 32, 7);
        break;
    case 2:
        CopyToBgTilemapRect(work->view->bgConfig, GF_BG_LYR_MAIN_0, 0, 7, 32, 2, tiles, 0, 0, 32, 7);
        CopyToBgTilemapRect(work->view->bgConfig, GF_BG_LYR_MAIN_0, 0, 10, 32, 2, tiles, 0, 5, 32, 7);
        break;
    case 10:
        FillBgTilemapRect(work->view->bgConfig, GF_BG_LYR_MAIN_0, 0, 0, 4, 32, 11, 16);
    case 3:
        CopyToBgTilemapRect(work->view->bgConfig, GF_BG_LYR_MAIN_0, 0, 6, 32, 7, tiles, 0, 0, 32, 7);
        break;
    case 4:
        CopyToBgTilemapRect(work->view->bgConfig, GF_BG_LYR_MAIN_0, 0, 5, 32, 2, tiles, 0, 0, 32, 7);
        CopyToBgTilemapRect(work->view->bgConfig, GF_BG_LYR_MAIN_0, 0, 12, 32, 2, tiles, 0, 5, 32, 7);
        break;
    case 5:
        CopyToBgTilemapRect(work->view->bgConfig, GF_BG_LYR_MAIN_0, 0, 4, 32, 2, tiles, 0, 0, 32, 7);
        CopyToBgTilemapRect(work->view->bgConfig, GF_BG_LYR_MAIN_0, 0, 13, 32, 2, tiles, 0, 5, 32, 7);
        break;
    }
    ScheduleBgTilemapBufferTransfer(work->view->bgConfig, GF_BG_LYR_MAIN_0);
    if (view->subState == 10) {
        view->subState = 0;
        return FALSE;
    }
    view->subState++;
    return TRUE;
}

u32 PCBox_AnimateDepositBoxSelectClose(PCBoxWork *work) {
    PCBoxView *view = work->view;
    FillBgTilemapRect(view->bgConfig, GF_BG_LYR_MAIN_0, 0, 0, (u8)(view->subState + 6), 0x20, 1, 0x10);
    FillBgTilemapRect(work->view->bgConfig, GF_BG_LYR_MAIN_0, 0, 0, (u8)(0xc - view->subState), 0x20, 1, 0x10);
    ScheduleBgTilemapBufferTransfer(work->view->bgConfig, GF_BG_LYR_MAIN_0);
    if (view->subState == 3) {
        view->subState = 0;
        return 0;
    }
    view->subState++;
    return 1;
}

u32 PCBox_WaitSummaryOutChangeBoxIn(PCBoxWork *work) {
    PCBoxView *view = work->view;
    switch (view->subState) {
    case 0:
        if (!BgCellManager_UpdateCellMove(view->panels, PC_BOX_PANEL_SUMMARY_BUTTON)) {
            PCBox_SlideInChangeBoxButton(work->view->panels);
            view->subState++;
        }
        break;
    case 1:
        if (!BgCellManager_UpdateCellMove(view->panels, PC_BOX_PANEL_CHANGE_BOX_BUTTON)) {
            view->subState = 0;
            return 0;
        }
        break;
    }
    return 1;
}

u32 PCBox_WaitTrayButtonsSlide(PCBoxWork *work) {
    if (!BgCellManager_UpdateCellMove(work->view->panels, PC_BOX_PANEL_SUMMARY_BUTTON) && !BgCellManager_UpdateCellMove(work->view->panels, PC_BOX_PANEL_CHANGE_BOX_BUTTON)) {
        return 0;
    }
    return 1;
}

u32 PCBox_WaitChangeBoxOutSummaryIn(PCBoxWork *work) {
    PCBoxView *view = work->view;
    switch (view->subState) {
    case 0:
        if (!BgCellManager_UpdateCellMove(view->panels, PC_BOX_PANEL_CHANGE_BOX_BUTTON)) {
            PCBox_SlideInSummaryButton(work->view->panels);
            view->subState++;
        }
        break;
    case 1:
        if (!BgCellManager_UpdateCellMove(view->panels, PC_BOX_PANEL_SUMMARY_BUTTON)) {
            view->subState = 0;
            return 0;
        }
        break;
    }
    return 1;
}

u32 PCBox_WaitTitleAndReturnButtonSlide(PCBoxWork *work) {
    u32 titleMoving = BgCellManager_UpdateCellMove(work->view->panels, PC_BOX_PANEL_TITLE);
    u32 returnButtonMoving = BgCellManager_UpdateCellMove(work->view->panels, PC_BOX_PANEL_RETURN_BUTTON);
    if (titleMoving == 0 && returnButtonMoving == 0) {
        return 0;
    }
    return 1;
}

u32 PCBox_UpdateDepositDrag(PCBoxWork *work) {
    struct {
        s16 pos[2];
        u32 touchX;
        u32 touchY;
    } coords;

    PCBoxView *view = work->view;
    u32 readyA;
    u32 readyB;
    u32 readyC;

    if (view->subState <= 1) {
        ManagedSprite_GetPositionXY(
            view->sprites[view->slotIcons[work->selectedSlot]],
            &coords.pos[1],
            &coords.pos[0]);
    }
    readyA = PCBox_UpdateActionMenuSlide(work->view->panels);
    readyB = PCBox_UpdatePartyPanelMove(work);
    readyC = BgCellManager_UpdateCellMove(work->view->panels, PC_BOX_PANEL_RETURN_BUTTON);

    switch (view->subState) {
    case 0:
        view->subState = 1;
    case 1:
        if (work->view->partyPanelLowered == 1 && readyB == 0) {
            work->view->partyPanelLowered = 2;
            PCBox_DrawWindowFrame(work, 40);
        }
        if (!System_GetTouchHeldCoords(&coords.touchY, &coords.touchX)) {
            ManagedSprite_SetPositionXY(
                work->view->sprites[work->view->slotIcons[work->selectedSlot]],
                coords.pos[1],
                coords.pos[0]);
            u32 value = PC_BOX_SLOT_NONE;
            if (work->view->partyPanelLowered == 2) {
                value = PCBox_GetTouchedBoxSlot(work->view->touchX,
                    work->view->touchY);
            }
            PCBox_SetupDepositMoveEntries(work, work->selectedSlot, value);
            PCBox_SetSelectedIconOutlineVisible(work, 0);
            work->selectedSlot = (u8)PCBox_GetMoveEntryTarget(work, work->selectedSlot);
            if (work->selectedSlot < PC_BOX_SLOT_PARTY_START) {
                view->subState = 5;
                break;
            }
            PCBox_RaisePartyPanel(work->view->panels);
            PCBox_SlideInActionMenu(work->view->panels);
            PCBox_SlideInMovesPanel(work->view);
            view->subState = 2;
            break;
        }
        if (work->view->partyPanelLowered == 0 && readyA == 0 && readyC == 0 && (coords.touchY < 16 || coords.touchX < 48 || coords.touchY >= 104)) {
            work->view->partyPanelLowered = 1;
            PCBox_LowerPartyPanel(work->view->panels);
        }
        ManagedSprite_SetPositionXY(
            work->view->sprites[work->view->slotIcons[work->selectedSlot]],
            coords.touchY,
            (s16)((s16)coords.touchX - 8));
        PCBox_UpdateSelectedIconOutline(work);
        work->view->touchX = coords.touchY;
        work->view->touchY = coords.touchX;
        break;
    case 2:
    case 3:
    case 4:
        if (PCBox_AnimateMonMove(work) == 0 && readyB == 0 && readyA == 0) {
            PCBox_ApplyMoveEntryIcons(work, view->temp);
            PCBox_UpdateSelectedIconOutline(work);
            PCBox_SetSelectedIconOutlineVisible(work, work->view->showOutlineAfterMove);
            view->subState = 7;
        }
        break;
    case 5:
        if (PCBox_AnimateSelectedSlotMoveEntry(work) == 0) {
            PCBox_ApplyMoveEntryIcons(work, view->temp);
            PCBox_ClearMonInfo(work);
            PCBox_SlideInPartyPanel(work->view->panels);
            work->selectedSlot = PC_BOX_SLOT_NONE;
            view->subState = 6;
        }
        break;
    case 6:
        if (readyB == 0) {
            view->subState = 7;
        }
        break;
    case 7:
        PCBox_SetIconsTranslucent(work, 1, 1);
        PCBox_SetIconsTranslucent(work, 2, 0);
        work->view->partyPanelLowered = 0;
        view->subState = 0;
        return 0;
    }
    return 1;
}

u32 PCBox_UpdateWithdrawDrag(PCBoxWork *work) {
    u32 touchY;
    u32 touchX;
    s16 pos[2];
    PCBoxView *view = work->view;
    u32 readyA = PCBox_UpdateActionMenuSlide(view->panels);
    u32 readyB = PCBox_UpdatePartyPanelSlide(work);
    u32 readyC = BgCellManager_UpdateCellMove(work->view->panels, PC_BOX_PANEL_RETURN_BUTTON);

    switch (view->subState) {
    case 0:
        view->subState = 1;
    case 1:
        if (work->view->partyPanelLowered == 1 && readyB == 0) {
            work->view->partyPanelLowered = 2;
            PCBox_DrawWindowFrame(work, 40);
        }
        if (!System_GetTouchHeldCoords(&touchY, &touchX)) {
            u32 value = PC_BOX_SLOT_NONE;
            if (work->view->partyPanelLowered == 2) {
                value = PCBox_GetTouchedPartySlot(work->view->touchX,
                    work->view->touchY,
                    gPCBoxTrayPartyDropRects);
            }
            PCBox_SetupMonMoveToPartyEnd(work, work->selectedSlot, value);
            PCBox_SetSelectedIconOutlineVisible(work, 0);
            work->selectedSlot = (u8)PCBox_GetMoveEntryTarget(work, work->selectedSlot);
            if (work->selectedSlot >= PC_BOX_SLOT_PARTY_START) {
                view->subState = 5;
                break;
            }
            if (work->view->partyPanelLowered != 0) {
                PCBox_SlideOutPartyPanel(work->view->panels);
            }
            view->subState = 2;
            break;
        }
        if (work->view->partyPanelLowered == 0 && readyA == 0 && readyC == 0) {
            PCBox_GetSlotPosition(work->selectedSlot, &pos[1], &pos[0], work->partyLayout);
            if (touchY < (u32)(pos[1] - 16) || touchY >= (u32)(pos[1] + 16) || touchX < (u32)(pos[0] - 16) || touchX >= (u32)(pos[0] + 16)) {
                work->view->partyPanelLowered = 1;
                PCBox_PlacePartyPanelRightHidden(work->view->panels);
                PCBox_SlideInPartyPanel(work->view->panels);
            }
        }
        ManagedSprite_SetPositionXY(
            work->view->sprites[work->view->slotIcons[work->selectedSlot]],
            touchY,
            (s16)((s16)touchX - 8));
        PCBox_UpdateSelectedIconOutline(work);
        work->view->touchX = touchY;
        work->view->touchY = touchX;
        break;
    case 2:
        if (readyB == 0) {
            PCBox_SlideInActionMenu(work->view->panels);
            PCBox_SlideInMovesPanel(work->view);
            view->subState = 3;
        }
    case 3:
    case 4:
        if (PCBox_AnimateMonMove(work) == 0 && view->subState == 4 && readyA == 0) {
            PCBox_ApplyMoveEntryIcons(work, view->temp);
            PCBox_UpdateSelectedIconOutline(work);
            PCBox_SetSelectedIconOutlineVisible(work, work->view->showOutlineAfterMove);
            view->subState = 8;
            break;
        }
        if (view->subState == 3) {
            view->subState = 4;
        }
        break;
    case 5:
        if (PCBox_AnimateMonMove(work) == 0) {
            PCBox_ApplyMoveEntryIcons(work, view->temp);
            work->selectedSlot = PC_BOX_SLOT_NONE;
            PCBox_SlideOutPartyPanel(work->view->panels);
            view->subState++;
        }
        break;
    case 6:
        if (readyB == 0) {
            PCBox_ClearMonInfo(work);
            PCBox_SlideInReturnButton(work->view->panels);
            view->subState++;
        }
        break;
    case 7:
        if (readyC == 0) {
            view->subState = 8;
        }
        break;
    case 8:
        PCBox_SetIconsTranslucent(work, 1, 0);
        PCBox_SetIconsTranslucent(work, 2, 0);
        work->view->partyPanelLowered = 0;
        view->subState = 0;
        return 0;
    }
    return 1;
}

u32 PCBox_UpdateCursorSlide(PCBoxWork *work) {
    s16 pos[2];
    PCBoxCursorSlide *slide = work->view->temp;

    BgCellManager_UpdateCellMove(work->view->panels, PC_BOX_PANEL_SUMMARY_BUTTON);
    if (slide->frames == 0) {
        ManagedSprite_SetPositionXY(work->view->sprites[PC_BOX_SPRITE_CURSOR], slide->x, slide->y);
        if (work->view->cursorHolding == 1) {
            if (work->args->mode == PC_BOX_MODE_MOVE_ITEMS) {
                ManagedSprite_SetPositionXY(work->view->sprites[PC_BOX_SPRITE_HELD_ITEM], slide->x, (s16)(slide->y + 8));
            } else {
                ManagedSprite_SetPositionXY(work->view->sprites[work->view->slotIcons[work->selectedSlot]], slide->x, (s16)(slide->y + 4));
            }
        }
        return 0;
    }

    slide->frames--;
    ManagedSprite_GetPositionXY(work->view->sprites[PC_BOX_SPRITE_CURSOR], &pos[1], &pos[0]);
    if (slide->xNegative == 0) {
        pos[1] += slide->dx;
    } else {
        pos[1] -= slide->dx;
    }
    if (slide->yNegative == 0) {
        pos[0] += slide->dy;
    } else {
        pos[0] -= slide->dy;
    }
    ManagedSprite_SetPositionXY(work->view->sprites[PC_BOX_SPRITE_CURSOR], pos[1], pos[0]);
    if (work->view->cursorHolding == 1) {
        if (work->args->mode == PC_BOX_MODE_MOVE_ITEMS) {
            ManagedSprite_SetPositionXY(work->view->sprites[PC_BOX_SPRITE_HELD_ITEM], pos[1], (s16)(pos[0] + 8));
        } else {
            ManagedSprite_SetPositionXY(work->view->sprites[work->view->slotIcons[work->selectedSlot]], pos[1], (s16)(pos[0] + 4));
        }
    }
    return 1;
}

u32 PCBox_WaitSelectWithActionMenu(PCBoxWork *work) {
    PCBoxView *view = work->view;
    switch (view->subState) {
    case 0:
        if (!BgCellManager_UpdateCellMove(view->panels, PC_BOX_PANEL_RETURN_BUTTON)) {
            view->subState++;
        }
        break;
    case 1: {
        u32 actionMenuMoving = PCBox_UpdateActionMenuSlide(view->panels);
        u32 cursorMoving = PCBox_UpdateCursorSlide(work);
        if (actionMenuMoving == 0 && cursorMoving == 0) {
            view->subState = 0;
            return 0;
        }
        break;
    }
    }
    return 1;
}

u32 PCBox_WaitSelectWithActionMenuAndButtons(PCBoxWork *work) {
    PCBoxView *view = work->view;
    switch (view->subState) {
    case 0: {
        u32 partyButtonMoving = BgCellManager_UpdateCellMove(view->panels, PC_BOX_PANEL_PARTY_BUTTON);
        u32 trayTabMoving = BgCellManager_UpdateCellMove(work->view->panels, PC_BOX_PANEL_TRAY_TAB);
        u32 returnButtonMoving = BgCellManager_UpdateCellMove(work->view->panels, PC_BOX_PANEL_RETURN_BUTTON);
        if (partyButtonMoving == 0 && trayTabMoving == 0 && returnButtonMoving == 0) {
            view->subState++;
        }
        break;
    }
    case 1: {
        u32 cursorMoving = PCBox_UpdateCursorSlide(work);
        u32 actionMenuMoving = PCBox_UpdateActionMenuSlide(work->view->panels);
        if (cursorMoving == 0 && actionMenuMoving == 0) {
            view->subState = 0;
            return 0;
        }
        break;
    }
    }
    return 1;
}

u32 PCBox_WaitDeselectThenReturnButton(PCBoxWork *work) {
    PCBoxView *view = work->view;
    switch (view->subState) {
    case 0: {
        u32 actionMenuMoving = PCBox_UpdateActionMenuSlide(view->panels);
        u32 cursorMoving = PCBox_UpdateCursorSlide(work);
        if (actionMenuMoving == 0 && cursorMoving == 0) {
            view->subState++;
        }
        break;
    }
    case 1:
        if (!BgCellManager_UpdateCellMove(view->panels, PC_BOX_PANEL_RETURN_BUTTON)) {
            view->subState = 0;
            return 0;
        }
        break;
    }
    return 1;
}

u32 PCBox_WaitDeselectThenButtons(PCBoxWork *work) {
    PCBoxView *view = work->view;
    switch (view->subState) {
    case 0: {
        u32 cursorMoving = PCBox_UpdateCursorSlide(work);
        u32 actionMenuMoving = PCBox_WaitActionMenuSlide(work);
        if (cursorMoving == 0 && actionMenuMoving == 0) {
            view->subState++;
        }
        break;
    }
    case 1: {
        u32 partyButtonMoving = BgCellManager_UpdateCellMove(view->panels, PC_BOX_PANEL_PARTY_BUTTON);
        u32 trayTabMoving = BgCellManager_UpdateCellMove(work->view->panels, PC_BOX_PANEL_TRAY_TAB);
        u32 returnButtonMoving = BgCellManager_UpdateCellMove(work->view->panels, PC_BOX_PANEL_RETURN_BUTTON);
        if (partyButtonMoving == 0 && trayTabMoving == 0 && returnButtonMoving == 0) {
            view->subState = 0;
            return 0;
        }
        break;
    }
    }
    return 1;
}

void PCBox_AttachIconToCursor(PCBoxWork *work) {
    s16 pos[2];
    PCBox_SetSpriteAnim(work->view, PC_BOX_SPRITE_CURSOR, 0xa);
    ManagedSprite_GetPositionXY(work->view->sprites[PC_BOX_SPRITE_CURSOR], &pos[1], &pos[0]);
    ManagedSprite_SetPositionXY(work->view->sprites[work->view->slotIcons[work->selectedSlot]], pos[1], (s16)(pos[0] + 4));
    PCBox_SetIconLayer(work->view, work->selectedSlot, FALSE);
}

// Cursor dip animation over the selected mon (and its icon).
BOOL PCBox_AnimateTrayPickUp(PCBoxWork *work) {
    s16 x, y;
    PCBoxView *view = work->view;

    BgCellManager_UpdateCellMove(view->panels, PC_BOX_PANEL_SUMMARY_BUTTON);
    switch (view->subState) {
    case 0:
        PCBox_SetSpriteAnim(work->view, PC_BOX_SPRITE_CURSOR, 9);
        view->subState++;
    case 1:
        if (view->counter == 4) {
            view->counter = 0;
            view->subState++;
        } else {
            ManagedSprite_GetPositionXY(work->view->sprites[PC_BOX_SPRITE_CURSOR], &x, &y);
            ManagedSprite_SetPositionXY(work->view->sprites[PC_BOX_SPRITE_CURSOR], x, (s16)(y + 2));
            view->counter++;
        }
        break;
    case 2:
        PCBox_SetSpriteAnim(work->view, PC_BOX_SPRITE_CURSOR, 10);
        view->subState++;
    case 3:
        if (view->counter == 4) {
            view->counter = 0;
            view->subState = 0;
            return FALSE;
        } else {
            int index;
            ManagedSprite_GetPositionXY(work->view->sprites[PC_BOX_SPRITE_CURSOR], &x, &y);
            ManagedSprite_SetPositionXY(work->view->sprites[PC_BOX_SPRITE_CURSOR], x, (s16)(y - 2));
            index = work->view->slotIcons[work->selectedSlot];
            ManagedSprite_GetPositionXY(work->view->sprites[index], &x, &y);
            ManagedSprite_SetPositionXY(work->view->sprites[index], x, (s16)(y - 2));
            view->counter++;
        }
        break;
    }
    return TRUE;
}

u32 PCBox_AnimateTrayDrop(PCBoxWork *work) {
    PCBoxView *view = work->view;
    BgCellManager_UpdateCellMove(view->panels, PC_BOX_PANEL_SUMMARY_BUTTON);
    switch (view->subState) {
    case 0: {
        u32 target;
        PCBox_SetSpriteAnim(work->view, PC_BOX_SPRITE_CURSOR, 9);
        target = work->view->dropTarget;
        if (target >= 0x25 && target <= 0x2a) {
            target += 0x5b;
        }
        PCBox_SetupMonMove(work, work->selectedSlot, target);
        if ((target & PC_BOX_TARGET_TRAY_BOX) == 0) {
            work->selectedSlot = (u8)PCBox_GetMoveEntryTarget(work, work->selectedSlot);
        }
        view->subState++;
    }
    case 1:
        if (PCBox_AnimateMonMove(work) == 0) {
            PCBox_ApplyMoveEntryIcons(work, view->temp);
            PCBox_SetSpriteAnim(work->view, PC_BOX_SPRITE_CURSOR, 8);
            view->subState = 0;
            return 0;
        }
        break;
    }
    return 1;
}

u32 PCBox_WaitItemModeSelect(PCBoxWork *work) {
    PCBoxView *view = work->view;
    switch (view->subState) {
    case 0:
        if (view->heldItem != ITEM_NONE) {
            PCBox_SetHeldItemIconAffine(view, 1);
            PCBox_SetSpriteAnim(work->view, PC_BOX_SPRITE_HELD_ITEM, 1);
            PCBox_SetSpriteVisible(work->view, PC_BOX_SPRITE_HELD_ITEM, TRUE);
        }
        view->subState++;
    case 1: {
        u32 partyButtonMoving = BgCellManager_UpdateCellMove(work->view->panels, PC_BOX_PANEL_PARTY_BUTTON);
        u32 trayTabMoving = BgCellManager_UpdateCellMove(work->view->panels, PC_BOX_PANEL_TRAY_TAB);
        u32 returnButtonMoving = BgCellManager_UpdateCellMove(work->view->panels, PC_BOX_PANEL_RETURN_BUTTON);
        if (partyButtonMoving == 0 && trayTabMoving == 0 && returnButtonMoving == 0) {
            view->subState++;
        }
        break;
    }
    case 2: {
        u32 cursorMoving = PCBox_UpdateCursorSlide(work);
        u32 actionMenuMoving = PCBox_UpdateActionMenuSlide(work->view->panels);
        if (cursorMoving == 0 && actionMenuMoving == 0) {
            if (work->view->heldItem != ITEM_NONE) {
                PCBox_SetHeldItemIconAffine(work->view, 0);
                PCBox_ShowHeldItemIconOutline(work->view);
            }
            view->subState = 0;
            return 0;
        }
        break;
    }
    }
    return 1;
}

int PCBox_UpdateItemModeBoxDrag(PCBoxWork *work) {
    PCBoxView *view = work->view;
    int x, y;
    u16 selected, raw;
    int busy = PCBox_UpdateActionMenuSlide(view->panels);
    BgCellManager_UpdateCellMove(work->view->panels, PC_BOX_PANEL_PARTY_BUTTON);
    BgCellManager_UpdateCellMove(work->view->panels, PC_BOX_PANEL_TRAY_TAB);
    BgCellManager_UpdateCellMove(work->view->panels, PC_BOX_PANEL_RETURN_BUTTON);
    switch (view->subState) {
    case 0:
        if (work->view->heldItem) {
            PCBox_SetHeldItemIconAffine(work->view, 1);
            PCBox_SetSpriteAnim(work->view, PC_BOX_SPRITE_HELD_ITEM, 1);
            PCBox_SetSpriteVisible(work->view, PC_BOX_SPRITE_HELD_ITEM, TRUE);
            view->subState = 1;
        } else {
            PCBox_SlideInActionMenu(work->view->panels);
            view->subState = 10;
        }
        break;
    case 1:
        if (PCBox_IsSpriteAnimated(work->view, PC_BOX_SPRITE_HELD_ITEM) == 1) {
            break;
        }
        PCBox_SetHeldItemIconAffine(work->view, 0);
        PCBox_ShowHeldItemIconOutline(work->view);
        view->subState = 2;
    case 2:
        if (!System_GetTouchHeldCoords(&x, &y)) {
            selected = PCBox_GetTouchedBoxSlot(work->view->touchX, work->view->touchY);
            raw = selected;
            if (selected == 255) {
                selected = work->selectedSlot;
            } else if (!PCBox_CanSwapHeldItems(work, work->selectedSlot, selected)) {
                selected = work->selectedSlot;
            }
            if (selected == work->selectedSlot) {
                PCBox_SlideInActionMenu(work->view->panels);
            } else {
                PCBox_SlideOutItemInfoPanel(work->view->panels);
            }
            PCBox_StartHeldItemMoveWithIcon(work, raw, selected, 2);
            view->subState = 3;
        } else {
            PCBox_SetHeldItemIconPosition(work->view, x, y);
            PCBox_UpdateHeldItemIconOutline(work->view);
            work->view->touchX = x;
            work->view->touchY = y;
        }
        break;
    case 3:
        if (!PCBox_UpdateHeldItemMoveWithIcon(work)) {
            view->subState = 10;
        }
        break;
    case 10:
        if (!busy) {
            if (work->view->heldItem) {
                PCBox_SetHeldItemIconAffine(work->view, 0);
                PCBox_ShowHeldItemIconOutline(work->view);
            }
            view->subState = 0;
            return 0;
        }
        break;
    }
    return 1;
}

u32 PCBox_WaitItemModeDeselect(PCBoxWork *work) {
    PCBoxView *view = work->view;
    switch (view->subState) {
    case 0:
        if (view->heldItem != ITEM_NONE) {
            PCBox_SetHeldItemIconAffine(view, 1);
            PCBox_SetSpriteAnim(work->view, PC_BOX_SPRITE_HELD_ITEM, 2);
        }
        view->subState++;
    case 1: {
        u32 cursorMoving = PCBox_UpdateCursorSlide(work);
        u32 actionMenuMoving = PCBox_WaitActionMenuSlide(work);
        if (cursorMoving == 0 && actionMenuMoving == 0) {
            view->subState++;
        }
        break;
    }
    case 2: {
        u32 partyButtonMoving = BgCellManager_UpdateCellMove(view->panels, PC_BOX_PANEL_PARTY_BUTTON);
        u32 trayTabMoving = BgCellManager_UpdateCellMove(work->view->panels, PC_BOX_PANEL_TRAY_TAB);
        u32 returnButtonMoving = BgCellManager_UpdateCellMove(work->view->panels, PC_BOX_PANEL_RETURN_BUTTON);
        if (partyButtonMoving == 0 && trayTabMoving == 0 && returnButtonMoving == 0) {
            if (work->view->heldItem != ITEM_NONE) {
                PCBox_SetHeldItemIconAffine(work->view, 0);
                PCBox_SetSpriteVisible(work->view, PC_BOX_SPRITE_HELD_ITEM, FALSE);
            }
            view->subState = 0;
            return 0;
        }
        break;
    }
    }
    return 1;
}

u32 PCBox_AnimateSwappedItemMove(PCBoxWork *work) {
    PCBoxView *view = work->view;
    switch (view->subState) {
    case 0:
        if (PCBox_IsSpriteAnimated(view, PC_BOX_SPRITE_HELD_ITEM) != 1) {
            u32 old = work->selectedSlot;
            work->selectedSlot = (u8)((PCBoxHeldItemMove *)view->temp)->toSlot;
            PCBox_StartHeldItemMoveWithIcon(work, old, old, 2);
            view->subState = 1;
        }
        break;
    case 1:
        if (PCBox_UpdateHeldItemMoveWithIcon(work) == 0) {
            view->subState = 0;
            return 0;
        }
        break;
    }
    return 1;
}

int PCBox_UpdateItemTrayDrag(PCBoxWork *work) {
    PCBoxView *view = work->view;
    int x, y;
    u16 selected, raw;
    BgCellManager_UpdateCellMove(view->panels, PC_BOX_PANEL_CHANGE_BOX_BUTTON);
    BgCellManager_UpdateCellMove(work->view->panels, PC_BOX_PANEL_SUMMARY_BUTTON);
    switch (view->subState) {
    case 0:
        PCBox_SetHeldItemIconAffine(work->view, 1);
        PCBox_SetSpriteAnim(work->view, PC_BOX_SPRITE_HELD_ITEM, 1);
        PCBox_SetSpriteVisible(work->view, PC_BOX_SPRITE_HELD_ITEM, TRUE);
        view->subState = 1;
        break;
    case 1:
        if (PCBox_IsSpriteAnimated(work->view, PC_BOX_SPRITE_HELD_ITEM) == 0) {
            PCBox_SetHeldItemIconAffine(work->view, 0);
            PCBox_ShowHeldItemIconOutline(work->view);
            view->subState = 2;
        }
        break;
    case 2:
        if (!System_GetTouchHeldCoords(&x, &y)) {
            selected = PCBox_GetTouchedBoxSlot(work->view->touchX, work->view->touchY);
            if (selected == 255) {
                selected = PCBox_GetTouchedPartySlot(work->view->touchX, work->view->touchY, gPCBoxTrayPartyDropRects);
            }
            raw = selected;
            if (selected == 255) {
                selected = work->selectedSlot;
            } else if (!PCBox_CanSwapHeldItems(work, work->selectedSlot, selected)) {
                selected = work->selectedSlot;
            }
            PCBox_StartHeldItemMoveWithIcon(work, raw, selected, 2);
            view->subState = 3;
        } else {
            PCBox_SetHeldItemIconPosition(work->view, x, y);
            PCBox_UpdateHeldItemIconOutline(work->view);
            work->view->touchX = x;
            work->view->touchY = y;
        }
        break;
    case 3:
        if (!PCBox_UpdateHeldItemMoveWithIcon(work)) {
            PlaySE(SEQ_SE_DP_BOX01);
            PCBox_SlideInSummaryButton(work->view->panels);
            view->subState = 4;
        }
        break;
    case 4:
        PCBox_SetHeldItemIconAffine(work->view, 1);
        PCBox_SetSpriteAnim(work->view, PC_BOX_SPRITE_HELD_ITEM, 2);
        PCBox_SetSelectedIconOutlineVisible(work, 0);
        view->subState = 5;
        break;
    case 5:
        if (!PCBox_IsSpriteAnimated(work->view, PC_BOX_SPRITE_HELD_ITEM)) {
            PCBox_SetSpriteVisible(work->view, PC_BOX_SPRITE_HELD_ITEM, FALSE);
            PCBox_SetHeldItemIconAffine(work->view, 0);
            view->subState = 6;
        }
        break;
    case 6:
        view->subState = 0;
        return 0;
    }
    return 1;
}

u32 PCBox_AnimateTraySwappedItemMove(PCBoxWork *work) {
    PCBoxView *view = work->view;
    switch (view->subState) {
    case 0:
        PCBox_SetHeldItemIconAffine(view, 1);
        PCBox_SetSpriteAnim(work->view, PC_BOX_SPRITE_HELD_ITEM, 1);
        PCBox_SetSpriteVisible(work->view, PC_BOX_SPRITE_HELD_ITEM, TRUE);
        view->subState = 1;
        break;
    case 1:
        if (PCBox_IsSpriteAnimated(view, PC_BOX_SPRITE_HELD_ITEM) == 0) {
            PCBox_SetHeldItemIconAffine(work->view, 0);
            view->subState = 2;
        }
        break;
    case 2: {
        u32 old = work->selectedSlot;
        work->selectedSlot = (u8)((PCBoxHeldItemMove *)view->temp)->toSlot;
        PCBox_StartHeldItemMoveWithIcon(work, old, old, 2);
        view->subState = 3;
        break;
    }
    case 3:
        if (PCBox_UpdateHeldItemMoveWithIcon(work) == 0) {
            PlaySE(SEQ_SE_DP_BOX01);
            view->subState = 4;
        }
        break;
    case 4:
        PCBox_SetHeldItemIconAffine(view, 1);
        PCBox_SetSpriteAnim(work->view, PC_BOX_SPRITE_HELD_ITEM, 2);
        view->subState = 5;
        break;
    case 5:
        if (PCBox_IsSpriteAnimated(view, PC_BOX_SPRITE_HELD_ITEM) == 0) {
            PCBox_SetSpriteVisible(work->view, PC_BOX_SPRITE_HELD_ITEM, FALSE);
            PCBox_SetHeldItemIconAffine(work->view, 0);
            view->subState = 6;
        }
        break;
    case 6:
        view->subState = 0;
        return 0;
    }
    return 1;
}

BOOL PCBox_AnimateTrayItemPickUp(PCBoxWork *work) {
    PCBoxView *view = work->view;

    struct {
        s16 y, x;
    } pos;

    BgCellManager_UpdateCellMove(view->panels, PC_BOX_PANEL_SUMMARY_BUTTON);
    switch (view->subState) {
    case 0:
        PCBox_SetHeldItemIconAffine(work->view, 1);
        PCBox_SetSpriteAnim(work->view, PC_BOX_SPRITE_HELD_ITEM, 1);
        PCBox_SetSpriteVisible(work->view, PC_BOX_SPRITE_HELD_ITEM, TRUE);
        view->subState++;
        break;
    case 1:
        if (!PCBox_IsSpriteAnimated(work->view, PC_BOX_SPRITE_HELD_ITEM)) {
            PCBox_SetHeldItemIconAffine(work->view, 0);
            view->subState++;
        }
        break;
    case 2:
        PCBox_SetSpriteAnim(work->view, PC_BOX_SPRITE_CURSOR, 9);
        view->subState++;
    case 3:
        if (view->counter == 4) {
            view->counter = 0;
            view->subState++;
        } else {
            ManagedSprite_GetPositionXY(work->view->sprites[PC_BOX_SPRITE_CURSOR], &pos.x, &pos.y);
            ManagedSprite_SetPositionXY(work->view->sprites[PC_BOX_SPRITE_CURSOR], pos.x, (s16)(pos.y + 2));
            view->counter++;
        }
        break;
    case 4:
        PCBox_SetSpriteAnim(work->view, PC_BOX_SPRITE_CURSOR, 10);
        view->subState++;
    case 5:
        if (view->counter == 4) {
            view->counter = 0;
            view->subState = 0;
            return FALSE;
        }
        ManagedSprite_GetPositionXY(work->view->sprites[PC_BOX_SPRITE_CURSOR], &pos.x, &pos.y);
        ManagedSprite_SetPositionXY(work->view->sprites[PC_BOX_SPRITE_CURSOR], pos.x, (s16)(pos.y - 2));
        ManagedSprite_GetPositionXY(work->view->sprites[PC_BOX_SPRITE_HELD_ITEM], &pos.x, &pos.y);
        ManagedSprite_SetPositionXY(work->view->sprites[PC_BOX_SPRITE_HELD_ITEM], pos.x, (s16)(pos.y - 2));
        view->counter++;
        break;
    default:
        break;
    }
    return TRUE;
}

u32 PCBox_AnimateTrayItemDrop(PCBoxWork *work) {
    s16 pos[2];
    PCBoxView *view = work->view;
    switch (view->subState) {
    case 0:
        PCBox_SetSpriteAnim(view, PC_BOX_SPRITE_CURSOR, 9);
        view->subState = 1;
    case 1:
        if (view->counter == 4) {
            view->counter = 0;
            view->subState = 2;
            break;
        }
        ManagedSprite_GetPositionXY(work->view->sprites[PC_BOX_SPRITE_HELD_ITEM], &pos[1], &pos[0]);
        ManagedSprite_SetPositionXY(work->view->sprites[PC_BOX_SPRITE_HELD_ITEM], pos[1], (s16)(pos[0] + 2));
        view->counter++;
        break;
    case 2:
        PCBox_SetSpriteAnim(view, PC_BOX_SPRITE_CURSOR, 8);
        PCBox_SetHeldItemIconAffine(work->view, 1);
        PCBox_SetSpriteAnim(work->view, PC_BOX_SPRITE_HELD_ITEM, 2);
        view->subState = 3;
        break;
    case 3:
        if (PCBox_IsSpriteAnimated(view, PC_BOX_SPRITE_HELD_ITEM) == 0) {
            PCBox_SetHeldItemIconAffine(work->view, 0);
            PCBox_SetSpriteVisible(work->view, PC_BOX_SPRITE_HELD_ITEM, FALSE);
            view->subState = 4;
        }
        break;
    case 4:
        PCBox_SetSpriteAnim(view, PC_BOX_SPRITE_CURSOR, 8);
        view->subState = 0;
        return 0;
    }
    return 1;
}

u32 PCBox_AnimateTrayItemReturn(PCBoxWork *work) {
    PCBoxView *view = work->view;
    BgCellManager_UpdateCellMove(view->panels, PC_BOX_PANEL_SUMMARY_BUTTON);
    switch (view->subState) {
    case 0:
        PCBox_SetSpriteAnim(work->view, PC_BOX_SPRITE_CURSOR, 9);
        PCBox_StartHeldItemMoveFromDropTarget(work, work->view->itemFromSlot, 2);
        view->subState = 1;
        break;
    case 1:
        if (PCBox_UpdateHeldItemMoveNoIcon(work) == 0) {
            view->subState = 2;
        }
        break;
    case 2:
        PCBox_SetHeldItemIconAffine(work->view, 1);
        PCBox_SetSpriteAnim(work->view, PC_BOX_SPRITE_HELD_ITEM, 2);
        view->subState = 3;
        break;
    case 3:
        if (PCBox_IsSpriteAnimated(work->view, PC_BOX_SPRITE_HELD_ITEM) == 0) {
            PCBox_SetHeldItemIconAffine(work->view, 0);
            PCBox_SetSpriteVisible(work->view, PC_BOX_SPRITE_HELD_ITEM, FALSE);
            view->subState = 4;
        }
        break;
    case 4:
        PCBox_SetSpriteAnim(work->view, PC_BOX_SPRITE_CURSOR, 8);
        view->subState = 0;
        return 0;
    }
    return 1;
}

int PCBox_UpdateItemModePartyDrag(PCBoxWork *work) {
    PCBoxView *view = work->view;
    int busy = PCBox_UpdateActionMenuSlide(view->panels), other = PCBox_UpdatePartyPanelSlide(work);
    u32 x, y;
    BgCellManager_UpdateCellMove(work->view->panels, PC_BOX_PANEL_RETURN_BUTTON);
    switch (view->subState) {
    case 0:
        if (work->view->heldItem) {
            PCBox_SetHeldItemIconAffine(work->view, 1);
            PCBox_SetSpriteAnim(work->view, PC_BOX_SPRITE_HELD_ITEM, 1);
            PCBox_SetSpriteVisible(work->view, PC_BOX_SPRITE_HELD_ITEM, TRUE);
            view->subState = 1;
        } else {
            PCBox_SlideInActionMenu(work->view->panels);
            view->subState = 10;
        }
        break;
    case 1:
        if (PCBox_IsSpriteAnimated(work->view, PC_BOX_SPRITE_HELD_ITEM) == 1) {
            break;
        }
        PCBox_SetHeldItemIconAffine(work->view, 0);
        PCBox_ShowHeldItemIconOutline(work->view);
        view->subState = 2;
    case 2:
        if (work->view->partyPanelLowered == 1 && other == 0) {
            work->view->partyPanelLowered = 2;
            PCBox_DrawWindowFrame(work, 40);
            PCBox_SetIconsTranslucent(work, 129, 0);
        }
        if (!System_GetTouchHeldCoords(&x, &y)) {
            if (work->view->partyPanelLowered == 2) {
                other = (u16)PCBox_GetTouchedBoxSlot(work->view->touchX, work->view->touchY);
            } else {
                other = (u16)PCBox_GetTouchedPartySlot(work->view->touchX, work->view->touchY, gPCBoxPartyDropRects);
            }
            busy = other;
            if (other == 255) {
                other = work->selectedSlot;
            } else if (!PCBox_CanSwapHeldItems(work, work->selectedSlot, other)) {
                other = work->selectedSlot;
            }
            if (other == work->selectedSlot) {
                PCBox_SlideInActionMenu(work->view->panels);
                if (work->view->partyPanelLowered) {
                    PCBox_RaisePartyPanel(work->view->panels);
                    PCBox_SetIconsTranslucent(work, 1, 1);
                }
            } else {
                PCBox_SlideOutItemInfoPanel(work->view->panels);
            }
            PCBox_StartHeldItemMoveWithIcon(work, busy, other, 1);
            view->subState = 3;
        } else {
            if (busy == 0 && work->view->partyPanelLowered == 0 && (x < 16 || y < 48 || x >= 104)) {
                work->view->partyPanelLowered = 1;
                PCBox_LowerPartyPanel(work->view->panels);
            }
            PCBox_SetHeldItemIconPosition(work->view, x, y);
            PCBox_UpdateHeldItemIconOutline(work->view);
            work->view->touchX = x;
            work->view->touchY = y;
        }
        break;
    case 3:
        if (!PCBox_UpdateHeldItemMoveWithIcon(work)) {
            view->subState = 10;
        }
        break;
    case 10:
        if (busy == 0 && other == 0) {
            if (work->view->heldItem) {
                PCBox_SetHeldItemIconAffine(work->view, 0);
                PCBox_ShowHeldItemIconOutline(work->view);
            }
            view->subState = 0;
            return 0;
        }
        break;
    }
    return 1;
}

u32 PCBox_AnimatePartySwappedItemMove(PCBoxWork *work) {
    PCBoxView *view = work->view;
    u32 partyPanelMoving = PCBox_UpdatePartyPanelSlide(work);
    switch (view->subState) {
    case 0:
        if (PCBox_IsSpriteAnimated(work->view, PC_BOX_SPRITE_HELD_ITEM) == 0) {
            u32 old = work->selectedSlot;
            work->selectedSlot = (u8)((PCBoxHeldItemMove *)view->temp)->toSlot;
            PCBox_StartHeldItemMoveWithIcon(work, old, old, 1);
            if (work->view->partyPanelLowered != 0) {
                work->view->partyPanelLowered = 0;
                PCBox_RaisePartyPanel(work->view->panels);
                PCBox_SetIconsTranslucent(work, 1, 1);
            }
            view->subState = 1;
        }
        break;
    case 1:
        if (PCBox_UpdateHeldItemMoveWithIcon(work) == 0 && partyPanelMoving == 0) {
            view->subState = 0;
            return 0;
        }
        break;
    }
    return 1;
}

BOOL PCBox_RunStateMachine(PCBoxWork *work, int *state) {
    *state = gPCBoxStateTable[*state](work);
    if (*state == PC_BOX_STATE_EXIT) {
        return FALSE;
    }
    return TRUE;
}
