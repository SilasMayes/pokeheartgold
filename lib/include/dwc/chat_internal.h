#ifndef POKEHEARTGOLD_LIB_INCLUDE_DWC_CHAT_INTERNAL_H
#define POKEHEARTGOLD_LIB_INCLUDE_DWC_CHAT_INTERNAL_H

#include <stdarg.h>

// GameSpy socket layer (BSD names).
#ifndef INVALID_SOCKET
#define INVALID_SOCKET (-1)
#define SOCKET_ERROR   (-1)
#define AF_INET        2
#define SOCK_STREAM    1
#define SOCK_DGRAM     2
#endif

// Chat client of the OVY_45 network library: the connection object, the queue of pending user callbacks
// and the table of joined channels with their users.

// A user callback waiting to be called: its kind, the function, a heap copy of its arguments (an array
// of words; string arguments are duplicated) and the user data passed back to it.
typedef struct ChatCallback {
    int type; // 0 .. 31, selects the argument layout
    void *callback;
    void *param; // u32 array of the arguments
    void *user;
    int id;        // 0 = not tied to a request
    char *channel; // NULL = not tied to a channel
} ChatCallback;

// The callback signatures by number of word arguments (connection first, user data last).
typedef void (*ChatCallbackFunc1)(void *, u32, void *);
typedef void (*ChatCallbackFunc2)(void *, u32, u32, void *);
typedef void (*ChatCallbackFunc3)(void *, u32, u32, u32, void *);
typedef void (*ChatCallbackFunc4)(void *, u32, u32, u32, u32, void *);
typedef void (*ChatCallbackFunc5)(void *, u32, u32, u32, u32, u32, void *);
typedef void (*ChatCallbackFunc6)(void *, u32, u32, u32, u32, u32, u32, void *);
typedef void (*ChatCallbackFunc7)(void *, u32, u32, u32, u32, u32, u32, u32, void *);

// Success flag of some chat functions (an enum, not BOOL: the conditional selects are emitted in a
// different order for an int result).
typedef enum ChatResult {
    CHAT_FAILURE,
    CHAT_SUCCESS,
} ChatResult;

// Callback types (ChatCallback.type): what ciAddCallback_ queued and which arguments it copied.
enum ChatCallbackType {
    CALLBACK_RAW,
    CALLBACK_DISCONNECTED,
    CALLBACK_PRIVATE_MESSAGE,
    CALLBACK_INVITED,
    CALLBACK_CHANNEL_MESSAGE,
    CALLBACK_KICKED,
    CALLBACK_USER_JOINED,
    CALLBACK_USER_PARTED,
    CALLBACK_USER_CHANGED_NICK,
    CALLBACK_TOPIC_CHANGED,
    CALLBACK_CHANNEL_MODE_CHANGED,
    CALLBACK_USER_MODE_CHANGED,
    CALLBACK_USER_LIST_UPDATED,
    CALLBACK_ENUM_CHANNELS_EACH,
    CALLBACK_ENUM_CHANNELS_ALL,
    CALLBACK_ENTER_CHANNEL,
    CALLBACK_GET_CHANNEL_TOPIC,
    CALLBACK_GET_CHANNEL_MODE,
    CALLBACK_GET_CHANNEL_PASSWORD,
    CALLBACK_ENUM_USERS,
    CALLBACK_GET_USER_INFO,
    CALLBACK_GET_BASIC_USER_INFO,
    CALLBACK_GET_CHANNEL_BASIC_USER_INFO,
    CALLBACK_GET_USER_MODE,
    CALLBACK_ENUM_CHANNEL_BANS,
    CALLBACK_NICK_ERROR,
    CALLBACK_CHANGE_NICK,
    CALLBACK_NEW_USER_LIST,
    CALLBACK_BROADCAST_KEY_CHANGED,
    CALLBACK_GET_GLOBAL_KEYS,
    CALLBACK_GET_CHANNEL_KEYS,
    CALLBACK_AUTHENTICATE_CDKEY,
    CALLBACK_NUM,
};

// Callbacks the user registered for one channel (copied into the channel when it is entered).
typedef struct ChatChannelCallbacks {
    void *message;         // callback type 4: a message to the channel (ChatChannelMessageArgs)
    void *kicked;          // callback type 5: the own user was kicked (ChatKickedArgs)
    void *userJoined;      // callback type 6: a user entered the channel (ChatUserJoinedArgs)
    void *userLeft;        // callback type 7: a user left the channel (ChatUserLeftArgs)
    void *nickChanged;     // callback type 8: a user of the channel changed the nick
    void *topicChanged;    // callback type 9: the topic changed (ChatTopicArgs)
    void *modeChanged;     // callback type 10: the mode of the channel changed (ChatChannelModeChangedArgs)
    void *userModeChanged; // callback type 11: a user's mode in the channel changed
    void *usersChanged;    // callback type 12: the user list changed (argument: the channel)
    void *unk_24;
    void *broadcastKeyChanged; // callback type 28: a broadcast key changed (ChatBroadcastKeyArgs)
    void *param;               // user data passed to the callbacks
} ChatChannelCallbacks;

// A user in a channel (element of ChatChannel.users, keyed by the nick).
typedef struct ChatChannelUser {
    char nick[128];
    char user[24];
    char address[64];
    BOOL hasUserInfo; // user and address are known
    int mode;         // 0 .. 3
} ChatChannelUser;

// A joined channel (element of ChatConnection.channels, keyed by the name).
typedef struct ChatChannel {
    char name[257];
    u8 unk_101[3];
    ChatChannelCallbacks callbacks;
    void *users; // hash table of ChatChannelUser
    u8 mode[32];
    BOOL hasMode; // mode is valid
    char *password;
    BOOL joined;
    char topic[128];
} ChatChannel;

// State of the connection's stream cipher.
typedef struct ChatCipher {
    u8 state[256];
    u8 x;
    u8 y;
} ChatCipher;

#include "dwc/chat_connection.h"

// The users of a channel, collected for a ChatUserListFunc.
typedef struct ChatUserList {
    ChatConnection *chat;
    int count;
    ChatChannelUser **users;
    int *modes;
} ChatUserList;

