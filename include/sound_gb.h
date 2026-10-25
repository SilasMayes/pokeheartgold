#ifndef POKEHEARTGOLD_SOUND_GB_H
#define POKEHEARTGOLD_SOUND_GB_H

#include "global.h"

void Sound_SetKeepPlayingCries(u8 value);
void Sound_SetChatotRecordingDisabled(u8 value);
BOOL GF_SndReadSeqVariable(u16 seqNo, u32 variable, s16 *value);
void Sound_ApplyFootstepVariation(u16 seqNo);
int Sound_IsSelectSEMuted(void);
u16 GBSounds_GetGBSeqNoByDSSeqNo(u16 seqNo);
u16 GBSounds_GetDSSeqNoByGBSeqNo(u16 seqNo);
void GBSounds_SetAllocatableChannels(void);
void Sound_SetFieldBGMStopOnce(BOOL enabled);

#endif // POKEHEARTGOLD_SOUND_GB_H
