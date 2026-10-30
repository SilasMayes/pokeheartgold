// Converted from asm/spin_trade_flow_data.s by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout. Keep that when editing, or rerun tools/s2c.py.

#include "global.h"

#pragma force_active on

FS_EXTERN_OVERLAY(OVY_85);

extern void SpinTradeApp_Exit(void);
extern void SpinTradeApp_Init(void);
extern void SpinTradeApp_Main(void);
extern void SpinTradeFlow_Finish(void);
extern void SpinTradeFlow_LaunchGroupApp(void);
extern void SpinTradeFlow_WaitGroupApp(void);
extern void SpinTradeFlow_WaitPartyMenu(void);
extern void SpinTradeFlow_WaitSpinTradeApp(void);
extern void SpinTradeFlow_WaitSummary(void);
extern void SpinTradeGroupApp_Exit(void);
extern void SpinTradeGroupApp_Init(void);
extern void SpinTradeGroupApp_Main(void);

void (*const gSpinTradeFlowStates[6])(void) = {
    SpinTradeFlow_LaunchGroupApp,
    SpinTradeFlow_WaitGroupApp,
    SpinTradeFlow_WaitPartyMenu,
    SpinTradeFlow_WaitSummary,
    SpinTradeFlow_WaitSpinTradeApp,
    SpinTradeFlow_Finish,
};

const struct {
    void (*unk0)(void);
    void (*unk4)(void);
    void (*unk8)(void);
    u32 unkC;
} gOverlayTemplate_SpinTradeGroup = {
    SpinTradeGroupApp_Init,
    SpinTradeGroupApp_Main,
    SpinTradeGroupApp_Exit,
    FS_OVERLAY_ID(OVY_85),
};

const struct {
    void (*unk0)(void);
    void (*unk4)(void);
    void (*unk8)(void);
    u32 unkC;
} gOverlayTemplate_SpinTrade = {
    SpinTradeApp_Init,
    SpinTradeApp_Main,
    SpinTradeApp_Exit,
    FS_OVERLAY_ID(OVY_85),
};
