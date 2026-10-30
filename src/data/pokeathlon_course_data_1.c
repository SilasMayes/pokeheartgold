// Converted from asm/pokeathlon_course_data.s (part 1 of 2) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

// The C declarations of these do not match the data (see the notes at each
// definition): keep them out of the way of the definitions below.
#define gPokeathlonCourseEventSteps   gPokeathlonCourseEventSteps_header_decl
#define gPokeathlonCourseEvents       gPokeathlonCourseEvents_header_decl
#define sPokeathlonStateInfoFuncTable sPokeathlonStateInfoFuncTable_header_decl

#include "global.h"

#include "pokeathlon/pokeathlon_course_internal.h"

#pragma force_active on

#undef gPokeathlonCourseEventSteps
#undef gPokeathlonCourseEvents
#undef sPokeathlonStateInfoFuncTable

FS_EXTERN_OVERLAY(OVY_97);

extern void PokeathlonBlockSmash_Draw(void);
extern void PokeathlonBlockSmash_Exit(void);
extern void PokeathlonBlockSmash_Init(void);
extern void PokeathlonBlockSmash_ShowResults(void);
extern void PokeathlonBox_Exit(void);
extern void PokeathlonBox_Init(void);
extern void PokeathlonBox_Main(void);
extern void PokeathlonCirclePush_CalcResults(void);
extern void PokeathlonCirclePush_Exit(void);
extern void PokeathlonCirclePush_Init(void);
extern void PokeathlonCirclePush_Main(void);
extern void PokeathlonCourseClosing_Exit(void);
extern void PokeathlonCourseClosing_Init(void);
extern void PokeathlonCourseClosing_Main(void);
extern void PokeathlonCourseOpening_Exit(void);
extern void PokeathlonCourseOpening_Init(void);
extern void PokeathlonCourseOpening_Main(void);
extern void PokeathlonCourseWait_Exit(void);
extern void PokeathlonCourseWait_Init(void);
extern void PokeathlonCourseWait_Main(void);
extern void PokeathlonDiscCatch_Draw(void);
extern void PokeathlonDiscCatch_Exit(void);
extern void PokeathlonDiscCatch_Init(void);
extern void PokeathlonDiscCatch_ShowResults(void);
extern void PokeathlonEventIntro_Exit(void);
extern void PokeathlonEventIntro_Init(void);
extern void PokeathlonEventIntro_Main(void);
extern void PokeathlonGoalRoll_Draw(void);
extern void PokeathlonGoalRoll_Exit(void);
extern void PokeathlonGoalRoll_Init(void);
extern void PokeathlonGoalRoll_ShowResults(void);
extern void PokeathlonHurdleDash_Draw(void);
extern void PokeathlonHurdleDash_Exit(void);
extern void PokeathlonHurdleDash_Init(void);
extern void PokeathlonHurdleDash_ShowResults(void);
extern void PokeathlonLampJump_Draw(void);
extern void PokeathlonLampJump_Exit(void);
extern void PokeathlonLampJump_Init(void);
extern void PokeathlonLampJump_ShowResults(void);
extern void PokeathlonPennantCapture_Draw(void);
extern void PokeathlonPennantCapture_Exit(void);
extern void PokeathlonPennantCapture_Init(void);
extern void PokeathlonPennantCapture_ShowResults(void);
extern void PokeathlonRelayRun_Draw(void);
extern void PokeathlonRelayRun_Exit(void);
extern void PokeathlonRelayRun_Init(void);
extern void PokeathlonRelayRun_ShowResults(void);
extern void PokeathlonResults_Draw(void);
extern void PokeathlonResults_Exit(void);
extern void PokeathlonResults_Init(void);
extern void PokeathlonRingDrop_Draw(void);
extern void PokeathlonRingDrop_Exit(void);
extern void PokeathlonRingDrop_Init(void);
extern void PokeathlonRingDrop_ShowResults(void);
extern void PokeathlonSnowThrow_Draw(void);
extern void PokeathlonSnowThrow_Exit(void);
extern void PokeathlonSnowThrow_Init(void);
extern void PokeathlonSnowThrow_ShowResults(void);
extern const u8 gPokeathlonBlockSmashStates[];
extern const u8 gPokeathlonCirclePushStates[];
extern const u8 gPokeathlonDiscCatchStates[];
extern const u8 gPokeathlonGoalRollStates[];
extern const u8 gPokeathlonHurdleDashStates[];
extern const u8 gPokeathlonLampJumpStates[];
extern const u8 gPokeathlonPennantCaptureStates[];
extern const u8 gPokeathlonRelayRunStates[];
extern const u8 gPokeathlonRingDropStates[];
extern const u8 gPokeathlonSnowThrowStates[];

