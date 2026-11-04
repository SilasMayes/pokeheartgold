// A save written by the port before its layout matched the DS's is rewritten in the DS layout when the
// game starts, before the save code reads it.
//
// Until then the port aligned 64-bit save members to 8 bytes (the DS's compiler aligns them to 4),
// which padded a party Pokémon to 240 bytes instead of 236 and moved every chunk after it, and its
// CRC-16 used libntr's reflected 0xA001 table in the CCITT update the game does (the game's SDK makes
// that the 0x1021 table). Such a save is recognised by its block footers at the old offsets with the
// old CRC. Each of the nine structures that changed is copied field by field with the runs in
// save_migrate_v1_runs.h (generated from the two builds' DWARF); the other chunks are copied as they
// are; the per-chunk CRCs some chunks keep after themselves, the block footers and the battle video
// footers get the DS's CRC. A slot with a valid DS-layout block is left alone, so this runs once.
#include "global.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "math_util.h"
#include "save.h"
#include "save_arrays.h"

#include "save_migrate_v1_runs.h"

BOOL PortSave_FlashLoad(u32 offset, void *data, u32 size);
s32 PortSave_FlashWrite(u32 offset, void *data, u32 size);

#define SLOT_SIZE  0x40000
#define SLOT_BYTES (SAVE_PAGE_MAX * SAVE_SECTOR_SIZE)

typedef struct ChunkLayout {
    u32 offset[SAVE_BLOCK_NUM];
    u32 blockOffset[2];
    u32 blockSize[2];
} ChunkLayout;

static MATHCRC16Table sOldTable;

static u16 OldCRC(const void *data, u32 size) {
    return MATH_CalcCRC16CCITT(&sOldTable, data, size);
}

static const PortSaveChangedStruct *FindChanged(int chunk) {
    for (int i = 0; i < (int)NELEMS(sChangedStructs); i++) {
        if (sChangedStructs[i].chunk == chunk) {
            return &sChangedStructs[i];
        }
    }
    return NULL;
}

static u32 ChunkSize(int idx, BOOL old) {
    u32 size = gSaveChunkHeaders[idx].sizeFunc();
    const PortSaveChangedStruct *changed = FindChanged(idx);
    if (old && changed != NULL) {
        GF_ASSERT(size == changed->newSize);
        size = changed->oldSize;
    }
    return size;
}

static u32 RoundUp4(u32 size) {
    return (size + 3) & ~3;
}

// As SaveData_InitSubstructs and SaveData_InitSlotSpecs lay the chunks out
static void ComputeLayout(ChunkLayout *layout, BOOL old) {
    u32 adrs = 0;
    for (int i = 0; i < gNumSaveChunkHeaders; i++) {
        layout->offset[i] = adrs;
        adrs += RoundUp4(ChunkSize(i, old)) + 4;
        BOOL last = i == gNumSaveChunkHeaders - 1;
        if (last || gSaveChunkHeaders[i].block != gSaveChunkHeaders[i + 1].block) {
            adrs += sizeof(struct SaveChunkFooter);
            if (!last && adrs % 0x100 != 0) {
                adrs += 0x100 - adrs % 0x100;
            }
        }
    }
    adrs = 0;
    for (int b = 0; b < 2; b++) {
        u32 size = 0;
        for (int i = 0; i < gNumSaveChunkHeaders; i++) {
            if (gSaveChunkHeaders[i].block == (u32)b) {
                size += RoundUp4(ChunkSize(i, old)) + 4;
            }
        }
        size += sizeof(struct SaveChunkFooter);
        layout->blockOffset[b] = adrs;
        layout->blockSize[b] = size;
        adrs += size;
        if (adrs % 0x100 != 0) {
            adrs += 0x100 - adrs % 0x100;
        }
    }
}

static BOOL BlockValid(const u8 *slot, const ChunkLayout *layout, int b, BOOL old) {
    const u8 *block = slot + layout->blockOffset[b];
    u32 size = layout->blockSize[b];
    const struct SaveChunkFooter *footer = (const struct SaveChunkFooter *)(block + size - sizeof(struct SaveChunkFooter));
    if (layout->blockOffset[b] + size > SLOT_BYTES || footer->magic != SAVE_CHUNK_MAGIC || footer->size != size || footer->slot != b) {
        return FALSE;
    }
    u32 crcSize = size - sizeof(struct SaveChunkFooter);
    return footer->crc == (old ? OldCRC(block, crcSize) : GF_CalcCRC16(block, crcSize));
}

static void CopyStruct(const PortSaveChangedStruct *changed, u8 *dest, const u8 *src) {
    for (int i = 0; i < changed->numRuns; i++) {
        const PortSaveRun *run = &changed->runs[i];
        memcpy(dest + run->newOffset, src + run->oldOffset, run->length);
    }
}

