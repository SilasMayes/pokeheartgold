// Converted from asm/spl_data.s (part 1 of 2) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

// The C declarations of these do not match the data (see the notes at each
// definition): keep them out of the way of the definitions below.
#define gSplDrawPlaneFuncs gSplDrawPlaneFuncs_header_decl
#define gSplRotateFuncs    gSplRotateFuncs_header_decl

#include "global.h"

#include "spl_internal.h"

#pragma force_active on

#undef gSplDrawPlaneFuncs
#undef gSplRotateFuncs

// C declares this const, but it lives in .data
void (*gSplDrawPlaneFuncs[2])(fx32 s, fx32 t, fx32 x, fx32 y) = { drawXYPlane, drawXZPlane };

// C declares this const, but it lives in .data
void (*gSplRotateFuncs[2])(fx32 sin, fx32 cos, MtxFx43 *mtx) = { rotTypeY, rotTypeXYZ };

u32 spl_rndm_seed;
