// Converted from asm/gts_data.s (part 5 of 7) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

#include "global.h"

#include "constants/pokemon.h"

#include "gts/gts_internal.h"

#pragma force_active on

FS_EXTERN_OVERLAY(OVY_71);

extern void TradeSequence_Exit(void);
extern void TradeSequence_Init(void);
extern void TradeSequence_Main(void);

// clang-format off
const OverlayManagerTemplate gGtsTradeSequenceTemplate = {
    (OverlayFunction)TradeSequence_Init, (OverlayFunction)TradeSequence_Main,
    (OverlayFunction)TradeSequence_Exit, FS_OVERLAY_ID(OVY_71),
};
// clang-format on

// clang-format off
const u8 gGtsViewMonSummaryPages[8] __attribute__((aligned(4))) = {
    0x00, 0x01, 0x02, 0x03, 0x04, 0x00, 0x00, 0x00,
};
// clang-format on

GtsGlobals gGtsGlobals;

#ifndef SDK_PORT // part of gGtsServer on the port (gts_internal.h)
u8 gGtsServerShortResponse[8];
#endif

// zero bytes after gGtsGlobals in the asm
static u8 gGtsGlobals_pad[20];
