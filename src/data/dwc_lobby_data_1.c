// Converted from asm/dwc_lobby_data.s (part 1 of 5) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

// The C declarations of these do not match the data (see the notes at each
// definition): keep them out of the way of the definitions below.
#define gPPWLobbyClockChannelMode      gPPWLobbyClockChannelMode_header_decl
#define gPPWLobbyNewsChannelMode       gPPWLobbyNewsChannelMode_header_decl
#define gPPWLobbyFootChannelMode       gPPWLobbyFootChannelMode_header_decl
#define gPPWLobbyMainChannelMode       gPPWLobbyMainChannelMode_header_decl
#define gPPWLobbyMainChannelSecretMode gPPWLobbyMainChannelSecretMode_header_decl

#include "global.h"

#include "lobby_chat_internal.h"
#include "lobby_chat_manager.h"
#include "lobby_event_deque.h"
#include "ppw_lobby_work.h"

#pragma force_active on

#undef gPPWLobbyClockChannelMode
#undef gPPWLobbyNewsChannelMode
#undef gPPWLobbyFootChannelMode
#undef gPPWLobbyMainChannelMode
#undef gPPWLobbyMainChannelSecretMode

extern const u8 gLobbyStr_C[];
extern const u8 gLobbyStr_F1[];
extern const u8 gLobbyStr_F2[];
extern const u8 gLobbyStr_Invalid[];
extern const u8 gLobbyStr_M[];
extern const u8 gLobbyStr_N[];

// 0x02254D1C
// C declares this as `const struct ChatChannelMode gPPWLobbyClockChannelMode`, but that type is
// incomplete.
// clang-format off
const u8 gPPWLobbyClockChannelMode[32] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00,
};
// clang-format on

// 0x02254D3C
// C declares this as `const struct ChatChannelMode gPPWLobbyNewsChannelMode`, but that type is
// incomplete.
// clang-format off
const u8 gPPWLobbyNewsChannelMode[32] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00,
};
// clang-format on

// 0x02254D5C
// C declares this as `const struct ChatChannelMode gPPWLobbyFootChannelMode`, but that type is
// incomplete.
// clang-format off
const u8 gPPWLobbyFootChannelMode[32] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00,
};
// clang-format on

// 0x02254D7C
// C declares this as `const struct ChatChannelMode gPPWLobbyMainChannelMode`, but that type is
// incomplete.
// clang-format off
const u8 gPPWLobbyMainChannelMode[32] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00,
};
// clang-format on

// 0x02254D9C
// C declares this as `const struct ChatChannelMode gPPWLobbyMainChannelSecretMode`, but that type is
// incomplete.
// clang-format off
const u8 gPPWLobbyMainChannelSecretMode[32] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00,
};
// clang-format on

const void *const gPPWLobbyChannelNamePrefixes[6] = {
    gLobbyStr_M,
    gLobbyStr_F1,
    gLobbyStr_F2,
    gLobbyStr_C,
    gLobbyStr_N,
    gLobbyStr_Invalid,
};

// 0x022577CC
u32 gLobbyEventDequeMapBufferMaxSizeSet;

// 0x022577D8
u8 gPPWLobbyFinishedRequest[4];

// 0x022577D4
u8 gPPWLobbyCurrentRequest[4];

// 0x022577C8
u32 gLobbyDequeMaxSizeInit;

PPWLobbyWork *gPPWLobbyWork;

// 0x022577D0
u32 gLobbyEventDequeMapMaxSizeSet;
