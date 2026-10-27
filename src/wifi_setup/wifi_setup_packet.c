#include "global.h"

#include "nitrowifi/socl_internal.h"
#include "wifi_setup/wifi_setup_internal.h"
#include "wifi_setup/wifi_setup_wcm.h"

#include "WM.h"

// Swaps the two bytes of a 16-bit value (network byte order).
#define Swap16(value) ((u16)((u8)((value) >> 8) | (((value) << 8) & 0xff00)))

// The own address, then the broadcast destination.
typedef struct WifiSetupBroadcastAddress {
    u8 host[4];
    SocAddress to;
} WifiSetupBroadcastAddress;

typedef struct WifiSetupVersion {
    u8 bytes[7];
} WifiSetupVersion;

typedef struct WifiSetupVersionRecord {
    u16 value;
    WifiSetupVersion version;
} WifiSetupVersionRecord;

extern u8 gWifiSetupReply[];

static int WifiSetup_SendDatagram(int socket, SocAddress *address, const u8 *unused, const void *data, int length);
static int WifiSetup_BroadcastDatagram(int socket, const void *data, int length);
static u8 *WifiSetup_GetPacketPayload(u8 *data, u32 *type, u32 *length);
static u8 *WifiSetup_NextRecord(u8 **cursor, u8 *end, u32 *type, u32 *length);
static u8 *WifiSetup_AppendRecord(u8 *out, int tag, const void *source, int size);
static BOOL WifiSetup_GetOwnMacAddress(u8 *mac);
static BOOL WifiSetup_HexToBytes(u8 *dst, const char *src, int length);

#pragma optimization_level 3

static const WifiSetupVersion sWifiSetupClientVersion = {
    .bytes = { 6, 0, 1, 2, 3, 4, 5 },
};

// Scans up to 30 times for the access point until WifiSetup_PickSetupAccessPoint picks one.
int WifiSetup_FindSetupAccessPoint(void) {
    char text[32];
    OSAlarm alarm;
    u32 selected;
    int attempt;
    int i;
    int total;
    u32 size;
    WifiSetupApEntryList *out;
    WifiSetupApEntryList *previous;
    int result;
    BOOL running;
    int event;
    int found;
    WifiSetupApInfo *ap;

    result = -1;
    previous = NULL;
    selected = 0;
    size = sizeof(WifiSetupApEntry) * gWifiSetupWork.apListCount + sizeof(WifiSetupApEntryList) + sizeof(WifiSetupApEntry);
    out = WifiSetup_WorkCalloc(1, size);
    if (out == NULL) {
        goto done;
    }
    previous = WifiSetup_WorkCalloc(1, size);
    if (previous == NULL) {
        goto done;
    }
    for (attempt = 0; attempt < 30 && !gWifiSetupWork.stop; attempt++) {
        if (WifiSetup_GetMilliseconds() >= gWifiSetupConfig.deadline) {
            break;
        }
        if (!WifiSetupLink_StartSearch(NULL, NULL, 0, 0x30BFFE)) {
            result = -2;
            goto done;
        }
        OS_CreateAlarm(&alarm);
        OS_SetAlarm(&alarm, 0xFFB10, (OSAlarmHandler)WifiSetupLink_PostEvent, (void *)WIFI_SETUP_WCM_EVENT_SEARCH_TIMEOUT);
        running = TRUE;
        result = 0;
        do {
            OS_Sleep(10);
            if (WifiSetup_GetMilliseconds() >= gWifiSetupConfig.deadline || gWifiSetupWork.stop) {
                break;
            }
            while ((event = WifiSetupLink_PopEvent()) != 0) {
                switch (event) {
                case WIFI_SETUP_WCM_EVENT_SEARCH_TIMEOUT:
                    running = FALSE;
                    break;
                case WIFI_SETUP_WCM_EVENT_FOUND_AP:
                    found = WifiSetupLink_CopyApList(gWifiSetupWork.apList, gWifiSetupWork.apListCount);
                    if (found > result) {
                        result = found;
                        OS_CancelAlarm(&alarm);
                        OS_SetAlarm(&alarm, 0xFFB10, (OSAlarmHandler)WifiSetupLink_PostEvent, (void *)WIFI_SETUP_WCM_EVENT_SEARCH_TIMEOUT);
                    }
                    break;
                case WIFI_SETUP_WCM_EVENT_SEARCH_ENDED:
                    running = FALSE;
                    break;
                case 4:
                case WIFI_SETUP_WCM_EVENT_SEARCH_STARTED:
                case WIFI_SETUP_WCM_EVENT_CONNECT_TIMEOUT:
                    break;
                case 0:
                case WIFI_SETUP_WCM_EVENT_UNKNOWN:
                case WIFI_SETUP_WCM_EVENT_FAILED:
                case 3:
                default:
                    running = FALSE;
                    break;
                }
            }
        } while (running);
        OS_CancelAlarm(&alarm);
        while (WifiSetupLink_PopEvent() != 0) {
        }
        if (gWifiSetupWork.stop) {
            break;
        }
        total = 0;
        if (result >= gWifiSetupWork.apListCount) {
            result = -6;
            goto done;
        }
        ap = gWifiSetupWork.apList;
        i = 0;
        if (result > 0) {
            for (; i < result; i++) {
                memcpy(out->entries[total].ssid, ap->ssid, sizeof(out->entries[total].ssid));
                out->entries[total].ssidLength = ap->ssidLength;
                out->entries[total].ssid[ap->ssidLength] = 0;
                out->entries[total].privacy = (ap->capability & 0x10) ? 1 : 0;
                memcpy(out->entries[total].bssid, ap->bssid, sizeof(out->entries[total].bssid));
                ap++;
                total++;
            }
        }
        out->count = result;
        if (gWifiSetupWork.state != WIFI_SETUP_SIMPLE_START_STARTED && WifiSetup_PickSetupAccessPoint(out, previous, &selected)) {
            WifiSetupApEntry *entry = &out->entries[selected];
            gWifiSetupWork.selection = selected;
            strcpy(gWifiSetupApSsid, entry->ssid);
            memcpy(gWifiSetupApBssid, entry->bssid, sizeof(gWifiSetupApBssid));
            WifiSetup_FormatMacAddress(text, (const s8 *)gWifiSetupApBssid);
            break;
        }
        memcpy(previous, out, size);
        gWifiSetupWork.state = WIFI_SETUP_SIMPLE_START_SEARCHING;
        WifiSetup_ReportSimpleStartStatus();
    }
    if (attempt >= 30 || WifiSetup_GetMilliseconds() > gWifiSetupConfig.deadline) {
        result = -3;
    } else if (gWifiSetupWork.stop) {
        result = -8;
    } else {
        result = 1;
    }
done:
    if (out != NULL) {
        WifiSetup_WorkFree(out);
    }
    if (previous != NULL) {
        WifiSetup_WorkFree(previous);
    }
    return result;
}