typedef void (*ChatUserListFunc)(ChatConnection *chat, const char *channel, int count, ChatChannelUser **users, int *modes, int param);
typedef void (*ChatUserSearchFunc)(ChatConnection *chat, const char *nick, ChatChannel *channel, void *param);

// Search of one nick in all channels.
typedef struct ChatUserSearch {
    ChatConnection *chat;
    char *nick;
    ChatUserSearchFunc callback;
    void *param;
    char buffer[sizeof(ChatChannelUser)];
} ChatUserSearch;

typedef struct ChatNickChange {
    ChatConnection *chat;
    const char *oldNick;
    const char *newNick;
} ChatNickChange;

// Arguments of the nick changed callback.
typedef struct ChatNickChangeArgs {
    const char *channel;
    const char *oldNick;
    const char *newNick;
} ChatNickChangeArgs;

// Arguments of the user mode changed callback.
typedef struct ChatUserModeArgs {
    const char *channel;
    const char *nick;
    int mode;
} ChatUserModeArgs;

typedef struct ChatUserInfo {
    const char *nick;
    const char *user;
    const char *address;
} ChatUserInfo;

// User callbacks
void ciFreeCallbackData(ChatCallback *callback);
ChatResult ciInitCallbacks(ChatConnection *chat);
void ciCleanupCallbacks(ChatConnection *chat);
BOOL ciAddCallback_(ChatConnection *chat, int type, void *func, u32 *src, void *user, int id, char *channel, int size);
void ciCallCallback(ChatConnection *chat, ChatCallback *callback);
void ciCallCallbacks(ChatConnection *chat, int id);
int ciGetCallbackIndexByID(ChatConnection *chat, int id);
ChatResult ciCheckCallbacksForID(ChatConnection *chat, int id);

// Frees one queued callback (array element destructor).
void ciCallbacksArrayElementFreeFn(void *element);

// Channels
int ciHashString(const signed char *s, int numBuckets);
int ciChannelTableHashFn(const void *element, int numBuckets);
int ciChannelTableCompareFn(const void *first, const void *second);
void ciChannelTableElementFreeFn(void *element);
int ciUserTableHashFn(const void *element, int numBuckets);
int ciUserTableCompareFn(const void *first, const void *second);
void ciUserTableElementFreeFn(void *element);
BOOL ciInitChannels(ChatConnection *chat);
void ciCleanupChannels(ChatConnection *chat);
void ciChannelEntering(ChatConnection *chat, const char *channel);
BOOL ciIsEnteringChannel(ChatConnection *chat, const char *channel);
void ciChannelEntered(ChatConnection *chat, const char *name, const ChatChannelCallbacks *callbacks);
void ciChannelLeft(ChatConnection *chat, const char *name);
ChatChannelCallbacks *ciGetChannelCallbacks(ChatConnection *chat, const char *name);
void ciChannelListUsersMap(void *element, void *arg);
void ciChannelListUsers(ChatConnection *chat, const char *name, ChatUserListFunc callback, int param);
BOOL ciInChannel(ChatConnection *chat, const char *name);
BOOL ciGetChannelMode(ChatConnection *chat, const char *name, void *mode);
void ciSetChannelMode(ChatConnection *chat, const char *name, const void *mode);
void ciSetChannelPassword(ChatConnection *chat, const char *name, const char *password);
void ciJoinCallbackCalled(ChatConnection *chat, const char *name);
BOOL ciWasJoinCallbackCalled(ChatConnection *chat, const char *name);
void ciSetChannelTopic(ChatConnection *chat, const char *name, const char *topic);
int ciGetChannelNumUsers(ChatConnection *chat, const char *name);
void ciUserEnteredChannel(ChatConnection *chat, const char *nick, const char *name, int mode, const char *user, const char *address);
void ciUserLeftChannel(ChatConnection *chat, const char *nick, const char *name);
void ciUserEnumChannelsMap(void *element, void *arg);
void ciUserEnumChannels(ChatConnection *chat, const char *nick, ChatUserSearchFunc callback, void *param);
void ciUserChangeNickMap(void *element, void *arg);
void ciUserChangedNick(ChatConnection *chat, const char *oldNick, const char *newNick);
void ciUserChangedMode(ChatConnection *chat, const char *nick, const char *name, int mode, BOOL set);
void ciSetUserBasicInfoMap(void *element, void *arg);
void ciSetUserBasicInfo(ChatConnection *chat, const char *nick, const char *user, const char *address);

// Cipher
void gs_prepare_key(const u8 *key, int keyLength, ChatCipher *cipher);
void gs_crypt(u8 *data, int length, ChatCipher *cipher);
void gs_xcode_buf(s8 *data, int length, const s8 *key);

#define CHAT_REQUEST_TYPE_COUNT 17

// Request (filter) types: ChatRequest.type, the server reply each one waits for.
enum ChatRequestType {
    TYPE_LIST,
    TYPE_JOIN,
    TYPE_TOPIC,
    TYPE_NAMES,
    TYPE_WHOIS,
    TYPE_CMODE,
    TYPE_UMODE,
    TYPE_BAN,
    TYPE_GETBAN,
    TYPE_NICK,
    TYPE_WHO,
    TYPE_CWHO,
    TYPE_GETKEY,
    TYPE_GETCKEY,
    TYPE_GETCHANKEY,
    TYPE_UNQUIET,
    TYPE_CDKEY,
};

// A request sent to the server whose answer is still awaited (element of ChatConnection.requests).
struct ChatRequest {
    int type;       // 0 .. 16, selects data and the callback type (ciFinishFilter)
    u32 expireTime; // current_time time after which the request is ended without an answer
    char *name;     // e.g. the channel or the nick
    char *name2;
    void *callback;  // request type 0: called for each channel of the list
    void *callback2; // request type 0: called with the whole list at the end
    void *param;     // user data passed to the callback
    void *data;      // ChatRequestData, results collected so far
    int id;
    ChatRequest *next;
};

// Key of ciFindFilter.
typedef struct ChatRequestKey {
    int type;
    const char *name;
    const char *name2;
} ChatRequestKey;

// Request type 0: the channels collected so far.
typedef struct ChatChannelListData {
    BOOL started; // the start of the list (321) was received
    int count;
    char **names;
    int *numUsers;
    char **topics;
} ChatChannelListData;

