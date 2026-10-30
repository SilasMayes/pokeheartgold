// Converted from asm/map_object_movement_command_steps.s by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout. Keep that when editing, or rerun tools/s2c.py.

// The C declarations of these do not match the data (see the notes at each
// definition): keep them out of the way of the definitions below.
#define gMovementCmdSteps_098 gMovementCmdSteps_098_header_decl
#define gMovementCmdSteps_099 gMovementCmdSteps_099_header_decl
#define gMovementCmdSteps_097 gMovementCmdSteps_097_header_decl
#define gMovementCmdSteps_096 gMovementCmdSteps_096_header_decl
#define gMovementCmdSteps_064 gMovementCmdSteps_064_header_decl
#define gMovementCmdSteps_090 gMovementCmdSteps_090_header_decl
#define gMovementCmdSteps_060 gMovementCmdSteps_060_header_decl
#define gMovementCmdSteps_088 gMovementCmdSteps_088_header_decl
#define gMovementCmdSteps_092 gMovementCmdSteps_092_header_decl
#define gMovementCmdSteps_082 gMovementCmdSteps_082_header_decl
#define gMovementCmdSteps_056 gMovementCmdSteps_056_header_decl
#define gMovementCmdSteps_080 gMovementCmdSteps_080_header_decl
#define gMovementCmdSteps_055 gMovementCmdSteps_055_header_decl
#define gMovementCmdSteps_007 gMovementCmdSteps_007_header_decl
#define gMovementCmdSteps_100 gMovementCmdSteps_100_header_decl
#define gMovementCmdSteps_075 gMovementCmdSteps_075_header_decl
#define gMovementCmdSteps_103 gMovementCmdSteps_103_header_decl
#define gMovementCmdSteps_101 gMovementCmdSteps_101_header_decl
#define gMovementCmdSteps_040 gMovementCmdSteps_040_header_decl
#define gMovementCmdSteps_038 gMovementCmdSteps_038_header_decl
#define gMovementCmdSteps_036 gMovementCmdSteps_036_header_decl
#define gMovementCmdSteps_034 gMovementCmdSteps_034_header_decl
#define gMovementCmdSteps_032 gMovementCmdSteps_032_header_decl
#define gMovementCmdSteps_030 gMovementCmdSteps_030_header_decl
#define gMovementCmdSteps_068 gMovementCmdSteps_068_header_decl
#define gMovementCmdSteps_067 gMovementCmdSteps_067_header_decl
#define gMovementCmdSteps_066 gMovementCmdSteps_066_header_decl
#define gMovementCmdSteps_065 gMovementCmdSteps_065_header_decl
#define gMovementCmdSteps_084 gMovementCmdSteps_084_header_decl
#define gMovementCmdSteps_063 gMovementCmdSteps_063_header_decl
#define gMovementCmdSteps_062 gMovementCmdSteps_062_header_decl
#define gMovementCmdSteps_061 gMovementCmdSteps_061_header_decl
#define gMovementCmdSteps_016 gMovementCmdSteps_016_header_decl
#define gMovementCmdSteps_095 gMovementCmdSteps_095_header_decl
#define gMovementCmdSteps_094 gMovementCmdSteps_094_header_decl
#define gMovementCmdSteps_093 gMovementCmdSteps_093_header_decl
#define gMovementCmdSteps_008 gMovementCmdSteps_008_header_decl
#define gMovementCmdSteps_059 gMovementCmdSteps_059_header_decl
#define gMovementCmdSteps_058 gMovementCmdSteps_058_header_decl
#define gMovementCmdSteps_057 gMovementCmdSteps_057_header_decl
#define gMovementCmdSteps_081 gMovementCmdSteps_081_header_decl
#define gMovementCmdSteps_054 gMovementCmdSteps_054_header_decl
#define gMovementCmdSteps_053 gMovementCmdSteps_053_header_decl
#define gMovementCmdSteps_076 gMovementCmdSteps_076_header_decl
#define gMovementCmdSteps_047 gMovementCmdSteps_047_header_decl
#define gMovementCmdSteps_048 gMovementCmdSteps_048_header_decl
#define gMovementCmdSteps_077 gMovementCmdSteps_077_header_decl
#define gMovementCmdSteps_102 gMovementCmdSteps_102_header_decl
#define gMovementCmdSteps_049 gMovementCmdSteps_049_header_decl
#define gMovementCmdSteps_046 gMovementCmdSteps_046_header_decl
#define gMovementCmdSteps_045 gMovementCmdSteps_045_header_decl
#define gMovementCmdSteps_044 gMovementCmdSteps_044_header_decl
#define gMovementCmdSteps_043 gMovementCmdSteps_043_header_decl
#define gMovementCmdSteps_042 gMovementCmdSteps_042_header_decl
#define gMovementCmdSteps_041 gMovementCmdSteps_041_header_decl
#define gMovementCmdSteps_050 gMovementCmdSteps_050_header_decl
#define gMovementCmdSteps_039 gMovementCmdSteps_039_header_decl
#define gMovementCmdSteps_078 gMovementCmdSteps_078_header_decl
#define gMovementCmdSteps_037 gMovementCmdSteps_037_header_decl
#define gMovementCmdSteps_051 gMovementCmdSteps_051_header_decl
#define gMovementCmdSteps_035 gMovementCmdSteps_035_header_decl
#define gMovementCmdSteps_052 gMovementCmdSteps_052_header_decl
#define gMovementCmdSteps_033 gMovementCmdSteps_033_header_decl
#define gMovementCmdSteps_079 gMovementCmdSteps_079_header_decl
#define gMovementCmdSteps_031 gMovementCmdSteps_031_header_decl
#define gMovementCmdSteps_104 gMovementCmdSteps_104_header_decl
#define gMovementCmdSteps_029 gMovementCmdSteps_029_header_decl
#define gMovementCmdSteps_028 gMovementCmdSteps_028_header_decl
#define gMovementCmdSteps_027 gMovementCmdSteps_027_header_decl
#define gMovementCmdSteps_026 gMovementCmdSteps_026_header_decl
#define gMovementCmdSteps_025 gMovementCmdSteps_025_header_decl
#define gMovementCmdSteps_024 gMovementCmdSteps_024_header_decl
#define gMovementCmdSteps_087 gMovementCmdSteps_087_header_decl
#define gMovementCmdSteps_086 gMovementCmdSteps_086_header_decl
#define gMovementCmdSteps_085 gMovementCmdSteps_085_header_decl
#define gMovementCmdSteps_005 gMovementCmdSteps_005_header_decl
#define gMovementCmdSteps_023 gMovementCmdSteps_023_header_decl
#define gMovementCmdSteps_022 gMovementCmdSteps_022_header_decl
#define gMovementCmdSteps_021 gMovementCmdSteps_021_header_decl
#define gMovementCmdSteps_020 gMovementCmdSteps_020_header_decl
#define gMovementCmdSteps_019 gMovementCmdSteps_019_header_decl
#define gMovementCmdSteps_018 gMovementCmdSteps_018_header_decl
#define gMovementCmdSteps_017 gMovementCmdSteps_017_header_decl
#define gMovementCmdSteps_009 gMovementCmdSteps_009_header_decl
#define gMovementCmdSteps_015 gMovementCmdSteps_015_header_decl
#define gMovementCmdSteps_014 gMovementCmdSteps_014_header_decl
#define gMovementCmdSteps_013 gMovementCmdSteps_013_header_decl
#define gMovementCmdSteps_012 gMovementCmdSteps_012_header_decl
#define gMovementCmdSteps_108 gMovementCmdSteps_108_header_decl
#define gMovementCmdSteps_110 gMovementCmdSteps_110_header_decl
#define gMovementCmdSteps_112 gMovementCmdSteps_112_header_decl
#define gMovementCmdSteps_106 gMovementCmdSteps_106_header_decl
#define gMovementCmdSteps_105 gMovementCmdSteps_105_header_decl
#define gMovementCmdSteps_107 gMovementCmdSteps_107_header_decl
#define gMovementCmdSteps_109 gMovementCmdSteps_109_header_decl
#define gMovementCmdSteps_111 gMovementCmdSteps_111_header_decl

