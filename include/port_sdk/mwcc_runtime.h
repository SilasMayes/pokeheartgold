#ifndef PORT_SDK_MWCC_RUNTIME_H
#define PORT_SDK_MWCC_RUNTIME_H

// Port build only. The decomp calls a few of mwcc's ARM runtime helpers (_fadd, _fflt,
// _ll_mul, ...) by name to reproduce the original code generation. On ARM a float travels in
// an integer register, so the decomp's prototypes for them mix f32 and u32 freely; on x86-64
// and aarch64 floats and integers are returned in different registers, so each file defines
// static versions with the flavour its own prototype used, from these bit-cast helpers.
// Single-precision IEEE arithmetic rounds the same as mwcc's soft-float routines.

#include <string.h>

static inline u32 MwRt_F32ToBits(f32 value) {
    u32 bits;
    memcpy(&bits, &value, sizeof(bits));
    return bits;
}

static inline f32 MwRt_BitsToF32(u32 bits) {
    f32 value;
    memcpy(&value, &bits, sizeof(value));
    return value;
}

#endif // PORT_SDK_MWCC_RUNTIME_H
