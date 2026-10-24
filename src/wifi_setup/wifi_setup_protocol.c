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

static int WifiSetup_HandleJoinReply(int state, WifiSetupAossReceived *received, int *counter, WifiSetupAossPacketParams *params);
static int WifiSetup_HandleSettingsReply(int state, WifiSetupAossReceived *received, int *counter, WifiSetupAossPacketParams *params);
static int WifiSetup_HandleDoneReply(int state, void *packet, int *counter, void *context);
static int WifiSetup_DecryptPacket(WifiSetupAossPacket *packet);
static int WifiSetup_CheckPeer(int value, const void *data);
static int WifiSetup_CheckReplySequence(const u8 *expected, u8 *received);
static int WifiSetup_ParseJoinReply(const u8 *src, u8 *dst);
static int WifiSetup_ReadLittleEndian(const u8 *src, int length);
static int WifiSetup_ParseWepRecord(const u8 *src, WifiSetupKeyRecord *dst);
static int WifiSetup_ParseWpaRecord(const u8 *src, WifiSetupWpaKeyRecord *dst);
static int WifiSetup_ParseType70Record(const u8 *src, void *dst);
static int WifiSetup_ParseSecurityRecords(int id, u8 *cursor, int remaining, WifiSetupAossKeyRecords *out, u8 *other);
static int WifiSetup_IsEncryptionRequested(int value);
static int WifiSetup_SendJoinRequest(void *unused, const WifiSetupAossPacketParams *params, int socket);
static int WifiSetup_SendSettingsRequest(void *unused, const WifiSetupAossPacketParams *params, int socket);
static int WifiSetup_SendDoneRequest(void *unused, const WifiSetupAossPacketParams *params, int socket);
static int WifiSetup_BuildJoinPayload(u8 *dst);
static void WifiSetup_WriteBody(int mode, WifiSetupAossBody *body, const void *src, s16 *length, u16 *flag, const void *extra);
static void WifiSetup_WritePacketHeader(WifiSetupAossPacket *packet, int kind, int length, int flags, s8 checksum, s8 protocol, const void *tag);
static void WifiSetup_SendPacket(void *buffer, int size, int index, int socket);
static int WifiSetup_Encrypt(void *src, void *dst, int size, u8 *checksum, void *seedDst, const void *seedSrc, int seedSize);
static int WifiSetup_Decrypt(void *dst, const void *src, int size, int expected, void *seedDst, const void *seedSrc, int seedSize);
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

