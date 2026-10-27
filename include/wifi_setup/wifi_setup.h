#ifndef POKEHEARTGOLD_WIFI_SETUP_H
#define POKEHEARTGOLD_WIFI_SETUP_H

#include "global.h"

#include "nitrowifi/socl_internal.h"

// Access-point setup client: scans for the access point, exchanges UDP packets with it on the local network and
// reads the connection settings it hands out.

// UDP port and addresses of the AOSS exchange on the access point's network
#define WIFI_SETUP_AOSS_PORT         0x5790
#define WIFI_SETUP_AOSS_AP_ADDRESS   0xC0A80B01 // 192.168.11.1
#define WIFI_SETUP_AOSS_HOST_ADDRESS 0xC0A80B65 // 192.168.11.101

// Protocol number in the header of every AOSS packet
#define WIFI_SETUP_AOSS_PROTOCOL 0x11

// Settings of WifiSetupRequest.requestMask and WifiSetupState.requestedMask / receivedMask
#define WIFI_SETUP_AOSS_SETTING_WEP64    (1 << 0)
#define WIFI_SETUP_AOSS_SETTING_WEP128   (1 << 1)
#define WIFI_SETUP_AOSS_SETTING_WPA_TKIP (1 << 2)
#define WIFI_SETUP_AOSS_SETTING_WPA_AES  (1 << 3)

// Steps of the exchange: the request sent next (WifiSetup_SendRequest) and the reply it waits for
// (WifiSetup_HandlePacket)
enum WifiSetupAossStep {
    WIFI_SETUP_AOSS_STEP_FAILED = -1,
    WIFI_SETUP_AOSS_STEP_JOIN = 0,
    WIFI_SETUP_AOSS_STEP_SETTINGS,
    WIFI_SETUP_AOSS_STEP_DONE,
    WIFI_SETUP_AOSS_STEP_FINISHED = 100,
};

// Packet kinds: the requests and the access point's replies to them
enum WifiSetupAossPacketKind {
    WIFI_SETUP_AOSS_KIND_JOIN = 0x1000,
    WIFI_SETUP_AOSS_KIND_JOIN_REPLY = 0x1010,
    WIFI_SETUP_AOSS_KIND_SETTINGS = 0x2000,
    WIFI_SETUP_AOSS_KIND_SETTINGS_REPLY = 0x2010,
    WIFI_SETUP_AOSS_KIND_DONE = 0x3000,
    WIFI_SETUP_AOSS_KIND_DONE_REPLY = 0x3010,
};

// Record types of a packet body
enum WifiSetupAossRecordType {
    WIFI_SETUP_AOSS_RECORD_JOIN = 1,
    WIFI_SETUP_AOSS_RECORD_SETTINGS = 2,
    WIFI_SETUP_AOSS_RECORD_STATUS = 7,
};

// Progress reported through WifiSetup_SetStatus
enum WifiSetupAossStatus {
    WIFI_SETUP_AOSS_STATUS_RESET = -1,
    WIFI_SETUP_AOSS_STATUS_SEARCHING = 0,
    WIFI_SETUP_AOSS_STATUS_CONNECTING,
    WIFI_SETUP_AOSS_STATUS_JOINING,
    WIFI_SETUP_AOSS_STATUS_GETTING_SETTINGS,
    WIFI_SETUP_AOSS_STATUS_RECONNECTING,
    WIFI_SETUP_AOSS_STATUS_FINISHING,
};

// Results of WifiSetup_FindAossAccessPoint
enum WifiSetupAossScanResult {
    WIFI_SETUP_AOSS_SCAN_FOUND = 0,
    WIFI_SETUP_AOSS_SCAN_SEVERAL = 4,
    WIFI_SETUP_AOSS_SCAN_NONE = 5,
};

