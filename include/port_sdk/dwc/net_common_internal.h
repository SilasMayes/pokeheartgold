#ifndef PORT_SDK_DWC_NET_COMMON_INTERNAL_H
#define PORT_SDK_DWC_NET_COMMON_INTERNAL_H

// Port build: the decomp's own reconstruction of this SDK-internal header (lib/include)
// re-declares SDK internals with its own prototypes. libntr is the SDK here and declares all
// of what the game uses from it.
#include <dwc.h>

typedef DWCInetControl NetConnection; // work passed to DWC_InitInetEx
typedef DWCApInfo NetApInfo;

#endif // PORT_SDK_DWC_NET_COMMON_INTERNAL_H
