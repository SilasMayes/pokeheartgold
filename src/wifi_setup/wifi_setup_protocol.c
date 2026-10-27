#include "global.h"

#include "wifi_setup/wifi_setup.h"
#include "wifi_setup/wifi_setup_wcm.h"

#define U16_AT(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define U32_AT(p, o) (*(u32 *)((u8 *)(p) + (o)))
// Item of a reply record: type, data length, offset of the next item (0 for the last one), data
typedef struct WifiSetupAossItem {
    u8 type;
    u8 reserved;
    u16 length;
    u16 next;
    u8 data[1];
} WifiSetupAossItem;

static enum WifiSetupAossStep WifiSetup_HandleJoinReply(enum WifiSetupAossStep state, WifiSetupAossReceived *received, int *counter, WifiSetupAossPacketParams *params);
static enum WifiSetupAossStep WifiSetup_HandleSettingsReply(enum WifiSetupAossStep state, WifiSetupAossReceived *received, int *counter, WifiSetupAossPacketParams *params);
static enum WifiSetupAossStep WifiSetup_HandleDoneReply(enum WifiSetupAossStep state, void *packet, int *counter, void *context);
static int WifiSetup_DecryptPacket(WifiSetupAossPacket *packet);
static int WifiSetup_CheckPeer(int value, const u8 *address);
static int WifiSetup_CheckReplySequence(const WifiSetupAossTag *expected, WifiSetupAossTag *received);
static int WifiSetup_ParseJoinReply(const u8 *src, u8 *dst);
static int WifiSetup_ReadLittleEndian(const u8 *src, int length);
static int WifiSetup_ParseWepRecord(const u8 *src, WifiSetupKeyRecord *dst);
static int WifiSetup_ParseWpaRecord(const u8 *src, WifiSetupWpaKeyRecord *dst);
static int WifiSetup_ParseType70Record(const u8 *src, u8 *dst);
static int WifiSetup_ParseSecurityRecords(int id, u8 *cursor, int remaining, WifiSetupAossKeyRecords *out, u8 *other);
static BOOL WifiSetup_IsEncryptionRequested(int value);
static int WifiSetup_SendJoinRequest(const WifiSetupAossAddresses *addresses, const WifiSetupAossPacketParams *params, int socket);
static int WifiSetup_SendSettingsRequest(const WifiSetupAossAddresses *addresses, const WifiSetupAossPacketParams *params, int socket);
static int WifiSetup_SendDoneRequest(const WifiSetupAossAddresses *addresses, const WifiSetupAossPacketParams *params, int socket);
static int WifiSetup_BuildJoinPayload(u8 *dst);
static void WifiSetup_WriteBody(BOOL encrypt, WifiSetupAossBody *body, const void *src, s16 *length, s16 *flag, const void *extra);
static void WifiSetup_WritePacketHeader(WifiSetupAossPacket *packet, enum WifiSetupAossPacketKind kind, int length, int flags, s8 checksum, s8 protocol, const u8 *tag);
static void WifiSetup_SendPacket(const WifiSetupAossPacket *packet, int size, int index, int socket);
static int WifiSetup_Encrypt(void *src, void *dst, int size, u8 *checksum, u16 *seedDst, const u8 *seedSrc, int seedSize);
static int WifiSetup_Decrypt(void *dst, const void *src, int size, int expected, u16 *seedDst, const u8 *seedSrc, int seedSize);
static void WifiSetup_CipherInit(WifiSetupCipher *state, const u8 *key, u32 keySize, u32 tableSize);
static void WifiSetup_CipherXor(WifiSetupCipher *state, u8 *dst, const u8 *src, u32 size);
static u8 WifiSetup_CipherNextByte(WifiSetupCipher *state);
static u8 WifiSetup_CalcCrc32(const void *data, s32 size);
static u32 WifiSetup_UpdateCrc32(u32 crc, const u8 *data, s32 size, s32 init, u32 *table);
static void WifiSetup_InitCrc32Table(s32 unused, u32 *table);
static s32 WifiSetup_Scramble(void *dst, s32 size, const s8 *key, s32 keySize);
static void WifiSetup_ScrambleMakeKey(int start, s8 *out, int length, const s8 *key, int keylen);
static void WifiSetup_ScrambleXorHalf(s8 *in, u8 *out, int length);
static void WifiSetup_ScrambleSwapHalves(u8 *dst, s32 size, u8 *tmp);

int WifiSetup_CheckPrintable(const u8 *data, int length) {
    int i;
    for (i = 0; i < length; i++) {
        u8 value = *data++;
        if (value < 0x20 || value > 0x7F) {
            return -1;
        }
    }
    return 0;
}