#include "global.h"

#include "constants/field_move_response.h"
#include "constants/flags.h"
#include "constants/items.h"
#include "constants/maps.h"
#include "constants/pokemon.h"
#include "constants/sndseq.h"
#include "constants/species.h"
#include "constants/std_script.h"
#include "constants/vars.h"

#include "fielddata/script/scr_seq/event_D24R0204.h"

#pragma force_active on

#undef gMovementCmdSteps_098
#undef gMovementCmdSteps_099
#undef gMovementCmdSteps_097
#undef gMovementCmdSteps_096
#undef gMovementCmdSteps_064
#undef gMovementCmdSteps_090
#undef gMovementCmdSteps_060
#undef gMovementCmdSteps_088
#undef gMovementCmdSteps_092
#undef gMovementCmdSteps_082
#undef gMovementCmdSteps_056
#undef gMovementCmdSteps_080
#undef gMovementCmdSteps_055
#undef gMovementCmdSteps_007
#undef gMovementCmdSteps_100
#undef gMovementCmdSteps_075
#undef gMovementCmdSteps_103
#undef gMovementCmdSteps_101
#undef gMovementCmdSteps_040
#undef gMovementCmdSteps_038
#undef gMovementCmdSteps_036
#undef gMovementCmdSteps_034
#undef gMovementCmdSteps_032
#undef gMovementCmdSteps_030
#undef gMovementCmdSteps_068
#undef gMovementCmdSteps_067
#undef gMovementCmdSteps_066
#undef gMovementCmdSteps_065
#undef gMovementCmdSteps_084
#undef gMovementCmdSteps_063
#undef gMovementCmdSteps_062
#undef gMovementCmdSteps_061
#undef gMovementCmdSteps_016
#undef gMovementCmdSteps_095
#undef gMovementCmdSteps_094
#undef gMovementCmdSteps_093
#undef gMovementCmdSteps_008
#undef gMovementCmdSteps_059
#undef gMovementCmdSteps_058
#undef gMovementCmdSteps_057
#undef gMovementCmdSteps_081
#undef gMovementCmdSteps_054
#undef gMovementCmdSteps_053
#undef gMovementCmdSteps_076
#undef gMovementCmdSteps_047
#undef gMovementCmdSteps_048
#undef gMovementCmdSteps_077
#undef gMovementCmdSteps_102
#undef gMovementCmdSteps_049
#undef gMovementCmdSteps_046
#undef gMovementCmdSteps_045
#undef gMovementCmdSteps_044
#undef gMovementCmdSteps_043
#undef gMovementCmdSteps_042
#undef gMovementCmdSteps_041
#undef gMovementCmdSteps_050
#undef gMovementCmdSteps_039
#undef gMovementCmdSteps_078
#undef gMovementCmdSteps_037
#undef gMovementCmdSteps_051
#undef gMovementCmdSteps_035
#undef gMovementCmdSteps_052
#undef gMovementCmdSteps_033
#undef gMovementCmdSteps_079
#undef gMovementCmdSteps_031
#undef gMovementCmdSteps_104
#undef gMovementCmdSteps_029
#undef gMovementCmdSteps_028
#undef gMovementCmdSteps_027
#undef gMovementCmdSteps_026
#undef gMovementCmdSteps_025
#undef gMovementCmdSteps_024
#undef gMovementCmdSteps_087
#undef gMovementCmdSteps_086
#undef gMovementCmdSteps_085
#undef gMovementCmdSteps_005
#undef gMovementCmdSteps_023
#undef gMovementCmdSteps_022
#undef gMovementCmdSteps_021
#undef gMovementCmdSteps_020
#undef gMovementCmdSteps_019
#undef gMovementCmdSteps_018
#undef gMovementCmdSteps_017
#undef gMovementCmdSteps_009
#undef gMovementCmdSteps_015
#undef gMovementCmdSteps_014
#undef gMovementCmdSteps_013
#undef gMovementCmdSteps_012
#undef gMovementCmdSteps_108
#undef gMovementCmdSteps_110
#undef gMovementCmdSteps_112
#undef gMovementCmdSteps_106
#undef gMovementCmdSteps_105
#undef gMovementCmdSteps_107
#undef gMovementCmdSteps_109
#undef gMovementCmdSteps_111

