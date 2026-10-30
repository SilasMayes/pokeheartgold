// Converted from asm/pokewalker_data.s (part 4 of 15) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

// The C declarations of these do not match the data (see the notes at each
// definition): keep them out of the way of the definitions below.
#define gStartStrollStates  gStartStrollStates_header_decl
#define gLinkSaveStates     gLinkSaveStates_header_decl
#define gStrollReportStates gStrollReportStates_header_decl

#include "global.h"

#include "application/pokewalker/pokewalker_app.h"
#include "application/pokewalker/pokewalker_app_internal.h"
#include "application/pokewalker/pokewalker_event_log.h"
#include "application/pokewalker/pokewalker_ir_internal.h"
#include "application/pokewalker/pokewalker_trainer_house.h"

#pragma force_active on

#undef gStartStrollStates
#undef gLinkSaveStates
#undef gStrollReportStates

// C declares this const, but it lives in .data
// clang-format off
PokewalkerAppStateFunc gStrollReportStates[37] = {
    PokewalkerApp_StrollReport_Start, PokewalkerApp_StrollReport_ShowResults,
    PokewalkerApp_StrollReport_WaitResultsFade, PokewalkerApp_StrollReport_PrintMonArrived,
    PokewalkerApp_StrollReport_PrintLevelUp, PokewalkerApp_StrollReport_PrintWatts,
    PokewalkerApp_StrollReport_PrintRouteFound, PokewalkerApp_StrollReport_PrintRouteAvailable,
    PokewalkerApp_StrollReport_PrintMilestone, PokewalkerApp_StrollReport_PrintStarfBerry,
    PokewalkerApp_StrollReport_FadeOut, PokewalkerApp_StrollReport_WaitFadeOut,
    PokewalkerApp_StrollReport_ShowCaughtMons, PokewalkerApp_StrollReport_WaitCaughtMonsFade,
    PokewalkerApp_StrollReport_PrintMonsSent, PokewalkerApp_StrollReport_CaughtMonsFadeOut,
    PokewalkerApp_StrollReport_WaitCaughtMonsFadeOut, PokewalkerApp_StrollReport_ShowItems,
    PokewalkerApp_StrollReport_WaitItemsFade, PokewalkerApp_StrollReport_PrintItemsPlaced,
    PokewalkerApp_StrollReport_ItemsFadeOut, PokewalkerApp_StrollReport_WaitItemsFadeOut,
    PokewalkerApp_StrollReport_GiftsFadeOut, PokewalkerApp_StrollReport_WaitGiftsFadeOut,
    PokewalkerApp_StrollReport_ShowGifts, PokewalkerApp_StrollReport_WaitGiftsFade,
    PokewalkerApp_StrollReport_PrintGiftWatts, PokewalkerApp_StrollReport_PrintGiftRouteFound,
    PokewalkerApp_StrollReport_GiftsDoneFadeOut, PokewalkerApp_StrollReport_WaitGiftsDoneFadeOut,
    PokewalkerApp_StrollReport_RecordsFadeOut, PokewalkerApp_StrollReport_WaitRecordsFadeOut,
    PokewalkerApp_StrollReport_ShowRecords, PokewalkerApp_StrollReport_WaitRecordsFade,
    PokewalkerApp_StrollReport_PrintRecords, PokewalkerApp_StrollReport_WaitMessage,
    PokewalkerApp_StrollReport_End,
};
// clang-format on

// C declares this const, but it lives in .data
// clang-format off
PokewalkerAppStateFunc gLinkSaveStates[11] = {
    PokewalkerApp_LinkSave_PrintSaving, PokewalkerApp_LinkSave_WaitSaving, PokewalkerApp_LinkSave_Save,
    PokewalkerApp_LinkSave_EndSave, PokewalkerApp_LinkSave_SetNextMode, PokewalkerApp_LinkSave_PrintSaving2,
    PokewalkerApp_LinkSave_WaitSaving2, PokewalkerApp_LinkSave_Save2, PokewalkerApp_LinkSave_EndSave2,
    PokewalkerApp_LinkSave_GoToStrollReport, PokewalkerApp_LinkSave_End,
};
// clang-format on

