// Converted from asm/footprint_stamp_data.s (part 3 of 3) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

#include "global.h"

#include "application/footprint_stamp.h"

#pragma force_active on

const WiFiPlazaLobbyCommand gFootprintStampLinkCommands[3] = {
    { (void (*)(int, const void *, u32, void *))FootprintStamp_HandlePlayerJoined,  0x0000000C },
    { (void (*)(int, const void *, u32, void *))FootprintStamp_HandlePlayerLeft,    0x00000000 },
    { (void (*)(int, const void *, u32, void *))FootprintStamp_HandleStampReceived, 0x0000000C },
};