// Request type 1: entering a channel.
typedef struct ChatEnterData {
    ChatChannelCallbacks callbacks;
    BOOL joined; // the JOIN of the own user was received
    char password[32];
} ChatEnterData;

// Request types 3 and 15: the nicks collected so far.
typedef struct ChatNickListData {
    int capacity; // size of nicks and modes
    int count;
    char **nicks;
    int *modes;
} ChatNickListData;

// Request type 4: a WHOIS of a nick.
typedef struct ChatWhoisData {
    char *user;
    char *realName;
    char *address;
    int channelCount;
    char **channels;
} ChatWhoisData;

// Request type 7: a ban by nick (the address of the nick is asked for first).
typedef struct ChatBanData {
    char *channel;
} ChatBanData;

// Request type 8: the ban list of a channel.
typedef struct ChatBanListData {
    int count;
    char **bans;
} ChatBanListData;

// Request types 12, 13 and 14: keys.
typedef struct ChatKeysData {
    int count;
    char **keys;

    union {
        char *channel;      // type 12: all users of the channel (NULL = one user)
        BOOL allUsers;      // type 13
        BOOL broadcastKeys; // type 14
    } arg;

    BOOL broadcastKeys; // type 13
} ChatKeysData;

typedef union ChatRequestData {
    ChatChannelListData channels;
    ChatEnterData enter;
    ChatNickListData nicks;
    ChatWhoisData whois;
    ChatBanData ban;
    ChatBanListData banList;
    ChatKeysData keys;
} ChatRequestData;

// Channel mode letters (ciParseMode).
enum ChatModeType {
    CHAT_MODE_END = 0,
    CHAT_MODE_BAN,                   // b
    CHAT_MODE_INVITE_ONLY,           // i
    CHAT_MODE_LIMIT,                 // l
    CHAT_MODE_PRIVATE,               // p
    CHAT_MODE_SECRET,                // s
    CHAT_MODE_KEY,                   // k
    CHAT_MODE_MODERATED,             // m
    CHAT_MODE_NO_EXTERNAL_MESSAGES,  // n
    CHAT_MODE_ONLY_OPS_CHANGE_TOPIC, // t
    CHAT_MODE_OP,                    // o
    CHAT_MODE_VOICE,                 // v
    CHAT_MODE_U,                     // u
    CHAT_MODE_W,                     // w
    CHAT_MODE_E,                     // e
};

// One change of a parsed channel mode string.
typedef struct ChatModeChange {
    int type; // ChatModeType
    BOOL set;
    const char *arg; // letters b, k, l, o and v
} ChatModeChange;

// Requests
ChatRequest *ciFindFilter(ChatConnection *chat, int count, const ChatRequestKey *keys);
ChatRequest *ciFindGetKeyFilter(ChatConnection *chat, const char *channel);
void ciDestroyFilter(ChatRequest *request);
void ciRemoveFilter(ChatConnection *chat, ChatRequest *target);
void ciFinishFilter(ChatConnection *chat, ChatRequest *request, u32 *results);
void ciFilterTimedout(ChatConnection *chat, ChatRequest *request);
int ciAddFilter(ChatConnection *chat, int type, const char *name, const char *name2, void *callback, void *callback2, void *param, void *data);
ChatModeChange *ciParseMode(const char *modes, const char **args, int argCount);
void ciApplyChangesToMode(ChatChannelMode *mode, ChatModeChange *changes);

// Message types of the message callbacks (server commands PRIVMSG, CTCP ACTION, NOTICE, UTM, ATM).
enum ChatMessageType {
    CHAT_MESSAGE_NORMAL,
    CHAT_MESSAGE_ACTION,
    CHAT_MESSAGE_NOTICE,
    CHAT_MESSAGE_UTM,
    CHAT_MESSAGE_ATM,
};

// Why a user left a channel (ChatUserLeftArgs.reason: server commands PART, QUIT, KICK, KILL).
enum ChatUserLeftReason {
    CHAT_LEFT_PART,
    CHAT_LEFT_QUIT,
    CHAT_LEFT_KICK,
    CHAT_LEFT_KILL,
};

// Arguments of the private message callback (ChatGlobalCallbacks.privateMessage).
typedef struct ChatPrivateMessageArgs {
    const char *nick; // NULL for a message from the server
    const char *message;
    int type; // ChatMessageType
} ChatPrivateMessageArgs;

// Arguments of the invited callback (ChatGlobalCallbacks.invited, callback type 3).
typedef struct ChatInviteArgs {
    const char *channel;
    const char *nick;
} ChatInviteArgs;

// Arguments of the kicked callback (ChatChannelCallbacks.kicked).
typedef struct ChatKickedArgs {
    const char *channel;
    const char *kicker;
    const char *reason;
} ChatKickedArgs;

// Arguments of the user joined callback (ChatChannelCallbacks.userJoined).
typedef struct ChatUserJoinedArgs {
    const char *channel;
    const char *nick;
    int mode; // 0 .. 2
} ChatUserJoinedArgs;

// Arguments of the user left callback (ChatChannelCallbacks.userLeft).
typedef struct ChatUserLeftArgs {
    const char *channel;
    const char *nick;
    int reason;          // ChatUserLeftReason
    const char *message; // part / quit message or reason
    const char *kicker;  // CHAT_LEFT_KICK
} ChatUserLeftArgs;

// Arguments of the topic changed callback (ChatChannelCallbacks.topicChanged).
typedef struct ChatTopicArgs {
    const char *channel;
    const char *topic;
} ChatTopicArgs;

// Arguments of the mode changed callback (ChatChannelCallbacks.modeChanged).
typedef struct ChatChannelModeChangedArgs {
    const char *channel;
    ChatChannelMode *mode;
} ChatChannelModeChangedArgs;

// Arguments of the broadcast key changed callback (ChatChannelCallbacks.broadcastKeyChanged).
typedef struct ChatBroadcastKeyArgs {
    const char *channel;
    const char *nick; // NULL for a key of the channel
    const char *key;
    const char *value;
} ChatBroadcastKeyArgs;

