// Converted from asm/plaza_game_data.s (part 4 of 4) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

// The C declarations of these do not match the data (see the notes at each
// definition): keep them out of the way of the definitions below.
#define gPlazaGameCommands gPlazaGameCommands_header_decl

#include "global.h"

#include "application/plaza_game.h"

#pragma force_active on

#undef gPlazaGameCommands

// C declares this as `const u8 gPlazaGameCommands[]`, but an address sits where that type has a 1-byte
// field.
void (*const gPlazaGameCommands[15])(void) = {
    (void (*)(void))PlazaGame_HandleVoteYesCommand,
    (void (*)(void))PlazaGame_GetCommandSizeNone,
    NULL,
    (void (*)(void))PlazaGame_HandleVoteNoCommand,
    (void (*)(void))PlazaGame_GetCommandSizeNone,
    NULL,
    (void (*)(void))PlazaGame_HandleContinueCommand,
    (void (*)(void))PlazaGame_GetCommandSizeNone,
    NULL,
    (void (*)(void))PlazaGame_HandleQuitCommand,
    (void (*)(void))PlazaGame_GetCommandSizeNone,
    NULL,
    (void (*)(void))PlazaGame_HandleSelectionCommand,
    (void (*)(void))PlazaGame_GetCommandSizeU32,
    NULL,
};
