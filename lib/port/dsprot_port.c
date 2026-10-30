// Port build only (the DS build links lib/dsprot).
// DS Protect, the anti-piracy library HGSS checks in the Pokédex: always report a genuine
// cartridge on real hardware. The Detect* checks find nothing and call no callback; the
// Detect*Not* checks pass and call theirs, exactly what a retail card does.

#include <nitro/types.h>

#include <dsprot.h>

static u32 DSProtPort_Pass(void *callback) {
    if (callback != NULL) {
        ((void (*)(void))callback)();
    }
    return 1;
}

u32 DSProt_DetectFlashcart(void *callback) {
    (void)callback;
    return 0;
}

u32 DSProt_DetectNotFlashcart(void *callback) {
    return DSProtPort_Pass(callback);
}

u32 DSProt_DetectEmulator(void *callback) {
    (void)callback;
    return 0;
}

u32 DSProt_DetectNotEmulator(void *callback) {
    return DSProtPort_Pass(callback);
}

u32 DSProt_DetectDummy(void *callback) {
    (void)callback;
    return 0;
}

u32 DSProt_DetectNotDummy(void *callback) {
    return DSProtPort_Pass(callback);
}
