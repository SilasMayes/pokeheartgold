// Converted from asm/plaza_game_mime_jr_top_data.s (part 9 of 9) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

// The C declarations of these do not match the data (see the notes at each
// definition): keep them out of the way of the definitions below.
#define gMimeJrTopRoutines      gMimeJrTopRoutines_header_decl
#define gMimeJrTopRoutineCounts gMimeJrTopRoutineCounts_header_decl
#define gMimeJrTopRoutineSpeeds gMimeJrTopRoutineSpeeds_header_decl
#define gMimeJrTopRoutineTasks  gMimeJrTopRoutineTasks_header_decl

#include "global.h"

#include "application/plaza_game_mime_jr_top.h"

#pragma force_active on

#undef gMimeJrTopRoutines
#undef gMimeJrTopRoutineCounts
#undef gMimeJrTopRoutineSpeeds
#undef gMimeJrTopRoutineTasks

#ifdef SDK_PORT
const MimeJrTopRoutineTask gMimeJrTopRoutineTasks[9] = {
    { NULL },
    { (SysTaskFunc)MimeJrTopDance_Routine1 },
    { (SysTaskFunc)MimeJrTopDance_Routine2 },
    { (SysTaskFunc)MimeJrTopDance_Routine2 },
    { (SysTaskFunc)MimeJrTopDance_Routine3 },
    { (SysTaskFunc)MimeJrTopDance_Routine3 },
    { (SysTaskFunc)MimeJrTopDance_Routine4 },
    { (SysTaskFunc)MimeJrTopDance_Routine5 },
    { (SysTaskFunc)MimeJrTopDance_Routine5 },
};
#else
// C declares this as `const MimeJrTopRoutineTask gMimeJrTopRoutineTasks[]`, but the label holds 4 more
// bytes of data after it.
const struct {
    u8 unk0[40];
    void (*unk28)(void);
    u8 unk2C[36];
    void (*unk50)(void);
    u8 unk54[36];
    void (*unk78)(void);
    u8 unk7C[36];
    void (*unkA0)(void);
    u8 unkA4[36];
    void (*unkC8)(void);
    u8 unkCC[36];
    void (*unkF0)(void);
    u8 unkF4[36];
    void (*unk118)(void);
    u8 unk11C[36];
    void (*unk140)(void);
} gMimeJrTopRoutineTasks = {
    {
     0x00,
     0x00,
     0x00,
     0x00,
     0x96,
     0x00,
     0x00,
     0x00,
     0x02,
     0x00,
     0x00,
     0x00,
     0x01,
     0x00,
     0x00,
     0x00,
     0x00,
     0x00,
     0x00,
     0x00,
     0x00,
     0x00,
     0x00,
     0x00,
     0x00,
     0x00,
     0x00,
     0x00,
     0x00,
     0x00,
     0x00,
     0x00,
     0x00,
     0x00,
     0x00,
     0x00,
     0x00,
     0x00,
     0x00,
     0x00,
     },
    (void (*)(void))MimeJrTopDance_Routine1,
    {
     0x96,
     0x00,
     0x00,
     0x00,
     0x03,
     0x00,
     0x00,
     0x00,
     0x02,
     0x00,
     0x00,
     0x00,
     0x00,
     0x00,
     0x00,
     0x00,
     0x00,
     0x00,
     0x00,
     0x00,
     0x00,
     0x00,
     0x00,
     0x00,
     0x00,
     0x00,
     0x00,
     0x00,
     0x00,
     0x00,
     0x00,
     0x00,
     0x00,
     0x00,
     0x00,
     0x00,
     },
    (void (*)(void))MimeJrTopDance_Routine2,
    {
     0x96,
     0x00,
     0x00,
     0x00,
     0x03,
     0x00,
     0x00,
     0x00,
     0x02,
     0x00,
     0x00,
     0x00,
     0x00,
     0x00,
     0x00,
     0x00,
     0x01,
     0x00,
     0x00,
     0x00,
     0x00,
     0x00,
     0x00,
     0x00,
     0x01,
     0x00,
     0x00,
     0x00,
     0x00,
     0x00,
     0x00,
     0x00,
     0x00,
     0x00,
     0x00,
     0x00,
     },
    (void (*)(void))MimeJrTopDance_Routine2,
    {
     0x96,
     0x00,
     0x00,
     0x00,
     0x03,
     0x00,
     0x00,
     0x00,
     0x03,
     0x00,
     0x00,
     0x00,
     0x00,
     0x00,
     0x00,
     0x00,
     0x01,
     0x00,
     0x00,
     0x00,
     0x02,
     0x00,
     0x00,
     0x00,
     0x02,
     0x00,
     0x00,
     0x00,
     0x00,
     0x00,
     0x00,
     0x00,
     0x00,
     0x00,
     0x00,
     0x00,
     },
    (void (*)(void))MimeJrTopDance_Routine3,
    {
     0x96,
     0x00,
     0x00,
     0x00,
     0x03,
     0x00,
     0x00,
     0x00,
     0x04,
     0x00,
     0x00,
     0x00,
     0x00,
     0x00,
     0x00,
     0x00,
     0x01,
     0x00,
     0x00,
     0x00,
     0x02,
     0x00,
     0x00,
     0x00,
     0x02,
     0x00,
     0x00,
     0x00,
     0x00,
     0x00,
     0x00,
     0x00,
     0x00,
     0x00,
     0x00,
     0x00,
     },
    (void (*)(void))MimeJrTopDance_Routine3,
    {
     0x96,
     0x00,
     0x00,
     0x00,
     0x03,
     0x00,
     0x00,
     0x00,
     0x05,
     0x00,
     0x00,
     0x00,
     0x02,
     0x00,
     0x00,
     0x00,
     0x01,
     0x00,
     0x00,
     0x00,
     0x00,
     0x00,
     0x00,
     0x00,
     0x01,
     0x00,
     0x00,
     0x00,
     0x00,
     0x00,
     0x00,
     0x00,
     0x00,
     0x00,
     0x00,
     0x00,
     },
    (void (*)(void))MimeJrTopDance_Routine4,
    {
     0x96,
     0x00,
     0x00,
     0x00,
     0x03,
     0x00,
     0x00,
     0x00,
     0x05,
     0x00,
     0x00,
     0x00,
     0x02,
     0x00,
     0x00,
     0x00,
     0x01,
     0x00,
     0x00,
     0x00,
     0x00,
     0x00,
     0x00,
     0x00,
     0x02,
     0x00,
     0x00,
     0x00,
     0x00,
     0x00,
     0x00,
     0x00,
     0x00,
     0x00,
     0x00,
     0x00,
     },
    (void (*)(void))MimeJrTopDance_Routine5,
    {
     0x96,
     0x00,
     0x00,
     0x00,
     0x03,
     0x00,
     0x00,
     0x00,
     0x05,
     0x00,
     0x00,
     0x00,
     0x02,
     0x00,
     0x00,
     0x00,
     0x01,
     0x00,
     0x00,
     0x00,
     0x00,
     0x00,
     0x00,
     0x00,
     0x02,
     0x00,
     0x00,
     0x00,
     0x00,
     0x00,
     0x00,
     0x00,
     0x00,
     0x00,
     0x00,
     0x00,
     },
    (void (*)(void))MimeJrTopDance_Routine5,
};
#endif

