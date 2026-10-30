// Port-only heap debugging (not part of the make build). The game's heaps live inside libntr's
// emulated main memory, so the host's sanitizers can't see an allocation overrun its block there.
// With HGSS_HEAP_CHECK=1 in the environment, every Heap_Alloc/Heap_Free first checks the block
// lists of all heaps; the first failed check names the corrupted block and the allocation that
// physically precedes it (usually the one that overran), with the code address that allocated it.

#include "global.h"

#include <stdio.h>
#include <stdlib.h>

#include "port_heap_debug.h"

#define SIG_USED ('UD')
#define SIG_FREE ('FR')

typedef struct PortHeapTag {
    void *caller; // where Heap_Alloc was called
    u32 size;     // what the game asked for
} PortHeapTag;

static int sEnabled = -1;
static void *sLastCaller, *sPrevCaller;
static const char *sLastOp = "start", *sPrevOp = "start";

BOOL PortHeapDebug_Enabled(void) {
    if (sEnabled < 0) {
        const char *env = getenv("HGSS_HEAP_CHECK");
        sEnabled = env != NULL && env[0] == '1';
        if (sEnabled) {
            printf("[heap] checking every allocation (HGSS_HEAP_CHECK=1)\n");
        }
    }
    return sEnabled;
}

void PortHeapDebug_Tag(void *gameHeader, u32 size, void *caller) {
    // gameHeader is the game's MemoryBlock header: its first 12 bytes are filler
    PortHeapTag *tag = gameHeader;
    tag->caller = caller;
    tag->size = size;
}

static BOOL InRange(const void *p, const NNSiFndHeapHead *head) {
    return (const u8 *)p >= (const u8 *)head && (const u8 *)p < (const u8 *)head->heapEnd;
}

static const NNSiFndExpHeapHead *ExpHead(const NNSiFndHeapHead *head) {
    return (const NNSiFndExpHeapHead *)(head + 1);
}

static void Report(int heapIndex, const NNSiFndHeapHead *head, const NNSiFndExpHeapMBlockHead *bad, const char *why) {
    printf("[heap] heap %d (%p-%p): block %p %s, found at %s from %p (the heap was fine at %s from %p)\n",
           heapIndex, (void *)head, head->heapEnd, (const void *)bad, why, sLastOp, sLastCaller, sPrevOp, sPrevCaller);
    // The used block that ends closest below the bad header
    const NNSiFndExpHeapMBlockHead *best = NULL;
    const u8 *bestEnd = NULL;
    for (const NNSiFndExpHeapMBlockHead *b = ExpHead(head)->mbUsedList.head; b != NULL && b != bad && InRange(b, head); b = b->pMBHeadNext) {
        if (b->signature != SIG_USED) {
            break;
        }
        const u8 *end = (const u8 *)(b + 1) + b->blockSize;
        if ((const u8 *)b < (const u8 *)bad && (bestEnd == NULL || end > bestEnd)) {
            best = b;
            bestEnd = end;
        }
    }
    if (best != NULL) {
        const PortHeapTag *tag = (const PortHeapTag *)(best + 1);
        printf("[heap] preceding used block %p (%u bytes, ends %p): game size %u, allocated from %p\n",
               (const void *)best, best->blockSize, (const void *)bestEnd, tag->size, tag->caller);
    }
    fflush(stdout);
    abort();
}

static void CheckList(int heapIndex, const NNSiFndHeapHead *head, const NNSiFndExpHeapMBlockHead *first, u16 signature) {
    const NNSiFndExpHeapMBlockHead *prev = NULL;
    for (const NNSiFndExpHeapMBlockHead *b = first; b != NULL; b = b->pMBHeadNext) {
        if (!InRange(b, head)) {
            Report(heapIndex, head, b, "outside the heap");
        }
        if (b->signature != signature) {
            Report(heapIndex, head, b, "has a bad signature");
        }
        if (b->pMBHeadPrev != prev) {
            Report(heapIndex, head, b, "has a bad back link");
        }
        if ((const u8 *)(b + 1) + b->blockSize > (const u8 *)head->heapEnd) {
            Report(heapIndex, head, b, "runs past the heap end");
        }
        prev = b;
    }
}

void PortHeapDebug_Check(NNSFndHeapHandle *handles, int count, const char *op, void *caller) {
    sPrevOp = sLastOp;
    sPrevCaller = sLastCaller;
    sLastOp = op;
    sLastCaller = caller;
    for (int i = 0; i < count; i++) {
        const NNSiFndHeapHead *head = handles[i];
        if (head == NULL) {
            continue;
        }
        CheckList(i, head, ExpHead(head)->mbUsedList.head, SIG_USED);
        CheckList(i, head, ExpHead(head)->mbFreeList.head, SIG_FREE);
    }
}

// GF_ASSERT is silent on the DS outside of communication (GF_AssertFail only resets when a link is
// up); the port prints each failing call site once, so a bad state shows up where it starts.
// Resolve an address with: gdb -batch -ex "info line *0x<addr minus the load base>" build_linux/main
void PortDebug_AssertFail(void *caller) {
    static void *seen[64];
    static int numSeen;
    for (int i = 0; i < numSeen; i++) {
        if (seen[i] == caller) {
            return;
        }
    }
    if (numSeen < (int)(sizeof(seen) / sizeof(seen[0]))) {
        seen[numSeen++] = caller;
    }
    printf("[assert] GF_ASSERT failed at %p\n", caller);
    fflush(stdout);
}
