// Converted from asm/spin_trade_data.s (part 6 of 6) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

// The C declarations of these do not match the data (see the notes at each
// definition): keep them out of the way of the definitions below.
#define gSpinTradeBonusBerryRanges    gSpinTradeBonusBerryRanges_header_decl
#define gSpinTradeBonusBerryRangeEnds gSpinTradeBonusBerryRangeEnds_header_decl

#include "global.h"

#pragma force_active on

#undef gSpinTradeBonusBerryRanges
#undef gSpinTradeBonusBerryRangeEnds

extern void SpinTrade_State_AlignToSlot(void);
extern void SpinTrade_State_BeginSpin(void);
extern void SpinTrade_State_Cancel(void);
extern void SpinTrade_State_CheckEggs(void);
extern void SpinTrade_State_ClearNames(void);
extern void SpinTrade_State_DropEggs(void);
extern void SpinTrade_State_Exit(void);
extern void SpinTrade_State_FadeOut(void);
extern void SpinTrade_State_GiveBonusBerry(void);
extern void SpinTrade_State_ReceiveResult(void);
extern void SpinTrade_State_RotateToOwnEgg(void);
extern void SpinTrade_State_Save(void);
extern void SpinTrade_State_SendJoin(void);
extern void SpinTrade_State_SendParty(void);
extern void SpinTrade_State_SendPlayerCount(void);
extern void SpinTrade_State_SendReady(void);
extern void SpinTrade_State_SendResult(void);
extern void SpinTrade_State_SendSlots(void);
extern void SpinTrade_State_SendSpinStart(void);
extern void SpinTrade_State_SendStart(void);
extern void SpinTrade_State_SendTradeSlot(void);
extern void SpinTrade_State_SetupDrop(void);
extern void SpinTrade_State_ShowBagFull(void);
extern void SpinTrade_State_ShowNames(void);
extern void SpinTrade_State_ShowReceivedEgg(void);
extern void SpinTrade_State_SpinClient(void);
extern void SpinTrade_State_SpinHost(void);
extern void SpinTrade_State_Start(void);
extern void SpinTrade_State_StartCountdown(void);
extern void SpinTrade_State_StartExitSync(void);
extern void SpinTrade_State_StartResultSync(void);
extern void SpinTrade_State_StartSave(void);
extern void SpinTrade_State_StartSpinSync(void);
extern void SpinTrade_State_StartSync(void);
extern void SpinTrade_State_StopSpin(void);
extern void SpinTrade_State_Wait(void);
extern void SpinTrade_State_WaitBeforeSpin(void);
extern void SpinTrade_State_WaitBerryFanfare(void);
extern void SpinTrade_State_WaitCancelMessage(void);
extern void SpinTrade_State_WaitConfirm(void);
extern void SpinTrade_State_WaitConnections(void);
extern void SpinTrade_State_WaitDisconnect(void);
extern void SpinTrade_State_WaitEggFanfare(void);
extern void SpinTrade_State_WaitEggsLanded(void);
extern void SpinTrade_State_WaitExitSync(void);
extern void SpinTrade_State_WaitFadeIn(void);
extern void SpinTrade_State_WaitFadeOut(void);
extern void SpinTrade_State_WaitMembers(void);
extern void SpinTrade_State_WaitReady(void);
extern void SpinTrade_State_WaitResultSync(void);
extern void SpinTrade_State_WaitSaveSync(void);
extern void SpinTrade_State_WaitSpinStart(void);
extern void SpinTrade_State_WaitSpinSync(void);
extern void SpinTrade_State_WaitSync(void);

extern const u8 gSpinTradeBonusRanges2P[];
extern const u8 gSpinTradeBonusRanges3P[8];
extern const u8 gSpinTradeBonusRanges4P[8];
extern const u8 gSpinTradeBonusRanges5P[16];

