// Converted from asm/nintendo_wfc_connect_unused_data.s by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout. Keep that when editing, or rerun tools/s2c.py.

#include "global.h"

#include "nintendo_wfc_connect_unused.h"

#pragma force_active on

const u8 ov73_021EA67C[8] __attribute__((aligned(4))) = { 0x00, 0x17, 0x0D, 0x07, 0x04, 0x0D, 0x00, 0x00 };

const u16 gNintendoWfcUnusedArrowPositions[2][2] = {
    { 224, 111 },
    { 224, 129 }
};
