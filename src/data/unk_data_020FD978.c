// Converted from asm/unk_data_020FD978.s by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout. Keep that when editing, or rerun tools/s2c.py.

// The C declarations of these do not match the data (see the notes at each
// definition): keep them out of the way of the definitions below.
#define gMovementCmdSteps_001 gMovementCmdSteps_001_header_decl
#define gMovementCmdSteps_003 gMovementCmdSteps_003_header_decl
#define gMovementCmdSteps_073 gMovementCmdSteps_073_header_decl
#define gMovementCmdSteps_074 gMovementCmdSteps_074_header_decl
#define gMovementCmdSteps_072 gMovementCmdSteps_072_header_decl
#define gMovementCmdSteps_070 gMovementCmdSteps_070_header_decl
#define gMovementCmdSteps_069 gMovementCmdSteps_069_header_decl
#define gMovementCmdSteps_000 gMovementCmdSteps_000_header_decl
#define gMovementCmdSteps_002 gMovementCmdSteps_002_header_decl
#define gMovementCmdSteps_071 gMovementCmdSteps_071_header_decl
#define gMovementCmdSteps_010 gMovementCmdSteps_010_header_decl
#define gMovementCmdSteps_089 gMovementCmdSteps_089_header_decl
#define gMovementCmdSteps_083 gMovementCmdSteps_083_header_decl
#define gMovementCmdSteps_006 gMovementCmdSteps_006_header_decl
#define gMovementCmdSteps_091 gMovementCmdSteps_091_header_decl
#define gMovementCmdSteps_004 gMovementCmdSteps_004_header_decl
#define gMovementCmdSteps_011 gMovementCmdSteps_011_header_decl

#include "global.h"

#pragma force_active on

#undef gMovementCmdSteps_001
#undef gMovementCmdSteps_003
#undef gMovementCmdSteps_073
#undef gMovementCmdSteps_074
#undef gMovementCmdSteps_072
#undef gMovementCmdSteps_070
#undef gMovementCmdSteps_069
#undef gMovementCmdSteps_000
#undef gMovementCmdSteps_002
#undef gMovementCmdSteps_071
#undef gMovementCmdSteps_010
#undef gMovementCmdSteps_089
#undef gMovementCmdSteps_083
#undef gMovementCmdSteps_006
#undef gMovementCmdSteps_091
#undef gMovementCmdSteps_004
#undef gMovementCmdSteps_011

extern void MapObjectMovementCmd000_Step0(void);
extern void MapObjectMovementCmd001_Step0(void);
extern void MapObjectMovementCmd002_Step0(void);
extern void MapObjectMovementCmd003_Step0(void);
extern void MapObjectMovementCmd004_Step0(void);
extern void MapObjectMovementCmd006_Step0(void);
extern void MapObjectMovementCmd010_Step0(void);
extern void MapObjectMovementCmd011_Step0(void);
extern void MapObjectMovementCmd069_Step0(void);
extern void MapObjectMovementCmd070_Step0(void);
extern void MapObjectMovementCmd071_Step0(void);
extern void MapObjectMovementCmd072_Step0(void);
extern void MapObjectMovementCmd073_Step0(void);
extern void MapObjectMovementCmd074_Step0(void);
extern void MapObjectMovementCmd082_Step1(void);
extern void MapObjectMovementCmd083_Step0(void);
extern void MapObjectMovementCmd089_Step0(void);
extern void MapObjectMovementCmd090_Step1(void);
extern void MapObjectMovementCmd091_Step0(void);
extern void MapObjectMovementCmd098_Step2(void);

// An address sits where that type has a 1-byte field.
void (*const gMovementCmdSteps_004[3])(void) = {
    MapObjectMovementCmd004_Step0,
    MapObjectMovementCmd090_Step1,
    MapObjectMovementCmd098_Step2,
};

// An address sits where that type has a 1-byte field.
void (*const gMovementCmdSteps_011[3])(void) = {
    MapObjectMovementCmd011_Step0,
    MapObjectMovementCmd090_Step1,
    MapObjectMovementCmd098_Step2,
};

// An address sits where that type has a 1-byte field.
void (*const gMovementCmdSteps_006[3])(void) = {
    MapObjectMovementCmd006_Step0,
    MapObjectMovementCmd090_Step1,
    MapObjectMovementCmd098_Step2,
};

// An address sits where that type has a 1-byte field.
void (*const gMovementCmdSteps_010[3])(void) = {
    MapObjectMovementCmd010_Step0,
    MapObjectMovementCmd090_Step1,
    MapObjectMovementCmd098_Step2,
};

// An address sits where that type has a 1-byte field.
void (*const gMovementCmdSteps_089[3])(void) = {
    MapObjectMovementCmd089_Step0,
    MapObjectMovementCmd090_Step1,
    MapObjectMovementCmd098_Step2,
};

// An address sits where that type has a 1-byte field.
void (*const gMovementCmdSteps_083[3])(void) = {
    MapObjectMovementCmd083_Step0,
    MapObjectMovementCmd082_Step1,
    MapObjectMovementCmd098_Step2,
};

// An address sits where that type has a 1-byte field.
void (*const gMovementCmdSteps_091[3])(void) = {
    MapObjectMovementCmd091_Step0,
    MapObjectMovementCmd090_Step1,
    MapObjectMovementCmd098_Step2,
};

// An address sits where that type has a 1-byte field.
void (*const gMovementCmdSteps_002[2])(void) = {
    MapObjectMovementCmd002_Step0,
    MapObjectMovementCmd098_Step2,
};

// An address sits where that type has a 1-byte field.
void (*const gMovementCmdSteps_000[2])(void) = {
    MapObjectMovementCmd000_Step0,
    MapObjectMovementCmd098_Step2,
};

// An address sits where that type has a 1-byte field.
void (*const gMovementCmdSteps_001[2])(void) = {
    MapObjectMovementCmd001_Step0,
    MapObjectMovementCmd098_Step2,
};

// An address sits where that type has a 1-byte field.
void (*const gMovementCmdSteps_072[2])(void) = {
    MapObjectMovementCmd072_Step0,
    MapObjectMovementCmd098_Step2,
};

// An address sits where that type has a 1-byte field.
void (*const gMovementCmdSteps_003[2])(void) = {
    MapObjectMovementCmd003_Step0,
    MapObjectMovementCmd098_Step2,
};

// An address sits where that type has a 1-byte field.
void (*const gMovementCmdSteps_071[2])(void) = {
    MapObjectMovementCmd071_Step0,
    MapObjectMovementCmd098_Step2,
};

// An address sits where that type has a 1-byte field.
void (*const gMovementCmdSteps_074[2])(void) = {
    MapObjectMovementCmd074_Step0,
    MapObjectMovementCmd098_Step2,
};

// An address sits where that type has a 1-byte field.
void (*const gMovementCmdSteps_070[2])(void) = {
    MapObjectMovementCmd070_Step0,
    MapObjectMovementCmd098_Step2,
};

// An address sits where that type has a 1-byte field.
void (*const gMovementCmdSteps_069[2])(void) = {
    MapObjectMovementCmd069_Step0,
    MapObjectMovementCmd098_Step2,
};

// An address sits where that type has a 1-byte field.
void (*const gMovementCmdSteps_073[2])(void) = {
    MapObjectMovementCmd073_Step0,
    MapObjectMovementCmd098_Step2,
};
