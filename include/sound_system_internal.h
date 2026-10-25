#ifndef POKEHEARTGOLD_SOUND_SYSTEM_INTERNAL_H
#define POKEHEARTGOLD_SOUND_SYSTEM_INTERNAL_H

#include "global.h"

#include "sound.h"

struct NNSSndArcBankInfo;

// Fields of the sound work reached through GF_SdatGetAttrPtr
enum SoundWorkAttr {
    SOUND_ATTR_WAVE_OUT_14_HANDLE,
    SOUND_ATTR_WAVE_OUT_15_HANDLE,
    SOUND_ATTR_QUEUED_BANK_INFO,
    SOUND_ATTR_BGM_DISABLED = 5,
    SOUND_ATTR_CRY_QUEUE,
    SOUND_ATTR_FADE_TIMER,
    SOUND_ATTR_AFTER_FADE_DELAY_TIMER,
    SOUND_ATTR_QUEUED_SEQ_FADE_IN,
    SOUND_ATTR_CURRENT_SEQ,
    SOUND_ATTR_QUEUED_SEQ,
    SOUND_ATTR_FIELD_PLAYER_PAUSED,
    SOUND_ATTR_BGM_PLAYER_PAUSED,
    SOUND_ATTR_AFTER_FANFARE_WAIT_TIMER,
    SOUND_ATTR_REVERSED_CRY_STARTED,
    SOUND_ATTR_WAVE_OUT_14_ALLOCATED,
    SOUND_ATTR_WAVE_OUT_15_ALLOCATED,
    SOUND_ATTR_USE_CHORUS,
    SOUND_ATTR_RELOAD_FIELD_SEQ,
    SOUND_ATTR_PRIMARY_SCENE = 21,
    SOUND_ATTR_SECONDARY_SCENE,
    SOUND_ATTR_SAVED_HEAP_LEVEL_0,
    SOUND_ATTR_SAVED_HEAP_LEVEL_1,
    SOUND_ATTR_SAVED_HEAP_LEVEL_2,
    SOUND_ATTR_SAVED_HEAP_LEVEL_3,
    SOUND_ATTR_SAVED_HEAP_LEVEL_4,
    SOUND_ATTR_SAVED_HEAP_LEVEL_5,
    SOUND_ATTR_SAVED_HEAP_LEVEL_6,
    SOUND_ATTR_CHATOT_PLAYING,
    SOUND_ATTR_CHATOT_FORCE_DEFAULT_CRY,
    SOUND_ATTR_FIELD_SEQ,
    SOUND_ATTR_REVERSED_WAVE_BUFFER = 34,
    SOUND_ATTR_CRY_STOP_TASK,
    SOUND_ATTR_MY_CHATOT,
    SOUND_ATTR_QUEUED_CRY_PATTERN_0 = 41,
    SOUND_ATTR_QUEUED_CRY_PAN_0,
    SOUND_ATTR_QUEUED_CRY_VOLUME_0,
    SOUND_ATTR_QUEUED_CRY_HEAP_ID_0,
    SOUND_ATTR_QUEUED_CRY_SPECIES_0,
    SOUND_ATTR_QUEUED_CRY_DELAY_0,
    SOUND_ATTR_QUEUED_CRY_PATTERN_1,
    SOUND_ATTR_QUEUED_CRY_PAN_1,
    SOUND_ATTR_QUEUED_CRY_VOLUME_1,
    SOUND_ATTR_QUEUED_CRY_HEAP_ID_1,
    SOUND_ATTR_QUEUED_CRY_SPECIES_1,
    SOUND_ATTR_QUEUED_CRY_DELAY_1,
    SOUND_ATTR_KEEP_PLAYING_CRIES,
    SOUND_ATTR_CHATOT_RECORDING_DISABLED,
    SOUND_ATTR_FOOTSTEP_VARIATION,
    SOUND_ATTR_SELECT_SE_MUTED,
    SOUND_ATTR_GB_SOUNDS_ENABLED,
    SOUND_ATTR_PLAYING_GB_SEQ,
};

typedef struct SoundSystemFlags {
    u8 micSampling;       // auto sampling started by GF_MIC_StartAutoSampling (restarted when the lid opens)
    BOOL fieldBGMStopped; // the field BGM was stopped once for a reload
    BOOL mono;
    BOOL fieldBGMStopOnce; // stop the field BGM only on the first reload
} SoundSystemFlags;

extern SoundSystemFlags gSoundSystemFlags;

void Sound_ClearBGMPauseFlags(void);
int GF_NNS_SndPlayerGetSeqNo(NNSSndHandle *handle);
int GF_GetBankBySeqNo(int seqNo);
void Sound_SetReloadFieldSeqFlag(u16 state);
int Sound_GetSavedHeapLevel(int state);
void Sound_ReloadFieldSceneData(u16 seqNo, int bankNo);
BOOL Sound_PlayFieldBGM(u16 seqNo);
void Sound_SetBGMPlayerChannels(int mode);
void Sound_ApplyVoiceChatVolume(int seqNo, enum SoundHandleNo handleNo);
u8 GF_GetPlayerNoBySeq(u16 seqNo);
const struct NNSSndArcBankInfo *GF_GetBankInfoBySeqNo(int seqNo);
BOOL Sound_PlayReversedWaveArc(int waveArcNo, int volume, int pan, int channel, int heapId);
void Sound_StopWaveOut(int channel);
void Sound_SetWaveOutPan(int channel, u8 pan);
void Sound_SetWaveOutSpeed(int channel, u32 speed);
void GF_SndHandleSetTrackPitch(int handleNo, u32 tracks, int pitch);
void GF_SndSetTrackPitchBySeqNo(u16 seqNo, u32 tracks, int pitch);
void GF_SndSetTrackPitchByPlayerNo(int playerNo, u32 tracks, int pitch);
void GF_SndHandleSetTrackPan(int handleNo, u32 tracks, int pan);
void GF_SndHandleSetTempoRatio(int handleNo, int ratio);
void GF_SndSetFadeTimer(u32 frames);
BOOL GF_NowStartMusicId(u16 seqNo, u16 fadeOutFrames, int delay, u8 reload, int unused);
BOOL GF_FadeStartMusicId(u16 seqNo, u16 fadeOutFrames, int delay, int fadeInFrames, u8 reload, int unused);

#endif // POKEHEARTGOLD_SOUND_SYSTEM_INTERNAL_H