#pragma optimization_level reset

static int WifiSetup_SendDatagram(int socket, SocAddress *address, const u8 *unused, const void *data, int length) {
    int result = SOC_SendTo(socket, data, length, 0, address);
    if (result < 0) {
        result = -4;
    }
    return result;
}

// Broadcasts to the simple start port.
static int WifiSetup_BroadcastDatagram(int socket, const void *data, int length) {
    WifiSetupBroadcastAddress address;
    address.to.length = sizeof(SocAddress);
    address.to.family = 2;
    address.to.ip = 0xFFFFFFFF;
    address.to.port = WIFI_SETUP_SIMPLE_START_PORT;
    SOC_U32to4U8(SOCL_GetHostID(), address.host);
    return WifiSetup_SendDatagram(socket, &address.to, address.host, data, length);
}

int WifiSetup_SendSetupPacket(int socket, const WifiSetupSockAddr *to, const void *data, int length) {
    return WifiSetup_BroadcastDatagram(socket, data, length);
}

// Packet: type (2), length (2), 2 bytes, payload, 16-bit byte sum. Returns the payload or NULL.
static u8 *WifiSetup_GetPacketPayload(u8 *data, u32 *type, u32 *length) {
    u32 sum = 0;
    u8 *end;
    u8 *byte;

    *type = Swap16(*(u16 *)data);
    end = data + 6 + (*length = Swap16(*(u16 *)(data + 2)));
    for (byte = data; byte < end; byte++) {
        sum += *byte;
    }
    if ((u16)sum != Swap16(*(u16 *)end)) {
        return NULL;
    }
    return data + 6;
}

// Next record (type, length, value padded to 8 bytes) of a record list.
static u8 *WifiSetup_NextRecord(u8 **cursor, u8 *end, u32 *type, u32 *length) {
    u8 *record = *cursor;
    u32 padded;
    if (record >= end) {
        return NULL;
    }
    *type = Swap16(*(u16 *)record);
    *length = Swap16(*(u16 *)(record + 2));
    record += 4;
    padded = (*length + 11) & ~7;
    padded -= 4;
    *cursor = record + padded;
    return record;
}

