/* Stand-in SDL2 build configuration for the aarch64 compile check (cross_aarch64_check.ini).
 * Only libntr's headers see it, and only declarations matter; nothing is linked. */
#ifndef PORT_AARCH64_CHECK_SDL_CONFIG_H
#define PORT_AARCH64_CHECK_SDL_CONFIG_H

#define SIZEOF_VOIDP 8
#define HAVE_STDINT_H 1
#define HAVE_STDIO_H 1
#define HAVE_STDLIB_H 1
#define HAVE_STDARG_H 1
#define HAVE_STRING_H 1
#define HAVE_INTTYPES_H 1
#define HAVE_MATH_H 1
#define HAVE_LIMITS_H 1
#define HAVE_SYS_TYPES_H 1
#define HAVE_LIBC 1
#define SDL_THREAD_PTHREAD 1

#endif