// C declares this const, but it lives in .data
// clang-format off
PokewalkerAppStateFunc gStartStrollStates[8] = {
    PokewalkerApp_StartStroll_PrintSaving, PokewalkerApp_StartStroll_WaitSaving,
    PokewalkerApp_StartStroll_Save, PokewalkerApp_StartStroll_EndSave,
    PokewalkerApp_StartStroll_CheckFirstStroll, PokewalkerApp_StartStroll_PrintRegistered,
    PokewalkerApp_StartStroll_WaitRegistered, PokewalkerApp_StartStroll_End,
};
// clang-format on

// clang-format off
const u8 gPokewalkerAppSpritePalettes[16] = {
    0x01, 0x00, 0x00, 0x00, 0x00, 0x02, 0x03, 0x01, 0x04, 0x05, 0x05, 0x05, 0x05, 0x00, 0x00, 0x00,
};
// clang-format on

// not static: used in another part of asm/pokewalker_data.s
const WindowTemplate sWindowBank0Template6 = { 0x04, 0x01, 0x10, 0x0C, 0x02, 0x01, 0x0110 };

// not static: used in another part of asm/pokewalker_data.s
const WindowTemplate sWindowBank5Template2 = { 0x01, 0x01, 0x04, 0x0F, 0x02, 0x01, 0x00BC };

// not static: used in another part of asm/pokewalker_data.s
const WindowTemplate sWindowBank1Template0 = { 0x01, 0x02, 0x13, 0x13, 0x04, 0x0E, 0x0014 };

// not static: used in another part of asm/pokewalker_data.s
const WindowTemplate sWindowBank1Template1 = { 0x01, 0x19, 0x15, 0x06, 0x02, 0x0E, 0x0060 };

// not static: used in another part of asm/pokewalker_data.s
const WindowTemplate sWindowBank1Template2 = { 0x01, 0x02, 0x13, 0x1B, 0x04, 0x0E, 0x006C };

// not static: used in another part of asm/pokewalker_data.s
const WindowTemplate sWindowBank1Template3 = { 0x01, 0x03, 0x06, 0x1A, 0x03, 0x0E, 0x00D8 };

// not static: used in another part of asm/pokewalker_data.s
const WindowTemplate sWindowBank1Template4 = { 0x01, 0x03, 0x0B, 0x1A, 0x03, 0x0E, 0x0126 };

// not static: used in another part of asm/pokewalker_data.s
const WindowTemplate sWindowBank1Template5 = { 0x01, 0x03, 0x09, 0x1A, 0x03, 0x0E, 0x0174 };

// not static: used in another part of asm/pokewalker_data.s
const WindowTemplate sWindowBank5Template5 = { 0x01, 0x08, 0x0C, 0x08, 0x02, 0x01, 0x00FA };

// not static: used in another part of asm/pokewalker_data.s
const WindowTemplate sWindowBank2Template0 = { 0x04, 0x03, 0x03, 0x1A, 0x03, 0x01, 0x0014 };

// not static: used in another part of asm/pokewalker_data.s
const WindowTemplate sWindowBank2Template1 = { 0x04, 0x05, 0x0C, 0x16, 0x06, 0x01, 0x0062 };

// not static: used in another part of asm/pokewalker_data.s
const WindowTemplate sWindowBank3Template0 = { 0x01, 0x04, 0x01, 0x18, 0x02, 0x0E, 0x0014 };

// not static: used in another part of asm/pokewalker_data.s
const WindowTemplate sWindowBank3Template1 = { 0x01, 0x04, 0x05, 0x18, 0x02, 0x0E, 0x0044 };

// not static: used in another part of asm/pokewalker_data.s
const WindowTemplate sWindowBank3Template2 = { 0x01, 0x04, 0x09, 0x18, 0x02, 0x0E, 0x0074 };

// not static: used in another part of asm/pokewalker_data.s
const WindowTemplate sWindowBank3Template3 = { 0x01, 0x04, 0x0D, 0x18, 0x02, 0x0E, 0x00A4 };

// not static: used in another part of asm/pokewalker_data.s
const WindowTemplate sWindowBank3Template4 = { 0x01, 0x04, 0x11, 0x18, 0x02, 0x0E, 0x00D4 };

// not static: used in another part of asm/pokewalker_data.s
const WindowTemplate sWindowBank3Template5 = { 0x01, 0x10, 0x15, 0x07, 0x02, 0x0E, 0x0104 };

// not static: used in another part of asm/pokewalker_data.s
const WindowTemplate sWindowBank3Template6 = { 0x01, 0x19, 0x15, 0x06, 0x02, 0x0E, 0x0112 };

