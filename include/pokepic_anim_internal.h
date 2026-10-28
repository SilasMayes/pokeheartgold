#ifndef POKEHEARTGOLD_POKEPIC_ANIM_INTERNAL_H
#define POKEHEARTGOLD_POKEPIC_ANIM_INTERNAL_H

#include "global.h"

#include "heap.h"
#include "pokepic.h"

typedef struct PokepicAnimManager PokepicAnimManager;

PokepicAnimManager *PokepicAnimManager_New(enum HeapID heapId, int count, BOOL allowReverse);
void PokepicAnimManager_Delete(PokepicAnimManager *mgr);
u32 PokepicAnimManager_GetAnimState(PokepicAnimManager *mgr, u32 index);
void PokepicAnimManager_StopAnim(PokepicAnimManager *mgr, u32 index);

#endif // POKEHEARTGOLD_POKEPIC_ANIM_INTERNAL_H
