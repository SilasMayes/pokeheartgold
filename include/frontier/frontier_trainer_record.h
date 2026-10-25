#ifndef POKEHEARTGOLD_FRONTIER_FRONTIER_TRAINER_RECORD_H
#define POKEHEARTGOLD_FRONTIER_FRONTIER_TRAINER_RECORD_H

#include "global.h"

#include "constants/pokemon.h"

#include "filesystem.h"

// Win streak battles of the single battle streak against the facility's Frontier Brain (silver and gold print)
#define FRONTIER_BRAIN_BATTLE_SILVER 21
#define FRONTIER_BRAIN_BATTLE_GOLD   49

// A facility trainer as FrontierTrainer_Load fills it in from the trainer data and its name.
typedef struct FrontierTrainerRecord {
    u32 id;
    u16 trainerClass;
    u16 unk_06;
    u16 name[8];
    u16 introMsgBank;
    u16 introMsgNo;
    u8 introMsgFields[4];
    u16 messages[8]; // win and lose easy chat messages
} FrontierTrainerRecord;

// First u16s of a trainer's narc member: its class and the ids of its Pokemon sets.
typedef struct FrontierTrainerEntry {
    u16 trainerClass;
    u16 numSets;
    u16 setIds[];
} FrontierTrainerEntry;

// Pokemon set (narc member).
typedef struct FrontierMonSet {
    u16 species;
    u16 moves[MAX_MON_MOVES];
    u8 evMask;
    u8 nature;
    u16 item;
    u16 form;
} FrontierMonSet;

// Trainer ids of a round: regular trainers, and the 7th battle of a round.
typedef struct FrontierTrainerRange {
    u16 min;
    u16 max;
    u16 lastBattleMin;
    u16 lastBattleMax;
} FrontierTrainerRange;

void *FrontierTrainer_Load(FrontierTrainerRecord *record, int trainerId, enum HeapID heapID, NarcId narcId);

#endif // POKEHEARTGOLD_FRONTIER_FRONTIER_TRAINER_RECORD_H