// not static: used in another part of asm/pokewalker_data.s
const WindowTemplate sWindowBank3Template7 = { 0x01, 0x09, 0x15, 0x06, 0x02, 0x0E, 0x011E };

// not static: used in another part of asm/pokewalker_data.s
const WindowTemplate sWindowBank6Template3 = { 0x01, 0x10, 0x04, 0x0C, 0x02, 0x01, 0x00D4 };

// not static: used in another part of asm/pokewalker_data.s
const WindowTemplate sWindowBank4Template0 = { 0x01, 0x02, 0x13, 0x1B, 0x04, 0x0E, 0x0014 };

// not static: used in another part of asm/pokewalker_data.s
const WindowTemplate sWindowBank4Template1 = { 0x01, 0x02, 0x01, 0x1E, 0x02, 0x01, 0x0080 };

// not static: used in another part of asm/pokewalker_data.s
const WindowTemplate sWindowBank4Template2 = { 0x01, 0x02, 0x04, 0x12, 0x02, 0x01, 0x00BC };

// not static: used in another part of asm/pokewalker_data.s
const WindowTemplate sWindowBank4Template3 = { 0x01, 0x03, 0x06, 0x11, 0x02, 0x01, 0x00E0 };

// not static: used in another part of asm/pokewalker_data.s
const WindowTemplate sWindowBank4Template4 = { 0x01, 0x03, 0x08, 0x11, 0x02, 0x01, 0x0102 };

// not static: used in another part of asm/pokewalker_data.s
const WindowTemplate sWindowBank4Template5 = { 0x01, 0x02, 0x0A, 0x16, 0x02, 0x01, 0x0124 };

// not static: used in another part of asm/pokewalker_data.s
const WindowTemplate sWindowBank4Template6 = { 0x01, 0x15, 0x0C, 0x0A, 0x02, 0x01, 0x0150 };

// not static: used in another part of asm/pokewalker_data.s
const WindowTemplate sWindowBank4Template7 = { 0x01, 0x02, 0x0E, 0x16, 0x02, 0x01, 0x0164 };

// not static: used in another part of asm/pokewalker_data.s
const WindowTemplate sWindowBank4Template8 = { 0x01, 0x15, 0x10, 0x0A, 0x02, 0x01, 0x0190 };

// not static: used in another part of asm/pokewalker_data.s
const WindowTemplate sWindowBank0Template1 = { 0x04, 0x11, 0x03, 0x0C, 0x02, 0x01, 0x008C };

// not static: used in another part of asm/pokewalker_data.s
const WindowTemplate sWindowBank0Template4 = { 0x04, 0x14, 0x0B, 0x09, 0x02, 0x01, 0x00CE };

const u8 gWindowBankScreens[8] = { 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00 };

// not static: used in another part of asm/pokewalker_data.s
const WindowTemplate sWindowBank6Template10 = { 0x01, 0x02, 0x0C, 0x0C, 0x02, 0x01, 0x017C };

// not static: used in another part of asm/pokewalker_data.s
const WindowTemplate sWindowBank5Template3 = { 0x01, 0x08, 0x08, 0x08, 0x02, 0x01, 0x00DA };

// not static: used in another part of asm/pokewalker_data.s
const WindowTemplate sWindowBank5Template4 = { 0x01, 0x15, 0x08, 0x08, 0x02, 0x01, 0x00EA };

// not static: used in another part of asm/pokewalker_data.s
const WindowTemplate sWindowBank6Template11 = { 0x01, 0x10, 0x0C, 0x0C, 0x02, 0x01, 0x0194 };

// not static: used in another part of asm/pokewalker_data.s
const WindowTemplate sWindowBank5Template6 = { 0x01, 0x15, 0x0C, 0x08, 0x02, 0x01, 0x010A };

// not static: used in another part of asm/pokewalker_data.s
const WindowTemplate sWindowBank6Template12 = { 0x01, 0x02, 0x0E, 0x0C, 0x02, 0x01, 0x01AC };

// not static: used in another part of asm/pokewalker_data.s
const WindowTemplate sWindowBank6Template0 = { 0x01, 0x02, 0x13, 0x1B, 0x04, 0x0E, 0x0014 };

// not static: used in another part of asm/pokewalker_data.s
const WindowTemplate sWindowBank6Template1 = { 0x01, 0x02, 0x01, 0x1E, 0x02, 0x0E, 0x0080 };

// not static: used in another part of asm/pokewalker_data.s
const WindowTemplate sWindowBank6Template2 = { 0x01, 0x02, 0x04, 0x0C, 0x02, 0x01, 0x00BC };

