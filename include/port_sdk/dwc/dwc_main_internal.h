#ifndef PORT_SDK_DWC_DWC_MAIN_INTERNAL_H
#define PORT_SDK_DWC_DWC_MAIN_INTERNAL_H

// Port build: the decomp's own reconstruction of this SDK-internal header (lib/include)
// re-declares SDK internals with its own prototypes. libntr is the SDK here and declares all
// of what the game uses from it.
#include <dwc.h>

// Work the game hands to DWC_InitFriendsMatch; libntrdwc's layout (it holds pointers)
typedef DWCFriendsMatchControl DwcControl;
typedef DWCMatchOptMinComplete DwcMatchOptMinComplete;

#endif // PORT_SDK_DWC_DWC_MAIN_INTERNAL_H