enum WifiSetupAossScanResult WifiSetup_FindAossAccessPoint(WifiSetupAossApList *list) {
    enum WifiSetupAossScanResult result = WIFI_SETUP_AOSS_SCAN_FOUND;
    int matches = 0;
    int i;
    int count;
    if (list->count == 0) {
        return WIFI_SETUP_AOSS_SCAN_NONE;
    }
    count = list->count;
    if (count > NELEMS(list->entries)) {
        count = NELEMS(list->entries);
    }
    for (i = 0; i < count; i++) {
        if (list->entries[i].mode & 1) {
            if (list->entries[i].ssidLength == WifiSetup_StrLen(sStr_ESSID_AOSS) && WifiSetup_MemCompare(list->entries[i].ssid, (const u8 *)sStr_ESSID_AOSS, WifiSetup_StrLen(sStr_ESSID_AOSS)) == 0) {
                matches++;
            }
        }
    }
    if (matches > 1) {
        result = WIFI_SETUP_AOSS_SCAN_SEVERAL;
    }
    if (matches == 0) {
        result = WIFI_SETUP_AOSS_SCAN_NONE;
    }
    return result;
}

int WifiSetup_InitAossConnectInfo(WifiSetupAossConnectInfo *info) {
    info->ssidLength = WifiSetup_StrLen(sStr_ESSID_AOSS);
    WifiSetup_MemCopy(info->ssid, sStr_ESSID_AOSS, info->ssidLength);
    info->mode = 1;
    info->keyLength = WifiSetup_StrLen(sStr_MELCO);
    if (info->keyLength > 13) {
        return -1;
    }
    WifiSetup_MemCopy(info->key, sStr_MELCO, info->keyLength);
    return 0;
}

void WifiSetup_InitPacketAddresses(int count, WifiSetupAossPacketParams *params, const u8 *mac) {
    WifiSetupAossTag *tag = params->tags;
    int i;
    for (i = 0; i < count; i++) {
        WifiSetup_MemCopy(tag->mac, mac, sizeof(tag->mac));
        tag->sequence = WifiSetup_Random();
        tag->sequence = WifiSetup_HostToNet16(tag->sequence);
        tag++;
    }
}

int WifiSetup_SetStatus(enum WifiSetupAossStatus status) {
    if (status == WIFI_SETUP_AOSS_STATUS_RESET) {
        gWifiSetupSocket.lastStatus = status;
        return 0;
    }
    if (gWifiSetupSocket.lastStatus != status) {
        gWifiSetupSocket.lastStatus = status;
        return WifiSetup_NotifyStatus(status);
    }
    return 0;
}

enum WifiSetupAossStep WifiSetup_HandlePacket(enum WifiSetupAossStep state, WifiSetupAossReceived *received, int *counter, WifiSetupAossPacketParams *params, int socket) {
    WifiSetupAossPacket *header = &received->packet;
    int type;

    if (WifiSetup_NetToHost16(header->version) < 1) {
        (*counter)++;
        return state;
    }
    if (header->protocol != WIFI_SETUP_AOSS_PROTOCOL) {
        (*counter)++;
        return state;
    }
    if (WifiSetup_DecryptPacket(&received->packet) > 0) {
        (*counter)++;
        return state;
    }
    type = WifiSetup_NetToHost16(header->kind);
    switch (type) {
    case WIFI_SETUP_AOSS_KIND_JOIN_REPLY:
        state = WifiSetup_HandleJoinReply(state, received, counter, params);
        break;
    case WIFI_SETUP_AOSS_KIND_SETTINGS_REPLY:
        state = WifiSetup_HandleSettingsReply(state, received, counter, params);
        break;
    case WIFI_SETUP_AOSS_KIND_DONE_REPLY:
        state = WifiSetup_HandleDoneReply(state, received, counter, params);
        break;
    }
    return state;
}

static enum WifiSetupAossStep WifiSetup_HandleJoinReply(enum WifiSetupAossStep state, WifiSetupAossReceived *received, int *counter, WifiSetupAossPacketParams *params) {
    WifiSetupAossPacket *header;
    WifiSetupAossBody *body;
    int value;

    if (state != WIFI_SETUP_AOSS_STEP_JOIN) {
        (*counter)++;
        return state;
    }
    header = &received->packet;
    body = &received->packet.body;
    if (WifiSetup_CheckReplySequence(&params->tags[0], &header->tag) < 0) {
        (*counter)++;
        return state;
    }
    if (WifiSetup_NetToHost16(body->record.length) == 0) {
        (*counter)++;
        return state;
    }
    if (body->record.type == WIFI_SETUP_AOSS_RECORD_STATUS) {
        value = WifiSetup_NetToHost32(body->record.data.status);
        if (value == -2) {
            WifiSetup_SetError(0x14);
        } else {
            value = WifiSetup_NetToHost32(body->record.data.status);
            if (value == -3) {
                WifiSetup_SetError(0x15);
            } else {
                WifiSetup_SetError(0x18);
            }
        }
        return WIFI_SETUP_AOSS_STEP_FAILED;
    }
    if (body->record.type != WIFI_SETUP_AOSS_RECORD_JOIN) {
        (*counter)++;
        return state;
    }
    value = WifiSetup_ParseJoinReply(body->record.data.bytes, gWifiSetupJoinReply);
    if (value < 0) {
        if (value == -2) {
            WifiSetup_SetError(0x16);
            return WIFI_SETUP_AOSS_STEP_FAILED;
        }
        (*counter)++;
        return state;
    }
    gWifiSetupState.encryptBody = WifiSetup_IsEncryptionRequested(WifiSetup_NetToHost16(header->flags));
    *counter = 0;
    return WIFI_SETUP_AOSS_STEP_SETTINGS;
}

