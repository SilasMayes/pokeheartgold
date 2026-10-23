#include "global.h"

#include "dwc/net_common_internal.h"

#include "lobby_event_deque.h"

#include <nitro/code32.h>

LobbyEventDequeMap *LobbyEventDequeMap_Destroy(LobbyEventDequeMap *map) {
    if (map->blocks) {
        u32 size = map->size;

        struct {
            u8 control;
        } local = { 0 };

        map->size = map->size - size;
        (void)local;
        if (map->blocks) {
            DWC_Free(0, map->blocks, 0);
        }
    }
    return map;
}
