// Converted from asm/nintendo_wfc_connect_data.s (part 2 of 5) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

// The C declarations of these do not match the data (see the notes at each
// definition): keep them out of the way of the definitions below.
#define gNintendoWfcInfoUrl       gNintendoWfcInfoUrl_header_decl
#define gNintendoWfcSetProfileUrl gNintendoWfcSetProfileUrl_header_decl

#include "global.h"

#include "nintendo_wfc_connect_internal.h"

#pragma force_active on

#undef gNintendoWfcInfoUrl
#undef gNintendoWfcSetProfileUrl

// C declares this const, but it lives in .data
char gNintendoWfcInfoUrl[72] = "http://gamestats2.gs.nintendowifi.net/pokemondpds/battletower/info.asp";

// C declares this const, but it lives in .data
char gNintendoWfcSetProfileUrl[72] = "http://gamestats2.gs.nintendowifi.net/pokemondpds/common/setProfile.asp";

// clang-format off
const BgTemplate gNintendoWfcBgTemplate_Sub0 = {
    0, 0, 0x00000800, 0, 0x01, 0x00, 0x1E, 0x04, 0x00, 0x00, 0x00, 0x00, 0,
};
// clang-format on

// clang-format off
const BgTemplate gNintendoWfcBgTemplate_Main0 = {
    0, 0, 0x00000800, 0, 0x01, 0x00, 0x1F, 0x00, 0x00, 0x00, 0x00, 0x00, 0,
};
// clang-format on

// clang-format off
const BgTemplate gNintendoWfcBgTemplate_Main1 = {
    0, 0, 0x00000800, 0, 0x01, 0x00, 0x1E, 0x02, 0x00, 0x01, 0x00, 0x00, 0,
};
// clang-format on

// clang-format off
const BgTemplate gNintendoWfcBgTemplate_Sub2 = {
    0, 0, 0x00000800, 0, 0x01, 0x00, 0x1F, 0x01, 0x00, 0x01, 0x00, 0x00, 0,
};
// clang-format on

// clang-format off
const BgTemplate gNintendoWfcBgTemplate_Sub1 = {
    0, 0, 0x00000800, 0, 0x01, 0x00, 0x1B, 0x02, 0x00, 0x02, 0x00, 0x00, 0,
};
// clang-format on

#ifndef SDK_PORT // parts of gNintendoWfcHttp on the port (nintendo_wfc_connect_internal.h)
u8 gNintendoWfcHttpFriendKey[8];

u8 gNintendoWfcHttpRequestBuffer[204];
#endif
