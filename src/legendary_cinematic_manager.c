#include "legendary_cinematic_manager.h"

#include "global.h"

#include "heap.h"
#include "legendary_cinematic.h"
#include "legendary_cinematic_internal.h"
#include "overlay_manager.h"

static int (*const sLegendaryCinematicScripts[])(void *) = {
    ScriptCinematic_HoOh,
    ScriptCinematic_Lugia,
    ScriptCinematic_Arceus,
};

BOOL LegendaryCinematic_Init(OverlayManager *man, int *state) {
    LegendaryCinematic *cinematic;

    Heap_Create(HEAP_ID_3, HEAP_ID_153, 0x80000);
    cinematic = OverlayManager_CreateAndGetData(man, sizeof(LegendaryCinematic), HEAP_ID_153);
    MI_CpuFill8(cinematic, 0, sizeof(LegendaryCinematic));
    cinematic->args = OverlayManager_GetArgs(man);
    return TRUE;
}

BOOL LegendaryCinematic_Main(OverlayManager *man, int *state) {
    LegendaryCinematic *cinematic = OverlayManager_GetData(man);

    return !sLegendaryCinematicScripts[cinematic->args->scene](cinematic);
}

BOOL LegendaryCinematic_Exit(OverlayManager *man, int *state) {
    OverlayManager_FreeData(man);
    Heap_Destroy(HEAP_ID_153);
    return TRUE;
}
