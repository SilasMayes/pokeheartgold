#include "global.h"

#include "wifi_setup/wifi_setup.h"
#include "wifi_setup/wifi_setup_wcm.h"

// Number of tries and the delay between them
typedef struct WifiSetupAossRetry {
    s16 max;
    s16 delay;
} WifiSetupAossRetry;

typedef struct AossSession {
    SocAddress address;
    WifiSetupPollTime time;
    SocPollFd set;
    int length;
    SocAddress remote;
    int attempts;
    int option;
    WifiSetupAossRetry retry;
    WifiSetupAossRetry connection;
    WifiSetupAossAddresses config;
    WifiSetupAossConnectInfo context;
    WifiSetupAossPacketParams params;
} AossSession;

static const WifiSetupAossRetry sWifiSetupUnsetConnection = {
    .max = -1,
    .delay = -1,
};

static inline void PutPort(SocAddress *address, u16 port) {
    address->port = port;
}

static inline int GetTimeout(WifiSetupRequest *request) {
    return request->receiveTimeout;
}

static inline void ClearRetry(WifiSetupAossRetry *pair, int *mode) {
    *(s16 *)((u32)pair) = 0;
    *mode = 0;
    *(s16 *)((u32)pair + 2) = 0;
}

#pragma opt_loop_invariants off
// Find the AOSS access point and connect to it, then send requests and handle the replies until the settings arrive.
int WifiSetup_RunAossSession(WifiSetupRequest *request) {
    AossSession session;
    int connected;
    int mode;
    int nextMode;
    u32 ip;
    WifiSetupAossReceived *data;
    int seconds;
    int microseconds;
    int timeout;
    int tmp;
    int result;
    int zero;
    u8 error;
    s16 i;
    s16 limit;
    s16 delay;
    session.connection = sWifiSetupUnsetConnection;
    ClearRetry(&session.retry, &mode);
    session.option = 1;
    zero = mode;
    session.attempts = zero;
    ip = zero;
    WifiSetup_MemFill(&session.params, mode, sizeof(WifiSetupAossPacketParams));
    session.connection.max = request->connectRetries;
    if (session.connection.max == -1) {
        session.connection.max = 10;
    }
    session.retry.max = request->receiveRetries;
    if (session.retry.max == -1) {
        session.retry.max = 10;
    }
    session.connection.delay = request->connectDelay;
    if (session.connection.delay == -1) {
        session.connection.delay = 100;
    }
    session.retry.delay = request->receiveDelay;
    if (session.retry.delay == -1) {
        session.retry.delay = 100;
    }
    tmp = GetTimeout(request);
    timeout = tmp;
    if (tmp == -1) {
        timeout = 2000;
    }
    WifiSetup_InitState(request);
    if ((gWifiSetupState.requestedMask & WIFI_SETUP_AOSS_SETTING_WEP64) != WIFI_SETUP_AOSS_SETTING_WEP64) {
        WifiSetup_SetError(WIFI_SETUP_AOSS_ERROR_WEP64_NOT_REQUESTED);
        request->error = WIFI_SETUP_AOSS_REQUEST_FAILED;
        WifiSetup_FreeWorkBuffers();
        return -1;
    }
    i = 0;
    WifiSetup_SetStatus(WIFI_SETUP_AOSS_STATUS_SEARCHING);
    delay = session.connection.delay;
    limit = session.connection.max;
    for (;;) {
        if (gWifiSetupState.connection) {
            WifiSetup_Free(gWifiSetupState.connection);
            gWifiSetupState.connection = NULL;
        }
        if (WifiSetup_SearchAccessPoints(&ov13_0224CF9C) == -1) {
            request->error = WIFI_SETUP_AOSS_REQUEST_FAILED;
            WifiSetup_FreeWorkBuffers();
            return -1;
        }
        tmp = WifiSetup_FindAossAccessPoint(gWifiSetupState.connection);
        if (tmp == WIFI_SETUP_AOSS_SCAN_SEVERAL) {
            request->error = WIFI_SETUP_AOSS_REQUEST_SEVERAL_FOUND;
            WifiSetup_FreeWorkBuffers();
            return -1;
        }
        if (tmp == WIFI_SETUP_AOSS_SCAN_FOUND) {
            break;
        }
        if (i >= limit) {
            request->error = WIFI_SETUP_AOSS_REQUEST_NOT_FOUND;
            WifiSetup_FreeWorkBuffers();
            return -1;
        }
        WifiSetup_Sleep(delay);
        i++;
    }
    WifiSetup_SetStatus(WIFI_SETUP_AOSS_STATUS_CONNECTING);
    WifiSetup_MemFill(&session.context, 0, sizeof(WifiSetupAossConnectInfo));
    if (WifiSetup_InitAossConnectInfo(&session.context)) {
        request->error = WIFI_SETUP_AOSS_REQUEST_FAILED;
        WifiSetup_FreeWorkBuffers();
        return -1;
    }
    gWifiSetupState.connectResult = WifiSetup_Alloc(sizeof(WifiSetupAossConnectResult));
    if (!gWifiSetupState.connectResult) {
        request->error = WIFI_SETUP_AOSS_REQUEST_FAILED;
        WifiSetup_FreeWorkBuffers();
        return -1;
    }
    WifiSetup_MemFill(gWifiSetupState.connectResult, 0, sizeof(WifiSetupAossConnectResult));
    limit = session.connection.max;
    for (i = 0; i < limit; i++) {
        tmp = WifiSetup_ConnectAccessPoint(&session.context, gWifiSetupState.connectResult);
        if (tmp == -1) {
            request->error = WIFI_SETUP_AOSS_REQUEST_FAILED;
            WifiSetup_FreeWorkBuffers();
            return -1;
        }
        if (tmp == 0) {
            if (tmp != 0 || gWifiSetupState.connectResult->connected == 1) {
                break;
            }
        }
        WifiSetup_Sleep(delay);
    }
    if (i == session.connection.max) {
        request->error = WIFI_SETUP_AOSS_REQUEST_FAILED;
        WifiSetup_FreeWorkBuffers();
        return -1;
    }
    if (WifiSetup_StartupSocket(WIFI_SETUP_AOSS_HOST_ADDRESS, 0xFFFFFF00, WIFI_SETUP_AOSS_HOST_ADDRESS)) {
        WifiSetup_SetError(WIFI_SETUP_AOSS_ERROR_SOCKET_STARTUP);
        request->error = WIFI_SETUP_AOSS_REQUEST_FAILED;
        WifiSetup_FreeWorkBuffers();
        return -1;
    }
    WifiSetup_FreeWorkBuffers();
    WifiSetup_InitPacketAddresses(3, &session.params, request->macAddress);
    gWifiSetupSocket.socket = WifiSetup_Socket(2, 2, 0);
    if (gWifiSetupSocket.socket < 0) {
        request->error = WIFI_SETUP_AOSS_REQUEST_FAILED;
        WifiSetup_FreeWorkBuffers();
        return -1;
    }
    if (WifiSetup_SetSockOpt(gWifiSetupSocket.socket, 65535, 1, &session.option, sizeof(session.option)) < 0) {
        WifiSetup_SetError(WIFI_SETUP_AOSS_ERROR_SOCKET_OPTION);
        request->error = WIFI_SETUP_AOSS_REQUEST_FAILED;
        WifiSetup_FreeWorkBuffers();
        return -1;
    }
    WifiSetup_MemFill(&session.address, 0, sizeof(SocAddress));
    session.address.family = 2;
    session.address.ip = WifiSetup_HostToNet32(WIFI_SETUP_AOSS_HOST_ADDRESS);
    PutPort(&session.address, WifiSetup_HostToNet16(WIFI_SETUP_AOSS_PORT));
    if (WifiSetup_Bind(gWifiSetupSocket.socket, &session.address, sizeof(session.address)) < 0) {
        request->error = WIFI_SETUP_AOSS_REQUEST_FAILED;
        WifiSetup_FreeWorkBuffers();
        return -1;
    }
restart:
    data = gWifiSetupState.data;
    WifiSetup_MemFill(&session.config, 0, sizeof(WifiSetupAossAddresses));
    session.config.gateway = WIFI_SETUP_AOSS_HOST_ADDRESS;
    session.config.ip = WIFI_SETUP_AOSS_AP_ADDRESS;
    seconds = (timeout) / 1000;
    microseconds = ((timeout) % 1000) * 1000;
    limit = session.connection.max;
    for (;;) {
        if (mode == WIFI_SETUP_AOSS_STEP_SETTINGS && ov13_0224CFB8[28] != 1) {
            if (gWifiSetupSocket.socket != -1) {
                WifiSetup_Close(gWifiSetupSocket.socket);
            }
            gWifiSetupSocket.socket = -1;
            if (WifiSetup_CleanupSocket()) {
                request->error = WIFI_SETUP_AOSS_REQUEST_FAILED;
                WifiSetup_FreeWorkBuffers();
                return -1;
            }
            gWifiSetupState.connection = WifiSetup_Alloc(88);
            if (!gWifiSetupState.connection) {
                request->error = WIFI_SETUP_AOSS_REQUEST_FAILED;
                WifiSetup_FreeWorkBuffers();
                return -1;
            }
            for (;;) {
                if (gWifiSetupState.connection) {
                    WifiSetup_Free(gWifiSetupState.connection);
                    gWifiSetupState.connection = NULL;
                }
                connected = WifiSetup_SearchAccessPoints(&ov13_0224CF9C);
                if (connected == -1) {
                    request->error = WIFI_SETUP_AOSS_REQUEST_FAILED;
                    WifiSetup_FreeWorkBuffers();
                    return -1;
                }
                tmp = WifiSetup_FindAossAccessPoint(gWifiSetupState.connection);
                if (tmp == WIFI_SETUP_AOSS_SCAN_SEVERAL) {
                    request->error = WIFI_SETUP_AOSS_REQUEST_SEVERAL_FOUND;
                    WifiSetup_FreeWorkBuffers();
                    return -1;
                }
                if (tmp == WIFI_SETUP_AOSS_SCAN_FOUND) {
                    break;
                }
                if (i >= limit) {
                    request->error = WIFI_SETUP_AOSS_REQUEST_NOT_FOUND;
                    WifiSetup_FreeWorkBuffers();
                    return -1;
                }
                WifiSetup_Sleep(delay);
                i++;
            }
            if (connected == -1) {
                request->error = WIFI_SETUP_AOSS_REQUEST_FAILED;
                WifiSetup_FreeWorkBuffers();
                return -1;
            }
            gWifiSetupState.connectResult = WifiSetup_Alloc(sizeof(WifiSetupAossConnectResult));
            if (!gWifiSetupState.connectResult) {
                request->error = WIFI_SETUP_AOSS_REQUEST_FAILED;
                WifiSetup_FreeWorkBuffers();
                return -1;
            }
            WifiSetup_MemFill(gWifiSetupState.connectResult, 0, sizeof(WifiSetupAossConnectResult));
            for (i = 0; i < limit; i++) {
                tmp = WifiSetup_ConnectAccessPoint(&session.context, gWifiSetupState.connectResult);
                if (tmp == -1) {
                    request->error = WIFI_SETUP_AOSS_REQUEST_FAILED;
                    WifiSetup_FreeWorkBuffers();
                    return -1;
                }
                if (tmp == 0) {
                    if (tmp != 0 || gWifiSetupState.connectResult->connected == 1) {
                        break;
                    }
                }
                WifiSetup_Sleep(delay);
            }
            if (i == limit) {
                request->error = WIFI_SETUP_AOSS_REQUEST_FAILED;
                WifiSetup_FreeWorkBuffers();
                return -1;
            }
            ip = WifiSetup_NextHostAddress(gWifiSetupState.address, gWifiSetupState.netmask);
            if (WifiSetup_StartupSocket(ip, gWifiSetupState.netmask, ip)) {
                WifiSetup_SetError(WIFI_SETUP_AOSS_ERROR_SOCKET_STARTUP);
                request->error = WIFI_SETUP_AOSS_REQUEST_FAILED;
                WifiSetup_FreeWorkBuffers();
                return -1;
            }
            ov13_0224CFB8[28] = 1;
            WifiSetup_FreeWorkBuffers();
            gWifiSetupSocket.socket = WifiSetup_Socket(2, 2, 0);
            if (gWifiSetupSocket.socket < 0) {
                request->error = WIFI_SETUP_AOSS_REQUEST_FAILED;
                WifiSetup_FreeWorkBuffers();
                return -1;
            }
            if (WifiSetup_SetSockOpt(gWifiSetupSocket.socket, 65535, 1, &session.option, sizeof(session.option)) < 0) {
                WifiSetup_SetError(WIFI_SETUP_AOSS_ERROR_SOCKET_OPTION);
                request->error = WIFI_SETUP_AOSS_REQUEST_FAILED;
                WifiSetup_FreeWorkBuffers();
                return -1;
            }
            WifiSetup_MemFill(&session.address, 0, sizeof(SocAddress));
            session.address.family = 2;
            session.address.ip = WifiSetup_HostToNet32(ip);
            PutPort(&session.address, WifiSetup_HostToNet16(WIFI_SETUP_AOSS_PORT));
            if (WifiSetup_Bind(gWifiSetupSocket.socket, &session.address, sizeof(session.address)) < 0) {
                request->error = WIFI_SETUP_AOSS_REQUEST_FAILED;
                WifiSetup_FreeWorkBuffers();
                return -1;
            }
        }
        if (WifiSetup_SendRequest(mode, &session.config, &session.params, gWifiSetupSocket.socket) == -1) {
            {
                int current = mode;
                WifiSetup_SetError(WIFI_SETUP_AOSS_ERROR_SEND + current);
            }
            request->error = WIFI_SETUP_AOSS_REQUEST_FAILED;
            WifiSetup_FreeWorkBuffers();
            return -1;
        }
        WifiSetup_MemFill(data, 0, 0x5f8);
        WifiSetup_ClearPollSet(&session.set);
        WifiSetup_AddToPollSet(gWifiSetupSocket.socket, &session.set);
        session.time.seconds = seconds;
        session.time.microseconds = microseconds;
        if (WifiSetup_Poll(gWifiSetupSocket.socket + 1, &session.set, 0, 0, &session.time) <= 0) {
            session.attempts++;
            if (session.attempts > session.retry.max) {
                int current = mode;
                if (current == WIFI_SETUP_AOSS_STEP_JOIN) {
                    WifiSetup_SetError(WIFI_SETUP_AOSS_ERROR_JOIN_TIMEOUT);
                } else if (current == WIFI_SETUP_AOSS_STEP_SETTINGS) {
                    WifiSetup_SetError(WIFI_SETUP_AOSS_ERROR_SETTINGS_TIMEOUT);
                } else {
                    WifiSetup_SetError(WIFI_SETUP_AOSS_ERROR_DONE_TIMEOUT);
                }
                result = -1;
                break;
            }
            WifiSetup_Sleep(session.retry.delay);
            continue;
        }
        session.length = sizeof(session.remote);
        tmp = WifiSetup_RecvFrom(gWifiSetupSocket.socket, &data->packet, sizeof(WifiSetupAossPacket), 0, &session.remote, &session.length);
        data->socket = gWifiSetupSocket.socket;
        data->length = WifiSetup_NetToHost16((u16)tmp);
        nextMode = WifiSetup_HandlePacket(mode, data, &session.attempts, &session.params, gWifiSetupSocket.socket);
        if (nextMode == WIFI_SETUP_AOSS_STEP_FINISHED) {
            result = 0;
            break;
        }
        result = -1;
        if (nextMode == WIFI_SETUP_AOSS_STEP_FAILED) {
            break;
        }
        if (mode != nextMode) {
            if (nextMode == WIFI_SETUP_AOSS_STEP_DONE) {
                if (gWifiSetupSocket.socket != -1) {
                    WifiSetup_Close(gWifiSetupSocket.socket);
                }
                gWifiSetupSocket.socket = -1;
                if (WifiSetup_CleanupSocket()) {
                    request->error = WIFI_SETUP_AOSS_REQUEST_FAILED;
                    WifiSetup_FreeWorkBuffers();
                    return -1;
                }
                i = 0;
                WifiSetup_SetStatus(WIFI_SETUP_AOSS_STATUS_RECONNECTING);
                limit = session.connection.max;
                for (;;) {
                    if (gWifiSetupState.connection) {
                        WifiSetup_Free(gWifiSetupState.connection);
                        gWifiSetupState.connection = NULL;
                    }
                    if (WifiSetup_SearchAccessPoints(&ov13_0224CF9C) == -1) {
                        request->error = WIFI_SETUP_AOSS_REQUEST_FAILED;
                        WifiSetup_FreeWorkBuffers();
                        return -1;
                    }
                    tmp = WifiSetup_FindAossAccessPoint(gWifiSetupState.connection);
                    if (tmp == WIFI_SETUP_AOSS_SCAN_SEVERAL) {
                        request->error = WIFI_SETUP_AOSS_REQUEST_SEVERAL_FOUND;
                        WifiSetup_FreeWorkBuffers();
                        return -1;
                    }
                    if (tmp == WIFI_SETUP_AOSS_SCAN_FOUND) {
                        break;
                    }
                    if (i >= limit) {
                        request->error = WIFI_SETUP_AOSS_REQUEST_NOT_FOUND;
                        WifiSetup_FreeWorkBuffers();
                        return -1;
                    }
                    WifiSetup_Sleep(delay);
                    i++;
                }
                gWifiSetupState.connectResult = WifiSetup_Alloc(sizeof(WifiSetupAossConnectResult));
                if (!gWifiSetupState.connectResult) {
                    request->error = WIFI_SETUP_AOSS_REQUEST_FAILED;
                    WifiSetup_FreeWorkBuffers();
                    return -1;
                }
                WifiSetup_MemFill(gWifiSetupState.connectResult, 0, sizeof(WifiSetupAossConnectResult));
                limit = session.connection.max;
                for (i = 0; i < limit; i++) {
                    tmp = WifiSetup_ConnectAccessPoint(&session.context, gWifiSetupState.connectResult);
                    if (tmp == -1) {
                        request->error = WIFI_SETUP_AOSS_REQUEST_FAILED;
                        WifiSetup_FreeWorkBuffers();
                        return -1;
                    }
                    if (tmp == 0) {
                        if (tmp != 0 || gWifiSetupState.connectResult->connected == 1) {
                            break;
                        }
                    }
                    WifiSetup_Sleep(delay);
                }
                if (i == session.connection.max) {
                    request->error = WIFI_SETUP_AOSS_REQUEST_FAILED;
                    WifiSetup_FreeWorkBuffers();
                    return -1;
                }
                if (WifiSetup_StartupSocket(ip, gWifiSetupState.netmask, ip)) {
                    WifiSetup_SetError(WIFI_SETUP_AOSS_ERROR_SOCKET_STARTUP);
                    request->error = WIFI_SETUP_AOSS_REQUEST_FAILED;
                    WifiSetup_FreeWorkBuffers();
                    return -1;
                }
                WifiSetup_FreeWorkBuffers();
                gWifiSetupSocket.socket = WifiSetup_Socket(2, 2, 0);
                if (gWifiSetupSocket.socket < 0) {
                    request->error = WIFI_SETUP_AOSS_REQUEST_FAILED;
                    WifiSetup_FreeWorkBuffers();
                    return -1;
                }
                if (WifiSetup_SetSockOpt(gWifiSetupSocket.socket, 65535, 1, &session.option, sizeof(session.option)) < 0) {
                    WifiSetup_SetError(WIFI_SETUP_AOSS_ERROR_SOCKET_OPTION);
                    request->error = WIFI_SETUP_AOSS_REQUEST_FAILED;
                    WifiSetup_FreeWorkBuffers();
                    return -1;
                }
                WifiSetup_MemFill(&session.address, 0, sizeof(SocAddress));
                session.address.family = 2;
                session.address.ip = WifiSetup_HostToNet32(ip);
                PutPort(&session.address, WifiSetup_HostToNet16(WIFI_SETUP_AOSS_PORT));
                if (WifiSetup_Bind(gWifiSetupSocket.socket, &session.address, sizeof(session.address)) < 0) {
                    request->error = WIFI_SETUP_AOSS_REQUEST_FAILED;
                    WifiSetup_FreeWorkBuffers();
                    return -1;
                }
            }
            mode = nextMode;
            goto restart;
        }
        mode = nextMode;
        if (session.attempts > session.retry.max) {
            int current = nextMode;
            if (current == WIFI_SETUP_AOSS_STEP_JOIN) {
                WifiSetup_SetError(WIFI_SETUP_AOSS_ERROR_JOIN_TIMEOUT);
            } else if (current == WIFI_SETUP_AOSS_STEP_SETTINGS) {
                WifiSetup_SetError(WIFI_SETUP_AOSS_ERROR_SETTINGS_TIMEOUT);
            } else {
                WifiSetup_SetError(WIFI_SETUP_AOSS_ERROR_DONE_TIMEOUT);
            }
            result = -1;
            break;
        }
        WifiSetup_Sleep(session.retry.delay);
        goto restart;
    }
    if (gWifiSetupSocket.socket != -1) {
        WifiSetup_Close(gWifiSetupSocket.socket);
    }
    gWifiSetupSocket.socket = -1;
    if (WifiSetup_CleanupSocket()) {
        request->error = WIFI_SETUP_AOSS_REQUEST_FAILED;
        WifiSetup_FreeWorkBuffers();
        return -1;
    }
    if (result) {
        switch (WifiSetup_GetError()) {
        case WIFI_SETUP_AOSS_ERROR_JOIN_TIMEOUT:
            error = WIFI_SETUP_AOSS_REQUEST_JOIN_TIMEOUT;
            break;
        case WIFI_SETUP_AOSS_ERROR_SETTINGS_TIMEOUT:
            error = WIFI_SETUP_AOSS_REQUEST_SETTINGS_TIMEOUT;
            break;
        case WIFI_SETUP_AOSS_ERROR_DONE_TIMEOUT:
            error = WIFI_SETUP_AOSS_REQUEST_DONE_TIMEOUT;
            break;
        case 20:
            error = 7;
            break;
        case 21:
            error = 8;
            break;
        default:
            error = WIFI_SETUP_AOSS_REQUEST_FAILED;
            break;
        }
        request->error = error;
        WifiSetup_FreeWorkBuffers();
        return -1;
    }
    if (WifiSetup_StoreAossResult(request)) {
        request->error = WIFI_SETUP_AOSS_REQUEST_STORE_FAILED;
        WifiSetup_FreeWorkBuffers();
        return -1;
    }
    return 0;
}
#pragma opt_loop_invariants reset
