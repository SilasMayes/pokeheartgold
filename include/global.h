#ifndef POKEHEARTGOLD_GLOBAL_H
#define POKEHEARTGOLD_GLOBAL_H

#include <MSL.h>
#include <nitro.h>
#include <nitro/code16.h>
#include <nnsys.h>
#include <stddef.h>
#include <string.h>

#ifdef SDK_PORT
#include <stdint.h>

#include "port_compat.h" // include/port_sdk: decomp SDK names libntr spells differently
#else
#define PORT_STATIC
#define PORT_CB(type, func) func
#define PORT_RESULT(var, call) call
#define PORT_SIZEOF(type, dsSize) (dsSize)
#define PORT_PARTICLE_HEAP(dsSize) dsSize
#define PORT_HEAP_SIZE(dsSize) dsSize
// Pointer-sized integers for address arithmetic: u32 on the DS (the same type, so the same
// code), 64 bits on the port, where <stdint.h> provides them.
typedef u32 uintptr_t;
typedef s32 intptr_t;
#endif

#include "constants/global.h"

#include "assert.h"
#include "config.h" // MUST COME BEFORE ANY OTHER GAMEFREAK HEADERS
#include "pm_version.h"

#define NELEMS(a) (sizeof(a) / sizeof(*(a)))

typedef struct {
    int x;
    int y;
    int z;
} Vec32;

#define ARRAY_ASSIGN_EX(dest, src, as_type, count)            \
    {                                                         \
        struct tmp {                                          \
            as_type _[count];                                 \
        };                                                    \
        *(struct tmp *)&(dest) = *(const struct tmp *)&(src); \
    }

#define ARRAY_ASSIGN(dest, src) ARRAY_ASSIGN_EX(dest, src, typeof(*(dest)), NELEMS(dest))

#endif // POKEHEARTGOLD_GLOBAL_H
