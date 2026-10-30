// Converted from asm/nintendo_wfc_connect_data.s (part 5 of 5) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

// The C declarations of these do not match the data (see the notes at each
// definition): keep them out of the way of the definitions below.
#define gNintendoWfcYesNoStates gNintendoWfcYesNoStates_header_decl

#include "global.h"

#include "nintendo_wfc_connect_internal.h"

#pragma force_active on

#undef gNintendoWfcYesNoStates

// C declares this const, but it lives in .data
// clang-format off
BOOL (*gNintendoWfcYesNoStates[4])(NintendoWfcYesNoMenu *menu) = {
    (BOOL (*)(NintendoWfcYesNoMenu *))NintendoWfcYesNo_Start,
    (BOOL (*)(NintendoWfcYesNoMenu *))NintendoWfcYesNo_HandleInput,
    (BOOL (*)(NintendoWfcYesNoMenu *))NintendoWfcYesNo_UnusedState2,
    (BOOL (*)(NintendoWfcYesNoMenu *))NintendoWfcYesNo_WaitClose,
};
// clang-format on
