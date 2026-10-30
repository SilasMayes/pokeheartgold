// Converted from asm/easy_chat_app_data.s (part 1 of 2) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

#include "global.h"

#include "easy_chat_app_panels.h"

#pragma force_active on

extern void EasyChatAppView_Cmd_CloseCategories(void);
extern void EasyChatAppView_Cmd_CloseWordList(void);
extern void EasyChatAppView_Cmd_CloseYesNo(void);
extern void EasyChatAppView_Cmd_ConfirmFinish(void);
extern void EasyChatAppView_Cmd_ConfirmQuit(void);
extern void EasyChatAppView_Cmd_DrawYesNoCursor(void);
extern void EasyChatAppView_Cmd_FadeIn(void);
extern void EasyChatAppView_Cmd_FocusMenu(void);
extern void EasyChatAppView_Cmd_FocusSentence(void);
extern void EasyChatAppView_Cmd_HideMessage(void);
extern void EasyChatAppView_Cmd_Load(void);
extern void EasyChatAppView_Cmd_MoveMenuCursor(void);
extern void EasyChatAppView_Cmd_Nop(void);
extern void EasyChatAppView_Cmd_OpenCategories(void);
extern void EasyChatAppView_Cmd_OpenWordList(void);
extern void EasyChatAppView_Cmd_PressPageDown(void);
extern void EasyChatAppView_Cmd_PressPageUp(void);
extern void EasyChatAppView_Cmd_RedrawSentence(void);
extern void EasyChatAppView_Cmd_ReleasePageDown(void);
extern void EasyChatAppView_Cmd_ReleasePageUp(void);
extern void EasyChatAppView_Cmd_ScrollWordList(void);
extern void EasyChatAppView_Cmd_SetCategoryCursor(void);
extern void EasyChatAppView_Cmd_SetMenuCursor(void);
extern void EasyChatAppView_Cmd_SetWordListCursor(void);
extern void EasyChatAppView_Cmd_ShowCategoryCursor(void);
extern void EasyChatAppView_Cmd_ShowIncompleteMessage(void);
extern void EasyChatAppView_Cmd_ShowWordListCursor(void);
extern void EasyChatAppView_Cmd_SwitchListMode(void);
extern void EasyChatAppView_Cmd_SwitchMode(void);
extern void EasyChatAppView_Cmd_Unload(void);
extern void EasyChatAppView_Cmd_WordListToCategories(void);
extern void EasyChatAppView_Cmd_WordListToMenu(void);

// 0x021EC788
// clang-format off
const EasyChatViewCommandFunc gEasyChatViewCommandFuncs[32] = {
    (EasyChatViewCommandFunc)EasyChatAppView_Cmd_Load, (EasyChatViewCommandFunc)EasyChatAppView_Cmd_Unload,
    (EasyChatViewCommandFunc)EasyChatAppView_Cmd_FadeIn,
    (EasyChatViewCommandFunc)EasyChatAppView_Cmd_RedrawSentence,
    (EasyChatViewCommandFunc)EasyChatAppView_Cmd_Nop,
    (EasyChatViewCommandFunc)EasyChatAppView_Cmd_ShowCategoryCursor,
    (EasyChatViewCommandFunc)EasyChatAppView_Cmd_ShowWordListCursor,
    (EasyChatViewCommandFunc)EasyChatAppView_Cmd_FocusMenu,
    (EasyChatViewCommandFunc)EasyChatAppView_Cmd_FocusSentence,
    (EasyChatViewCommandFunc)EasyChatAppView_Cmd_OpenCategories,
    (EasyChatViewCommandFunc)EasyChatAppView_Cmd_CloseCategories,
    (EasyChatViewCommandFunc)EasyChatAppView_Cmd_OpenWordList,
    (EasyChatViewCommandFunc)EasyChatAppView_Cmd_WordListToCategories,
    (EasyChatViewCommandFunc)EasyChatAppView_Cmd_CloseWordList,
    (EasyChatViewCommandFunc)EasyChatAppView_Cmd_WordListToMenu,
    (EasyChatViewCommandFunc)EasyChatAppView_Cmd_MoveMenuCursor,
    (EasyChatViewCommandFunc)EasyChatAppView_Cmd_SetMenuCursor,
    (EasyChatViewCommandFunc)EasyChatAppView_Cmd_SetCategoryCursor,
    (EasyChatViewCommandFunc)EasyChatAppView_Cmd_SetWordListCursor,
    (EasyChatViewCommandFunc)EasyChatAppView_Cmd_ScrollWordList,
    (EasyChatViewCommandFunc)EasyChatAppView_Cmd_HideMessage,
    (EasyChatViewCommandFunc)EasyChatAppView_Cmd_ConfirmFinish,
    (EasyChatViewCommandFunc)EasyChatAppView_Cmd_ConfirmQuit,
    (EasyChatViewCommandFunc)EasyChatAppView_Cmd_ShowIncompleteMessage,
    (EasyChatViewCommandFunc)EasyChatAppView_Cmd_DrawYesNoCursor,
    (EasyChatViewCommandFunc)EasyChatAppView_Cmd_CloseYesNo,
    (EasyChatViewCommandFunc)EasyChatAppView_Cmd_SwitchMode,
    (EasyChatViewCommandFunc)EasyChatAppView_Cmd_SwitchListMode,
    (EasyChatViewCommandFunc)EasyChatAppView_Cmd_PressPageUp,
    (EasyChatViewCommandFunc)EasyChatAppView_Cmd_PressPageDown,
    (EasyChatViewCommandFunc)EasyChatAppView_Cmd_ReleasePageUp,
    (EasyChatViewCommandFunc)EasyChatAppView_Cmd_ReleasePageDown,
};
// clang-format on