static enum WifiSetupAossStep WifiSetup_HandleSettingsReply(enum WifiSetupAossStep state, WifiSetupAossReceived *received, int *counter, WifiSetupAossPacketParams *params) {
    WifiSetupAossPacket *header;
    WifiSetupAossBody *body;
    int value;

    if (state != WIFI_SETUP_AOSS_STEP_SETTINGS) {
        (*counter)++;
        return state;
    }
    header = &received->packet;
    body = &received->packet.body;
    if (WifiSetup_CheckReplySequence(&params->tags[1], &header->tag) < 0) {
        (*counter)++;
        return state;
    }
    if (WifiSetup_NetToHost16(body->record.length) == 0) {
        (*counter)++;
        return state;
    }
    if (body->record.type == WIFI_SETUP_AOSS_RECORD_STATUS) {
        value = WifiSetup_NetToHost32(body->record.data.status);
        if (value == -2) {
            WifiSetup_SetError(0x14);
        } else {
            value = WifiSetup_NetToHost32(body->record.data.status);
            if (value == -3) {
                WifiSetup_SetError(0x15);
            } else {
                WifiSetup_SetError(0x18);
            }
        }
        return WIFI_SETUP_AOSS_STEP_FAILED;
    }
    WifiSetup_MemFill(gWifiSetupSecurityRecords, 0, sizeof(gWifiSetupSecurityRecords));
    value = WifiSetup_NetToHost16(header->bodyLength);
    if (WifiSetup_ParseSecurityRecords(0, body->bytes, value, gWifiSetupSecurityRecords, gWifiSetupJoinReply) < 0) {
        (*counter)++;
        return state;
    }
    if ((gWifiSetupState.receivedMask & gWifiSetupState.requestedMask) == 0) {
        return state;
    }
    *counter = 0;
    return WIFI_SETUP_AOSS_STEP_DONE;
}

static enum WifiSetupAossStep WifiSetup_HandleDoneReply(enum WifiSetupAossStep state, void *packet, int *counter, void *context) {
    u8 *body;
    int value;

    if (state != WIFI_SETUP_AOSS_STEP_DONE) {
        (*counter)++;
        return state;
    }
    body = (u8 *)packet + 0x24;
    context = (u8 *)context + 0x10;
    packet = (u8 *)packet + 0xC;
    if (WifiSetup_CheckReplySequence(context, &((WifiSetupAossPacket *)packet)->tag) < 0) {
        (*counter)++;
        return state;
    }
    if (body[0] != WIFI_SETUP_AOSS_RECORD_STATUS) {
        (*counter)++;
        return state;
    }
    if (WifiSetup_NetToHost16(U16_AT(body, 2)) == 0) {
        (*counter)++;
        return state;
    }
    value = WifiSetup_NetToHost32(U32_AT(body, 4));
    if (value == 0) {
        return WIFI_SETUP_AOSS_STEP_FINISHED;
    }
    value = WifiSetup_NetToHost32(U32_AT(body, 4));
    if (value == -2) {
        WifiSetup_SetError(0x14);
        return WIFI_SETUP_AOSS_STEP_FAILED;
    }
    value = WifiSetup_NetToHost32(U32_AT(body, 4));
    if (value == -3) {
        WifiSetup_SetError(0x15);
        return WIFI_SETUP_AOSS_STEP_FAILED;
    }
    WifiSetup_SetError(0x18);
    return WIFI_SETUP_AOSS_STEP_FAILED;
}

static int WifiSetup_DecryptPacket(WifiSetupAossPacket *packet) {
    u8 address[8];
    WifiSetupAossEncryptedBody *body = &packet->body.encrypted;
    int result;
    WifiSetup_MemCopy(address, &packet->tag, sizeof(address));
    result = WifiSetup_Scramble(address, sizeof(address), sStr_MELCO, WifiSetup_StrLen(sStr_MELCO));
    if (result == -1) {
        WifiSetup_SetError(WIFI_SETUP_AOSS_ERROR_OUT_OF_MEMORY);
        return -100;
    }
    result = WifiSetup_CheckPeer(WifiSetup_NetToHost16(packet->kind), address);
    if (result == 0) {
        int size;
        void *buffer;
        if (WifiSetup_NetToHost16(packet->kind) == WIFI_SETUP_AOSS_KIND_JOIN) {
            WifiSetup_MemCopy(gWifiSetupPeerAddress, address, sizeof(gWifiSetupPeerAddress));
        }
        if ((WifiSetup_NetToHost16(packet->flags) & 15) == 0) {
            return 0;
        }
        size = WifiSetup_NetToHost16(body->length);
        buffer = WifiSetup_Alloc(size);
        if (buffer == NULL) {
            WifiSetup_SetError(WIFI_SETUP_AOSS_ERROR_OUT_OF_MEMORY);
            return 100;
        }
        if (WifiSetup_Decrypt(body->data, buffer, size, packet->checksum, &body->seed, gWifiSetupPeerAddress, 8) < 0) {
            WifiSetup_Free(buffer);
            if (WifiSetup_GetError() == WIFI_SETUP_AOSS_ERROR_OUT_OF_MEMORY) {
                return 100;
            }
            return 200;
        }
        WifiSetup_MemCopy(body, buffer, size);
        packet->bodyLength = WifiSetup_HostToNet16((u16)size);
        WifiSetup_Free(buffer);
        result = 0;
    }
    return result;
}

