#ifndef PORT_SDK_PORT_HEAP_DEBUG_H
#define PORT_SDK_PORT_HEAP_DEBUG_H

// Port-only heap checking, see lib/port/heap_debug.c (HGSS_HEAP_CHECK=1)
BOOL PortHeapDebug_Enabled(void);
void PortHeapDebug_Check(NNSFndHeapHandle *handles, int count, const char *op, void *caller);
void PortHeapDebug_Tag(void *gameHeader, u32 size, void *caller);

// src/heap.c: check every heap now, when HGSS_HEAP_CHECK=1 (report names `where` and its caller)
void Heap_PortCheck(const char *where);

// GF_AssertFail on the port: prints the failing function's address (once per call site)
void PortDebug_AssertFail(void *caller);

#endif // PORT_SDK_PORT_HEAP_DEBUG_H
