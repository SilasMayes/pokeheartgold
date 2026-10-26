#ifndef POKEHEARTGOLD_WIFI_SETUP_WCM_H
#define POKEHEARTGOLD_WIFI_SETUP_WCM_H

#include "global.h"

// Wireless connection manager (WCM_*) wrapper of the access-point setup client.

// wrapper states (gWifiSetupWcm.state)
#define WIFI_SETUP_WCM_STATE_NONE            0
#define WIFI_SETUP_WCM_STATE_READY           1 // WCM_Init done
#define WIFI_SETUP_WCM_STATE_CLEANUP         2
#define WIFI_SETUP_WCM_STATE_IDLE            3
#define WIFI_SETUP_WCM_STATE_BUSY            4 // starting up, ending a search or disconnecting
#define WIFI_SETUP_WCM_STATE_SEARCHING       5
#define WIFI_SETUP_WCM_STATE_SEARCH_STARTING 6
#define WIFI_SETUP_WCM_STATE_CONNECTED       7
#define WIFI_SETUP_WCM_STATE_CONNECTING      8

// events passed to the wrapper's callback
#define WIFI_SETUP_WCM_EVENT_UNKNOWN           1
#define WIFI_SETUP_WCM_EVENT_FAILED            2 // a request could not be started
#define WIFI_SETUP_WCM_EVENT_FOUND_AP          5
#define WIFI_SETUP_WCM_EVENT_STARTED           6
#define WIFI_SETUP_WCM_EVENT_SEARCH_STARTED    8
#define WIFI_SETUP_WCM_EVENT_SEARCH_FAILED     9
#define WIFI_SETUP_WCM_EVENT_SEARCH_ENDED      10
#define WIFI_SETUP_WCM_EVENT_SEARCH_END_FAILED 11
#define WIFI_SETUP_WCM_EVENT_CONNECTED         12
#define WIFI_SETUP_WCM_EVENT_CONNECT_FAILED    13
#define WIFI_SETUP_WCM_EVENT_DISCONNECTED      14
#define WIFI_SETUP_WCM_EVENT_DISCONNECT_FAILED 15
#define WIFI_SETUP_WCM_EVENT_CONNECT_TIMEOUT   18 // sent by the access point connection's timeout alarm
#define WIFI_SETUP_WCM_EVENT_SEARCH_TIMEOUT    19 // sent by the access point search's timeout alarm
#define WIFI_SETUP_WCM_EVENT_CLEANED_UP        20

// Event passed to the WCM callback
typedef struct WifiSetupWcmEvent {
    s16 type;
    s16 result;
} WifiSetupWcmEvent;

// Start-up parameters handed to WCM_StartupAsync
typedef struct WifiSetupWcmConfig {
    u32 dmaNo;    // always 3
    void *buffer; // rest of the caller's allocation
    u32 bufferSize;
    u32 apListMode; // always 0
} WifiSetupWcmConfig;

typedef struct WifiSetupWcm {
    void *wcmWork; // WCM_Init work area
    int searchOption;
    WifiSetupWcmConfig *config;
    int connectOption;
    u8 *searchBssid;
    u8 *searchSsid;
    int state;
    void (*callback)(int event, int arg);
    void *connectAp;  // access point description
    void *connectKey; // key description
} WifiSetupWcm;

extern WifiSetupWcm gWifiSetupWcm;
extern u8 gWifiSetupWcmSearchBssid[6];
extern u8 gWifiSetupWcmSearchSsid[32];
extern u8 WCM_Bssid_Any[]; // BSSID ff:ff:ff:ff:ff:ff (any)
extern u8 WCM_Essid_Any[]; // SSID of 0xFF bytes (any)

void WifiSetup_Sleep(s32 ticks);

int WCM_Init(void *work, u32 size);
int WCM_StartupAsync(WifiSetupWcmConfig *config, void (*callback)(WifiSetupWcmEvent *event));
int WCM_CleanupAsync(void);
void WCM_Finish(void);
int WCM_SearchAsync(void *bssid, void *ssid, int option);
int WCM_ConnectAsync(void *ap, void *key, int option);
int WCM_DisconnectAsync(void);
int WCM_LockApList(int lock);
int WCM_CountApList(void);
void *WCM_PointApList(u16 index);
s32 WifiSetup_NotifyStatus(s32 arg);
BOOL WifiSetupWcm_StartCleanup(void);
BOOL WifiSetupWcm_StartDisconnect(void);
BOOL WifiSetupWcm_StopSearch(void);
int WifiSetupWcm_CopyApList(u8 *dst, int max);
BOOL WifiSetupWcm_Init(void (*callback)(int event, int arg), void *allocation, u32 size);
BOOL WifiSetupWcm_StartSearch(const u8 *bssid, const u8 *ssid, int len, int option);
BOOL WifiSetupWcm_StartConnect(void *ap, void *key, int option);

#endif // POKEHEARTGOLD_WIFI_SETUP_WCM_H