// Errors recorded with WifiSetup_SetError; a request that cannot be sent records
// WIFI_SETUP_AOSS_ERROR_SEND + its step
enum WifiSetupAossError {
    WIFI_SETUP_AOSS_ERROR_UNKNOWN = 1,
    WIFI_SETUP_AOSS_ERROR_OUT_OF_MEMORY = 2,
    WIFI_SETUP_AOSS_ERROR_JOIN_PAYLOAD = 3,
    WIFI_SETUP_AOSS_ERROR_SOCKET_OPTION = 11,
    WIFI_SETUP_AOSS_ERROR_SOCKET_STARTUP = 12,
    WIFI_SETUP_AOSS_ERROR_JOIN_TIMEOUT = 15,
    WIFI_SETUP_AOSS_ERROR_SETTINGS_TIMEOUT = 16,
    WIFI_SETUP_AOSS_ERROR_DONE_TIMEOUT = 17,
    WIFI_SETUP_AOSS_ERROR_CHECKSUM = 18,
    WIFI_SETUP_AOSS_ERROR_WEP64_NOT_REQUESTED = 19,
    WIFI_SETUP_AOSS_ERROR_SEND = 0x1000,
};

// WifiSetupRequest.error
enum WifiSetupAossRequestError {
    WIFI_SETUP_AOSS_REQUEST_OK = 0,
    WIFI_SETUP_AOSS_REQUEST_NOT_FOUND = 1,
    WIFI_SETUP_AOSS_REQUEST_SEVERAL_FOUND = 2,
    WIFI_SETUP_AOSS_REQUEST_JOIN_TIMEOUT = 3,
    WIFI_SETUP_AOSS_REQUEST_SETTINGS_TIMEOUT = 4,
    WIFI_SETUP_AOSS_REQUEST_DONE_TIMEOUT = 5,
    WIFI_SETUP_AOSS_REQUEST_STORE_FAILED = 6,
    WIFI_SETUP_AOSS_REQUEST_FAILED = 15,
};

typedef void *(*WifiSetupAllocFunc)(u32 size);
typedef void (*WifiSetupFreeFunc)(void *ptr);

typedef struct WifiSetupRuntime {
    WifiSetupAllocFunc alloc;
    s32 (*callback)(s32 event); // see WifiSetup_NotifyStatus
    void *allocation;           // wireless work buffer
    WifiSetupFreeFunc free;
} WifiSetupRuntime;

// The setup key sent with a request.
typedef struct WifiSetupRequestKey {
    u8 tag;
    u8 unused;
    u16 length; // including the terminator
    u8 data[256];
} WifiSetupRequestKey;

// Settings received by the AOSS client: the keys and the SSID of each security mode
typedef struct WifiSetupAossResult {
    u8 wep64Keys[4][6];
    u8 wep64Ssid[33];
    u8 wep128Keys[4][14];
    u8 wep128Ssid[33];
    u8 wpaTkipKey[64];
    u8 wpaTkipSsid[33];
    u8 wpaAesKey[64];
    u8 wpaAesSsid[33];
} WifiSetupAossResult;

// Request/result block passed in by the caller of WifiSetup_RunAoss.
typedef struct WifiSetupRequest {
    u16 requestMask; // which settings to fetch
    WifiSetupRequestKey key;
    s16 connectRetries; // -1 = default
    s16 connectDelay;
    s16 receiveRetries;
    s16 receiveDelay;
    s16 receiveTimeout;
    u8 macAddress[6];
    u8 error;
    WifiSetupAossResult result;
} WifiSetupRequest;

typedef struct WifiSetupCipher {
    u32 x;
    u32 y;
    u8 *table;
    u32 size;
} WifiSetupCipher;

// Access point the AOSS exchange runs on (see WifiSetup_InitAossConnectInfo)
typedef struct WifiSetupAossConnectInfo {
    u32 ssidLength;
    u8 ssid[32];
    int mode;
    u32 keyLength;
    u8 key[16];
} WifiSetupAossConnectInfo;

// Address and sequence number carried, scrambled, in each AOSS packet
typedef struct WifiSetupAossTag {
    u8 mac[6];
    u16 sequence;
} WifiSetupAossTag;

// Addresses of the session, handed to WifiSetup_SendRequest
typedef struct WifiSetupAossAddresses {
    u32 ip;
    u8 padding_04[12];
    u32 gateway;
} WifiSetupAossAddresses;

// Tags of the join, settings and done requests
typedef struct WifiSetupAossPacketParams {
    WifiSetupAossTag tags[3];
} WifiSetupAossPacketParams;

// One record of a packet body: type, length of the data, data
typedef struct WifiSetupAossRecord {
    u8 type;
    u8 reserved;
    u16 length;
    union {
        u32 status;
        u8 bytes[1];
    } data;
} WifiSetupAossRecord;

