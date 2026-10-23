#include "global.h"

#include "wifi_setup/wifi_setup.h"

// Copy the keys of the requested settings that were received into the result.
int WifiSetup_StoreAossResult(WifiSetupRequest *request) {
    WifiSetupWpaKeyRecord *wpaTkip = &gWifiSetupSecurityRecords[0].wpaTkip;
    u8 *dst = request->result;
    WifiSetupKeyRecord *wep64 = &gWifiSetupSecurityRecords[0].wep64;
    WifiSetupKeyRecord *wep128 = &gWifiSetupSecurityRecords[0].wep128;
    WifiSetupWpaKeyRecord *wpaAes = &gWifiSetupSecurityRecords[0].wpaAes;

    if (dst == NULL) {
        return -1;
    }
    request->requestMask = gWifiSetupState.requestedMask & gWifiSetupState.receivedMask;
    WifiSetup_MemFill(dst, 0, sizeof(request->result));
    if (request->requestMask & 1) {
        WifiSetup_MemCopy(dst, wep64->fields[0], wep64->length);
        WifiSetup_MemCopy(dst + 6, wep64->fields[1], wep64->length);
        WifiSetup_MemCopy(dst + 12, wep64->fields[2], wep64->length);
        WifiSetup_MemCopy(dst + 18, wep64->fields[3], wep64->length);
        if (WifiSetup_CheckPrintable(wep64->text, WifiSetup_StrLen(wep64->text))) {
            goto fail;
        }
        WifiSetup_MemCopy(dst + 0x18, wep64->text, WifiSetup_StrLen(wep64->text));
    }
    if (request->requestMask & 2) {
        WifiSetup_MemCopy(dst + 0x39, wep128->fields[0], wep128->length);
        WifiSetup_MemCopy(dst + 0x47, wep128->fields[1], wep128->length);
        WifiSetup_MemCopy(dst + 0x55, wep128->fields[2], wep128->length);
        WifiSetup_MemCopy(dst + 0x63, wep128->fields[3], wep128->length);
        if (WifiSetup_CheckPrintable(wep128->text, WifiSetup_StrLen(wep128->text))) {
            goto fail;
        }
        WifiSetup_MemCopy(dst + 0x71, wep128->text, WifiSetup_StrLen(wep128->text));
    }
    if (request->requestMask & 4) {
        if (WifiSetup_CheckPrintable(wpaTkip->key, wpaTkip->length - 1)) {
            goto fail;
        }
        WifiSetup_MemCopy(dst + 0x92, wpaTkip->key, wpaTkip->length);
        if (WifiSetup_CheckPrintable(wpaTkip->text, WifiSetup_StrLen(wpaTkip->text))) {
            goto fail;
        }
        WifiSetup_MemCopy(dst + 0xD2, wpaTkip->text, WifiSetup_StrLen(wpaTkip->text));
    }
    if (request->requestMask & 8) {
        if (WifiSetup_CheckPrintable(wpaAes->key, wpaAes->length - 1)) {
            goto fail;
        }
        WifiSetup_MemCopy(dst + 0xF3, wpaAes->key, wpaAes->length);
        if (WifiSetup_CheckPrintable(wpaAes->text, WifiSetup_StrLen(wpaAes->text))) {
            goto fail;
        }
        WifiSetup_MemCopy(dst + 0x133, wpaAes->text, WifiSetup_StrLen(wpaAes->text));
    }
    request->error = 0;
    return 0;
fail:
    WifiSetup_MemFill(dst, 0, sizeof(request->result));
    return -1;
}
