#ifndef PORT_SDK_NITRO_WM_WM_INTERNAL_H
#define PORT_SDK_NITRO_WM_WM_INTERNAL_H

// Port build: the decomp's own view of the wireless manager (lib/include/nitro/wm/wm_internal.h)
// spells the SDK's types differently. libntr implements the real WM API, so the game code
// gets the real types under the decomp's names. The ARM7 request plumbing in the decomp header
// (WmSystemWork, gWm* labels, the command buffers) has no counterpart and is left out.

#include <nitro.h>

typedef WMCallbackFunc WmCallback;
typedef WMParentParam WmParentParam;
typedef WMScanParam WmScanParam;
typedef WMScanExParam WmScanExParam;
typedef WMStatus WmStatus;
typedef WMPortRecvCallback WmPortEvent;
typedef WMOtherElements WMOtherElementResults;

// API ids (callback apiid field)
#define WM_API_INITIALIZE       WM_APIID_INITIALIZE
#define WM_API_RESET            WM_APIID_RESET
#define WM_API_END              WM_APIID_END
#define WM_API_ENABLE           WM_APIID_ENABLE
#define WM_API_DISABLE          WM_APIID_DISABLE
#define WM_API_POWER_ON         WM_APIID_POWER_ON
#define WM_API_POWER_OFF        WM_APIID_POWER_OFF
#define WM_API_SET_PARENT_PARAM WM_APIID_SET_P_PARAM
#define WM_API_START_PARENT     WM_APIID_START_PARENT
#define WM_API_END_PARENT       WM_APIID_END_PARENT
#define WM_API_START_SCAN       WM_APIID_START_SCAN
#define WM_API_END_SCAN         WM_APIID_END_SCAN
#define WM_API_START_CONNECT    WM_APIID_START_CONNECT
#define WM_API_DISCONNECT       WM_APIID_DISCONNECT
#define WM_API_START_MP         WM_APIID_START_MP
#define WM_API_SET_MP_DATA      WM_APIID_SET_MP_DATA
#define WM_API_END_MP           WM_APIID_END_MP
#define WM_API_START_DCF        WM_APIID_START_DCF
#define WM_API_SET_DCF_DATA     WM_APIID_SET_DCF_DATA
#define WM_API_END_DCF          WM_APIID_END_DCF
#define WM_API_SET_WEP_KEY      WM_APIID_SET_WEPKEY
#define WM_API_SET_GAME_INFO    WM_APIID_SET_GAMEINFO
#define WM_API_SET_BEACON_IND   WM_APIID_SET_BEACON_IND
#define WM_API_SET_LIFE_TIME    WM_APIID_SET_LIFETIME
#define WM_API_MEASURE_CHANNEL  WM_APIID_MEASURE_CHANNEL
#define WM_API_SET_ENTRY        WM_APIID_SET_ENTRY
#define WM_API_START_SCAN_EX    WM_APIID_START_SCAN_EX
#define WM_API_SET_WEP_KEY_EX   WM_APIID_SET_WEPKEY_EX
#define WM_API_INDICATION       WM_APIID_INDICATION
#define WM_API_PORT_RECEIVE     WM_APIID_PORT_RECV

// WmStatus.state
#define WM_STATE_INIT      WM_STATE_READY
#define WM_STATE_ENABLED   WM_STATE_STOP
#define WM_STATE_POWER_ON  WM_STATE_IDLE
#define WM_STATE_SCANNING  WM_STATE_SCAN

// WmPortEvent.state
#define WM_EVENT_CONNECTED    WM_STATECODE_CONNECTED
#define WM_EVENT_DISCONNECTED WM_STATECODE_DISCONNECTED
#define WM_EVENT_PORT_RECEIVE WM_STATECODE_PORT_RECV
#define WM_EVENT_PORT_INIT    WM_STATECODE_PORT_INIT
#define WM_EVENT_26           26

#endif // PORT_SDK_NITRO_WM_WM_INTERNAL_H
