// Converted from asm/vs_recorder_data.s (part 12 of 14) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

// The C declarations of these do not match the data (see the notes at each
// definition): keep them out of the way of the definitions below.
#define gVsRecorderSendVideoSubStates    gVsRecorderSendVideoSubStates_header_decl
#define gVsRecorderNumberSearchSubStates gVsRecorderNumberSearchSubStates_header_decl
#define gVsRecorderVideoSearchSubStates  gVsRecorderVideoSearchSubStates_header_decl

#include "global.h"

#include "application/vs_recorder/vs_recorder_screens.h"

#pragma force_active on

#undef gVsRecorderSendVideoSubStates
#undef gVsRecorderNumberSearchSubStates
#undef gVsRecorderVideoSearchSubStates

// C declares this non-const, but it lives in .rodata
// clang-format off
const VsRecorderScreenFunc gVsRecorderVideoSearchSubStates[32] = {
    VsRecorder_VideoSearchInit, VsRecorder_VideoSearchEnter, VsRecorder_VideoSearchShowConditions,
    VsRecorder_VideoSearchConditionsMain, VsRecorder_VideoSearchExit, VsRecorder_VideoSearchOpenCondition,
    VsRecorder_VideoSearchSelectFacility, VsRecorder_VideoSearchClearSpecies,
    VsRecorder_VideoSearchSelectCategory, VsRecorder_VideoSearchSelectSpecies,
    VsRecorder_VideoSearchSelectLocation, VsRecorder_VideoSearchReturnToConditions,
    VsRecorder_VideoSearchRequest, VsRecorder_VideoSearchLeaveConditions, VsRecorder_VideoSearchShowResults,
    VsRecorder_VideoSearchResultsMain, VsRecorder_VideoSearchResultsBack, VsRecorder_VideoSearchShowDetails,
    VsRecorder_VideoSearchDetailsMain, VsRecorder_VideoSearchToggleProfile, VsRecorder_VideoSearchPlay,
    VsRecorder_VideoSearchBackToResults, VsRecorder_VideoSearchShowSlots, VsRecorder_VideoSearchSlotsMain,
    VsRecorder_VideoSearchSlotsCancel, VsRecorder_VideoSearchConfirmOverwrite,
    VsRecorder_VideoSearchOverwriteMain, VsRecorder_VideoSearchOverwriteNo, VsRecorder_VideoSearchSave,
    VsRecorder_VideoSearchDownloadVideo, VsRecorder_VideoSearchResume, VsRecorder_VideoSearchReturnToDetails,
};
// clang-format on

// C declares this non-const, but it lives in .rodata
// clang-format off
const VsRecorderScreenFunc gVsRecorderNumberSearchSubStates[21] = {
    VsRecorder_VideoSearchInit, VsRecorder_VideoSearchEnter, VsRecorder_NumberSearchShowPad,
    VsRecorder_NumberSearchPadMain, VsRecorder_NumberSearchClosePad, VsRecorder_NumberSearchExit,
    VsRecorder_NumberSearchDownloadVideo, VsRecorder_NumberSearchShowDetails,
    VsRecorder_NumberSearchDetailsMain, VsRecorder_NumberSearchToggleProfile, VsRecorder_NumberSearchPlay,
    VsRecorder_NumberSearchExitDetails, VsRecorder_NumberSearchShowSlots, VsRecorder_NumberSearchSlotsMain,
    VsRecorder_NumberSearchSlotsCancel, VsRecorder_NumberSearchConfirmOverwrite,
    VsRecorder_NumberSearchOverwriteMain, VsRecorder_NumberSearchOverwriteNo, VsRecorder_NumberSearchSave,
    VsRecorder_NumberSearchResume, VsRecorder_NumberSearchReturnToDetails,
};
// clang-format on

// C declares this non-const, but it lives in .rodata
// clang-format off
const VsRecorderScreenFunc gVsRecorderSendVideoSubStates[5] = {
    VsRecorder_VideoSearchInit, VsRecorder_VideoSearchEnter, VsRecorder_SendVideoShowCursor,
    VsRecorder_SendVideoUpload, VsRecorder_SendVideoExit,
};
// clang-format on
