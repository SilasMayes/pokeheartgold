#ifndef PORT_SDK_VCT_VCT_SESSION_H
#define PORT_SDK_VCT_VCT_SESSION_H

// Port build: libvct is the voice chat library here. The game keeps its names for the session
// and the init arguments; InitArgs has VCTConfig's field types in the same order (on any
// pointer size), so it is handed to libvct as one.

#include <vct.h>

typedef VCTSession VctSession;

typedef void (*VctCallback)(u32 aid, u32 event, VctSession *session, void *context);

typedef struct InitArgs {
    VctSession *data;
    u32 count;
    s32 mode;
    u8 id;
    u8 pad[3];
    void *buffer; // 32-byte aligned
    u32 size;
    VctCallback callback;
    void *arg;
} InitArgs;

#define VCT_Init(args) VCT_Init((VCTConfig *)(args))

#endif // PORT_SDK_VCT_VCT_SESSION_H
