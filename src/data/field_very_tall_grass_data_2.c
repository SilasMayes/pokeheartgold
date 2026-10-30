// Converted from asm/field_very_tall_grass_data.s (part 2 of 2) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

#include "global.h"

#pragma force_active on

extern void UnusedBillboardEffect_Destroy(void);
extern void UnusedBillboardEffect_Draw(void);
extern void UnusedBillboardEffect_Init(void);
extern void UnusedBillboardEffect_Update(void);

static const struct {
    u32 unk0;
    void (*unk4)(void);
    void (*unk8)(void);
    void (*unkC)(void);
    void (*unk10)(void);
} sUnusedBillboardEffectTemplate = {
    0x00000040,
    UnusedBillboardEffect_Init,
    UnusedBillboardEffect_Destroy,
    UnusedBillboardEffect_Update,
    UnusedBillboardEffect_Draw,
};