extern const PokeathlonCourseEvent gPokeathlonHurdleDashEvent;
extern const PokeathlonCourseEvent gPokeathlonPennantCaptureEvent;
extern const PokeathlonCourseEvent gPokeathlonCirclePushEvent;
extern const PokeathlonCourseEvent gPokeathlonBlockSmashEvent;
extern const PokeathlonCourseEvent gPokeathlonDiscCatchEvent;
extern const PokeathlonCourseEvent gPokeathlonLampJumpEvent;
extern const PokeathlonCourseEvent gPokeathlonRelayRunEvent;
extern const PokeathlonCourseEvent gPokeathlonRingDropEvent;
extern const PokeathlonCourseEvent gPokeathlonSnowThrowEvent;
extern const PokeathlonCourseEvent gPokeathlonGoalRollEvent;

// clang-format off
const u16 gPokeathlonPerformanceFileIds[494] = {
    0, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0xA, 0xB, 0xC, 0xD, 0xE, 0xF, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16,
    0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27,
    0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38,
    0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F, 0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49,
    0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F, 0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5A,
    0x5B, 0x5C, 0x5D, 0x5E, 0x5F, 0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6A, 0x6B,
    0x6C, 0x6D, 0x6E, 0x6F, 0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7A, 0x7B, 0x7C,
    0x7D, 0x7E, 0x7F, 0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D,
    0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98, 0x99, 0x9A, 0x9B, 0x9C, 0x9D, 0x9E,
    0x9F, 0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAD, 0xAE, 0xAF, 0xB0,
    0xB1, 0xB2, 0xB3, 0xB4, 0xB5, 0xB6, 0xB7, 0xB8, 0xB9, 0xBA, 0xBB, 0xBC, 0xBD, 0xBE, 0xBF, 0xC0, 0xC1,
    0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xE5, 0xE6, 0xE7, 0xE8, 0xE9, 0xEA, 0xEB, 0xEC, 0xED,
    0xEE, 0xEF, 0xF0, 0xF1, 0xF2, 0xF3, 0xF4, 0xF5, 0xF6, 0xF7, 0xF8, 0xF9, 0xFA, 0xFB, 0xFC, 0xFD, 0xFE,
    0xFF, 0x100, 0x101, 0x102, 0x103, 0x104, 0x105, 0x106, 0x107, 0x108, 0x109, 0x10A, 0x10B, 0x10C, 0x10D,
    0x10E, 0x10F, 0x110, 0x111, 0x112, 0x113, 0x114, 0x115, 0x116, 0x117, 0x118, 0x119, 0x11A, 0x11B, 0x11C,
    0x11D, 0x11E, 0x11F, 0x120, 0x121, 0x122, 0x123, 0x124, 0x125, 0x126, 0x127, 0x128, 0x129, 0x12A, 0x12B,
    0x12C, 0x12D, 0x12E, 0x12F, 0x130, 0x131, 0x132, 0x133, 0x134, 0x135, 0x136, 0x137, 0x138, 0x139, 0x13A,
    0x13B, 0x13C, 0x13D, 0x13E, 0x13F, 0x140, 0x141, 0x142, 0x143, 0x144, 0x145, 0x146, 0x147, 0x148, 0x149,
    0x14A, 0x14B, 0x14C, 0x14D, 0x14E, 0x14F, 0x150, 0x151, 0x152, 0x153, 0x154, 0x155, 0x156, 0x157, 0x158,
    0x159, 0x15A, 0x15B, 0x15C, 0x15D, 0x15E, 0x15F, 0x160, 0x161, 0x162, 0x163, 0x164, 0x165, 0x166, 0x167,
    0x168, 0x169, 0x16A, 0x16B, 0x16C, 0x16D, 0x16E, 0x16F, 0x170, 0x171, 0x172, 0x173, 0x174, 0x175, 0x176,
    0x177, 0x178, 0x179, 0x17A, 0x17B, 0x17C, 0x17D, 0x17E, 0x17F, 0x180, 0x181, 0x182, 0x183, 0x184, 0x185,
    0x186, 0x187, 0x188, 0x189, 0x18A, 0x18B, 0x18C, 0x18D, 0x18E, 0x18F, 0x190, 0x191, 0x192, 0x193, 0x194,
    0x195, 0x196, 0x197, 0x198, 0x199, 0x19A, 0x19B, 0x19C, 0x19D, 0x1A1, 0x1A2, 0x1A3, 0x1A4, 0x1A5, 0x1A6,
    0x1A7, 0x1A8, 0x1A9, 0x1AA, 0x1AB, 0x1AC, 0x1AD, 0x1AE, 0x1AF, 0x1B0, 0x1B1, 0x1B2, 0x1B3, 0x1B4, 0x1B5,
    0x1B6, 0x1B7, 0x1B8, 0x1B9, 0x1BA, 0x1BD, 0x1C0, 0x1C1, 0x1C2, 0x1C3, 0x1C4, 0x1C5, 0x1C6, 0x1C7, 0x1C8,
    0x1CA, 0x1CC, 0x1CD, 0x1CE, 0x1CF, 0x1D0, 0x1D1, 0x1D2, 0x1D3, 0x1D4, 0x1D5, 0x1D6, 0x1D7, 0x1D8, 0x1D9,
    0x1DA, 0x1DB, 0x1DC, 0x1DD, 0x1DE, 0x1DF, 0x1E0, 0x1E1, 0x1E2, 0x1E3, 0x1E4, 0x1E5, 0x1E6, 0x1E7, 0x1E8,
    0x1E9, 0x1EA, 0x1EB, 0x1EC, 0x1ED, 0x1EE, 0x1EF, 0x1F0, 0x1F1, 0x1F2, 0x1F3, 0x1F4, 0x1F5, 0x1F6, 0x1F7,
    0x1F8, 0x1F9, 0x1FA, 0x1FB, 0x1FC, 0x1FD, 0x1FE, 0x1FF, 0x200, 0x201, 0x202, 0x203, 0x209, 0x20A, 0x20B,
    0x20C, 0x20D, 0x20E, 0x20F, 0x210, 0x212, 0x213, 0x214, 0x215, 0x216, 0x218,
};
// clang-format on