extern void MapObjectMovementCmd005_Step0(void);
extern void MapObjectMovementCmd007_Step0(void);
extern void MapObjectMovementCmd008_Step0(void);
extern void MapObjectMovementCmd009_Step0(void);
extern void MapObjectMovementCmd012_Step0(void);
extern void MapObjectMovementCmd013_Step0(void);
extern void MapObjectMovementCmd014_Step0(void);
extern void MapObjectMovementCmd015_Step0(void);
extern void MapObjectMovementCmd016_Step0(void);
extern void MapObjectMovementCmd017_Step0(void);
extern void MapObjectMovementCmd018_Step0(void);
extern void MapObjectMovementCmd019_Step0(void);
extern void MapObjectMovementCmd020_Step0(void);
extern void MapObjectMovementCmd021_Step0(void);
extern void MapObjectMovementCmd022_Step0(void);
extern void MapObjectMovementCmd023_Step0(void);
extern void MapObjectMovementCmd024_Step0(void);
extern void MapObjectMovementCmd025_Step0(void);
extern void MapObjectMovementCmd026_Step0(void);
extern void MapObjectMovementCmd027_Step0(void);
extern void MapObjectMovementCmd028_Step0(void);
extern void MapObjectMovementCmd029_Step0(void);
extern void MapObjectMovementCmd030_Step0(void);
extern void MapObjectMovementCmd031_Step0(void);
extern void MapObjectMovementCmd032_Step0(void);
extern void MapObjectMovementCmd033_Step0(void);
extern void MapObjectMovementCmd034_Step0(void);
extern void MapObjectMovementCmd035_Step0(void);
extern void MapObjectMovementCmd036_Step0(void);
extern void MapObjectMovementCmd037_Step0(void);
extern void MapObjectMovementCmd038_Step0(void);
extern void MapObjectMovementCmd039_Step0(void);
extern void MapObjectMovementCmd040_Step0(void);
extern void MapObjectMovementCmd040_Step1(void);
extern void MapObjectMovementCmd041_Step0(void);
extern void MapObjectMovementCmd042_Step0(void);
extern void MapObjectMovementCmd043_Step0(void);
extern void MapObjectMovementCmd044_Step0(void);
extern void MapObjectMovementCmd045_Step0(void);
extern void MapObjectMovementCmd046_Step0(void);
extern void MapObjectMovementCmd047_Step0(void);
extern void MapObjectMovementCmd048_Step0(void);
extern void MapObjectMovementCmd049_Step0(void);
extern void MapObjectMovementCmd050_Step0(void);
extern void MapObjectMovementCmd051_Step0(void);
extern void MapObjectMovementCmd052_Step0(void);
extern void MapObjectMovementCmd053_Step0(void);
extern void MapObjectMovementCmd054_Step0(void);
extern void MapObjectMovementCmd055_Step0(void);
extern void MapObjectMovementCmd056_Step0(void);
extern void MapObjectMovementCmd057_Step0(void);
extern void MapObjectMovementCmd058_Step0(void);
extern void MapObjectMovementCmd059_Step0(void);
extern void MapObjectMovementCmd060_Step0(void);
extern void MapObjectMovementCmd061_Step0(void);
extern void MapObjectMovementCmd062_Step0(void);
extern void MapObjectMovementCmd063_Step0(void);
extern void MapObjectMovementCmd064_Step0(void);
extern void MapObjectMovementCmd064_Step1(void);
extern void MapObjectMovementCmd065_Step0(void);
extern void MapObjectMovementCmd066_Step0(void);
extern void MapObjectMovementCmd067_Step0(void);
extern void MapObjectMovementCmd067_Step1(void);
extern void MapObjectMovementCmd068_Step0(void);
extern void MapObjectMovementCmd068_Step1(void);
extern void MapObjectMovementCmd075_Step0(void);
extern void MapObjectMovementCmd075_Step1(void);
extern void MapObjectMovementCmd076_Step0(void);
extern void MapObjectMovementCmd076_Step1(void);
extern void MapObjectMovementCmd077_Step0(void);
extern void MapObjectMovementCmd078_Step0(void);
extern void MapObjectMovementCmd079_Step0(void);
extern void MapObjectMovementCmd080_Step0(void);
extern void MapObjectMovementCmd081_Step0(void);
extern void MapObjectMovementCmd082_Step0(void);
extern void MapObjectMovementCmd082_Step1(void);
extern void MapObjectMovementCmd084_Step0(void);
extern void MapObjectMovementCmd085_Step0(void);
extern void MapObjectMovementCmd086_Step0(void);
extern void MapObjectMovementCmd087_Step0(void);
extern void MapObjectMovementCmd088_Step0(void);
extern void MapObjectMovementCmd090_Step0(void);
extern void MapObjectMovementCmd090_Step1(void);
extern void MapObjectMovementCmd092_Step0(void);
extern void MapObjectMovementCmd092_Step1(void);
extern void MapObjectMovementCmd093_Step0(void);
extern void MapObjectMovementCmd094_Step0(void);
extern void MapObjectMovementCmd095_Step0(void);
extern void MapObjectMovementCmd096_Step0(void);
extern void MapObjectMovementCmd097_Step0(void);
extern void MapObjectMovementCmd098_Step0(void);
extern void MapObjectMovementCmd098_Step1(void);
extern void MapObjectMovementCmd098_Step2(void);
extern void MapObjectMovementCmd099_Step0(void);
extern void MapObjectMovementCmd100_Step0(void);
extern void MapObjectMovementCmd100_Step1(void);
extern void MapObjectMovementCmd101_Step0(void);
extern void MapObjectMovementCmd101_Step1(void);
extern void MapObjectMovementCmd102_Step0(void);
extern void MapObjectMovementCmd102_Step1(void);
extern void MapObjectMovementCmd103_Step0(void);
extern void MapObjectMovementCmd104_Step0(void);
extern void MapObjectMovementCmd105_Step0(void);
extern void MapObjectMovementCmd105_Step2(void);
extern void MapObjectMovementCmd105_Step4(void);
extern void MapObjectMovementCmd105_Step6(void);
extern void MapObjectMovementCmd105_Step8(void);
extern void MapObjectMovementCmd106_Step0(void);
extern void MapObjectMovementCmd106_Step2(void);
extern void MapObjectMovementCmd106_Step4(void);
extern void MapObjectMovementCmd106_Step6(void);
extern void MapObjectMovementCmd107_Step0(void);
extern void MapObjectMovementCmd107_Step10(void);
extern void MapObjectMovementCmd107_Step12(void);
extern void MapObjectMovementCmd107_Step2(void);
extern void MapObjectMovementCmd107_Step4(void);
extern void MapObjectMovementCmd107_Step6(void);
extern void MapObjectMovementCmd107_Step8(void);
extern void MapObjectMovementCmd108_Step0(void);
extern void MapObjectMovementCmd108_Step1(void);
extern void MapObjectMovementCmd108_Step2(void);
extern void MapObjectMovementCmd109_Step12(void);
extern void MapObjectMovementCmd110_Step0(void);
extern void MapObjectMovementCmd111_Step0(void);
extern void MapObjectMovementCmd111_Step10(void);
extern void MapObjectMovementCmd111_Step14(void);
extern void MapObjectMovementCmd111_Step16(void);
extern void MapObjectMovementCmd111_Step18(void);
extern void MapObjectMovementCmd111_Step2(void);
extern void MapObjectMovementCmd111_Step4(void);
extern void MapObjectMovementCmd111_Step6(void);
extern void MapObjectMovementCmd112_Step0(void);