static int WifiSetup_CheckPeer(int value, const u8 *address) {
    int i;
    BOOL present;
    int result;
    result = 0;
    present = result;
    for (i = 0; i < 6; i++) {
        if (gWifiSetupPeerAddress[i] != 0) {
            present = TRUE;
            break;
        }
    }
    if (present) {
        if (WifiSetup_MemCompare(gWifiSetupPeerAddress, address, 6) != 0) {
            result = 1;
        }
    } else if (value != WIFI_SETUP_AOSS_KIND_JOIN) {
        result = 2;
    }
    return result;
}

static int WifiSetup_CheckReplySequence(const WifiSetupAossTag *expected, WifiSetupAossTag *received) {
    int result = 0;
    WifiSetup_Scramble(received, sizeof(*received), sStr_MELCO, WifiSetup_StrLen(sStr_MELCO));
    if (WifiSetup_MemCompare(expected->mac, received->mac, sizeof(received->mac)) != 0) {
        result = -1;
    } else {
        int expectedSequence = WifiSetup_NetToHost16(expected->sequence);
        int receivedSequence = WifiSetup_NetToHost16(received->sequence);
        if (expectedSequence + 1 != receivedSequence) {
            result = -2;
        }
    }
    return result;
}

static int WifiSetup_ParseJoinReply(const u8 *src, u8 *dst) {
    const WifiSetupAossItem *entry;
    u8 *dst80;
    int length;

    WifiSetup_MemFill(dst, 0, 0x104);
    dst80 = dst;
    entry = (const WifiSetupAossItem *)src;
    dst80 += 0x80;
    for (;;) {
        length = WifiSetup_NetToHost16(entry->length);
        if (length <= 0) {
            return -1;
        }
        switch (entry->type) {
        case 0:
            WifiSetup_MemCopy(dst, entry->data, length);
            break;
        case 1:
            WifiSetup_MemCopy(dst80, entry->data, length);
            break;
        case 2:
            WifiSetup_MemCopy(dst + 0x100, entry->data, length);
            break;
        case 3:
        case 4:
            if (((int (*)(int))WifiSetup_NetToHost16)(entry->data[0]) <= 0) {
                return -2;
            }
            break;
        case 5:
            gWifiSetupState.address = WifiSetup_NetToHost32(WifiSetup_ReadLittleEndian(entry->data, length));
            break;
        case 6:
            gWifiSetupState.netmask = WifiSetup_NetToHost32(WifiSetup_ReadLittleEndian(entry->data, length));
            break;
        default:
            return -1;
        }
        if (entry->next == 0) {
            break;
        }
        entry = (const WifiSetupAossItem *)(src + WifiSetup_NetToHost16(entry->next));
    }
    return 0;
}

static int WifiSetup_ReadLittleEndian(const u8 *src, int length) {
    int offset = length - 1;
    int value = 0;
    const u8 *byte = src + offset;
    int i = value;
    for (; i < length; i++) {
        value = (value << 8) + *byte--;
    }
    return value;
}

static int WifiSetup_ParseWepRecord(const u8 *src, WifiSetupKeyRecord *dst) {
    const WifiSetupAossItem *entry = (const WifiSetupAossItem *)(src + 6);
    const u8 *base;
    u8 *ssid = dst->ssid;
    u8 *key3 = dst->keys[3];
    u8 *key2 = dst->keys[2];
    u8 *key1 = dst->keys[1];
    u8 *key0 = dst->keys[0];
    u32 length;
    base = (const u8 *)entry;

    for (;;) {
        length = WifiSetup_NetToHost16(entry->length);
        switch (entry->type) {
        case 0x10:
        case 0x11:
        case 0x12:
        case 0x13:
            if (length > 5) {
                return -1;
            }
            break;
        case 0x20:
        case 0x21:
        case 0x22:
        case 0x23:
            if (length > 13) {
                return -1;
            }
            break;
        case 0x15:
        case 0x25:
            if (length > 33) {
                return -1;
            }
            break;
        }
        switch (entry->type) {
        case 0x10:
        case 0x20:
            WifiSetup_MemCopy(key0, entry->data, length);
            dst->length = length;
            break;
        case 0x11:
        case 0x21:
            WifiSetup_MemCopy(key1, entry->data, length);
            dst->length = length;
            break;
        case 0x12:
        case 0x22:
            WifiSetup_MemCopy(key2, entry->data, length);
            dst->length = length;
            break;
        case 0x13:
        case 0x23:
            WifiSetup_MemCopy(key3, entry->data, length);
            dst->length = length;
            break;
        case 0x15:
        case 0x25:
            if (length != 0 && entry->data[length - 1] != 0) {
                return -1;
            }
            WifiSetup_MemCopy(ssid, entry->data, length);
            break;
        default:
            return -1;
        }
        if (entry->next == 0) {
            break;
        }
        entry = (const WifiSetupAossItem *)(base + WifiSetup_NetToHost16(entry->next));
    }
    return 0;
}