// clang-format off
const u16 gPokeathlonNpcTeamSpriteIds[POKEATHLON_NPC_TEAMS] = {
    0x140, 0x13F, 0x142, 0x143, 0x13D, 0x145, 0x147, 0x158, 0x155, 0x14C, 0x141, 0x146, 0x13E, 0x14A, 0x143,
    0x15A, 0x147, 0x14D, 0x158, 0x179, 0x149, 0x140, 0x15C, 0x15A, 0x159, 0x140, 0x13F, 0x142, 0x15A, 0x159,
    0x149, 0x140, 0x15C, 0x14A, 0x143, 0x141, 0x146, 0x13E, 0x155, 0x14C, 0x145, 0x147, 0x158, 0x158, 0x179,
    0x15A, 0x147, 0x14D, 0x143, 0x13D, 0x144, 0x162, 0x140, 0x158, 0x159, 0x180, 0x81, 0x145, 0x14C, 0x14D,
    0x155, 0x13D, 0x146, 0xE8, 0x17A, 0x165, 0x141, 0x179, 0x158, 0x13E, 0x142, 0x13F, 0x160, 0x15A, 0x155,
    0x144, 0x162, 0x140, 0x15A, 0x155, 0x142, 0x13F, 0x160, 0xE8, 0x17A, 0x155, 0x13D, 0x146, 0x14C, 0x14D,
    0x180, 0x81, 0x145, 0x158, 0x13E, 0x165, 0x141, 0x179, 0x159, 0x158,
};
// clang-format on

