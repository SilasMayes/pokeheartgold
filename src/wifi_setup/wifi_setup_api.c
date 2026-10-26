#include "global.h"

#include "wifi_setup/wifi_setup_internal.h"

static int WifiSetup_GetSimpleStartStatus(s32 *status);

void WifiSetup_EncodeLittleEndian(u8 *dst, const u32 *src, u32 len) {
    u32 i = 0;
    while (i < len) {
        u8 *word = dst + i;
        dst[i] = *src;
        word[1] = *src >> 8;
        word[2] = *src >> 16;
        word[3] = *src++ >> 24;
        i += 4;
    }
}

void WifiSetup_DecodeLittleEndian(u32 *dst, const u8 *src, u32 len) {
    u32 i = 0;
    while (i < len) {
        *dst++ = src[i] | (src[i + 1] << 8) | (src[i + 2] << 16) | (src[i + 3] << 24);
        i += 4;
    }
}

void WifiSetup_CopyBytes(u8 *dst, const u8 *src, u32 len) {
    u32 i = 0;
    while (i < len) {
        dst[i] = src[i];
        i++;
    }
}

void WifiSetup_FillBytes(void *dst, int value, u32 count) {
    u32 i = 0;
    s8 *out = dst;
    for (; i < count;) {
        i++;
        *out++ = value;
    }
}

void WifiSetup_CalcMd5(u8 *digest, const u8 *src, u32 len) {
    WifiSetupMd5Context context;
    WifiSetup_Md5Init(&context);
    WifiSetup_Md5Update(&context, src, len);
    WifiSetup_Md5Final(digest, &context);
}

// Milliseconds since start-up.
u32 WifiSetup_GetMilliseconds(void) {
    return (OS_GetTick() << 6) / 0x82ea;
}

void *WifiSetup_WorkCalloc(u32 count, u32 size) {
    u32 total = count * size;
    void *ptr = gWifiSetupWork.alloc(total);
    if (ptr != NULL) {
        memset(ptr, 0, total);
    }
    return ptr;
}

void WifiSetup_WorkFree(void *ptr) {
    gWifiSetupWork.free(ptr);
}

// Two uppercase hex digits of a byte.
int WifiSetup_FormatHexByte(char *dst, int value) {
    char *cursor = dst;
    int count;
    u8 byte = value;
    int digit = (byte & 0xF0) >> 4;
    count = 0;
    int next = byte & 0xF;
    do {
        if (digit <= 9) {
            digit += '0';
        } else {
            digit += 'A' - 10;
        }
        count++;
        *cursor = digit;
        cursor++;
        digit = next;
    } while (count < 2);
    *cursor = '\0';
    return cursor - dst;
}

// "XX:XX:XX:XX:XX:XX"
int WifiSetup_FormatMacAddress(char *dst, const s8 *mac) {
    char *cursor = dst;
    int i;
    for (i = 0; i < 6; i++) {
        cursor += WifiSetup_FormatHexByte(cursor, *mac++);
        if (i < 5) {
            *cursor++ = ':';
        }
    }
    *cursor = '\0';
    return cursor - dst;
}

// the worker thread changes the state: read and write it as volatile here
#define WORK_STATE (*(volatile s32 *)&gWifiSetupWork.state)

int WifiSetup_StartSimpleStart(u32 priority, u32 count, void (*statusCallback)(s32 *), WifiSetupWorkAllocFunc alloc, WifiSetupWorkFreeFunc free, u32 stackSize) {
    int result;
    int state;

    state = WORK_STATE;
    if (state >= WIFI_SETUP_SIMPLE_START_STARTED && state <= WIFI_SETUP_SIMPLE_START_GETTING_SETTINGS) {
        return -10;
    }
    gWifiSetupConfig.count = count;
    WORK_STATE = WIFI_SETUP_SIMPLE_START_STOPPED;
    gWifiSetupWork.statusCallback = statusCallback;
    gWifiSetupWork.alloc = alloc;
    gWifiSetupWork.free = free;
    gWifiSetupConfig.threadStackSize = stackSize;
    result = WifiSetupLink_Open(count);
    gWifiSetupWork.resultReady = 1;
    if (result < 0) {
        gWifiSetupWork.error = result;
        return result;
    }
    gWifiSetupWork.threadStack = gWifiSetupWork.alloc(gWifiSetupConfig.threadStackSize);
    if (gWifiSetupWork.threadStack == NULL) {
        gWifiSetupWork.error = -1;
        return -1;
    }
    if (OS_IsThreadAvailable() != TRUE) {
        gWifiSetupWork.error = -9;
        return -9;
    }
    OS_CreateThread(&gWifiSetupThread, WifiSetup_SimpleStartThread, NULL, (u8 *)gWifiSetupWork.threadStack + (gWifiSetupConfig.threadStackSize & ~7), gWifiSetupConfig.threadStackSize, priority);
    WORK_STATE = WIFI_SETUP_SIMPLE_START_STARTED;
    gWifiSetupConfig.deadline = WifiSetup_GetMilliseconds() + 60000;
    gWifiSetupWork.stop = 0;
    memset(&gWifiSetupResult, 0, sizeof(gWifiSetupResult));
    WifiSetup_ReportSimpleStartStatus();
    OS_WakeupThreadDirect(&gWifiSetupThread);
    gWifiSetupWork.active = TRUE;
    return 1;
}

#undef WORK_STATE

int WifiSetup_StopSimpleStart(void) {
    s32 old;
    if (gWifiSetupWork.active) {
        old = gWifiSetupWork.state;
        gWifiSetupWork.stop = 1;
        while (gWifiSetupWork.state >= WIFI_SETUP_SIMPLE_START_STARTED && gWifiSetupWork.state <= WIFI_SETUP_SIMPLE_START_GETTING_SETTINGS) {
            OS_Sleep(100);
        }
        OS_Sleep(500);
        while (!OS_IsThreadTerminated(&gWifiSetupThread)) {
            OS_WakeupThreadDirect(&gWifiSetupThread);
            OS_JoinThread(&gWifiSetupThread);
        }
        if (gWifiSetupWork.threadStack != NULL) {
            gWifiSetupWork.free(gWifiSetupWork.threadStack);
            gWifiSetupWork.threadStack = NULL;
        }
        gWifiSetupWork.active = FALSE;
        if (old != gWifiSetupWork.state) {
            WifiSetup_ReportSimpleStartStatus();
        }
    }
    if (gWifiSetupWork.resultReady > 0) {
        int result = WifiSetupLink_Close();
        gWifiSetupWork.resultReady = 0;
        return result;
    }
    return -10;
}

static int WifiSetup_GetSimpleStartStatus(s32 *status) {
    status[0] = gWifiSetupWork.state;
    if (gWifiSetupConfig.deadline == -1) {
        status[1] = -1;
    } else {
        status[1] = gWifiSetupConfig.deadline - WifiSetup_GetMilliseconds();
    }
    status[2] = gWifiSetupWork.error;
    return 1;
}

int WifiSetup_GetSimpleStartResult(WifiSetupResult *dst) {
    memcpy(dst, &gWifiSetupResult, sizeof(gWifiSetupResult));
    return 1;
}

void WifiSetup_ReportSimpleStartStatus(void) {
    s32 status[3];
    WifiSetup_GetSimpleStartStatus(status);
    gWifiSetupWork.statusCallback(status);
}
