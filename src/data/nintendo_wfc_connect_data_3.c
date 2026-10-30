// Converted from asm/nintendo_wfc_connect_data.s (part 3 of 5) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

// The C declarations of these do not match the data (see the notes at each
// definition): keep them out of the way of the definitions below.
#define gNintendoWfcScreens                    gNintendoWfcScreens_header_decl
#define gNintendoWfcStates                     gNintendoWfcStates_header_decl
#define gNintendoWfcPadKeysUpFromLeftButton    gNintendoWfcPadKeysUpFromLeftButton_header_decl
#define gNintendoWfcPadKeysDownFromLeftButton  gNintendoWfcPadKeysDownFromLeftButton_header_decl
#define gNintendoWfcPadKeysUpFromRightButton   gNintendoWfcPadKeysUpFromRightButton_header_decl
#define gNintendoWfcPadKeysDownFromRightButton gNintendoWfcPadKeysDownFromRightButton_header_decl
#ifndef SDK_PORT
#define ov72_0223B900 ov72_0223B900_header_decl
#endif

#include "global.h"

#include "nintendo_wfc_connect_internal.h"

#pragma force_active on

#undef gNintendoWfcScreens
#undef gNintendoWfcStates
#undef gNintendoWfcPadKeysUpFromLeftButton
#undef gNintendoWfcPadKeysDownFromLeftButton
#undef gNintendoWfcPadKeysUpFromRightButton
#undef gNintendoWfcPadKeysDownFromRightButton
#ifndef SDK_PORT
#undef ov72_0223B900
#endif

