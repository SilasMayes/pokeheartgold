#ifndef POKEHEARTGOLD_BATTLE_LINK_COMM_H
#define POKEHEARTGOLD_BATTLE_LINK_COMM_H
#include "global.h"

#include "battle/battle_system.h"

#include "render_window.h"

// Work of the link data exchange stage (BSTATE_LINK_INIT/MAIN): the battle setup data the linked players exchange
// before the battle, one command at a time through the buffer.
typedef struct BattleLinkWork {
    BattleSetup *setup;
    BgConfig *bgConfig;
    Window *window;
    PaletteData *palette;
    SavePalPad *friends[4];
    union {
        u32 words[1024];
        Trainer trainer;
        SOUND_CHATOT chatot;
        SavePalPad palPad;
    } buffer;
    u8 received;
    u8 state;
    u16 timer;
    WaitingIcon *waitingIcon;
} BattleLinkWork;
typedef struct BattleLinkTask {
    BattleSystem *battle;
    u8 state;
} BattleLinkTask;
typedef struct BattleLinkHeader {
    u8 command, battler;
    u16 size;
} BattleLinkHeader;
// Entry of the battle link command table (Comm_RegisterCommandTable): each receive function takes the context the
// table was registered with (the BattleSystem during the battle, the BattleLinkWork while the setup is exchanged).
typedef struct BattleLinkCommand {
    void (*recv)();
    u32 (*getSize)(void);
    void *(*getBuffer)();
} BattleLinkCommand;

// LinkSync_StartSync / LinkSync_IsSynced ids of the link data exchange: each send waits for its sync
enum BattleLinkSync {
    BATTLE_LINK_SYNC_START = 50,
    BATTLE_LINK_SYNC_AI_FLAGS,
    BATTLE_LINK_SYNC_PROFILE,
    BATTLE_LINK_SYNC_TRAINER,
    BATTLE_LINK_SYNC_PARTY,
    BATTLE_LINK_SYNC_CHATOT,
    BATTLE_LINK_SYNC_PAL_PAD,
    BATTLE_LINK_SYNC_PARTNER_TRAINER_1,
    BATTLE_LINK_SYNC_PARTNER_TRAINER_3,
    BATTLE_LINK_SYNC_PARTNER_PARTY_1,
    BATTLE_LINK_SYNC_PARTNER_PARTY_3,
};

extern const BattleLinkCommand gBattleLinkCommands[];
int Comm_GetSendBufferFreeSpace(void);
BOOL Comm_SendCommandNoCopy(int command, void *data, int size);
BOOL BattleController_RecvLinkData(BattleSystem *battle, u8 *data);
void BattleLink_Start(BattleSystem *battle);
void BattleLink_RegisterSetupCommands(BattleLinkWork *work);
void BattleLink_QueueSendData(BattleSystem *battle, int command, int battler, const u8 *data, u8 size);
BOOL BattleLink_SendAiFlags(BattleLinkWork *work, u32 value, ...);
BOOL BattleLink_PrepareProfile(BattleLinkWork *work);
BOOL BattleLink_SendProfile(BattleLinkWork *work);
BOOL BattleLink_PrepareTrainer(BattleLinkWork *work);
BOOL BattleLink_SendTrainer(BattleLinkWork *work);
BOOL BattleLink_PrepareParty(BattleLinkWork *work);
BOOL BattleLink_SendParty(BattleLinkWork *work);
BOOL BattleLink_PrepareChatot(BattleLinkWork *work);
BOOL BattleLink_SendChatot(BattleLinkWork *work);
BOOL BattleLink_PreparePalPad(BattleLinkWork *work);
BOOL BattleLink_SendPalPad(BattleLinkWork *work);
BOOL BattleLink_PreparePartnerTrainer(BattleLinkWork *work, int index);
BOOL BattleLink_SendPartnerTrainer(BattleLinkWork *work, int index, int syncId);
BOOL BattleLink_PreparePartnerParty(BattleLinkWork *work, int index);
BOOL BattleLink_SendPartnerParty(BattleLinkWork *work, int index, int syncId);

#endif