// An address sits where that type has a 1-byte field.
void (*const gMovementCmdSteps_111[21])(void) = {
    MapObjectMovementCmd111_Step0,
    MapObjectMovementCmd108_Step1,
    MapObjectMovementCmd111_Step2,
    MapObjectMovementCmd108_Step1,
    MapObjectMovementCmd111_Step4,
    MapObjectMovementCmd108_Step1,
    MapObjectMovementCmd111_Step6,
    MapObjectMovementCmd108_Step1,
    MapObjectMovementCmd111_Step6,
    MapObjectMovementCmd108_Step1,
    MapObjectMovementCmd111_Step10,
    MapObjectMovementCmd108_Step1,
    MapObjectMovementCmd111_Step10,
    MapObjectMovementCmd108_Step1,
    MapObjectMovementCmd111_Step14,
    MapObjectMovementCmd108_Step1,
    MapObjectMovementCmd111_Step16,
    MapObjectMovementCmd108_Step1,
    MapObjectMovementCmd111_Step18,
    MapObjectMovementCmd108_Step1,
    MapObjectMovementCmd098_Step2,
};

// An address sits where that type has a 1-byte field.
void (*const gMovementCmdSteps_107[15])(void) = {
    MapObjectMovementCmd107_Step0,
    MapObjectMovementCmd108_Step1,
    MapObjectMovementCmd107_Step2,
    MapObjectMovementCmd108_Step1,
    MapObjectMovementCmd107_Step4,
    MapObjectMovementCmd108_Step1,
    MapObjectMovementCmd107_Step6,
    MapObjectMovementCmd108_Step1,
    MapObjectMovementCmd107_Step8,
    MapObjectMovementCmd108_Step1,
    MapObjectMovementCmd107_Step10,
    MapObjectMovementCmd108_Step1,
    MapObjectMovementCmd107_Step12,
    MapObjectMovementCmd108_Step1,
    MapObjectMovementCmd098_Step2,
};

// An address sits where that type has a 1-byte field.
void (*const gMovementCmdSteps_109[15])(void) = {
    MapObjectMovementCmd107_Step0,
    MapObjectMovementCmd108_Step1,
    MapObjectMovementCmd107_Step2,
    MapObjectMovementCmd108_Step1,
    MapObjectMovementCmd107_Step4,
    MapObjectMovementCmd108_Step1,
    MapObjectMovementCmd107_Step6,
    MapObjectMovementCmd108_Step1,
    MapObjectMovementCmd107_Step8,
    MapObjectMovementCmd108_Step1,
    MapObjectMovementCmd107_Step10,
    MapObjectMovementCmd108_Step1,
    MapObjectMovementCmd109_Step12,
    MapObjectMovementCmd108_Step1,
    MapObjectMovementCmd098_Step2,
};

// An address sits where that type has a 1-byte field.
void (*const gMovementCmdSteps_105[11])(void) = {
    MapObjectMovementCmd105_Step0,
    MapObjectMovementCmd108_Step1,
    MapObjectMovementCmd105_Step2,
    MapObjectMovementCmd108_Step1,
    MapObjectMovementCmd105_Step4,
    MapObjectMovementCmd108_Step1,
    MapObjectMovementCmd105_Step6,
    MapObjectMovementCmd108_Step1,
    MapObjectMovementCmd105_Step8,
    MapObjectMovementCmd108_Step1,
    MapObjectMovementCmd098_Step2,
};

// An address sits where that type has a 1-byte field.
void (*const gMovementCmdSteps_106[9])(void) = {
    MapObjectMovementCmd106_Step0,
    MapObjectMovementCmd108_Step1,
    MapObjectMovementCmd106_Step2,
    MapObjectMovementCmd108_Step1,
    MapObjectMovementCmd106_Step4,
    MapObjectMovementCmd108_Step1,
    MapObjectMovementCmd106_Step6,
    MapObjectMovementCmd108_Step1,
    MapObjectMovementCmd098_Step2,
};