// 0x021EA800
void (*const gSpinTradeStateFuncs[54])(void) = {
    SpinTrade_State_Start,
    SpinTrade_State_WaitFadeIn,
    SpinTrade_State_WaitMembers,
    SpinTrade_State_SendStart,
    SpinTrade_State_WaitConnections,
    SpinTrade_State_SendPlayerCount,
    SpinTrade_State_SendSlots,
    SpinTrade_State_SendReady,
    SpinTrade_State_SendJoin,
    SpinTrade_State_WaitReady,
    SpinTrade_State_StartSync,
    SpinTrade_State_WaitSync,
    SpinTrade_State_SendTradeSlot,
    SpinTrade_State_SendParty,
    SpinTrade_State_CheckEggs,
    SpinTrade_State_WaitConfirm,
    SpinTrade_State_SetupDrop,
    SpinTrade_State_DropEggs,
    SpinTrade_State_WaitEggsLanded,
    SpinTrade_State_WaitBeforeSpin,
    SpinTrade_State_SendSpinStart,
    SpinTrade_State_WaitSpinStart,
    SpinTrade_State_StartSpinSync,
    SpinTrade_State_WaitSpinSync,
    SpinTrade_State_StartCountdown,
    SpinTrade_State_ClearNames,
    SpinTrade_State_BeginSpin,
    SpinTrade_State_SpinHost,
    SpinTrade_State_SpinClient,
    SpinTrade_State_StopSpin,
    SpinTrade_State_RotateToOwnEgg,
    SpinTrade_State_AlignToSlot,
    SpinTrade_State_StartResultSync,
    SpinTrade_State_WaitResultSync,
    SpinTrade_State_SendResult,
    SpinTrade_State_ReceiveResult,
    SpinTrade_State_ShowNames,
    SpinTrade_State_ShowReceivedEgg,
    SpinTrade_State_WaitEggFanfare,
    SpinTrade_State_GiveBonusBerry,
    SpinTrade_State_WaitBerryFanfare,
    SpinTrade_State_ShowBagFull,
    SpinTrade_State_Wait,
    SpinTrade_State_StartSave,
    SpinTrade_State_WaitSaveSync,
    SpinTrade_State_Save,
    SpinTrade_State_Cancel,
    SpinTrade_State_WaitCancelMessage,
    SpinTrade_State_StartExitSync,
    SpinTrade_State_WaitExitSync,
    SpinTrade_State_WaitDisconnect,
    SpinTrade_State_FadeOut,
    SpinTrade_State_WaitFadeOut,
    SpinTrade_State_Exit,
};

// 0x021EA788
const u16 gSpinTradeSlotAngles[6][5] = {
    { 0, 0,      0,      0,      0      },
    { 0, 0,      0,      0,      0      },
    { 0, 0x00B4, 0,      0,      0      },
    { 0, 0x00F0, 0x0078, 0,      0      },
    { 0, 0x010E, 0x00B4, 0x005A, 0      },
    { 0, 0x0120, 0x00D8, 0x0090, 0x0048 },
};

// 0x021EA7C4
const u16 gSpinTradeDropTargetAngles[6][5] = {
    { 0,      0,      0,      0,      0      },
    { 0,      0,      0,      0,      0      },
    { 0x005A, 0x010E, 0,      0,      0      },
    { 0x005A, 0x00D2, 0x014A, 0,      0      },
    { 0x005A, 0x00B4, 0x010E, 0,      0      },
    { 0x005A, 0x00A2, 0x00EA, 0x0132, 0x0012 },
};

// 0x021EA758
const struct {
    u32 unk0;
    const void *unk4;
} gSpinTradeBonusAreas[6] = {
    { 0, NULL                    },
    { 0, NULL                    },
    { 1, gSpinTradeBonusRanges2P },
    { 2, gSpinTradeBonusRanges3P },
    { 2, gSpinTradeBonusRanges4P },
    { 2, gSpinTradeBonusRanges5P },
};

#ifdef SDK_PORT
// clang-format off
u32 gSpinTradeBonusBerryRangeEnds[6][2] = { { 0, 0 }, { 0, 0x9F }, { 0xA3, 0x9F }, { 0xA3, 0xA4 }, { 0xA8, 0xAF }, { 0xB7, 0 } };
// clang-format on
#else
// 0x021EA72C
// The label holds 4 more bytes of data after it.
// clang-format off
const u8 gSpinTradeBonusBerryRangeEnds[44] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x9F, 0x00, 0x00, 0x00,
    0xA3, 0x00, 0x00, 0x00, 0x9F, 0x00, 0x00, 0x00, 0xA3, 0x00, 0x00, 0x00, 0xA4, 0x00, 0x00, 0x00,
    0xA8, 0x00, 0x00, 0x00, 0xAF, 0x00, 0x00, 0x00, 0xB7, 0x00, 0x00, 0x00,
};
// clang-format on
#endif

#ifdef SDK_PORT
// On the DS both labels are one u32[6][2] table ({first, last} berry by player count), the
// second read from its last member; the port has a complete copy for each (non-const as
// declared).
// clang-format off
u32 gSpinTradeBonusBerryRanges[6][2] = { { 0, 0 }, { 0, 0 }, { 0x9F, 0xA3 }, { 0x9F, 0xA3 }, { 0xA4, 0xA8 }, { 0xAF, 0xB7 } };
// clang-format on
#else
// 0x021EA728
// One element of that type is larger than the data under this label.
const u8 gSpinTradeBonusBerryRanges[4] = { 0x00, 0x00, 0x00, 0x00 };
#endif
