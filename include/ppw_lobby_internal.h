#ifndef POKEHEARTGOLD_PPW_LOBBY_INTERNAL_H
#define POKEHEARTGOLD_PPW_LOBBY_INTERNAL_H

// PPW lobby (overlay 45): the lobby player sessions, the event deques and vectors behind them, and the
// functions shared between the PPW lobby source files.

#include "global.h"

#include "dwc/net_common_internal.h"

#include "lobby_mem.h"
#include "lobby_string.h"

#include "../lib/NitroDWC/src/tree-iterator4.h"

#include "ppw_lobby_work.h"

extern unsigned char __lower_mapC[];
void _ZNSt15__vector_commonILb1EE18throw_length_errorEv(void);

void LobbyString_ReplaceRange(Str *, u32, u32, const char *, const char *, LobbyTag);

void LobbyCharVector_AppendFillSlow(LobbyCharVector *, u32, const char *);
void LobbyTreeIterator_Advance(Iterator *);
void *LobbyTree_EraseRebalance(void *node, void *root);
extern char gLobbyStr_TreeInsertLengthError_2[];
int printf(const char *, ...);
void abort(void);
void LobbyTree_InsertRebalance(void *node, void *root);

extern u8 ov45_02255200[];
PPWLobbyPlayerSetNode *PPWLobbyPlayerSet_FindInsertPos(PPWLobbyPlayerSet *set, PPWLobbyPlayer **key, PPWLobbyPlayerSetNode **parent, u8 *left, u8 *leftmost);
PPWLobbyPlayerSetNode *PPWLobbyPlayerSet_InsertNode(PPWLobbyPlayerSet *set, PPWLobbyPlayerSetNode *parent, u8 left, u8 leftmost, PPWLobbyPlayer **key);

typedef struct FindState {
    int id;
    PPWLobbyPlayerSetNode *end;
    Iterator it;
} FindState;

static inline void VecReserve(LobbyU32Vector *v, u32 n) {
    if (n > v->capacity) {
        LobbyU32Vector_Reserve(v, n);
    }
}

void PPWLobbyPlayers_GetEnteredIds(LobbyU32Vector *out, PPWLobbyPlayers *players);

static inline void SwapU32(u32 *a, u32 *b) {
    u32 t = *a;
    *a = *b;
    *b = t;
}

static inline void SwapPtr(void **a, void **b) {
    void *t = *a;
    *a = *b;
    *b = t;
}

extern PPWLobbyPlayerVtable gPPWLobbyPlayerVtable;
void PPWLobbyPlayerSet_Insert(PPWLobbyPlayerSetInsertResult *out, PPWLobbyPlayerSet *set, PPWLobbyPlayer **key);
extern char gLobbyStr_SpaceSpace[];
extern char gLobbyStr_Space_2[];
extern char gLobbyStr_B[];
extern char gLobbyStr_S[];
extern char gLobbyStr_Empty_16[];
extern char gLobbyFmt_Hex_3[];
extern char gLobbyStr_A[];
extern char gLobbyStr__[];
extern char gLobbyFmt_Str_3[];
int DWC_Base64Encode(const void *src, u32 len, char *dst, u32 dstLen);
void MI_CpuFill8(void *dst, u8 val, u32 size);

static inline void TouchTag(void) {
    volatile LobbyTag t = { 0 };
}

BOOL PPWLobbyPlayers_Add(PPWLobbyPlayers *players, int id);
BOOL PPWLobbyPlayers_Remove(PPWLobbyPlayers *players, int id);
PPWLobbyPlayer *PPWLobbyPlayers_Find(PPWLobbyPlayers *players, int id);

void LobbyCharVector_PushBackSlow(LobbyCharVector *s, const char *c);
int LobbyString_ToLowerChar(int c);
BOOL PPWLobbyPlayer_HasProfiles(PPWLobbyPlayer *player);
BOOL PPWLobby_EncodeMessage(int type, int mode, u32 value, const void *data, u32 len, Str *out);

// The state of the lobby library (PPWLobbyState), read from the current work.
static inline int PPWLobby_GetState(void) {
    PPWLobbyWork *volatile *work = &gPPWLobbyWork;
    return (*work)->state;
}

#endif // POKEHEARTGOLD_PPW_LOBBY_INTERNAL_H
