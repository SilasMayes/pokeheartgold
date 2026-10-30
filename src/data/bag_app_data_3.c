// Converted from asm/bag_app_data.s (part 3 of 5) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

#include "global.h"

#include "constants/items.h"
#include "constants/sndseq.h"

#include "application/bag/bag_app.h"
#include "msgdata/msg/msg_0010.h"

#pragma force_active on

extern void Bag_Exit(void);
extern void Bag_Init(void);
extern void Bag_Main(void);

// clang-format off
const OverlayManagerTemplate gOverlayTemplate_Bag = {
    (OverlayFunction)Bag_Init, (OverlayFunction)Bag_Main, (OverlayFunction)Bag_Exit, 0xFFFFFFFF,
};
// clang-format on

const u8 gPocketCapacities[8] = { 0xA5, 0x28, 0x18, 0x65, 0x40, 0x0C, 0x1E, 0x32 };
