// Converted from asm/pokewalker_data.s (part 1 of 15) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

// The C declarations of these do not match the data (see the notes at each
// definition): keep them out of the way of the definitions below.
#define gPokewalkerRouteImages gPokewalkerRouteImages_header_decl
#define gPokewalkerAppModes    gPokewalkerAppModes_header_decl

#include "global.h"

#include "application/pokewalker/pokewalker_app.h"
#include "application/pokewalker/pokewalker_app_internal.h"
#include "application/pokewalker/pokewalker_event_log.h"
#include "application/pokewalker/pokewalker_ir_internal.h"
#include "application/pokewalker/pokewalker_trainer_house.h"

#pragma force_active on

#undef gPokewalkerRouteImages
#undef gPokewalkerAppModes

extern const u8 sTouchButtons_Back[8];
extern const u8 sPokewalkerRouteImage1[192];
extern const u8 sPokewalkerRouteImage2[192];
extern const u8 sPokewalkerRouteImage3[192];
extern const u8 sPokewalkerRouteImage4[192];
extern const u8 sPokewalkerRouteImage5[192];
extern const u8 sPokewalkerRouteImage6[192];
extern const u8 sPokewalkerRouteImage7[192];
extern const u8 sPokewalkerRouteImage8[192];
extern const TouchscreenHitbox sTouchButtons_TwoChoices[3];
extern const TouchscreenHitbox sTouchButtons_OneChoiceBack[3];
extern const TouchscreenHitbox sTouchButtons_TwoChoicesBack[4];
extern const PokewalkerSpotPixel sSpindaSpot0Pixels[53];
extern const PokewalkerSpotPixel sSpindaSpot1Pixels[53];
extern const PokewalkerSpotPixel sSpindaSpot2Pixels[52];
extern const PokewalkerSpotPixel sSpindaSpot3Pixels[75];

// C declares this const, but it lives in .data
PokewalkerAppModeFuncs gPokewalkerAppModes[11] = {
    {
     (PokewalkerAppStateFunc)PokewalkerApp_MainMenu_Enter,
     (PokewalkerAppStateFunc)PokewalkerApp_MainMenu_Update,
     (PokewalkerAppStateFunc)PokewalkerApp_MainMenu_Exit,
     },
    {
     (PokewalkerAppStateFunc)PokewalkerApp_QuitMessage_Enter,
     (PokewalkerAppStateFunc)PokewalkerApp_QuitMessage_Update,
     (PokewalkerAppStateFunc)PokewalkerApp_QuitMessage_Exit,
     },
    {
     (PokewalkerAppStateFunc)PokewalkerApp_EraseRecords_Enter,
     (PokewalkerAppStateFunc)PokewalkerApp_EraseRecords_Update,
     (PokewalkerAppStateFunc)PokewalkerApp_EraseRecords_Exit,
     },
    {
     (PokewalkerAppStateFunc)PokewalkerApp_Link_Enter,
     (PokewalkerAppStateFunc)PokewalkerApp_Link_Update,
     (PokewalkerAppStateFunc)PokewalkerApp_Link_Exit,
     },
    {
     (PokewalkerAppStateFunc)PokewalkerApp_WaitKeyToSave_Enter,
     (PokewalkerAppStateFunc)PokewalkerApp_WaitKeyToSave_Update,
     (PokewalkerAppStateFunc)PokewalkerApp_WaitKeyToSave_Exit,
     },
    {
     (PokewalkerAppStateFunc)PokewalkerApp_StartStroll_Enter,
     (PokewalkerAppStateFunc)PokewalkerApp_StartStroll_Update,
     (PokewalkerAppStateFunc)PokewalkerApp_StartStroll_Exit,
     },
    {
     (PokewalkerAppStateFunc)PokewalkerApp_LinkSave_Enter,
     (PokewalkerAppStateFunc)PokewalkerApp_LinkSave_Update,
     (PokewalkerAppStateFunc)PokewalkerApp_LinkSave_Exit,
     },
    {
     (PokewalkerAppStateFunc)PokewalkerApp_SelectMon_Enter,
     (PokewalkerAppStateFunc)PokewalkerApp_SelectMon_Update,
     (PokewalkerAppStateFunc)PokewalkerApp_SelectMon_Exit,
     },
    {
     (PokewalkerAppStateFunc)PokewalkerApp_EventLog_Enter,
     (PokewalkerAppStateFunc)PokewalkerApp_EventLog_Update,
     (PokewalkerAppStateFunc)PokewalkerApp_EventLog_Exit,
     },
    {
     (PokewalkerAppStateFunc)PokewalkerApp_WaitKey_Enter,
     (PokewalkerAppStateFunc)PokewalkerApp_WaitKey_Update,
     (PokewalkerAppStateFunc)PokewalkerApp_WaitKey_Exit,
     },
    {
     (PokewalkerAppStateFunc)PokewalkerApp_StrollReport_Enter,
     (PokewalkerAppStateFunc)PokewalkerApp_StrollReport_Update,
     (PokewalkerAppStateFunc)PokewalkerApp_StrollReport_Exit,
     },
};

