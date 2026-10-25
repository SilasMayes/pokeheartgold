#include "global.h"

#include "wifi_setup/wifi_setup.h"

u32 WifiSetup_NextHostAddress(u32 value, u32 mask) {
    u32 common = value & mask;
    mask = ~mask;
    value &= mask;
    value++;
    value |= common;
    mask |= common;
    if (value >= mask) {
        value = common | 1;
    }
    return value;
}

void WifiSetup_FreeWorkBuffers(void) {
    if (gWifiSetupState.connectResult != NULL) {
        WifiSetup_Free(gWifiSetupState.connectResult);
        gWifiSetupState.connectResult = NULL;
    }
    if (gWifiSetupState.connection != NULL) {
        WifiSetup_Free(gWifiSetupState.connection);
        gWifiSetupState.connection = NULL;
    }
}

void WifiSetup_InitState(WifiSetupRequest *request) {
    WifiSetup_MemFill(gWifiSetupPeerAddress, 0, sizeof(gWifiSetupPeerAddress));
    gWifiSetupState.error = WIFI_SETUP_AOSS_ERROR_UNKNOWN;
    WifiSetup_MemFill(ov13_0224CFBC, 0, 0x1C);
    gWifiSetupState.key = request->key.data;
    gWifiSetupState.keyLength = request->key.length;
    gWifiSetupState.requestedMask = request->requestMask & 0xF;
    ov13_0224CFB8[0x1D] = request->key.tag;
    gWifiSetupState.receivedMask = 0;
    gWifiSetupState.address = WIFI_SETUP_AOSS_AP_ADDRESS;
    ov13_0224CFB8[0x1C] = 0;
}

void WifiSetup_SetError(int error) {
    gWifiSetupState.error = error;
}

int WifiSetup_GetError(void) {
    return gWifiSetupState.error;
}
