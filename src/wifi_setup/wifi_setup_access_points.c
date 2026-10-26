#include "wifi_setup/wifi_setup_access_points.h"

#include "global.h"

#include "dwc/dwc_bm_internal.h"
#include "wifi_setup/wifi_setup.h"
#include "nnsys/snd_arc_internal.h"
#include "wifi_setup/wifi_setup_local_wireless.h"
#include "wifi_setup/wifi_setup_ui.h"

#include <nitro/code32.h>

// Access-point data: the scan for access points over WM, the saved connection settings (written back with a CRC per
// page), address parsing for the address entry, and the start and end of the sound archive.

extern long atol(const char *);

static int WifiSetupApScan_Continue(void);
static void WifiSetupApScan_Callback(void *arg);
static void WifiSetupApScan_StoreResults(WMStartScanExCallback *cb);
static void WifiSetupConnections_WritePage(int index);
static int WifiSetup_HexDigitValue(u8 ch);

int WifiSetupApScan_Start(void) {
    WifiSetupApScan *scan;
    MI_CpuClear16(gWifiSetupApScan->entries, sizeof(gWifiSetupApScan->entries));
    if (WM_Initialize(gWifiSetupApScan, WifiSetupApScan_Callback, 3) != WM_ERRCODE_OPERATING) {
        return 0;
    }
    do {
        WM_ReadStatus(&gWifiSetupApScan->status);
        scan = gWifiSetupApScan;
    } while (scan->status.state != 2);
    scan->param = gWifiSetupApScanParam;
    scan->param.buffer = scan->scanBuf;
    gWifiSetupApScan->param.dwell = WM_GetDispersionScanPeriod();
    return WifiSetupApScan_Continue() ? 1 : 0;
}

static int WifiSetupApScan_Continue(void) {
    return WM_StartScanEx(WifiSetupApScan_Callback, &gWifiSetupApScan->param) == WM_ERRCODE_OPERATING ? 1 : 0;
}

BOOL WifiSetupApScan_End(void) {
    gWifiSetupApScan->ending = 1;
    WM_ReadStatus(&gWifiSetupApScan->status);
    if (gWifiSetupApScan->status.state != 2) {
        if (WM_Reset(WifiSetupApScan_Callback) != WM_ERRCODE_OPERATING) {
            return FALSE;
        }
        do {
            WM_ReadStatus(&gWifiSetupApScan->status);
        } while (gWifiSetupApScan->status.state != 2);
    }
    if (WM_End(WifiSetupApScan_Callback) != WM_ERRCODE_OPERATING) {
        return FALSE;
    }
    return TRUE;
}

int WifiSetupApScan_GetEntries(WifiSetupScanEntry **out) {
    WifiSetupScanEntry *entries;
    int count = 0;
    int i;
    *out = entries = gWifiSetupApScan->entries;
    for (i = 0; i < WIFI_SETUP_NUM_SCAN_ENTRIES; i++) {
        if (memcmp(entries[i].bssid, gWifiSetupApScanEmptyBssid, sizeof(entries[i].bssid)) != 0) {
            count++;
        }
    }
    return count;
}

static void WifiSetupApScan_Callback(void *arg) {
    WMStartScanExCallback *cb = arg;
    if (cb->errcode != WM_ERRCODE_SUCCESS) {
        return;
    }
    if (gWifiSetupApScan->ending != 0 || cb->apiid != 0x26) {
        return;
    }
    switch (cb->state) {
    case 5:
        WifiSetupApScan_StoreResults(cb);
        WifiSetupApScan_Continue();
        break;
    case 4:
        WifiSetupApScan_Continue();
        break;
    default:
        OS_Terminate();
        break;
    }
}