// Arguments of the per channel callback of a channel list request (ChatRequest.callback, callback type 13).
typedef struct ChatChannelListEntryArgs {
    BOOL success;
    int index;
    const char *channel;
    const char *topic;
    int numUsers;
    int unk_14;
} ChatChannelListEntryArgs;

// ChatConnection.fillInUserCallback: gets the own address (from the 302 reply) and may write a user name.
typedef void (*ChatFillInUserFunc)(ChatConnection *chat, int address, char *user, void *param);

// Result of an enter request (request type 1, second result word).
enum ChatEnterResult {
    CHAT_ENTER_SUCCESS,
    CHAT_ENTER_NO_SUCH_CHANNEL,   // 403
    CHAT_ENTER_CHANNEL_FULL,      // 471
    CHAT_ENTER_INVITE_ONLY,       // 473
    CHAT_ENTER_BANNED,            // 474
    CHAT_ENTER_BAD_PASSWORD,      // 475
    CHAT_ENTER_TOO_MANY_CHANNELS, // 405
    CHAT_ENTER_TIMED_OUT,         // no answer
    CHAT_ENTER_BAD_CHANNEL_NAME,  // 476
};

// Server line handlers (table ciServerMessageHandlers)
void ciPrivmsgHandler(ChatConnection *chat, ChatMessage *message);
void ciNoticeHandler(ChatConnection *chat, ChatMessage *message);
void ciUTMHandler(ChatConnection *chat, ChatMessage *message);
void ciATMHandler(ChatConnection *chat, ChatMessage *message);
void ciPingHandler(ChatConnection *chat, ChatMessage *message);
void ciNickHandler(ChatConnection *chat, ChatMessage *message);
void ciJoinHandler(ChatConnection *chat, ChatMessage *message);
void ciPartHandler(ChatConnection *chat, ChatMessage *message);
void ciKickHandler(ChatConnection *chat, ChatMessage *message);
void ciQuitEnumChannelsCallback(ChatConnection *chat, const char *nick, ChatChannel *channel, void *param);
void ciQuitHandler(ChatConnection *chat, ChatMessage *message);
void ciKillEnumChannelsCallback(ChatConnection *chat, const char *nick, ChatChannel *channel, void *param);
void ciKillHandler(ChatConnection *chat, ChatMessage *message);
void ciTopicHandler(ChatConnection *chat, ChatMessage *message);
void ciModeHandler(ChatConnection *chat, ChatMessage *message);
void ciErrorHandler(ChatConnection *chat, ChatMessage *message);
void ciInviteHandler(ChatConnection *chat, ChatMessage *message);
void ciNameReplyHandler(ChatConnection *chat, ChatMessage *message);
void ciEndOfNamesHandler(ChatConnection *chat, ChatMessage *message);
void ciRplTopicHandler(ChatConnection *chat, ChatMessage *message);
void ciRplNoTopicHandler(ChatConnection *chat, ChatMessage *message);
void ciErrNickInUseHandler(ChatConnection *chat, ChatMessage *message);
void ciRplWhoReplyHandler(ChatConnection *chat, ChatMessage *message);
void ciRplEndOfWhoHandler(ChatConnection *chat, ChatMessage *message);
char *ciParseValue(const char *text, int *length);
void ciRplGetKeyHandler(ChatConnection *chat, ChatMessage *message);
void ciRplEndGetKeyHandler(ChatConnection *chat, ChatMessage *message);
void ciRplGetCKeyHandler(ChatConnection *chat, ChatMessage *message);
void ciRplEndGetCKeyHandler(ChatConnection *chat, ChatMessage *message);
void ciRplGetChanKeyHandler(ChatConnection *chat, ChatMessage *message);
void ciRplUserIPHandler(ChatConnection *chat, ChatMessage *message);
void ciRplListStartHandler(ChatConnection *chat, ChatMessage *message);
void ciRplListHandler(ChatConnection *chat, ChatMessage *message);
void ciRplListEndHandler(ChatConnection *chat, ChatMessage *message);
void ciRplChannelModeIsHandler(ChatConnection *chat, ChatMessage *message);
void ciRplWhoisUserHandler(ChatConnection *chat, ChatMessage *message);
void ciRplWhoisChannelsHandler(ChatConnection *chat, ChatMessage *message);
void ciRplEndOfWhoisHandler(ChatConnection *chat, ChatMessage *message);
void ciRplBanListHandler(ChatConnection *chat, ChatMessage *message);
void ciRplEndOfBanListHandler(ChatConnection *chat, ChatMessage *message);
void ciRplWelcomeHandler(ChatConnection *chat, ChatMessage *message);
void ciRplSecureKeyHandler(ChatConnection *chat, ChatMessage *message);
void ciRplCDKeyHandler(ChatConnection *chat, ChatMessage *message);
void ciRplLoginHandler(ChatConnection *chat, ChatMessage *message);
void ciErrNoSuchChannelHandler(ChatConnection *chat, ChatMessage *message);
void ciErrTooManyChannelsHandler(ChatConnection *chat, ChatMessage *message);
void ciErrChannelIsFullHandler(ChatConnection *chat, ChatMessage *message);
void ciErrInviteOnlyChanHandler(ChatConnection *chat, ChatMessage *message);
void ciErrBannedFromChanHandler(ChatConnection *chat, ChatMessage *message);
void ciErrBadChannelKeyHandler(ChatConnection *chat, ChatMessage *message);
void ciErrBadChanMaskHandler(ChatConnection *chat, ChatMessage *message);
void ciErrNoSuchNickHandler(ChatConnection *chat, ChatMessage *message);
void ciErrErroneusNicknameHandler(ChatConnection *chat, ChatMessage *message);
void ciErrLoginFailedHandler(ChatConnection *chat, ChatMessage *message);
void ciErrNoUniqueNickHandler(ChatConnection *chat, ChatMessage *message);
void ciErrUniqueNickExpiredHandler(ChatConnection *chat, ChatMessage *message);
void ciErrRegisterNickFailedHandler(ChatConnection *chat, ChatMessage *message);

