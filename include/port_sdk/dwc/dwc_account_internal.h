#ifndef PORT_SDK_DWC_DWC_ACCOUNT_INTERNAL_H
#define PORT_SDK_DWC_DWC_ACCOUNT_INTERNAL_H

// Port build: the decomp's own reconstruction of this SDK-internal header (lib/include)
// re-declares SDK internals with its own prototypes. libntr is the SDK here and declares all
// of what the game uses from it.
#include <dwc.h>

// Friend roster entries and the user's login data (12 and 64 bytes, kept in the save)
typedef DWCFriendData DwcAccData;
typedef DWCUserData DwcUserData;

#endif // PORT_SDK_DWC_DWC_ACCOUNT_INTERNAL_H
