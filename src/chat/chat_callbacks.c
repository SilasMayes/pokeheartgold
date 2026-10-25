#include "global.h"

#include "dwc/chat_internal.h"

#include <nitro/code32.h>

#define ASSERT_CHAT(chat, func, line)                                                 \
    do {                                                                              \
        if (!(chat)) {                                                                \
            __msl_assertion_failed(gChatStr_ChatNeNULL, gLobbyStr_ChatCallbacksC, func, line); \
        }                                                                             \
    } while (0)
#define ASSERT_CALLBACK(callback, func, line)                                                       \
    do {                                                                                            \
        if (!(callback)) {                                                                          \
            __msl_assertion_failed(gLobbyStr_DataNeNULL, gLobbyStr_ChatCallbacksC, func, line);               \
        }                                                                                           \
        if ((callback)->type < 0) {                                                                 \
            __msl_assertion_failed(gChatStr_DataTypeGe0, gLobbyStr_ChatCallbacksC, func, line);              \
        }                                                                                           \
        if ((callback)->type >= CALLBACK_NUM) {                                                     \
            __msl_assertion_failed(gChatStr_DataTypeLtCALLBACK_NUM, gLobbyStr_ChatCallbacksC, func, line);   \
        }                                                                                           \
        if (!(callback)->callback) {                                                                \
            __msl_assertion_failed(gChatStr_DataCallbackNeNULL, gLobbyStr_ChatCallbacksC, func, line);       \
        }                                                                                           \
        if (!(callback)->param) {                                                                   \
            __msl_assertion_failed(gChatStr_DataCallbackParamsNeNULL, gLobbyStr_ChatCallbacksC, func, line); \
        }                                                                                           \
        if ((callback)->id < 0) {                                                                   \
            __msl_assertion_failed(gChatStr_DataID_Ge0, gLobbyStr_ChatCallbacksC, func, line);               \
        }                                                                                           \
    } while (0)

