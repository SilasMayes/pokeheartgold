// Converted from asm/pokemon_summary_data.s (part 2 of 2) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

// The C declarations of these do not match the data (see the notes at each
// definition): keep them out of the way of the definitions below.
#define gOverlayTemplate_PokemonSummary gOverlayTemplate_PokemonSummary_header_decl

#include "global.h"

#include "constants/field_move_response.h"
#include "constants/items.h"
#include "constants/moves.h"
#include "constants/pokemon.h"
#include "constants/ribbon.h"

#include "msgdata/msg/msg_0300.h"

#include "pokemon_summary.h"
#include "pokemon_summary_internal.h"

#pragma force_active on

#undef gOverlayTemplate_PokemonSummary

// C declares this non-const, but it lives in .rodata
// clang-format off
const struct OverlayManagerTemplate gOverlayTemplate_PokemonSummary = {
    PokemonSummary_Init, PokemonSummary_Main, PokemonSummary_Exit, 0xFFFFFFFF,
};
// clang-format on
