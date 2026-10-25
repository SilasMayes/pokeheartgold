#include "global.h"

#include "wifi_setup/wifi_setup.h"

// Copy the keys of the requested settings that were received into the result.
int WifiSetup_StoreAossResult(WifiSetupRequest *request) {
    WifiSetupWpaKeyRecord *wpaTkip = &gWifiSetupSecurityRecords[0].wpaTkip;
    WifiSetupAossResult *result = &request->result;
    WifiSetupKeyRecord *wep64 = &gWifiSetupSecurityRecords[0].wep64;
    WifiSetupKeyRecord *wep128 = &gWifiSetupSecurityRecords[0].wep128;
    WifiSetupWpaKeyRecord *wpaAes = &gWifiSetupSecurityRecords[0].wpaAes;

    if (result == NULL) {
        return -1;
    }
    request->requestMask = gWifiSetupState.requestedMask & gWifiSetupState.receivedMask;
    WifiSetup_MemFill(result, 0, sizeof(request->result));
    if (request->requestMask & WIFI_SETUP_AOSS_SETTING_WEP64) {
        WifiSetup_MemCopy(result->wep64Keys[0], wep64->keys[0], wep64->length);
        WifiSetup_MemCopy(result->wep64Keys[1], wep64->keys[1], wep64->length);
        WifiSetup_MemCopy(result->wep64Keys[2], wep64->keys[2], wep64->length);
        WifiSetup_MemCopy(result->wep64Keys[3], wep64->keys[3], wep64->length);
        if (WifiSetup_CheckPrintable(wep64->ssid, WifiSetup_StrLen(wep64->ssid))) {
            goto fail;
        }
        WifiSetup_MemCopy(result->wep64Ssid, wep64->ssid, WifiSetup_StrLen(wep64->ssid));
    }
    if (request->requestMask & WIFI_SETUP_AOSS_SETTING_WEP128) {
        WifiSetup_MemCopy(result->wep128Keys[0], wep128->keys[0], wep128->length);
        WifiSetup_MemCopy(result->wep128Keys[1], wep128->keys[1], wep128->length);
        WifiSetup_MemCopy(result->wep128Keys[2], wep128->keys[2], wep128->length);
        WifiSetup_MemCopy(result->wep128Keys[3], wep128->keys[3], wep128->length);
        if (WifiSetup_CheckPrintable(wep128->ssid, WifiSetup_StrLen(wep128->ssid))) {
            goto fail;
        }
        WifiSetup_MemCopy(result->wep128Ssid, wep128->ssid, WifiSetup_StrLen(wep128->ssid));
    }
    if (request->requestMask & WIFI_SETUP_AOSS_SETTING_WPA_TKIP) {
        if (WifiSetup_CheckPrintable(wpaTkip->key, wpaTkip->length - 1)) {
            goto fail;
        }
        WifiSetup_MemCopy(result->wpaTkipKey, wpaTkip->key, wpaTkip->length);
        if (WifiSetup_CheckPrintable(wpaTkip->ssid, WifiSetup_StrLen(wpaTkip->ssid))) {
            goto fail;
        }
        WifiSetup_MemCopy(result->wpaTkipSsid, wpaTkip->ssid, WifiSetup_StrLen(wpaTkip->ssid));
    }
    if (request->requestMask & WIFI_SETUP_AOSS_SETTING_WPA_AES) {
        if (WifiSetup_CheckPrintable(wpaAes->key, wpaAes->length - 1)) {
            goto fail;
        }
        WifiSetup_MemCopy(result->wpaAesKey, wpaAes->key, wpaAes->length);
        if (WifiSetup_CheckPrintable(wpaAes->ssid, WifiSetup_StrLen(wpaAes->ssid))) {
            goto fail;
        }
        WifiSetup_MemCopy(result->wpaAesSsid, wpaAes->ssid, WifiSetup_StrLen(wpaAes->ssid));
    }
    request->error = WIFI_SETUP_AOSS_REQUEST_OK;
    return 0;
fail:
    WifiSetup_MemFill(result, 0, sizeof(request->result));
    return -1;
}