// clang-format off
const GraphicsBanks gPokewalkerAppGraphicsBanks = {
    GX_VRAM_BG_128_B, GX_VRAM_BGEXTPLTT_NONE, GX_VRAM_SUB_BG_128_C, GX_VRAM_SUB_BGEXTPLTT_NONE,
    GX_VRAM_OBJ_64_E, GX_VRAM_OBJEXTPLTT_NONE, GX_VRAM_SUB_OBJ_16_I, GX_VRAM_SUB_OBJEXTPLTT_NONE,
    GX_VRAM_TEX_0_A, GX_VRAM_TEXPLTT_0_F,
};
// clang-format on

static const TouchscreenHitbox sTouchButtons_CourseList[9] = {
    { 0x00, 0x1F, 0x0B, 0xEF },
    { 0x20, 0x3F, 0x0B, 0xEF },
    { 0x40, 0x5F, 0x0B, 0xEF },
    { 0x60, 0x7F, 0x0B, 0xEF },
    { 0x80, 0x9F, 0x0B, 0xEF },
    { 0xA0, 0xBF, 0xC0, 0xFF },
    { 0xA2, 0xBF, 0x0C, 0x23 },
    { 0xA2, 0xBF, 0x24, 0x41 },
    { 0xFF, 0x00, 0x00, 0x00 },
};

// C declares this const, but it lives in .data
// clang-format off
const u8 *gPokewalkerRouteImages[9] = {
    sTouchButtons_Back, sPokewalkerRouteImage1, sPokewalkerRouteImage2,
    sPokewalkerRouteImage3, sPokewalkerRouteImage4, sPokewalkerRouteImage5,
    sPokewalkerRouteImage6, sPokewalkerRouteImage7, sPokewalkerRouteImage8,
};
// clang-format on

static const TouchscreenHitbox sTouchButtons_ThreeChoicesBack[5] = {
    { 0x0B, 0x34, 0x0B, 0xEF },
    { 0x35, 0x5B, 0x0B, 0xEF },
    { 0x5C, 0x84, 0x0B, 0xEF },
    { 0xA0, 0xBF, 0xC0, 0xFF },
    { 0xFF, 0x00, 0x00, 0x00 },
};

// clang-format off
const TouchscreenHitbox *gTouchButtons[5] = {
    sTouchButtons_TwoChoices, sTouchButtons_OneChoiceBack,
    sTouchButtons_TwoChoicesBack, sTouchButtons_ThreeChoicesBack,
    sTouchButtons_CourseList,
};
// clang-format on

// clang-format off
const PokewalkerSpotPixel *gSpindaSpotPixels[4] = {
    sSpindaSpot0Pixels, sSpindaSpot1Pixels, sSpindaSpot2Pixels,
    sSpindaSpot3Pixels,
};
// clang-format on

// not static: used above its definition
const TouchscreenHitbox sTouchButtons_TwoChoicesBack[4] = {
    { 0x25, 0x4C, 0x0D, 0xEF },
    { 0x4D, 0x73, 0x0D, 0xEF },
    { 0xA0, 0xBF, 0xC0, 0xFF },
    { 0xFF, 0x00, 0x00, 0x00 },
};

// clang-format off
const GraphicsModes gPokewalkerAppGraphicsModes = {
    GX_DISPMODE_GRAPHICS, GX_BGMODE_0, GX_BGMODE_0, GX_BG0_AS_3D,
};
// clang-format on

// not static: used above its definition
const TouchscreenHitbox sTouchButtons_TwoChoices[3] = {
    { 0x25, 0x4C, 0x0D, 0xEF },
    { 0x4D, 0x73, 0x0D, 0xEF },
    { 0xFF, 0x00, 0x00, 0x00 },
};

// not static: used above its definition
const TouchscreenHitbox sTouchButtons_OneChoiceBack[3] = {
    { 0x3C, 0x64, 0x0C, 0xEF },
    { 0xA0, 0xBF, 0xC0, 0xFF },
    { 0xFF, 0x00, 0x00, 0x00 },
};

// global: C declares it extern although the asm label was local
// clang-format off
const u8 sTouchButtons_Back[8] __attribute__((aligned(4))) = {
    0xA0, 0xBF, 0xC0, 0xFF, 0xFF, 0x00, 0x00, 0x00,
};
// clang-format on

u8 gPokewalkerIrLinkArgs[4] __attribute__((aligned(4))) = { 0xFF, 0xFF, 0x00, 0x00 };

OSThread sPokewalkerIrThread;
