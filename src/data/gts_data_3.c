// Converted from asm/gts_data.s (part 3 of 7) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

// The C declarations of these do not match the data (see the notes at each
// definition): keep them out of the way of the definitions below.
#define gGtsConnectionStates gGtsConnectionStates_header_decl
#define gGtsServerPending    gGtsServerPending_header_decl

#include "global.h"

#include "constants/pokemon.h"

#include "gts/gts_internal.h"

#pragma force_active on

#undef gGtsConnectionStates
#undef gGtsServerPending

extern void GtsConnection_AskConnect(void);
extern void GtsConnection_AskDisconnect(void);
extern void GtsConnection_Disconnect(void);
extern void GtsConnection_DisconnectAfterError(void);
extern void GtsConnection_FadeOut(void);
extern void GtsConnection_HandleConnectPrompt(void);
extern void GtsConnection_HandleDisconnectMenu(void);
extern void GtsConnection_HandleExitPrompt(void);
extern void GtsConnection_InitServer(void);
extern void GtsConnection_PrintDisconnected(void);
extern void GtsConnection_PrintDisconnecting(void);
extern void GtsConnection_PrintServerError(void);
extern void GtsConnection_SendInfo(void);
extern void GtsConnection_SendSetProfile(void);
extern void GtsConnection_ShowConnectionError(void);
extern void GtsConnection_StartAuth(void);
extern void GtsConnection_StartConnect(void);
extern void GtsConnection_WaitAuth(void);
extern void GtsConnection_WaitCloseError(void);
extern void GtsConnection_WaitConnect(void);
extern void GtsConnection_WaitInfo(void);
extern void GtsConnection_WaitSetProfile(void);
extern void GtsConnection_WaitText(void);
extern void GtsConnection_WaitTextAndDelay(void);
extern void GtsConnection_WaitTextAndShowYesNo(void);

// C declares this const, but it lives in .data
// clang-format off
enum GtsAppState (*gGtsConnectionStates[25])(GtsApp *app) = {
    (enum GtsAppState (*)(GtsApp *))GtsConnection_AskConnect,
    (enum GtsAppState (*)(GtsApp *))GtsConnection_HandleConnectPrompt,
    (enum GtsAppState (*)(GtsApp *))GtsConnection_StartConnect,
    (enum GtsAppState (*)(GtsApp *))GtsConnection_WaitConnect,
    (enum GtsAppState (*)(GtsApp *))GtsConnection_StartAuth,
    (enum GtsAppState (*)(GtsApp *))GtsConnection_WaitAuth,
    (enum GtsAppState (*)(GtsApp *))GtsConnection_InitServer,
    (enum GtsAppState (*)(GtsApp *))GtsConnection_SendInfo,
    (enum GtsAppState (*)(GtsApp *))GtsConnection_WaitInfo,
    (enum GtsAppState (*)(GtsApp *))GtsConnection_SendSetProfile,
    (enum GtsAppState (*)(GtsApp *))GtsConnection_WaitSetProfile,
    (enum GtsAppState (*)(GtsApp *))GtsConnection_FadeOut,
    (enum GtsAppState (*)(GtsApp *))GtsConnection_WaitText,
    (enum GtsAppState (*)(GtsApp *))GtsConnection_WaitTextAndShowYesNo,
    (enum GtsAppState (*)(GtsApp *))GtsConnection_HandleExitPrompt,
    (enum GtsAppState (*)(GtsApp *))GtsConnection_AskDisconnect,
    (enum GtsAppState (*)(GtsApp *))GtsConnection_HandleDisconnectMenu,
    (enum GtsAppState (*)(GtsApp *))GtsConnection_PrintDisconnecting,
    (enum GtsAppState (*)(GtsApp *))GtsConnection_Disconnect,
    (enum GtsAppState (*)(GtsApp *))GtsConnection_PrintDisconnected,
    (enum GtsAppState (*)(GtsApp *))GtsConnection_WaitTextAndDelay,
    (enum GtsAppState (*)(GtsApp *))GtsConnection_PrintServerError,
    (enum GtsAppState (*)(GtsApp *))GtsConnection_DisconnectAfterError,
    (enum GtsAppState (*)(GtsApp *))GtsConnection_ShowConnectionError,
    (enum GtsAppState (*)(GtsApp *))GtsConnection_WaitCloseError,
};
// clang-format on

// clang-format off
const BgTemplate gGtsTransactionBg2Template = {
    0, 0, 0x00000800, 0, 0x01, 0x00, 0x1D, 0x02, 0x00, 0x01, 0x00, 0x00, 0,
};
// clang-format on

// clang-format off
const BgTemplate gGtsTransactionSubBg0Template = {
    0, 0, 0x00000800, 0, 0x01, 0x00, 0x1E, 0x04, 0x00, 0x00, 0x00, 0x00, 0,
};
// clang-format on

// clang-format off
const BgTemplate gGtsTransactionBg0Template = {
    0, 0, 0x00000800, 0, 0x01, 0x00, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0,
};
// clang-format on

// clang-format off
const BgTemplate gGtsTransactionBg1Template = {
    0, 0, 0x00000800, 0, 0x01, 0x00, 0x1E, 0x02, 0x00, 0x01, 0x00, 0x00, 0,
};
// clang-format on

// clang-format off
const BgTemplate gGtsTransactionSubBg1Template = {
    0, 0, 0x00000800, 0, 0x01, 0x01, 0x1C, 0x00, 0x00, 0x02, 0x00, 0x00, 0,
};
// clang-format on

// clang-format off
const GraphicsModes gGtsTransactionGraphicsModes = {
    GX_DISPMODE_GRAPHICS, GX_BGMODE_0, GX_BGMODE_0, GX_BG0_AS_2D,
};
// clang-format on

// C declares this as `GtsServerPending gGtsServerPending`, but that type is 0x44 bytes and the label
// covers only 0x20 (later labels overlap it).
u8 gGtsServerPending[32];