// The label holds 152 more bytes of data after it.
void (*const sPokeathlonStateInfoFuncTable[39])(void) = {
    (void (*)(void))PokeathlonCourse_State_SendEvents,
    (void (*)(void))PokeathlonCourse_State_RunEventOverlay,
    (void (*)(void))PokeathlonCourse_State_RunWait,
    (void (*)(void))PokeathlonCourse_State_SendParticipant,
    (void (*)(void))PokeathlonCourse_State_SendParticipants,
    (void (*)(void))PokeathlonCourse_State_SendProfiles,
    (void (*)(void))PokeathlonCourse_State_SendRecord,
    (void (*)(void))PokeathlonCourse_State_StartOpening,
    (void (*)(void))PokeathlonCourse_State_WaitOpeningStart,
    (void (*)(void))PokeathlonCourse_State_RunOpening,
    (void (*)(void))PokeathlonCourse_State_EndOpening,
    (void (*)(void))PokeathlonCourse_State_StartEventIntro,
    (void (*)(void))PokeathlonCourse_State_WaitEventIntroStart,
    (void (*)(void))PokeathlonCourse_State_RunEventIntro,
    (void (*)(void))PokeathlonCourse_State_EndEventIntro,
    (void (*)(void))PokeathlonCourse_State_StartRound,
    (void (*)(void))PokeathlonCourse_State_WaitRoundStart,
    (void (*)(void))PokeathlonCourse_State_SendEventData,
    (void (*)(void))PokeathlonCourse_State_RunEvent,
    (void (*)(void))PokeathlonCourse_State_ResetDataCopyArea,
    (void (*)(void))PokeathlonCourse_State_SendEventResult,
    (void (*)(void))PokeathlonCourse_State_SendEventResults,
    (void (*)(void))PokeathlonCourse_State_EndRound,
    (void (*)(void))PokeathlonCourse_State_ExitEvent,
    (void (*)(void))PokeathlonCourse_State_NextRound,
    (void (*)(void))PokeathlonCourse_State_StartResults,
    (void (*)(void))PokeathlonCourse_State_WaitResultsStart,
    (void (*)(void))PokeathlonCourse_State_RunResults,
    (void (*)(void))PokeathlonCourse_State_EndResults,
    (void (*)(void))PokeathlonCourse_State_SendMonCounters,
    (void (*)(void))PokeathlonCourse_State_SendResults,
    (void (*)(void))PokeathlonCourse_State_StartClosing,
    (void (*)(void))PokeathlonCourse_State_WaitClosingStart,
    (void (*)(void))PokeathlonCourse_State_RunClosing,
    (void (*)(void))PokeathlonCourse_State_CreateJuiceRecords,
    (void (*)(void))PokeathlonCourse_State_SendJuiceRecord,
    (void (*)(void))PokeathlonCourse_State_StoreJuiceRecords,
    (void (*)(void))PokeathlonCourse_State_Exit,
    (void (*)(void))PokeathlonCourse_State_WaitForCommand,
};

const u8 gPokeathlonCourseEventIds[10][POKEATHLON_LINK_ROUNDS] = {
    { 0x00, 0x01, 0x06, 0x0A },
    { 0x03, 0x02, 0x09, 0x0A },
    { 0x08, 0x09, 0x01, 0x0A },
    { 0x07, 0x06, 0x03, 0x0A },
    { 0x05, 0x04, 0x00, 0x0A },
    { 0x00, 0x05, 0x04, 0x06 },
    { 0x05, 0x04, 0x01, 0x08 },
    { 0x09, 0x08, 0x01, 0x03 },
    { 0x03, 0x02, 0x09, 0x07 },
    { 0x06, 0x07, 0x00, 0x02 },
};

const u8 gPokeathlonCourse10EventSets[POKEATHLON_RANDOM_EVENT_SETS][POKEATHLON_LINK_ROUNDS] = {
    { 0x04, 0x02, 0x09, 0x07 },
    { 0x07, 0x02, 0x03, 0x08 },
    { 0x05, 0x00, 0x09, 0x07 },
    { 0x03, 0x06, 0x08, 0x05 },
    { 0x08, 0x05, 0x03, 0x00 },
    { 0x01, 0x02, 0x09, 0x04 },
    { 0x02, 0x06, 0x05, 0x03 },
    { 0x00, 0x07, 0x03, 0x09 },
    { 0x09, 0x08, 0x04, 0x01 },
    { 0x06, 0x03, 0x07, 0x00 },
};

// C declares this const, but it lives in .data
// clang-format off
const PokeathlonCourseStepFunc *gPokeathlonCourseEventSteps[10] = {
    (const PokeathlonCourseStepFunc *const)gPokeathlonHurdleDashStates,
    (const PokeathlonCourseStepFunc *const)gPokeathlonPennantCaptureStates,
    (const PokeathlonCourseStepFunc *const)gPokeathlonCirclePushStates,
    (const PokeathlonCourseStepFunc *const)gPokeathlonBlockSmashStates,
    (const PokeathlonCourseStepFunc *const)gPokeathlonDiscCatchStates,
    (const PokeathlonCourseStepFunc *const)gPokeathlonLampJumpStates,
    (const PokeathlonCourseStepFunc *const)gPokeathlonRelayRunStates,
    (const PokeathlonCourseStepFunc *const)gPokeathlonRingDropStates,
    (const PokeathlonCourseStepFunc *const)gPokeathlonSnowThrowStates,
    (const PokeathlonCourseStepFunc *const)gPokeathlonGoalRollStates,
};
// clang-format on

