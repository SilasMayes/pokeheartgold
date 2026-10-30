// Converted from asm/palpad_data.s (part 1 of 5) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

// The C declarations of these do not match the data (see the notes at each
// definition): keep them out of the way of the definitions below.
#define gPalPadDetailsPagePrinters   gPalPadDetailsPagePrinters_header_decl
#define gPalPadRosterScrollCallbacks gPalPadRosterScrollCallbacks_header_decl
#define gPalPadRosterNameColors      gPalPadRosterNameColors_header_decl

#include "global.h"

#include "application/palpad/palpad_internal.h"

#pragma force_active on

#undef gPalPadDetailsPagePrinters
#undef gPalPadRosterScrollCallbacks
#undef gPalPadRosterNameColors

// not static: used in another part of asm/palpad_data.s
const PalPadWindowSpec sPalPadDetailsPage2WindowSpecs[4] = {
    { 0x05, 0x05, 0x0B, 0x02 },
    { 0x05, 0x09, 0x1A, 0x05 },
    { 0x0D, 0x00, 0x0C, 0x00 },
    { 0x0A, 0x00, 0x09, 0x00 },
};

// clang-format off
const u8 sPalPadRosterFriendMenuTemplate[16] = {
    0x00, 0x01, 0x0F, 0x00, 0x03, 0x04, 0x01, 0x0F, 0x00, 0x00, 0xC7, 0x00, 0xAC, 0x00, 0x88, 0x00,
};
// clang-format on

// C declares this const, but it lives in .data
// clang-format off
PalPadRosterScrollCallback gPalPadRosterScrollCallbacks[4] = {
    PalPadRoster_DeselectTab, NULL, PalPadRoster_DrawTabsOnScroll, NULL,
};
// clang-format on

// clang-format off
u8 gPalPadRenderSurfaceRect[16] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0xF0, 0x0F, 0x00, 0x00, 0x00, 0x0C, 0x00,
};
// clang-format on

// C declares this const, but it lives in .data
// clang-format off
PalPadDetailsPagePrinter gPalPadDetailsPagePrinters[3] = {
    (PalPadDetailsPagePrinter)PalPadDetails_PrintUnionRoomPage,
    (PalPadDetailsPagePrinter)PalPadDetails_PrintWiFiPlazaPage,
    (PalPadDetailsPagePrinter)PalPadDetails_PrintReturnPage,
};
// clang-format on

const TouchscreenHitbox gPalPadFriendCodeHitboxes[2] = {
    { 0xA0, 0xC0, 0x88, 0xF8 },
    { 0xFF, 0x00, 0x00, 0x00 },
};

// C declares this as `const u32 gPalPadRosterNameColors[3]`, but that type is 0xc bytes and the label
// covers only 0x8 (later labels overlap it).
// clang-format off
const u8 gPalPadRosterNameColors[8] __attribute__((aligned(4))) = {
    0x00, 0x05, 0x06, 0x00, 0x00, 0x03, 0x04, 0x00,
};
// clang-format on

const u16 gPalPadRosterPageBaseTiles[3] = { 1, 0x01BB, 0x01BB };

// not static: used in another part of asm/palpad_data.s
const PalPadWindowSpec sPalPadDetailsPage4WindowSpecs = { 0x02, 0x05, 0x1A, 0x0B };

// not static: used in another part of asm/palpad_data.s
const PalPadWindowSpec sPalPadDetailsPage5WindowSpecs = { 0x02, 0x05, 0x1A, 0x0B };

// not static: used in another part of asm/palpad_data.s
const PalPadWindowSpec sPalPadDetailsPage7WindowSpecs = { 0x01, 0x05, 0x1B, 0x02 };

// not static: used in another part of asm/palpad_data.s
const PalPadWindowSpec sPalPadDetailsPage1WindowSpecs[1] = {
    { 0x02, 0x05, 0x16, 0x0B }
};

// not static: used in another part of asm/palpad_data.s
const PalPadWindowSpec sPalPadDetailsPage6WindowSpecs = { 0x02, 0x05, 0x1A, 0x0B };

// MWCC gives a char array a section of its own, which the linker starts 4-aligned; to stay at
// offset 0x0 next to its neighbours it is written as the only row of a 2-D array, which shares
// their section.
const u8 gPalPadTables[1][3] __attribute__((aligned(4))) = {
    { 0x02, 0x02, 0x09 }
};
