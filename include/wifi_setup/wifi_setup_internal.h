#ifndef POKEHEARTGOLD_WIFI_SETUP_INTERNAL_H
#define POKEHEARTGOLD_WIFI_SETUP_INTERNAL_H

#include "global.h"

#include "wifi_setup/wifi_setup_wcm.h"

// Access-point setup client: worker thread, access-point scan, packet records, AES key wrap, MD5.

typedef void *(*WifiSetupWorkAllocFunc)(u32 size);
typedef void (*WifiSetupWorkFreeFunc)(void *ptr);

// UDP port of the simple start exchange, as stored in a socket address (port 0xE601 on the network)
#define WIFI_SETUP_SIMPLE_START_PORT 0x1E6

// WifiSetupWork.state, reported to the status callback
enum WifiSetupSimpleStartState {
    WIFI_SETUP_SIMPLE_START_STARTED = 1,
    WIFI_SETUP_SIMPLE_START_SEARCHING,         // no access point picked yet, searching again
    WIFI_SETUP_SIMPLE_START_CONNECTING,        // access point picked
    WIFI_SETUP_SIMPLE_START_EXCHANGING_KEYS,   // version packet received
    WIFI_SETUP_SIMPLE_START_GETTING_SETTINGS,  // settings key received
    WIFI_SETUP_SIMPLE_START_SUCCEEDED,
    WIFI_SETUP_SIMPLE_START_STOPPED,           // failed, or not started
};

// Packet types of the simple start exchange (WifiSetup_BuildPacket / WifiSetup_ReadPacket)
enum WifiSetupSimpleStartPacket {
    WIFI_SETUP_PACKET_VERSION = 1,     // from the access point
    WIFI_SETUP_PACKET_VERSION_REQUEST, // answer, with the client's version records
    WIFI_SETUP_PACKET_KEY,             // from the access point: WIFI_SETUP_RECORD_SETTINGS_KEY
    WIFI_SETUP_PACKET_KEY_REPLY,       // WIFI_SETUP_RECORD_TIMESTAMP_DIGEST
    WIFI_SETUP_PACKET_SETTINGS,        // from the access point: the settings records
    WIFI_SETUP_PACKET_RESULT,          // WIFI_SETUP_RECORD_RESULT
};

// Record types of the simple start packets
enum WifiSetupSimpleStartRecord {
    WIFI_SETUP_RECORD_MAC_ADDRESS = 4,
    WIFI_SETUP_RECORD_EXTENDED = 5, // version packet: >= 1 asks for the MAC address
    WIFI_SETUP_RECORD_SETTINGS_KEY = 0x101,
    WIFI_SETUP_RECORD_TIMESTAMP_DIGEST = 0x102,
    WIFI_SETUP_RECORD_SSID = 0x201,
    WIFI_SETUP_RECORD_SECURITY = 0x202,
    WIFI_SETUP_RECORD_WEP_KEY_0 = 0x206,
    WIFI_SETUP_RECORD_WEP_KEY_1 = 0x207,
    WIFI_SETUP_RECORD_WEP_KEY_2 = 0x208,
    WIFI_SETUP_RECORD_WEP_KEY_3 = 0x209,
    WIFI_SETUP_RECORD_WPA_KEY = 0x20A,
    WIFI_SETUP_RECORD_RESULT = 0x301,
};

// Access point found by the scan (in WifiSetupWork.apList)
typedef struct WifiSetupApInfo {
    u8 unk_00[4];
    u8 bssid[6];
    u16 ssidLength;
    char ssid[32];
    u16 capability; // bit 4: privacy
    u8 unk_2E[0x92];
} WifiSetupApInfo;

// Scan result as compared by WifiSetup_PickSetupAccessPoint
typedef struct WifiSetupApEntry {
    u32 ssidLength;
    char ssid[32];
    u8 unk_24[4];
    u8 bssid[6];
    u16 privacy;
} WifiSetupApEntry;

typedef struct WifiSetupApEntryList {
    u32 count;
    WifiSetupApEntry entries[];
} WifiSetupApEntryList;