#ifdef SDK_PORT
const MimeJrTopRoutineValue gMimeJrTopRoutineSpeeds[9] = {
    { 0 },
    { 1 },
    { 2 },
    { 2 },
    { 3 },
    { 4 },
    { 5 },
    { 5 },
    { 5 },
};
#else
// C declares this as `const MimeJrTopRoutineValue gMimeJrTopRoutineSpeeds[]`, but one element of that
// type is larger than the data under this label.
// clang-format off
const u8 gMimeJrTopRoutineSpeeds[28] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
// clang-format on
#endif

#ifdef SDK_PORT
const MimeJrTopRoutineValue gMimeJrTopRoutineCounts[9] = {
    { 0 },
    { 2 },
    { 3 },
    { 3 },
    { 3 },
    { 3 },
    { 3 },
    { 3 },
    { 3 },
};
#else
// C declares this as `const MimeJrTopRoutineValue gMimeJrTopRoutineCounts[]`, but one element of that
// type is larger than the data under this label.
const u8 gMimeJrTopRoutineCounts[4] = { 0x00, 0x00, 0x00, 0x00 };
#endif

#ifdef SDK_PORT
// One table by level: on the DS gMimeJrTopRoutineCounts, gMimeJrTopRoutineSpeeds and
// gMimeJrTopRoutineTasks are views of its count, speed and func members with the DS stride (0x28),
// which the function pointer changes on the port; so the port has its own copy of each column.
// clang-format off
const MimeJrTopRoutine gMimeJrTopRoutines[9] = {
    { 150, 0, 0, { 0, 0, 0 }, { 0, 0, 0 }, NULL },
    { 150, 2, 1, { 0, 0, 0 }, { 0, 0, 0 }, (SysTaskFunc)MimeJrTopDance_Routine1 },
    { 150, 3, 2, { 0, 0, 0 }, { 0, 0, 0 }, (SysTaskFunc)MimeJrTopDance_Routine2 },
    { 150, 3, 2, { 0, 1, 0 }, { 1, 0, 0 }, (SysTaskFunc)MimeJrTopDance_Routine2 },
    { 150, 3, 3, { 0, 1, 2 }, { 2, 0, 0 }, (SysTaskFunc)MimeJrTopDance_Routine3 },
    { 150, 3, 4, { 0, 1, 2 }, { 2, 0, 0 }, (SysTaskFunc)MimeJrTopDance_Routine3 },
    { 150, 3, 5, { 2, 1, 0 }, { 1, 0, 0 }, (SysTaskFunc)MimeJrTopDance_Routine4 },
    { 150, 3, 5, { 2, 1, 0 }, { 2, 0, 0 }, (SysTaskFunc)MimeJrTopDance_Routine5 },
    { 150, 3, 5, { 2, 1, 0 }, { 2, 0, 0 }, (SysTaskFunc)MimeJrTopDance_Routine5 },
};
// clang-format on
#else
// C declares this as `const MimeJrTopRoutine gMimeJrTopRoutines[]`, but one element of that type is
// larger than the data under this label.
const u8 gMimeJrTopRoutines[4] = { 0x96, 0x00, 0x00, 0x00 };
#endif
