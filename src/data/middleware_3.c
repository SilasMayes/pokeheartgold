// Converted from asm/middleware.s (part 3 of 4) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

// The C declarations of these do not match the data (see the notes at each
// definition): keep them out of the way of the definitions below.
#define _version_UBIQUITOUS_CPS _version_UBIQUITOUS_CPS_header_decl
#define _version_UBIQUITOUS_SSL _version_UBIQUITOUS_SSL_header_decl

#include <nitro/section.h>

#include "global.h"

#include "cps/cps_internal.h"
#include "cps/cps_ssl_internal.h"
#include "dwc/dwc_account_internal.h"
#include "nitrowifi/socl_internal.h"
#include "vct/vct_internal.h"

#pragma force_active on

#undef _version_UBIQUITOUS_CPS
#undef _version_UBIQUITOUS_SSL

#pragma section VERSION begin
char _version_Abiosso_libVCT[28] = "[SDK+Abiosso:libVCT 1.3.1]";
#pragma section VERSION end

#pragma section VERSION begin
// C declares this const, but it lives in .version
char _version_UBIQUITOUS_CPS[24] = "[SDK+UBIQUITOUS:CPS]";
#pragma section VERSION end

#pragma section VERSION begin
// C declares this const, but it lives in .version
char _version_UBIQUITOUS_SSL[24] = "[SDK+UBIQUITOUS:SSL]";
#pragma section VERSION end