// An address sits where that type has a 1-byte field.
void (*const gMovementCmdSteps_112[7])(void) = {
    MapObjectMovementCmd112_Step0,
    MapObjectMovementCmd108_Step1,
    MapObjectMovementCmd112_Step0,
    MapObjectMovementCmd108_Step1,
    MapObjectMovementCmd112_Step0,
    MapObjectMovementCmd108_Step1,
    MapObjectMovementCmd098_Step2,
};

// An address sits where that type has a 1-byte field.
void (*const gMovementCmdSteps_108[5])(void) = {
    MapObjectMovementCmd108_Step0,
    MapObjectMovementCmd108_Step1,
    MapObjectMovementCmd108_Step2,
    MapObjectMovementCmd108_Step1,
    MapObjectMovementCmd098_Step2,
};

// An address sits where that type has a 1-byte field.
void (*const gMovementCmdSteps_110[5])(void) = {
    MapObjectMovementCmd110_Step0,
    MapObjectMovementCmd108_Step1,
    MapObjectMovementCmd108_Step2,
    MapObjectMovementCmd108_Step1,
    MapObjectMovementCmd098_Step2,
};

// An address sits where that type has a 1-byte field.
void (*const gMovementCmdSteps_013[3])(void) = {
    MapObjectMovementCmd013_Step0,
    MapObjectMovementCmd090_Step1,
    MapObjectMovementCmd098_Step2,
};

// An address sits where that type has a 1-byte field.
void (*const gMovementCmdSteps_014[3])(void) = {
    MapObjectMovementCmd014_Step0,
    MapObjectMovementCmd090_Step1,
    MapObjectMovementCmd098_Step2,
};

// An address sits where that type has a 1-byte field.
void (*const gMovementCmdSteps_015[3])(void) = {
    MapObjectMovementCmd015_Step0,
    MapObjectMovementCmd090_Step1,
    MapObjectMovementCmd098_Step2,
};

// An address sits where that type has a 1-byte field.
void (*const gMovementCmdSteps_009[3])(void) = {
    MapObjectMovementCmd009_Step0,
    MapObjectMovementCmd090_Step1,
    MapObjectMovementCmd098_Step2,
};

// An address sits where that type has a 1-byte field.
void (*const gMovementCmdSteps_017[3])(void) = {
    MapObjectMovementCmd017_Step0,
    MapObjectMovementCmd090_Step1,
    MapObjectMovementCmd098_Step2,
};

// An address sits where that type has a 1-byte field.
void (*const gMovementCmdSteps_018[3])(void) = {
    MapObjectMovementCmd018_Step0,
    MapObjectMovementCmd090_Step1,
    MapObjectMovementCmd098_Step2,
};

// An address sits where that type has a 1-byte field.
void (*const gMovementCmdSteps_019[3])(void) = {
    MapObjectMovementCmd019_Step0,
    MapObjectMovementCmd090_Step1,
    MapObjectMovementCmd098_Step2,
};

// An address sits where that type has a 1-byte field.
void (*const gMovementCmdSteps_020[3])(void) = {
    MapObjectMovementCmd020_Step0,
    MapObjectMovementCmd090_Step1,
    MapObjectMovementCmd098_Step2,
};

// An address sits where that type has a 1-byte field.
void (*const gMovementCmdSteps_021[3])(void) = {
    MapObjectMovementCmd021_Step0,
    MapObjectMovementCmd090_Step1,
    MapObjectMovementCmd098_Step2,
};

// An address sits where that type has a 1-byte field.
void (*const gMovementCmdSteps_022[3])(void) = {
    MapObjectMovementCmd022_Step0,
    MapObjectMovementCmd090_Step1,
    MapObjectMovementCmd098_Step2,
};

// An address sits where that type has a 1-byte field.
void (*const gMovementCmdSteps_023[3])(void) = {
    MapObjectMovementCmd023_Step0,
    MapObjectMovementCmd090_Step1,
    MapObjectMovementCmd098_Step2,
};

// An address sits where that type has a 1-byte field.
void (*const gMovementCmdSteps_005[3])(void) = {
    MapObjectMovementCmd005_Step0,
    MapObjectMovementCmd090_Step1,
    MapObjectMovementCmd098_Step2,
};

// An address sits where that type has a 1-byte field.
void (*const gMovementCmdSteps_085[3])(void) = {
    MapObjectMovementCmd085_Step0,
    MapObjectMovementCmd090_Step1,
    MapObjectMovementCmd098_Step2,
};

// An address sits where that type has a 1-byte field.
void (*const gMovementCmdSteps_086[3])(void) = {
    MapObjectMovementCmd086_Step0,
    MapObjectMovementCmd090_Step1,
    MapObjectMovementCmd098_Step2,
};

// An address sits where that type has a 1-byte field.
void (*const gMovementCmdSteps_087[3])(void) = {
    MapObjectMovementCmd087_Step0,
    MapObjectMovementCmd090_Step1,
    MapObjectMovementCmd098_Step2,
};

// An address sits where that type has a 1-byte field.
void (*const gMovementCmdSteps_024[3])(void) = {
    MapObjectMovementCmd024_Step0,
    MapObjectMovementCmd040_Step1,
    MapObjectMovementCmd098_Step2,
};

// An address sits where that type has a 1-byte field.
void (*const gMovementCmdSteps_025[3])(void) = {
    MapObjectMovementCmd025_Step0,
    MapObjectMovementCmd040_Step1,
    MapObjectMovementCmd098_Step2,
};

// An address sits where that type has a 1-byte field.
void (*const gMovementCmdSteps_026[3])(void) = {
    MapObjectMovementCmd026_Step0,
    MapObjectMovementCmd040_Step1,
    MapObjectMovementCmd098_Step2,
};