static void WifiSetupApScan_StoreResults(WMStartScanExCallback *cb) {
    WMOtherElementResults elems;
    WifiSetupScanEntry *entries;
    WMBssDesc *desc;
    int i;
    int j;
    int k;
    int count;

    entries = gWifiSetupApScan->entries;
    DC_InvalidateRange(gWifiSetupApScan->scanBuf, 0x400);
    for (i = 0; i < cb->bssDescCount; i++) {
        desc = cb->bssDesc[i];
        if (desc->ssid[0] == 0 || desc->gameInfoLength != 0) {
            continue;
        }
        for (j = 0; j < WIFI_SETUP_NUM_SCAN_ENTRIES; j++) {
            if (memcmp(desc->bssid, entries[j].bssid, sizeof(desc->bssid)) == 0) {
                break;
            }
        }
        if (j == WIFI_SETUP_NUM_SCAN_ENTRIES) {
            for (j = 0; j < WIFI_SETUP_NUM_SCAN_ENTRIES; j++) {
                if (memcmp(entries[j].bssid, gWifiSetupApScanEmptyBssid, sizeof(entries[j].bssid)) == 0) {
                    break;
                }
            }
            if (j == WIFI_SETUP_NUM_SCAN_ENTRIES) {
                return;
            }
        }
        MI_CpuCopy8(desc->bssid, entries[j].bssid, sizeof(entries[j].bssid));
        MI_CpuCopy8(desc->ssid, entries[j].ssid, sizeof(entries[j].ssid));
        entries[j].linkLevel = cb->linkLevel[i];
        if (!(desc->capaInfo & 0x10)) {
            entries[j].security = 0;
            continue;
        }
        entries[j].security = 1;
        elems = WM_GetOtherElements(desc);
        count = elems.count;
        for (k = 0; k < count; k++) {
            if (elems.element[k].id == 0x30) {
                entries[j].security = 2;
                break;
            }
            if (elems.element[k].id == 0xdd && elems.element[k].length >= 4) {
                if (memcmp(elems.element[k].body, gWifiSetupWpaVendorPrefix, 4) == 0) {
                    entries[j].security = 2;
                    break;
                }
            }
        }
    }
}

void WifiSetupConnections_Load(void) {
    WifiSetupConnections *connections = WifiSetupHeap_AllocZeroed(sizeof(WifiSetupConnections), 0x20);
    gWifiSetupConnections = connections;
    MATHi_CRC16InitTableRev(&connections->crcTable, 0xA001);
    DWCi_BACKUPlRead(gWifiSetupConnections);
}

void WifiSetupConnections_Free(void) {
    WifiSetupHeap_FreeAndClear(&gWifiSetupConnections);
}

WifiSetupConnection *WifiSetupConnections_GetEdit(void) {
    return &gWifiSetupConnections->edit;
}

void WifiSetupConnections_SetAutoAddress(int on) {
    gWifiSetupConnections->edit.autoAddress = on;
}

void WifiSetupConnections_SetAutoDns(int on) {
    gWifiSetupConnections->edit.autoDns = on;
}

void WifiSetupConnections_SetSsid(const u8 *ssid) {
    MI_CpuCopy8(ssid, gWifiSetupConnections->edit.settings.ssid, sizeof(gWifiSetupConnections->edit.settings.ssid));
    gWifiSetupConnections->edit.settings.setupMethod = WIFI_SETUP_METHOD_MANUAL;
}

#pragma force_active on

void WifiSetupConnections_SetWepKey(const char *key) {
    int i;
    int len;
    u8 *dst;
    int hi;

    MI_CpuFill8(gWifiSetupConnections->edit.settings.wepKeys[0], 0, sizeof(gWifiSetupConnections->edit.settings.wepKeys[0]));
    len = WifiSetup_StrNLen(key, 0x20);
    switch (len) {
    case 0:
    case 10:
    case 26:
    case 32:
        gWifiSetupConnections->edit.settings.keyFormat = WIFI_SETUP_KEY_FORMAT_HEX;
        dst = gWifiSetupConnections->edit.settings.wepKeys[0];
        for (i = 0; i < len; i += 2) {
            hi = WifiSetup_HexDigitValue(key[i]);
            *dst++ = WifiSetup_HexDigitValue(key[i + 1]) + (hi << 4);
        }
        break;
    default:
        gWifiSetupConnections->edit.settings.keyFormat = WIFI_SETUP_KEY_FORMAT_TEXT;
        MI_CpuCopy8(key, gWifiSetupConnections->edit.settings.wepKeys[0], sizeof(gWifiSetupConnections->edit.settings.wepKeys[0]));
        break;
    }
    switch (len) {
    case 0:
        gWifiSetupConnections->edit.settings.keyType = WM_WEPMODE_NO;
        break;
    case 5:
    case 10:
        gWifiSetupConnections->edit.settings.keyType = WM_WEPMODE_40BIT;
        break;
    case 13:
    case 26:
        gWifiSetupConnections->edit.settings.keyType = WM_WEPMODE_104BIT;
        break;
    default:
        gWifiSetupConnections->edit.settings.keyType = WM_WEPMODE_128BIT;
        break;
    }
}

