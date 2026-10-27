#ifndef POKEHEARTGOLD_PPW_LOBBY_STATE_H
#define POKEHEARTGOLD_PPW_LOBBY_STATE_H

// LobbyChatManager.state: how far the lobby chat session has come
enum LobbyChatState {
    LOBBY_CHAT_STATE_INIT,
    LOBBY_CHAT_STATE_CONNECTING,
    LOBBY_CHAT_STATE_CONNECTED, // logged in, waits 60 frames before READY
    LOBBY_CHAT_STATE_READY,
    LOBBY_CHAT_STATE_DISCONNECTING,
    LOBBY_CHAT_STATE_ERROR,
};

// The state of the lobby library (gPPWLobbyWork->state), returned by PPW_LobbyProcess
enum PPWLobbyState {
    PPW_LOBBY_STATE_NOT_INITIALIZED,
    PPW_LOBBY_STATE_CONNECTING,
    PPW_LOBBY_STATE_CONNECTED,
    PPW_LOBBY_STATE_WAIT_SCHEDULE,
    PPW_LOBBY_STATE_ENUM_CHANNELS,
    PPW_LOBBY_STATE_SEARCHING_CHANNEL,
    PPW_LOBBY_STATE_ENTER_MAIN_CHANNEL,
    PPW_LOBBY_STATE_WAIT_MAIN_CHANNEL,
    PPW_LOBBY_STATE_READY,
    PPW_LOBBY_STATE_CLOSED,
    PPW_LOBBY_STATE_ERROR,
};

// PPW_LobbyGetSubChannelState
enum PPWLobbyChannelState {
    PPW_LOBBY_CHANNEL_STATE_NONE,
    PPW_LOBBY_CHANNEL_STATE_JOINING,
    PPW_LOBBY_CHANNEL_STATE_JOINED,
    PPW_LOBBY_CHANNEL_STATE_ERROR,
};

// The lobby channels (PPWLobbyChannel.kind, the channel in a player's system profile)
enum PPWLobbyChannelKind {
    PPW_LOBBY_CHANNEL_KIND_MAIN,
    PPW_LOBBY_CHANNEL_KIND_FOOT1, // the footprint channels
    PPW_LOBBY_CHANNEL_KIND_FOOT2,
    PPW_LOBBY_CHANNEL_KIND_CLOCK,
    PPW_LOBBY_CHANNEL_KIND_NEWS,
    PPW_LOBBY_CHANNEL_KIND_INVALID, // no channel; as a message target, one player
};

// How a lobby message carries its data (PPWLobby_SendMessage): as text ("S") or as base64 binary ("B")
enum PPWLobbyMessageFormat {
    PPW_LOBBY_MESSAGE_FORMAT_STRING,
    PPW_LOBBY_MESSAGE_FORMAT_BINARY,
};

// The longest text a lobby message carries, and the most bytes of binary data (base64, it fits that text)
#define PPW_LOBBY_MESSAGE_MAX_LENGTH      400
#define PPW_LOBBY_MESSAGE_MAX_BINARY_SIZE 300

// Who a lobby message is for: the lobby library itself ("S") or the game ("A")
enum PPWLobbyMessageKind {
    PPW_LOBBY_MESSAGE_KIND_SYSTEM,
    PPW_LOBBY_MESSAGE_KIND_USER,
};

// The lobby library's own messages (PPWLobby_HandleSystemMessage)
enum PPWLobbySystemMessage {
    PPW_LOBBY_SYSTEM_MESSAGE_START_SCHEDULE, // the lobby events start
    PPW_LOBBY_SYSTEM_MESSAGE_RECRUIT,        // a player recruits for a match (its PPWLobbyRecruitInfo)
    PPW_LOBBY_SYSTEM_MESSAGE_STOP_RECRUIT,   // a player has stopped recruiting
};

// PPWLobbySchedule.state: how far the questionnaire, the schedule and the lobby events have come
enum PPWLobbyScheduleState {
    PPW_LOBBY_SCHEDULE_STATE_NONE = 0,
    PPW_LOBBY_SCHEDULE_STATE_QUESTIONNAIRE = 2, // the questionnaire has arrived
    PPW_LOBBY_SCHEDULE_STATE_LOADED = 4,        // the schedule of the lobby is loaded
    PPW_LOBBY_SCHEDULE_STATE_STARTED = 5,       // the lobby events run
};