typedef struct WifiSetupAossEncryptedBody {
    u16 length;
    u16 seed;
    u8 data[1];
} WifiSetupAossEncryptedBody;

typedef union WifiSetupAossBody {
    WifiSetupAossRecord record;
    WifiSetupAossEncryptedBody encrypted;
    u8 bytes[1476];
} WifiSetupAossBody;

// Packet header (see WifiSetup_WritePacketHeader) followed by the body
typedef struct WifiSetupAossPacket {
    u16 version;
    u16 unk_02;
    u16 unk_04;
    u16 kind;
    u16 unk_08;
    u16 bodyLength;
    u16 flags;
    u8 checksum;
    u8 protocol;
    WifiSetupAossTag tag;
    WifiSetupAossBody body;
} WifiSetupAossPacket;

// Packet received from the access point
typedef struct WifiSetupAossReceived {
    int socket;
    int length;
    u8 padding_08[4];
    WifiSetupAossPacket packet;
} WifiSetupAossReceived;

// Packet buffer of the client (gWifiSetupState.data): the request being sent or the packet received
#define WIFI_SETUP_AOSS_BUFFER_SIZE 1528

typedef union WifiSetupAossBuffer {
    WifiSetupAossPacket send;
    WifiSetupAossReceived received;
} WifiSetupAossBuffer;

// WEP keys received from the setup access point: the key length and the four keys
typedef struct WifiSetupKeyRecord {
    u32 unused;
    int length;
    u8 ssid[40];
    u8 keys[4][64];
} WifiSetupKeyRecord;

// WPA key received from the setup access point
typedef struct WifiSetupWpaKeyRecord {
    u32 unused;
    int length;
    u8 ssid[40];
    u8 key[64];
} WifiSetupWpaKeyRecord;

// Keys of every security mode received in the settings reply
typedef struct WifiSetupAossKeyRecords {
    u8 padding_00[8];
    WifiSetupKeyRecord wep64;
    WifiSetupKeyRecord wep128;
    WifiSetupWpaKeyRecord wpaTkip;
    WifiSetupWpaKeyRecord wpaAes;
    u8 padding_348[8];
} WifiSetupAossKeyRecords;

// Access point found by the AOSS scan (see WifiSetup_SearchAccessPoints)
typedef struct WifiSetupAossApEntry {
    u32 ssidLength;
    u8 ssid[32];
    u32 channel;
    u8 unk_28[8];
    u8 mac[6];
    u8 unk_36[2];
    int rateCount;
    u8 rates[16];
    int beaconPeriod;
    int mode;
} WifiSetupAossApEntry;

typedef struct WifiSetupAossApList {
    u32 count;
    WifiSetupAossApEntry entries[64];
} WifiSetupAossApList;

// Result of WifiSetup_ConnectAccessPoint
typedef struct WifiSetupAossConnectResult {
    u32 connected;
    WifiSetupAossApEntry accessPoint;
} WifiSetupAossConnectResult;

typedef struct WifiSetupPollTime {
    int seconds;
    int microseconds;
} WifiSetupPollTime;

// The UDP socket of the AOSS exchange and the socket library configuration it is started with
typedef struct WifiSetupSocketState {
    int socket;     // -1 while closed
    enum WifiSetupAossStatus lastStatus; // last status reported by WifiSetup_SetStatus, WIFI_SETUP_AOSS_STATUS_RESET for none
    SocConfig config;
} WifiSetupSocketState;

typedef struct WifiSetupState {
    int encryptBody;
    WifiSetupAossApList *connection; // access points found by the last search
    BOOL randomSeeded;
    WifiSetupAossConnectResult *connectResult;
    int error;
    WifiSetupAossBuffer *data;
    u32 randomState;
    u32 randomMultiplier;
    u32 randomIncrement;
    u8 *key;
    int keyLength;
    u32 requestedMask; // settings the caller asked for
    u32 receivedMask;  // settings received so far
    u32 address;
    u32 netmask;
} WifiSetupState;

