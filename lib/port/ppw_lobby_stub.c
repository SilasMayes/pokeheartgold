// The Wi-Fi Plaza lobby API for builds without the lobby library (Android, as in the Platinum port,
// where the game code skips these calls). Joining the Plaza fails at the first step with a session
// error, so the game shows its "could not connect" message; nothing else can be reached from there.
// Port only (not part of the make build).

#include "global.h"

#include "ppw_lobby_state.h"
#include "wifi_plaza/wifi_plaza_internal.h"

// PPW_LobbyToErrorCode, as the library maps a session error (LobbyChat_ToErrorCode)
#define PPW_STUB_ERROR_CODE (42000 + PPW_LOBBY_ERROR_SESSION)

enum PPWLobbyResult PPW_LobbyInitializeAsync(const char *gameName, const char *secretKey, int prefix, const PPWLobbyCallbacks *callbacks, const DWCUserData *userData, const void *playerData, u32 playerDataSize) {
    return PPW_LOBBY_RESULT_ERROR_SESSION;
}

enum PPWLobbyState PPW_LobbyProcess(void) {
    return PPW_LOBBY_STATE_ERROR;
}

enum PPWLobbyResult PPW_LobbyShutdownAsync(void) {
    return PPW_LOBBY_RESULT_SUCCESS;
}

enum PPWLobbyError PPW_LobbyGetLastError(void) {
    return PPW_LOBBY_ERROR_SESSION;
}

enum PPWLobbyError PPW_LobbyInitResultToLastError(int result) {
    return result == PPW_LOBBY_RESULT_SUCCESS ? PPW_LOBBY_ERROR_NONE : PPW_LOBBY_ERROR_SESSION;
}

int PPW_LobbyToErrorCode(int error) {
    return PPW_STUB_ERROR_CODE;
}

int PPW_LobbyGetMyUserId(void) {
    return 0;
}

enum PPWLobbyResult PPW_LobbyGetTimeInfo(PPWLobbyTimeInfo *timeInfo) {
    return PPW_LOBBY_RESULT_ERROR_STATE;
}

enum PPWLobbyResult PPW_LobbyGetSchedule(PPWLobbyScheduleRecord *records, u32 *size) {
    return PPW_LOBBY_RESULT_ERROR_STATE;
}

enum PPWLobbyChannelState PPW_LobbyGetSubChannelState(void) {
    return PPW_LOBBY_CHANNEL_STATE_NONE;
}

enum PPWLobbyResult PPW_LobbyJoinSubChannelAsync(int channel) {
    return PPW_LOBBY_RESULT_ERROR_STATE;
}

enum PPWLobbyResult PPW_LobbyLeaveSubChannel(void) {
    return PPW_LOBBY_RESULT_ERROR_STATE;
}

enum PPWLobbyResult PPW_LobbySetChannelData(int userId, enum PPWLobbyChannelKind channel, const char *key, const void *data, u32 size) {
    return PPW_LOBBY_RESULT_ERROR_STATE;
}

enum PPWLobbyResult PPW_LobbyGetChannelDataAsync(int userId, enum PPWLobbyChannelKind channel, const char *key, u32 param) {
    return PPW_LOBBY_RESULT_ERROR_STATE;
}

enum PPWLobbyResult PPW_LobbySendChannelBinaryMessage(int channel, int type, const void *data, int size) {
    return PPW_LOBBY_RESULT_ERROR_STATE;
}

enum PPWLobbyResult PPW_LobbySendPlayerBinaryMessage(int userId, int type, const void *data, int size) {
    return PPW_LOBBY_RESULT_ERROR_STATE;
}

enum PPWLobbyResult PPW_LobbyUpdateMyProfile(const void *data, u32 size, int force) {
    return PPW_LOBBY_RESULT_ERROR_STATE;
}

enum PPWLobbyResult PPW_LobbySubmitQuestionnaire(int mode) {
    return PPW_LOBBY_RESULT_ERROR_STATE;
}

enum PPWLobbyResult PPW_LobbyStartRecruit(WiFiPlazaLobbyMatch *match) {
    return PPW_LOBBY_RESULT_ERROR_STATE;
}

enum PPWLobbyResult PPW_LobbyUpdateRecruitInfo(WiFiPlazaLobbyMatch *match) {
    return PPW_LOBBY_RESULT_ERROR_STATE;
}

enum PPWLobbyResult PPW_LobbyStopRecruit(void) {
    return PPW_LOBBY_RESULT_ERROR_STATE;
}
