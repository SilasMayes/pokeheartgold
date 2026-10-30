// Converted from asm/gts_data.s (part 1 of 7) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

// The C declarations of these do not match the data (see the notes at each
// definition): keep them out of the way of the definitions below.
#define gGtsCountryCount      gGtsCountryCount_header_decl
#define gGtsGenderSymbolMsgs  gGtsGenderSymbolMsgs_header_decl
#define gGtsWantedStates      gGtsWantedStates_header_decl
#define gGtsTransactionStates gGtsTransactionStates_header_decl
#define gGtsWantedBg1Template gGtsWantedBg1Template_header_decl
#define gGtsServer            gGtsServer_header_decl

#include "global.h"

#include "constants/pokemon.h"

#include "gts/gts_internal.h"

#pragma force_active on

#undef gGtsCountryCount
#undef gGtsGenderSymbolMsgs
#undef gGtsWantedStates
#undef gGtsTransactionStates
#undef gGtsWantedBg1Template
#undef gGtsServer

extern void GtsTransaction_AlreadyTraded(void);
extern void GtsTransaction_DepositDone(void);
extern void GtsTransaction_ExchangeDone(void);
extern void GtsTransaction_ExitToMainMenu(void);
extern void GtsTransaction_FadeOut(void);
extern void GtsTransaction_Idle(void);
extern void GtsTransaction_ReceiveDone(void);
extern void GtsTransaction_ReceiveTradedMon(void);
extern void GtsTransaction_SaveAndExit(void);
extern void GtsTransaction_SaveFirstPart(void);
extern void GtsTransaction_SaveRest(void);
extern void GtsTransaction_SaveWithMessage(void);
extern void GtsTransaction_SendDelete(void);
extern void GtsTransaction_SendExchange(void);
extern void GtsTransaction_SendExchangeFinish(void);
extern void GtsTransaction_SendGet(void);
extern void GtsTransaction_SendPost(void);
extern void GtsTransaction_SendPostFinish(void);
extern void GtsTransaction_SendResult(void);
extern void GtsTransaction_SendReturn(void);
extern void GtsTransaction_SendStatusGet(void);
extern void GtsTransaction_SendUnsavedReturn(void);
extern void GtsTransaction_ServerError(void);
extern void GtsTransaction_ServerErrorExit(void);
extern void GtsTransaction_Start(void);
extern void GtsTransaction_StartSave(void);
extern void GtsTransaction_StartSaveWithMessage(void);
extern void GtsTransaction_TradedDone(void);
extern void GtsTransaction_WaitDelete(void);
extern void GtsTransaction_WaitExchange(void);
extern void GtsTransaction_WaitExchangeFinish(void);
extern void GtsTransaction_WaitGet(void);
extern void GtsTransaction_WaitPost(void);
extern void GtsTransaction_WaitPostFinish(void);
extern void GtsTransaction_WaitResult(void);
extern void GtsTransaction_WaitReturn(void);
extern void GtsTransaction_WaitSaveDelay(void);
extern void GtsTransaction_WaitStatusGet(void);
extern void GtsTransaction_WaitText(void);
extern void GtsTransaction_WaitUnsavedReturn(void);
extern void GtsWanted_AskConfirm(void);
extern void GtsWanted_AskGender(void);
extern void GtsWanted_AskLevel(void);
extern void GtsWanted_FadeOut(void);
extern void GtsWanted_HandleConfirmPrompt(void);
extern void GtsWanted_HandleGenderSelector(void);
extern void GtsWanted_HandleInput(void);
extern void GtsWanted_HandleLevelSelector(void);
extern void GtsWanted_HandleSpeciesSelector(void);
extern void GtsWanted_InvalidState4(void);
extern void GtsWanted_InvalidState5(void);
extern void GtsWanted_OpenGenderSelector(void);
extern void GtsWanted_OpenLevelSelector(void);
extern void GtsWanted_OpenSpeciesSelector(void);
extern void GtsWanted_ShowConfirmPrompt(void);
extern void GtsWanted_Start(void);
extern void GtsWanted_WaitText(void);

