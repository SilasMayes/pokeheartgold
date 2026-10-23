#ifndef POKEHEARTGOLD_FIELD_FIELD_HOOK_UNUSED_H
#define POKEHEARTGOLD_FIELD_FIELD_HOOK_UNUSED_H

#include "global.h"

typedef struct FieldHookState FieldHookState;

void FieldHookUnused_OnEvent(FieldHookState *state, u32 event);
u8 FieldHookUnused_IsMovementAllowed(FieldHookState *state);

#endif // POKEHEARTGOLD_FIELD_FIELD_HOOK_UNUSED_H
