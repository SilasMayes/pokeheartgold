// Converted from asm/wobbuffet_pop_data.s (part 4 of 4) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

// The C declarations of these do not match the data (see the notes at each
// definition): keep them out of the way of the definitions below.
#define gWobbuffetPopLocalModelFiles gWobbuffetPopLocalModelFiles_header_decl
#define gWobbuffetPopSlotModelFiles0 gWobbuffetPopSlotModelFiles0_header_decl
#define gWobbuffetPopSlotModelFiles1 gWobbuffetPopSlotModelFiles1_header_decl
#define gWobbuffetPopSlotModelFiles2 gWobbuffetPopSlotModelFiles2_header_decl
#define gWobbuffetPopSlotModelFiles3 gWobbuffetPopSlotModelFiles3_header_decl

#include "global.h"

#include "wobbuffet_pop_internal.h"

#pragma force_active on

#undef gWobbuffetPopLocalModelFiles
#undef gWobbuffetPopSlotModelFiles0
#undef gWobbuffetPopSlotModelFiles1
#undef gWobbuffetPopSlotModelFiles2
#undef gWobbuffetPopSlotModelFiles3

const BgTemplate gWobbuffetPopSubBgTemplates[4] = {
    { 0, 0, 0x00000800, 0, 0x01, 0x00, 0x00, 0x02, 0x00, 0x01, 0x00, 0x00, 0 },
    { 0, 0, 0x00000800, 0, 0x01, 0x00, 0x04, 0x04, 0x00, 0x03, 0x00, 0x00, 0 },
    { 0, 0, 0x00001000, 0, 0x01, 0x00, 0x08, 0x05, 0x00, 0x03, 0x00, 0x00, 0 },
    { 0, 0, 0x00000400, 0, 0x01, 0x01, 0x0C, 0x06, 0x00, 0x00, 0x00, 0x00, 0 },
};

const BgTemplate gWobbuffetPopMainBgTemplates[3] = {
    { 0, 0, 0x00001000, 0, 0x03, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0 },
    { 0, 0, 0x00002000, 0, 0x04, 0x00, 0x02, 0x03, 0x00, 0x01, 0x00, 0x00, 0 },
    { 0, 0, 0x00001000, 0, 0x03, 0x00, 0x06, 0x04, 0x00, 0x02, 0x00, 0x00, 0 },
};

// C declares this as `const WobbuffetPopModelFiles gWobbuffetPopSlotModelFiles3[]`, but the label
// holds 4 more bytes of data after it.
// clang-format off
const u8 gWobbuffetPopSlotModelFiles3[64] = {
    0x2A, 0x00, 0x00, 0x00, 0x21, 0x00, 0x00, 0x00, 0x2F, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00,
    0x31, 0x00, 0x00, 0x00, 0x32, 0x00, 0x00, 0x00, 0x22, 0x00, 0x00, 0x00, 0x33, 0x00, 0x00, 0x00,
    0x34, 0x00, 0x00, 0x00, 0x35, 0x00, 0x00, 0x00, 0x36, 0x00, 0x00, 0x00, 0x1F, 0x00, 0x00, 0x00,
    0x2B, 0x00, 0x00, 0x00, 0x2C, 0x00, 0x00, 0x00, 0x2D, 0x00, 0x00, 0x00, 0x2E, 0x00, 0x00, 0x00,
};
// clang-format on

// C declares this as `const WobbuffetPopModelFiles gWobbuffetPopSlotModelFiles1[]`, but one element of
// that type is larger than the data under this label.
const u8 gWobbuffetPopSlotModelFiles1[4] = { 0x28, 0x00, 0x00, 0x00 };

// C declares this as `const WobbuffetPopModelFiles gWobbuffetPopSlotModelFiles0[]`, but one element of
// that type is larger than the data under this label.
const u8 gWobbuffetPopSlotModelFiles0[4] = { 0x27, 0x00, 0x00, 0x00 };

// C declares this as `const WobbuffetPopModelFiles gWobbuffetPopSlotModelFiles2[]`, but one element of
// that type is larger than the data under this label.
const u8 gWobbuffetPopSlotModelFiles2[4] = { 0x29, 0x00, 0x00, 0x00 };

// C declares this as `const WobbuffetPopModelFiles gWobbuffetPopLocalModelFiles[]`, but one element of
// that type is larger than the data under this label.
const u8 gWobbuffetPopLocalModelFiles[4] = { 0x20, 0x00, 0x00, 0x00 };