void ciFreeCallbackData(ChatCallback *callback) {
    ASSERT_CALLBACK(callback, gChatStr_ciFreeCallbackData, 171);
    switch (callback->type) {
    case CALLBACK_RAW: {
        ChatRawArgs *args = callback->param;
        DWCi_GsFree(args->raw);
        break;
    }
    case CALLBACK_DISCONNECTED: {
        ChatDisconnectedArgs *args = callback->param;
        DWCi_GsFree(args->reason);
        break;
    }
    case CALLBACK_PRIVATE_MESSAGE: {
        ChatPrivateMessageArgs *args = callback->param;
        DWCi_GsFree(args->nick);
        DWCi_GsFree(args->message);
        break;
    }
    case CALLBACK_INVITED: {
        ChatInviteArgs *args = callback->param;
        DWCi_GsFree(args->channel);
        DWCi_GsFree(args->nick);
        break;
    }
    case CALLBACK_CHANNEL_MESSAGE: {
        ChatChannelMessageArgs *args = callback->param;
        DWCi_GsFree(args->channel);
        DWCi_GsFree(args->sender);
        DWCi_GsFree(args->message);
        break;
    }
    case CALLBACK_KICKED: {
        ChatKickedArgs *args = callback->param;
        DWCi_GsFree(args->channel);
        DWCi_GsFree(args->kicker);
        DWCi_GsFree(args->reason);
        break;
    }
    case CALLBACK_USER_JOINED: {
        ChatUserJoinedArgs *args = callback->param;
        DWCi_GsFree(args->channel);
        DWCi_GsFree(args->nick);
        break;
    }
    case CALLBACK_USER_PARTED: {
        ChatUserLeftArgs *args = callback->param;
        DWCi_GsFree(args->channel);
        DWCi_GsFree(args->nick);
        DWCi_GsFree(args->message);
        DWCi_GsFree(args->kicker);
        break;
    }
    case CALLBACK_USER_CHANGED_NICK: {
        ChatNickChangeArgs *args = callback->param;
        DWCi_GsFree(args->channel);
        DWCi_GsFree(args->oldNick);
        DWCi_GsFree(args->newNick);
        break;
    }
    case CALLBACK_TOPIC_CHANGED: {
        ChatTopicArgs *args = callback->param;
        DWCi_GsFree(args->channel);
        DWCi_GsFree(args->topic);
        break;
    }
    case CALLBACK_CHANNEL_MODE_CHANGED: {
        ChatChannelModeChangedArgs *args = callback->param;
        DWCi_GsFree(args->channel);
        DWCi_GsFree(args->mode);
        break;
    }
    case CALLBACK_USER_MODE_CHANGED: {
        ChatUserModeArgs *args = callback->param;
        DWCi_GsFree(args->channel);
        DWCi_GsFree(args->nick);
        break;
    }
    case CALLBACK_USER_LIST_UPDATED: {
        ChatUsersChangedArgs *args = callback->param;
        DWCi_GsFree(args->channel);
        break;
    }
    case CALLBACK_ENUM_CHANNELS_EACH: {
        ChatChannelListEntryArgs *args = callback->param;
        DWCi_GsFree(args->channel);
        DWCi_GsFree(args->topic);
        break;
    }
    case CALLBACK_ENUM_CHANNELS_ALL: {
        int i;
        ChatChannelListArgs *args = callback->param;
        for (i = 0; i < args->numChannels; i++) {
            DWCi_GsFree(args->channels[i]);
            DWCi_GsFree(args->topics[i]);
        }
        DWCi_GsFree(args->channels);
        DWCi_GsFree(args->topics);
        DWCi_GsFree(args->numUsers);
        break;
    }
    case CALLBACK_ENTER_CHANNEL: {
        ChatEnterChannelArgs *args = callback->param;
        DWCi_GsFree(args->channel);
        break;
    }
    case CALLBACK_GET_CHANNEL_TOPIC: {
        ChatGetTopicArgs *args = callback->param;
        DWCi_GsFree(args->channel);
        DWCi_GsFree(args->topic);
        break;
    }
    case CALLBACK_GET_CHANNEL_MODE: {
        ChatChannelModeArgs *args = callback->param;
        DWCi_GsFree(args->channel);
        DWCi_GsFree(args->mode);
        break;
    }
    case CALLBACK_GET_CHANNEL_PASSWORD: {
        ChatGetPasswordArgs *args = callback->param;
        DWCi_GsFree(args->channel);
        DWCi_GsFree(args->password);
        break;
    }
    case CALLBACK_ENUM_USERS: {
        int i;
        ChatEnumUsersArgs *args = callback->param;
        DWCi_GsFree(args->channel);
        for (i = 0; i < args->numUsers; i++) {
            DWCi_GsFree(args->users[i]);
        }
        DWCi_GsFree(args->users);
        DWCi_GsFree(args->modes);
        break;
    }
    case CALLBACK_GET_USER_INFO: {
        int i;
        ChatGetUserInfoArgs *args = callback->param;
        DWCi_GsFree(args->nick);
        DWCi_GsFree(args->user);
        DWCi_GsFree(args->name);
        DWCi_GsFree(args->address);
        for (i = 0; i < args->numChannels; i++) {
            DWCi_GsFree(args->channels[i]);
        }
        DWCi_GsFree(args->channels);
        break;
    }
    case CALLBACK_GET_BASIC_USER_INFO: {
        ChatGetBasicUserInfoArgs *args = callback->param;
        DWCi_GsFree(args->nick);
        DWCi_GsFree(args->user);
        DWCi_GsFree(args->address);
        break;
    }
    case CALLBACK_GET_CHANNEL_BASIC_USER_INFO: {
        ChatGetChannelBasicUserInfoArgs *args = callback->param;
        DWCi_GsFree(args->channel);
        DWCi_GsFree(args->nick);
        DWCi_GsFree(args->user);
        DWCi_GsFree(args->address);
        break;
    }
    case CALLBACK_GET_USER_MODE: {
        ChatGetUserModeArgs *args = callback->param;
        DWCi_GsFree(args->channel);
        DWCi_GsFree(args->user);
        break;
    }
    case CALLBACK_ENUM_CHANNEL_BANS: {
        int i;
        ChatEnumBansArgs *args = callback->param;
        DWCi_GsFree(args->channel);
        for (i = 0; i < args->numBans; i++) {
            DWCi_GsFree(args->bans[i]);
        }
        DWCi_GsFree(args->bans);
        break;
    }
    case CALLBACK_NICK_ERROR: {
        int i;
        ChatNickErrorArgs *args = callback->param;
        DWCi_GsFree(args->nick);
        for (i = 0; i < args->numSuggestedNicks; i++) {
            DWCi_GsFree(args->suggestedNicks[i]);
        }
        DWCi_GsFree(args->suggestedNicks);
        break;
    }
    case CALLBACK_CHANGE_NICK: {
        ChatChangeNickArgs *args = callback->param;
        DWCi_GsFree(args->oldNick);
        DWCi_GsFree(args->newNick);
        break;
    }
    case CALLBACK_NEW_USER_LIST: {
        int i;
        ChatNewUserListArgs *args = callback->param;
        DWCi_GsFree(args->channel);
        for (i = 0; i < args->numUsers; i++) {
            DWCi_GsFree(args->users[i]);
        }
        DWCi_GsFree(args->users);
        DWCi_GsFree(args->modes);
        break;
    }
    case CALLBACK_BROADCAST_KEY_CHANGED: {
        ChatBroadcastKeyArgs *args = callback->param;
        DWCi_GsFree(args->channel);
        DWCi_GsFree(args->nick);
        DWCi_GsFree(args->key);
        DWCi_GsFree(args->value);
        break;
    }
    case CALLBACK_GET_GLOBAL_KEYS: {
        int i;
        ChatGetGlobalKeysArgs *args = callback->param;
        DWCi_GsFree(args->user);
        for (i = 0; i < args->num; i++) {
            DWCi_GsFree(args->keys[i]);
            if (args->values) {
                DWCi_GsFree(args->values[i]);
            }
        }
        DWCi_GsFree(args->keys);
        DWCi_GsFree(args->values);
        break;
    }
    case CALLBACK_GET_CHANNEL_KEYS: {
        int i;
        ChatGetChannelKeysArgs *args = callback->param;
        DWCi_GsFree(args->channel);
        DWCi_GsFree(args->user);
        for (i = 0; i < args->num; i++) {
            DWCi_GsFree(args->keys[i]);
            if (args->values) {
                DWCi_GsFree(args->values[i]);
            }
        }
        DWCi_GsFree(args->keys);
        DWCi_GsFree(args->values);
        break;
    }
    case CALLBACK_AUTHENTICATE_CDKEY: {
        ChatAuthenticateCDKeyArgs *args = callback->param;
        DWCi_GsFree(args->message);
        break;
    }
    default:
        __msl_assertion_failed(gChatStr_0_8, gLobbyStr_ChatCallbacksC, gChatStr_ciFreeCallbackData, 485);
        break;
    }
    DWCi_GsFree(callback->param);
}

