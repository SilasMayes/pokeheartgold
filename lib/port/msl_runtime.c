// Port build only (not part of the DS build, which links the real MSL and mwcc runtime).
// The few Metrowerks C library and runtime entry points the game code calls by name.

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#include <nitro.h>

// MSL's assert() back end; the GameSpy chat code calls it directly
void __msl_assertion_failed(const char *condition, const char *file, const char *function, int line) {
    OS_TPrintf("assertion failed: %s (%s:%d, %s)\n", condition, file, line, function);
    abort();
}

// MSL extension: case-insensitive strncmp
int strnicmp(const char *a, const char *b, size_t n) {
    return strncasecmp(a, b, n);
}

// mwcc's signed division helper, called by name to reproduce the original code
s32 _s32_div_f(s32 dividend, s32 divisor) {
    return dividend / divisor;
}

// MSL's ctype tables: tolower for the C locale, indexed by an unsigned char
unsigned char __lower_mapC[256];

static void PortMsl_InitLowerMap(void) __attribute__((constructor));
static void PortMsl_InitLowerMap(void) {
    for (int i = 0; i < 256; i++) {
        __lower_mapC[i] = (i < 128) ? (unsigned char)tolower(i) : (unsigned char)i;
    }
}
