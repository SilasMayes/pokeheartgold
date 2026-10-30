// Converted from asm/field_emote_mark_data.s by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout. Keep that when editing, or rerun tools/s2c.py.

#include "global.h"

#include "constants/items.h"
#include "constants/maps.h"
#include "constants/mmodel.h"
#include "constants/moves.h"
#include "constants/sndseq.h"
#include "constants/species.h"
#include "constants/sprites.h"
#include "constants/std_script.h"

#include "msgdata/msg/msg_0066_D23R0102.h"
#include "msgdata/msg/msg_0096_D31R0201.h"

#pragma force_active on

extern void EmoteMarkEffect_Destroy(void);
extern void EmoteMarkEffect_Draw(void);
extern void EmoteMarkEffect_Init(void);
extern void EmoteMarkEffect_Update(void);
extern void MapObjectEmoteMarkEffect_Init(void);
extern void MapObjectEmoteMarkEffect_Update(void);

// clang-format off
const u8 gEmoteMarkRecordParams[24] = {
    0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
};
// clang-format on

const struct {
    u32 unk0;
    void (*unk4)(void);
    void (*unk8)(void);
    void (*unkC)(void);
    void (*unk10)(void);
} sEmoteMarkTemplate = {
    0x00000044,
    EmoteMarkEffect_Init,
    EmoteMarkEffect_Destroy,
    EmoteMarkEffect_Update,
    EmoteMarkEffect_Draw,
};

const struct {
    u32 unk0;
    void (*unk4)(void);
    void (*unk8)(void);
    void (*unkC)(void);
    void (*unk10)(void);
} gMapObjectEmoteMarkTemplate = {
    0x00000044,
    MapObjectEmoteMarkEffect_Init,
    EmoteMarkEffect_Destroy,
    MapObjectEmoteMarkEffect_Update,
    EmoteMarkEffect_Draw,
};