ChatResult ciInitCallbacks(ChatConnection *chat) {
    chat->callbacks = ArrayNew(sizeof(ChatCallback), 0x80, ciCallbacksArrayElementFreeFn);
    return chat->callbacks == NULL ? CHAT_FAILURE : CHAT_SUCCESS;
}

void ciCleanupCallbacks(ChatConnection *chat) {
    ChatCallback *callback;
    int n, i;
    ASSERT_CHAT(chat, gChatStr_ciCleanupCallbacks, 506);
    if (!chat->callbacks) {
        return;
    }
    n = ArrayLength(chat->callbacks);
    for (i = 0; i < n; i++) {
        callback = ArrayNth(chat->callbacks, i);
        ASSERT_CALLBACK(callback, gChatStr_ciCleanupCallbacks, 525);
        ciFreeCallbackData(callback);
    }
    ArrayFree(chat->callbacks);
}

#define ASSERT(test, string, line)                                                          \
    do {                                                                                    \
        if (!(test)) {                                                                      \
            __msl_assertion_failed(string, gLobbyStr_ChatCallbacksC, gChatStr_ciAddCallback_, line); \
        }                                                                                   \
    } while (0)
#define FAIL()                     \
    do {                           \
        DWCi_GsFree(dst);          \
        DWCi_GsFree(item.channel); \
        return FALSE;              \
    } while (0)
// Copies a string argument into the stored arguments.
#define COPY_STRING(field)                      \
    do {                                        \
        if (src->field) {                       \
            dst->field = goastrdup(src->field); \
            if (!dst->field) {                  \
                FAIL();                         \
            }                                   \
        }                                       \
    } while (0)
// Copies an array of count strings into the stored arguments.
#define COPY_STRING_ARRAY(count, array)                                \
    do {                                                               \
        if (!src->array) {                                             \
            dst->array = NULL;                                         \
        } else {                                                       \
            dst->array = DWCi_GsMalloc(src->count * sizeof(char *));   \
            if (!dst->array) {                                         \
                FAIL();                                                \
            }                                                          \
            for (i = 0; i < src->count; i++) {                         \
                if (!src->array[i]) {                                  \
                    dst->array[i] = NULL;                              \
                } else {                                               \
                    dst->array[i] = goastrdup(src->array[i]);          \
                    if (!dst->array[i]) {                              \
                        for (i--; i >= 0; i--) {                       \
                            DWCi_GsFree(dst->array[i]);                \
                        }                                              \
                        DWCi_GsFree(dst->array);                       \
                        FAIL();                                        \
                    }                                                  \
                }                                                      \
            }                                                          \
        }                                                              \
    } while (0)