// C declares this const, but it lives in .data
// clang-format off
enum GtsAppState (*gGtsTransactionStates[40])(GtsApp *app) = {
    (enum GtsAppState (*)(GtsApp *))GtsTransaction_Start, (enum GtsAppState (*)(GtsApp *))GtsTransaction_Idle,
    (enum GtsAppState (*)(GtsApp *))GtsTransaction_SendPost,
    (enum GtsAppState (*)(GtsApp *))GtsTransaction_WaitPost,
    (enum GtsAppState (*)(GtsApp *))GtsTransaction_SendPostFinish,
    (enum GtsAppState (*)(GtsApp *))GtsTransaction_WaitPostFinish,
    (enum GtsAppState (*)(GtsApp *))GtsTransaction_DepositDone,
    (enum GtsAppState (*)(GtsApp *))GtsTransaction_SendGet,
    (enum GtsAppState (*)(GtsApp *))GtsTransaction_WaitGet,
    (enum GtsAppState (*)(GtsApp *))GtsTransaction_SendReturn,
    (enum GtsAppState (*)(GtsApp *))GtsTransaction_WaitReturn,
    (enum GtsAppState (*)(GtsApp *))GtsTransaction_ReceiveDone,
    (enum GtsAppState (*)(GtsApp *))GtsTransaction_SendExchange,
    (enum GtsAppState (*)(GtsApp *))GtsTransaction_WaitExchange,
    (enum GtsAppState (*)(GtsApp *))GtsTransaction_SendExchangeFinish,
    (enum GtsAppState (*)(GtsApp *))GtsTransaction_WaitExchangeFinish,
    (enum GtsAppState (*)(GtsApp *))GtsTransaction_ExchangeDone,
    (enum GtsAppState (*)(GtsApp *))GtsTransaction_AlreadyTraded,
    (enum GtsAppState (*)(GtsApp *))GtsTransaction_ReceiveTradedMon,
    (enum GtsAppState (*)(GtsApp *))GtsTransaction_SendDelete,
    (enum GtsAppState (*)(GtsApp *))GtsTransaction_WaitDelete,
    (enum GtsAppState (*)(GtsApp *))GtsTransaction_TradedDone,
    (enum GtsAppState (*)(GtsApp *))GtsTransaction_SendUnsavedReturn,
    (enum GtsAppState (*)(GtsApp *))GtsTransaction_WaitUnsavedReturn,
    (enum GtsAppState (*)(GtsApp *))GtsTransaction_SendResult,
    (enum GtsAppState (*)(GtsApp *))GtsTransaction_WaitResult,
    (enum GtsAppState (*)(GtsApp *))GtsTransaction_SendStatusGet,
    (enum GtsAppState (*)(GtsApp *))GtsTransaction_WaitStatusGet,
    (enum GtsAppState (*)(GtsApp *))GtsTransaction_ExitToMainMenu,
    (enum GtsAppState (*)(GtsApp *))GtsTransaction_SaveAndExit,
    (enum GtsAppState (*)(GtsApp *))GtsTransaction_StartSave,
    (enum GtsAppState (*)(GtsApp *))GtsTransaction_WaitSaveDelay,
    (enum GtsAppState (*)(GtsApp *))GtsTransaction_SaveFirstPart,
    (enum GtsAppState (*)(GtsApp *))GtsTransaction_SaveRest,
    (enum GtsAppState (*)(GtsApp *))GtsTransaction_StartSaveWithMessage,
    (enum GtsAppState (*)(GtsApp *))GtsTransaction_SaveWithMessage,
    (enum GtsAppState (*)(GtsApp *))GtsTransaction_FadeOut,
    (enum GtsAppState (*)(GtsApp *))GtsTransaction_WaitText,
    (enum GtsAppState (*)(GtsApp *))GtsTransaction_ServerErrorExit,
    (enum GtsAppState (*)(GtsApp *))GtsTransaction_ServerError,
};
// clang-format on

