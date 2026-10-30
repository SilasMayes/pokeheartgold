// Converted from asm/ball_capsule_editor_data.s (part 2 of 2) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

#include "global.h"

#pragma force_active on

extern void BallCapsuleEditor_MenuEdit(void);
extern void BallCapsuleEditor_MenuQuit(void);
extern void BallCapsuleEditor_MenuRemove(void);
extern void BallCapsuleEditor_MenuSet(void);
extern void BallCapsuleEditor_MenuSwitch(void);
extern void BallCapsuleEditor_ModeEdit(void);
extern void BallCapsuleEditor_ModeNone(void);
extern void BallCapsuleEditor_ModeRemove(void);
extern void BallCapsuleEditor_ModeSelect(void);
extern void BallCapsuleEditor_ModeSwitch(void);

// clang-format off
const u8 gBallCapsuleEditorHitboxes[52] = {
    0x10, 0x20, 0x08, 0x18, 0x10, 0x20, 0x40, 0x50, 0x28, 0x38, 0x08, 0x18, 0x28, 0x38, 0x40, 0x50,
    0x40, 0x50, 0x08, 0x18, 0x40, 0x50, 0x40, 0x50, 0x58, 0x68, 0x08, 0x18, 0x58, 0x68, 0x40, 0x50,
    0x68, 0x80, 0x08, 0x30, 0x68, 0x80, 0x38, 0x60, 0xA8, 0xBC, 0x12, 0x4D, 0xA8, 0xBC, 0x61, 0x9C,
    0xA8, 0xBC, 0xB2, 0xED,
};
// clang-format on

const struct {
    u32 unk0;
    void (*unk4)(void);
} gBallCapsuleEditorMenuItems[5] = {
    { 0x00000000, BallCapsuleEditor_MenuEdit   },
    { 0x00000001, BallCapsuleEditor_MenuQuit   },
    { 0x00000002, BallCapsuleEditor_MenuSet    },
    { 0x00000003, BallCapsuleEditor_MenuRemove },
    { 0x00000004, BallCapsuleEditor_MenuSwitch },
};

void (*const gBallCapsuleEditorModes[5])(void) = {
    BallCapsuleEditor_ModeSelect,
    BallCapsuleEditor_ModeEdit,
    BallCapsuleEditor_ModeRemove,
    BallCapsuleEditor_ModeSwitch,
    BallCapsuleEditor_ModeNone,
};

const u8 gBallCapsuleEditorExitButtonHitboxes[8] = { 0xA8, 0xC0, 0xC0, 0x00, 0xFF, 0x00, 0x00, 0x00 };