int WifiSetup_FindAossAccessPoint(WifiSetupAossApList *list) {
    int result = 0;
    int matches = 0;
    int i;
    int count;
    if (list->count == 0) {
        return 5;
    }
    count = list->count;
    if ((u32)count > 64) {
        count = 64;
    }
    for (i = 0; i < count; i++) {
        if (list->entries[i].flags & 1) {
            if (list->entries[i].length == WifiSetup_StrLen(sStr_ESSID_AOSS) && WifiSetup_MemCompare(list->entries[i].data, (const u8 *)sStr_ESSID_AOSS, WifiSetup_StrLen(sStr_ESSID_AOSS)) == 0) {
                matches++;
            }
        }
    }
    if (matches > 1) {
        result = 4;
    }
    if (matches == 0) {
        result = 5;
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

void WifiSetup_InitPacketAddresses(int count, WifiSetupAossPacketParams *params, const void *mac) {
    WifiSetupAossTag *tag = params->tags;
    int i;
    for (i = 0; i < count; i++) {
        WifiSetup_MemCopy(tag->mac, mac, 6);
        tag->sequence = WifiSetup_Random();
        tag->sequence = WifiSetup_HostToNet16(tag->sequence);
        tag++;
    }
}

int WifiSetup_SetStatus(int value) {
    if (value == -1) {
        gWifiSetupSocket.lastStatus = value;
        return 0;
    }
    if (gWifiSetupSocket.lastStatus != value) {
        gWifiSetupSocket.lastStatus = value;
        return WifiSetup_NotifyStatus(value);
    }
    return 0;
}

int WifiSetup_HandlePacket(int state, WifiSetupAossReceived *received, int *counter, WifiSetupAossPacketParams *params, int socket) {
    WifiSetupAossPacket *header = &received->packet;
    int type;

    if (WifiSetup_NetToHost16(header->version) < 1) {
        (*counter)++;
        return state;
    }
    if (header->protocol != 0x11) {
        (*counter)++;
        return state;
    }
    if (WifiSetup_DecryptPacket(&received->packet) > 0) {
        (*counter)++;
        return state;
    }
    type = WifiSetup_NetToHost16(header->kind);
    switch (type) {
    case 0x1010:
        state = WifiSetup_HandleJoinReply(state, received, counter, params);
        break;
    case 0x2010:
        state = WifiSetup_HandleSettingsReply(state, received, counter, params);
        break;
    case 0x3010:
        state = WifiSetup_HandleDoneReply(state, received, counter, params);
        break;
    }
    return state;
}

static int WifiSetup_HandleJoinReply(int state, WifiSetupAossReceived *received, int *counter, WifiSetupAossPacketParams *params) {
    WifiSetupAossPacket *header;
    WifiSetupAossBody *body;
    int value;

    if (state != 0) {
        (*counter)++;
        return state;
    }
    header = &received->packet;
    body = &received->packet.body;
    if (WifiSetup_CheckReplySequence(params->tags[0].mac, header->tag.mac) < 0) {
        (*counter)++;
        return state;
    }
    if (WifiSetup_NetToHost16(body->record.length) == 0) {
        (*counter)++;
        return state;
    }
    if (body->record.type == 7) {
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
        return -1;
    }
    if (body->record.type != 1) {
        (*counter)++;
        return state;
    }
    value = WifiSetup_ParseJoinReply(body->record.data.bytes, gWifiSetupJoinReply);
    if (value < 0) {
        if (value == -2) {
            WifiSetup_SetError(0x16);
            return -1;
        }
        (*counter)++;
        return state;
    }
    gWifiSetupState.encryptBody = WifiSetup_IsEncryptionRequested(WifiSetup_NetToHost16(header->flags));
    *counter = 0;
    return 1;
}

static int WifiSetup_HandleSettingsReply(int state, WifiSetupAossReceived *received, int *counter, WifiSetupAossPacketParams *params) {
    WifiSetupAossPacket *header;
    WifiSetupAossBody *body;
    int value;

    if (state != 1) {
        (*counter)++;
        return state;
    }
    header = &received->packet;
    body = &received->packet.body;
    if (WifiSetup_CheckReplySequence(params->tags[1].mac, header->tag.mac) < 0) {
        (*counter)++;
        return state;
    }
    if (WifiSetup_NetToHost16(body->record.length) == 0) {
        (*counter)++;
        return state;
    }
    if (body->record.type == 7) {
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
        return -1;
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
    return 2;
}

static int WifiSetup_HandleDoneReply(int state, void *packet, int *counter, void *context) {
    u8 *body;
    int value;

    if (state != 2) {
        (*counter)++;
        return state;
    }
    body = (u8 *)packet + 0x24;
    context = (u8 *)context + 0x10;
    packet = (u8 *)packet + 0xC;
    if (WifiSetup_CheckReplySequence(context, (u8 *)packet + 0x10) < 0) {
        (*counter)++;
        return state;
    }
    if (body[0] != 7) {
        (*counter)++;
        return state;
    }
    if (WifiSetup_NetToHost16(U16_AT(body, 2)) == 0) {
        (*counter)++;
        return state;
    }
    value = WifiSetup_NetToHost32(U32_AT(body, 4));
    if (value == 0) {
        return 100;
    }
    value = WifiSetup_NetToHost32(U32_AT(body, 4));
    if (value == -2) {
        WifiSetup_SetError(0x14);
        return -1;
    }
    value = WifiSetup_NetToHost32(U32_AT(body, 4));
    if (value == -3) {
        WifiSetup_SetError(0x15);
        return -1;
    }
    WifiSetup_SetError(0x18);
    return -1;
}

static int WifiSetup_DecryptPacket(WifiSetupAossPacket *packet) {
    u8 address[8];
    WifiSetupAossEncryptedBody *body = &packet->body.encrypted;
    int result;
    WifiSetup_MemCopy(address, &packet->tag, 8);
    result = WifiSetup_Scramble(address, 8, sStr_MELCO, WifiSetup_StrLen(sStr_MELCO));
    if (result == -1) {
        WifiSetup_SetError(2);
        return -100;
    }
    result = WifiSetup_CheckPeer(WifiSetup_NetToHost16(packet->kind), address);
    if (result == 0) {
        int size;
        void *buffer;
        if (WifiSetup_NetToHost16(packet->kind) == 4096) {
            WifiSetup_MemCopy(gWifiSetupPeerAddress, address, 8);
        }
        if ((WifiSetup_NetToHost16(packet->flags) & 15) == 0) {
            return 0;
        }
        size = WifiSetup_NetToHost16(body->length);
        buffer = WifiSetup_Alloc(size);
        if (buffer == 0) {
            WifiSetup_SetError(2);
            return 100;
        }
        if (WifiSetup_Decrypt(body->data, buffer, size, packet->checksum, &body->seed, gWifiSetupPeerAddress, 8) < 0) {
            WifiSetup_Free(buffer);
            if (WifiSetup_GetError() == 2) {
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

static int WifiSetup_CheckPeer(int value, const void *data) {
    int i;
    int present;
    int result;
    result = 0;
    present = result;
    for (i = 0; i < 6; i++) {
        if (gWifiSetupPeerAddress[i] != 0) {
            present = 1;
            break;
        }
    }
    if (present) {
        if (WifiSetup_MemCompare(gWifiSetupPeerAddress, data, 6) != 0) {
            result = 1;
        }
    } else if (value != 0x1000) {
        result = 2;
    }
    return result;
}

static int WifiSetup_CheckReplySequence(const u8 *expected, u8 *received) {
    int result = 0;
    WifiSetup_Scramble(received, 8, sStr_MELCO, WifiSetup_StrLen(sStr_MELCO));
    if (WifiSetup_MemCompare(expected, received, 6) != 0) {
        result = -1;
    } else {
        int expectedSequence = WifiSetup_NetToHost16(*(u16 *)(expected + 6));
        int receivedSequence = WifiSetup_NetToHost16(*(u16 *)(received + 6));
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
            // called through an int-returning type: with the u16 return type the "<= 0" test becomes "== 0"
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
    u8 *text = dst->text;
    u8 *key3 = dst->fields[3];
    u8 *key2 = dst->fields[2];
    u8 *key1 = dst->fields[1];
    u8 *key0 = dst->fields[0];
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
            WifiSetup_MemCopy(text, entry->data, length);
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
    u8 *text = dst->text;
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
            WifiSetup_MemCopy(text, entry->data, length);
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

static int WifiSetup_ParseType70Record(const u8 *src, void *dst) {
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
            flags |= 1;
            break;
        case 4:
            result = WifiSetup_ParseWepRecord(cursor, &records->wep128);
            flags |= 2;
            break;
        case 5:
            result = WifiSetup_ParseWpaRecord(cursor, &records->wpaTkip);
            flags |= 4;
            break;
        case 6:
            result = WifiSetup_ParseWpaRecord(cursor, &records->wpaAes);
            flags |= 8;
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

static int WifiSetup_IsEncryptionRequested(int value) {
    int result = 0;
    if (value & 0x10) {
        result = 1;
    }
    return result;
}

int WifiSetup_SendRequest(int which, void *unused, WifiSetupAossPacketParams *params, int socket) {
    switch (which) {
    case 0:
        WifiSetup_SetStatus(2);
        return WifiSetup_SendJoinRequest(unused, params, socket);
    case 1:
        WifiSetup_SetStatus(3);
        return WifiSetup_SendSettingsRequest(unused, params, socket);
    case 2:
        WifiSetup_SetStatus(5);
        return WifiSetup_SendDoneRequest(unused, params, socket);
    default:
        return -1;
    }
}

static int WifiSetup_SendJoinRequest(void *unused, const WifiSetupAossPacketParams *params, int socket) {
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
    packet = gWifiSetupState.data;
    WifiSetup_MemFill(packet, 0, sizeof(WifiSetupAossPacket));
    payload = WifiSetup_Alloc(0x210);
    if (payload == NULL) {
        WifiSetup_SetError(2);
        return -1;
    }
    WifiSetup_MemFill(payload, 0, 0x210);
    body = &packet->body;
    WifiSetup_MemCopy(gWifiSetupPeerAddress, &params->tags[0], 8);
    WifiSetup_MemCopy(data, gWifiSetupPeerAddress, 8);
    header.length = WifiSetup_BuildJoinPayload(payload + 4);
    if (header.length < 0) {
        WifiSetup_SetError(3);
        if (payload != NULL) {
            WifiSetup_Free(payload);
        }
        return -1;
    }
    payload[0] = 0;
    *(u16 *)(payload + 2) = WifiSetup_HostToNet16((u16)header.length);
    header.length += 4;
    WifiSetup_WriteBody(0, body, payload, &header.length, (u16 *)&header.flag, &header);
    header.flag |= 0x10;
    if (WifiSetup_Scramble(data, 8, sStr_MELCO, 6) != 0) {
        WifiSetup_SetError(2);
        if (payload != NULL) {
            WifiSetup_Free(payload);
        }
        return -1;
    }
    WifiSetup_WritePacketHeader(packet, 1 << 12, header.length, header.flag, header.value, 0x11, data);
    header.length += 0x18;
    WifiSetup_SendPacket(packet, header.length, 0xFF, socket);
    if (payload != NULL) {
        WifiSetup_Free(payload);
    }
    return 0;
}

static int WifiSetup_SendSettingsRequest(void *unused, const WifiSetupAossPacketParams *params, int socket) {
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
    packet = gWifiSetupState.data;
    WifiSetup_MemFill(&record, 0, sizeof(WifiSetupAossRecord));
    WifiSetup_MemFill(packet, 0, sizeof(WifiSetupAossPacket));
    record.type = 2;
    record.reserved = 0;
    record.length = WifiSetup_HostToNet16(4);
    record.data.status = gWifiSetupState.requestedMask;
    record.data.status = WifiSetup_HostToNet32(record.data.status);
    header.length = 8;
    WifiSetup_WriteBody(gWifiSetupState.encryptBody, &packet->body, &record, &header.length, (u16 *)&header.flag, &header);
    WifiSetup_MemCopy(data, &params->tags[1], 8);
    size = WifiSetup_Scramble(data, 8, sStr_MELCO, 6);
    if (size != 0) {
        WifiSetup_SetError(2);
        return -1;
    }
    WifiSetup_WritePacketHeader(packet, 2 << 12, header.length, header.flag, header.value, 0x11, data);
    header.length += 0x18;
    WifiSetup_SendPacket(packet, header.length, 0, socket);
    return 0;
}

static int WifiSetup_SendDoneRequest(void *unused, const WifiSetupAossPacketParams *params, int socket) {
    u8 data[8];
    WifiSetupAossPacket *packet = gWifiSetupState.data;
    int size;

    WifiSetup_MemFill(packet, 0, sizeof(WifiSetupAossPacket));
    WifiSetup_MemCopy(data, &params->tags[2], 8);
    size = WifiSetup_StrLen(sStr_MELCO);
    WifiSetup_Scramble(data, 8, sStr_MELCO, size);
    WifiSetup_WritePacketHeader(packet, 3 << 12, 0, 0, 0, 0x11, data);
    WifiSetup_SendPacket(packet, 0x18, 0, socket);
    return 0;
}

static int WifiSetup_BuildJoinPayload(u8 *dst) {
    s16 sourceLen;
    s16 secondLen;
    s16 total = 0;
    u8 *second;
    u32 value;

    dst[0] = ov13_0224CFB8[0x1D];
    dst[1] = 1;
    sourceLen = (s16)gWifiSetupState.keyLength;
    WifiSetup_MemCopy(dst + 6, gWifiSetupState.key, sourceLen);
    *(u16 *)(dst + 2) = WifiSetup_HostToNet16((u16)sourceLen);
    secondLen = (s16)(sourceLen + 6);
    secondLen = (s16)(((secondLen + 1) / 2) * 2);
    *(u16 *)(dst + 4) = WifiSetup_HostToNet16((u16)secondLen);
    total += secondLen;
    second = dst + secondLen;
    dst[secondLen] = 0x60;
    second[1] = 0;
    *(u16 *)(second + 4) = WifiSetup_HostToNet16(0);
    value = WifiSetup_HostToNet32(0xE);
    WifiSetup_MemCopy(second + 6, &value, 4);
    *(u16 *)(second + 2) = WifiSetup_HostToNet16(4);
    total += 10;
    return total;
}

static void WifiSetup_WriteBody(int mode, WifiSetupAossBody *body, const void *src, s16 *length, u16 *flag, const void *extra) {
    if (mode == 1) {
        *flag = 1;
        WifiSetup_Encrypt(src, body->encrypted.data, *length, extra, &body->encrypted.seed, gWifiSetupPeerAddress, 8);
        body->encrypted.length = WifiSetup_HostToNet16((u16)*length);
        *length += 4;
    } else {
        WifiSetup_MemCopy(body, src, *length);
    }
}

static void WifiSetup_WritePacketHeader(WifiSetupAossPacket *packet, int kind, int length, int flags, s8 checksum, s8 protocol, const void *tag) {
    packet->version = WifiSetup_HostToNet16(1);
    packet->unk_02 = 0;
    packet->unk_04 = 0;
    packet->kind = WifiSetup_HostToNet16((u16)kind);
    packet->unk_08 = 0;
    packet->bodyLength = WifiSetup_HostToNet16((u16)length);
    packet->flags = WifiSetup_HostToNet16((u16)flags);
    packet->checksum = checksum;
    packet->protocol = protocol;
    WifiSetup_MemCopy(&packet->tag, tag, 8);
}

static void WifiSetup_SendPacket(void *buffer, int size, int index, int socket) {
    SocAddress address;
    int value;

    WifiSetup_MemFill(&address, 0, sizeof(address));
    address.family = 2;
    address.port = WifiSetup_HostToNet16(0x5790);
    value = WifiSetup_HostToNet32(gWifiSetupState.address);
    address.ip = value;
    if (index == 0xFF || ov13_0224CFB8[0x1C] == 0) {
        address.ip = -1;
    }
    WifiSetup_SendTo(socket, buffer, size, 0, &address, sizeof(address));
}

static int WifiSetup_Encrypt(void *src, void *dst, int size, u8 *checksum, void *seedDst, const void *seedSrc, int seedSize) {
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

static int WifiSetup_Decrypt(void *dst, const void *src, int size, int expected, void *seedDst, const void *seedSrc, int seedSize) {
    WifiSetupCipher state;

    state.table = WifiSetup_Alloc(size);
    if (state.table == NULL) {
        WifiSetup_SetError(2);
        return -1;
    }
    WifiSetup_MemCopy(gWifiSetupCipherSeed, seedDst, 2);
    WifiSetup_MemCopy(gWifiSetupCipherKey, seedSrc, seedSize);
    WifiSetup_CipherInit(&state, gWifiSetupCipherSeed, seedSize + 2, size);
    WifiSetup_CipherXor(&state, src, dst, size);
    {
        int actual = WifiSetup_CalcCrc32(src, size);
        if (actual != expected) {
            WifiSetup_SetError(0x12);
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
        // called through an int-returning type: the u8 return type adds a truncation here
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
