#include "error_handling.h"

#include "global.h"

#include "error_message_reset.h"
#include "comm_state.h"

#ifdef SDK_PORT
#include "port_heap_debug.h"
#endif

void GF_AssertFail(void) {
#ifdef SDK_PORT
    PortDebug_AssertFail(__builtin_return_address(0));
#endif
    if (!CommState_Exists()) {
        return;
    }

    if (OS_GetProcMode() != OS_PROCMODE_IRQ) {
        PrintErrorMessageAndReset();
    }
}
