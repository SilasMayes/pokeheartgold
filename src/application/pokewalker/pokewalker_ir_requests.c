// Pokewalker IR transfer work area and the requests that upload data to the Pokewalker (commands 0x32, 0x40
// and 0x52).

#include "global.h"

#include "application/pokewalker/pokewalker_ir.h"
#include "application/pokewalker/pokewalker_ir_work.h"

#ifdef SDK_PORT
#include "application/pokewalker/pokewalker_ir_internal.h"
#endif

#ifdef SDK_PORT
// See pokewalker_ir_internal.h: one object per view, and this file's names for the fields the
// views share on the DS
PokewalkerIrWorkArea gPokewalkerIrWorkArea;
OSMutex gPokewalkerIrSync;
OSMessageQueue gPokewalkerIrMessageQueue;
PokewalkerIrTransfer gPokewalkerIrTransfer;
u8 gPokewalkerIrSendBuffer[0x74];

// The PokewalkerIrWork view of the area (pokewalker_ir.c) must find the same fields
#define PORT_IR_VIEW_CHECK(area, view) \
    _Static_assert(offsetof(PokewalkerIrWorkArea, area) == offsetof(PokewalkerIrWork, view), #view)
PORT_IR_VIEW_CHECK(header.walkerMon, walkerMon);
PORT_IR_VIEW_CHECK(header.uploadImage, uploadImage);
PORT_IR_VIEW_CHECK(header.error, error);
PORT_IR_VIEW_CHECK(buffers.identity, identity);
PORT_IR_VIEW_CHECK(buffers.records, records);
PORT_IR_VIEW_CHECK(buffers.status, status);
PORT_IR_VIEW_CHECK(buffers.transferStartTick, transferStartTick);
PORT_IR_VIEW_CHECK(buffers.compressedStroll, compressedStroll);

#undef gPokewalkerIrWork
#undef gPokewalkerIrBuffers
#define gPokewalkerIrWork     (gPokewalkerIrWorkArea.header)
#define gPokewalkerIrBuffers  (gPokewalkerIrWorkArea.buffers)
#define gPokewalkerIrSync     gPokewalkerIrTransfer // .command, .step
#define gPokewalkerIrProgress gPokewalkerIrTransfer // .totalSize, .totalChunk, .totalChunks
#else
PokewalkerIrWorkHeader gPokewalkerIrWork;
PokewalkerIrWorkBuffers gPokewalkerIrBuffers;
PokewalkerIrWorkSync gPokewalkerIrSync;
PokewalkerIrWorkProgress gPokewalkerIrProgress;
#endif

void PokewalkerIr_RequestUpload(u8 *uploadImage, u8 *strollData, u8 *records) {
    gPokewalkerIrWork.uploadImage = uploadImage;
    gPokewalkerIrBuffers.strollData = strollData;
    gPokewalkerIrBuffers.records = records;
    gPokewalkerIrSync.command = 0x32;
    gPokewalkerIrSync.step = 0x20;
    PokewalkerIr_BeginTransfer(NULL, 0, 0xD4C);
    gPokewalkerIrProgress.totalSize = 0xB732;
    gPokewalkerIrProgress.totalChunk = 0;
    gPokewalkerIrProgress.totalChunks = (gPokewalkerIrProgress.totalSize + 0x7F) / 0x80;
    if (gPokewalkerIrBuffers.compressBuffer != NULL) {
        gPokewalkerIrBuffers.compressedImageSizes = gPokewalkerIrBuffers.compressedSizes;
        gPokewalkerIrBuffers.compressedImage = gPokewalkerIrBuffers.compressBuffer;
        PokewalkerIr_CompressBlocks(gPokewalkerIrWork.uploadImage, gPokewalkerIrBuffers.compressedImage, 0x8C50, gPokewalkerIrBuffers.compressedImageSizes);
        gPokewalkerIrBuffers.compressedStrollSizes = gPokewalkerIrBuffers.compressedSizes + 0x119;
        gPokewalkerIrBuffers.compressedStroll = gPokewalkerIrBuffers.compressBuffer + 0x8C80;
        PokewalkerIr_CompressBlocks(gPokewalkerIrBuffers.strollData, gPokewalkerIrBuffers.compressedStroll, 0x28BE, gPokewalkerIrBuffers.compressedStrollSizes);
        gPokewalkerIrBuffers.compressedRecordSizes = gPokewalkerIrBuffers.compressedStrollSizes + 0x52;
        gPokewalkerIrBuffers.compressedRecords = gPokewalkerIrBuffers.compressedStroll + 0x2900;
        PokewalkerIr_CompressBlocks(gPokewalkerIrBuffers.records, gPokewalkerIrBuffers.compressedRecords, 0x224, gPokewalkerIrBuffers.compressedRecordSizes);
    }
}

void PokewalkerIr_RequestReceive(u8 *walkerMon, u8 *status, u8 *blocks, u8 *records) {
    gPokewalkerIrWork.walkerMon = walkerMon;
    gPokewalkerIrBuffers.status = status;
    gPokewalkerIrBuffers.blocks = blocks;
    gPokewalkerIrBuffers.records = records;
    gPokewalkerIrSync.command = 0x40;
    gPokewalkerIrSync.step = 0x20;
    PokewalkerIr_BeginTransfer(NULL, 0, 0xD4C);
    gPokewalkerIrProgress.totalSize = 0x2BCA;
    gPokewalkerIrProgress.totalChunk = 0;
    gPokewalkerIrProgress.totalChunks = (gPokewalkerIrProgress.totalSize + 0x7F) / 0x80;
}

void PokewalkerIr_RequestSendStroll(u8 *strollData, u8 *records, u8 *status, u8 *blocks) {
    gPokewalkerIrBuffers.strollData = strollData;
    gPokewalkerIrBuffers.records = records;
    gPokewalkerIrBuffers.status = status;
    gPokewalkerIrBuffers.blocks = blocks;
    gPokewalkerIrSync.command = 0x52;
    gPokewalkerIrSync.step = 0x20;
    PokewalkerIr_BeginTransfer(NULL, 0, 0xD4C);
    gPokewalkerIrProgress.totalSize = 0x382E;
    gPokewalkerIrProgress.totalChunk = 0;
    gPokewalkerIrProgress.totalChunks = (gPokewalkerIrProgress.totalSize + 0x7F) / 0x80;
    if (gPokewalkerIrBuffers.compressBuffer != NULL) {
        gPokewalkerIrBuffers.compressedStrollSizes = gPokewalkerIrBuffers.compressedSizes + 0x119;
        gPokewalkerIrBuffers.compressedStroll = gPokewalkerIrBuffers.compressBuffer + 0x8C80;
        PokewalkerIr_CompressBlocks(gPokewalkerIrBuffers.strollData, gPokewalkerIrBuffers.compressedStroll, 0x28BE, gPokewalkerIrBuffers.compressedStrollSizes);
        gPokewalkerIrBuffers.compressedRecordSizes = gPokewalkerIrBuffers.compressedStrollSizes + 0x52;
        gPokewalkerIrBuffers.compressedRecords = gPokewalkerIrBuffers.compressedStroll + 0x2900;
        PokewalkerIr_CompressBlocks(gPokewalkerIrBuffers.records, gPokewalkerIrBuffers.compressedRecords, 0x224, gPokewalkerIrBuffers.compressedRecordSizes);
    }
}