// C declares this const, but it lives in .data
// clang-format off
enum NintendoWfcMainState (*gNintendoWfcStates[57])(NintendoWfcConnect *wfc) = {
    (enum NintendoWfcMainState (*)(NintendoWfcConnect *))NintendoWfc_AskConnect,
    (enum NintendoWfcMainState (*)(NintendoWfcConnect *))NintendoWfc_HandleConnectChoice,
    (enum NintendoWfcMainState (*)(NintendoWfcConnect *))NintendoWfc_StartConnect,
    (enum NintendoWfcMainState (*)(NintendoWfcConnect *))NintendoWfc_WaitConnect,
    (enum NintendoWfcMainState (*)(NintendoWfcConnect *))NintendoWfc_StartAuth,
    (enum NintendoWfcMainState (*)(NintendoWfcConnect *))NintendoWfc_WaitAuth,
    (enum NintendoWfcMainState (*)(NintendoWfcConnect *))NintendoWfc_InitHttp,
    (enum NintendoWfcMainState (*)(NintendoWfcConnect *))NintendoWfc_RequestInfo,
    (enum NintendoWfcMainState (*)(NintendoWfcConnect *))NintendoWfc_WaitInfo,
    (enum NintendoWfcMainState (*)(NintendoWfcConnect *))NintendoWfc_RequestSetProfile,
    (enum NintendoWfcMainState (*)(NintendoWfcConnect *))NintendoWfc_WaitSetProfile,
    (enum NintendoWfcMainState (*)(NintendoWfcConnect *))NintendoWfc_RequestRoomCount,
    (enum NintendoWfcMainState (*)(NintendoWfcConnect *))NintendoWfc_WaitRoomCount,
    (enum NintendoWfcMainState (*)(NintendoWfcConnect *))NintendoWfc_AskChallengeRoom,
    (enum NintendoWfcMainState (*)(NintendoWfcConnect *))NintendoWfc_StartChallengeRoomInput,
    (enum NintendoWfcMainState (*)(NintendoWfcConnect *))NintendoWfc_HandleChallengeRoomInput,
    (enum NintendoWfcMainState (*)(NintendoWfcConnect *))NintendoWfc_PrintReceivingTrainers,
    (enum NintendoWfcMainState (*)(NintendoWfcConnect *))NintendoWfc_RequestTrainersDownload,
    (enum NintendoWfcMainState (*)(NintendoWfcConnect *))NintendoWfc_WaitTrainersDownload,
    (enum NintendoWfcMainState (*)(NintendoWfcConnect *))NintendoWfc_PrintTrainersReceived,
    (enum NintendoWfcMainState (*)(NintendoWfcConnect *))NintendoWfc_PrintRoomUnavailable,
    (enum NintendoWfcMainState (*)(NintendoWfcConnect *))NintendoWfc_AskCancelChallenge,
    (enum NintendoWfcMainState (*)(NintendoWfcConnect *))NintendoWfc_HandleCancelChallengeChoice,
    (enum NintendoWfcMainState (*)(NintendoWfcConnect *))NintendoWfc_AskCancelDownload,
    (enum NintendoWfcMainState (*)(NintendoWfcConnect *))NintendoWfc_HandleCancelDownloadChoice,
    (enum NintendoWfcMainState (*)(NintendoWfcConnect *))NintendoWfc_PrintSendingRecord,
    (enum NintendoWfcMainState (*)(NintendoWfcConnect *))NintendoWfc_RequestUpload,
    (enum NintendoWfcMainState (*)(NintendoWfcConnect *))NintendoWfc_WaitUpload,
    (enum NintendoWfcMainState (*)(NintendoWfcConnect *))NintendoWfc_PrintRecordSent,
    (enum NintendoWfcMainState (*)(NintendoWfcConnect *))NintendoWfc_AskLeadersRank,
    (enum NintendoWfcMainState (*)(NintendoWfcConnect *))NintendoWfc_StartLeadersRankInput,
    (enum NintendoWfcMainState (*)(NintendoWfcConnect *))NintendoWfc_HandleLeadersRankInput,
    (enum NintendoWfcMainState (*)(NintendoWfcConnect *))NintendoWfc_AskLeadersRoom,
    (enum NintendoWfcMainState (*)(NintendoWfcConnect *))NintendoWfc_StartLeadersRoomInput,
    (enum NintendoWfcMainState (*)(NintendoWfcConnect *))NintendoWfc_HandleLeadersRoomInput,
    (enum NintendoWfcMainState (*)(NintendoWfcConnect *))NintendoWfc_PrintReceivingLeaders,
    (enum NintendoWfcMainState (*)(NintendoWfcConnect *))NintendoWfc_RequestLeadersDownload,
    (enum NintendoWfcMainState (*)(NintendoWfcConnect *))NintendoWfc_WaitLeadersDownload,
    (enum NintendoWfcMainState (*)(NintendoWfcConnect *))NintendoWfc_PrintLeadersReceived,
    (enum NintendoWfcMainState (*)(NintendoWfcConnect *))NintendoWfc_StartSave,
    (enum NintendoWfcMainState (*)(NintendoWfcConnect *))NintendoWfc_Save,
    (enum NintendoWfcMainState (*)(NintendoWfcConnect *))NintendoWfc_PrintDisconnecting,
    (enum NintendoWfcMainState (*)(NintendoWfcConnect *))NintendoWfc_CloseConnection,
    (enum NintendoWfcMainState (*)(NintendoWfcConnect *))NintendoWfc_PrintDisconnected,
    (enum NintendoWfcMainState (*)(NintendoWfcConnect *))NintendoWfc_UnusedState_Idle,
    (enum NintendoWfcMainState (*)(NintendoWfcConnect *))NintendoWfc_StartDisconnect,
    (enum NintendoWfcMainState (*)(NintendoWfcConnect *))NintendoWfc_StartExit,
    (enum NintendoWfcMainState (*)(NintendoWfcConnect *))NintendoWfc_WaitMessage,
    (enum NintendoWfcMainState (*)(NintendoWfcConnect *))NintendoWfc_OpenYesNoMenu,
    (enum NintendoWfcMainState (*)(NintendoWfcConnect *))NintendoWfc_WaitMessageAndDelay,
    (enum NintendoWfcMainState (*)(NintendoWfcConnect *))NintendoWfc_UnusedState_HandleYesNo,
    (enum NintendoWfcMainState (*)(NintendoWfcConnect *))NintendoWfc_AskLogOut,
    (enum NintendoWfcMainState (*)(NintendoWfcConnect *))NintendoWfc_HandleLogOutChoice,
    (enum NintendoWfcMainState (*)(NintendoWfcConnect *))NintendoWfc_ShowHttpError,
    (enum NintendoWfcMainState (*)(NintendoWfcConnect *))NintendoWfc_Disconnect,
    (enum NintendoWfcMainState (*)(NintendoWfcConnect *))NintendoWfc_ShowDwcError,
    (enum NintendoWfcMainState (*)(NintendoWfcConnect *))NintendoWfc_WaitErrorDismiss,
};
// clang-format on

