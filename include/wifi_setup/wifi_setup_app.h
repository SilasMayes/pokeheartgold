#ifndef POKEHEARTGOLD_WIFI_SETUP_APP_H
#define POKEHEARTGOLD_WIFI_SETUP_APP_H

#include "wifi_setup/wifi_setup_share.h"
#include "wifi_setup/wifi_setup_ui.h"

struct WifiSetupRequest;

// Access-point setup screens, application core: the entry point the game calls, the per-frame main loop, the setup
// client request, the text banks and the session started from the screens.

// results of WifiSetupApp_PollAossClient
#define WIFI_SETUP_CLIENT_BUSY   0
#define WIFI_SETUP_CLIENT_DONE   1
#define WIFI_SETUP_CLIENT_FAILED 2

// WifiSetupApp_GetKind: the screen the application starts on
#define WIFI_SETUP_KIND_TOP_MENU        0
#define WIFI_SETUP_KIND_CONNECTION_LIST 1 // leaving the connection list quits

// How the next screen shows the banner and the button bar (WifiSetupApp_SetTransition)
enum WifiSetupBannerMode {
    WIFI_SETUP_BANNER_KEEP,
    WIFI_SETUP_BANNER_OPEN,
    WIFI_SETUP_BANNER_CHANGE,
};

enum WifiSetupButtonBarMode {
    WIFI_SETUP_BUTTON_BAR_KEEP,
    WIFI_SETUP_BUTTON_BAR_CREATE,
};

typedef void (*WifiSetupAppStateFunc)(void);

typedef union WifiSetupAppFlags {
    u32 raw;

    struct {
        u32 kind : 4;     // WIFI_SETUP_KIND_*: low bits of the caller's flags
        u32 options : 28; // the other bits
    } bits;
} WifiSetupAppFlags;

typedef struct WifiSetupApp {
    s8 language; // 0-6
    u8 exit;     // ends the main loop
    u8 unk_02[2];
    void *heap; // work memory handed in by the caller
    WifiSetupAppFlags flags;
    WifiSetupAppStateFunc stateFunc; // called once per frame
    enum WifiSetupBannerMode bannerMode;
    enum WifiSetupButtonBarMode buttonBarMode;
    int screenArg0;
    int screenArg1;
} WifiSetupApp;

typedef struct WifiSetupClient {
    u8 done; // the request finished successfully
    u8 unk_01[3];
    struct WifiSetupRequest *request;
} WifiSetupClient;

// A loaded text bank: a table of offsets into a block of u16 strings.
// String offset block of a message file; the string data block follows it.
typedef struct WifiSetupMessageInfo {
    u32 magic;
    u32 size; // header included
    u16 count;
    u16 entrySize;
    u32 unk_0C;
    u32 offsets[1];
} WifiSetupMessageInfo;

// Message file: a 32-byte file header, then the string offset block.
typedef struct WifiSetupMessageFile {
    u8 header[0x20];
    WifiSetupMessageInfo info;
} WifiSetupMessageFile;

typedef struct WifiSetupTextBank {
    u32 *offsets;
    u8 *strings;
    void *file;
} WifiSetupTextBank;

typedef struct WifiSetupTextBanks {
    WifiSetupTextBank items[8];
    WifiSetupPool *pool;
} WifiSetupTextBanks;

// Events passed to the transfer callback
#define WIFI_SETUP_TRANSFER_EVENT_CHILD_ENTERED   0 // a child asked for the download
#define WIFI_SETUP_TRANSFER_EVENT_ENTRY_CANCELLED 1
#define WIFI_SETUP_TRANSFER_EVENT_DONE            2
#define WIFI_SETUP_TRANSFER_EVENT_STOPPED         3 // stopped or aborted
#define WIFI_SETUP_TRANSFER_EVENT_FAILED          4

typedef void (*WifiSetupSessionCallback)(int event);

typedef struct WifiSetupSession {
    WifiSetupShare share;
    WifiSetupMbParentUser childUser; // the child that asked for the download
    WifiSetupSessionCallback callback;
    WifiSetupTask *task;
    u8 missedEvent; // an event arrived while there was no callback
    u8 cancelled;
} WifiSetupSession;

extern WifiSetupClient gWifiSetupClient;
extern struct WifiSetupRequest *ov13_0224F4C8;
extern WifiSetupApp gWifiSetupApp;
extern WifiSetupTextBanks *gWifiSetupTextBanks;
extern WifiSetupSession *gWifiSetupSession;
extern WifiSetupTextBank *gWifiSetupTextBank;
extern const u8 gWifiSetupAossClientName[12];
extern const WifiSetupSessionParams gWifiSetupTransferSessionParams;

int WifiSetupApp_Run(void *heap, s32 language, s32 flags);
void WifiSetupApp_StartAossClient(void);
void WifiSetupApp_StopAossClient(BOOL apply);
int WifiSetupApp_PollAossClient(void);
void WifiSetupApp_SetStateFunc(WifiSetupAppStateFunc func);
void WifiSetupApp_SetTransition(enum WifiSetupBannerMode bannerMode, enum WifiSetupButtonBarMode buttonBarMode);
void WifiSetupApp_GetTransition(enum WifiSetupBannerMode *bannerMode, enum WifiSetupButtonBarMode *buttonBarMode);
void WifiSetupApp_SetScreenArgs(int arg0, int arg1);
void WifiSetupApp_GetScreenArgs(int *arg0, int *arg1);
u8 WifiSetupApp_GetLanguage(void);
u32 WifiSetupApp_GetKind(void);
BOOL WifiSetupApp_HasOption(u32 mask);
void WifiSetupApp_Exit(void);

void WifiSetupText_InitBanks(void);
void WifiSetupText_FreeBanks(void);
WifiSetupTextBank *WifiSetupText_LoadBank(const char *path);
void WifiSetupText_UnloadBank(WifiSetupTextBank *bank);
u16 *WifiSetupText_GetString(WifiSetupTextBank *bank, int index);
u16 *WifiSetupText_GetStringWithDigit(WifiSetupTextBank *bank, u32 index, int pos, u32 digit);

void WifiSetupTransfer_Start(WifiSetupSessionCallback callback);
void WifiSetupTransfer_Cancel(void);
BOOL WifiSetupTransfer_IsFinished(void);
void WifiSetupTransfer_SetCallback(WifiSetupSessionCallback callback);
void WifiSetupTransfer_StartDownload(void);
WifiSetupMbParentUser *WifiSetupTransfer_GetChildUser(void);

#endif // POKEHEARTGOLD_WIFI_SETUP_APP_H
