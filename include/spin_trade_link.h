#ifndef POKEHEARTGOLD_SPIN_TRADE_LINK_H
#define POKEHEARTGOLD_SPIN_TRADE_LINK_H

#include "global.h"

#include "field_types_def.h"
#include "game_stats.h"
#include "heap.h"
#include "options.h"
#include "save.h"

// Link commands (SpinTradeLink_SendCommand), each with its handler in spin_trade_link.c
enum SpinTradeLinkCommand {
    SPIN_TRADE_CMD_MEMBER_JOINED,
    SPIN_TRADE_CMD_CLEAR_MESSAGE,
    SPIN_TRADE_CMD_JOIN_REQUEST,
    SPIN_TRADE_CMD_CLOSE_YES_NO,
    SPIN_TRADE_CMD_JOIN_NOTICE,
    SPIN_TRADE_CMD_START_SYNC,
    SPIN_TRADE_CMD_SYNC_COUNT,
    SPIN_TRADE_CMD_LEADER_MENU_STATE,
    SPIN_TRADE_CMD_STATUS,
    SPIN_TRADE_CMD_JOIN,
    SPIN_TRADE_CMD_JUMP,
    SPIN_TRADE_CMD_SPIN,
    SPIN_TRADE_CMD_SLOT,
    SPIN_TRADE_CMD_COUNT,
    SPIN_TRADE_CMD_TRADE_SLOT,
    SPIN_TRADE_CMD_RESULT,
    SPIN_TRADE_CMD_CANCEL,
    SPIN_TRADE_CMD_CONFIRM,
};

typedef struct SpinTradeCommonArgs {
    u8 sendData[4];
    u32 frame;
    SaveData *saveData;
    struct UnionRoomObjects *communication;
    Options *options;
    GameStats *gameStats;
    FieldSystem *fieldSystem;
} SpinTradeCommonArgs;

typedef struct SpinTradeArgs {
    u32 unk_00;
    u32 partySlot;
    u32 playerCount;
    u32 memberMask;
    u32 result;
    SpinTradeCommonArgs input;
    struct SpinTradeLink *menu;
    struct SpinTradeApp *tradeApp;
    struct SpinTradeGroupApp *groupApp;
} SpinTradeArgs;

typedef struct SpinTradeLinkPacket {
    u32 command;
    u8 data[20];
} SpinTradeLinkPacket;

typedef struct SpinTradeLink {
    SpinTradeArgs *parent;
    SpinTradeLinkPacket packet;
    u32 blocked, count, state, leaderJoinPending, participantCount, leavingMask, unk34;
    u16 assignedCount;
    u16 unk3A;
    u32 unk3C;
    u16 receivedStatus, memberMask, flags44;
    s16 partyReceivedMask;
    u16 cancelMask, confirmMask;
    u8 *partyRecvBuffer; // the link layer receives each member's party here
    u8 *parties;         // then SpinTradeLink_ReceiveParty copies it here
    u32 unk54;
} SpinTradeLink;

SpinTradeLink *SpinTradeLink_New(SpinTradeArgs *parent, enum HeapID heap);
void SpinTradeLink_RegisterCommands(SpinTradeLink *link);
BOOL SpinTradeLink_SendCommand(SpinTradeLink *link, u32 command, void *data, u32 size);
void *SpinTradeLink_GetReceivedParty(SpinTradeLink *link, int sender);
void SpinTradeLink_Close(SpinTradeLink *link);
void SpinTradeLink_Free(SpinTradeLink *link);

#endif
