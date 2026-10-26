#include "global.h"

#include <nitro/code32.h>

#include "lobby_chat_internal.h"

void LobbyUserMap_MakeEntry(LobbyUserMapEntry *entry, int userId, const Str *nick) {
    entry->userId = userId;
    LobbyString_InitCopy(&entry->nick, nick);
}

BOOL LobbyChat_AreChannelUsersEnumerated(LobbyChatManager *manager, Str *key) {
    Iter n;
    LobbyChannelMap_Find(&n, &manager->channelMap, key);
    if (n.current == &manager->channelMap.root) {
        return FALSE;
    }
    return ((LobbyChannelMapNode *)n.current)->entry.channel.usersEnumerated;
}

BOOL LobbyChat_SetChannelUsersEnumerated(LobbyChatManager *manager, Str *key) {
    Iter n;
    LobbyChannelMap_Find(&n, &manager->channelMap, key);
    if (n.current == &manager->channelMap.root) {
        return FALSE;
    }
    ((LobbyChannelMapNode *)n.current)->entry.channel.usersEnumerated = TRUE;
    return TRUE;
}

int LobbyChat_GetChannelUserLimit(LobbyChatManager *manager, Str *key) {
    Iter n;
    LobbyChannelMap_Find(&n, &manager->channelMap, key);
    if (n.current == &manager->channelMap.root) {
        return -1;
    }
    return ((LobbyChannelMapNode *)n.current)->entry.channel.userLimit;
}