u8 *WifiSetup_FirstRecord(u8 *data, u32 *type, u32 *length) {
    u8 *cursor = data + 8;
    return WifiSetup_NextRecord(&cursor, cursor + Swap16(*(u16 *)data), type, length);
}

// Builds a packet from a record list, AES-key-wrapped when `key` is given; returns its size.
u32 WifiSetup_BuildPacket(u8 *dest, u32 type, u8 *data, u32 length, const void *key) {
    u8 *end = dest;
    u8 *byte;
    u32 sum = 0;
    data[0] = 0;
    data[1] = 0;
    data[2] = 0;
    data[3] = 0;
    data[4] = 0;
    data[5] = 0;
    data[6] = 0;
    data[7] = 0;
    *(u16 *)data = Swap16((u16)(length - 8));
    if (key) {
        WifiSetup_AesKeyWrap(dest + 6, data, length, key, 16);
        length += 8;
    } else {
        memcpy(dest + 6, data, length);
    }
    dest[0] = 0;
    dest[1] = 0;
    dest[2] = 0;
    dest[3] = 0;
    dest[4] = 0;
    dest[5] = 0;
    *(u16 *)dest = Swap16((u16)type);
    *(u16 *)(dest + 2) = Swap16((u16)length);
    end += 6;
    end += length;
    for (byte = dest; byte < end; byte++) {
        sum += *byte;
    }
    *(u16 *)end = Swap16((u16)sum);
    return end + 2 - dest;
}

#pragma push
#pragma opt_propagation off

// Appends one record; returns the end of it.
static u8 *WifiSetup_AppendRecord(u8 *out, int tag, const void *source, int size) {
    int aligned;
    out[0] = 0;
    out[1] = 0;
    out[2] = 0;
    out[3] = 0;
    *(u16 *)out = Swap16((u16)tag);
    aligned = ((size + 11) & ~7) - 4;
    *(u16 *)(out + 2) = Swap16((u16)size);
    out += 4;
    memset(out, 0, aligned);
    memcpy(out, source, size);
    return out + aligned;
}

#pragma pop

// A record list holding one record; the list header stores its length.
u32 WifiSetup_BuildSingleRecordList(u8 *dst, u16 type, const void *src, u32 length) {
    int result;
    int size;
    memset(dst, 0, 8);
    result = (int)WifiSetup_AppendRecord(dst + 8, type, src, length);
    result -= (int)dst;
    size = result;
    size -= 8;
    *(u16 *)dst = size;
    return result;
}

// Reply of type 1: records 1 and 2 must be 1; record 5 >= 1 asks for the extended request.
BOOL WifiSetup_CheckVersionReply(u8 *data, BOOL *extended) {
    u32 type;
    u32 length;
    u32 tag;
    u32 size;
    u8 *cursor;
    u8 *blob = WifiSetup_GetPacketPayload(data, &type, &length);
    int record1 = 0;
    int record2;
    int record5 = 0;
    const u16 *value;
    u8 *end;
    cursor = blob;
    record2 = 0;
    if (!blob) {
        return FALSE;
    }
    if (type != WIFI_SETUP_PACKET_VERSION) {
        return FALSE;
    }
    end = blob + length;
    cursor = blob + 8;
    while ((value = (const u16 *)WifiSetup_NextRecord(&cursor, end, &tag, &size)) != NULL) {
        switch (tag) {
        case 1:
            record1 = Swap16(*value);
            break;
        case 2:
            record2 = Swap16(*value);
            break;
        case WIFI_SETUP_RECORD_EXTENDED:
            record5 = Swap16(*value);
            break;
        }
    }
    if (record1 != 1 || record2 != 1) {
        return FALSE;
    }
    if (record5 >= 1) {
        *extended = TRUE;
    } else {
        *extended = FALSE;
    }
    return TRUE;
}

// Copies the payload of a packet of `expectedType`, AES-key-unwrapped when `key` is given.
int WifiSetup_ReadPacket(u8 *data, u32 expectedType, u8 *dst, const u8 *key) {
    u32 type, length;
    u8 *payload = WifiSetup_GetPacketPayload(data, &type, &length);
    if (payload == NULL) {
        return 0;
    }
    if (type != expectedType) {
        return 0;
    }
    if (key) {
        WifiSetup_AesKeyUnwrap(dst, payload, length, key, 16);
        length -= 8;
    } else {
        memcpy(dst, payload, length);
    }
    return length;
}