// not static: used in another part of asm/pokewalker_data.s
const WindowTemplate sWindowBank6Template14 = { 0x01, 0x02, 0x10, 0x0C, 0x02, 0x01, 0x01DC };

// not static: used in another part of asm/pokewalker_data.s
const WindowTemplate sWindowBank6Template4 = { 0x01, 0x02, 0x06, 0x0C, 0x02, 0x01, 0x00EC };

// not static: used in another part of asm/pokewalker_data.s
const WindowTemplate sWindowBank6Template5 = { 0x01, 0x10, 0x06, 0x0C, 0x02, 0x01, 0x0104 };

// not static: used in another part of asm/pokewalker_data.s
const WindowTemplate sWindowBank6Template6 = { 0x01, 0x02, 0x08, 0x0C, 0x02, 0x01, 0x011C };

// not static: used in another part of asm/pokewalker_data.s
const WindowTemplate sWindowBank6Template7 = { 0x01, 0x10, 0x08, 0x0C, 0x02, 0x01, 0x0134 };

// not static: used in another part of asm/pokewalker_data.s
const WindowTemplate sWindowBank6Template8 = { 0x01, 0x02, 0x0A, 0x0C, 0x02, 0x01, 0x014C };

// not static: used in another part of asm/pokewalker_data.s
const WindowTemplate sWindowBank5Template1 = { 0x01, 0x02, 0x01, 0x1E, 0x02, 0x01, 0x0080 };

// not static: used in another part of asm/pokewalker_data.s
const WindowTemplate sWindowBank7Template1 = { 0x01, 0x19, 0x15, 0x06, 0x02, 0x0E, 0x0060 };

// not static: used in another part of asm/pokewalker_data.s
const WindowTemplate sWindowBank0Template2 = { 0x04, 0x14, 0x05, 0x09, 0x02, 0x01, 0x00A4 };

// not static: used in another part of asm/pokewalker_data.s
const WindowTemplate sWindowBank7Template2 = { 0x01, 0x02, 0x13, 0x1B, 0x04, 0x0E, 0x006C };

// not static: used in another part of asm/pokewalker_data.s
const WindowTemplate sWindowBank6Template13 = { 0x01, 0x10, 0x0E, 0x0C, 0x02, 0x01, 0x01C4 };

// not static: used in another part of asm/pokewalker_data.s
const WindowTemplate sWindowBank7Template3 = { 0x01, 0x03, 0x03, 0x1A, 0x02, 0x00, 0x00D8 };

// not static: used in another part of asm/pokewalker_data.s
const WindowTemplate sWindowBank6Template15 = { 0x01, 0x10, 0x10, 0x0C, 0x02, 0x01, 0x01F4 };

// not static: used in another part of asm/pokewalker_data.s
const WindowTemplate sWindowBank0Template5 = { 0x04, 0x03, 0x0C, 0x0C, 0x04, 0x01, 0x00E0 };

// not static: used in another part of asm/pokewalker_data.s
const WindowTemplate sWindowBank6Template9 = { 0x01, 0x10, 0x0A, 0x0C, 0x02, 0x01, 0x0164 };

// not static: used in another part of asm/pokewalker_data.s
const WindowTemplate sWindowBank7Template5 = { 0x01, 0x03, 0x08, 0x1A, 0x02, 0x00, 0x0140 };

// not static: used in another part of asm/pokewalker_data.s
const WindowTemplate sWindowBank0Template0 = { 0x04, 0x01, 0x13, 0x1E, 0x04, 0x01, 0x0014 };

// not static: used in another part of asm/pokewalker_data.s
const WindowTemplate sWindowBank5Template0 = { 0x01, 0x02, 0x13, 0x1B, 0x04, 0x0E, 0x0014 };

// not static: used in another part of asm/pokewalker_data.s
const WindowTemplate sWindowBank0Template3 = { 0x04, 0x11, 0x09, 0x0C, 0x02, 0x01, 0x00B6 };

// not static: used in another part of asm/pokewalker_data.s
const WindowTemplate sWindowBank7Template0 = { 0x01, 0x02, 0x13, 0x13, 0x04, 0x0E, 0x0014 };

// not static: used in another part of asm/pokewalker_data.s
const WindowTemplate sWindowBank7Template4 = { 0x01, 0x03, 0x0D, 0x1A, 0x02, 0x00, 0x010C };
