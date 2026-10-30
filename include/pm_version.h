#ifndef POKEHEARTGOLD_PM_VERSION_H
#define POKEHEARTGOLD_PM_VERSION_H

#include <nitro.h>

#ifdef SDK_PORT
extern u8 gGameVersion; // the loaded ROM's (IPKE: HeartGold, IPGE: SoulSilver)
void PortGameVersion_Init(void);
#else
extern const u8 gGameVersion;
#endif
extern const u8 gGameLanguage;

#endif // POKEHEARTGOLD_PM_VERSION_H
