// Converted from asm/vs_recorder_data.s (part 8 of 14) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

// The C declarations of these do not match the data (see the notes at each
// definition): keep them out of the way of the definitions below.
#define gVsRecorderVideoListSubStates gVsRecorderVideoListSubStates_header_decl

#include "global.h"

#include "application/vs_recorder/vs_recorder_screens.h"

#pragma force_active on

#undef gVsRecorderVideoListSubStates

// C declares this non-const, but it lives in .rodata
// clang-format off
const VsRecorderScreenFunc gVsRecorderVideoListSubStates[21] = {
    VsRecorder_VideoListInit, VsRecorder_VideoListEnter, VsRecorder_VideoListDownloadList,
    VsRecorder_VideoListShowList, VsRecorder_VideoListSelect, VsRecorder_VideoListExit,
    VsRecorder_VideoListShowDetails, VsRecorder_VideoListDetailsMain, VsRecorder_VideoListToggleProfile,
    VsRecorder_VideoListPlay, VsRecorder_VideoListBackToList, VsRecorder_VideoListShowSlots,
    VsRecorder_VideoListSlotsMain, VsRecorder_VideoListSlotsCancel, VsRecorder_VideoListConfirmOverwrite,
    VsRecorder_VideoListOverwriteMain, VsRecorder_VideoListOverwriteNo, VsRecorder_VideoListSave,
    VsRecorder_VideoListDownloadVideo, VsRecorder_VideoListResume, VsRecorder_VideoListReturnToDetails,
};
// clang-format on
