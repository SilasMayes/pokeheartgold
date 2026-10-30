#include "system_card.h"

#include "global.h"

// The NitroSDK headers below need the types from global.h.
#include <nitro/card.h>
#include <nitro/fs.h>
#include <nitro/hw/ARM9/mmap.h>
#include <nitro/mi.h>
#include <nitro/os.h>

#ifdef SDK_PORT
// libntr backs the DS memory map with host memory: the same locations by name (as Platinum's
// boot.c does)
#define HW_ROM_HEADER_MIRROR   ((void *)HW_MAIN_MEM_SHARED)
#define HW_ROM_HEADER_MIRROR_2 ((void *)HW_CARD_ROM_HEADER)
#define HW_ROM_HEADER_VALID    ((u32 *)(HW_MAIN_MEM_SHARED + 0x0C))
#define HW_ROM_BASE_OFFSET     ((u32 *)HW_ROM_BASE_OFFSET_BUF)
#else
#define HW_ROM_HEADER_MIRROR   ((void *)0x027FF000)
#define HW_ROM_HEADER_MIRROR_2 ((void *)0x027FFA80)
#define HW_ROM_HEADER_VALID    ((u32 *)0x027FF00C)
#define HW_ROM_BASE_OFFSET     ((u32 *)0x027FFC2C)
#endif
#define ROM_GAME_CODE          0x4A414441
#define ROM_MAKER_CODE         0x3130

typedef struct RomHeaderFields {
    u8 pad00[0x0C];
    u32 gameCode;
    u16 makerCode;
    u8 pad12[0x2E];
    u32 fntOffset;
    u32 fntSize;
    u32 fatOffset;
    u32 fatSize;
} RomHeaderFields;

static const char sRomArchiveName[] = "rom";

void SystemCard_InitRomArchive(void) {
    FSArchive *archive;
    RomHeaderFields *header = HW_ROM_HEADER_MIRROR;

    if (!FS_IsAvailable()) {
        OS_Terminate();
        return;
    }

    if (*HW_ROM_HEADER_VALID == 0) {
        CARD_Init();
        MI_CpuCopy8((const void *)HW_ROM_HEADER_BUF, HW_ROM_HEADER_MIRROR, 0x160);
        MI_CpuCopy8((const void *)HW_ROM_HEADER_BUF, HW_ROM_HEADER_MIRROR_2, 0x160);
        *HW_ROM_HEADER_VALID = ROM_GAME_CODE;
    }

    archive = FS_FindArchive(sRomArchiveName, 3);
    archive->fat = header->fatOffset;
    archive->fat_size = header->fatSize;
    archive->fnt = header->fntOffset;
    archive->fnt_size = header->fntSize;
    if (header->gameCode != ROM_GAME_CODE || header->makerCode != ROM_MAKER_CODE) {
        OS_Terminate();
    }
}

void SystemCard_RebootIntoFile(const char *path) {
    FSFile file;

    FS_InitFile(&file);
    if (FS_OpenFile(&file, path)) {
        *HW_ROM_BASE_OFFSET = file.prop.file.top;
        OS_ResetSystem(0);
    }
}