// C declares this const, but it lives in .data
// clang-format off
const PokeathlonCourseEvent *gPokeathlonCourseEvents[10] = {
    &gPokeathlonHurdleDashEvent, &gPokeathlonPennantCaptureEvent,
    &gPokeathlonCirclePushEvent, &gPokeathlonBlockSmashEvent, &gPokeathlonDiscCatchEvent,
    &gPokeathlonLampJumpEvent, &gPokeathlonRelayRunEvent, &gPokeathlonRingDropEvent,
    &gPokeathlonSnowThrowEvent, &gPokeathlonGoalRollEvent,
};
// clang-format on

// clang-format off
const PokeathlonCourseEvent gPokeathlonHurdleDashEvent = {
    (BOOL (*)(PokeathlonCourseData *))PokeathlonHurdleDash_Init,
    (void (*)(PokeathlonCourseData *, u32))PokeathlonHurdleDash_Draw,
    (void (*)(PokeathlonCourseData *, u32))PokeathlonHurdleDash_ShowResults,
    (void (*)(PokeathlonCourseData *, u32))PokeathlonHurdleDash_Exit, 1,
};
// clang-format on

// clang-format off
const PokeathlonCourseEvent gPokeathlonSnowThrowEvent = {
    (BOOL (*)(PokeathlonCourseData *))PokeathlonSnowThrow_Init,
    (void (*)(PokeathlonCourseData *, u32))PokeathlonSnowThrow_Draw,
    (void (*)(PokeathlonCourseData *, u32))PokeathlonSnowThrow_ShowResults,
    (void (*)(PokeathlonCourseData *, u32))PokeathlonSnowThrow_Exit, 0,
};
// clang-format on

// clang-format off
const PokeathlonCourseEvent gPokeathlonCourseEvent_EventIntro = {
    (BOOL (*)(PokeathlonCourseData *))PokeathlonEventIntro_Init,
    (void (*)(PokeathlonCourseData *, u32))PokeathlonEventIntro_Main, NULL,
    (void (*)(PokeathlonCourseData *, u32))PokeathlonEventIntro_Exit, 0,
};
// clang-format on

// clang-format off
const PokeathlonCourseEvent gPokeathlonPennantCaptureEvent = {
    (BOOL (*)(PokeathlonCourseData *))PokeathlonPennantCapture_Init,
    (void (*)(PokeathlonCourseData *, u32))PokeathlonPennantCapture_Draw,
    (void (*)(PokeathlonCourseData *, u32))PokeathlonPennantCapture_ShowResults,
    (void (*)(PokeathlonCourseData *, u32))PokeathlonPennantCapture_Exit, 0,
};
// clang-format on

// clang-format off
const PokeathlonCourseEvent gPokeathlonCourseEvent_Wait = {
    (BOOL (*)(PokeathlonCourseData *))PokeathlonCourseWait_Init,
    (void (*)(PokeathlonCourseData *, u32))PokeathlonCourseWait_Main, NULL,
    (void (*)(PokeathlonCourseData *, u32))PokeathlonCourseWait_Exit, 0,
};
// clang-format on

// clang-format off
const PokeathlonCourseEvent gPokeathlonDiscCatchEvent = {
    (BOOL (*)(PokeathlonCourseData *))PokeathlonDiscCatch_Init,
    (void (*)(PokeathlonCourseData *, u32))PokeathlonDiscCatch_Draw,
    (void (*)(PokeathlonCourseData *, u32))PokeathlonDiscCatch_ShowResults,
    (void (*)(PokeathlonCourseData *, u32))PokeathlonDiscCatch_Exit, 0,
};
// clang-format on

// clang-format off
const PokeathlonCourseEvent gPokeathlonCirclePushEvent = {
    (BOOL (*)(PokeathlonCourseData *))PokeathlonCirclePush_Init,
    (void (*)(PokeathlonCourseData *, u32))PokeathlonCirclePush_Main,
    (void (*)(PokeathlonCourseData *, u32))PokeathlonCirclePush_CalcResults,
    (void (*)(PokeathlonCourseData *, u32))PokeathlonCirclePush_Exit, 0,
};
// clang-format on

