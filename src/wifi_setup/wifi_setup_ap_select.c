#include <string.h>

#include "global.h"

#include "wifi_setup/wifi_setup_internal.h"

static inline int NameEqual(const char *name, const char *wanted) {
    return strlen(name) == strlen(wanted) && !memcmp(name, wanted, strlen(wanted));
}

static inline char *CopyName(char *name, const WifiSetupApEntry *entry) {
    memcpy(name, entry->ssid, 32);
    name[entry->ssidLength] = 0;
    return name;
}

// Compares two scan results. Picks the first access point of current that is also in previous
// (same SSID and BSSID) but has just dropped privacy, or else the open setup access point
// (sWifiSetupSetupApSsid) when it is new in current. Returns 1 and its index in *selected if one was found.
int WifiSetup_PickSetupAccessPoint(const WifiSetupApEntryList *current, const WifiSetupApEntryList *previous, u32 *selected) {
    BOOL changed = FALSE;
    int result = 0;
    BOOL newHas;
    BOOL oldHas;
    u32 count;
    u32 i;
    u32 j;
    const WifiSetupApEntry *left = current->entries;
    const WifiSetupApEntry *right = previous->entries;

    for (i = 0; i < current->count; i++) {
        char newName[34] = { 0 };
        memcpy(newName, left->ssid, 32);
        newName[left->ssidLength] = 0;
        count = previous->count;
        j = 0;
        if (count > j) {
            u32 length = left->ssidLength;
            do {
                if (length == 0 || length > 32) {
                    break;
                }
                // a one-character SSID of NUL or space is hidden
                if (length == 1 && (((const u8 *)left->ssid)[0] == 0 || ((const u8 *)left->ssid)[0] == ' ')) {
                    break;
                }
                if (!memcmp(newName, right->ssid, strlen(newName)) && !memcmp(left->bssid, right->bssid, sizeof(left->bssid)) && left->privacy != right->privacy && left->privacy == 0) {
                    changed = TRUE;
                    break;
                }
                j++;
                right++;
            } while (j < count);
        }
        if (changed) {
            break;
        }
        right = previous->entries;
        left++;
    }
    if (!changed) {
        char oldName[34] = { 0 };
        newHas = FALSE;
        oldHas = FALSE;
        left = current->entries;
        right = previous->entries;
        for (j = 0; j < previous->count; j++, right++) {
            memcpy(oldName, right->ssid, 32);
            oldName[right->ssidLength] = 0;
            if (!memcmp(oldName, sWifiSetupSetupApSsid, strlen(sWifiSetupSetupApSsid)) && right->privacy == 0) {
                oldHas = TRUE;
                break;
            }
        }
        for (i = 0; i < current->count; i++, left++) {
            if (NameEqual(CopyName(oldName, left), sWifiSetupSetupApSsid) && left->privacy == 0) {
                newHas = TRUE;
                break;
            }
        }
        if (newHas && !oldHas) {
            changed = TRUE;
        }
    }
    if (changed) {
        *selected = i;
        result = 1;
    }
    return result;
}