typedef struct WifiSetupWork {
    u8 unk_00; // sent as record 0x301
    u8 unk_01[3];
    WifiSetupWorkAllocFunc alloc;
    WifiSetupWcmConfig *wcmConfig;
    WifiSetupWorkFreeFunc free;
    u32 stop; // set to make the worker thread finish
    int packetLength;
    u32 selection; // index of the chosen access point
    int step;      // WifiSetup_RunSession state machine
    u32 connected;
    u32 socketStarted;
    void *connectKey; // key description
    int wcmState;     // see wifi_setup_wcm.h
    void *threadStack;
    u32 recordLength;
    s32 state;     // WIFI_SETUP_SIMPLE_START_*
    void *wcmWork; // WCM_Init work area
    void *buffer;  // aligned start of allocation
    void *searchBssid;
    void *searchSsid;
    void *connectAp;     // access point description
    int extendedRequest; // also send records 4 and 5
    void *allocation;
    int connectOption;
    WifiSetupApInfo *apList; // room for apListCount entries
    int searchOption;
    s32 active;
    int eventWrite; // gWifiSetupLinkEventQueue queue
    int eventRead;
    int apListCount;
    s32 resultReady;
    s32 error;
    void (*statusCallback)(s32 *status); // receives {state, ms left, error}
} WifiSetupWork;

// gWifiSetupConfig
typedef struct WifiSetupConfig {
    u8 *packetBuffer;
    BOOL debug;
    u32 threadStackSize;
    s32 deadline; // ms tick, -1 = none
    volatile u32 count;
} WifiSetupConfig;

typedef struct WifiSetupMd5Context {
    u32 state[4];
    u32 bitsLo;
    u32 bitsHi;
    u8 buffer[64];
} WifiSetupMd5Context;

// Socket address
typedef struct WifiSetupSockAddr {
    u8 len;
    u8 family;
    u16 port;
    u32 addr;
} WifiSetupSockAddr;

// The two MAC addresses (the smaller one first) and "WARP": the seed of the session key
typedef struct WifiSetupMacPair {
    u8 first[6];
    u8 second[6];
    u8 prefix[4];
} WifiSetupMacPair;

// WPA key of the result
typedef struct WifiSetupSettings64 {
    u64 words[8];
} WifiSetupSettings64;

// gWifiSetupClientSettings, followed by the SSID received from the setup access point
typedef struct WifiSetupClientSettings {
    u8 padding_00[20];
    s8 ssid[32];
} WifiSetupClientSettings;

extern WifiSetupWork gWifiSetupWork;
extern WifiSetupConfig gWifiSetupConfig;
extern OSThread gWifiSetupThread;

// result block handed to the caller (WifiSetup_GetSimpleStartResult): the settings received from the
// setup access point
typedef struct WifiSetupResult {
    u8 ssid[32];
    int keyType; // WM_WEPMODE_*, 4-5: WPA
    int unk_24;
    u8 wepKeys[4][32];
    u8 wpaKey[64];
} WifiSetupResult;

extern WifiSetupResult gWifiSetupResult;

extern const u8 sWifiSetupMd5Padding[];
extern char sWifiSetupSetupApSsid[]; // SSID of the setup access point

extern void (*gWifiSetupLinkEventCallback)(u32 event, int arg);
extern u32 gWifiSetupLinkEventQueue[4];
extern OSMutex gWifiSetupLinkMutex;
extern u8 gWifiSetupLinkSearchBssid[6];
extern u8 gWifiSetupLinkSearchSsid[32];

extern char gWifiSetupApSsid[];       // SSID of the chosen access point
extern u8 gWifiSetupApBssid[6];       // BSSID of the chosen access point
extern u8 gWifiSetupOwnMacAddress[6]; // own MAC address
extern u8 sStr_WARP[4];
extern int gWifiSetupExtendedRequest[];
extern u8 gWifiSetupSessionKey[16];
extern u8 gWifiSetupSettingsKey[8];
extern u8 gWifiSetupTimestampDigest[24];
extern u8 gWifiSetupPacketBuffer[2048];
extern u8 gWifiSetupRecordBuffer[2048];
extern WifiSetupClientSettings gWifiSetupClientSettings;
extern u32 gWifiSetupRecvSsid[8];
extern u32 gWifiSetupRecvSecurity[];
extern u8 gWifiSetupRecvWepKeys[][40];
extern u32 gWifiSetupRecvWpaKey[18];
extern u8 ov13_0224E0B0[];
extern u8 gWifiSetupResultWepKeys[];
extern WifiSetupSettings64 gWifiSetupResultWpaKey;