void WifiSetupConnections_SetIpAddress(const char *str) {
    WifiSetup_ParseAddress(str, gWifiSetupConnections->edit.settings.ip);
}

void WifiSetupConnections_SetSubnetMask(const char *str) {
    WifiSetup_ParseAddress(str, gWifiSetupConnections->edit.mask);
}

void WifiSetupConnections_SetGateway(const char *str) {
    WifiSetup_ParseAddress(str, gWifiSetupConnections->edit.settings.gateway);
}

void WifiSetupConnections_SetPrimaryDns(const char *str) {
    WifiSetup_ParseAddress(str, gWifiSetupConnections->edit.settings.dns1);
}

void WifiSetupConnections_SetSecondaryDns(const char *str) {
    WifiSetup_ParseAddress(str, gWifiSetupConnections->edit.settings.dns2);
}

#pragma force_active reset

void WifiSetupConnections_GetSsid(u8 *dst) {
    MI_CpuCopy8(gWifiSetupConnections->edit.settings.ssid, dst, sizeof(gWifiSetupConnections->edit.settings.ssid));
}

void WifiSetupConnections_FormatIpAddress(char *buf) {
    WifiSetupConnections *connections = gWifiSetupConnections;
    OS_SPrintf(buf, gWifiSetupConnectionsAddressFormat, connections->edit.settings.ip[0], connections->edit.settings.ip[1], connections->edit.settings.ip[2], connections->edit.settings.ip[3]);
}

void WifiSetupConnections_FormatSubnetMask(char *buf) {
    WifiSetupConnections *connections = gWifiSetupConnections;
    OS_SPrintf(buf, gWifiSetupConnectionsAddressFormat, connections->edit.mask[0], connections->edit.mask[1], connections->edit.mask[2], connections->edit.mask[3]);
}

void WifiSetupConnections_FormatGateway(char *buf) {
    WifiSetupConnections *connections = gWifiSetupConnections;
    u8 *address = connections->edit.settings.gateway;
    OS_SPrintf(buf, gWifiSetupConnectionsAddressFormat, address[0], address[1], address[2], address[3]);
}

void WifiSetupConnections_FormatPrimaryDns(char *buf) {
    WifiSetupConnections *connections = gWifiSetupConnections;
    u8 *address = connections->edit.settings.dns1;
    OS_SPrintf(buf, gWifiSetupConnectionsAddressFormat, address[0], address[1], address[2], address[3]);
}

void WifiSetupConnections_FormatSecondaryDns(char *buf) {
    WifiSetupConnections *connections = gWifiSetupConnections;
    u8 *address = connections->edit.settings.dns2;
    OS_SPrintf(buf, gWifiSetupConnectionsAddressFormat, address[0], address[1], address[2], address[3]);
}

u8 WifiSetupConnections_GetSetupMethod(int idx) {
    return gWifiSetupConnections->pages[idx].settings.setupMethod;
}

void WifiSetupConnections_Edit(int idx) {
    WifiSetupConnections *connections = gWifiSetupConnections;
    WifiSetupConnectionPage *page = &connections->pages[idx];
    connections->edit.settings = page->settings;
    connections->edit.index = idx;
    if (memcmp(page->settings.ip, gWifiSetupZeroAddress, sizeof(page->settings.ip)) != 0) {
        gWifiSetupConnections->edit.autoAddress = FALSE;
    } else {
        gWifiSetupConnections->edit.autoAddress = TRUE;
    }
    if (memcmp(page->settings.dns1, gWifiSetupZeroAddress, sizeof(page->settings.dns1)) != 0 || memcmp(page->settings.dns2, gWifiSetupZeroAddress, sizeof(page->settings.dns2)) != 0) {
        gWifiSetupConnections->edit.autoDns = FALSE;
    } else {
        gWifiSetupConnections->edit.autoDns = TRUE;
    }
    DWCi_BACKUPlConvMaskAddr(page->settings.cidr, gWifiSetupConnections->edit.mask);
}

