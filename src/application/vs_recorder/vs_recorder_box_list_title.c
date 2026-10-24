#include "global.h"

#include "application/vs_recorder/vs_recorder_internal.h"

#include "bg_window.h"

// VS Recorder box data view: removes the box list title. Its own translation unit: built at -O2 (Makefile override).

void VsRecorder_RemoveBoxListTitle(VsRecorderWork *work) {
    VsRecorderBoxData *boxData = work->screenWork;
    u32 i = 0;
    Window *window = boxData->windows;

    do {
        ClearWindowTilemapAndCopyToVram(window);
        RemoveWindow(window);
        i++;
        window++;
    } while (i < 1);
}