BOOL ciAddCallback_(ChatConnection *chat, int type, void *func, const void *params, void *user, int id, const char *channel, int size) {
    ChatCallback item;
    ASSERT(chat, gChatStr_ChatNeNULL, 0x21f);
    ASSERT(type >= 0, gChatStr_TypeGe0, 0x221);
    ASSERT(type < CALLBACK_NUM, gChatStr_TypeLtCALLBACK_NUM, 0x222);
    ASSERT(chat->callbacks, gChatStr_ConnectionCallbackListNeNULL, 0x223);
    ASSERT(func, gChatStr_CallbackNeNULL_2, 0x224);
    ASSERT(params, gChatStr_CallbackParamsNeNULL, 0x225);
    ASSERT(size, gChatStr_CallbackParamsSizeGt0, 0x226);
    ASSERT(id >= 0, gChatStr_ID_Ge0, 0x227);
    memset(&item, 0, sizeof(item));
    item.type = type;
    item.callback = func;
    item.param = DWCi_GsMalloc(size);
    if (!item.param) {
        return FALSE;
    }
    memcpy(item.param, params, size);
    item.user = user;
    item.id = id;
    if (!channel) {
        item.channel = NULL;
    } else {
        int length = strlen(channel);
        item.channel = DWCi_GsMalloc(length + 1);
        if (!item.channel) {
            DWCi_GsFree(item.param);
            return FALSE;
        }
        memcpy(item.channel, channel, length + 1);
    }
    switch (item.type) {
    case CALLBACK_RAW: {
        const ChatRawArgs *src = params;
        ChatRawArgs *dst = item.param;
        COPY_STRING(raw);
        break;
    }
    case CALLBACK_DISCONNECTED: {
        const ChatDisconnectedArgs *src = params;
        ChatDisconnectedArgs *dst = item.param;
        COPY_STRING(reason);
        break;
    }
    case CALLBACK_PRIVATE_MESSAGE: {
        const ChatPrivateMessageArgs *src = params;
        ChatPrivateMessageArgs *dst = item.param;
        COPY_STRING(nick);
        COPY_STRING(message);
        break;
    }
    case CALLBACK_INVITED: {
        const ChatInviteArgs *src = params;
        ChatInviteArgs *dst = item.param;
        COPY_STRING(channel);
        COPY_STRING(nick);
        break;
    }
    case CALLBACK_CHANNEL_MESSAGE: {
        const ChatChannelMessageArgs *src = params;
        ChatChannelMessageArgs *dst = item.param;
        COPY_STRING(channel);
        COPY_STRING(sender);
        COPY_STRING(message);
        break;
    }
    case CALLBACK_KICKED: {
        const ChatKickedArgs *src = params;
        ChatKickedArgs *dst = item.param;
        COPY_STRING(channel);
        COPY_STRING(kicker);
        COPY_STRING(reason);
        break;
    }
    case CALLBACK_USER_JOINED: {
        const ChatUserJoinedArgs *src = params;
        ChatUserJoinedArgs *dst = item.param;
        COPY_STRING(channel);
        COPY_STRING(nick);
        break;
    }
    case CALLBACK_USER_PARTED: {
        const ChatUserLeftArgs *src = params;
        ChatUserLeftArgs *dst = item.param;
        COPY_STRING(channel);
        COPY_STRING(nick);
        COPY_STRING(message);
        COPY_STRING(kicker);
        break;
    }
    case CALLBACK_USER_CHANGED_NICK: {
        const ChatNickChangeArgs *src = params;
        ChatNickChangeArgs *dst = item.param;
        COPY_STRING(channel);
        COPY_STRING(oldNick);
        COPY_STRING(newNick);
        break;
    }
    case CALLBACK_TOPIC_CHANGED: {
        const ChatTopicArgs *src = params;
        ChatTopicArgs *dst = item.param;
        COPY_STRING(channel);
        COPY_STRING(topic);
        break;
    }
    case CALLBACK_CHANNEL_MODE_CHANGED: {
        const ChatChannelModeChangedArgs *src = params;
        ChatChannelModeChangedArgs *dst = item.param;
        COPY_STRING(channel);
        if (src->mode) {
            dst->mode = DWCi_GsMalloc(sizeof(ChatChannelMode));
            if (!dst->mode) {
                FAIL();
            }
            memcpy(dst->mode, src->mode, sizeof(ChatChannelMode));
        }
        break;
    }
    case CALLBACK_USER_MODE_CHANGED: {
        const ChatUserModeArgs *src = params;
        ChatUserModeArgs *dst = item.param;
        COPY_STRING(channel);
        COPY_STRING(nick);
        break;
    }
    case CALLBACK_USER_LIST_UPDATED: {
        const ChatUsersChangedArgs *src = params;
        ChatUsersChangedArgs *dst = item.param;
        COPY_STRING(channel);
        break;
    }
    case CALLBACK_ENUM_CHANNELS_EACH: {
        const ChatChannelListEntryArgs *src = params;
        ChatChannelListEntryArgs *dst = item.param;
        COPY_STRING(channel);
        COPY_STRING(topic);
        break;
    }
    case CALLBACK_ENUM_CHANNELS_ALL: {
        int i;
        const ChatChannelListArgs *src = params;
        ChatChannelListArgs *dst = item.param;
        ASSERT(src->numChannels >= 0, gChatStr_SrcParamsNumChannelsGe0, 0x2d3);
        COPY_STRING_ARRAY(numChannels, channels);
        ASSERT(src->numChannels >= 0, gChatStr_SrcParamsNumChannelsGe0, 0x2d4);
        COPY_STRING_ARRAY(numChannels, topics);
        ASSERT(src->numChannels >= 0, gChatStr_SrcParamsNumChannelsGe0, 0x2d5);
        if (src->numChannels > 0) {
            int bytes;
            ASSERT(src->numUsers, gChatStr_SrcParamsNumUsersNeNULL, 0x2d5);
            bytes = src->numChannels * sizeof(int);
            dst->numUsers = DWCi_GsMalloc(bytes);
            if (!dst->numUsers) {
                FAIL();
            }
            memcpy(dst->numUsers, src->numUsers, bytes);
        }
        break;
    }
    case CALLBACK_ENTER_CHANNEL: {
        const ChatEnterChannelArgs *src = params;
        ChatEnterChannelArgs *dst = item.param;
        COPY_STRING(channel);
        break;
    }
    case CALLBACK_GET_CHANNEL_TOPIC: {
        const ChatGetTopicArgs *src = params;
        ChatGetTopicArgs *dst = item.param;
        COPY_STRING(channel);
        COPY_STRING(topic);
        break;
    }
    case CALLBACK_GET_CHANNEL_MODE: {
        const ChatChannelModeArgs *src = params;
        ChatChannelModeArgs *dst = item.param;
        COPY_STRING(channel);
        if (src->mode) {
            dst->mode = DWCi_GsMalloc(sizeof(ChatChannelMode));
            if (!dst->mode) {
                FAIL();
            }
            memcpy(dst->mode, src->mode, sizeof(ChatChannelMode));
        }
        break;
    }
    case CALLBACK_GET_CHANNEL_PASSWORD: {
        const ChatGetPasswordArgs *src = params;
        ChatGetPasswordArgs *dst = item.param;
        COPY_STRING(channel);
        COPY_STRING(password);
        break;
    }
    case CALLBACK_ENUM_USERS: {
        const ChatEnumUsersArgs *src = params;
        ChatEnumUsersArgs *dst = item.param;
        int i;
        COPY_STRING(channel);
        ASSERT(src->numUsers >= 0, gChatStr_SrcParamsNumUsersGe0, 0x301);
        COPY_STRING_ARRAY(numUsers, users);
        ASSERT(src->numUsers >= 0, gChatStr_SrcParamsNumUsersGe0, 0x302);
        if (src->numUsers > 0) {
            int bytes;
            ASSERT(src->modes, gChatStr_SrcParamsModesNeNULL, 0x302);
            bytes = src->numUsers * sizeof(int);
            dst->modes = DWCi_GsMalloc(bytes);
            if (!dst->modes) {
                FAIL();
            }
            memcpy(dst->modes, src->modes, bytes);
        }
        break;
    }
    case CALLBACK_GET_USER_INFO: {
        const ChatGetUserInfoArgs *src = params;
        ChatGetUserInfoArgs *dst = item.param;
        int i;
        COPY_STRING(nick);
        COPY_STRING(user);
        COPY_STRING(name);
        COPY_STRING(address);
        ASSERT(src->numChannels >= 0, gChatStr_SrcParamsNumChannelsGe0, 0x30e);
        COPY_STRING_ARRAY(numChannels, channels);
        break;
    }
    case CALLBACK_GET_BASIC_USER_INFO: {
        const ChatGetBasicUserInfoArgs *src = params;
        ChatGetBasicUserInfoArgs *dst = item.param;
        COPY_STRING(nick);
        COPY_STRING(user);
        COPY_STRING(address);
        break;
    }
    case CALLBACK_GET_CHANNEL_BASIC_USER_INFO: {
        const ChatGetChannelBasicUserInfoArgs *src = params;
        ChatGetChannelBasicUserInfoArgs *dst = item.param;
        COPY_STRING(channel);
        COPY_STRING(nick);
        COPY_STRING(user);
        COPY_STRING(address);
        break;
    }
    case CALLBACK_GET_USER_MODE: {
        const ChatGetUserModeArgs *src = params;
        ChatGetUserModeArgs *dst = item.param;
        COPY_STRING(channel);
        COPY_STRING(user);
        break;
    }
    case CALLBACK_ENUM_CHANNEL_BANS: {
        const ChatEnumBansArgs *src = params;
        ChatEnumBansArgs *dst = item.param;
        int i;
        COPY_STRING(channel);
        ASSERT(src->numBans >= 0, gChatStr_SrcParamsNumBansGe0, 0x335);
        COPY_STRING_ARRAY(numBans, bans);
        break;
    }
    case CALLBACK_NICK_ERROR: {
        const ChatNickErrorArgs *src = params;
        ChatNickErrorArgs *dst = item.param;
        int i;
        COPY_STRING(nick);
        ASSERT(src->numSuggestedNicks >= 0, gChatStr_SrcParamsNumSuggestedNicksGe0, 0x33e);
        COPY_STRING_ARRAY(numSuggestedNicks, suggestedNicks);
        break;
    }
    case CALLBACK_CHANGE_NICK: {
        const ChatChangeNickArgs *src = params;
        ChatChangeNickArgs *dst = item.param;
        COPY_STRING(oldNick);
        COPY_STRING(newNick);
        break;
    }
    case CALLBACK_NEW_USER_LIST: {
        const ChatNewUserListArgs *src = params;
        ChatNewUserListArgs *dst = item.param;
        int i;
        COPY_STRING(channel);
        ASSERT(src->numUsers >= 0, gChatStr_SrcParamsNumUsersGe0, 0x350);
        COPY_STRING_ARRAY(numUsers, users);
        ASSERT(src->numUsers >= 0, gChatStr_SrcParamsNumUsersGe0, 0x351);
        if (src->numUsers > 0) {
            int bytes;
            ASSERT(src->modes, gChatStr_SrcParamsModesNeNULL, 0x351);
            bytes = src->numUsers * sizeof(int);
            dst->modes = DWCi_GsMalloc(bytes);
            if (!dst->modes) {
                FAIL();
            }
            memcpy(dst->modes, src->modes, bytes);
        }
        break;
    }
    case CALLBACK_BROADCAST_KEY_CHANGED: {
        const ChatBroadcastKeyArgs *src = params;
        ChatBroadcastKeyArgs *dst = item.param;
        COPY_STRING(channel);
        COPY_STRING(nick);
        COPY_STRING(key);
        COPY_STRING(value);
        break;
    }
    case CALLBACK_GET_GLOBAL_KEYS: {
        const ChatGetGlobalKeysArgs *src = params;
        ChatGetGlobalKeysArgs *dst = item.param;
        int i;
        COPY_STRING(user);
        ASSERT(src->num >= 0, gChatStr_SrcParamsNumGe0, 0x365);
        COPY_STRING_ARRAY(num, keys);
        ASSERT(src->num >= 0, gChatStr_SrcParamsNumGe0, 0x366);
        COPY_STRING_ARRAY(num, values);
        break;
    }
    case CALLBACK_GET_CHANNEL_KEYS: {
        const ChatGetChannelKeysArgs *src = params;
        ChatGetChannelKeysArgs *dst = item.param;
        int i;
        COPY_STRING(channel);
        COPY_STRING(user);
        ASSERT(src->num >= 0, gChatStr_SrcParamsNumGe0, 0x370);
        COPY_STRING_ARRAY(num, keys);
        ASSERT(src->num >= 0, gChatStr_SrcParamsNumGe0, 0x371);
        COPY_STRING_ARRAY(num, values);
        break;
    }
    case CALLBACK_AUTHENTICATE_CDKEY: {
        const ChatAuthenticateCDKeyArgs *src = params;
        ChatAuthenticateCDKeyArgs *dst = item.param;
        COPY_STRING(message);
        break;
    }
    default:
        __msl_assertion_failed(gChatStr_0_8, gLobbyStr_ChatCallbacksC, gChatStr_ciAddCallback_, 0x380);
        break;
    }
    ArrayAppend(chat->callbacks, &item);
    return TRUE;
}