void WifiSetupConnections_SaveEdit(void) {
    WifiSetupConnections *connections = gWifiSetupConnections;
    WifiSetupConnection *work = &connections->edit;
    WifiSetupConnectionPage *page = &connections->pages[work->index];
    int cidr;
    page->settings = work->settings;
    if (work->autoAddress) {
        MI_CpuFill8(page->settings.ip, 0, sizeof(page->settings.ip));
        MI_CpuFill8(page->settings.gateway, 0, sizeof(page->settings.gateway));
        cidr = 0;
    } else {
        MI_CpuCopy8(work->settings.ip, page->settings.ip, sizeof(page->settings.ip));
        MI_CpuCopy8(work->settings.gateway, page->settings.gateway, sizeof(page->settings.gateway));
        cidr = DWCi_BACKUPlConvMaskCidr(work->mask);
    }
    page->settings.cidr = cidr;
    if (work->autoDns) {
        MI_CpuFill8(page->settings.dns1, 0, 8);
    } else {
        MI_CpuCopy8(work->settings.dns1, page->settings.dns1, 8);
    }
    WifiSetupConnections_WritePage(work->index);
}

void WifiSetupConnections_SetFromClientResult(WifiSetupResult *src) {
    WifiSetupConnections *connections = gWifiSetupConnections;
    WifiSetupConnection *work = &connections->edit;
    u32 len;
    int i;
    MI_CpuFill8(work, 0, offsetof(WifiSetupConnection, settings.usedMask));
    MI_CpuCopy8(src, work->settings.ssid, sizeof(work->settings.ssid));
    switch (src->keyType) {
    case WM_WEPMODE_40BIT:
        work->settings.keyType = WM_WEPMODE_40BIT;
        len = 5;
        break;
    case WM_WEPMODE_104BIT:
        work->settings.keyType = WM_WEPMODE_104BIT;
        len = 13;
        break;
    case WM_WEPMODE_128BIT:
        work->settings.keyType = WM_WEPMODE_128BIT;
        len = 16;
        break;
    default:
        work->settings.keyType = WM_WEPMODE_NO;
        len = 0;
        break;
    }
    work->settings.keyFormat = WIFI_SETUP_KEY_FORMAT_HEX;
    for (i = 0; i < 4; i++) {
        MI_CpuCopy8(src->wepKeys[i], work->settings.wepKeys[i], len);
    }
    work->settings.setupMethod = WIFI_SETUP_METHOD_AUTO;
    MI_CpuFill8(work->mask, 0, sizeof(work->mask));
    work->autoAddress = TRUE;
    work->autoDns = TRUE;
    WifiSetupConnections_SaveEdit();
}

void WifiSetupConnections_SetFromInfo(const WifiSetupAossResult *src) {
    WifiSetupConnection *work = &gWifiSetupConnections->edit;
    MI_CpuFill8(work, 0, offsetof(WifiSetupConnection, settings.usedMask));
    MI_CpuCopy8(src->wep64Keys[0], &work->settings.wep40Keys[0], 5);
    MI_CpuCopy8(src->wep64Keys[1], &work->settings.wep40Keys[5], 5);
    MI_CpuCopy8(src->wep64Keys[2], &work->settings.wep40Keys[10], 5);
    MI_CpuCopy8(src->wep64Keys[3], &work->settings.wep40Keys[15], 5);
    MI_CpuCopy8(src->wep64Ssid, work->settings.unk_60, sizeof(work->settings.unk_60));
    MI_CpuCopy8(src->wep128Keys[0], work->settings.wepKeys[0], 13);
    MI_CpuCopy8(src->wep128Keys[1], work->settings.wepKeys[1], 13);
    MI_CpuCopy8(src->wep128Keys[2], work->settings.wepKeys[2], 13);
    MI_CpuCopy8(src->wep128Keys[3], work->settings.wepKeys[3], 13);
    MI_CpuCopy8(src->wep128Ssid, work->settings.ssid, sizeof(work->settings.ssid));
    work->settings.keyType = WM_WEPMODE_104BIT;
    work->settings.keyFormat = WIFI_SETUP_KEY_FORMAT_HEX;
    work->settings.setupMethod = WIFI_SETUP_METHOD_COPIED;
    MI_CpuFill8(work->mask, 0, sizeof(work->mask));
    work->autoAddress = TRUE;
    work->autoDns = TRUE;
    WifiSetupConnections_SaveEdit();
}

WifiSetupConnections *WifiSetupConnections_Get(void) {
    return gWifiSetupConnections;
}

void WifiSetupConnections_Erase(int idx) {
    WifiSetupConnectionPage *page = &gWifiSetupConnections->pages[idx];
    MI_CpuFill8(page, 0, offsetof(WifiSetupConnectionPage, settings.usedMask));
    page->settings.setupMethod = WIFI_SETUP_METHOD_ERASED;
    WifiSetupConnections_WritePage(idx);
}

