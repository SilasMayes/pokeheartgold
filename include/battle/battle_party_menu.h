#ifndef POKEHEARTGOLD_BATTLE_BATTLE_PARTY_MENU_H
#define POKEHEARTGOLD_BATTLE_BATTLE_PARTY_MENU_H

#include "battle/battle.h"

#include "bg_window.h"
#include "dpad_menu_box.h"
#include "party.h"
#include "sprite_system.h"

enum BattlePartyMode {
    BATTLE_PARTY_MODE_SWITCH,
    BATTLE_PARTY_MODE_SWITCH_NO_CANCEL,
    BATTLE_PARTY_MODE_USE_ITEM,
    BATTLE_PARTY_MODE_LEARN_MOVE,
};

// Arguments of the in-battle party screen, filled by the battle controller before
// BattlePartyMenu_Create and read back once `done` is set.
typedef struct BattlePartyContext {
    Party *party;
    void *unk_04;
    BattleSystem *battleSystem;
    enum HeapID heapID;
    u8 unk_10;
    u8 selectedMon; // party slot picked, 6 for cancel
    u8 reservedMon; // party index the partner battler already chose to send out, 6 for none (msg 93)
    u8 unk_13;
    u8 battlingMons[2]; // party indices of the mons on the field (msg 76)
    u8 unk_16[2];
    BOOL embargo[2]; // the mon on the field in that slot is under Embargo (msg 95)
    u16 hpRestored;  // HP restored by the item used, for the battle message
    u16 item;        // item being used (BATTLE_PARTY_MODE_USE_ITEM)
    u16 move;        // move to learn (BATTLE_PARTY_MODE_LEARN_MOVE); in switch mode non-zero when the battler cannot switch out (msg 78)
    u8 unk_26[2];
    int battlerId;
    u8 partyOrder[6]; // party index of each slot on the screen
    u8 cursorActive;  // d-pad cursor state, kept between openings
    u8 pocket;        // battle pocket of item
    u8 selectedMove;  // move slot picked, 4 for the move to learn
    u8 mode;          // enum BattlePartyMode
    u8 done;          // set when the screen has closed
} BattlePartyContext;

typedef struct BattlePartyMenuPos {
    int x;
    int y;
} BattlePartyMenuPos;

extern const u32 gBattlePartyMoveNameMsgIds[];
extern const u32 gBattlePartyMonNameMsgIds[];
extern const WindowTemplate gBattlePartyMonMenuWindows[];
extern const WindowTemplate gBattlePartyRestorePPWindows[];
extern const WindowTemplate gBattlePartyLearnMoveWindows[];
extern const WindowTemplate gBattlePartyWindowTemplates[];
extern const WindowTemplate gBattlePartyContestForgetMoveWindows[];
extern const WindowTemplate gBattlePartyCheckMovesWindows[];
extern const WindowTemplate gBattlePartyForgetMoveWindows[];
extern const WindowTemplate gBattlePartyMoveDetailWindows[];
extern const WindowTemplate gBattlePartyPartyListWindows[];
extern const WindowTemplate gBattlePartySummaryWindows[];
extern const BattlePartyMenuPos gBattlePartyForgetMoveTypeIconPos[];
extern const BattlePartyMenuPos gBattlePartyLearnMoveTypeIconPos[];
extern const BattlePartyMenuPos gBattlePartyCheckMovesTypeIconPos[];
extern const BattlePartyMenuPos gBattlePartyMoveDetailTypeIconPos[];
extern const BattlePartyMenuPos gBattlePartySummaryTypeIconPos[];
extern const BattlePartyMenuPos gBattlePartyCheckMovesMoveIconPos[];
extern const BattlePartyMenuPos gBattlePartyLearnMoveMoveIconPos[];
extern const BattlePartyMenuPos gBattlePartyListIconPos[];
extern const BattlePartyMenuPos gBattlePartyListStatusIconPos[];
extern const SpriteResourceCountsListUnion gBattlePartySpriteCapacities;
// {char, palette, cell, anim, draw priority} per sprite
extern const int gBattlePartySpriteTemplates[][5];
extern const u8 gBattlePartyButtonScrollAmounts[];
extern const u8 gBattlePartySlotButtonScrollAmounts[];
extern const s16 gBattlePartyButtonSpriteOffsets[];
extern const s16 gBattlePartySlotButtonSpriteOffsets[];
extern const u8 *const gBattlePartyButtonWindowLists[];
// {x, y, width, height} of each button on the bottom screen tilemap
extern const u8 gBattlePartyButtonRects[][4];
extern const DpadMenuBox *const gBattlePartyPageCursorBoxes[];

void BattlePartyMenu_Create(BattlePartyContext *context);

#endif // POKEHEARTGOLD_BATTLE_BATTLE_PARTY_MENU_H