// An address sits where that type has a 1-byte field.
void (*const gMovementCmdSteps_027[3])(void) = {
    MapObjectMovementCmd027_Step0,
    MapObjectMovementCmd040_Step1,
    MapObjectMovementCmd098_Step2,
};

// An address sits where that type has a 1-byte field.
void (*const gMovementCmdSteps_028[3])(void) = {
    MapObjectMovementCmd028_Step0,
    MapObjectMovementCmd040_Step1,
    MapObjectMovementCmd098_Step2,
};

// An address sits where that type has a 1-byte field.
void (*const gMovementCmdSteps_029[3])(void) = {
    MapObjectMovementCmd029_Step0,
    MapObjectMovementCmd040_Step1,
    MapObjectMovementCmd098_Step2,
};

// An address sits where that type has a 1-byte field.
void (*const gMovementCmdSteps_104[3])(void) = {
    MapObjectMovementCmd104_Step0,
    MapObjectMovementCmd102_Step1,
    MapObjectMovementCmd098_Step2,
};

// An address sits where that type has a 1-byte field.
void (*const gMovementCmdSteps_031[3])(void) = {
    MapObjectMovementCmd031_Step0,
    MapObjectMovementCmd040_Step1,
    MapObjectMovementCmd098_Step2,
};

// An address sits where that type has a 1-byte field.
void (*const gMovementCmdSteps_079[3])(void) = {
    MapObjectMovementCmd079_Step0,
    MapObjectMovementCmd076_Step1,
    MapObjectMovementCmd098_Step2,
};

// An address sits where that type has a 1-byte field.
void (*const gMovementCmdSteps_033[3])(void) = {
    MapObjectMovementCmd033_Step0,
    MapObjectMovementCmd040_Step1,
    MapObjectMovementCmd098_Step2,
};

// An address sits where that type has a 1-byte field.
void (*const gMovementCmdSteps_052[3])(void) = {
    MapObjectMovementCmd052_Step0,
    MapObjectMovementCmd092_Step1,
    MapObjectMovementCmd098_Step2,
};

// An address sits where that type has a 1-byte field.
void (*const gMovementCmdSteps_035[3])(void) = {
    MapObjectMovementCmd035_Step0,
    MapObjectMovementCmd040_Step1,
    MapObjectMovementCmd098_Step2,
};

// An address sits where that type has a 1-byte field.
void (*const gMovementCmdSteps_051[3])(void) = {
    MapObjectMovementCmd051_Step0,
    MapObjectMovementCmd092_Step1,
    MapObjectMovementCmd098_Step2,
};

// An address sits where that type has a 1-byte field.
void (*const gMovementCmdSteps_037[3])(void) = {
    MapObjectMovementCmd037_Step0,
    MapObjectMovementCmd040_Step1,
    MapObjectMovementCmd098_Step2,
};

// An address sits where that type has a 1-byte field.
void (*const gMovementCmdSteps_078[3])(void) = {
    MapObjectMovementCmd078_Step0,
    MapObjectMovementCmd076_Step1,
    MapObjectMovementCmd098_Step2,
};

// An address sits where that type has a 1-byte field.
void (*const gMovementCmdSteps_039[3])(void) = {
    MapObjectMovementCmd039_Step0,
    MapObjectMovementCmd040_Step1,
    MapObjectMovementCmd098_Step2,
};

// An address sits where that type has a 1-byte field.
void (*const gMovementCmdSteps_050[3])(void) = {
    MapObjectMovementCmd050_Step0,
    MapObjectMovementCmd092_Step1,
    MapObjectMovementCmd098_Step2,
};

// An address sits where that type has a 1-byte field.
void (*const gMovementCmdSteps_041[3])(void) = {
    MapObjectMovementCmd041_Step0,
    MapObjectMovementCmd040_Step1,
    MapObjectMovementCmd098_Step2,
};

// An address sits where that type has a 1-byte field.
void (*const gMovementCmdSteps_042[3])(void) = {
    MapObjectMovementCmd042_Step0,
    MapObjectMovementCmd040_Step1,
    MapObjectMovementCmd098_Step2,
};

// An address sits where that type has a 1-byte field.
void (*const gMovementCmdSteps_043[3])(void) = {
    MapObjectMovementCmd043_Step0,
    MapObjectMovementCmd040_Step1,
    MapObjectMovementCmd098_Step2,
};

// An address sits where that type has a 1-byte field.
void (*const gMovementCmdSteps_044[3])(void) = {
    MapObjectMovementCmd044_Step0,
    MapObjectMovementCmd092_Step1,
    MapObjectMovementCmd098_Step2,
};

// An address sits where that type has a 1-byte field.
void (*const gMovementCmdSteps_045[3])(void) = {
    MapObjectMovementCmd045_Step0,
    MapObjectMovementCmd092_Step1,
    MapObjectMovementCmd098_Step2,
};

// An address sits where that type has a 1-byte field.
void (*const gMovementCmdSteps_046[3])(void) = {
    MapObjectMovementCmd046_Step0,
    MapObjectMovementCmd092_Step1,
    MapObjectMovementCmd098_Step2,
};

// An address sits where that type has a 1-byte field.
void (*const gMovementCmdSteps_049[3])(void) = {
    MapObjectMovementCmd049_Step0,
    MapObjectMovementCmd092_Step1,
    MapObjectMovementCmd098_Step2,
};

// An address sits where that type has a 1-byte field.
void (*const gMovementCmdSteps_102[3])(void) = {
    MapObjectMovementCmd102_Step0,
    MapObjectMovementCmd102_Step1,
    MapObjectMovementCmd098_Step2,
};

// An address sits where that type has a 1-byte field.
void (*const gMovementCmdSteps_034[3])(void) = {
    MapObjectMovementCmd034_Step0,
    MapObjectMovementCmd040_Step1,
    MapObjectMovementCmd098_Step2,
};