// OVY_0 network library functions used by the chat client
u32 current_time(void);
void *DWCi_GsMalloc(int size);
void *DWCi_GsRealloc(void *ptr, int size);
void DWCi_GsFree(void *ptr);
void *ArrayNew(int elemSize, int count, void (*freeElement)(void *));
void ArrayFree(void *array);
void *ArrayNth(void *array, int i);
void ArrayAppend(void *array, void *elem);
void ArrayRemoveAt(void *array, int i);
void ArrayDeleteAt(void *array, int i);
int ArraySearch(void *array, const void *key, int (*compare)(const void *, const void *), int start, int sorted);
void *TableNew2(int elemSize, int numBuckets, int unused, int (*hash)(const void *, int), int (*compare)(const void *, const void *), void (*freeElement)(void *));
void TableFree(void *table);
int TableCount(void *table);
void TableEnter(void *table, void *elem);
int TableRemove(void *table, void *elem);
void *TableLookup(void *table, const void *key);
void TableMap(void *table, void (*func)(void *element, void *arg), void *arg);
int ArrayLength(void *array);
char *goastrdup(const char *str);

// MSL functions without a header here
void __msl_assertion_failed(const char *expr, const char *file, const char *func, int line);
char *strchr(const char *str, int c);
int strnicmp(const char *a, const char *b);
long atol(const char *str);
int sprintf(char *buf, const char *fmt, ...);
int vsprintf(char *buf, const char *fmt, va_list args);
extern u8 __lower_mapC[];

// Data of the connection and the public functions: assert texts, function names and command formats.
extern int gChatCryptVersion; // 0, the number sent with the CRYPT command
extern const char gChatStr_ciThink[];
extern const char gChatStr_ciSendNick[];
extern const char gChatStr_ciSendUser[];
extern const char gChatStr_ciSendLogin[];
extern const char gChatStr_chatInChannelA[];
extern const char gChatStr_chatDisconnect[];
extern const char gChatStr_chatEnumUsersA[];
extern const char gChatStr_chatConnectDoit[];
extern const char gChatStr_chatEnumChannelsA[];
extern const char gChatStr_chatEnterChannelA[];
extern const char gChatStr_chatLeaveChannelA[];
extern const char gChatStr_ciHandleDisconnect[];
extern const char gChatStr_chatRetryWithNickA[];
extern const char gChatStr_ciSendGetChannelKey[];
extern const char gChatStr_ciEnumUsersCallback[];
extern const char gChatStr_chatGetChannelKeysA[];
extern const char gChatStr_chatSetChannelKeysA[];
extern const char gChatStr_chatSetChannelModeA[];
extern const char gChatStr_chatGetChannelModeA[];
extern const char gChatStr_ciNickError[];
extern const char gChatStr_chatSetChannelLimitA[];
extern const char gChatStr_chatSendUserMessageA[];
extern const char gChatStr_ciProcessServerMessage[];
extern const char gChatStr_chatRegisterUniqueNickA[];
extern const char gChatStr_chatGetChannelNumUsersA[];
extern const char gChatStr_chatSendChannelMessageA[];
extern const char gChatStr_MessageNeNULL_2[];
extern const char gChatStr_ChatMainC[];
extern const char gChatStr_ChatNeNULL_4[];
extern const char gChatStr_ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuv_3[];
extern const char gChatStr_Disconnected[];
extern const ChatBytes2 gChatStr_Star_3;
extern const char gChatFmt_NICK[];
extern const char gChatFmt_USER[];
extern const char gChatStr_127_Dot0_Dot0_Dot1[];
extern const char gChatFmt_LOGINPREAUTH[];
extern const char gChatFmt_LOGIN[];
extern const char gChatFmt_LOGIN_2[];
extern const char gChatStr_0_11[];
extern const char gChatStr_Empty_21[];
extern const char gChatStr_ServerAddressNeNULL[];
extern const char gChatStr_CallbacksNeNULL_2[];
extern const char gChatStr_ConnectCallbackNeNULL[];
extern const char gChatStr_NickNeNULL_2[];
extern const char gChatStr_Nick0_Ne0_3[];
extern const char gChatStr_StrlenNickLtMAX_NICK[];
extern const char gChatStr_NamespaceID_Gt0[];
extern const char gChatStr_UniquenickAndUniquenick0[];
extern const char gChatStr_PasswordAndPassword0[];
extern const char gChatStr_NamespaceID_Ge0[];
extern const char gChatStr_EmailAndEmail0[];
extern const char gChatStr_ProfilenickAndProfilenick0[];
extern const char gChatStr_AuthtokenAndAuthtoken0[];
extern const char gChatStr_PartnerchallengeAndPartnerchallenge0[];
extern const char gChatStr_preauth[];
extern const char gChatStr_GamenameAndGamename0[];
extern const char gChatStr_SecretKeyAndSecretKey0[];
extern const char gChatFmt_CRYPT_Des[];
extern const char gChatStr_USRIP_2[];
extern const char gChatFmt_NICK_2[];
extern const char gChatFmt_REGISTERNICK[];
extern const char gChatStr_QUIT_Later[];
extern const char gChatStr_CallbackAllNeNULL_OrCallbackEachNeNULL[];
extern const char gChatFmt_LIST[];
extern const char gChatStr_ChannelNeNULL_3[];
extern const char gChatStr_Channel0_Ne0_3[];
extern const char gChatFmt_JOIN[];
extern const char gChatFmt_PART[];
extern const char gChatStr_TypeEqCHAT_MESSAGE_OrTypeEqCHAT_ACTION_OrTypeEq[];
extern const char gChatFmt_PRIVMSG[];
extern const char gChatFmt_PRIVMSG_ACTION[];
extern const char gChatFmt_NOTICE[];
extern const char gChatFmt_UTM[];
extern const char gChatFmt_ATM[];
extern const char gChatStr_CallbackNeNULL_4[];
extern const char gChatStr_ModeNeNULL_2[];
extern const char gChatStr_XiXpXsXmXnXtXlXe[];
extern const char gChatFmt_SpaceInt[];
extern const char gChatFmt_MODE_2[];
extern const char gChatFmt_MODE_3[];
extern const char gChatStr_LimitGe0[];
extern const char gChatFmt_MODE_L[];
extern const char gChatFmt_MODE_L_2[];
extern const char gChatStr_NumUsersGe0[];
extern const char gChatStr_ParamNeNULL[];
extern const char gChatStr_DataCallbackNeNULL_3[];
extern const char gChatFmt_NAMES[];
extern const char gChatStr_UserNeNULL_3[];
extern const char gChatStr_User0_Ne0_3[];
extern const char gChatStr_StrlenUserLtMAX_USER[];
extern const char gChatFmt_BackslashStrBackslashStr[];
extern const char gChatFmt_Int_6[];
extern const char gChatStr_CookieAndCookie0[];
extern const char gChatStr_NumGe0[];
extern const char gChatFmt_SETCHANKEY[];
extern const char gChatFmt_SETCKEY[];
extern const char gChatStr_ChannelAndChannel0[];
extern const char gChatStr_NotNumOrKeys[];
extern const char gChatFmt_GETCHANKEY_0[];
extern const char gChatFmt_GETCKEY_0[];
extern const char gChatStr_B_UnderscoreStar_2[];