// PPWLobbyPlayer.state: how far a player of the lobby has come (PPWLobbyPlayer_UpdateState)
enum PPWLobbyPlayerState {
    PPW_LOBBY_PLAYER_STATE_NEW,
    PPW_LOBBY_PLAYER_STATE_HAS_PROFILES, // its system and user profiles have arrived
    PPW_LOBBY_PLAYER_STATE_READY,        // its system profile says it is in the main channel
    PPW_LOBBY_PLAYER_STATE_ENTERED,      // the game has been told (onPlayerEnter)
};

// The keys of the lobby timers (the chat's timer map and gPPWLobbyWork->timers), named after what they run
enum PPWLobbyTimer {
    PPW_LOBBY_TIMER_CONNECT_TIMEOUT,
    PPW_LOBBY_TIMER_UPLOAD_SYSTEM_PROFILE,
    PPW_LOBBY_TIMER_UPLOAD_USER_PROFILE,
    PPW_LOBBY_TIMER_SEND_RECRUIT_INFO,
    PPW_LOBBY_TIMER_POLL_CHANNEL_MODE,
    PPW_LOBBY_TIMER_REQUEST_CHANNEL_TIME,
    PPW_LOBBY_TIMER_REQUEST_LOBBY_DATA,
};

// Results of the PPW_Lobby* calls and of the lobby chat commands they pass through
enum PPWLobbyResult {
    PPW_LOBBY_RESULT_SUCCESS,
    PPW_LOBBY_RESULT_ERROR_ALLOC,
    PPW_LOBBY_RESULT_ERROR_SESSION,
    PPW_LOBBY_RESULT_ERROR_PARAM,
    PPW_LOBBY_RESULT_ERROR_STATE,
    PPW_LOBBY_RESULT_ERROR_CHANNEL,
    PPW_LOBBY_RESULT_ERROR_NODATA,
    PPW_LOBBY_RESULT_ERROR_CONDITION, // the library is in PPW_LOBBY_STATE_ERROR
};

// Results of the lobby's web requests (PPWLobby_ParseWebResponse), as the own record, schedule, special visitor and
// questionnaire callbacks receive them
enum PPWLobbyWebResult {
    PPW_LOBBY_WEB_RESULT_SUCCESS,
    PPW_LOBBY_WEB_RESULT_SERVER_ERROR, // the server answered with error code 6
    PPW_LOBBY_WEB_RESULT_INVALID,      // no answer, a short or unexpected answer, or another server error code
};

// PPW_LobbyGetLastError
enum PPWLobbyError {
    PPW_LOBBY_ERROR_NONE,
    PPW_LOBBY_ERROR_UNKNOWN,
    PPW_LOBBY_ERROR_ALLOC,
    PPW_LOBBY_ERROR_SESSION,
    PPW_LOBBY_ERROR_SCHEDULE,      // the schedule answer was bad
    PPW_LOBBY_ERROR_VIP,           // the VIP list answer was bad
    PPW_LOBBY_ERROR_CHECK_PROFILE, // the profile check answer was bad
    PPW_LOBBY_ERROR_QUESTIONNAIRE, // the questionnaire answer was bad
};

#ifdef __cplusplus
// The last error (PPW_LobbyGetLastError) a failed lobby chat call leaves behind; PPW_LOBBY_ERROR_NONE when it is not fatal
class PPWLobbyErrorMap {
public:
    PPWLobbyError Map(PPWLobbyResult result) const;
};

inline PPWLobbyError PPWLobbyErrorMap::Map(PPWLobbyResult result) const {
    PPWLobbyError error = PPW_LOBBY_ERROR_NONE;
    switch (result) {
    case PPW_LOBBY_RESULT_ERROR_ALLOC:
        error = PPW_LOBBY_ERROR_ALLOC;
        break;
    case PPW_LOBBY_RESULT_ERROR_SESSION:
        error = PPW_LOBBY_ERROR_SESSION;
        break;
    }
    return error;
}
#endif

#endif // POKEHEARTGOLD_PPW_LOBBY_STATE_H
