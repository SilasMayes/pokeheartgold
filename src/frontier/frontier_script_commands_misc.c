#include "global.h"

#include "constants/game_stats.h"
#include "constants/sndseq.h"

#include "frontier/battle_tower_setup.h"
#include "frontier/frontier.h"
#include "frontier/frontier_script_commands.h"
#include "frontier/frontier_script_context.h"
#include "frontier/frontier_script_ui.h"
#include "frontier/frontier_scrcmd.h"

#include "communication_core.h"
#include "frontier_field_system.h"
#include "frontier_save_data_helpers_internal.h"
#include "frontier_script_commands_misc_internal.h"
#include "game_stats.h"
#include "launch_application.h"
#include "link_synchronization.h"
#include "scrcmd_9.h"
#include "sound_playback.h"
#include "sound_system.h"

static u32 BattleTower_GetOverworldSprite(FrontierFieldSystem *tower, u32 mode);
static BOOL FrontierScriptNative_WaitPartnerPacket(FrontierScriptContext *ctx);
static BOOL FrontierScript_ReadPartnerPacket(FrontierScriptContext *ctx, FrontierFieldSystem *tower, SaveData *saveData, u32 mode, u16 value);

BOOL FrtCmd_StopBGM(FrontierScriptContext *ctx) {
    FrontierScriptContext_ReadHalfWord(ctx);
    StopBGM(GF_GetCurrentPlayingBGM(), 0);
    return FALSE;
}

enum {
    TOWER_ACTION_RESET_SYSTEM = 2,
    TOWER_ACTION_GET_BATTLE_NUMBER = 0x21,
    TOWER_ACTION_INC_BATTLE_NUMBER,
    TOWER_ACTION_HAS_WON_SET,
    TOWER_ACTION_GET_WIN_STREAK,
    TOWER_ACTION_RECORD_SET_LOST,
    TOWER_ACTION_RECORD_SET_WON,
    TOWER_ACTION_SAVE_CHALLENGE,
    TOWER_ACTION_GENERATE_OPPONENTS,
    TOWER_ACTION_GET_TRAINER_SPRITE,
    TOWER_ACTION_GET_MODE = 0x2B,
    TOWER_ACTION_SET_PALMER_DEFEATED,
    TOWER_ACTION_AWARD_BATTLE_POINTS = 0x2E,
    TOWER_ACTION_GET_OVERWORLD_SPRITE = 0x37,
    TOWER_ACTION_IS_FREED = 0x64,
};

BOOL FrtCmd_TowerAction(FrontierScriptContext *ctx) {
    FrontierLaunchArgs *args = Frontier_GetLaunchArgs(ctx->frontierSystem->frontierWork);
    u16 command = FrontierScriptContext_ReadHalfWord(ctx);
    u32 value = FrontierScript_ReadVar(ctx);
    u16 *dst = FrontierScript_ReadVarPtr(ctx);
    FrontierFieldSystem *tower = Frontier_GetData(ctx->frontierSystem->frontierWork);

    switch (command) {
    case TOWER_ACTION_RESET_SYSTEM:
        ResetSystem();
        break;
    case TOWER_ACTION_AWARD_BATTLE_POINTS:
        *dst = FrontierFieldSystem_AwardTowerBattlePoints(tower);
        GameStats_Add(Save_GameStats_Get(args->saveData), GAME_STAT_BATTLE_POINTS_RECEIVED, *dst);
        break;
    case TOWER_ACTION_GET_OVERWORLD_SPRITE:
        *dst = BattleTower_GetOverworldSprite(tower, (u8)value);
        break;
    case TOWER_ACTION_GET_BATTLE_NUMBER:
        *dst = FrontierFieldSystem_GetFrontierBattleNumber(tower);
        break;
    case TOWER_ACTION_INC_BATTLE_NUMBER:
        *dst = BattleTower_IncBattleNumber(tower);
        break;
    case TOWER_ACTION_HAS_WON_SET:
        *dst = FrontierFieldSystem_HasWonSet(tower);
        break;
    case TOWER_ACTION_GET_WIN_STREAK:
        *dst = BattleTower_GetWinStreak(tower);
        break;
    case TOWER_ACTION_GET_MODE:
        *dst = FrontierFieldSystem_GetBattleTowerMode(tower);
        break;
    case TOWER_ACTION_GENERATE_OPPONENTS:
        BattleTower_GenerateOpponents(tower, args->saveData);
        break;
    case TOWER_ACTION_GET_TRAINER_SPRITE:
        *dst = BattleTower_GetTrainerSprite(tower, value);
        break;
    case TOWER_ACTION_SET_PALMER_DEFEATED:
        BattleTower_SetPalmerDefeated(tower, value);
        break;
    case TOWER_ACTION_RECORD_SET_LOST:
        FrontierFieldSystem_RecordSetLost(tower, args->saveData);
        break;
    case TOWER_ACTION_RECORD_SET_WON:
        FrontierFieldSystem_RecordSetWon(tower, args->saveData);
        break;
    case TOWER_ACTION_SAVE_CHALLENGE:
        FrontierFieldSystem_SaveChallenge(tower);
        break;
    case 0x3A:
        MI_CpuFill8(tower->unk884, 0, sizeof(tower->unk884));
        break;
    case 0x3B:
        tower->filler8D6[0] = 1;
        break;
    case TOWER_ACTION_IS_FREED:
        if (tower == NULL) {
            *dst = 1;
        } else {
            *dst = 0;
        }
        break;
    default:
        GF_ASSERT(FALSE);
        break;
    }
    return FALSE;
}