// First request (type 2): version records, plus own MAC address in the extended form.
u32 WifiSetup_BuildVersionRequest(u8 *dst) {
    WifiSetupVersionRecord record;
    u8 *ptr;
    record.value = 256;
    record.version = sWifiSetupClientVersion;
    ptr = WifiSetup_AppendRecord(gWifiSetupConfig.packetBuffer, 1, &record, 2);
    ptr = WifiSetup_AppendRecord(ptr, 2, &record, 2);
    if (gWifiSetupWork.extendedRequest) {
        ptr = WifiSetup_AppendRecord(ptr, WIFI_SETUP_RECORD_EXTENDED, &record, 2);
    }
    ptr = WifiSetup_AppendRecord(ptr, 3, &record.version, 7);
    if (gWifiSetupWork.extendedRequest) {
        ptr = WifiSetup_AppendRecord(ptr, WIFI_SETUP_RECORD_MAC_ADDRESS, gWifiSetupOwnMacAddress, sizeof(gWifiSetupOwnMacAddress));
    }
    return WifiSetup_BuildPacket(dst, WIFI_SETUP_PACKET_VERSION_REQUEST, gWifiSetupRecordBuffer, ptr - gWifiSetupConfig.packetBuffer + 8, NULL);
}

static BOOL WifiSetup_GetOwnMacAddress(u8 *mac) {
    OS_GetMacAddress(mac);
    return TRUE;
}

// Orders the access point's and our MAC address (the smaller one first).
BOOL WifiSetup_BuildMacPair(WifiSetupMacPair *pair, void *unused) {
    u8 other[6];
    u8 own[6];
    char text1[32];
    char text2[32];
    u8 *src;

    memcpy(pair->prefix, sStr_WARP, sizeof(pair->prefix));
    memcpy(other, gWifiSetupApBssid, sizeof(other));
    other[0] &= 0xFD;
    WifiSetup_GetOwnMacAddress(own);
    memcpy(gWifiSetupOwnMacAddress, own, sizeof(gWifiSetupOwnMacAddress));
    if (memcmp(other, own, sizeof(other)) <= 0) {
        memcpy(pair->first, own, sizeof(pair->first));
        src = other;
    } else {
        memcpy(pair->first, other, sizeof(pair->first));
        src = own;
    }
    memcpy(pair->second, src, sizeof(pair->second));
    if (gWifiSetupConfig.debug) {
        WifiSetup_FormatMacAddress(text1, (const s8 *)own);
        WifiSetup_FormatMacAddress(text2, (const s8 *)other);
    }
    return TRUE;
}

// Settings reply: records 0x201-0x20A.
int WifiSetup_ParseSettingsRecords(const u8 *data) {
    u8 *start = (u8 *)data + 8;
    u8 *pos = start;
    u8 *value;
    int result = 0;
    u32 bytes = Swap16(*(const u16 *)data);
    u32 type;
    u32 length;
    value = WifiSetup_NextRecord(&pos, start + bytes, &type, &length);
    while (value) {
        switch (type) {
        case WIFI_SETUP_RECORD_SSID:
            memset(gWifiSetupRecvSsid, 0, sizeof(gWifiSetupRecvSsid));
            memcpy(gWifiSetupRecvSsid, value, length);
            result = 1;
            break;
        case WIFI_SETUP_RECORD_SECURITY:
            gWifiSetupRecvSecurity[0] = Swap16(*(u16 *)value);
            break;
        case 0x203: {
            int i = 0;
            u8 *entry = gWifiSetupReply;
            u16 setting = Swap16(*(u16 *)value);
            do {
                *(u32 *)(entry + 0x15c) = setting;
                entry += 40;
                i++;
            } while (i < 4);
            break;
        }
        case 0x204: {
            u8 *entry = gWifiSetupReply;
            int i = 0;
            u16 setting = Swap16(*(u16 *)value);
            do {
                *(u32 *)(entry + 0x160) = setting;
                entry += 40;
                i++;
            } while (i < 4);
            break;
        }
        case 0x205:
            gWifiSetupRecvSecurity[1] = Swap16(*(u16 *)value);
            break;
        case WIFI_SETUP_RECORD_WEP_KEY_0:
        case WIFI_SETUP_RECORD_WEP_KEY_1:
        case WIFI_SETUP_RECORD_WEP_KEY_2:
        case WIFI_SETUP_RECORD_WEP_KEY_3: {
            u8 *out;
            int i;
            memset(gWifiSetupRecvWepKeys[type - WIFI_SETUP_RECORD_WEP_KEY_0], 0, 32);
            if (gWifiSetupRecvSecurity[12] == 1) {
                out = gWifiSetupRecvWepKeys[type - WIFI_SETUP_RECORD_WEP_KEY_0];
                for (i = 0; i < (int)length; i++) {
                    out += WifiSetup_FormatHexByte((char *)out, *(s8 *)value++);
                }
            } else {
                memcpy(gWifiSetupRecvWepKeys[type - WIFI_SETUP_RECORD_WEP_KEY_0], value, length);
            }
            break;
        }
        case WIFI_SETUP_RECORD_WPA_KEY:
            memset(gWifiSetupRecvWpaKey, 0, sizeof(gWifiSetupRecvWpaKey));
            memcpy(gWifiSetupRecvWpaKey, value, length);
            break;
        }
        value = WifiSetup_NextRecord(&pos, start + bytes, &type, &length);
    }
    return result;
}

