// Converted from asm/plaza_game_mime_jr_top_data.s (part 1 of 9) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

#include "global.h"

#include "application/plaza_game_mime_jr_top.h"

#pragma force_active on

MimeJrTopPlayerPalettes gMimeJrTopPlayerPalettes[16] = {
    { { 0, 0, 0, 0, 0 } },
    { { 0, 0, 0, 0, 0 } },
    { { 0, 0, 0, 0, 0 } },
    { { 0, 0, 0, 0, 0 } },
    { { 1, 2, 0, 0, 0 } },
    { { 2, 1, 0, 0, 0 } },
    { { 0, 0, 0, 0, 0 } },
    { { 0, 0, 0, 0, 0 } },
    { { 1, 2, 3, 0, 0 } },
    { { 2, 1, 3, 0, 0 } },
    { { 3, 1, 2, 0, 0 } },
    { { 0, 0, 0, 0, 0 } },
    { { 1, 2, 3, 4, 0 } },
    { { 2, 1, 3, 4, 0 } },
    { { 3, 1, 2, 4, 0 } },
    { { 4, 1, 2, 3, 0 } },
};

const MimeJrTopDemoPath gMimeJrTopDemoPath = {
    {
     { 0, 0 },
     { 0, -40 },
     { 0, -30 },
     { 0, -20 },
     { 0, -10 },
     { 0, 0 },
     { 0, 10 },
     { 0, 20 },
     { 0, 30 },
     { 0, 40 },
     { 0, 0 },
     { 0, 0 },
     { 0, 0 },
     { 0, -40 },
     { 0, -30 },
     { 0, -20 },
     { 0, -10 },
     { 0, 0 },
     { 0, 10 },
     { 0, 20 },
     { 0, 30 },
     { 0, 40 },
     { 0, 0 },
     { 0, 0 },
     { 0, 0 },
     { 10, 0 },
     { 20, 0 },
     { 30, 0 },
     { 40, 0 },
     { 50, 0 },
     { 60, 0 },
     { 70, 0 },
     { 80, 0 },
     { 90, 0 },
     { 0, 0 },
     { 0, 0 },
     { 0, 0 },
     { 10, 0 },
     { 20, 0 },
     { 30, 0 },
     { 40, 0 },
     { 50, 0 },
     { 60, 0 },
     { 70, 0 },
     { 80, 0 },
     { 90, 0 },
     { 0, 0 },
     { 0, 0 },
     },
};

const MimeJrTopModelFiles gMimeJrTopAudienceModelFiles = {
    {
     { 44, 43 },
     { 46, 45 },
     { 48, 47 },
     { 50, 49 },
     { 44, 43 },
     { 46, 45 },
     { 48, 47 },
     { 50, 49 },
     { 44, 43 },
     { 46, 45 },
     { 48, 47 },
     { 50, 49 },
     { 44, 43 },
     { 46, 45 },
     { 48, 47 },
     { 50, 49 },
     },
};

const MimeJrTopBgTemplates gMimeJrTopMainBgTemplates = {
    {
     { 0, 0, 0x00000800, 0, 0x01, 0x00, 0x04, 0x04, 0x00, 0x03, 0x00, 0x00, 0 },
     { 0, 0, 0x00001000, 0, 0x03, 0x00, 0x05, 0x05, 0x00, 0x02, 0x00, 0x00, 0 },
     { 0, 0, 0x00001000, 0, 0x03, 0x00, 0x07, 0x05, 0x00, 0x02, 0x00, 0x00, 0 },
     { 0, 0, 0x00000800, 0, 0x01, 0x00, 0x09, 0x04, 0x00, 0x03, 0x00, 0x00, 0 },
     },
};

const MimeJrTopBgTemplates gMimeJrTopSubBgTemplates = {
    {
     { 0, 0, 0x00000800, 0, 0x01, 0x00, 0x16, 0x00, 0x00, 0x03, 0x00, 0x00, 0 },
     { 0, 0, 0x00001000, 0, 0x03, 0x00, 0x17, 0x01, 0x00, 0x01, 0x00, 0x00, 0 },
     { 0, 0, 0x00001000, 0, 0x03, 0x00, 0x19, 0x01, 0x00, 0x01, 0x00, 0x00, 0 },
     { 0, 0, 0x00001000, 0, 0x02, 0x00, 0x1B, 0x01, 0x00, 0x00, 0x00, 0x00, 0 },
     },
};

const MimeJrTopBanks gMimeJrTopBanks = {
    { 1, 0, 4, 0, 0x00000010, 0, 0x00000100, 0, 2, 0x00000060 }
};

const OamManagerParam gMimeJrTopOamManagerParam = { 0, 128, 0, 32, 0, 128, 0, 32 };

const SpriteResourceCountsListUnion gMimeJrTopSpriteResourceCounts = { 128, 32, 128, 128, 16, 16 };

// clang-format off
const OamCharTransferParam gMimeJrTopOamCharTransferParam = {
    128, 65536, 16384, GX_OBJVRAMMODE_CHAR_1D_64K, GX_OBJVRAMMODE_CHAR_1D_64K,
};
// clang-format on

const MimeJrTopTopModels gMimeJrTopTopModels = {
    { 3, 1, 4, 2 }
};

const u16 gMimeJrTopEdgeColors[8] = { 0, 0x1084, 0x1084, 0x1084, 0x1084, 0x1084, 0x1084, 0x1084 };

const MimeJrTopGraphicsModes gMimeJrTopGraphicsModes = {
    { 1, 0, 0, 1 }
};

const VecFx32 gMimeJrTopDemoTurnTiltAxis = { 0, 409600, 0 };

const VecFx32 gMimeJrTopDemoSpinTiltAxis = { 0, 409600, 0 };