static u32 BattleTower_GetOverworldSprite(FrontierFieldSystem *tower, u32 mode) {
    if (mode == 2) {
        return tower->multiBattleAllyID;
    }
    if (mode == 1) {
        if (tower->towerMode == TOWER_MODE_MULTI) {
            return gBattleTowerAllySprites[tower->multiBattleAllyID];
        }
        if (tower->linkAllyGender != 0) {
            return 0x61;
        }
        return 0;
    }
    if (tower->trainerGender != 0) {
        return 0x61;
    }
    return 0;
}

BOOL FrtCmd_TowerPrintTrainerMessage(FrontierScriptContext *ctx) {
    u8 arg;
    FrontierFieldSystem *tower;
    Frontier_GetLaunchArgs(ctx->frontierSystem->frontierWork);
    arg = FrontierScriptContext_ReadByte(ctx);
    tower = Frontier_GetData(ctx->frontierSystem->frontierWork);
    if (tower == NULL) {
        return FALSE;
    }
    FrontierScript_PrintMessageEntryFromBank(ctx, &tower->opponents[arg].introMessage.msg_bank, BattleTower_GetTrainerMessageBank(tower->towerMode));
    return TRUE;
}

BOOL FrtCmd_TowerFreeData(FrontierScriptContext *ctx) {
    FrontierFieldSystem_Free(Frontier_GetData(ctx->frontierSystem->frontierWork));
    return FALSE;
}

BOOL FrtCmd_TowerStartBattle(FrontierScriptContext *ctx) {
    FrontierLaunchArgs *args = Frontier_GetLaunchArgs(ctx->frontierSystem->frontierWork);
    FrontierFieldSystem *tower = Frontier_GetData(ctx->frontierSystem->frontierWork);
    BattleSetup *setup = BattleTower_NewBattleSetup(tower, args);
    tower->battleSetup = setup;
    Sound_SetSceneAndPlayBGM(5, SEQ_GS_VS_TRAINER, 1);
    Frontier_LaunchApplication(ctx->frontierSystem->frontierWork, &gOverlayTemplate_Battle, setup, 0, 0);
    return TRUE;
}

BOOL FrtCmd_TowerEndBattle(FrontierScriptContext *ctx) {
    FrontierFieldSystem *tower = Frontier_GetData(ctx->frontierSystem->frontierWork);
    u16 *dst = FrontierScript_ReadVarPtr(ctx);
    BattleSetup *setup = tower->battleSetup;
    tower->battleWon = IsBattleResultWin(setup->winFlag);
    *dst = tower->battleWon;
    BattleSetup_Delete(setup);
    return FALSE;
}

BOOL FrtCmd_TowerSendLinkMessage(FrontierScriptContext *ctx) {
    u32 kind;
    u32 value;
    FrontierFieldSystem *tower;
    u16 *dst;
    Frontier_GetLaunchArgs(ctx->frontierSystem->frontierWork);
    kind = FrontierScript_ReadVar(ctx);
    value = FrontierScript_ReadVar(ctx);
    dst = FrontierScript_ReadVarPtr(ctx);
    tower = Frontier_GetData(ctx->frontierSystem->frontierWork);
    if (kind == 2) {
        BattleTowerSetup_SetLinkFlag(tower, value);
    } else {
        GF_ASSERT(FALSE);
    }
    if (LinkSync_SendPacket(Comm_GetLocalNetId(), tower->linkSendBuffer) == 1) {
        *dst = 1;
    } else {
        *dst = 0;
        return TRUE;
    }
    return FALSE;
}

BOOL FrtCmd_TowerWaitLink(FrontierScriptContext *ctx) {
    u16 first = FrontierScriptContext_ReadHalfWord(ctx);
    u16 second = FrontierScriptContext_ReadHalfWord(ctx);
    ctx->data[0] = first;
    ctx->data[1] = second;
    FrontierScriptContext_Pause(ctx, FrontierScriptNative_WaitPartnerPacket);
    return TRUE;
}

static BOOL FrontierScriptNative_WaitPartnerPacket(FrontierScriptContext *ctx) {
    FrontierLaunchArgs *args = Frontier_GetLaunchArgs(ctx->frontierSystem->frontierWork);
    FrontierFieldSystem *tower = Frontier_GetData(ctx->frontierSystem->frontierWork);
    return FrontierScript_ReadPartnerPacket(ctx, tower, args->saveData, ctx->data[0], ctx->data[1]) == 1;
}

static BOOL FrontierScript_ReadPartnerPacket(FrontierScriptContext *ctx, FrontierFieldSystem *tower, SaveData *saveData, u32 mode, u16 value) {
    u16 *remote = LinkSync_GetPacket(1 - Comm_GetLocalNetId());
    u16 *dst;
    if (remote == NULL) {
        return FALSE;
    }
    dst = FrontierScript_GetVarPtr(ctx, value);
    if (mode == 2) {
        *dst = BattleTowerSetup_IsLinkFlagSetByEither(tower, remote);
    } else {
        GF_ASSERT(FALSE);
    }
    return TRUE;
}