static BOOL WifiSetup_HexToBytes(u8 *dst, const char *src, int length) {
    int len = length;
    int ch;
    int nibble = 0;
    const char *text = src;
    int i = nibble;

    for (; i < len; i++) {
        ch = text[i];
        switch (ch) {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            nibble += ch - '0';
            break;
        case 'a':
        case 'b':
        case 'c':
        case 'd':
        case 'e':
        case 'f':
            nibble += ch - 'a' + 10;
            break;
        case 'A':
        case 'B':
        case 'C':
        case 'D':
        case 'E':
        case 'F':
            nibble += ch - 'A' + 10;
            break;
        default:
            return FALSE;
        }
        if ((i % 2) == 0) {
            nibble <<= 4;
        } else {
            dst[i / 2] = nibble;
            nibble = 0;
        }
    }
    return TRUE;
}

// Copies the received settings into the result block; WEP keys of 5/13/16 characters or
// 10/26/32 hex digits.
int WifiSetup_StoreSimpleStartResult(void) {
    int result = 1;
    int i;
    u8 *src;
    char buf[33];
    char *key;
    u8 *out;
    strcpy((char *)&gWifiSetupResult, (char *)gWifiSetupRecvSsid);
    switch (gWifiSetupRecvSecurity[0]) {
    case 0:
        *(u32 *)(ov13_0224E0B0 + 0xC) = WM_WEPMODE_NO;
        break;
    case 1:
        if (gWifiSetupRecvSecurity[1] == 0) {
            result = -7;
            break;
        }
        *(u32 *)(ov13_0224E0B0 + 0x10) = gWifiSetupRecvSecurity[1];
        src = (u8 *)gWifiSetupRecvWepKeys;
        out = gWifiSetupResultWepKeys;
        i = 0;
        key = buf;
        for (; i < 4; i++, src += 0x28, out += 0x20) {
            memcpy(buf, src, 0x20);
            buf[32] = 0;
            switch (strlen(buf)) {
            case 0:
                break;
            case 5:
                *(u32 *)(ov13_0224E0B0 + 0xC) = WM_WEPMODE_40BIT;
                memcpy(out, key, 5);
                break;
            case 10:
                *(u32 *)(ov13_0224E0B0 + 0xC) = WM_WEPMODE_40BIT;
                WifiSetup_HexToBytes(out, key, 10);
                break;
            case 13:
                *(u32 *)(ov13_0224E0B0 + 0xC) = WM_WEPMODE_104BIT;
                memcpy(out, key, 13);
                break;
            case 26:
                *(u32 *)(ov13_0224E0B0 + 0xC) = WM_WEPMODE_104BIT;
                WifiSetup_HexToBytes(out, key, 26);
                break;
            case 16:
                *(u32 *)(ov13_0224E0B0 + 0xC) = WM_WEPMODE_128BIT;
                memcpy(out, key, 16);
                break;
            case 32:
                *(u32 *)(ov13_0224E0B0 + 0xC) = WM_WEPMODE_128BIT;
                WifiSetup_HexToBytes(out, key, 32);
                break;
            default:
                result = -7;
                break;
            }
        }
        break;
    case 2:
        *(u32 *)(ov13_0224E0B0 + 0xC) = 4;
        memcpy(&gWifiSetupResultWpaKey, &gWifiSetupRecvWpaKey, sizeof(WifiSetupSettings64));
        break;
    case 3:
        *(u32 *)(ov13_0224E0B0 + 0xC) = 5;
        memcpy(&gWifiSetupResultWpaKey, &gWifiSetupRecvWpaKey, sizeof(WifiSetupSettings64));
        break;
    default:
        result = -7;
        break;
    }
    return result;
}