// An address sits where that type has a 1-byte field.
void (*const gMovementCmdSteps_076[3])(void) = {
    MapObjectMovementCmd076_Step0,
    MapObjectMovementCmd076_Step1,
    MapObjectMovementCmd098_Step2,
};

// An address sits where that type has a 1-byte field.
void (*const gMovementCmdSteps_036[3])(void) = {
    MapObjectMovementCmd036_Step0,
    MapObjectMovementCmd040_Step1,
    MapObjectMovementCmd098_Step2,
};

// An address sits where that type has a 1-byte field.
void (*const gMovementCmdSteps_096[3])(void) = {
    MapObjectMovementCmd096_Step0,
    MapObjectMovementCmd098_Step1,
    MapObjectMovementCmd098_Step2,
};

// An address sits where that type has a 1-byte field.
void (*const gMovementCmdSteps_012[3])(void) = {
    MapObjectMovementCmd012_Step0,
    MapObjectMovementCmd090_Step1,
    MapObjectMovementCmd098_Step2,
};

// An address sits where that type has a 1-byte field.
void (*const gMovementCmdSteps_054[3])(void) = {
    MapObjectMovementCmd054_Step0,
    MapObjectMovementCmd092_Step1,
    MapObjectMovementCmd098_Step2,
};

// An address sits where that type has a 1-byte field.
void (*const gMovementCmdSteps_081[3])(void) = {
    MapObjectMovementCmd081_Step0,
    MapObjectMovementCmd082_Step1,
    MapObjectMovementCmd098_Step2,
};

// An address sits where that type has a 1-byte field.
void (*const gMovementCmdSteps_057[3])(void) = {
    MapObjectMovementCmd057_Step0,
    MapObjectMovementCmd092_Step1,
    MapObjectMovementCmd098_Step2,
};

// An address sits where that type has a 1-byte field.
void (*const gMovementCmdSteps_058[3])(void) = {
    MapObjectMovementCmd058_Step0,
    MapObjectMovementCmd092_Step1,
    MapObjectMovementCmd098_Step2,
};

// An address sits where that type has a 1-byte field.
void (*const gMovementCmdSteps_059[3])(void) = {
    MapObjectMovementCmd059_Step0,
    MapObjectMovementCmd092_Step1,
    MapObjectMovementCmd098_Step2,
};

// An address sits where that type has a 1-byte field.
void (*const gMovementCmdSteps_008[3])(void) = {
    MapObjectMovementCmd008_Step0,
    MapObjectMovementCmd090_Step1,
    MapObjectMovementCmd098_Step2,
};

// An address sits where that type has a 1-byte field.
void (*const gMovementCmdSteps_093[3])(void) = {
    MapObjectMovementCmd093_Step0,
    MapObjectMovementCmd092_Step1,
    MapObjectMovementCmd098_Step2,
};

// An address sits where that type has a 1-byte field.
void (*const gMovementCmdSteps_094[3])(void) = {
    MapObjectMovementCmd094_Step0,
    MapObjectMovementCmd092_Step1,
    MapObjectMovementCmd098_Step2,
};

// An address sits where that type has a 1-byte field.
void (*const gMovementCmdSteps_095[3])(void) = {
    MapObjectMovementCmd095_Step0,
    MapObjectMovementCmd092_Step1,
    MapObjectMovementCmd098_Step2,
};

// An address sits where that type has a 1-byte field.
void (*const gMovementCmdSteps_016[3])(void) = {
    MapObjectMovementCmd016_Step0,
    MapObjectMovementCmd090_Step1,
    MapObjectMovementCmd098_Step2,
};

// An address sits where that type has a 1-byte field.
void (*const gMovementCmdSteps_061[3])(void) = {
    MapObjectMovementCmd061_Step0,
    MapObjectMovementCmd064_Step1,
    MapObjectMovementCmd098_Step2,
};

// An address sits where that type has a 1-byte field.
void (*const gMovementCmdSteps_062[3])(void) = {
    MapObjectMovementCmd062_Step0,
    MapObjectMovementCmd064_Step1,
    MapObjectMovementCmd098_Step2,
};

// An address sits where that type has a 1-byte field.
void (*const gMovementCmdSteps_063[3])(void) = {
    MapObjectMovementCmd063_Step0,
    MapObjectMovementCmd064_Step1,
    MapObjectMovementCmd098_Step2,
};

// An address sits where that type has a 1-byte field.
void (*const gMovementCmdSteps_084[3])(void) = {
    MapObjectMovementCmd084_Step0,
    MapObjectMovementCmd090_Step1,
    MapObjectMovementCmd098_Step2,
};

// An address sits where that type has a 1-byte field.
void (*const gMovementCmdSteps_065[3])(void) = {
    MapObjectMovementCmd065_Step0,
    MapObjectMovementCmd064_Step1,
    MapObjectMovementCmd098_Step2,
};

// An address sits where that type has a 1-byte field.
void (*const gMovementCmdSteps_066[3])(void) = {
    MapObjectMovementCmd066_Step0,
    MapObjectMovementCmd064_Step1,
    MapObjectMovementCmd098_Step2,
};

// An address sits where that type has a 1-byte field.
void (*const gMovementCmdSteps_067[3])(void) = {
    MapObjectMovementCmd067_Step0,
    MapObjectMovementCmd067_Step1,
    MapObjectMovementCmd098_Step2,
};

// An address sits where that type has a 1-byte field.
void (*const gMovementCmdSteps_068[3])(void) = {
    MapObjectMovementCmd068_Step0,
    MapObjectMovementCmd068_Step1,
    MapObjectMovementCmd098_Step2,
};

// An address sits where that type has a 1-byte field.
void (*const gMovementCmdSteps_030[3])(void) = {
    MapObjectMovementCmd030_Step0,
    MapObjectMovementCmd040_Step1,
    MapObjectMovementCmd098_Step2,
};

// An address sits where that type has a 1-byte field.
void (*const gMovementCmdSteps_077[3])(void) = {
    MapObjectMovementCmd077_Step0,
    MapObjectMovementCmd076_Step1,
    MapObjectMovementCmd098_Step2,
};

