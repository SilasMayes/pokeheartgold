// Converted from asm/pokeathlon_pennant_capture_rodata.s (part 2 of 2) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

#include "global.h"

#include "pokeathlon/pokeathlon_pennant_capture.h"

#pragma force_active on

const u8 gPennantCaptureTimerDigitX[4] = { 0x80, 0x90, 0x00, 0x00 };

const u8 gPennantCaptureTimerDigitAnims[4] = { 0x01, 0x01, 0x00, 0x00 };
