// Converted from asm/touchscreen_menu_data.s (part 1 of 10) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

#include "global.h"

#pragma force_active on

extern void TouchscreenChoiceMenu_State_CancelYesNo(void);
extern void TouchscreenChoiceMenu_State_Done(void);
extern void TouchscreenChoiceMenu_State_Idle(void);
extern void TouchscreenChoiceMenu_State_Init(void);
extern void TouchscreenChoiceMenu_State_ListEnd(void);
extern void TouchscreenChoiceMenu_State_ListInput(void);
extern void TouchscreenChoiceMenu_State_ListWriteResult(void);
extern void TouchscreenChoiceMenu_State_ShowList(void);
extern void TouchscreenChoiceMenu_State_ShowYesNo(void);
extern void TouchscreenChoiceMenu_State_WaitReturn(void);
extern void TouchscreenChoiceMenu_State_YesNoEnd(void);
extern void TouchscreenChoiceMenu_State_YesNoInput(void);

extern const u8 sTouchscreenChoiceMenu2ItemNeighbors[8];
extern const u8 sTouchscreenChoiceMenu3ItemNeighbors[12];
extern const u8 sTouchscreenChoiceMenu4ItemNeighbors[16];
extern const u8 sTouchscreenChoiceMenu5ItemNeighbors[20];
extern const u8 sTouchscreenChoiceMenu6ItemNeighbors[24];
extern const u8 sTouchscreenChoiceMenu7ItemNeighbors[28];
extern const u8 sTouchscreenChoiceMenu8ItemNeighbors[32];
extern const u8 sTouchscreenChoiceMenu2ItemHitboxes[12];
extern const u8 sTouchscreenChoiceMenu3ItemHitboxes[16];
extern const u8 sTouchscreenChoiceMenu4ItemHitboxes[20];
extern const u8 sTouchscreenChoiceMenu5ItemHitboxes[24];
extern const u8 sTouchscreenChoiceMenu6ItemHitboxes[28];
extern const u8 sTouchscreenChoiceMenu7ItemHitboxes[32];
extern const u8 sTouchscreenChoiceMenu8ItemHitboxes[36];
extern const u8 sTouchscreenChoiceMenu2ItemWindowTemplates[16];
extern const u8 sTouchscreenChoiceMenu3ItemWindowTemplates[24];
extern const u8 sTouchscreenChoiceMenu4ItemWindowTemplates[32];
extern const u8 sTouchscreenChoiceMenu5ItemWindowTemplates[40];
extern const u8 sTouchscreenChoiceMenu6ItemWindowTemplates[48];
extern const u8 sTouchscreenChoiceMenu7ItemWindowTemplates[56];
extern const u8 sTouchscreenChoiceMenu8ItemWindowTemplates[64];

void (*gTouchscreenChoiceMenuStateFuncs[12])(void) = {
    TouchscreenChoiceMenu_State_Init,
    TouchscreenChoiceMenu_State_Idle,
    TouchscreenChoiceMenu_State_WaitReturn,
    TouchscreenChoiceMenu_State_ShowYesNo,
    TouchscreenChoiceMenu_State_YesNoInput,
    TouchscreenChoiceMenu_State_YesNoEnd,
    TouchscreenChoiceMenu_State_Done,
    TouchscreenChoiceMenu_State_ShowList,
    TouchscreenChoiceMenu_State_ListInput,
    TouchscreenChoiceMenu_State_ListEnd,
    TouchscreenChoiceMenu_State_ListWriteResult,
    TouchscreenChoiceMenu_State_CancelYesNo,
};

// clang-format off
const s8 *gTouchscreenChoiceMenuListNeighbors[7] = {
    (const s8 *)sTouchscreenChoiceMenu2ItemNeighbors, (const s8 *)sTouchscreenChoiceMenu3ItemNeighbors,
    (const s8 *)sTouchscreenChoiceMenu4ItemNeighbors, (const s8 *)sTouchscreenChoiceMenu5ItemNeighbors,
    (const s8 *)sTouchscreenChoiceMenu6ItemNeighbors, (const s8 *)sTouchscreenChoiceMenu7ItemNeighbors,
    (const s8 *)sTouchscreenChoiceMenu8ItemNeighbors,
};
// clang-format on

const void *gTouchscreenChoiceMenuListHitboxes[7] = {
    sTouchscreenChoiceMenu2ItemHitboxes,
    sTouchscreenChoiceMenu3ItemHitboxes,
    sTouchscreenChoiceMenu4ItemHitboxes,
    sTouchscreenChoiceMenu5ItemHitboxes,
    sTouchscreenChoiceMenu6ItemHitboxes,
    sTouchscreenChoiceMenu7ItemHitboxes,
    sTouchscreenChoiceMenu8ItemHitboxes,
};

const void *gTouchscreenChoiceMenuListWindowTemplates[7] = {
    sTouchscreenChoiceMenu2ItemWindowTemplates,
    sTouchscreenChoiceMenu3ItemWindowTemplates,
    sTouchscreenChoiceMenu4ItemWindowTemplates,
    sTouchscreenChoiceMenu5ItemWindowTemplates,
    sTouchscreenChoiceMenu6ItemWindowTemplates,
    sTouchscreenChoiceMenu7ItemWindowTemplates,
    sTouchscreenChoiceMenu8ItemWindowTemplates,
};

// clang-format off
const u8 gTouchscreenMenuButtonHitboxes[12] = {
    0x56, 0x86, 0xB8, 0xFC, 0x90, 0xBC, 0xA8, 0xFF, 0xFF, 0x00, 0x00, 0x00,
};
// clang-format on

static const u8 _0225CEBC[8] __attribute__((aligned(4))) = { 0x07, 0x04, 0x02, 0x05, 0x00, 0x00, 0x00, 0x00 };

const u32 gTouchscreenMenuTextColors[2] = { 0x000E070F, 0x00050403 };
