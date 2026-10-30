#include "nitrocrypto_bn.h"

// RC4 stream cipher: en-/decrypts `length` bytes with the key state in `context`
// (bytes i and j at +0 and +1, the 256-byte permutation from +4).

#ifdef SDK_PORT
#include "nitrocrypto_rc4.h"

// Port build: C version of the ARM routine below (same context layout and results).
void CRYPTO_RC4Encrypt(void *context, const void *in, u32 length, void *out) {
    u8 *ctx = context;
    u8 *s = ctx + 4;
    const u8 *src = in;
    u8 *dst = out;
    u8 i = ctx[0];
    u8 j = ctx[1];

    while (length-- != 0) {
        u8 x, y;
        i++;
        x = s[i];
        j += x;
        y = s[j];
        s[i] = y;
        s[j] = x;
        *dst++ = *src++ ^ s[(u8)(x + y)];
    }
    ctx[0] = i;
    ctx[1] = j;
}
#else
// clang-format off
asm void CRYPTO_RC4Encrypt(void *context, const void *in, u32 length, void *out)
{
    stmdb sp!, {r4, r5, r6, r7, r8, r9, lr}
    ldrb r7, [r0]
    ldrb r6, [r0, #1]
    add r0, r0, #4
    mov lr, #0x1000000
    add r7, lr, r7, lsl #24
    mov r6, r6, lsl #0x18
    ldrb r9, [r0, r7, lsr #24]
    subs r2, r2, #1
    bmi @L022370CC
@L02237094:
    add r6, r6, r9, lsl #24
    subs r2, r2, #1
    ldrb r8, [r0, r6, lsr #24]
    ldrb r5, [r1], #1
    strb r8, [r0, r7, lsr #24]
    strb r9, [r0, r6, lsr #24]
    add r4, r9, r8
    and r4, r4, #0xff
    add r7, r7, lr
    ldrb r4, [r0, r4]
    ldrb r9, [r0, r7, lsr #24]
    eor r5, r5, r4
    strb r5, [r3], #1
    bge @L02237094
@L022370CC:
    sub r7, r7, lr
    mov r7, r7, lsr #0x18
    mov r6, r6, lsr #0x18
    strb r7, [r0, #-4]
    strb r6, [r0, #-3]
    ldmia sp!, {r4, r5, r6, r7, r8, r9, pc}
}
// clang-format on
#endif // SDK_PORT
