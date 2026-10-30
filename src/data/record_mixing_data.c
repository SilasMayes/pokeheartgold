// Converted from asm/record_mixing_data.s by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout. Keep that when editing, or rerun tools/s2c.py.

#include "global.h"

#include "record_mixing/record_mixing_exchange.h"

#pragma force_active on

extern void BattleRoomTrainer_sizeof(void);
extern void RecordMixing_Block23List0_GetSize(void);
extern void RecordMixing_Block23List0_Load(void);
extern void RecordMixing_Block23List0_Load2(void);
extern void RecordMixing_Block23List1_GetSize(void);
extern void RecordMixing_Block23List1_Load(void);
extern void RecordMixing_Block23List1_Load2(void);
extern void RecordMixing_Block23List2_GetSize(void);
extern void RecordMixing_Block23List2_Load(void);
extern void RecordMixing_Block23List2_Load2(void);
extern void Save_Rankings_GetMixingSize(void);

const RecordMixingHandler sRecordMixingHandlers[RECORD_MIXING_NUM_HANDLERS] = {
    {
     (u32(*)(SaveData *))RecordMixing_FriendGroup_GetSize,
     (void *(*)(SaveData *,                                                    enum HeapID,                     u32))RecordMixing_FriendGroup_Load,
     (void (*)(RecordMixingMergeArgs *))RecordMixing_FriendGroup_Merge,
     },
    {
     (u32(*)(SaveData *))RecordMixing_Fashion_GetSize,
     (void *(*)(SaveData *,                                                                              enum HeapID,                                                          u32))RecordMixing_Fashion_Load,
     (void (*)(RecordMixingMergeArgs *))RecordMixing_Fashion_Merge,
     },
    {
     (u32(*)(SaveData *))RecordMixing_Block23List0_GetSize,
     (void *(*)(SaveData *,           enum HeapID,                                                                                                         u32))RecordMixing_Block23List0_Load,
     NULL,
     },
    {
     (u32(*)(SaveData *))RecordMixing_Block23List1_GetSize,
     (void *(*)(SaveData *,                             enum HeapID,u32))RecordMixing_Block23List1_Load,
     NULL,
     },
    {
     (u32(*)(SaveData *))RecordMixing_Block23List2_GetSize,
     (void *(*)(SaveData *,                    enum HeapID,                                                                                     u32))RecordMixing_Block23List2_Load,
     NULL,
     },
    {
     (u32(*)(SaveData *))Save_Rankings_GetMixingSize,
     (void *(*)(SaveData *,                                                                        enum HeapID,                                                                                                               u32))RecordMixing_Rankings_Load,
     (void (*)(RecordMixingMergeArgs *))RecordMixing_Rankings_Merge,
     },
    {
     (u32(*)(SaveData *))BattleRoomTrainer_sizeof,
     (void *(*)(SaveData *,     enum HeapID,                                                                                                     u32))RecordMixing_BattleRoomTrainer_Load,
     (void (*)(RecordMixingMergeArgs *))RecordMixing_BattleRoomTrainer_Merge,
     },
    {
     (u32(*)(SaveData *))RecordMixing_Block23List0_GetSize,
     (void *(*)(SaveData *,                                                    enum HeapID, u32))RecordMixing_Block23List0_Load2,
     NULL,
     },
    {
     (u32(*)(SaveData *))RecordMixing_Block23List1_GetSize,
     (void *(*)(SaveData *,                                                                              enum HeapID,                                                              u32))RecordMixing_Block23List1_Load2,
     NULL,
     },
    {
     (u32(*)(SaveData *))RecordMixing_Block23List2_GetSize,
     (void *(*)(SaveData *, enum HeapID,                                                                                                         u32))RecordMixing_Block23List2_Load2,
     (void (*)(RecordMixingMergeArgs *))RecordMixing_Block23_Merge,
     },
};
