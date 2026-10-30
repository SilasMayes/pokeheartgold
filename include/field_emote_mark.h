#ifndef POKEHEARTGOLD_FIELD_EMOTE_MARK_H
#define POKEHEARTGOLD_FIELD_EMOTE_MARK_H

#include "player_avatar.h"

// The mark is a FieldEffect *, which callers keep in an integer (intptr_t: int on the DS)
intptr_t EmoteMark_Spawn(LocalMapObject *obj, int kind, int playSound);
BOOL EmoteMark_IsDone(intptr_t effect);
void EmoteMark_Hide(intptr_t effect);

#endif // POKEHEARTGOLD_FIELD_EMOTE_MARK_H