#undef COPY_STRING_ARRAY
#undef COPY_STRING
#undef FAIL
#undef ASSERT

void ciCallCallback(ChatConnection *chat, ChatCallback *callback) {
    void *user;
    ASSERT_CHAT(chat, gChatStr_ciCallCallback, 909);
    ASSERT_CALLBACK(callback, gChatStr_ciCallCallback, 911);
    user = callback->user;
    switch (callback->type) {
    case CALLBACK_RAW: {
        ChatRawArgs *args = callback->param;
        ChatRawCallback func = callback->callback;
        func(chat, args->raw, user);
        break;
    }
    case CALLBACK_DISCONNECTED: {
        ChatDisconnectedArgs *args = callback->param;
        ChatDisconnectedCallback func = callback->callback;
        func(chat, args->reason, user);
        break;
    }
    case CALLBACK_PRIVATE_MESSAGE: {
        ChatPrivateMessageArgs *args = callback->param;
        ChatPrivateMessageCallback func = callback->callback;
        func(chat, args->nick, args->message, args->type, user);
        break;
    }
    case CALLBACK_INVITED: {
        ChatInviteArgs *args = callback->param;
        ChatInvitedCallback func = callback->callback;
        func(chat, args->channel, args->nick, user);
        break;
    }
    case CALLBACK_CHANNEL_MESSAGE: {
        ChatChannelMessageArgs *args = callback->param;
        ChatChannelMessageCallback func = callback->callback;
        func(chat, args->channel, args->sender, args->message, args->type, user);
        break;
    }
    case CALLBACK_KICKED: {
        ChatKickedArgs *args = callback->param;
        ChatKickedCallback func = callback->callback;
        func(chat, args->channel, args->kicker, args->reason, user);
        break;
    }
    case CALLBACK_USER_JOINED: {
        ChatUserJoinedArgs *args = callback->param;
        ChatUserJoinedCallback func = callback->callback;
        func(chat, args->channel, args->nick, args->mode, user);
        break;
    }
    case CALLBACK_USER_PARTED: {
        ChatUserLeftArgs *args = callback->param;
        ChatUserPartedCallback func = callback->callback;
        func(chat, args->channel, args->nick, args->reason, args->message, args->kicker, user);
        break;
    }
    case CALLBACK_USER_CHANGED_NICK: {
        ChatNickChangeArgs *args = callback->param;
        ChatUserChangedNickCallback func = callback->callback;
        func(chat, args->channel, args->oldNick, args->newNick, user);
        break;
    }
    case CALLBACK_TOPIC_CHANGED: {
        ChatTopicArgs *args = callback->param;
        ChatTopicChangedCallback func = callback->callback;
        func(chat, args->channel, args->topic, user);
        break;
    }
    case CALLBACK_CHANNEL_MODE_CHANGED: {
        ChatChannelModeChangedArgs *args = callback->param;
        ChatChannelModeChangedCallback func = callback->callback;
        func(chat, args->channel, args->mode, user);
        break;
    }
    case CALLBACK_USER_MODE_CHANGED: {
        ChatUserModeArgs *args = callback->param;
        ChatUserModeChangedCallback func = callback->callback;
        func(chat, args->channel, args->nick, args->mode, user);
        break;
    }
    case CALLBACK_USER_LIST_UPDATED: {
        ChatUsersChangedArgs *args = callback->param;
        ChatUserListUpdatedCallback func = callback->callback;
        func(chat, args->channel, user);
        break;
    }
    case CALLBACK_ENUM_CHANNELS_EACH: {
        ChatChannelListEntryArgs *args = callback->param;
        ChatEnumChannelsEachCallback func = callback->callback;
        func(chat, args->success, args->index, args->channel, args->topic, args->numUsers, user);
        break;
    }
    case CALLBACK_ENUM_CHANNELS_ALL: {
        ChatChannelListArgs *args = callback->param;
        ChatEnumChannelsAllCallback func = callback->callback;
        func(chat, args->success, args->numChannels, args->channels, args->topics, args->numUsers, user);
        break;
    }
    case CALLBACK_ENTER_CHANNEL: {
        ChatEnterChannelArgs *args = callback->param;
        ChatEnterChannelCallback func = callback->callback;
        ciJoinCallbackCalled(chat, args->channel);
        func(chat, args->success, args->result, args->channel, user);
        break;
    }
    case CALLBACK_GET_CHANNEL_TOPIC: {
        ChatGetTopicArgs *args = callback->param;
        ChatGetChannelTopicCallback func = callback->callback;
        func(chat, args->success, args->channel, args->topic, user);
        break;
    }
    case CALLBACK_GET_CHANNEL_MODE: {
        ChatChannelModeArgs *args = callback->param;
        ChatGetChannelModeCallback func = callback->callback;
        func(chat, args->success, args->channel, args->mode, user);
        break;
    }
    case CALLBACK_GET_CHANNEL_PASSWORD: {
        ChatGetPasswordArgs *args = callback->param;
        ChatGetChannelPasswordCallback func = callback->callback;
        func(chat, args->success, args->channel, args->enabled, args->password, user);
        break;
    }
    case CALLBACK_ENUM_USERS: {
        ChatEnumUsersArgs *args = callback->param;
        ChatEnumUsersCallback func = callback->callback;
        func(chat, args->success, args->channel, args->numUsers, args->users, args->modes, user);
        break;
    }
    case CALLBACK_GET_USER_INFO: {
        ChatGetUserInfoArgs *args = callback->param;
        ChatGetUserInfoCallback func = callback->callback;
        func(chat, args->success, args->nick, args->user, args->name, args->address, args->numChannels, args->channels, user);
        break;
    }
    case CALLBACK_GET_BASIC_USER_INFO: {
        ChatGetBasicUserInfoArgs *args = callback->param;
        ChatGetBasicUserInfoCallback func = callback->callback;
        func(chat, args->success, args->nick, args->user, args->address, user);
        break;
    }
    case CALLBACK_GET_CHANNEL_BASIC_USER_INFO: {
        ChatGetChannelBasicUserInfoArgs *args = callback->param;
        ChatGetChannelBasicUserInfoCallback func = callback->callback;
        func(chat, args->success, args->channel, args->nick, args->user, args->address, user);
        break;
    }
    case CALLBACK_GET_USER_MODE: {
        ChatGetUserModeArgs *args = callback->param;
        ChatGetUserModeCallback func = callback->callback;
        func(chat, args->success, args->channel, args->user, args->mode, user);
        break;
    }
    case CALLBACK_ENUM_CHANNEL_BANS: {
        ChatEnumBansArgs *args = callback->param;
        ChatEnumChannelBansCallback func = callback->callback;
        func(chat, args->success, args->channel, args->numBans, args->bans, user);
        break;
    }
    case CALLBACK_NICK_ERROR: {
        ChatNickErrorArgs *args = callback->param;
        ChatNickErrorCallback func = callback->callback;
        func(chat, args->type, args->nick, args->numSuggestedNicks, args->suggestedNicks, user);
        break;
    }
    case CALLBACK_CHANGE_NICK: {
        ChatChangeNickArgs *args = callback->param;
        ChatChangeNickCallback func = callback->callback;
        func(chat, args->success, args->oldNick, args->newNick, user);
        break;
    }
    case CALLBACK_NEW_USER_LIST: {
        ChatNewUserListArgs *args = callback->param;
        ChatNewUserListCallback func = callback->callback;
        func(chat, args->channel, args->numUsers, args->users, args->modes, user);
        break;
    }
    case CALLBACK_BROADCAST_KEY_CHANGED: {
        ChatBroadcastKeyArgs *args = callback->param;
        ChatBroadcastKeyChangedCallback func = callback->callback;
        func(chat, args->channel, args->nick, args->key, args->value, user);
        break;
    }
    case CALLBACK_GET_GLOBAL_KEYS: {
        ChatGetGlobalKeysArgs *args = callback->param;
        ChatGetGlobalKeysCallback func = callback->callback;
        func(chat, args->success, args->user, args->num, args->keys, args->values, user);
        break;
    }
    case CALLBACK_GET_CHANNEL_KEYS: {
        ChatGetChannelKeysArgs *args = callback->param;
        ChatGetChannelKeysCallback func = callback->callback;
        func(chat, args->success, args->channel, args->user, args->num, args->keys, args->values, user);
        break;
    }
    case CALLBACK_AUTHENTICATE_CDKEY: {
        ChatAuthenticateCDKeyArgs *args = callback->param;
        ChatAuthenticateCDKeyCallback func = callback->callback;
        func(chat, args->result, args->message, user);
        break;
    }
    default:
        __msl_assertion_failed(gChatStr_0_8, gLobbyStr_ChatCallbacksC, gChatStr_ciCallCallback, 0x5ef);
        break;
    }
    ciFreeCallbackData(callback);
}

