// Converted from asm/gts_data.s (part 4 of 7) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

// The C declarations of these do not match the data (see the notes at each
// definition): keep them out of the way of the definitions below.
#ifndef SDK_PORT
#define gGtsServerAnswer gGtsServerAnswer_header_decl
#endif

#include "global.h"

#include "constants/pokemon.h"

#include "gts/gts_internal.h"

#pragma force_active on

#ifndef SDK_PORT
#undef gGtsServerAnswer
#endif

const TouchscreenHitbox gGtsAvatarHitboxes[8] = {
    { 0x46, 0x66, 0x70, 0x90 },
    { 0x47, 0x67, 0x50, 0x70 },
    { 0x47, 0x67, 0x90, 0xB0 },
    { 0x56, 0x76, 0x30, 0x50 },
    { 0x56, 0x76, 0xB0, 0xD0 },
    { 0x76, 0x96, 0x20, 0x40 },
    { 0x76, 0x96, 0xC0, 0xE0 },
    { 0xFF, 0x00, 0x00, 0x00 },
};

const GtsAvatarPosition gGtsAvatarPositions[7] = {
    { 0x0080, 0x0036 },
    { 0x0060, 0x0037 },
    { 0x00A0, 0x0037 },
    { 0x0040, 0x0046 },
    { 0x00C0, 0x0046 },
    { 0x0030, 0x0066 },
    { 0x00D0, 0x0066 },
};

const u16 gGtsAvatarCharOffsets[7] = { 0x2400, 0x2600, 0x2800, 0x2A00, 0x2C00, 0x2E00, 0x3000 };

#ifndef SDK_PORT // part of gGtsServer on the port (gts_internal.h)
// C declares this as `volatile GtsServerAnswer gGtsServerAnswer`, but that type is 0x20 bytes and the
// label covers only 0x1c: the type describes it together with the label after it.
u8 gGtsServerAnswer[28];
#endif
