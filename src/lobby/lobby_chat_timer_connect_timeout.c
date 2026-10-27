#include "global.h"

#include <nitro/code32.h>

#include "lobby_chat_internal.h"

BOOL LobbyChat_TimerConnectTimeout(void) {
    LobbyChatManager *manager = gLobbyChatManager;
    manager->lastError = PPW_LOBBY_ERROR_SESSION;
    manager->state = LOBBY_CHAT_STATE_ERROR;
    return FALSE;
}
