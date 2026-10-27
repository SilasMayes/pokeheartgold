#include "global.h"

#include <nitro/code32.h>

#include "lobby_chat_internal.h"

enum PPWLobbyError LobbyChat_GetLastError(void) {
    return gLobbyChatManager ? gLobbyChatManager->lastError : PPW_LOBBY_ERROR_NONE;
}

// The error code shown to the player for a lobby chat error
int LobbyChat_ToErrorCode(int error) {
    return error + 42000;
}

BOOL LobbyChat_IsInChannel(char *channel) {
    Str channelName;
    Str fullName;
    BOOL inChannel;
    if (!gLobbyChatManager) {
        return FALSE;
    }
    LobbyString_InitFromCStr(&channelName, channel);
    LobbyChat_GetFullChannelName(&fullName, gLobbyChatManager, &channelName);
    inChannel = chatInChannelA(gLobbyChatManager->connection, StrData(&fullName)) == 1;
    LobbyString_Destroy(&fullName);
    LobbyString_Destroy(&channelName);
    return inChannel;
}
