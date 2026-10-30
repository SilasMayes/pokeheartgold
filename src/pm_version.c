#include "global.h"

#include "pm_version.h"

#ifdef SDK_PORT
#ifdef HEARTGOLD
u8 gGameVersion = VERSION_HEARTGOLD;
#else
u8 gGameVersion = VERSION_SOULSILVER;
#endif

// The header libntr loaded keeps the ROM's own game code when it is one this build runs
// (libntr's card_game_code list): its third letter is K for HeartGold (IPKE), G for SoulSilver
// (IPGE). Anything else keeps the build's default.
void PortGameVersion_Init(void) {
    const CARDRomHeader *header = (const CARDRomHeader *)HW_ROM_HEADER_BUF; // libntr reads header.bin there
    const char *code = (const char *)&header->game_code;
    if (code[0] == 'I' && code[1] == 'P' && code[2] == 'K') {
        gGameVersion = VERSION_HEARTGOLD;
    } else if (code[0] == 'I' && code[1] == 'P' && code[2] == 'G') {
        gGameVersion = VERSION_SOULSILVER;
    }
}
#else
const u8 gGameVersion = GAME_VERSION;
#endif
const u8 gGameLanguage = GAME_LANGUAGE;