static int WifiSetup_ParseWpaRecord(const u8 *src, WifiSetupWpaKeyRecord *dst) {
    const WifiSetupAossItem *entry = (const WifiSetupAossItem *)(src + 6);
    const u8 *base;
    u8 *ssid = dst->ssid;
    u8 *key = dst->key;
    u32 length;
    base = (const u8 *)entry;

    for (;;) {
        length = WifiSetup_NetToHost16(entry->length);
        switch (entry->type) {
        case 0x30:
        case 0x40:
            if (length > 0x40) {
                return -1;
            }
            break;
        case 0x35:
        case 0x45:
            if (length > 0x21) {
                return -1;
            }
            break;
        }
        switch (entry->type) {
        case 0x30:
        case 0x40:
            WifiSetup_MemCopy(key, entry->data, length);
            dst->length = length;
            break;
        case 0x35:
        case 0x45:
            if (length != 0 && entry->data[length - 1] != 0) {
                return -1;
            }
            WifiSetup_MemCopy(ssid, entry->data, length);
            break;
        default:
            return -1;
        }
        if (entry->next == 0) {
            break;
        }
        entry = (const WifiSetupAossItem *)(base + WifiSetup_NetToHost16(entry->next));
    }
    return 0;
}

static int WifiSetup_ParseType70Record(const u8 *src, u8 *dst) {
    const WifiSetupAossItem *item = (const WifiSetupAossItem *)(src + 6);
    int size = WifiSetup_NetToHost16(item->length);
    if (size <= 0) {
        return -1;
    }
    if (item->type != 0x70) {
        return -1;
    }
    WifiSetup_MemCopy(dst, item->data, size);
    return 0;
}

static int WifiSetup_ParseSecurityRecords(int id, u8 *cursor, int remaining, WifiSetupAossKeyRecords *out, u8 *other) {
    int flags = 0;
    if (remaining <= 0) {
        return -2;
    }
    WifiSetupAossRecord *record;
    for (;;) {
        record = (WifiSetupAossRecord *)cursor;
        if (record->type == sWifiSetupSecurityRecordTypes[id]) {
            break;
        }
        int skip = WifiSetup_NetToHost16(record->length) + 4;
        remaining -= skip;
        cursor += skip;
        if (remaining <= 0) {
            return -4;
        }
    }
    u16 encoded = record->length;
    cursor += 4;
    int size = WifiSetup_NetToHost16(encoded);
    WifiSetupAossKeyRecords *records = &out[id];
    u32 offset;
    u8 *otherCopy;
    otherCopy = other;
    offset = (id + 3) * 128;
    do {
        int result;
        switch (cursor[0]) {
        case 3:
            result = WifiSetup_ParseWepRecord(cursor, &records->wep64);
            flags |= WIFI_SETUP_AOSS_SETTING_WEP64;
            break;
        case 4:
            result = WifiSetup_ParseWepRecord(cursor, &records->wep128);
            flags |= WIFI_SETUP_AOSS_SETTING_WEP128;
            break;
        case 5:
            result = WifiSetup_ParseWpaRecord(cursor, &records->wpaTkip);
            flags |= WIFI_SETUP_AOSS_SETTING_WPA_TKIP;
            break;
        case 6:
            result = WifiSetup_ParseWpaRecord(cursor, &records->wpaAes);
            flags |= WIFI_SETUP_AOSS_SETTING_WPA_AES;
            break;
        case 10:
            result = WifiSetup_ParseType70Record(cursor, otherCopy + offset);
            break;
        default:
            result = -3;
            break;
        }
        if (result) {
            return result;
        }
        int skip = WifiSetup_NetToHost16(*(u16 *)(cursor + 2)) + 4;
        size -= skip;
        cursor += skip;
    } while (size > 0);
    gWifiSetupState.receivedMask |= flags;
    return 0;
}

static BOOL WifiSetup_IsEncryptionRequested(int value) {
    BOOL result = FALSE;
    if (value & 0x10) {
        result = TRUE;
    }
    return result;
}

