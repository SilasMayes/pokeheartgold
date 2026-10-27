#ifndef POKEHEARTGOLD_RECORD_MIXING_EXCHANGE_H
#define POKEHEARTGOLD_RECORD_MIXING_EXCHANGE_H

#include "save.h"

// The record types record mixing exchanges (one part builds what is sent, the other merges what was
// received).

#define RECORD_MIXING_SEND_SIZE    3000
#define RECORD_MIXING_NUM_HANDLERS 10
#define RECORD_MIXING_BUFFER_SIZE  0xBC0 // one member's records in the link transfer

// What the merge function of a record type gets: the received records of every member.
typedef struct RecordMixingMergeArgs {
    enum HeapID heapID;
    SaveData *saveData;
    int numPlayers;
    int localId;
    void **records;
    void **records2;
} RecordMixingMergeArgs;

// One record type: size and copy of the local data to send, merge of the received data.
typedef struct RecordMixingHandler {
    u32 (*getSize)(SaveData *saveData);
    void *(*load)(SaveData *saveData, enum HeapID heapID, u32 size);
    void (*merge)(RecordMixingMergeArgs *args);
} RecordMixingHandler;

struct SaveRankingsEntry;

extern const RecordMixingHandler sRecordMixingHandlers[RECORD_MIXING_NUM_HANDLERS];

u32 RecordMixing_FriendGroup_GetSize(SaveData *saveData);
void *RecordMixing_FriendGroup_Load(SaveData *saveData, enum HeapID heapID, u32 size);
void RecordMixing_FriendGroup_Merge(RecordMixingMergeArgs *args);
u32 RecordMixing_Fashion_GetSize(SaveData *saveData);
void *RecordMixing_Fashion_Load(SaveData *saveData, enum HeapID heapID, u32 size);
void RecordMixing_Fashion_Merge(RecordMixingMergeArgs *args);
void RecordMixing_Block23_Merge(RecordMixingMergeArgs *args);
struct SaveRankingsEntry *RecordMixing_Rankings_Load(SaveData *saveData, enum HeapID heapID);
void RecordMixing_Rankings_Merge(RecordMixingMergeArgs *args);
void *RecordMixing_BattleRoomTrainer_Load(SaveData *saveData, enum HeapID heapID, u32 size);
void RecordMixing_BattleRoomTrainer_Merge(RecordMixingMergeArgs *args);
void RecordMixing_BuildSendBuffer(SaveData *saveData, void *dest);
void RecordMixing_MergeReceivedRecords(SaveData *saveData, u8 (*buffers)[RECORD_MIXING_BUFFER_SIZE]);

#endif // POKEHEARTGOLD_RECORD_MIXING_EXCHANGE_H