// An address sits where that type has a 1-byte field.
void (*const gMovementCmdSteps_053[3])(void) = {
    MapObjectMovementCmd053_Step0,
    MapObjectMovementCmd092_Step1,
    MapObjectMovementCmd098_Step2,
};

// An address sits where that type has a 1-byte field.
void (*const gMovementCmdSteps_098[3])(void) = {
    MapObjectMovementCmd098_Step0,
    MapObjectMovementCmd098_Step1,
    MapObjectMovementCmd098_Step2,
};

// An address sits where that type has a 1-byte field.
void (*const gMovementCmdSteps_038[3])(void) = {
    MapObjectMovementCmd038_Step0,
    MapObjectMovementCmd040_Step1,
    MapObjectMovementCmd098_Step2,
};

// An address sits where that type has a 1-byte field.
void (*const gMovementCmdSteps_040[3])(void) = {
    MapObjectMovementCmd040_Step0,
    MapObjectMovementCmd040_Step1,
    MapObjectMovementCmd098_Step2,
};

// An address sits where that type has a 1-byte field.
void (*const gMovementCmdSteps_101[3])(void) = {
    MapObjectMovementCmd101_Step0,
    MapObjectMovementCmd101_Step1,
    MapObjectMovementCmd098_Step2,
};

// An address sits where that type has a 1-byte field.
void (*const gMovementCmdSteps_103[3])(void) = {
    MapObjectMovementCmd103_Step0,
    MapObjectMovementCmd075_Step1,
    MapObjectMovementCmd098_Step2,
};

// An address sits where that type has a 1-byte field.
void (*const gMovementCmdSteps_075[3])(void) = {
    MapObjectMovementCmd075_Step0,
    MapObjectMovementCmd075_Step1,
    MapObjectMovementCmd098_Step2,
};

// An address sits where that type has a 1-byte field.
void (*const gMovementCmdSteps_100[3])(void) = {
    MapObjectMovementCmd100_Step0,
    MapObjectMovementCmd100_Step1,
    MapObjectMovementCmd098_Step2,
};

// An address sits where that type has a 1-byte field.
void (*const gMovementCmdSteps_007[3])(void) = {
    MapObjectMovementCmd007_Step0,
    MapObjectMovementCmd090_Step1,
    MapObjectMovementCmd098_Step2,
};

// An address sits where that type has a 1-byte field.
void (*const gMovementCmdSteps_055[3])(void) = {
    MapObjectMovementCmd055_Step0,
    MapObjectMovementCmd092_Step1,
    MapObjectMovementCmd098_Step2,
};

// An address sits where that type has a 1-byte field.
void (*const gMovementCmdSteps_080[3])(void) = {
    MapObjectMovementCmd080_Step0,
    MapObjectMovementCmd082_Step1,
    MapObjectMovementCmd098_Step2,
};

// An address sits where that type has a 1-byte field.
void (*const gMovementCmdSteps_032[3])(void) = {
    MapObjectMovementCmd032_Step0,
    MapObjectMovementCmd040_Step1,
    MapObjectMovementCmd098_Step2,
};

// An address sits where that type has a 1-byte field.
void (*const gMovementCmdSteps_048[3])(void) = {
    MapObjectMovementCmd048_Step0,
    MapObjectMovementCmd092_Step1,
    MapObjectMovementCmd098_Step2,
};

// An address sits where that type has a 1-byte field.
void (*const gMovementCmdSteps_092[3])(void) = {
    MapObjectMovementCmd092_Step0,
    MapObjectMovementCmd092_Step1,
    MapObjectMovementCmd098_Step2,
};

// An address sits where that type has a 1-byte field.
void (*const gMovementCmdSteps_088[3])(void) = {
    MapObjectMovementCmd088_Step0,
    MapObjectMovementCmd090_Step1,
    MapObjectMovementCmd098_Step2,
};

// An address sits where that type has a 1-byte field.
void (*const gMovementCmdSteps_060[3])(void) = {
    MapObjectMovementCmd060_Step0,
    MapObjectMovementCmd064_Step1,
    MapObjectMovementCmd098_Step2,
};

// An address sits where that type has a 1-byte field.
void (*const gMovementCmdSteps_090[3])(void) = {
    MapObjectMovementCmd090_Step0,
    MapObjectMovementCmd090_Step1,
    MapObjectMovementCmd098_Step2,
};

// An address sits where that type has a 1-byte field.
void (*const gMovementCmdSteps_056[3])(void) = {
    MapObjectMovementCmd056_Step0,
    MapObjectMovementCmd092_Step1,
    MapObjectMovementCmd098_Step2,
};

// An address sits where that type has a 1-byte field.
void (*const gMovementCmdSteps_082[3])(void) = {
    MapObjectMovementCmd082_Step0,
    MapObjectMovementCmd082_Step1,
    MapObjectMovementCmd098_Step2,
};

// An address sits where that type has a 1-byte field.
void (*const gMovementCmdSteps_097[3])(void) = {
    MapObjectMovementCmd097_Step0,
    MapObjectMovementCmd098_Step1,
    MapObjectMovementCmd098_Step2,
};

// An address sits where that type has a 1-byte field.
void (*const gMovementCmdSteps_064[3])(void) = {
    MapObjectMovementCmd064_Step0,
    MapObjectMovementCmd064_Step1,
    MapObjectMovementCmd098_Step2,
};

// An address sits where that type has a 1-byte field.
void (*const gMovementCmdSteps_047[3])(void) = {
    MapObjectMovementCmd047_Step0,
    MapObjectMovementCmd092_Step1,
    MapObjectMovementCmd098_Step2,
};

// An address sits where that type has a 1-byte field.
void (*const gMovementCmdSteps_099[3])(void) = {
    MapObjectMovementCmd099_Step0,
    MapObjectMovementCmd098_Step1,
    MapObjectMovementCmd098_Step2,
};
