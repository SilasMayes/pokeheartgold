// Port only: the stats upload client's data (src/stats_upload.c), which the DS keeps in
// lib/NitroDWC/asm/dwc_lobby_chat_data.s. The strings are as there; gStatsUpload and
// gStatsUploadServer get their C types, since on the DS gStatsUpload spans three labels
// (gStatsUpload, gStatsUploadGameName, gStatsUploadSecretKey; see port_sdk/dwc/stats_upload_internal.h)
// and the server is a pointer.

#include "global.h"

#include <dwc/stats_upload_internal.h>

char *gStatsUploadServer = NULL;
StatsUpload gStatsUpload = { .state = STATS_UPLOAD_STOPPED };
char gStatsUploadLastHash[44];

char gStatsUploadStr_Hash[8] = "&hash=";
char gStatsUploadStr_Error[8] = "error:";
char gStatsUploadServerRelease[40] = "http://gamestats2.gs.nintendowifi.net/";
char gStatsUploadServerDev1[36] = "http://sdkdev.gamespy.com/games/";
char gStatsUploadServerDev2[40] = "http://ishikawa.servebeer.com/games/";
char gStatsUploadStr_Data[8] = "&data=";
char gStatsUploadFmt_Int_7[4] = "%d";
char gStatsUploadStr_Pid[8] = "?pid=";
char gStatsUploadFmt_PidHashData[28] = "%s%s%s?pid=%d&hash=%s&data=";
char gStatsUploadStr_0000000000000000000000000000000000000000[44] = "0000000000000000000000000000000000000000";
char gStatsUploadEmptyString[20];
