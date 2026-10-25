#include "global.h"

#include <nitro/code32.h>

#include "lobby_chat_internal.h"

extern char gLobbyStr_SERVER[];
extern char gLobbyStr_ExcessFlood[];
extern char gLobbyStr_SpaceColon[];

static inline char *TextChars(Str *text) {
    if (text->l.isLong == 0) {
        return text->s.buf;
    } else {
        return text->l.ptr;
    }
}

static inline int Compare(char *key, char *str, Str *strText, Str *keyText, int len) {
    int result;
    LobbyString_InitFromCStr(strText, str);
    LobbyString_InitFromCStr(keyText, key);
    result = LobbyString_CompareNoCase(strText, keyText, len);
    LobbyString_Destroy(keyText);
    LobbyString_Destroy(strText);
    return result;
}

static inline u32 StringVectorSize(const volatile LobbyStringVector *vector) {
    return vector->size;
}

#pragma opt_propagation off

// Messages from the server only matter as excess flood notices; user messages are passed on by user ID.
void LobbyChat_OnPrivateMessage(void *chat, char *nick, char *message, int type, void *param) {
    struct {
        Str messageStr, floodStr, nickStr, serverStr;
        LobbyChatCallbacks messageCallbacks;
        Str senderNick;
        LobbyChatCallbacks floodCallbacks;
        Str separator, text;
        LobbyStringVector vector;
    } frame;

    char *serverKey, *floodKey;
    int serverCmp, floodCmp, userId;
    if (gLobbyChatManager && gLobbyChatManager->state == LOBBY_CHAT_STATE_ERROR) {
        return;
    }
    serverKey = gLobbyStr_SERVER;
    serverCmp = Compare(serverKey, nick, &frame.nickStr, &frame.serverStr, 6);
    if (serverCmp == 0) {
        floodKey = gLobbyStr_ExcessFlood;
        floodCmp = Compare(floodKey, message, &frame.messageStr, &frame.floodStr, 12);
        if (floodCmp != 0) {
            return;
        }
        LobbyString_InitFromCStr(&frame.text, message);
        LobbyString_InitFromCStr(&frame.separator, gLobbyStr_SpaceColon);
        LobbyChat_SplitString(&frame.vector, &frame.text, &frame.separator, 0);
        LobbyString_Destroy(&frame.separator);
        LobbyString_Destroy(&frame.text);
        if (frame.vector.size == 0) {
            LobbyStringVector_Destroy(&frame.vector);
            return;
        }
        {
            Str *last = &frame.vector.data[StringVectorSize(&frame.vector) - 1];
            userId = atol(TextChars(last));
        }
        if (userId == 0) {
            LobbyStringVector_Destroy(&frame.vector);
            return;
        }
        frame.floodCallbacks = gLobbyChatManager->callbacks;
        frame.floodCallbacks.onExcessFlood(userId, param);
        LobbyStringVector_Destroy(&frame.vector);
        return;
    }
    if (type != 3) {
        return;
    }
    LobbyString_InitFromCStr(&frame.senderNick, nick);
    userId = LobbyChat_FindUserIdByNick(gLobbyChatManager, &frame.senderNick);
    LobbyString_Destroy(&frame.senderNick);
    if (userId == -1) {
        return;
    }
    frame.messageCallbacks = gLobbyChatManager->callbacks;
    frame.messageCallbacks.onMessage(userId, message, param);
}