// clang-format off
const PokeathlonCourseEvent gPokeathlonCourseEvent_Opening = {
    (BOOL (*)(PokeathlonCourseData *))PokeathlonCourseOpening_Init,
    (void (*)(PokeathlonCourseData *, u32))PokeathlonCourseOpening_Main, NULL,
    (void (*)(PokeathlonCourseData *, u32))PokeathlonCourseOpening_Exit, 0,
};
// clang-format on

// clang-format off
const PokeathlonCourseEvent gPokeathlonCourseEvent_ResultsAnnouncement = {
    (BOOL (*)(PokeathlonCourseData *))PokeathlonResults_Init,
    (void (*)(PokeathlonCourseData *, u32))PokeathlonResults_Draw, NULL,
    (void (*)(PokeathlonCourseData *, u32))PokeathlonResults_Exit, 0,
};
// clang-format on

// clang-format off
const PokeathlonCourseEvent gPokeathlonLampJumpEvent = {
    (BOOL (*)(PokeathlonCourseData *))PokeathlonLampJump_Init,
    (void (*)(PokeathlonCourseData *, u32))PokeathlonLampJump_Draw,
    (void (*)(PokeathlonCourseData *, u32))PokeathlonLampJump_ShowResults,
    (void (*)(PokeathlonCourseData *, u32))PokeathlonLampJump_Exit, 1,
};
// clang-format on

// clang-format off
const PokeathlonCourseEvent gPokeathlonRelayRunEvent = {
    (BOOL (*)(PokeathlonCourseData *))PokeathlonRelayRun_Init,
    (void (*)(PokeathlonCourseData *, u32))PokeathlonRelayRun_Draw,
    (void (*)(PokeathlonCourseData *, u32))PokeathlonRelayRun_ShowResults,
    (void (*)(PokeathlonCourseData *, u32))PokeathlonRelayRun_Exit, 0,
};
// clang-format on

// clang-format off
const PokeathlonCourseEvent gPokeathlonBlockSmashEvent = {
    (BOOL (*)(PokeathlonCourseData *))PokeathlonBlockSmash_Init,
    (void (*)(PokeathlonCourseData *, u32))PokeathlonBlockSmash_Draw,
    (void (*)(PokeathlonCourseData *, u32))PokeathlonBlockSmash_ShowResults,
    (void (*)(PokeathlonCourseData *, u32))PokeathlonBlockSmash_Exit, 1,
};
// clang-format on

const u16 gPokeathlonEventTargetScores[10] = { 3000, 35, 40, 80, 40, 350, 12288, 70, 30, 3 };

// clang-format off
const PokeathlonCourseEvent gPokeathlonRingDropEvent = {
    (BOOL (*)(PokeathlonCourseData *))PokeathlonRingDrop_Init,
    (void (*)(PokeathlonCourseData *, u32))PokeathlonRingDrop_Draw,
    (void (*)(PokeathlonCourseData *, u32))PokeathlonRingDrop_ShowResults,
    (void (*)(PokeathlonCourseData *, u32))PokeathlonRingDrop_Exit, 0,
};
// clang-format on

// clang-format off
const PokeathlonCourseEvent gPokeathlonCourseEvent_Closing = {
    (BOOL (*)(PokeathlonCourseData *))PokeathlonCourseClosing_Init,
    (void (*)(PokeathlonCourseData *, u32))PokeathlonCourseClosing_Main, NULL,
    (void (*)(PokeathlonCourseData *, u32))PokeathlonCourseClosing_Exit, 0,
};
// clang-format on

// clang-format off
const PokeathlonCourseEvent gPokeathlonGoalRollEvent = {
    (BOOL (*)(PokeathlonCourseData *))PokeathlonGoalRoll_Init,
    (void (*)(PokeathlonCourseData *, u32))PokeathlonGoalRoll_Draw,
    (void (*)(PokeathlonCourseData *, u32))PokeathlonGoalRoll_ShowResults,
    (void (*)(PokeathlonCourseData *, u32))PokeathlonGoalRoll_Exit, 0,
};
// clang-format on

const struct {
    void (*unk0)(void);
    void (*unk4)(void);
    void (*unk8)(void);
    u32 unkC;
} subOverlayTemplate = { PokeathlonBox_Init, PokeathlonBox_Main, PokeathlonBox_Exit, FS_OVERLAY_ID(OVY_97) };

// clang-format off
const u8 gPokeathlonEventScoreOrders[12] __attribute__((aligned(4))) = {
    0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0, 0, 0, 0,
};
// clang-format on