void WifiSetupConnections_Reset(void) {
    DwcWiFiInfo info;
    u8 *conv;
    int i;
    MI_CpuClear16(gWifiSetupConnections, 0x400);
    for (i = 0; i < 3; i++) {
        gWifiSetupConnections->pages[i].settings.setupMethod = WIFI_SETUP_METHOD_ERASED;
    }
    DWCi_AUTH_GetNewWiFiInfo(&info);
    conv = DWCi_BACKUPlConvWifiInfo(&info);
    for (i = 0; i < 2; i++) {
        MI_CpuCopy8(conv, gWifiSetupConnections->pages[i].tail.page.info, sizeof(gWifiSetupConnections->pages[i].tail.page.info));
    }
    for (i = 0; i < 4; i++) {
        WifiSetupConnections_WritePage(i);
    }
}

static void WifiSetupConnections_WritePage(int index) {
    BOOL changed[4];
    void *temp;
    int status = gWifiSetupConnections->pages[index].settings.setupMethod;
    int active = 0, i, offset;
    int value = 1 << index;
    MI_CpuFill8(changed, 0, sizeof(changed));
    changed[index] = 1;
    if (index <= 2) {
        if (gWifiSetupConnections->pages[0].settings.usedMask & value) {
            active = 1;
        }
        if (status == WIFI_SETUP_METHOD_ERASED && active) {
            gWifiSetupConnections->pages[0].settings.usedMask &= ~value;
            gWifiSetupConnections->pages[1].settings.usedMask &= ~value;
            changed[0] = changed[1] = 1;
        } else if (status != WIFI_SETUP_METHOD_ERASED && !active) {
            gWifiSetupConnections->pages[0].settings.usedMask |= value;
            gWifiSetupConnections->pages[1].settings.usedMask |= value;
            changed[0] = changed[1] = 1;
        }
    }
    i = 0;
    offset = 0;
    for (; i < 4; i++, offset += 256) {
        if (changed[i]) {
            gWifiSetupConnections->pages[i].tail.page.crc = MATH_CalcCRC16(&gWifiSetupConnections->crcTable, (u8 *)gWifiSetupConnections + offset, 254);
        }
    }
    temp = WifiSetupHeap_AllocZeroed(256, 32);
    DWCi_BACKUPlWritePage(gWifiSetupConnections, changed, temp);
    WifiSetupHeap_FreeAndClear(&temp);
}

void WifiSetup_ParseAddress(const char *str, u8 *out) {
    u8 buf[4];
    int i;
    int j;
    int off;
    MI_CpuFill8(buf, 0, sizeof(buf));
    for (i = 0, off = 0; i < 4; i++, off += 3) {
        MI_CpuCopy8(str + off, buf, 3);
        for (j = 0; j < 3; j++) {
            if (buf[j] != 0) {
                break;
            }
            buf[j] = ' ';
        }
        out[i] = atol((char *)buf);
    }
}

static int WifiSetup_HexDigitValue(u8 ch) {
    if (ch <= '9') {
        return ch - '0';
    }
    if (ch <= 'F') {
        return ch - 'A' + 10;
    }
    return ch - 'a' + 10;
}

void WifiSetupSound_Init(void) {
    u32 size;
    gWifiSetupSound = WifiSetupHeap_AllocZeroed(sizeof(WifiSetupSound), 4);
    gWifiSetupSound->data = WifiSetupFile_Load(gWifiSetupSoundArchivePath, &size, 0x20);
    NNS_SndInit();
    NNS_SndArcInitOnMemory(&gWifiSetupSound->arc, gWifiSetupSound->data);
    NNS_SndArcPlayerSetup(0);
    NNS_SndHandleInit(&gWifiSetupSound->handle);
    gWifiSetupSound->task = WifiSetupTask_Create(WIFI_SETUP_TASK_QUEUE_MAIN, WifiSetupSound_UpdateTask, NULL, 0xc8);
}

WifiSetupSound *gWifiSetupSound;

void WifiSetupSound_Free(void) {
    WifiSetupTask_DestroyLater(WIFI_SETUP_TASK_QUEUE_MAIN, gWifiSetupSound->task);
    WifiSetupHeap_FreeAndClear(&gWifiSetupSound);
}
