// Converted from asm/middleware.s (part 1 of 4) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

// The C declarations of these do not match the data (see the notes at each
// definition): keep them out of the way of the definitions below.
#define _version_NINTENDO_DWC _version_NINTENDO_DWC_header_decl

#include <nitro/section.h>

#include "global.h"

#include "cps/cps_internal.h"
#include "cps/cps_ssl_internal.h"
#include "dwc/dwc_account_internal.h"
#include "nitrowifi/socl_internal.h"
#include "vct/vct_internal.h"

#pragma force_active on

#undef _version_NINTENDO_DWC

#pragma section VERSION begin
// C declares this const, but it lives in .version
char _version_NINTENDO_DWC[56] __attribute__((aligned(4))) = "[SDK+NINTENDO:DWC2.2.30008.080630.1906_DWC_2_2_PLUS8]";
#pragma section VERSION end
