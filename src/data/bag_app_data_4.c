// Converted from asm/bag_app_data.s (part 4 of 5) by tools/s2c.py.
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

const BagAppWindowTemplate gItemListWindowTemplates[12] = {
    { 4,          5,          0x000000BF },
    { 0x00000014, 5,          0x000000EB },
    { 4,          0x0000000A, 0x00000117 },
    { 0x00000014, 0x0000000A, 0x00000143 },
    { 4,          0x0000000F, 0x0000016F },
    { 0x00000014, 0x0000000F, 0x0000019B },
    { 4,          5,          0x000001C7 },
    { 0x00000014, 5,          0x000001F3 },
    { 4,          0x0000000A, 0x0000021F },
    { 0x00000014, 0x0000000A, 0x0000024B },
    { 4,          0x0000000F, 0x00000277 },
    { 0x00000014, 0x0000000F, 0x000002A3 },
};

const BagAppWindowPos gItemMenuWindowPositions[4] = {
    { 1,          0x00000011 },
    { 0x0000000D, 0x00000011 },
    { 1,          0x00000015 },
    { 0x0000000D, 0x00000015 },
};

const BagAppWindowPos gQuantityDigitWindowPositions[3] = {
    { 0x00000010, 0x0000000E },
    { 0x00000014, 0x0000000E },
    { 0x00000018, 0x0000000E },
};

const u8 gListPocketCapacities[8] = { 0xA5, 0x28, 0x18, 0x65, 0x40, 0x0C, 0x1E, 0x32 };
