#include "global.h"

#include "lobby_vector.h"

#include <nitro/code32.h>

u32 *LobbyU32Vector_Data2(LobbyU32Vector *vector) {
    return vector->size == 0 ? NULL : vector->data;
}