const u8 gNintendoWfcPadNeighbors[13][4] = {
    { 0x0A, 0x05, 0x04, 0x01 },
    { 0x0A, 0x06, 0x00, 0x02 },
    { 0x0B, 0x07, 0x01, 0x03 },
    { 0x0C, 0x08, 0x02, 0x04 },
    { 0x0C, 0x09, 0x03, 0x00 },
    { 0x00, 0x0A, 0x09, 0x06 },
    { 0x01, 0x0A, 0x05, 0x07 },
    { 0x02, 0x0B, 0x06, 0x08 },
    { 0x03, 0x0C, 0x07, 0x09 },
    { 0x04, 0x0C, 0x08, 0x05 },
    { 0x0D, 0x0E, 0x0C, 0x0B },
    { 0x07, 0x02, 0x0A, 0x0C },
    { 0x0F, 0x10, 0x0B, 0x0A },
};

const NintendoWfcPadKeyFlash gNintendoWfcPadKeyFlashes[10] = {
    { 0x01, 0x07 },
    { 0x07, 0x07 },
    { 0x0D, 0x07 },
    { 0x13, 0x07 },
    { 0x19, 0x07 },
    { 0x01, 0x0D },
    { 0x07, 0x0D },
    { 0x0D, 0x0D },
    { 0x13, 0x0D },
    { 0x19, 0x0D },
};

// C declares this const, but it lives in .data
NintendoWfcScreenFuncs gNintendoWfcScreens[1] = {
    { NintendoWfc_SessionInit, NintendoWfc_SessionMain, NintendoWfc_SessionExit },
};

const int gNintendoWfcNumberInputWindowX[3] = { 1, 12, 23 };

// C declares this as `const u8 gNintendoWfcPadKeysUpFromLeftButton[]`, but MWCC gives a char array a
// section of its own, which the linker starts 4-aligned; to stay at offset 0x134 next to its
// neighbours it is written as the only row of a 2-D array, which shares their section.
const u8 gNintendoWfcPadKeysUpFromLeftButton[1][2] = {
    { 0x05, 0x06 }
};

// C declares this as `const u8 gNintendoWfcPadKeysUpFromRightButton[]`, but MWCC gives a char array a
// section of its own, which the linker starts 4-aligned; to stay at offset 0x138 next to its
// neighbours it is written as the only row of a 2-D array, which shares their section.
const u8 gNintendoWfcPadKeysUpFromRightButton[1][2] = {
    { 0x08, 0x09 }
};

// C declares this as `const u8 gNintendoWfcPadKeysDownFromLeftButton[]`, but MWCC gives a char array a
// section of its own, which the linker starts 4-aligned; to stay at offset 0x136 next to its
// neighbours it is written as the only row of a 2-D array, which shares their section.
const u8 gNintendoWfcPadKeysDownFromLeftButton[1][2] = {
    { 0x00, 0x01 }
};

// C declares this as `const u8 gNintendoWfcPadKeysDownFromRightButton[]`, but MWCC gives a char array
// a section of its own, which the linker starts 4-aligned; to stay at offset 0x13a next to its
// neighbours it is written as the only row of a 2-D array, which shares their section.
const u8 gNintendoWfcPadKeysDownFromRightButton[1][2] = {
    { 0x03, 0x04 }
};

// Also holds the asm labels gNintendoWfcHttpUploadFriendKey (+0x1b). MWCC sorts a file's objects by
// size and the linker starts every section 4-aligned, so no arrangement of separate objects puts
// them where the asm has them; the code has to reach them through ov72_0223B900.
// C declares this as `u8 ov72_0223B900[]`, but that type does not describe the data.
#ifndef SDK_PORT // part of gNintendoWfcHttp on the port (nintendo_wfc_connect_internal.h)
u8 ov72_0223B900[32];
#endif