// The key that asks for the broadcast keys of a user (5 bytes with the terminator).
extern const struct {
    ChatBytes3 first;
    ChatBytes2 last;
} gChatStr_BackslashB_UnderscoreStar;

// Cookie buffer and counter of ciGetNextCookie.
extern char ciCookieBuffer[];
extern int ciCookieCounter;

// Data of the socket layer.
extern const char gChatStr_ciParseUser[];
extern const char gChatStr_ciSocketSend[];
extern const char gChatStr_ciParseParam[];
extern const char gChatStr_ciSocketSendf[];
extern const char gChatStr_ciSocketThink[];
extern const char gChatStr_ciParseMessage[];
extern const char gChatStr_ciSocketConnect[];
extern const char gChatStr_ciSocketThinkSend[];
extern const char gChatStr_ciSocketThinkRecv[];
extern const char gChatStr_ciSocketDisconnect[];
extern const char gChatStr_ciBufferInit[];
extern const char gChatStr_ciSocketInit[];
extern const char gChatStr_ciBufferPreAppend[];
extern const char gChatStr_ciBufferClipFront[];
extern const char gChatStr_ciSocketRecv[];
extern const char gChatStr_BufferNeNULL_2[];
extern const char gChatStr_ChatSocketC[];
extern const char gChatStr_BufferNeNULL_3[];
extern const char gChatStr_BufferSizeGe0[];
extern const char gChatStr_BufferSizeBUFFER_INC_Eq0[];
extern const char gChatStr_BufferLengthGe0[];
extern const char gChatStr_BufferLengthLeBufferSize[];
extern const char gChatStr_LenGe0_2[];
extern const char gChatStr_LenLeSHRT_MAX[];
extern const char gChatStr_LenLeBufferLength[];
extern const char gChatStr_SockNeNULL[];
extern const char gChatStr_SockNeNULL_2[];
extern const char gChatStr_SockConnectStateEqCiNotConnectedOrSock[];
extern const char gChatStr_SockInputQueueNeNULL[];
extern const char gChatStr_SockInputQueueSizeGe0[];
extern const char gChatStr_SockInputQueueSizeBUFFER_INC_Eq0[];
extern const char gChatStr_SockInputQueueLengthGe0[];
extern const char gChatStr_SockInputQueueLengthLeSockInputQueueSize[];
extern const char gChatStr_SockOutputQueueNeNULL[];
extern const char gChatStr_SockOutputQueueSizeGe0[];
extern const char gChatStr_SockOutputQueueSizeBUFFER_INC_Eq0[];
extern const char gChatStr_SockOutputQueueLengthGe0[];
extern const char gChatStr_SockOutputQueueLengthLeSockOutputQueueSize[];
extern const char gChatStr_ServerAddressNeNULL_2[];
extern const char gChatStr_PortGe0[];
extern const char gChatStr_PortLeUSHRT_MAX[];
extern const char gChatStr_SockConnectStateEqCiNotConnected[];
extern const char gChatStr_SockConnectStateEqCiConnected[];
extern const char gChatStr_0_12[];
extern const char gChatStr_PTextNeNULL[];
extern const char gChatStr_MessageNeNULL_3[];
extern const char gChatStr_SpaceColon_2[];
extern const char gChatStr_Space_4[];

// Line buffer of ciSocketSendf (4096 bytes).
extern char ciSendfBuffer[];