extern WifiSetupState gWifiSetupState;
extern WifiSetupAossApList *ov13_0224CF9C;
extern s8 ov13_0224CFB8[];
extern u8 ov13_0224CFBC[];
extern u8 gWifiSetupPeerAddress[8];
extern WifiSetupSocketState gWifiSetupSocket;
extern WifiSetupAossKeyRecords gWifiSetupSecurityRecords[2];
extern WifiSetupRuntime gWifiSetupRuntime;
extern WifiSetupFreeFunc gWifiSetupFreeHook;
extern OSMessage gWifiSetupMessages[4];
extern OSMessageQueue gWifiSetupMessageQueue;
extern u32 gWifiSetupCrc32Table[256];
extern char sStr_ESSID_AOSS[];
extern char sStr_MELCO[];
extern u8 gWifiSetupJoinReply[];
extern u8 sWifiSetupSecurityRecordTypes[];
extern u8 gWifiSetupCipherSeed[];
extern u8 gWifiSetupCipherKey[];

void *WifiSetup_Alloc(int size);
void WifiSetup_Free(void *ptr);
int WifiSetup_RunAoss(WifiSetupRequest *request);
int WifiSetup_RunAossSession(WifiSetupRequest *request);
int WifiSetup_StoreAossResult(WifiSetupRequest *);
u32 WifiSetup_NextHostAddress(u32 value, u32 mask);
void WifiSetup_FreeWorkBuffers(void);
void WifiSetup_InitState(WifiSetupRequest *request);
void WifiSetup_SetError(int error);
int WifiSetup_GetError(void);
int WifiSetup_SetStatus(enum WifiSetupAossStatus status);
void *WifiSetup_SocketAlloc(s32 unused, s32 size);
void *WifiSetup_SocketFree(s32 unused, s32 ptr);
int WifiSetup_StartupSocket(u32 address, u32 netmask, u32 gateway);
int WifiSetup_CleanupSocket(void);
int WifiSetup_MemCompare(const u8 *lhs, const u8 *rhs, int size);
void WifiSetup_MemCopy(void *dst, const void *src, u32 size);
void WifiSetup_MemFill(void *dst, int value, u32 size);
int WifiSetup_RecvFrom(int socket, void *buffer, int size, int flags, SocAddress *address, int *addressLength);
int WifiSetup_Poll(int count, SocPollFd *readSet, void *writeSet, void *exceptSet, WifiSetupPollTime *timeout);
int WifiSetup_SendTo(int socket, const void *buffer, int size, int flags, SocAddress *address, int addressLength);
int WifiSetup_SetSockOpt(int socket, int level, int name, const void *value, int length);
int WifiSetup_Socket(int domain, int type, int protocol);
int WifiSetup_Bind(int socket, SocAddress *address, int addressLength);
int WifiSetup_Close(int socket);
u32 WifiSetup_HostToNet32(u32 x);
u16 WifiSetup_HostToNet16(int x);
u32 WifiSetup_NetToHost32(u32 x);
u16 WifiSetup_NetToHost16(int x);
s32 WifiSetup_StrLen(const char *str);
u16 WifiSetup_Random(void);
void WifiSetup_ClearPollSet(SocPollFd *set);
void WifiSetup_AddToPollSet(int socket, SocPollFd *set);
void WifiSetup_CopyConnectSsid(const WifiSetupAossConnectInfo *src, void *dst);
void WifiSetup_StoreConnectResult(WifiSetupAossConnectResult *dst, const void *src, u32 value);
void WifiSetup_OnTimeoutAlarm(void *message);
int WifiSetup_Startup(WifiSetupAllocFunc alloc, WifiSetupFreeFunc free);
int WifiSetup_Cleanup(void);
int WifiSetup_SearchAccessPoints(WifiSetupAossApList **output);
int WifiSetup_ConnectAccessPoint(WifiSetupAossConnectInfo *param, WifiSetupAossConnectResult *out);
int WifiSetup_CheckPrintable(const u8 *data, int length);
enum WifiSetupAossScanResult WifiSetup_FindAossAccessPoint(WifiSetupAossApList *list);
int WifiSetup_InitAossConnectInfo(WifiSetupAossConnectInfo *info);
void WifiSetup_InitPacketAddresses(int count, WifiSetupAossPacketParams *params, const u8 *mac);
enum WifiSetupAossStep WifiSetup_HandlePacket(enum WifiSetupAossStep state, WifiSetupAossReceived *received, int *counter, WifiSetupAossPacketParams *params, int socket);
int WifiSetup_SendRequest(enum WifiSetupAossStep step, const WifiSetupAossAddresses *addresses, WifiSetupAossPacketParams *params, int socket);

#endif // POKEHEARTGOLD_WIFI_SETUP_H
