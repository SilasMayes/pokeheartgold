// Converted from asm/middleware.s (part 2 of 4) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

#include <nitro/section.h>

#include "global.h"

#include "cps/cps_internal.h"
#include "cps/cps_ssl_internal.h"
#include "dwc/dwc_account_internal.h"
#include "nitrowifi/socl_internal.h"
#include "vct/vct_internal.h"

#pragma force_active on

#pragma section VERSION begin
u8 _version_NINTENDO_WiFi[40] = "[SDK+NINTENDO:WiFi2.1.30003.0709200229]";
#pragma section VERSION end