int WifiSetup_SendRequest(enum WifiSetupAossStep step, const WifiSetupAossAddresses *addresses, WifiSetupAossPacketParams *params, int socket) {
    switch (step) {
    case WIFI_SETUP_AOSS_STEP_JOIN:
        WifiSetup_SetStatus(WIFI_SETUP_AOSS_STATUS_JOINING);
        return WifiSetup_SendJoinRequest(addresses, params, socket);
    case WIFI_SETUP_AOSS_STEP_SETTINGS:
        WifiSetup_SetStatus(WIFI_SETUP_AOSS_STATUS_GETTING_SETTINGS);
        return WifiSetup_SendSettingsRequest(addresses, params, socket);
    case WIFI_SETUP_AOSS_STEP_DONE:
        WifiSetup_SetStatus(WIFI_SETUP_AOSS_STATUS_FINISHING);
        return WifiSetup_SendDoneRequest(addresses, params, socket);
    default:
        return -1;
    }
}

static int WifiSetup_SendJoinRequest(const WifiSetupAossAddresses *addresses, const WifiSetupAossPacketParams *params, int socket) {
    struct Header {
        s8 value;
        u8 pad;
        s16 flag;
        s16 length;
    };

    u8 data[8];
    struct Header header;
    WifiSetupAossPacket *packet;
    u8 *payload;
    WifiSetupAossBody *body;

    header.value = 0;
    header.length = 0;
    header.flag = 0;
    packet = &gWifiSetupState.data->send;
    WifiSetup_MemFill(packet, 0, sizeof(WifiSetupAossPacket));
    payload = WifiSetup_Alloc(0x210);
    if (payload == NULL) {
        WifiSetup_SetError(WIFI_SETUP_AOSS_ERROR_OUT_OF_MEMORY);
        return -1;
    }
    WifiSetup_MemFill(payload, 0, 0x210);
    body = &packet->body;
    WifiSetup_MemCopy(gWifiSetupPeerAddress, &params->tags[0], sizeof(gWifiSetupPeerAddress));
    WifiSetup_MemCopy(data, gWifiSetupPeerAddress, sizeof(data));
    header.length = WifiSetup_BuildJoinPayload(payload + 4);
    if (header.length < 0) {
        WifiSetup_SetError(WIFI_SETUP_AOSS_ERROR_JOIN_PAYLOAD);
        if (payload != NULL) {
            WifiSetup_Free(payload);
        }
        return -1;
    }
    payload[0] = 0;
    *(u16 *)(payload + 2) = WifiSetup_HostToNet16((u16)header.length);
    header.length += 4;
    WifiSetup_WriteBody(FALSE, body, payload, &header.length, &header.flag, &header);
    header.flag |= 0x10;
    if (WifiSetup_Scramble(data, sizeof(data), sStr_MELCO, 6) != 0) {
        WifiSetup_SetError(WIFI_SETUP_AOSS_ERROR_OUT_OF_MEMORY);
        if (payload != NULL) {
            WifiSetup_Free(payload);
        }
        return -1;
    }
    WifiSetup_WritePacketHeader(packet, WIFI_SETUP_AOSS_KIND_JOIN, header.length, header.flag, header.value, WIFI_SETUP_AOSS_PROTOCOL, data);
    header.length += 0x18;
    WifiSetup_SendPacket(packet, header.length, 0xFF, socket);
    if (payload != NULL) {
        WifiSetup_Free(payload);
    }
    return 0;
}

static int WifiSetup_SendSettingsRequest(const WifiSetupAossAddresses *addresses, const WifiSetupAossPacketParams *params, int socket) {
    struct Header {
        s8 value;
        u8 pad;
        s16 flag;
        s16 length;
        u16 padEnd;
    };

    u8 data[8];
    WifiSetupAossRecord record;
    struct Header header;
    WifiSetupAossPacket *packet;
    int size;

    header.value = 0;
    header.length = 0;
    header.flag = 0;
    packet = &gWifiSetupState.data->send;
    WifiSetup_MemFill(&record, 0, sizeof(WifiSetupAossRecord));
    WifiSetup_MemFill(packet, 0, sizeof(WifiSetupAossPacket));
    record.type = WIFI_SETUP_AOSS_RECORD_SETTINGS;
    record.reserved = 0;
    record.length = WifiSetup_HostToNet16(4);
    record.data.status = gWifiSetupState.requestedMask;
    record.data.status = WifiSetup_HostToNet32(record.data.status);
    header.length = 8;
    WifiSetup_WriteBody(gWifiSetupState.encryptBody, &packet->body, &record, &header.length, &header.flag, &header);
    WifiSetup_MemCopy(data, &params->tags[1], sizeof(data));
    size = WifiSetup_Scramble(data, sizeof(data), sStr_MELCO, 6);
    if (size != 0) {
        WifiSetup_SetError(WIFI_SETUP_AOSS_ERROR_OUT_OF_MEMORY);
        return -1;
    }
    WifiSetup_WritePacketHeader(packet, WIFI_SETUP_AOSS_KIND_SETTINGS, header.length, header.flag, header.value, WIFI_SETUP_AOSS_PROTOCOL, data);
    header.length += 0x18;
    WifiSetup_SendPacket(packet, header.length, 0, socket);
    return 0;
}