void ciCallCallbacks(ChatConnection *chat, int id) {
    ChatCallback *callback;
    int i;
    ChatCallback copy;
    ASSERT_CHAT(chat, gChatStr_ciCallCallbacks, 0x5fc);
    i = 0;
    while (i < ArrayLength(chat->callbacks)) {
        callback = ArrayNth(chat->callbacks, i);
        ASSERT_CALLBACK(callback, gChatStr_ciCallCallbacks, 0x605);
        if (callback->channel && !ciInChannel(chat, callback->channel)) {
            ciFreeCallbackData(callback);
            ArrayDeleteAt(chat->callbacks, i);
        } else if ((!callback->channel || ciWasJoinCallbackCalled(chat, callback->channel)) && (!id || callback->id == id)) {
            copy = *callback;
            ArrayDeleteAt(chat->callbacks, i);
            ciCallCallback(chat, &copy);
            if (id) {
                return;
            }
        } else {
            ++i;
        }
    }
}

int ciGetCallbackIndexByID(ChatConnection *chat, int id) {
    ChatCallback *callback;
    int i, count;
    ASSERT_CHAT(chat, gChatStr_ciGetCallbackIndexByID, 0x63b);
    count = ArrayLength(chat->callbacks);
    for (i = 0; i < count; i++) {
        callback = ArrayNth(chat->callbacks, i);
        ASSERT_CALLBACK(callback, gChatStr_ciGetCallbackIndexByID, 0x648);
        if (callback->id == id) {
            return i;
        }
    }
    return -1;
}

ChatResult ciCheckCallbacksForID(ChatConnection *chat, int id) {
    return ciGetCallbackIndexByID(chat, id) == -1 ? CHAT_FAILURE : CHAT_SUCCESS;
}
