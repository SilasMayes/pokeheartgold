// Converted from asm/dowsing_mchn_data.s (part 1 of 4) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

#include "global.h"

#pragma force_active on

// Also holds the asm labels gDowsingMchnActionSpriteParams (+0xa),
// gDowsingMchnRunningShoesSpriteParams (+0xe), gDowsingMchnRunningShoesSprite2Params (+0x12),
// gDowsingMchnExitSpriteParams (+0x16). MWCC sorts a file's objects by size and the linker starts
// every section 4-aligned, so no arrangement of separate objects puts them where the asm has them;
// the code has to reach them through gDowsingMchnLevelParams.
// clang-format off
const u8 gDowsingMchnLevelParams[28] = {
    0x31, 0x1D, 0x4F, 0x27, 0x6D, 0x31, 0x81, 0x31, 0x9F, 0x9F, 0xA8, 0x90, 0x00, 0x05, 0xB8, 0x56,
    0x01, 0x03, 0xD2, 0x5E, 0x00, 0x07, 0xC8, 0x08, 0x00, 0x08, 0x00, 0x00,
};
// clang-format on

const u8 gDowsingMchnSearchAreaHitbox[8] = { 0xFE, 0x54, 0x64, 0x48, 0xFF, 0x00, 0x00, 0x00 };

const u8 gDowsingMchnExitButtonHitbox[4] = { 0x08, 0x27, 0xC0, 0xFF };

const u8 gDowsingMchnActionButtonHitbox[4] __attribute__((aligned(4))) = { 0x90, 0xBC, 0x9D, 0xFF };

const u8 gDowsingMchnRunningShoesHitbox[4] = { 0x56, 0x86, 0xB2, 0xFC };
