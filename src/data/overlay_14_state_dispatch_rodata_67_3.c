// Converted from asm/overlay_14_state_dispatch_rodata_67.s (part 3 of 6) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

#include "global.h"

#include "constants/pokemon.h"

#include "application/pc_box/pc_box_internal.h"

#pragma force_active on

// clang-format off
const PCBoxStateFunc gPCBoxStateTable[179] = {
    (PCBoxStateFunc)PCBox_State_Init, (PCBoxStateFunc)PCBox_State_Exit, (PCBoxStateFunc)PCBox_State_WaitFade,
    (PCBoxStateFunc)PCBox_State_WaitPaletteBuffers, (PCBoxStateFunc)PCBox_State_Delay,
    (PCBoxStateFunc)PCBox_State_WaitUpdateFunc, (PCBoxStateFunc)PCBox_State_WaitButton,
    (PCBoxStateFunc)PCBox_State_HandleYesNo, (PCBoxStateFunc)PCBox_State_WaitPaletteFlash,
    (PCBoxStateFunc)PCBox_State_StartSubApp, (PCBoxStateFunc)PCBox_State_RunSubApp,
    (PCBoxStateFunc)PCBox_State_Start, (PCBoxStateFunc)PCBox_State_MoveModeInput,
    (PCBoxStateFunc)PCBox_State_ApplyMonMove, (PCBoxStateFunc)PCBox_State_ReturnToActionMenu,
    (PCBoxStateFunc)PCBox_State_ReturnFromSummary, (PCBoxStateFunc)PCBox_State_ReturnFromNamingScreen,
    (PCBoxStateFunc)PCBox_State_GiveItemFromBag, (PCBoxStateFunc)PCBox_State_PrintItemHeld,
    (PCBoxStateFunc)PCBox_State_MarkingChosen, (PCBoxStateFunc)PCBox_State_OpenMarkingMenu,
    (PCBoxStateFunc)PCBox_State_SetupMarkingMenuInput, (PCBoxStateFunc)PCBox_State_MarkingMenuInput,
    (PCBoxStateFunc)PCBox_State_FinishCloseMarkingMenu,
    (PCBoxStateFunc)PCBox_State_EndCursorSlideToMarkingMenu, (PCBoxStateFunc)PCBox_State_TryRelease,
    (PCBoxStateFunc)PCBox_State_ReleaseMoveCheck, (PCBoxStateFunc)PCBox_State_PrintReleased,
    (PCBoxStateFunc)PCBox_State_PrintByeBye, (PCBoxStateFunc)PCBox_State_RemoveReleasedMon,
    (PCBoxStateFunc)PCBox_State_ReleaseCameBack, (PCBoxStateFunc)PCBox_State_PrintWorried,
    (PCBoxStateFunc)PCBox_State_CancelRelease, (PCBoxStateFunc)PCBox_State_EndPartyReleaseShift,
    (PCBoxStateFunc)PCBox_State_OpenPartyPanel, (PCBoxStateFunc)PCBox_State_SetupPartyPanelInput,
    (PCBoxStateFunc)PCBox_State_MoveModePartyInput, (PCBoxStateFunc)PCBox_State_SlideOutPartyPanel,
    (PCBoxStateFunc)PCBox_State_PartyPanelClosed, (PCBoxStateFunc)PCBox_State_EndMoveModePartyDrag,
    (PCBoxStateFunc)PCBox_State_SetupBoxTrayInput, (PCBoxStateFunc)PCBox_State_BoxTrayInput,
    (PCBoxStateFunc)PCBox_State_EndBoxTrayDrag, (PCBoxStateFunc)PCBox_State_EndTrayHoldingDrop,
    (PCBoxStateFunc)PCBox_State_ResumeBoxTrayInput, (PCBoxStateFunc)PCBox_State_OpenTrayBesideParty,
    (PCBoxStateFunc)PCBox_State_SetupPartyInputAfterTray, (PCBoxStateFunc)PCBox_State_OpenTrayFromBox,
    (PCBoxStateFunc)PCBox_State_SlideInTrayPartyPanel, (PCBoxStateFunc)PCBox_State_SlideOutTray,
    (PCBoxStateFunc)PCBox_State_TrayClosed, (PCBoxStateFunc)PCBox_State_ReturnToBoxFromTray,
    (PCBoxStateFunc)PCBox_State_HideButtonsForBoxMenu, (PCBoxStateFunc)PCBox_State_OpenBoxMenuTray,
    (PCBoxStateFunc)PCBox_State_ShowBoxMenuExitButton, (PCBoxStateFunc)PCBox_State_OpenBoxMenu,
    (PCBoxStateFunc)PCBox_State_SetupBoxMenuInput, (PCBoxStateFunc)PCBox_State_CloseBoxMenu,
    (PCBoxStateFunc)PCBox_State_SlideOutBoxMenu, (PCBoxStateFunc)PCBox_State_CloseBoxMenuTray,
    (PCBoxStateFunc)PCBox_State_BoxMenuClosed, (PCBoxStateFunc)PCBox_State_BoxMenuInput,
    (PCBoxStateFunc)PCBox_State_EndCursorSlideToBoxMenu, (PCBoxStateFunc)PCBox_State_OpenWallpaperMenu,
    (PCBoxStateFunc)PCBox_State_ShowWallpaperMenuTitle, (PCBoxStateFunc)PCBox_State_SetupWallpaperMenuInput,
    (PCBoxStateFunc)PCBox_State_WallpaperMenuInput, (PCBoxStateFunc)PCBox_State_CloseWallpaperMenu,
    (PCBoxStateFunc)PCBox_State_SlideOutWallpaperList, (PCBoxStateFunc)PCBox_State_ReturnToBoxMenu,
    (PCBoxStateFunc)PCBox_State_ApplyWallpaper, (PCBoxStateFunc)PCBox_State_WallpaperFadeOut,
    (PCBoxStateFunc)PCBox_State_WallpaperFadeIn, (PCBoxStateFunc)PCBox_State_EndCursorSlideToWallpaperMenu,
    (PCBoxStateFunc)PCBox_State_EndCursorSlideToMoveMode, (PCBoxStateFunc)PCBox_State_EndCursorSlideToBoxTray,
    (PCBoxStateFunc)PCBox_State_EndCursorSlideToMoveModeParty, (PCBoxStateFunc)PCBox_State_ResumeBoxInput,
    (PCBoxStateFunc)PCBox_State_ResumeMoveModePartyInput, (PCBoxStateFunc)PCBox_State_PrintEggCantHoldItem,
    (PCBoxStateFunc)PCBox_State_PrintMailCantBeTaken, (PCBoxStateFunc)PCBox_State_WithdrawInput,
    (PCBoxStateFunc)PCBox_State_ReturnToWithdrawInput, (PCBoxStateFunc)PCBox_State_SlideInWithdrawParty,
    (PCBoxStateFunc)PCBox_State_StartWithdrawMove, (PCBoxStateFunc)PCBox_State_EndWithdrawMove,
    (PCBoxStateFunc)PCBox_State_WithdrawPartyClosed, (PCBoxStateFunc)PCBox_State_EndWithdrawDrag,
    (PCBoxStateFunc)PCBox_State_EndCursorSlideToWithdraw,
    (PCBoxStateFunc)PCBox_State_EndCursorSlideToWithdrawPrompt,
    (PCBoxStateFunc)PCBox_State_ResumeWithdrawInput, (PCBoxStateFunc)PCBox_State_DepositInput,
    (PCBoxStateFunc)PCBox_State_TryDeposit, (PCBoxStateFunc)PCBox_State_ReturnFromDepositError,
    (PCBoxStateFunc)PCBox_State_ShowDepositBoxSelect, (PCBoxStateFunc)PCBox_State_ShowDepositTitle,
    (PCBoxStateFunc)PCBox_State_SetupDepositBoxInput, (PCBoxStateFunc)PCBox_State_DepositBoxInput,
    (PCBoxStateFunc)PCBox_State_CancelDepositBoxSelect, (PCBoxStateFunc)PCBox_State_HideDepositExitButton,
    (PCBoxStateFunc)PCBox_State_HideDepositBoxSelect, (PCBoxStateFunc)PCBox_State_DepositBoxSelectClosed,
    (PCBoxStateFunc)PCBox_State_ConfirmDepositBox, (PCBoxStateFunc)PCBox_State_CheckDepositBox,
    (PCBoxStateFunc)PCBox_State_ShiftPartyForDeposit, (PCBoxStateFunc)PCBox_State_SwitchBox,
    (PCBoxStateFunc)PCBox_State_StartDepositMove, (PCBoxStateFunc)PCBox_State_EndDepositMove,
    (PCBoxStateFunc)PCBox_State_ShowDepositReturnButton, (PCBoxStateFunc)PCBox_State_ResetDepositInput,
    (PCBoxStateFunc)PCBox_State_EndDepositDrag, (PCBoxStateFunc)PCBox_State_EndCursorSlideToDeposit,
    (PCBoxStateFunc)PCBox_State_EndCursorSlideToDepositPrompt,
    (PCBoxStateFunc)PCBox_State_EndCursorSlideToDepositBox, (PCBoxStateFunc)PCBox_State_ResumeDepositInput,
    (PCBoxStateFunc)PCBox_State_BoxTrayHoldingInput,
    (PCBoxStateFunc)PCBox_State_EndCursorSlideToBoxTrayHolding, (PCBoxStateFunc)PCBox_State_ItemModeInput,
    (PCBoxStateFunc)PCBox_State_EndCursorSlideToItemMode, (PCBoxStateFunc)PCBox_State_CloseItemMessage,
    (PCBoxStateFunc)PCBox_State_AskPutAwayItem, (PCBoxStateFunc)PCBox_State_WaitPutAwayItem,
    (PCBoxStateFunc)PCBox_State_CancelPutAwayItem, (PCBoxStateFunc)PCBox_State_EndItemCommand,
    (PCBoxStateFunc)PCBox_State_ItemModePrintEggCantHoldItem,
    (PCBoxStateFunc)PCBox_State_ItemModePrintItemHeld, (PCBoxStateFunc)PCBox_State_EndItemModeBoxDrag,
    (PCBoxStateFunc)PCBox_State_SwapHeldItems, (PCBoxStateFunc)PCBox_State_DropSwappedItem,
    (PCBoxStateFunc)PCBox_State_FinishItemSwap, (PCBoxStateFunc)PCBox_State_ItemModeBoxTrayInput,
    (PCBoxStateFunc)PCBox_State_EndCursorSlideToItemModeTray, (PCBoxStateFunc)PCBox_State_EndItemTrayDrag,
    (PCBoxStateFunc)PCBox_State_ApplyItemTrayDrop, (PCBoxStateFunc)PCBox_State_FinishItemTrayDrop,
    (PCBoxStateFunc)PCBox_State_ResumeItemModeTrayInput, (PCBoxStateFunc)PCBox_State_ItemTrayHoldingInput,
    (PCBoxStateFunc)PCBox_State_EndCursorSlideToItemTrayHolding,
    (PCBoxStateFunc)PCBox_State_ApplyItemTrayHoldingDrop, (PCBoxStateFunc)PCBox_State_ItemModePartyInput,
    (PCBoxStateFunc)PCBox_State_EndCursorSlideToItemModeParty,
    (PCBoxStateFunc)PCBox_State_EndItemModePartyDrag, (PCBoxStateFunc)PCBox_State_SwapPartyHeldItems,
    (PCBoxStateFunc)PCBox_State_ResumeItemModePartyInput, (PCBoxStateFunc)PCBox_State_DropSwappedPartyItem,
    (PCBoxStateFunc)PCBox_State_FinishPartyItemSwap, (PCBoxStateFunc)PCBox_State_ResumeItemModePartyAfterMail,
    (PCBoxStateFunc)PCBox_State_AskExit, (PCBoxStateFunc)PCBox_State_AskContinue,
    (PCBoxStateFunc)PCBox_State_ChooseParty, (PCBoxStateFunc)PCBox_State_ChooseTrayTab,
    (PCBoxStateFunc)PCBox_State_ChooseSummary, (PCBoxStateFunc)PCBox_State_ChooseItem,
    (PCBoxStateFunc)PCBox_State_ChooseMarking, (PCBoxStateFunc)PCBox_State_ChooseMarkingDone,
    (PCBoxStateFunc)PCBox_State_ChooseRelease, (PCBoxStateFunc)PCBox_State_CloseMoveModeActionMenu,
    (PCBoxStateFunc)PCBox_State_PartyChooseTray, (PCBoxStateFunc)PCBox_State_CloseMoveModePartyActionMenu,
    (PCBoxStateFunc)PCBox_State_ChoosePartyPanelExit, (PCBoxStateFunc)PCBox_State_ChooseTrayBox,
    (PCBoxStateFunc)PCBox_State_ChooseTrayExit, (PCBoxStateFunc)PCBox_State_BoxMenuSwitchBox,
    (PCBoxStateFunc)PCBox_State_ChooseWallpaper, (PCBoxStateFunc)PCBox_State_ChooseRename,
    (PCBoxStateFunc)PCBox_State_SwitchBoxForWallpaper, (PCBoxStateFunc)PCBox_State_ChooseWallpaperMenuExit,
    (PCBoxStateFunc)PCBox_State_ChooseWithdraw, (PCBoxStateFunc)PCBox_State_CloseWithdrawActionMenu,
    (PCBoxStateFunc)PCBox_State_ChooseDeposit, (PCBoxStateFunc)PCBox_State_CloseDepositActionMenu,
    (PCBoxStateFunc)PCBox_State_ItemModeChooseParty, (PCBoxStateFunc)PCBox_State_ItemModeChooseTrayTab,
    (PCBoxStateFunc)PCBox_State_ChooseBagGive, (PCBoxStateFunc)PCBox_State_CloseItemModeActionMenu,
    (PCBoxStateFunc)PCBox_State_ItemModeChooseTrayBox, (PCBoxStateFunc)PCBox_State_ItemModePartyChooseTray,
    (PCBoxStateFunc)PCBox_State_CloseItemModePartyActionMenu, (PCBoxStateFunc)PCBox_State_ChooseMoveFromBox,
};
// clang-format on