static void ConvertBlock(u8 *dest, const u8 *src, const ChunkLayout *oldLayout, const ChunkLayout *newLayout, int b) {
    for (int i = 0; i < gNumSaveChunkHeaders; i++) {
        if (gSaveChunkHeaders[i].block != (u32)b) {
            continue;
        }
        const u8 *from = src + oldLayout->offset[i] - oldLayout->blockOffset[b];
        u8 *to = dest + newLayout->offset[i] - newLayout->blockOffset[b];
        u32 oldSize = RoundUp4(ChunkSize(i, TRUE));
        u32 newSize = RoundUp4(ChunkSize(i, FALSE));
        const PortSaveChangedStruct *changed = FindChanged(i);
        if (changed != NULL) {
            CopyStruct(changed, to, from);
        } else {
            memcpy(to, from, newSize);
        }
        // The 4 bytes after a chunk: some chunks keep their CRC-16 there (SaveSubstruct_UpdateCRC)
        memcpy(to + newSize, from + oldSize, 4);
        u16 storedCRC;
        memcpy(&storedCRC, from + oldSize, sizeof(storedCRC));
        if (storedCRC == OldCRC(from, oldSize)) {
            u16 crc = GF_CalcCRC16(to, newSize);
            memcpy(to + newSize, &crc, sizeof(crc));
        }
    }
    const struct SaveChunkFooter *oldFooter = (const struct SaveChunkFooter *)(src + oldLayout->blockSize[b] - sizeof(struct SaveChunkFooter));
    struct SaveChunkFooter *footer = (struct SaveChunkFooter *)(dest + newLayout->blockSize[b] - sizeof(struct SaveChunkFooter));
    footer->count = oldFooter->count;
    footer->size = newLayout->blockSize[b];
    footer->magic = SAVE_CHUNK_MAGIC;
    footer->slot = b;
    footer->crc = GF_CalcCRC16(dest, newLayout->blockSize[b] - sizeof(struct SaveChunkFooter));
}

// The battle videos sit in sectors of their own: only their size, so their footer's place, changed
static void ConvertBattleVideos(void) {
    const PortSaveChangedStruct *changed = FindChanged(-1);
    u8 *src = malloc(changed->oldSize + sizeof(struct SaveArrayFooter));
    u8 *dest = malloc(changed->newSize + sizeof(struct SaveArrayFooter));
    for (int idx = 0; idx < gNumExtraSaveChunkHeaders; idx++) {
        const struct ExtraSaveChunkHeader *hdr = &gExtraSaveChunkHeaders[idx];
        if (hdr->sizeFunc() != changed->newSize) {
            continue;
        }
        for (int copy = 0; copy < 2; copy++) {
            u32 at = (hdr->sector + copy * 64) * SAVE_SECTOR_SIZE;
            if (!PortSave_FlashLoad(at, src, changed->oldSize + sizeof(struct SaveArrayFooter))) {
                continue;
            }
            struct SaveArrayFooter *footer = (struct SaveArrayFooter *)(src + changed->oldSize);
            if (footer->magic != SAVE_CHUNK_MAGIC || footer->size != changed->oldSize || footer->idx != idx
                || footer->crc != OldCRC(src, changed->oldSize + offsetof(struct SaveArrayFooter, crc))) {
                continue;
            }
            memset(dest, 0, changed->newSize + sizeof(struct SaveArrayFooter));
            CopyStruct(changed, dest, src);
            struct SaveArrayFooter *newFooter = (struct SaveArrayFooter *)(dest + changed->newSize);
            newFooter->magic = SAVE_CHUNK_MAGIC;
            newFooter->saveno = footer->saveno;
            newFooter->size = changed->newSize;
            newFooter->idx = idx;
            newFooter->crc = GF_CalcCRC16(dest, changed->newSize + offsetof(struct SaveArrayFooter, crc));
            PortSave_FlashWrite(at, dest, changed->newSize + sizeof(struct SaveArrayFooter));
            printf("Save: battle video %d (copy %d) converted to the DS layout\n", idx, copy);
        }
    }
    free(src);
    free(dest);
}

void PortSave_MigrateV1(void) {
    ChunkLayout *oldLayout = malloc(sizeof(ChunkLayout));
    ChunkLayout *newLayout = malloc(sizeof(ChunkLayout));
    u8 *slot = malloc(SLOT_BYTES);
    u8 *block = malloc(SLOT_BYTES);
    BOOL converted = FALSE;

    MATHi_CRC16InitTableRev(&sOldTable, 0xA001);
    ComputeLayout(oldLayout, TRUE);
    ComputeLayout(newLayout, FALSE);

    for (int s = 0; s < 2; s++) {
        if (!PortSave_FlashLoad(s * SLOT_SIZE, slot, SLOT_BYTES)) {
            continue;
        }
        if (BlockValid(slot, newLayout, 0, FALSE) || BlockValid(slot, newLayout, 1, FALSE)) {
            continue; // already the DS layout
        }
        for (int b = 0; b < 2; b++) {
            if (!BlockValid(slot, oldLayout, b, TRUE)) {
                continue;
            }
            memset(block, 0, newLayout->blockSize[b]);
            ConvertBlock(block, slot + oldLayout->blockOffset[b], oldLayout, newLayout, b);
            PortSave_FlashWrite(s * SLOT_SIZE + newLayout->blockOffset[b], block, newLayout->blockSize[b]);
            printf("Save: slot %d block %d converted to the DS layout\n", s, b);
            converted = TRUE;
        }
    }
    if (converted) {
        ConvertBattleVideos();
    }

    free(block);
    free(slot);
    free(newLayout);
    free(oldLayout);
}
