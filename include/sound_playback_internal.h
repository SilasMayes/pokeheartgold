#ifndef POKEHEARTGOLD_SOUND_PLAYBACK_INTERNAL_H
#define POKEHEARTGOLD_SOUND_PLAYBACK_INTERNAL_H

#include "global.h"

BOOL PlayBGMDirect(u16 seqNo);
void StopBGMSEAndCry(void);
BOOL PlaySEOnPlayer(u16 seqNo, int playerNo);
BOOL PlaySE_SetVolume(u16 seqNo, u16 volume);
void SetSeqTrackPan(u16 seqNo, u32 trackMask, int pan);
u32 GF_SndCountPlayingSeqOnPlayer(u32 playerNo);
void SetPlayerPan(int playerNo, int pan);
void SetAllSEPan(int pan);
BOOL IsFanfarePlayingOrWaiting(void);

#endif // POKEHEARTGOLD_SOUND_PLAYBACK_INTERNAL_H