static int WifiSetup_SendDoneRequest(const WifiSetupAossAddresses *addresses, const WifiSetupAossPacketParams *params, int socket) {
    u8 data[8];
    WifiSetupAossPacket *packet = &gWifiSetupState.data->send;
    int size;

    WifiSetup_MemFill(packet, 0, sizeof(WifiSetupAossPacket));
    WifiSetup_MemCopy(data, &params->tags[2], sizeof(data));
    size = WifiSetup_StrLen(sStr_MELCO);
    WifiSetup_Scramble(data, sizeof(data), sStr_MELCO, size);
    WifiSetup_WritePacketHeader(packet, WIFI_SETUP_AOSS_KIND_DONE, 0, 0, 0, WIFI_SETUP_AOSS_PROTOCOL, data);
    WifiSetup_SendPacket(packet, offsetof(WifiSetupAossPacket, body), 0, socket);
    return 0;
}

static int WifiSetup_BuildJoinPayload(u8 *dst) {
    s16 sourceLen;
    s16 secondLen;
    s16 total = 0;
    WifiSetupAossItem *key = (WifiSetupAossItem *)dst;
    WifiSetupAossItem *second;
    u32 value;

    key->type = ov13_0224CFB8[0x1D];
    key->reserved = 1;
    sourceLen = gWifiSetupState.keyLength;
    WifiSetup_MemCopy(key->data, gWifiSetupState.key, sourceLen);
    key->length = WifiSetup_HostToNet16((u16)sourceLen);
    secondLen = sourceLen + 6;
    secondLen = ((secondLen + 1) / 2) * 2;
    key->next = WifiSetup_HostToNet16((u16)secondLen);
    total += secondLen;
    second = (WifiSetupAossItem *)(dst + secondLen);
    second->type = 0x60;
    second->reserved = 0;
    second->next = WifiSetup_HostToNet16(0);
    value = WifiSetup_HostToNet32(0xE);
    WifiSetup_MemCopy(second->data, &value, 4);
    second->length = WifiSetup_HostToNet16(4);
    total += 10;
    return total;
}

static void WifiSetup_WriteBody(BOOL encrypt, WifiSetupAossBody *body, const void *src, s16 *length, s16 *flag, const void *extra) {
    if (encrypt == TRUE) {
        *flag = 1;
        WifiSetup_Encrypt(src, body->encrypted.data, *length, extra, &body->encrypted.seed, gWifiSetupPeerAddress, 8);
        body->encrypted.length = WifiSetup_HostToNet16((u16)*length);
        *length += 4;
    } else {
        WifiSetup_MemCopy(body, src, *length);
    }
}

static void WifiSetup_WritePacketHeader(WifiSetupAossPacket *packet, enum WifiSetupAossPacketKind kind, int length, int flags, s8 checksum, s8 protocol, const u8 *tag) {
    packet->version = WifiSetup_HostToNet16(1);
    packet->unk_02 = 0;
    packet->unk_04 = 0;
    packet->kind = WifiSetup_HostToNet16((u16)kind);
    packet->unk_08 = 0;
    packet->bodyLength = WifiSetup_HostToNet16((u16)length);
    packet->flags = WifiSetup_HostToNet16((u16)flags);
    packet->checksum = checksum;
    packet->protocol = protocol;
    WifiSetup_MemCopy(&packet->tag, tag, sizeof(packet->tag));
}

static void WifiSetup_SendPacket(const WifiSetupAossPacket *packet, int size, int index, int socket) {
    SocAddress address;
    int value;

    WifiSetup_MemFill(&address, 0, sizeof(address));
    address.family = 2;
    address.port = WifiSetup_HostToNet16(WIFI_SETUP_AOSS_PORT);
    value = WifiSetup_HostToNet32(gWifiSetupState.address);
    address.ip = value;
    if (index == 0xFF || ov13_0224CFB8[0x1C] == 0) {
        address.ip = -1;
    }
    WifiSetup_SendTo(socket, packet, size, 0, &address, sizeof(address));
}

static int WifiSetup_Encrypt(void *src, void *dst, int size, u8 *checksum, u16 *seedDst, const u8 *seedSrc, int seedSize) {
    u16 seed;
    WifiSetupCipher state;

    *checksum = WifiSetup_CalcCrc32(src, size);
    state.table = WifiSetup_Alloc(size);
    if (state.table == NULL) {
        return -1;
    }
    seed = WifiSetup_Random();
    WifiSetup_MemCopy(seedDst, &seed, 2);
    WifiSetup_MemCopy(gWifiSetupCipherSeed, seedDst, 2);
    WifiSetup_MemCopy(gWifiSetupCipherKey, seedSrc, seedSize);
    WifiSetup_CipherInit(&state, gWifiSetupCipherSeed, seedSize + 2, size);
    WifiSetup_CipherXor(&state, dst, src, size);
    WifiSetup_Free(state.table);
    return 0;
}

