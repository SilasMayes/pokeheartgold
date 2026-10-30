#ifndef POKEHEARTGOLD_APPLICATION_POKEWALKER_POKEWALKER_IR_WORK_H
#define POKEHEARTGOLD_APPLICATION_POKEWALKER_POKEWALKER_IR_WORK_H

#include "application/pokewalker/pokewalker_ir.h"

// The IR transfer work area as pokewalker_ir_requests.c defines it: four consecutive .bss objects.
// Other files read the same memory through the views in pokewalker_ir_internal.h.

typedef struct PokewalkerIrWorkHeader {
    u16 unk_00;
    u8 unk_02[6];
    u8 *walkerMon;
    u8 unk_0C[4];
    u8 *uploadImage;
    u32 error;
    u32 unk_18;
} PokewalkerIrWorkHeader;

typedef struct PokewalkerIrWorkBuffers {
    OSMessage messages[1];
    PokewalkerIrIdentity *identity;
    PokewalkerIrIdentity *peerIdentity;
    void *unk_28;
    u8 *strollData;
    u8 *records;
    u8 *blocks;
    u8 *status;
    u64 transferStartTick;
    u8 *compressedSizes;
    u8 *compressBuffer;
    u8 *compressedImageSizes;
    u8 *compressedImage;
    u8 *compressedStrollSizes;
    u8 *compressedStroll;
    u8 *compressedRecordSizes;
    u8 *compressedRecords;
} PokewalkerIrWorkBuffers;

typedef struct PokewalkerIrWorkSync {
    OSMutex mutex;
    OSMessageQueue queue;
    u8 command;
    u8 step;
    u8 unk_1E[2];
    u8 *data;
    u8 unk_24[0x12];
    u16 chunk;
} PokewalkerIrWorkSync;

typedef struct PokewalkerIrWorkProgress {
    u16 totalChunks;
    u16 totalChunk;
    u16 totalSize;
    u16 unk_3E;
    u8 buffer[0x74];
} PokewalkerIrWorkProgress;

#endif // POKEHEARTGOLD_APPLICATION_POKEWALKER_POKEWALKER_IR_WORK_H