// C declares this const, but it lives in .data
// clang-format off
enum GtsAppState (*gGtsWantedStates[17])(GtsApp *app) = {
    (enum GtsAppState (*)(GtsApp *))GtsWanted_Start, (enum GtsAppState (*)(GtsApp *))GtsWanted_HandleInput,
    (enum GtsAppState (*)(GtsApp *))GtsWanted_FadeOut,
    (enum GtsAppState (*)(GtsApp *))GtsWanted_OpenSpeciesSelector,
    (enum GtsAppState (*)(GtsApp *))GtsWanted_InvalidState4,
    (enum GtsAppState (*)(GtsApp *))GtsWanted_InvalidState5,
    (enum GtsAppState (*)(GtsApp *))GtsWanted_HandleSpeciesSelector,
    (enum GtsAppState (*)(GtsApp *))GtsWanted_AskGender,
    (enum GtsAppState (*)(GtsApp *))GtsWanted_OpenGenderSelector,
    (enum GtsAppState (*)(GtsApp *))GtsWanted_HandleGenderSelector,
    (enum GtsAppState (*)(GtsApp *))GtsWanted_AskLevel,
    (enum GtsAppState (*)(GtsApp *))GtsWanted_OpenLevelSelector,
    (enum GtsAppState (*)(GtsApp *))GtsWanted_HandleLevelSelector,
    (enum GtsAppState (*)(GtsApp *))GtsWanted_AskConfirm,
    (enum GtsAppState (*)(GtsApp *))GtsWanted_ShowConfirmPrompt,
    (enum GtsAppState (*)(GtsApp *))GtsWanted_HandleConfirmPrompt,
    (enum GtsAppState (*)(GtsApp *))GtsWanted_WaitText,
};
// clang-format on

// C declares this as `const BgTemplate gGtsWantedBg1Template`, but the label holds 32 more bytes of
// data after it.
// clang-format off
const u8 gGtsWantedBg1Template[60] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x01, 0x00, 0x1E, 0x02, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0A, 0x00, 0x06, 0x00,
    0x04, 0x08, 0x00, 0x12, 0x2F, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
};
// clang-format on

// clang-format off
u32 gGtsGenderColors[10] = {
    0x00050600, 0x00030400, 0x0000007C, 2, 0x0000007D, 0, 0x0000007E, 1, 0x0000007F, 0xFFFFFFFE,
};
// clang-format on

// clang-format off
const BgTemplate gGtsWantedBg2Template = {
    0, 0, 0x00000800, 0, 0x01, 0x00, 0x1D, 0x01, 0x00, 0x01, 0x00, 0x00, 0,
};
// clang-format on

// clang-format off
const BgTemplate gGtsWantedBg3Template = {
    0, 0, 0x00000800, 0, 0x01, 0x00, 0x1C, 0x00, 0x00, 0x00, 0x00, 0x00, 0,
};
// clang-format on

// clang-format off
const BgTemplate gGtsWantedBg0Template = {
    0, 0, 0x00000800, 0, 0x01, 0x00, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0,
};
// clang-format on

const GtsWantedWindowPosition gGtsWantedWindowPositions[6] = {
    { 2, 3      },
    { 3, 5      },
    { 3, 7      },
    { 2, 0x000B },
    { 3, 0x000D },
    { 3, 0x000F },
};

// C declares this non-const, but it lives in .rodata
const u32 gGtsGenderSymbolMsgs[4] = { 0x0000007C, 0x0000007D, 0x0000007E, 0x0000007C };

// C declares this non-const, but it lives in .rodata
const int gGtsCountryCount[1] = { 130 };

// C declares this as `volatile GtsServer gGtsServer`, but that type is 0x13c bytes and the label
// covers only 0xc (later labels overlap it).
u8 gGtsServer[12] __attribute__((aligned(4)));