// Data of the requests and the server message handlers.
extern const char gChatStr_ciGetNextID[];
extern const char gChatStr_ciAddFilter[];
extern const char gChatStr_ciParseMode[];
extern const char gChatStr_ciFindFilter[];
extern const char gChatStr_ciFilterThink[];
extern const char gChatStr_ciRemoveFilter[];
extern const char gChatStr_ciFinishFilter[];
extern const char gChatStr_ciAddJOINFilter[];
extern const char gChatStr_ciDestroyFilter[];
extern const char gChatStr_ciCleanupFilters[];
extern const char gChatStr_ciFilterTimedout[];
extern const char gChatStr_ciFindGetKeyFilter[];
extern const char gChatStr_ciCheckFiltersForID[];
extern const char gChatStr_ciApplyChangesToMode[];
extern const char gChatStr_ChatNeNULL_3[];
extern const char gChatStr_ChatHandlersC[];
extern const char gChatStr_NumMatchesGt0[];
extern const char gChatStr_matches[];
extern const char gChatStr_MatchesI_TypeGe0_AndMatchesI_TypeLtNUM_TYPES[];
extern const char gChatStr_channel[];
extern const char gChatStr_Channel0[];
extern const char gChatStr_FilterNeNULL[];
extern const char gChatStr_filter[];
extern const char gChatStr_FilterTypeGe0_AndFilterTypeLtNUM_TYPES[];
extern const char gChatStr_0_10[];
extern const char gChatStr_TimedOut[];
extern const char gChatStr_ID_Gt0[];
extern const char gChatStr_PasswordNeNULL[];
extern const char gChatStr_StrlenPasswordLtMAX_PASSWORD[];
extern const char gChatStr_B_UnderscoreStar[];
extern const char gChatStr_ModeNeNULL[];
extern const char gChatStr_ciParseValue[];
extern const char gChatStr_ciUTMHandler[];
extern const char gChatStr_ciATMHandler[];
extern const char gChatStr_ciPingHandler[];
extern const char gChatStr_ciNickHandler[];
extern const char gChatStr_ciJoinHandler[];
extern const char gChatStr_ciPartHandler[];
extern const char gChatStr_ciKickHandler[];
extern const char gChatStr_ciQuitHandler[];
extern const char gChatStr_ciKillHandler[];
extern const char gChatStr_ciModeHandler[];
extern const char gChatStr_ciTopicHandler[];
extern const char gChatStr_ciErrorHandler[];
extern const char gChatStr_ciNoticeHandler[];
extern const char gChatStr_ciInviteHandler[];
extern const char gChatStr_ciPrivmsgHandler[];
extern const char gChatStr_ciRplListHandler[];
extern const char gChatStr_ciRplCDKeyHandler[];
extern const char gChatStr_ciRplLoginHandler[];
extern const char gChatStr_ciRplTopicHandler[];
extern const char gChatStr_ciRplGetKeyHandler[];
extern const char gChatStr_ciRplUserIPHandler[];
extern const char gChatStr_ciNameReplyHandler[];
extern const char gChatStr_ciRplGetCKeyHandler[];
extern const char gChatStr_ciEndOfNamesHandler[];
extern const char gChatStr_ciRplBanListHandler[];
extern const char gChatStr_ciRplNoTopicHandler[];
extern const char gChatStr_ciRplWelcomeHandler[];
extern const char gChatStr_ciRplWhoReplyHandler[];
extern const char gChatStr_ciRplEndOfWhoHandler[];
extern const char gChatStr_ciRplSecureKeyHandler[];
extern const char gChatStr_ciRplEndGetKeyHandler[];
extern const char gChatStr_ciRplListStartHandler[];
extern const char gChatStr_ciRplWhoisUserHandler[];
extern const char gChatStr_ciErrNickInUseHandler[];
extern const char gChatStr_ciRplEndGetCKeyHandler[];
extern const char gChatStr_ciRplGetChanKeyHandler[];
extern const char gChatStr_ciRplEndOfWhoisHandler[];
extern const char gChatStr_ciErrBadChanMaskHandler[];
extern const char gChatStr_ciErrLoginFailedHandler[];
extern const char gChatStr_ciErrNoUniqueNickHandler[];
extern const char gChatStr_ciRplEndOfBanListHandler[];
extern const char gChatStr_ciErrBadChannelKeyHandler[];
extern const char gChatStr_ciErrNoSuchChannelHandler[];
extern const char gChatStr_ciRplChannelModeIsHandler[];
extern const char gChatStr_ciRplWhoisChannelsHandler[];
extern const char gChatStr_ciErrChannelIsFullHandler[];
extern const char gChatStr_ciQuitEnumChannelsCallback[];
extern const char gChatStr_ciKillEnumChannelsCallback[];
extern const char gChatStr_ciErrInviteOnlyChanHandler[];
extern const char gChatStr_ciErrBannedFromChanHandler[];
extern const char gChatStr_ciErrTooManyChannelsHandler[];
extern const char gChatStr_ciErrErroneusNicknameHandler[];
extern const char gChatStr_ciErrUniqueNickExpiredHandler[];
extern const char gChatStr_ciErrRegisterNickFailedHandler[];
extern const char gChatStr_MessageNumParamsEq2[];
extern const char gChatStr_Empty_20[];
extern const char gChatStr_ACTION[];
extern const char gChatFmt_PONG[];
extern const char gChatStr_MessageNumParamsEq1[];
extern const char gChatStr_StrlenNewNickLtMAX_NICK[];
extern const char gChatStr_NickNe0[];
extern const char gChatFmt_MODE[];
extern const char gChatStr_MessageNumParamsEq2_OrMessageNumParamsEq3[];
extern const char gChatStr_UserNeNULL_2[];
extern const char gChatStr_User0_Ne0_2[];
extern const char gChatStr_ChannelNeNULL_2[];
extern const char gChatStr_Channel0_Ne0_2[];
extern const char gChatStr_ReasonNeNULL[];
extern const char gChatStr_MessageNumParamsGe2[];
extern const char gChatStr_MessageNumParamsEq4[];
extern const char gChatStr_Space_3[];
extern const char gChatStr_Nick0_Ne0_2[];
extern const char gChatStr_Nick1_Ne0[];
extern const char gChatStr_MessageNumParamsEq3[];
extern const char gChatStr_Star_2[];
extern const char gChatStr_ConnectionConnecting[];
extern const char gChatStr_MessageNumParamsEq8[];
extern const char gChatStr_flags[];
extern const char gChatStr_len[];
extern const char gChatStr_MessageNumParamsEq5[];
extern const char gChatStr_BCAST[];
extern const char gChatStr_b_[];
extern const char gChatStr_MessageNumParamsGe1[];
extern const char gChatStr_DataNeNULL_2[];
extern const char gChatStr_MessageNumParamsGe3[];
extern const char gChatStr_MessageNumParamsEq6[];
extern const char gChatStr_DataChannelNeNULL[];
extern const char gChatStr_DataChannel0_Ne0[];
extern const char gChatFmt_MODE_B[];
extern const char gChatStr_MessageNumParamsGe3_2[];
extern const char gChatStr_DataNumBansGe0[];
extern const char gChatStr_USRIP[];
extern const char gChatStr_Backslash_2[];

