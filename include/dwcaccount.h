#ifndef POKEHEARTGOLD_DWCACCOUNT_H
#define POKEHEARTGOLD_DWCACCOUNT_H

#include "global.h"

#ifdef SDK_PORT
#include <dwc.h>
#else
// Declared without the user data the DS code left in r0 (see wifi_club_app.c)
BOOL DWC_CheckValidConsole(void);
BOOL DWC_CheckHasProfile(void);
#endif

#endif // POKEHEARTGOLD_DWCACCOUNT_H
