#include <string.h>

#include "global.h"

#include "wifi_setup/wifi_setup_internal.h"
#include "wifi_setup/wifi_setup_wcm.h"

typedef struct Id8 {
    u8 b[8];
} Id8;

// gWifiSetupReply
typedef struct WifiSetupReply {
    u32 words[149];
} WifiSetupReply;

extern WifiSetupReply gWifiSetupReply;

int SOC_Socket(int domain, int type, int protocol);
int SOC_Bind(int socket, void *addr);
int SOC_Close(int socket);
int SOC_RecvFrom(int socket, void *buf, int len, int flags, void *from);

static inline int BindSocket(int socket, WifiSetupSockAddr *address) {
    memset(address, 0, sizeof(*address));
    address->len = 8;
    address->family = 2;
    address->port = WIFI_SETUP_SIMPLE_START_PORT;
    address->addr = 0;
    return SOC_Bind(socket, address);
}

#pragma opt_dead_assignments off

// Worker state machine: scan for the access point, connect, open the UDP socket (port 486), wait for
// the request, exchange keys, then send and receive the settings records until done.
int WifiSetup_RunSession(void) {
    WifiSetupSockAddr bind, recv;
    u32 type, size;
    u32 timestamp;
    u8 *record;
    int sock;
    BOOL done;
    int result;
    u32 last;
    int retry;

    sock = 0;
    result = -5;
    last = 0;
    retry = 0;
    done = FALSE;

    gWifiSetupWork.step = WIFI_SETUP_SESSION_STEP_FIND_AP;
    while (!done && !gWifiSetupWork.stop) {
        OS_Sleep(500);
        switch (gWifiSetupWork.step) {
        case WIFI_SETUP_SESSION_STEP_FIND_AP:
            result = WifiSetup_FindSetupAccessPoint();
            if (result != 1) {
                done = TRUE;
                break;
            }
            gWifiSetupWork.state = WIFI_SETUP_SIMPLE_START_CONNECTING;
            WifiSetup_ReportSimpleStartStatus();
            gWifiSetupWork.step = WIFI_SETUP_SESSION_STEP_CONNECT_AP;
            break;
        case WIFI_SETUP_SESSION_STEP_CONNECT_AP:
            result = WifiSetupLink_ConnectSelectedAp();
            if (result != 1) {
                done = TRUE;
                break;
            }
            gWifiSetupWork.step = WIFI_SETUP_SESSION_STEP_OPEN_SOCKET;
            break;
        case WIFI_SETUP_SESSION_STEP_OPEN_SOCKET:
            sock = SOC_Socket(2, 2, 0);
            if (sock < 0) {
                result = -2;
                done = TRUE;
                break;
            }
            result = BindSocket(sock, &bind);
            if (result < 0) {
                result = -2;
                done = TRUE;
                break;
            }
            gWifiSetupWork.step = WIFI_SETUP_SESSION_STEP_WAIT_VERSION;
            break;
        case WIFI_SETUP_SESSION_STEP_WAIT_VERSION:
            if (WifiSetup_GetMilliseconds() >= gWifiSetupConfig.deadline) {
                SOC_Close(sock);
                result = -3;
                done = TRUE;
                break;
            }
            recv.len = 8;
            WifiSetup_BuildMacPair((WifiSetupMacPair *)gWifiSetupSessionKey, &recv);
            if (SOC_RecvFrom(sock, gWifiSetupPacketBuffer, sizeof(gWifiSetupPacketBuffer), 4, &recv) > 0 && WifiSetup_CheckVersionReply(gWifiSetupPacketBuffer, gWifiSetupExtendedRequest)) {
                gWifiSetupConfig.deadline = WifiSetup_GetMilliseconds() + 30000;
                gWifiSetupWork.step = WIFI_SETUP_SESSION_STEP_SEND_VERSION_REQUEST;
                gWifiSetupWork.state = WIFI_SETUP_SIMPLE_START_EXCHANGING_KEYS;
                WifiSetup_ReportSimpleStartStatus();
            }
            break;
        case WIFI_SETUP_SESSION_STEP_SEND_VERSION_REQUEST:
            gWifiSetupWork.packetLength = WifiSetup_BuildVersionRequest(gWifiSetupPacketBuffer);
            WifiSetup_SendSetupPacket(sock, &recv, gWifiSetupPacketBuffer, gWifiSetupWork.packetLength);
            last = WifiSetup_GetMilliseconds();
            gWifiSetupWork.step = WIFI_SETUP_SESSION_STEP_WAIT_KEY;
            break;
        case WIFI_SETUP_SESSION_STEP_WAIT_KEY:
            if (WifiSetup_GetMilliseconds() >= gWifiSetupConfig.deadline) {
                SOC_Close(sock);
                result = -4;
                done = TRUE;
                break;
            }
            if (SOC_RecvFrom(sock, gWifiSetupPacketBuffer, sizeof(gWifiSetupPacketBuffer), 4, &recv) > 0 && WifiSetup_ReadPacket(gWifiSetupPacketBuffer, WIFI_SETUP_PACKET_KEY, gWifiSetupRecordBuffer, gWifiSetupSessionKey)) {
                record = WifiSetup_FirstRecord(gWifiSetupRecordBuffer, &type, &size);
                if (type == WIFI_SETUP_RECORD_SETTINGS_KEY) {
                    timestamp = WifiSetup_GetMilliseconds();
                    *(Id8 *)gWifiSetupSettingsKey = *(Id8 *)record;
                    WifiSetup_CalcMd5(gWifiSetupTimestampDigest, (const u8 *)&timestamp, sizeof(timestamp));
                    retry = 0;
                    gWifiSetupWork.step = WIFI_SETUP_SESSION_STEP_SEND_KEY;
                    gWifiSetupWork.state = WIFI_SETUP_SIMPLE_START_GETTING_SETTINGS;
                    gWifiSetupConfig.deadline = -1;
                    WifiSetup_ReportSimpleStartStatus();
                }
                record = NULL;
                break;
            }
            if (WifiSetup_GetMilliseconds() >= last + 1000) {
                gWifiSetupWork.step = WIFI_SETUP_SESSION_STEP_SEND_VERSION_REQUEST;
            }
            break;
        case WIFI_SETUP_SESSION_STEP_SEND_KEY:
            gWifiSetupWork.recordLength = WifiSetup_BuildSingleRecordList(gWifiSetupRecordBuffer, WIFI_SETUP_RECORD_TIMESTAMP_DIGEST, gWifiSetupTimestampDigest, 8);
            gWifiSetupWork.packetLength = WifiSetup_BuildPacket(gWifiSetupPacketBuffer, WIFI_SETUP_PACKET_KEY_REPLY, gWifiSetupRecordBuffer, gWifiSetupWork.recordLength, gWifiSetupSessionKey);
            WifiSetup_SendSetupPacket(sock, &recv, gWifiSetupPacketBuffer, gWifiSetupWork.packetLength);
            last = WifiSetup_GetMilliseconds();
            memset(&gWifiSetupReply, 0, sizeof(gWifiSetupReply));
            gWifiSetupWork.step = WIFI_SETUP_SESSION_STEP_WAIT_SETTINGS;
            break;
        case WIFI_SETUP_SESSION_STEP_WAIT_SETTINGS:
            if (SOC_RecvFrom(sock, gWifiSetupPacketBuffer, sizeof(gWifiSetupPacketBuffer), 4, &recv) > 0) {
                gWifiSetupWork.recordLength = WifiSetup_ReadPacket(gWifiSetupPacketBuffer, WIFI_SETUP_PACKET_SETTINGS, gWifiSetupRecordBuffer, gWifiSetupSettingsKey);
                if (gWifiSetupWork.recordLength && WifiSetup_ParseSettingsRecords(gWifiSetupRecordBuffer)) {
                    if (gWifiSetupClientSettings.ssid[0]) {
                        gWifiSetupWork.unk_00 = 1;
                    } else {
                        gWifiSetupWork.unk_00 = 0;
                    }
                    retry = 0;
                    gWifiSetupWork.step = WIFI_SETUP_SESSION_STEP_SEND_RESULT;
                    break;
                }
            }
            if (WifiSetup_GetMilliseconds() >= last + 1000) {
                retry++;
                if (retry >= 10) {
                    SOC_Close(sock);
                    result = -2;
                    done = TRUE;
                } else {
                    gWifiSetupWork.step = WIFI_SETUP_SESSION_STEP_SEND_KEY;
                }
            }
            break;
        case WIFI_SETUP_SESSION_STEP_SEND_RESULT:
            gWifiSetupWork.recordLength = WifiSetup_BuildSingleRecordList(gWifiSetupRecordBuffer, WIFI_SETUP_RECORD_RESULT, gWifiSetupWcmSearchSsid + 0x20, 1);
            gWifiSetupWork.packetLength = WifiSetup_BuildPacket(gWifiSetupPacketBuffer, WIFI_SETUP_PACKET_RESULT, gWifiSetupRecordBuffer, gWifiSetupWork.recordLength, gWifiSetupSettingsKey);
            if (WifiSetupLink_GetState() != WIFI_SETUP_WCM_STATE_CONNECTED) {
                last = WifiSetup_GetMilliseconds() + 1000;
                retry = 10;
                gWifiSetupWork.step = WIFI_SETUP_SESSION_STEP_RESEND_RESULT;
                break;
            }
            WifiSetup_SendSetupPacket(sock, &recv, gWifiSetupPacketBuffer, gWifiSetupWork.packetLength);
            last = WifiSetup_GetMilliseconds();
            gWifiSetupWork.step = WIFI_SETUP_SESSION_STEP_RESEND_RESULT;
            break;
        case WIFI_SETUP_SESSION_STEP_RESEND_RESULT:
            if (WifiSetup_GetMilliseconds() >= last + 1000) {
                retry++;
                if (retry >= 10) {
                    done = TRUE;
                    result = WifiSetup_StoreSimpleStartResult();
                } else {
                    gWifiSetupWork.step = WIFI_SETUP_SESSION_STEP_SEND_RESULT;
                }
            }
            break;
        }
    }
    if (sock) {
        SOC_Close(sock);
    }
    if (gWifiSetupWork.stop) {
        result = -8;
    }
    return result;
}

#pragma opt_dead_assignments reset