static int WifiSetup_Decrypt(void *dst, const void *src, int size, int expected, u16 *seedDst, const u8 *seedSrc, int seedSize) {
    WifiSetupCipher state;

    state.table = WifiSetup_Alloc(size);
    if (state.table == NULL) {
        WifiSetup_SetError(WIFI_SETUP_AOSS_ERROR_OUT_OF_MEMORY);
        return -1;
    }
    WifiSetup_MemCopy(gWifiSetupCipherSeed, seedDst, 2);
    WifiSetup_MemCopy(gWifiSetupCipherKey, seedSrc, seedSize);
    WifiSetup_CipherInit(&state, gWifiSetupCipherSeed, seedSize + 2, size);
    WifiSetup_CipherXor(&state, src, dst, size);
    {
        int actual = WifiSetup_CalcCrc32(src, size);
        if (actual != expected) {
            WifiSetup_SetError(WIFI_SETUP_AOSS_ERROR_CHECKSUM);
            WifiSetup_Free(state.table);
            return -1;
        }
    }
    WifiSetup_Free(state.table);
    return 0;
}

static void WifiSetup_CipherInit(WifiSetupCipher *state, const u8 *key, u32 keySize, u32 tableSize) {
    u8 *table = state->table;
    u32 i;
    u32 keyIndex;
    u32 value;

    state->y = 0;
    state->x = 0;
    state->size = tableSize;
    for (i = 0; i < tableSize; i++) {
        table[i] = i;
    }
    value = 0;
    keyIndex = 0;
    for (i = 0; i < tableSize; i++) {
        u8 saved = table[i];
        u8 replacement;
        value = (value + key[keyIndex] + saved) % state->size;
        replacement = table[value];
        table[value] = saved;
        table[i] = replacement;
        keyIndex++;
        if (keyIndex >= keySize) {
            keyIndex = 0;
        }
    }
}

static void WifiSetup_CipherXor(WifiSetupCipher *state, u8 *dst, const u8 *src, u32 size) {
    u32 i;

    for (i = 0; i < size; i++) {
        u8 value = ((int (*)(WifiSetupCipher *))WifiSetup_CipherNextByte)(state);
        dst[i] = src[i] ^ value;
    }
}

static u8 WifiSetup_CipherNextByte(WifiSetupCipher *state) {
    u8 *table = state->table;
    u8 x = (state->x + 1) % state->size;
    u8 tx = table[x];
    u8 y = (tx + state->y) % state->size;
    u8 ty = table[y];
    state->x = x;
    state->y = y;
    table[y] = tx;
    table[x] = ty;
    return table[(tx + ty) % state->size];
}

static u8 WifiSetup_CalcCrc32(const void *data, s32 size) {
    return WifiSetup_UpdateCrc32(~0u, data, size, 0, gWifiSetupCrc32Table) ^ ~0u;
}

static u32 WifiSetup_UpdateCrc32(u32 crc, const u8 *data, s32 size, s32 init, u32 *table) {
    s32 i;
    if (init == 0) {
        WifiSetup_InitCrc32Table(init, table);
    }
    for (i = 0; i < size; i++) {
        crc = (crc >> 8) ^ table[(u8)(data[i] ^ crc)];
    }
    return crc;
}

static void WifiSetup_InitCrc32Table(s32 unused, u32 *table) {
    u32 value;
    s32 i, j;
    u32 *entries = table;
    for (i = 0; i < 256; i++) {
        value = i;
        for (j = 0; j < 8; j++) {
            if (value & 1) {
                value = (value >> 1) ^ 0xEDB88320;
            } else {
                value >>= 1;
            }
        }
        entries[i] = value;
    }
}

static s32 WifiSetup_Scramble(void *dst, s32 size, const s8 *key, s32 keySize) {
    s32 i;
    s8 *halfKey = WifiSetup_Alloc(size / 2);
    u8 *swapBuf;
    if (halfKey == NULL) {
        return -1;
    }
    swapBuf = WifiSetup_Alloc(size);
    if (swapBuf == NULL) {
        WifiSetup_Free(halfKey);
        return -1;
    }
    for (i = 0; i < 2; i++) {
        WifiSetup_ScrambleMakeKey(i, halfKey, size, key, keySize);
        WifiSetup_ScrambleXorHalf(halfKey, dst, size);
        WifiSetup_ScrambleSwapHalves(dst, size, swapBuf);
    }
    WifiSetup_Free(halfKey);
    WifiSetup_Free(swapBuf);
    return 0;
}

static void WifiSetup_ScrambleMakeKey(int start, s8 *out, int length, const s8 *key, int keylen) {
    int half = length / 2, pos = start % keylen, i;
    for (i = 0; i < half; i++) {
        out[i] = i;
        out[i] ^= key[pos++];
        if (pos >= keylen) {
            pos = 0;
        }
    }
}

static void WifiSetup_ScrambleXorHalf(s8 *in, u8 *out, int length) {
    int i;
    int half = length / 2;
    for (i = 0; i < half; i++) {
        out[i + half] ^= in[i];
    }
}

static void WifiSetup_ScrambleSwapHalves(u8 *dst, s32 size, u8 *tmp) {
    s32 half = size / 2;
    WifiSetup_MemCopy(tmp, dst + half, half);
    WifiSetup_MemCopy(tmp + half, dst, half);
    WifiSetup_MemCopy(dst, tmp, size);
}
