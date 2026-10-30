// Converted from asm/nintendo_wfc_connect_data.s (part 4 of 5) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

// The C declarations of these do not match the data (see the notes at each
// definition): keep them out of the way of the definitions below.
#define gNintendoWfcNumberInputStates  gNintendoWfcNumberInputStates_header_decl
#define gNintendoWfcPadHitboxes_Max100 gNintendoWfcPadHitboxes_Max100_header_decl
#define gNintendoWfcPadHitboxes        gNintendoWfcPadHitboxes_header_decl
#define gNintendoWfcHttpResponse       gNintendoWfcHttpResponse_header_decl
#define gNintendoWfcHttpShortResponse  gNintendoWfcHttpShortResponse_header_decl

#include "global.h"

#include "nintendo_wfc_connect_internal.h"

#pragma force_active on

#undef gNintendoWfcNumberInputStates
#undef gNintendoWfcPadHitboxes_Max100
#undef gNintendoWfcPadHitboxes
#undef gNintendoWfcHttpResponse
#undef gNintendoWfcHttpShortResponse

// C declares this const, but it lives in .data
TouchscreenHitbox gNintendoWfcPadHitboxes[17] = {
    { 0x0E, 0x2F, 0x48, 0x67 },
    { 0x0E, 0x2F, 0x68, 0x87 },
    { 0x0E, 0x2F, 0x88, 0xA7 },
    { 0x3C, 0x63, 0x0C, 0x33 },
    { 0x3C, 0x63, 0x3C, 0x63 },
    { 0x3C, 0x63, 0x6C, 0x93 },
    { 0x3C, 0x63, 0x9E, 0xC3 },
    { 0x3C, 0x63, 0xCC, 0xF3 },
    { 0x6C, 0x93, 0x0C, 0x33 },
    { 0x6C, 0x93, 0x3C, 0x63 },
    { 0x6C, 0x93, 0x6C, 0x93 },
    { 0x6C, 0x93, 0x9E, 0xC3 },
    { 0x6C, 0x93, 0xCC, 0xF3 },
    { 0xA4, 0xBB, 0x04, 0x4B },
    { 0xA4, 0xBB, 0x5C, 0xA3 },
    { 0xA4, 0xBB, 0xB4, 0xFB },
    { 0xFF, 0x00, 0x00, 0x00 },
};

// C declares this const, but it lives in .data
TouchscreenHitbox gNintendoWfcPadHitboxes_Max100[17] = {
    { 0x0E, 0x2F, 0x58, 0x77 },
    { 0x0E, 0x2F, 0x78, 0x97 },
    { 0x0E, 0x2F, 0x98, 0xB7 },
    { 0x3C, 0x63, 0x0C, 0x33 },
    { 0x3C, 0x63, 0x3C, 0x63 },
    { 0x3C, 0x63, 0x6C, 0x93 },
    { 0x3C, 0x63, 0x9E, 0xC3 },
    { 0x3C, 0x63, 0xCC, 0xF3 },
    { 0x6C, 0x93, 0x0C, 0x33 },
    { 0x6C, 0x93, 0x3C, 0x63 },
    { 0x6C, 0x93, 0x6C, 0x93 },
    { 0x6C, 0x93, 0x9E, 0xC3 },
    { 0x6C, 0x93, 0xCC, 0xF3 },
    { 0xA4, 0xBB, 0x04, 0x4B },
    { 0xA4, 0xBB, 0x5C, 0xA3 },
    { 0xA4, 0xBB, 0xB4, 0xFB },
    { 0xFF, 0x00, 0x00, 0x00 },
};

// C declares this const, but it lives in .data
// clang-format off
BOOL (*gNintendoWfcNumberInputStates[12])(NintendoWfcConnect *wfc) = {
    (BOOL (*)(NintendoWfcConnect *))NintendoWfc_NumberInput_FadeOut,
    (BOOL (*)(NintendoWfcConnect *))NintendoWfc_NumberInput_Setup,
    (BOOL (*)(NintendoWfcConnect *))NintendoWfc_NumberInput_WaitFadeIn,
    (BOOL (*)(NintendoWfcConnect *))NintendoWfc_NumberInput_Main,
    (BOOL (*)(NintendoWfcConnect *))NintendoWfc_NumberInput_UnusedState4,
    (BOOL (*)(NintendoWfcConnect *))NintendoWfc_NumberInput_UnusedState5,
    (BOOL (*)(NintendoWfcConnect *))NintendoWfc_NumberInput_UnusedState6,
    (BOOL (*)(NintendoWfcConnect *))NintendoWfc_NumberInput_StartFadeOut,
    (BOOL (*)(NintendoWfcConnect *))NintendoWfc_NumberInput_Teardown,
    (BOOL (*)(NintendoWfcConnect *))NintendoWfc_NumberInput_WaitFadeOut,
    (BOOL (*)(NintendoWfcConnect *))NintendoWfc_NumberInput_WaitButtonFlash,
    (BOOL (*)(NintendoWfcConnect *))NintendoWfc_NumberInput_Finish,
};
// clang-format on

const TouchscreenHitbox gNintendoWfcYesNoHitboxes[3] = {
    { 0x32, 0x5C, 0x03, 0xFB },
    { 0x63, 0x8C, 0x03, 0xFB },
    { 0xFF, 0x00, 0x00, 0x00 },
};

const NintendoWfcCursorPos gNintendoWfcYesNoCursorPositions[2] = {
    { 0x0080, 0x0048 },
    { 0x0080, 0x0078 }
};

// C declares this as `NintendoWfcHttpResponse gNintendoWfcHttpResponse`, but MWCC gives a char array a
// section of its own, which the linker starts 4-aligned; to stay at offset 0x100 next to its
// neighbours it is written as the only row of a 2-D array, which shares their section.
u8 gNintendoWfcHttpResponse[1][3];

// C declares this as `u8 gNintendoWfcHttpShortResponse[]`, but MWCC gives a char array a section of
// its own, which the linker starts 4-aligned; to stay at offset 0x103 next to its neighbours it is
// written as the only row of a 2-D array, which shares their section.
u8 gNintendoWfcHttpShortResponse[1][9];

NintendoWfcGlobal gNintendoWfcGlobal;