const PCBoxStateFunc gPCBoxYesNoHandlers[5][2] = {
    { (PCBoxStateFunc)PCBox_TakeHeldItemToBag, (PCBoxStateFunc)PCBox_State_ReturnToActionMenu },
    { (PCBoxStateFunc)PCBox_ConfirmRelease,    (PCBoxStateFunc)PCBox_State_CancelRelease      },
    { (PCBoxStateFunc)PCBox_PutAwayHeldItem,   (PCBoxStateFunc)PCBox_State_CancelPutAwayItem  },
    { (PCBoxStateFunc)PCBox_ConfirmExit,       (PCBoxStateFunc)PCBox_CancelExit               },
    { (PCBoxStateFunc)PCBox_CancelExit,        (PCBoxStateFunc)PCBox_ConfirmExit              },
};

const PCBoxSubApp gPCBoxSubApps[3] = {
    { PCBox_StartSummaryApp,      PCBox_EndSummaryApp,      PC_BOX_STATE_RETURN_FROM_SUMMARY       },
    { PCBox_StartBagApp,          PCBox_EndBagApp,          PC_BOX_STATE_GIVE_ITEM_FROM_BAG        },
    { PCBox_StartNamingScreenApp, PCBox_EndNamingScreenApp, PC_BOX_STATE_RETURN_FROM_NAMING_SCREEN },
};

const PCBoxMenuEntry gPCBoxMoveMenu[5] = {
    { 0x003D, 1 },
    { 0x0041, 0 },
    { 0x0042, 0 },
    { 0x0043, 0 },
    { 0x0044, 0 },
};

const PCBoxMenuEntry gPCBoxWithdrawMenu[4] = {
    { 0x0045, 0 },
    { 0x0041, 0 },
    { 0x0043, 0 },
    { 0x0044, 0 }
};

const PCBoxMenuEntry gPCBoxDepositMenu[4] = {
    { 0x0046, 0 },
    { 0x0041, 0 },
    { 0x0043, 0 },
    { 0x0044, 0 }
};

const u8 gPCBoxBagPockets[8] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x06, 0x07, 0xFF };

const u8 gPCBoxSummaryPages[8] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x00, 0x00, 0x00 };
