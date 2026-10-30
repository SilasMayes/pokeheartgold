// Converted from asm/vs_recorder_data.s (part 4 of 14) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

// The C declarations of these do not match the data (see the notes at each
// definition): keep them out of the way of the definitions below.
#define gVsRecorderBoxDataSendSubStates gVsRecorderBoxDataSendSubStates_header_decl
#define gVsRecorderBoxDataViewSubStates gVsRecorderBoxDataViewSubStates_header_decl

#include "global.h"

#include "application/vs_recorder/vs_recorder_screens.h"

#pragma force_active on

#undef gVsRecorderBoxDataSendSubStates
#undef gVsRecorderBoxDataViewSubStates

// C declares this non-const, but it lives in .rodata
// clang-format off
const VsRecorderScreenFunc gVsRecorderBoxDataViewSubStates[14] = {
    VsRecorder_BoxDataInit, VsRecorder_BoxDataEnter, VsRecorder_BoxDataViewShow,
    VsRecorder_BoxDataViewSelectCategory, VsRecorder_BoxDataViewDownload, VsRecorder_BoxListMain,
    VsRecorder_BoxListBack, VsRecorder_BoxListShowProfile, VsRecorder_BoxListHideProfile,
    VsRecorder_BoxDataViewOpenBox, VsRecorder_BoxDataViewBoxMain, VsRecorder_BoxDataViewCloseBox,
    VsRecorder_BoxDataViewQuit, VsRecorder_BoxDataViewExit,
};
// clang-format on

const VsRecorderListConfig gVsRecorderBoxListConfig = { NULL, 0, 3, 3, 7, 26, 15, 64, 2, 5, NULL };

// C declares this non-const, but it lives in .rodata
// clang-format off
const VsRecorderScreenFunc gVsRecorderBoxDataSendSubStates[11] = {
    VsRecorder_BoxDataInit, VsRecorder_BoxDataEnter, VsRecorder_BoxDataSendShow, VsRecorder_BoxDataSendMain,
    VsRecorder_BoxDataSendChangeBox, VsRecorder_BoxDataSendShowCategories,
    VsRecorder_BoxDataSendSelectCategory, VsRecorder_BoxDataSendCancelCategory, VsRecorder_BoxDataSendUpload,
    VsRecorder_BoxDataSendQuit, VsRecorder_BoxDataSendExit,
};
// clang-format on

const TouchscreenHitbox sVsRecorderBoxDataCategoryHitboxes[7] = {
    { 0x18, 0x28, 0x18, 0x78 },
    { 0x18, 0x28, 0x90, 0xF0 },
    { 0x40, 0x50, 0x18, 0x78 },
    { 0x40, 0x50, 0x90, 0xF0 },
    { 0x68, 0x78, 0x18, 0x78 },
    { 0x68, 0x78, 0x90, 0xF0 },
    { 0x98, 0xB8, 0x50, 0xB0 },
};

const VsRecorderBoxWindowRect sVsRecorderBoxDataCategoryButtonWindows[6] = {
    { 0x03, 0x03, 0x0B, 0x02 },
    { 0x12, 0x03, 0x0B, 0x02 },
    { 0x03, 0x08, 0x0B, 0x02 },
    { 0x12, 0x08, 0x0B, 0x02 },
    { 0x03, 0x0D, 0x0B, 0x02 },
    { 0x12, 0x0D, 0x0B, 0x02 },
};

const TouchscreenHitbox gVsRecorderBoxDataSendHitboxes[4] = {
    { 0x20, 0x40, 0x18, 0x48 },
    { 0x20, 0x40, 0xB8, 0xE0 },
    { 0x98, 0xB8, 0x20, 0x80 },
    { 0x98, 0xB8, 0x80, 0xE0 },
};