// 0x021EC760
// clang-format off
const GraphicsBanks gEasyChatAppViewGraphicsBanks = {
    GX_VRAM_BG_128_B, GX_VRAM_BGEXTPLTT_NONE, GX_VRAM_SUB_BG_128_C, GX_VRAM_SUB_BGEXTPLTT_NONE,
    GX_VRAM_OBJ_64_E, GX_VRAM_OBJEXTPLTT_NONE, GX_VRAM_SUB_OBJ_16_I, GX_VRAM_SUB_OBJEXTPLTT_NONE,
    GX_VRAM_TEX_NONE, GX_VRAM_TEXPLTT_NONE,
};
// clang-format on

// 0x021EC70C
// clang-format off
const BgTemplate gEasyChatBgTemplate_Main3 = {
    0, 0, 0x00000800, 0, 0x01, 0x00, 0x1F, 0x02, 0x00, 0x03, 0x00, 0x00, 0,
};
// clang-format on

// 0x021EC728
// clang-format off
const BgTemplate gEasyChatBgTemplate_Main0 = {
    0, 0, 0x00000800, 0, 0x01, 0x00, 0x1B, 0x00, 0x00, 0x00, 0x00, 0x00, 0,
};
// clang-format on

// 0x021EC6F0
// clang-format off
const BgTemplate gEasyChatBgTemplate_Sub1 = {
    0, 0, 0x00000800, 0, 0x01, 0x00, 0x1D, 0x02, 0x00, 0x01, 0x00, 0x00, 0,
};
// clang-format on

// 0x021EC6B8
// clang-format off
const BgTemplate gEasyChatBgTemplate_Main2 = {
    0, 0, 0x00000800, 0, 0x01, 0x00, 0x1E, 0x06, 0x00, 0x02, 0x00, 0x00, 0,
};
// clang-format on

// 0x021EC6D4
// clang-format off
const BgTemplate gEasyChatBgTemplate_Main1 = {
    0, 0, 0x00001000, 0, 0x03, 0x00, 0x1C, 0x04, 0x00, 0x01, 0x00, 0x00, 0,
};
// clang-format on

// 0x021EC744
// clang-format off
const BgTemplate gEasyChatBgTemplate_Sub0 = {
    0, 0, 0x00000800, 0, 0x01, 0x00, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x00, 0,
};
// clang-format on

// 0x021EC698
const ObjCharTransferTemplate gEasyChatObjCharTransferTemplate = { 2, 3200, 0, HEAP_ID_35 };

// 0x021EC6A8
// clang-format off
const GraphicsModes gEasyChatAppViewGraphicsModes = {
    GX_DISPMODE_GRAPHICS, GX_BGMODE_0, GX_BGMODE_0, GX_BG0_AS_2D,
};
// clang-format on

const u8 ov102_021EC690[8] __attribute__((aligned(4))) = { 0x10, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00 };