// Data of the channel table.
extern const char gChatStr_ciInChannel[];
extern const char gChatStr_ciHashString[];
extern const char gChatStr_ciChannelLeft[];
extern const char gChatStr_ciSetChannelMode[];
extern const char gChatStr_ciChannelEntered[];
extern const char gChatStr_ciGetChannelMode[];
extern const char gChatStr_ciUserChangedNick[];
extern const char gChatStr_ciUserChangedMode[];
extern const char gChatStr_ciUserLeftChannel[];
extern const char gChatStr_ciCleanupChannels[];
extern const char gChatStr_ciUserTableHashFn[];
extern const char gChatStr_ciSetChannelTopic[];
extern const char gChatStr_ciChannelEntering[];
extern const char gChatStr_ciUserEnumChannels[];
extern const char gChatStr_ciSetUserBasicInfo[];
extern const char gChatStr_ciChannelListUsers[];
extern const char gChatStr_ciUserChangeNickMap[];
extern const char gChatStr_ciIsEnteringChannel[];
extern const char gChatStr_ciUserTableCompareFn[];
extern const char gChatStr_ciSetChannelPassword[];
extern const char gChatStr_ciJoinCallbackCalled[];
extern const char gChatStr_ciChannelTableHashFn[];
extern const char gChatStr_ciGetChannelNumUsers[];
extern const char gChatStr_ciUserEnteredChannel[];
extern const char gChatStr_ciGetChannelCallbacks[];
extern const char gChatStr_ciChannelListUsersMap[];
extern const char gChatStr_ciSetUserBasicInfoMap[];
extern const char gChatStr_ciUserEnumChannelsMap[];
extern const char gChatStr_ciWasJoinCallbackCalled[];
extern const char gChatStr_ciChannelTableCompareFn[];
extern const char gChatStr_ciUserTableElementFreeFn[];
extern const char gChatStr_ciChannelTableElementFreeFn[];
extern const char gChatStr_StrNeNULL[];
extern const char gChatStr_ChatChannelC[];
extern const char gChatStr_Str0_Ne0[];
extern const char gChatStr_ElemNeNULL[];
extern const char gChatStr_NumBucketsGt0[];
extern const char gChatStr_Elem1_NeNULL[];
extern const char gChatStr_Elem2_NeNULL[];
extern const char gChatStr_Str1_NeNULL[];
extern const char gChatStr_Str2_NeNULL[];
extern const char gChatStr_Str1_0_Ne0[];
extern const char gChatStr_Str2_0_Ne0[];
extern const char gChatStr_ChatNeNULL_2[];
extern const char gChatStr_chatChannel[];
extern const char gChatStr_ChannelNeNULL[];
extern const char gChatStr_Channel0_Ne0[];
extern const char gChatStr_StrlenChannelLtMAX_CHANNEL[];
extern const char gChatStr_CallbacksNeNULL[];
extern const char gChatStr_Empty_19[];
extern const char gChatStr_ClientDataNeNULL[];
extern const char gChatStr_UserNameNeNULL[];
extern const char gChatStr_UserName0_Ne0[];
extern const char gChatStr_StrlenUserNameLtMAX_NAME[];
extern const char gChatStr_DataNumUsersGe0[];
extern const char gChatStr_0_9[];
extern const char gChatStr_CallbackNeNULL_3[];
extern const char gChatStr_NameNeNULL[];
extern const char gChatStr_Name0_Ne0[];
extern const char gChatStr_StrlenNameLtMAX_NAME[];
extern const char gChatStr_ModeGe0_AndModeLe3[];
extern const char gChatStr_TableLookupChatChannelUsersChatUserNeNULL[];
extern const char gChatStr_UserNeNULL[];
extern const char gChatStr_User0_Ne0[];
extern const char gChatStr_StrlenUserLtMAX_NAME[];
extern const char gChatStr_ChannelUsersNeNULL[];
extern const char gChatStr_DataUserNeNULL[];
extern const char gChatStr_DataUserName0_Ne0[];
extern const char gChatStr_DataCallbackNeNULL_2[];
extern const char gChatStr_DataNewNickNeNULL[];
extern const char gChatStr_DataNewNick0_Ne0[];
extern const char gChatStr_StrlenDataNewNickLtMAX_NAME[];
extern const char gChatStr_DataOldNickNeNULL[];
extern const char gChatStr_DataOldNick0_Ne0[];
extern const char gChatStr_StrlenDataOldNickLtMAX_NAME[];
extern const char gChatStr_RcodeNe0[];
extern const char gChatStr_OldNickNeNULL[];
extern const char gChatStr_OldNick0_Ne0[];
extern const char gChatStr_StrlenOldNickLtMAX_NAME[];
extern const char gChatStr_NewNickNeNULL[];
extern const char gChatStr_NewNick0_Ne0[];
extern const char gChatStr_StrlenNewNickLtMAX_NAME[];
extern const char gChatStr_NickNeNULL[];
extern const char gChatStr_Nick0_Ne0[];
extern const char gChatStr_StrlenNickLtMAX_NAME[];

// Data of the callback queue.
extern const char gLobbyStr_DataNeNULL[];
extern const char gLobbyStr_ChatCallbacksC[];
extern const char gChatStr_DataTypeGe0[];
extern const char gChatStr_DataTypeLtCALLBACK_NUM[];
extern const char gChatStr_DataCallbackNeNULL[];
extern const char gChatStr_DataCallbackParamsNeNULL[];
extern const char gChatStr_DataID_Ge0[];
extern const char gChatStr_ciAddCallback_[];
extern const char gChatStr_ciCallCallback[];
extern const char gChatStr_ciCallCallbacks[];
extern const char gChatStr_ciFreeCallbackData[];
extern const char gChatStr_ciCleanupCallbacks[];
extern const char gChatStr_ciGetCallbackIndexByID[];
extern const char gChatStr_0_8[];
extern const char gChatStr_ChatNeNULL[];
extern const char gChatStr_TypeGe0[];
extern const char gChatStr_TypeLtCALLBACK_NUM[];
extern const char gChatStr_ConnectionCallbackListNeNULL[];
extern const char gChatStr_CallbackNeNULL_2[];
extern const char gChatStr_CallbackParamsNeNULL[];
extern const char gChatStr_CallbackParamsSizeGt0[];
extern const char gChatStr_ID_Ge0[];
extern const char gChatStr_SrcParamsNumChannelsGe0[];
extern const char gChatStr_SrcParamsNumUsersNeNULL[];
extern const char gChatStr_SrcParamsNumUsersGe0[];
extern const char gChatStr_SrcParamsModesNeNULL[];
extern const char gChatStr_SrcParamsNumBansGe0[];
extern const char gChatStr_SrcParamsNumSuggestedNicksGe0[];
extern const char gChatStr_SrcParamsNumGe0[];

#endif // POKEHEARTGOLD_LIB_INCLUDE_DWC_CHAT_INTERNAL_H