// Connection manager events
int WifiSetupLink_CopyApList(WifiSetupApInfo *dst, int max);
BOOL WifiSetupLink_StartSearch(const u8 *bssid, const u8 *ssid, int len, int option);
int WifiSetupLink_GetState(void);
void *WifiSetupLink_Alloc(int unused, int size);
void WifiSetupLink_Free(int unused, void *ptr, int size);
u32 WifiSetupLink_PopEvent(void);
void WifiSetupLink_PostEvent(u32 event);
int WifiSetupLink_Open(u32 count);
int WifiSetupLink_Close(void);
int WifiSetupLink_ConnectSelectedAp(void);
void WifiSetupLink_DisconnectAp(void);

// Worker thread
int WifiSetup_RunSession(void);

// Setup packets
int WifiSetup_FindSetupAccessPoint(void);
int WifiSetup_SendSetupPacket(int socket, const WifiSetupSockAddr *to, const void *data, int length);
u8 *WifiSetup_FirstRecord(u8 *data, u32 *type, u32 *length);
u32 WifiSetup_BuildPacket(u8 *dest, u32 type, u8 *data, u32 length, const void *key);
u32 WifiSetup_BuildSingleRecordList(u8 *dst, u16 type, const void *src, u32 length);
BOOL WifiSetup_CheckVersionReply(void *data, int *extended);
int WifiSetup_ReadPacket(u8 *data, u32 expectedType, void *dst, const u8 *key);
u32 WifiSetup_BuildVersionRequest(void *dst);
BOOL WifiSetup_BuildMacPair(WifiSetupMacPair *pair, void *unused);
int WifiSetup_ParseSettingsRecords(const u8 *data);
int WifiSetup_StoreSimpleStartResult(void);

// Access point choice
int WifiSetup_PickSetupAccessPoint(const WifiSetupApEntryList *current, const WifiSetupApEntryList *previous, u32 *selected);

// Thread start-up and AES key wrap
void WifiSetup_SimpleStartThread(void *arg);
int WifiSetup_AesKeyWrap(u8 *out, const u8 *in, u32 length, const void *key, u32 keyLength);
int WifiSetup_AesKeyUnwrap(u8 *out, const u8 *in, u32 length, const void *key, u32 keyLength);

// MD5
void WifiSetup_Md5Init(WifiSetupMd5Context *context);
void WifiSetup_Md5Update(WifiSetupMd5Context *context, const u8 *input, u32 len);
void WifiSetup_Md5Final(u8 *digest, WifiSetupMd5Context *context);
void WifiSetup_Md5Transform(WifiSetupMd5Context *context, const u8 *input);

// Byte order helpers
void WifiSetup_EncodeLittleEndian(u8 *dst, const u32 *src, u32 len);
void WifiSetup_DecodeLittleEndian(u32 *dst, const u8 *src, u32 len);
void WifiSetup_CopyBytes(u8 *dst, const u8 *src, u32 len);
void WifiSetup_FillBytes(void *dst, int value, u32 count);
int WifiSetup_FormatHexByte(char *dst, int value);
void WifiSetup_CalcMd5(u8 *digest, const u8 *src, u32 len);
u32 WifiSetup_GetMilliseconds(void);
void *WifiSetup_WorkCalloc(u32 count, u32 size);
void WifiSetup_WorkFree(void *ptr);
int WifiSetup_FormatMacAddress(char *dst, const s8 *mac);
int WifiSetup_StartSimpleStart(u32 priority, u32 count, void (*statusCallback)(s32 *), WifiSetupWorkAllocFunc alloc, WifiSetupWorkFreeFunc free, u32 stackSize);
int WifiSetup_StopSimpleStart(void);
int WifiSetup_GetSimpleStartResult(void *dst);
void WifiSetup_ReportSimpleStartStatus(void);

#endif // POKEHEARTGOLD_WIFI_SETUP_INTERNAL_H
