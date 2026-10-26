#include "wifi_setup/wifi_setup.h"

#include "global.h"

void *WifiSetup_Alloc(int size) {
    return gWifiSetupRuntime.alloc(size);
}

void WifiSetup_Free(void *ptr) {
    gWifiSetupFreeHook(ptr);
}

int WifiSetup_RunAoss(WifiSetupRequest *request) {
    int valid;

    if (request->connectRetries == 0 || request->connectRetries < -1 || request->connectDelay < -1 || request->receiveRetries == 0 || request->receiveRetries < -1 || request->receiveDelay < -1 || request->receiveTimeout < -1 || request->key.length == 0 || request->key.length > 256 || request->key.data[request->key.length - 1] != 0) {
        valid = -1;
    } else {
        valid = 0;
    }
    if (!gWifiSetupRuntime.alloc || !gWifiSetupFreeHook) {
        valid = -1;
    }
    if (valid == -1) {
        request->error = WIFI_SETUP_AOSS_REQUEST_FAILED;
        WifiSetup_FreeWorkBuffers();
        return -1;
    }
    gWifiSetupState.data = WifiSetup_Alloc(WIFI_SETUP_AOSS_BUFFER_SIZE);
    if (gWifiSetupState.data == NULL) {
        request->error = WIFI_SETUP_AOSS_REQUEST_FAILED;
        WifiSetup_FreeWorkBuffers();
        return -1;
    }
    WifiSetup_SetStatus(WIFI_SETUP_AOSS_STATUS_RESET);
    int result = WifiSetup_RunAossSession(request);
    WifiSetup_Free(gWifiSetupState.data);
    WifiSetup_FreeWorkBuffers();
    if (gWifiSetupSocket.socket != -1) {
        WifiSetup_Close(gWifiSetupSocket.socket);
    }
    return result;
}
