// Converted from asm/wifi_plaza_lobby_data.s by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout. Keep that when editing, or rerun tools/s2c.py.

// The C declarations of these do not match the data (see the notes at each
// definition): keep them out of the way of the definitions below.
#define gWiFiPlazaPlayerObjectActions gWiFiPlazaPlayerObjectActions_header_decl

#include "global.h"

#include "wifi_plaza/wifi_plaza_internal.h"

#pragma force_active on

#undef gWiFiPlazaPlayerObjectActions

// C declares this const, but it lives in .data
// clang-format off
void (*gWiFiPlazaPlayerObjectActions[12])(WiFiPlazaPlayerObject *object) = {
    WiFiPlazaPlayerObject_ShowStandingSprite, WiFiPlazaPlayerObject_HoldWalkFrameThenRestart,
    WiFiPlazaPlayerObject_PlayStandingSequence, WiFiPlazaPlayerObject_PlayWalkingSequence,
    WiFiPlazaPlayerObject_ShowStandingSprite, WiFiPlazaPlayerObject_PlayStandingSequence,
    WiFiPlazaPlayerObject_PlayStandingSequence, WiFiPlazaPlayerObject_PlayStandingSequence,
    WiFiPlazaPlayerObject_PlayStandingSequence, WiFiPlazaPlayerObject_PlayStandingSequence,
    WiFiPlazaPlayerObject_PlayStandingSequence, NULL,
};
// clang-format on
