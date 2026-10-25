#ifndef POKEHEARTGOLD_APRICORN_INTERNAL_H
#define POKEHEARTGOLD_APRICORN_INTERNAL_H

#include "global.h"

#include "apricorn_box.h"
#include "heap.h"
#include "msgdata.h"
#include "player_data.h"

typedef struct ApricornRecord {
    u32 trainerId;
    u8 gender;
    u8 language;
    u8 version;
    u8 padding;
    u16 name[PLAYER_NAME_LENGTH + 1];
    ApricornJuice data;
} ApricornRecord;

#define APRICORN_JUICE_RECORD_COUNT 3

// Juice indices of ApricornBox_GetJuice: the presets, the stored records, then the player's own juice
#define APRICORN_JUICE_PRESET_COUNT 5
#define APRICORN_JUICE_PRESET_LAST  (APRICORN_JUICE_PRESET_COUNT - 1)
#define APRICORN_JUICE_FIRST_RECORD APRICORN_JUICE_PRESET_COUNT
#define APRICORN_JUICE_RECORD_LAST  (APRICORN_JUICE_FIRST_RECORD + APRICORN_JUICE_RECORD_COUNT - 1)
#define APRICORN_JUICE_OWN          (APRICORN_JUICE_RECORD_LAST + 1)
#define APRICORN_JUICE_COUNT        (APRICORN_JUICE_OWN + 1)

// The queued apricorns: five 3-bit slots (apricorn + 1, 0 = empty), then the mixing flag
#define APRICORN_QUEUE_SLOT_COUNT 5
#define APRICORN_QUEUE_SLOT_BITS  3
#define APRICORN_QUEUE_SLOT_MASK  7
#define APRICORN_QUEUE_MIXING     (1 << 15)

// A juice flavor of ApricornJuice_RankFlavors: its index (or one of the codes below), strength level and amount
#define APRICORN_JUICE_FLAVOR_MIXED 5 // several flavors of about the same amount
#define APRICORN_JUICE_FLAVOR_NONE  6

typedef struct ApricornJuiceEntry {
    u16 stat : 4;
    u16 strength : 4;
    u16 amount : 8;
} ApricornJuiceEntry;

// The flavors of a juice, strongest first
typedef struct ApricornJuiceRanking {
    ApricornJuiceEntry entries[3];
    u8 order[APRICORN_JUICE_FLAVOR_COUNT]; // flavor indices
    u8 ties;                               // flavors as weak as the weakest
    u8 count;                              // entries in use
} ApricornJuiceRanking;

struct SaveApricornBox {
    u8 apricorns[APRICORN_TYPE_COUNT];
    u8 kurtQuantity;
    u8 kurtApricorn;
    u8 juiceServings;
    union {
        u16 queuedApricorns;
        struct {
            u16 queuedSlots : 15;
            u16 mixing : 1;
        };
    };
    ApricornJuice juice;
    u32 mixStartSteps;
    u32 juiceAgingSteps;
    union {
        u32 mixWord;
        struct {
            u32 mixProgress : 30;
            u32 mixState : 2;
        };
    };
    ApricornRecord juiceRecords[APRICORN_JUICE_RECORD_COUNT];
};

int ApricornBox_CountQueuedApricorns(SaveApricornBox *box);
BOOL ApricornBox_GetJuice(SaveApricornBox *box, int index, ApricornJuice *out);
int ApricornJuice_GetFlavorTotal(ApricornJuice *data);
void ApricornJuice_RankFlavors(ApricornJuice *juice, ApricornJuiceRanking *out);
void ApricornBox_SetMixState(SaveApricornBox *apricornBox, u32 value);
int ApricornJuice_GetFlavorNameIndex(ApricornJuice *juice);
u32 Save_ApricornBox_sizeof(void);
u32 ApricornJuiceRecord_sizeof(void);
void Save_ApricornBox_Init(SaveApricornBox *apricornBox);
u32 ApricornBox_GetMixState(SaveApricornBox *apricornBox);
BOOL ApricornBox_QueueApricorn(SaveApricornBox *box, int apricorn, u32 value);
int ApricornBox_GetMixProgressLevel(SaveApricornBox *box);
u8 ApricornBox_GetJuiceServings(SaveApricornBox *box);
int ApricornJuice_GetTopMixIndex(ApricornJuice *juice);
int ApricornBox_UseJuiceServing(SaveApricornBox *box);
ApricornRecord *ApricornRecord_New(SaveApricornBox *box, PlayerProfile *profile, u32 value, enum HeapID heapId);
void ApricornBox_StoreJuiceRecords(SaveApricornBox *box, ApricornRecord *records, int count, int skip);

#endif // POKEHEARTGOLD_APRICORN_INTERNAL_H
