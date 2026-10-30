// Converted from asm/pokewalker_data.s (part 8 of 15) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

#include "global.h"

#include "application/pokewalker/pokewalker_app.h"
#include "application/pokewalker/pokewalker_app_internal.h"
#include "application/pokewalker/pokewalker_event_log.h"
#include "application/pokewalker/pokewalker_ir_internal.h"
#include "application/pokewalker/pokewalker_trainer_house.h"

#pragma force_active on

const s32 gCourseMenuCursorPositions[6] = { 6, 7, 8, 9, 10, 3 };

const int gTopMenuCursorPositions[6] = { 6, 7, 8, 9, 10, 3 };

const int gFullMenuCursorPositions[4] = { 11, 12, 13, 3 };

const int gReceiveMenuCursorPositions[3] = { 0, 1, 3 };
