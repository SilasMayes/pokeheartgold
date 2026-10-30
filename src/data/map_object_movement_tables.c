// Converted from asm/map_object_movement_tables.s by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout. Keep that when editing, or rerun tools/s2c.py.

#include "global.h"

#include "map_object_movement_commands_internal.h"

#pragma force_active on

extern void AlternatingSpinMovement_Init(void);
extern void AlternatingSpinMovement_Update(void);
extern void BackAndForthMovement_Init(void);
extern void BackAndForthMovement_Update(void);
extern void FaceDirectionMovement_InitDown(void);
extern void FaceDirectionMovement_InitLeft(void);
extern void FaceDirectionMovement_InitRight(void);
extern void FaceDirectionMovement_InitUp(void);
extern void FaceDirectionMovement_Update(void);
extern void FollowPartnerMovement_Delete(void);
extern void FollowPartnerMovement_Init(void);
extern void FollowPartnerMovement_Resume(void);
extern void FollowPartnerMovement_Update(void);
extern void FollowPlayerMovement_Delete(void);
extern void FollowPlayerMovement_Init(void);
extern void FollowPlayerMovement_Update(void);
extern void FollowPlayerMovement_UpdateFollowMon(void);
extern void FollowPlayerMovement_UpdateMirror(void);
extern void HiddenObjectMovement_Delete(void);
extern void HiddenObjectMovement_InitCover0(void);
extern void HiddenObjectMovement_InitCover1(void);
extern void HiddenObjectMovement_InitCover2(void);
extern void HiddenObjectMovement_InitCover3(void);
extern void HiddenObjectMovement_Resume(void);
extern void HiddenObjectMovement_Update(void);
extern void PathMovement_InitEastNorthSouthWest(void);
extern void PathMovement_InitEastNorthWestSouth(void);
extern void PathMovement_InitEastSouthNorthWest(void);
extern void PathMovement_InitEastSouthWestNorth(void);
extern void PathMovement_InitEastWestNorthSouth(void);
extern void PathMovement_InitEastWestSouthNorth(void);
extern void PathMovement_InitNorthEastSouthWest(void);
extern void PathMovement_InitNorthEastWestSouth(void);
extern void PathMovement_InitNorthSouthEastWest(void);
extern void PathMovement_InitNorthSouthWestEast(void);
extern void PathMovement_InitNorthWestSouthEast(void);
extern void PathMovement_InitSouthEastNorthWest(void);
extern void PathMovement_InitSouthEastWestNorth(void);
extern void PathMovement_InitSouthNorthEastWest(void);
extern void PathMovement_InitSouthNorthWestEast(void);
extern void PathMovement_InitSouthWestEastNorth(void);
extern void PathMovement_InitSouthWestNorthEast(void);
extern void PathMovement_InitWestEastNorthSouth(void);
extern void PathMovement_InitWestEastSouthNorth(void);
extern void PathMovement_InitWestEastSouthNorth2(void);
extern void PathMovement_InitWestNorthEastSouth(void);
extern void PathMovement_InitWestNorthSouthEast(void);
extern void PathMovement_InitWestSouthEastNorth(void);
extern void PathMovement_InitWestSouthNorthEast(void);
extern void PathMovement_Update(void);
extern void RandomLookMovement_Delete(void);
extern void RandomLookMovement_InitAnyDirection(void);
extern void RandomLookMovement_InitDownLeft(void);
extern void RandomLookMovement_InitDownLeftRight(void);
extern void RandomLookMovement_InitDownRight(void);
extern void RandomLookMovement_InitLeftRight(void);
extern void RandomLookMovement_InitUpDown(void);
extern void RandomLookMovement_InitUpDownLeft(void);
extern void RandomLookMovement_InitUpDownRight(void);
extern void RandomLookMovement_InitUpLeft(void);
extern void RandomLookMovement_InitUpLeftRight(void);
extern void RandomLookMovement_InitUpRight(void);
extern void RandomLookMovement_Update(void);
extern void RandomWalkMovement_InitAnyDirection(void);
extern void RandomWalkMovement_InitLeftRight(void);
extern void RandomWalkMovement_InitUpDown(void);
extern void RandomWalkMovement_Update(void);
extern void SpinMovement_InitClockwise(void);
extern void SpinMovement_InitCounterclockwise(void);
extern void SpinMovement_Update(void);
extern const u8 gMovementCmdSteps_000[];
extern const u8 gMovementCmdSteps_001[];
extern const u8 gMovementCmdSteps_002[];
extern const u8 gMovementCmdSteps_003[];
extern const u8 gMovementCmdSteps_004[];
extern const u8 gMovementCmdSteps_005[];
extern const u8 gMovementCmdSteps_006[];
extern const u8 gMovementCmdSteps_007[];
extern const u8 gMovementCmdSteps_008[];
extern const u8 gMovementCmdSteps_009[];
extern const u8 gMovementCmdSteps_010[];
extern const u8 gMovementCmdSteps_011[];
extern const u8 gMovementCmdSteps_012[];
extern const u8 gMovementCmdSteps_013[];
extern const u8 gMovementCmdSteps_014[];
extern const u8 gMovementCmdSteps_015[];
extern const u8 gMovementCmdSteps_016[];
extern const u8 gMovementCmdSteps_017[];
extern const u8 gMovementCmdSteps_018[];
extern const u8 gMovementCmdSteps_019[];
extern const u8 gMovementCmdSteps_020[];
extern const u8 gMovementCmdSteps_021[];
extern const u8 gMovementCmdSteps_022[];
extern const u8 gMovementCmdSteps_023[];
extern const u8 gMovementCmdSteps_024[];
extern const u8 gMovementCmdSteps_025[];
extern const u8 gMovementCmdSteps_026[];
extern const u8 gMovementCmdSteps_027[];
extern const u8 gMovementCmdSteps_028[];
extern const u8 gMovementCmdSteps_029[];
extern const u8 gMovementCmdSteps_030[];
extern const u8 gMovementCmdSteps_031[];
extern const u8 gMovementCmdSteps_032[];
extern const u8 gMovementCmdSteps_033[];
extern const u8 gMovementCmdSteps_034[];
extern const u8 gMovementCmdSteps_035[];
extern const u8 gMovementCmdSteps_036[];
extern const u8 gMovementCmdSteps_037[];
extern const u8 gMovementCmdSteps_038[];
extern const u8 gMovementCmdSteps_039[];
extern const u8 gMovementCmdSteps_040[];
extern const u8 gMovementCmdSteps_041[];
extern const u8 gMovementCmdSteps_042[];
extern const u8 gMovementCmdSteps_043[];
extern const u8 gMovementCmdSteps_044[];
extern const u8 gMovementCmdSteps_045[];
extern const u8 gMovementCmdSteps_046[];
extern const u8 gMovementCmdSteps_047[];
extern const u8 gMovementCmdSteps_048[];
extern const u8 gMovementCmdSteps_049[];
extern const u8 gMovementCmdSteps_050[];
extern const u8 gMovementCmdSteps_051[];
extern const u8 gMovementCmdSteps_052[];
extern const u8 gMovementCmdSteps_053[];
extern const u8 gMovementCmdSteps_054[];
extern const u8 gMovementCmdSteps_055[];
extern const u8 gMovementCmdSteps_056[];
extern const u8 gMovementCmdSteps_057[];
extern const u8 gMovementCmdSteps_058[];
extern const u8 gMovementCmdSteps_059[];
extern const u8 gMovementCmdSteps_060[];
extern const u8 gMovementCmdSteps_061[];
extern const u8 gMovementCmdSteps_062[];
extern const u8 gMovementCmdSteps_063[];
extern const u8 gMovementCmdSteps_064[];
extern const u8 gMovementCmdSteps_065[];
extern const u8 gMovementCmdSteps_066[];
extern const u8 gMovementCmdSteps_067[];
extern const u8 gMovementCmdSteps_068[];
extern const u8 gMovementCmdSteps_069[];
extern const u8 gMovementCmdSteps_070[];
extern const u8 gMovementCmdSteps_071[];
extern const u8 gMovementCmdSteps_072[];
extern const u8 gMovementCmdSteps_073[];
extern const u8 gMovementCmdSteps_074[];
extern const u8 gMovementCmdSteps_075[];
extern const u8 gMovementCmdSteps_076[];
extern const u8 gMovementCmdSteps_077[];
extern const u8 gMovementCmdSteps_078[];
extern const u8 gMovementCmdSteps_079[];
extern const u8 gMovementCmdSteps_080[];
extern const u8 gMovementCmdSteps_081[];
extern const u8 gMovementCmdSteps_082[];
extern const u8 gMovementCmdSteps_083[];
extern const u8 gMovementCmdSteps_084[];
extern const u8 gMovementCmdSteps_085[];
extern const u8 gMovementCmdSteps_086[];
extern const u8 gMovementCmdSteps_087[];
extern const u8 gMovementCmdSteps_088[];
extern const u8 gMovementCmdSteps_089[];
extern const u8 gMovementCmdSteps_090[];
extern const u8 gMovementCmdSteps_091[];
extern const u8 gMovementCmdSteps_092[];
extern const u8 gMovementCmdSteps_093[];
extern const u8 gMovementCmdSteps_094[];
extern const u8 gMovementCmdSteps_095[];
extern const u8 gMovementCmdSteps_096[];
extern const u8 gMovementCmdSteps_097[];
extern const u8 gMovementCmdSteps_098[];
extern const u8 gMovementCmdSteps_099[];
extern const u8 gMovementCmdSteps_100[];
extern const u8 gMovementCmdSteps_101[];
extern const u8 gMovementCmdSteps_102[];
extern const u8 gMovementCmdSteps_103[];
extern const u8 gMovementCmdSteps_104[];
extern const u8 gMovementCmdSteps_105[];
extern const u8 gMovementCmdSteps_106[];
extern const u8 gMovementCmdSteps_107[];
extern const u8 gMovementCmdSteps_108[];
extern const u8 gMovementCmdSteps_109[];
extern const u8 gMovementCmdSteps_110[];
extern const u8 gMovementCmdSteps_111[];
extern const u8 gMovementCmdSteps_112[];

struct sPlayerMovementCallbacks_Layout {
    u32 unk0;
    void (*unk4)(void);
    void (*unk8)(void);
    void (*unkC)(void);
    void (*unk10)(void);
};
struct sRandomLookAnyDirectionMovementCallbacks_Layout {
    u32 unk0;
    void (*unk4)(void);
    void (*unk8)(void);
    void (*unkC)(void);
    void (*unk10)(void);
};
struct sRandomWalkAnyDirectionMovementCallbacks_Layout {
    u32 unk0;
    void (*unk4)(void);
    void (*unk8)(void);
    void (*unkC)(void);
    void (*unk10)(void);
};
struct sRandomWalkUpDownMovementCallbacks_Layout {
    u32 unk0;
    void (*unk4)(void);
    void (*unk8)(void);
    void (*unkC)(void);
    void (*unk10)(void);
};
struct sRandomWalkLeftRightMovementCallbacks_Layout {
    u32 unk0;
    void (*unk4)(void);
    void (*unk8)(void);
    void (*unkC)(void);
    void (*unk10)(void);
};
struct sRandomLookUpLeftMovementCallbacks_Layout {
    u32 unk0;
    void (*unk4)(void);
    void (*unk8)(void);
    void (*unkC)(void);
    void (*unk10)(void);
};
struct sRandomLookUpRightMovementCallbacks_Layout {
    u32 unk0;
    void (*unk4)(void);
    void (*unk8)(void);
    void (*unkC)(void);
    void (*unk10)(void);
};
struct sRandomLookDownLeftMovementCallbacks_Layout {
    u32 unk0;
    void (*unk4)(void);
    void (*unk8)(void);
    void (*unkC)(void);
    void (*unk10)(void);
};
struct sRandomLookDownRightMovementCallbacks_Layout {
    u32 unk0;
    void (*unk4)(void);
    void (*unk8)(void);
    void (*unkC)(void);
    void (*unk10)(void);
};
struct sRandomLookUpDownLeftMovementCallbacks_Layout {
    u32 unk0;
    void (*unk4)(void);
    void (*unk8)(void);
    void (*unkC)(void);
    void (*unk10)(void);
};
struct sRandomLookUpDownRightMovementCallbacks_Layout {
    u32 unk0;
    void (*unk4)(void);
    void (*unk8)(void);
    void (*unkC)(void);
    void (*unk10)(void);
};
struct sRandomLookUpLeftRightMovementCallbacks_Layout {
    u32 unk0;
    void (*unk4)(void);
    void (*unk8)(void);
    void (*unkC)(void);
    void (*unk10)(void);
};
struct sRandomLookDownLeftRightMovementCallbacks_Layout {
    u32 unk0;
    void (*unk4)(void);
    void (*unk8)(void);
    void (*unkC)(void);
    void (*unk10)(void);
};
struct sFaceDirectionUpMovementCallbacks_Layout {
    u32 unk0;
    void (*unk4)(void);
    void (*unk8)(void);
    void (*unkC)(void);
    void (*unk10)(void);
};
struct sFaceDirectionDownMovementCallbacks_Layout {
    u32 unk0;
    void (*unk4)(void);
    void (*unk8)(void);
    void (*unkC)(void);
    void (*unk10)(void);
};
struct sFaceDirectionLeftMovementCallbacks_Layout {
    u32 unk0;
    void (*unk4)(void);
    void (*unk8)(void);
    void (*unkC)(void);
    void (*unk10)(void);
};
struct sFaceDirectionRightMovementCallbacks_Layout {
    u32 unk0;
    void (*unk4)(void);
    void (*unk8)(void);
    void (*unkC)(void);
    void (*unk10)(void);
};
struct sSpinCounterclockwiseMovementCallbacks_Layout {
    u32 unk0;
    void (*unk4)(void);
    void (*unk8)(void);
    void (*unkC)(void);
    void (*unk10)(void);
};
struct sSpinClockwiseMovementCallbacks_Layout {
    u32 unk0;
    void (*unk4)(void);
    void (*unk8)(void);
    void (*unkC)(void);
    void (*unk10)(void);
};
struct sBackAndForthMovementCallbacks_Layout {
    u32 unk0;
    void (*unk4)(void);
    void (*unk8)(void);
    void (*unkC)(void);
    void (*unk10)(void);
};
struct sPathTable14MovementCallbacks_Layout {
    u32 unk0;
    void (*unk4)(void);
    void (*unk8)(void);
    void (*unkC)(void);
    void (*unk10)(void);
};
struct sPathTable15MovementCallbacks_Layout {
    u32 unk0;
    void (*unk4)(void);
    void (*unk8)(void);
    void (*unkC)(void);
    void (*unk10)(void);
};
struct sPathTable16MovementCallbacks_Layout {
    u32 unk0;
    void (*unk4)(void);
    void (*unk8)(void);
    void (*unkC)(void);
    void (*unk10)(void);
};
struct sPathTable17MovementCallbacks_Layout {
    u32 unk0;
    void (*unk4)(void);
    void (*unk8)(void);
    void (*unkC)(void);
    void (*unk10)(void);
};
struct sPathTable18MovementCallbacks_Layout {
    u32 unk0;
    void (*unk4)(void);
    void (*unk8)(void);
    void (*unkC)(void);
    void (*unk10)(void);
};
struct sPathTable19MovementCallbacks_Layout {
    u32 unk0;
    void (*unk4)(void);
    void (*unk8)(void);
    void (*unkC)(void);
    void (*unk10)(void);
};
struct sPathTable20MovementCallbacks_Layout {
    u32 unk0;
    void (*unk4)(void);
    void (*unk8)(void);
    void (*unkC)(void);
    void (*unk10)(void);
};
struct sPathTable21MovementCallbacks_Layout {
    u32 unk0;
    void (*unk4)(void);
    void (*unk8)(void);
    void (*unkC)(void);
    void (*unk10)(void);
};
struct sPathTable22MovementCallbacks_Layout {
    u32 unk0;
    void (*unk4)(void);
    void (*unk8)(void);
    void (*unkC)(void);
    void (*unk10)(void);
};
struct sPathTable23MovementCallbacks_Layout {
    u32 unk0;
    void (*unk4)(void);
    void (*unk8)(void);
    void (*unkC)(void);
    void (*unk10)(void);
};
struct sPathTable24MovementCallbacks_Layout {
    u32 unk0;
    void (*unk4)(void);
    void (*unk8)(void);
    void (*unkC)(void);
    void (*unk10)(void);
};
struct sPathTable25MovementCallbacks_Layout {
    u32 unk0;
    void (*unk4)(void);
    void (*unk8)(void);
    void (*unkC)(void);
    void (*unk10)(void);
};
struct sPathTable26MovementCallbacks_Layout {
    u32 unk0;
    void (*unk4)(void);
    void (*unk8)(void);
    void (*unkC)(void);
    void (*unk10)(void);
};
struct sPathTable27MovementCallbacks_Layout {
    u32 unk0;
    void (*unk4)(void);
    void (*unk8)(void);
    void (*unkC)(void);
    void (*unk10)(void);
};
struct sPathTable28MovementCallbacks_Layout {
    u32 unk0;
    void (*unk4)(void);
    void (*unk8)(void);
    void (*unkC)(void);
    void (*unk10)(void);
};
struct sPathTable29MovementCallbacks_Layout {
    u32 unk0;
    void (*unk4)(void);
    void (*unk8)(void);
    void (*unkC)(void);
    void (*unk10)(void);
};
struct sPathTable30MovementCallbacks_Layout {
    u32 unk0;
    void (*unk4)(void);
    void (*unk8)(void);
    void (*unkC)(void);
    void (*unk10)(void);
};
struct sPathTable31MovementCallbacks_Layout {
    u32 unk0;
    void (*unk4)(void);
    void (*unk8)(void);
    void (*unkC)(void);
    void (*unk10)(void);
};
struct sPathTable32MovementCallbacks_Layout {
    u32 unk0;
    void (*unk4)(void);
    void (*unk8)(void);
    void (*unkC)(void);
    void (*unk10)(void);
};
struct sPathTable33MovementCallbacks_Layout {
    u32 unk0;
    void (*unk4)(void);
    void (*unk8)(void);
    void (*unkC)(void);
    void (*unk10)(void);
};
struct sPathTable34MovementCallbacks_Layout {
    u32 unk0;
    void (*unk4)(void);
    void (*unk8)(void);
    void (*unkC)(void);
    void (*unk10)(void);
};
struct sPathTable35MovementCallbacks_Layout {
    u32 unk0;
    void (*unk4)(void);
    void (*unk8)(void);
    void (*unkC)(void);
    void (*unk10)(void);
};
struct sPathTable36MovementCallbacks_Layout {
    u32 unk0;
    void (*unk4)(void);
    void (*unk8)(void);
    void (*unkC)(void);
    void (*unk10)(void);
};
struct sPathTable37MovementCallbacks_Layout {
    u32 unk0;
    void (*unk4)(void);
    void (*unk8)(void);
    void (*unkC)(void);
    void (*unk10)(void);
};
struct sRandomLookUpDownMovementCallbacks_Layout {
    u32 unk0;
    void (*unk4)(void);
    void (*unk8)(void);
    void (*unkC)(void);
    void (*unk10)(void);
};
struct sRandomLookLeftRightMovementCallbacks_Layout {
    u32 unk0;
    void (*unk4)(void);
    void (*unk8)(void);
    void (*unkC)(void);
    void (*unk10)(void);
};
struct sFollowPlayer48MovementCallbacks_Layout {
    u32 unk0;
    void (*unk4)(void);
    void (*unk8)(void);
    void (*unkC)(void);
    void (*unk10)(void);
};
struct sAlternatingSpinMovementCallbacks_Layout {
    u32 unk0;
    void (*unk4)(void);
    void (*unk8)(void);
    void (*unkC)(void);
    void (*unk10)(void);
};
struct sFollowPartnerMovementCallbacks_Layout {
    u32 unk0;
    void (*unk4)(void);
    void (*unk8)(void);
    void (*unkC)(void);
    void (*unk10)(void);
};
struct sHiddenObjectCover0MovementCallbacks_Layout {
    u32 unk0;
    void (*unk4)(void);
    void (*unk8)(void);
    void (*unkC)(void);
    void (*unk10)(void);
};
struct sHiddenObjectCover1MovementCallbacks_Layout {
    u32 unk0;
    void (*unk4)(void);
    void (*unk8)(void);
    void (*unkC)(void);
    void (*unk10)(void);
};
struct sHiddenObjectCover2MovementCallbacks_Layout {
    u32 unk0;
    void (*unk4)(void);
    void (*unk8)(void);
    void (*unkC)(void);
    void (*unk10)(void);
};
struct sHiddenObjectCover3MovementCallbacks_Layout {
    u32 unk0;
    void (*unk4)(void);
    void (*unk8)(void);
    void (*unkC)(void);
    void (*unk10)(void);
};
struct sFollowPlayer55MovementCallbacks_Layout {
    u32 unk0;
    void (*unk4)(void);
    void (*unk8)(void);
    void (*unkC)(void);
    void (*unk10)(void);
};
struct sFollowPlayer56MovementCallbacks_Layout {
    u32 unk0;
    void (*unk4)(void);
    void (*unk8)(void);
    void (*unkC)(void);
    void (*unk10)(void);
};
extern void (*const sNoMovementCallbacks[5])(void);
extern const struct sPlayerMovementCallbacks_Layout sPlayerMovementCallbacks;
extern const struct sRandomLookAnyDirectionMovementCallbacks_Layout sRandomLookAnyDirectionMovementCallbacks;
extern const struct sRandomWalkAnyDirectionMovementCallbacks_Layout sRandomWalkAnyDirectionMovementCallbacks;
extern const struct sRandomWalkUpDownMovementCallbacks_Layout sRandomWalkUpDownMovementCallbacks;
extern const struct sRandomWalkLeftRightMovementCallbacks_Layout sRandomWalkLeftRightMovementCallbacks;
extern const struct sRandomLookUpLeftMovementCallbacks_Layout sRandomLookUpLeftMovementCallbacks;
extern const struct sRandomLookUpRightMovementCallbacks_Layout sRandomLookUpRightMovementCallbacks;
extern const struct sRandomLookDownLeftMovementCallbacks_Layout sRandomLookDownLeftMovementCallbacks;
extern const struct sRandomLookDownRightMovementCallbacks_Layout sRandomLookDownRightMovementCallbacks;
extern const struct sRandomLookUpDownLeftMovementCallbacks_Layout sRandomLookUpDownLeftMovementCallbacks;
extern const struct sRandomLookUpDownRightMovementCallbacks_Layout sRandomLookUpDownRightMovementCallbacks;
extern const struct sRandomLookUpLeftRightMovementCallbacks_Layout sRandomLookUpLeftRightMovementCallbacks;
extern const struct sRandomLookDownLeftRightMovementCallbacks_Layout sRandomLookDownLeftRightMovementCallbacks;
extern const struct sFaceDirectionUpMovementCallbacks_Layout sFaceDirectionUpMovementCallbacks;
extern const struct sFaceDirectionDownMovementCallbacks_Layout sFaceDirectionDownMovementCallbacks;
extern const struct sFaceDirectionLeftMovementCallbacks_Layout sFaceDirectionLeftMovementCallbacks;
extern const struct sFaceDirectionRightMovementCallbacks_Layout sFaceDirectionRightMovementCallbacks;
extern const struct sSpinCounterclockwiseMovementCallbacks_Layout sSpinCounterclockwiseMovementCallbacks;
extern const struct sSpinClockwiseMovementCallbacks_Layout sSpinClockwiseMovementCallbacks;
extern const struct sBackAndForthMovementCallbacks_Layout sBackAndForthMovementCallbacks;
extern const struct sPathTable14MovementCallbacks_Layout sPathTable14MovementCallbacks;
extern const struct sPathTable15MovementCallbacks_Layout sPathTable15MovementCallbacks;
extern const struct sPathTable16MovementCallbacks_Layout sPathTable16MovementCallbacks;
extern const struct sPathTable17MovementCallbacks_Layout sPathTable17MovementCallbacks;
extern const struct sPathTable18MovementCallbacks_Layout sPathTable18MovementCallbacks;
extern const struct sPathTable19MovementCallbacks_Layout sPathTable19MovementCallbacks;
extern const struct sPathTable20MovementCallbacks_Layout sPathTable20MovementCallbacks;
extern const struct sPathTable21MovementCallbacks_Layout sPathTable21MovementCallbacks;
extern const struct sPathTable22MovementCallbacks_Layout sPathTable22MovementCallbacks;
extern const struct sPathTable23MovementCallbacks_Layout sPathTable23MovementCallbacks;
extern const struct sPathTable24MovementCallbacks_Layout sPathTable24MovementCallbacks;
extern const struct sPathTable25MovementCallbacks_Layout sPathTable25MovementCallbacks;
extern const struct sPathTable26MovementCallbacks_Layout sPathTable26MovementCallbacks;
extern const struct sPathTable27MovementCallbacks_Layout sPathTable27MovementCallbacks;
extern const struct sPathTable28MovementCallbacks_Layout sPathTable28MovementCallbacks;
extern const struct sPathTable29MovementCallbacks_Layout sPathTable29MovementCallbacks;
extern const struct sPathTable30MovementCallbacks_Layout sPathTable30MovementCallbacks;
extern const struct sPathTable31MovementCallbacks_Layout sPathTable31MovementCallbacks;
extern const struct sPathTable32MovementCallbacks_Layout sPathTable32MovementCallbacks;
extern const struct sPathTable33MovementCallbacks_Layout sPathTable33MovementCallbacks;
extern const struct sPathTable34MovementCallbacks_Layout sPathTable34MovementCallbacks;
extern const struct sPathTable35MovementCallbacks_Layout sPathTable35MovementCallbacks;
extern const struct sPathTable36MovementCallbacks_Layout sPathTable36MovementCallbacks;
extern const struct sPathTable37MovementCallbacks_Layout sPathTable37MovementCallbacks;
extern const struct sRandomLookUpDownMovementCallbacks_Layout sRandomLookUpDownMovementCallbacks;
extern const struct sRandomLookLeftRightMovementCallbacks_Layout sRandomLookLeftRightMovementCallbacks;
extern const struct sFollowPlayer48MovementCallbacks_Layout sFollowPlayer48MovementCallbacks;
extern const struct sAlternatingSpinMovementCallbacks_Layout sAlternatingSpinMovementCallbacks;
extern const struct sFollowPartnerMovementCallbacks_Layout sFollowPartnerMovementCallbacks;
extern const struct sHiddenObjectCover0MovementCallbacks_Layout sHiddenObjectCover0MovementCallbacks;
extern const struct sHiddenObjectCover1MovementCallbacks_Layout sHiddenObjectCover1MovementCallbacks;
extern const struct sHiddenObjectCover2MovementCallbacks_Layout sHiddenObjectCover2MovementCallbacks;
extern const struct sHiddenObjectCover3MovementCallbacks_Layout sHiddenObjectCover3MovementCallbacks;
extern const struct sFollowPlayer55MovementCallbacks_Layout sFollowPlayer55MovementCallbacks;
extern const struct sFollowPlayer56MovementCallbacks_Layout sFollowPlayer56MovementCallbacks;
extern const u32 sFaceMovements[4];
extern const u32 sWalkSlowerMovements[4];
extern const u32 sWalkSlowMovements[4];
extern const u32 sWalkNormalMovements[4];
extern const u32 sWalkFastMovements[4];
extern const u32 sWalkFasterMovements[4];
extern const u32 sWalkOnSpotSlowerMovements[4];
extern const u32 sWalkOnSpotSlowMovements[4];
extern const u32 sWalkOnSpotNormalMovements[4];
extern const u32 sWalkOnSpotFastMovements[4];
extern const u32 sWalkOnSpotFasterMovements[4];
extern const u32 sJumpOnSpotSlowMovements[4];
extern const u32 sJumpOnSpotFastMovements[4];
extern const u32 sJumpNearFastMovements[4];
extern const u32 sJumpFarMovements[4];
extern const u32 sWalkSlightlyFastMovements[4];
extern const u32 sWalkSlightlyFasterMovements[4];
extern const u32 sWalkFastestMovements[4];
extern const u32 sRunMovements[4];
extern const u32 sJumpNearSlowMovements[4];
extern const u32 sJumpFartherMovements[4];
extern const u32 sWalkEverSoSlightlyFastMovements[4];

// clang-format off
const MovementCommandFunc *const gMovementCmdTable[113] = {
    (const MovementCommandFunc *const)gMovementCmdSteps_000,
    (const MovementCommandFunc *const)gMovementCmdSteps_001,
    (const MovementCommandFunc *const)gMovementCmdSteps_002,
    (const MovementCommandFunc *const)gMovementCmdSteps_003,
    (const MovementCommandFunc *const)gMovementCmdSteps_004,
    (const MovementCommandFunc *const)gMovementCmdSteps_005,
    (const MovementCommandFunc *const)gMovementCmdSteps_006,
    (const MovementCommandFunc *const)gMovementCmdSteps_007,
    (const MovementCommandFunc *const)gMovementCmdSteps_008,
    (const MovementCommandFunc *const)gMovementCmdSteps_009,
    (const MovementCommandFunc *const)gMovementCmdSteps_010,
    (const MovementCommandFunc *const)gMovementCmdSteps_011,
    (const MovementCommandFunc *const)gMovementCmdSteps_012,
    (const MovementCommandFunc *const)gMovementCmdSteps_013,
    (const MovementCommandFunc *const)gMovementCmdSteps_014,
    (const MovementCommandFunc *const)gMovementCmdSteps_015,
    (const MovementCommandFunc *const)gMovementCmdSteps_016,
    (const MovementCommandFunc *const)gMovementCmdSteps_017,
    (const MovementCommandFunc *const)gMovementCmdSteps_018,
    (const MovementCommandFunc *const)gMovementCmdSteps_019,
    (const MovementCommandFunc *const)gMovementCmdSteps_020,
    (const MovementCommandFunc *const)gMovementCmdSteps_021,
    (const MovementCommandFunc *const)gMovementCmdSteps_022,
    (const MovementCommandFunc *const)gMovementCmdSteps_023,
    (const MovementCommandFunc *const)gMovementCmdSteps_024,
    (const MovementCommandFunc *const)gMovementCmdSteps_025,
    (const MovementCommandFunc *const)gMovementCmdSteps_026,
    (const MovementCommandFunc *const)gMovementCmdSteps_027,
    (const MovementCommandFunc *const)gMovementCmdSteps_028,
    (const MovementCommandFunc *const)gMovementCmdSteps_029,
    (const MovementCommandFunc *const)gMovementCmdSteps_030,
    (const MovementCommandFunc *const)gMovementCmdSteps_031,
    (const MovementCommandFunc *const)gMovementCmdSteps_032,
    (const MovementCommandFunc *const)gMovementCmdSteps_033,
    (const MovementCommandFunc *const)gMovementCmdSteps_034,
    (const MovementCommandFunc *const)gMovementCmdSteps_035,
    (const MovementCommandFunc *const)gMovementCmdSteps_036,
    (const MovementCommandFunc *const)gMovementCmdSteps_037,
    (const MovementCommandFunc *const)gMovementCmdSteps_038,
    (const MovementCommandFunc *const)gMovementCmdSteps_039,
    (const MovementCommandFunc *const)gMovementCmdSteps_040,
    (const MovementCommandFunc *const)gMovementCmdSteps_041,
    (const MovementCommandFunc *const)gMovementCmdSteps_042,
    (const MovementCommandFunc *const)gMovementCmdSteps_043,
    (const MovementCommandFunc *const)gMovementCmdSteps_044,
    (const MovementCommandFunc *const)gMovementCmdSteps_045,
    (const MovementCommandFunc *const)gMovementCmdSteps_046,
    (const MovementCommandFunc *const)gMovementCmdSteps_047,
    (const MovementCommandFunc *const)gMovementCmdSteps_048,
    (const MovementCommandFunc *const)gMovementCmdSteps_049,
    (const MovementCommandFunc *const)gMovementCmdSteps_050,
    (const MovementCommandFunc *const)gMovementCmdSteps_051,
    (const MovementCommandFunc *const)gMovementCmdSteps_052,
    (const MovementCommandFunc *const)gMovementCmdSteps_053,
    (const MovementCommandFunc *const)gMovementCmdSteps_054,
    (const MovementCommandFunc *const)gMovementCmdSteps_055,
    (const MovementCommandFunc *const)gMovementCmdSteps_056,
    (const MovementCommandFunc *const)gMovementCmdSteps_057,
    (const MovementCommandFunc *const)gMovementCmdSteps_058,
    (const MovementCommandFunc *const)gMovementCmdSteps_059,
    (const MovementCommandFunc *const)gMovementCmdSteps_060,
    (const MovementCommandFunc *const)gMovementCmdSteps_061,
    (const MovementCommandFunc *const)gMovementCmdSteps_062,
    (const MovementCommandFunc *const)gMovementCmdSteps_063,
    (const MovementCommandFunc *const)gMovementCmdSteps_064,
    (const MovementCommandFunc *const)gMovementCmdSteps_065,
    (const MovementCommandFunc *const)gMovementCmdSteps_066,
    (const MovementCommandFunc *const)gMovementCmdSteps_067,
    (const MovementCommandFunc *const)gMovementCmdSteps_068,
    (const MovementCommandFunc *const)gMovementCmdSteps_069,
    (const MovementCommandFunc *const)gMovementCmdSteps_070,
    (const MovementCommandFunc *const)gMovementCmdSteps_071,
    (const MovementCommandFunc *const)gMovementCmdSteps_072,
    (const MovementCommandFunc *const)gMovementCmdSteps_073,
    (const MovementCommandFunc *const)gMovementCmdSteps_074,
    (const MovementCommandFunc *const)gMovementCmdSteps_075,
    (const MovementCommandFunc *const)gMovementCmdSteps_076,
    (const MovementCommandFunc *const)gMovementCmdSteps_077,
    (const MovementCommandFunc *const)gMovementCmdSteps_078,
    (const MovementCommandFunc *const)gMovementCmdSteps_079,
    (const MovementCommandFunc *const)gMovementCmdSteps_080,
    (const MovementCommandFunc *const)gMovementCmdSteps_081,
    (const MovementCommandFunc *const)gMovementCmdSteps_082,
    (const MovementCommandFunc *const)gMovementCmdSteps_083,
    (const MovementCommandFunc *const)gMovementCmdSteps_084,
    (const MovementCommandFunc *const)gMovementCmdSteps_085,
    (const MovementCommandFunc *const)gMovementCmdSteps_086,
    (const MovementCommandFunc *const)gMovementCmdSteps_087,
    (const MovementCommandFunc *const)gMovementCmdSteps_088,
    (const MovementCommandFunc *const)gMovementCmdSteps_089,
    (const MovementCommandFunc *const)gMovementCmdSteps_090,
    (const MovementCommandFunc *const)gMovementCmdSteps_091,
    (const MovementCommandFunc *const)gMovementCmdSteps_092,
    (const MovementCommandFunc *const)gMovementCmdSteps_093,
    (const MovementCommandFunc *const)gMovementCmdSteps_094,
    (const MovementCommandFunc *const)gMovementCmdSteps_095,
    (const MovementCommandFunc *const)gMovementCmdSteps_096,
    (const MovementCommandFunc *const)gMovementCmdSteps_097,
    (const MovementCommandFunc *const)gMovementCmdSteps_098,
    (const MovementCommandFunc *const)gMovementCmdSteps_099,
    (const MovementCommandFunc *const)gMovementCmdSteps_100,
    (const MovementCommandFunc *const)gMovementCmdSteps_101,
    (const MovementCommandFunc *const)gMovementCmdSteps_102,
    (const MovementCommandFunc *const)gMovementCmdSteps_103,
    (const MovementCommandFunc *const)gMovementCmdSteps_104,
    (const MovementCommandFunc *const)gMovementCmdSteps_105,
    (const MovementCommandFunc *const)gMovementCmdSteps_106,
    (const MovementCommandFunc *const)gMovementCmdSteps_107,
    (const MovementCommandFunc *const)gMovementCmdSteps_108,
    (const MovementCommandFunc *const)gMovementCmdSteps_109,
    (const MovementCommandFunc *const)gMovementCmdSteps_110,
    (const MovementCommandFunc *const)gMovementCmdSteps_111,
    (const MovementCommandFunc *const)gMovementCmdSteps_112,
};
// clang-format on

const void *const gMapObjectMovementCallbacks[57] = {
    sNoMovementCallbacks,
    &sPlayerMovementCallbacks,
    &sRandomLookAnyDirectionMovementCallbacks,
    &sRandomWalkAnyDirectionMovementCallbacks,
    &sRandomWalkUpDownMovementCallbacks,
    &sRandomWalkLeftRightMovementCallbacks,
    &sRandomLookUpLeftMovementCallbacks,
    &sRandomLookUpRightMovementCallbacks,
    &sRandomLookDownLeftMovementCallbacks,
    &sRandomLookDownRightMovementCallbacks,
    &sRandomLookUpDownLeftMovementCallbacks,
    &sRandomLookUpDownRightMovementCallbacks,
    &sRandomLookUpLeftRightMovementCallbacks,
    &sRandomLookDownLeftRightMovementCallbacks,
    &sFaceDirectionUpMovementCallbacks,
    &sFaceDirectionDownMovementCallbacks,
    &sFaceDirectionLeftMovementCallbacks,
    &sFaceDirectionRightMovementCallbacks,
    &sSpinCounterclockwiseMovementCallbacks,
    &sSpinClockwiseMovementCallbacks,
    &sBackAndForthMovementCallbacks,
    &sPathTable14MovementCallbacks,
    &sPathTable15MovementCallbacks,
    &sPathTable16MovementCallbacks,
    &sPathTable17MovementCallbacks,
    &sPathTable18MovementCallbacks,
    &sPathTable19MovementCallbacks,
    &sPathTable20MovementCallbacks,
    &sPathTable21MovementCallbacks,
    &sPathTable22MovementCallbacks,
    &sPathTable23MovementCallbacks,
    &sPathTable24MovementCallbacks,
    &sPathTable25MovementCallbacks,
    &sPathTable26MovementCallbacks,
    &sPathTable27MovementCallbacks,
    &sPathTable28MovementCallbacks,
    &sPathTable29MovementCallbacks,
    &sPathTable30MovementCallbacks,
    &sPathTable31MovementCallbacks,
    &sPathTable32MovementCallbacks,
    &sPathTable33MovementCallbacks,
    &sPathTable34MovementCallbacks,
    &sPathTable35MovementCallbacks,
    &sPathTable36MovementCallbacks,
    &sPathTable37MovementCallbacks,
    &sRandomLookUpDownMovementCallbacks,
    &sRandomLookLeftRightMovementCallbacks,
    NULL,
    &sFollowPlayer48MovementCallbacks,
    &sAlternatingSpinMovementCallbacks,
    &sFollowPartnerMovementCallbacks,
    &sHiddenObjectCover0MovementCallbacks,
    &sHiddenObjectCover1MovementCallbacks,
    &sHiddenObjectCover2MovementCallbacks,
    &sHiddenObjectCover3MovementCallbacks,
    &sFollowPlayer55MovementCallbacks,
    &sFollowPlayer56MovementCallbacks,
};

// clang-format off
const u32 *const gMovementsByDirection[23] = {
    sFaceMovements, sWalkSlowerMovements, sWalkSlowMovements,
    sWalkNormalMovements, sWalkFastMovements, sWalkFasterMovements,
    sWalkOnSpotSlowerMovements, sWalkOnSpotSlowMovements, sWalkOnSpotNormalMovements,
    sWalkOnSpotFastMovements, sWalkOnSpotFasterMovements, sJumpOnSpotSlowMovements,
    sJumpOnSpotFastMovements, sJumpNearFastMovements, sJumpFarMovements,
    sWalkSlightlyFastMovements, sWalkSlightlyFasterMovements,
    sWalkFastestMovements, sRunMovements, sJumpNearSlowMovements,
    sJumpFartherMovements, sWalkEverSoSlightlyFastMovements, NULL,
};
// clang-format on

// not static: used above its definition
const struct sPlayerMovementCallbacks_Layout sPlayerMovementCallbacks = {
    0x00000001,
    (void (*)(void))MapObjectMovement_NoOpInit,
    (void (*)(void))MapObjectMovement_NoOpUpdate,
    (void (*)(void))MapObjectMovement_NoOpDelete,
    (void (*)(void))MapObjectMovement_NoOpRestore,
};

// not static: used above its definition
const struct sRandomWalkUpDownMovementCallbacks_Layout sRandomWalkUpDownMovementCallbacks = {
    0x00000003,
    RandomWalkMovement_InitUpDown,
    RandomWalkMovement_Update,
    (void (*)(void))MapObjectMovement_NoOpDelete,
    (void (*)(void))MapObjectMovement_NoOpRestore,
};

// not static: used above its definition
const struct sPathTable32MovementCallbacks_Layout sPathTable32MovementCallbacks = {
    0x00000003,
    PathMovement_InitWestSouthEastNorth,
    PathMovement_Update,
    (void (*)(void))MapObjectMovement_NoOpDelete,
    (void (*)(void))MapObjectMovement_NoOpRestore,
};

// not static: used above its definition
const struct sRandomLookUpLeftMovementCallbacks_Layout sRandomLookUpLeftMovementCallbacks = {
    0x00000003,
    RandomLookMovement_InitUpLeft,
    RandomLookMovement_Update,
    RandomLookMovement_Delete,
    (void (*)(void))MapObjectMovement_NoOpRestore,
};

// not static: used above its definition
const struct sRandomLookUpRightMovementCallbacks_Layout sRandomLookUpRightMovementCallbacks = {
    0x00000003,
    RandomLookMovement_InitUpRight,
    RandomLookMovement_Update,
    RandomLookMovement_Delete,
    (void (*)(void))MapObjectMovement_NoOpRestore,
};

// not static: used above its definition
const struct sRandomLookDownRightMovementCallbacks_Layout sRandomLookDownRightMovementCallbacks = {
    0x00000003,
    RandomLookMovement_InitDownRight,
    RandomLookMovement_Update,
    RandomLookMovement_Delete,
    (void (*)(void))MapObjectMovement_NoOpRestore,
};

// not static: used above its definition
const struct sPathTable35MovementCallbacks_Layout sPathTable35MovementCallbacks = {
    0x00000003,
    PathMovement_InitSouthWestNorthEast,
    PathMovement_Update,
    (void (*)(void))MapObjectMovement_NoOpDelete,
    (void (*)(void))MapObjectMovement_NoOpRestore,
};

// not static: used above its definition
const struct sRandomLookUpDownLeftMovementCallbacks_Layout sRandomLookUpDownLeftMovementCallbacks = {
    0x00000003,
    RandomLookMovement_InitUpDownLeft,
    RandomLookMovement_Update,
    RandomLookMovement_Delete,
    (void (*)(void))MapObjectMovement_NoOpRestore,
};

// not static: used above its definition
const struct sRandomLookUpDownRightMovementCallbacks_Layout sRandomLookUpDownRightMovementCallbacks = {
    0x00000003,
    RandomLookMovement_InitUpDownRight,
    RandomLookMovement_Update,
    RandomLookMovement_Delete,
    (void (*)(void))MapObjectMovement_NoOpRestore,
};

// not static: used above its definition
const struct sPathTable37MovementCallbacks_Layout sPathTable37MovementCallbacks = {
    0x00000003,
    PathMovement_InitEastSouthWestNorth,
    PathMovement_Update,
    (void (*)(void))MapObjectMovement_NoOpDelete,
    (void (*)(void))MapObjectMovement_NoOpRestore,
};

// not static: used above its definition
const struct sRandomLookUpDownMovementCallbacks_Layout sRandomLookUpDownMovementCallbacks = {
    0x00000003,
    RandomLookMovement_InitUpDown,
    RandomLookMovement_Update,
    RandomLookMovement_Delete,
    (void (*)(void))MapObjectMovement_NoOpRestore,
};

// not static: used above its definition
const struct sFollowPlayer48MovementCallbacks_Layout sFollowPlayer48MovementCallbacks = {
    0x00000003,
    FollowPlayerMovement_Init,
    FollowPlayerMovement_UpdateFollowMon,
    FollowPlayerMovement_Delete,
    (void (*)(void))MapObjectMovement_NoOpRestore,
};

// not static: used above its definition
const struct sRandomLookUpLeftRightMovementCallbacks_Layout sRandomLookUpLeftRightMovementCallbacks = {
    0x00000003,
    RandomLookMovement_InitUpLeftRight,
    RandomLookMovement_Update,
    RandomLookMovement_Delete,
    (void (*)(void))MapObjectMovement_NoOpRestore,
};

// not static: used above its definition
const struct sFaceDirectionDownMovementCallbacks_Layout sFaceDirectionDownMovementCallbacks = {
    0x00000003,
    FaceDirectionMovement_InitDown,
    FaceDirectionMovement_Update,
    (void (*)(void))MapObjectMovement_NoOpDelete,
    (void (*)(void))MapObjectMovement_NoOpRestore,
};

// not static: used above its definition
const struct sFollowPartnerMovementCallbacks_Layout sFollowPartnerMovementCallbacks = {
    0x00000003,
    FollowPartnerMovement_Init,
    FollowPartnerMovement_Update,
    FollowPartnerMovement_Delete,
    FollowPartnerMovement_Resume,
};

// not static: used above its definition
const struct sFaceDirectionLeftMovementCallbacks_Layout sFaceDirectionLeftMovementCallbacks = {
    0x00000003,
    FaceDirectionMovement_InitLeft,
    FaceDirectionMovement_Update,
    (void (*)(void))MapObjectMovement_NoOpDelete,
    (void (*)(void))MapObjectMovement_NoOpRestore,
};

// not static: used above its definition
const struct sFaceDirectionRightMovementCallbacks_Layout sFaceDirectionRightMovementCallbacks = {
    0x00000003,
    FaceDirectionMovement_InitRight,
    FaceDirectionMovement_Update,
    (void (*)(void))MapObjectMovement_NoOpDelete,
    (void (*)(void))MapObjectMovement_NoOpRestore,
};

// not static: used above its definition
const struct sSpinCounterclockwiseMovementCallbacks_Layout sSpinCounterclockwiseMovementCallbacks = {
    0x00000003,
    SpinMovement_InitCounterclockwise,
    SpinMovement_Update,
    (void (*)(void))MapObjectMovement_NoOpDelete,
    (void (*)(void))MapObjectMovement_NoOpRestore,
};

// not static: used above its definition
const struct sSpinClockwiseMovementCallbacks_Layout sSpinClockwiseMovementCallbacks = {
    0x00000003,
    SpinMovement_InitClockwise,
    SpinMovement_Update,
    (void (*)(void))MapObjectMovement_NoOpDelete,
    (void (*)(void))MapObjectMovement_NoOpRestore,
};

// not static: used above its definition
const struct sAlternatingSpinMovementCallbacks_Layout sAlternatingSpinMovementCallbacks = {
    0x00000003,
    AlternatingSpinMovement_Init,
    AlternatingSpinMovement_Update,
    (void (*)(void))MapObjectMovement_NoOpDelete,
    (void (*)(void))MapObjectMovement_NoOpRestore,
};

// not static: used above its definition
const struct sBackAndForthMovementCallbacks_Layout sBackAndForthMovementCallbacks = {
    0x00000003,
    BackAndForthMovement_Init,
    BackAndForthMovement_Update,
    (void (*)(void))MapObjectMovement_NoOpDelete,
    (void (*)(void))MapObjectMovement_NoOpRestore,
};

// not static: used above its definition
const struct sPathTable14MovementCallbacks_Layout sPathTable14MovementCallbacks = {
    0x00000003,
    PathMovement_InitNorthEastWestSouth,
    PathMovement_Update,
    (void (*)(void))MapObjectMovement_NoOpDelete,
    (void (*)(void))MapObjectMovement_NoOpRestore,
};

// not static: used above its definition
const struct sPathTable15MovementCallbacks_Layout sPathTable15MovementCallbacks = {
    0x00000003,
    PathMovement_InitEastWestSouthNorth,
    PathMovement_Update,
    (void (*)(void))MapObjectMovement_NoOpDelete,
    (void (*)(void))MapObjectMovement_NoOpRestore,
};

// not static: used above its definition
const struct sPathTable16MovementCallbacks_Layout sPathTable16MovementCallbacks = {
    0x00000003,
    PathMovement_InitSouthNorthEastWest,
    PathMovement_Update,
    (void (*)(void))MapObjectMovement_NoOpDelete,
    (void (*)(void))MapObjectMovement_NoOpRestore,
};

// not static: used above its definition
const struct sPathTable17MovementCallbacks_Layout sPathTable17MovementCallbacks = {
    0x00000003,
    PathMovement_InitWestSouthNorthEast,
    PathMovement_Update,
    (void (*)(void))MapObjectMovement_NoOpDelete,
    (void (*)(void))MapObjectMovement_NoOpRestore,
};

// not static: used above its definition
const struct sPathTable18MovementCallbacks_Layout sPathTable18MovementCallbacks = {
    0x00000003,
    PathMovement_InitWestEastSouthNorth,
    PathMovement_Update,
    (void (*)(void))MapObjectMovement_NoOpDelete,
    (void (*)(void))MapObjectMovement_NoOpRestore,
};

// not static: used above its definition
const struct sPathTable19MovementCallbacks_Layout sPathTable19MovementCallbacks = {
    0x00000003,
    PathMovement_InitWestEastSouthNorth2,
    PathMovement_Update,
    (void (*)(void))MapObjectMovement_NoOpDelete,
    (void (*)(void))MapObjectMovement_NoOpRestore,
};

// not static: used above its definition
const struct sPathTable34MovementCallbacks_Layout sPathTable34MovementCallbacks = {
    0x00000003,
    PathMovement_InitNorthEastSouthWest,
    PathMovement_Update,
    (void (*)(void))MapObjectMovement_NoOpDelete,
    (void (*)(void))MapObjectMovement_NoOpRestore,
};

// not static: used above its definition
const struct sPathTable33MovementCallbacks_Layout sPathTable33MovementCallbacks = {
    0x00000003,
    PathMovement_InitEastNorthWestSouth,
    PathMovement_Update,
    (void (*)(void))MapObjectMovement_NoOpDelete,
    (void (*)(void))MapObjectMovement_NoOpRestore,
};

// not static: used above its definition
const struct sPathTable21MovementCallbacks_Layout sPathTable21MovementCallbacks = {
    0x00000003,
    PathMovement_InitEastSouthNorthWest,
    PathMovement_Update,
    (void (*)(void))MapObjectMovement_NoOpDelete,
    (void (*)(void))MapObjectMovement_NoOpRestore,
};

// not static: used above its definition
const struct sPathTable22MovementCallbacks_Layout sPathTable22MovementCallbacks = {
    0x00000003,
    PathMovement_InitWestNorthSouthEast,
    PathMovement_Update,
    (void (*)(void))MapObjectMovement_NoOpDelete,
    (void (*)(void))MapObjectMovement_NoOpRestore,
};

// not static: used above its definition
const struct sPathTable24MovementCallbacks_Layout sPathTable24MovementCallbacks = {
    0x00000003,
    PathMovement_InitEastWestNorthSouth,
    PathMovement_Update,
    (void (*)(void))MapObjectMovement_NoOpDelete,
    (void (*)(void))MapObjectMovement_NoOpRestore,
};

// not static: used above its definition
const struct sPathTable31MovementCallbacks_Layout sPathTable31MovementCallbacks = {
    0x00000003,
    PathMovement_InitSouthEastNorthWest,
    PathMovement_Update,
    (void (*)(void))MapObjectMovement_NoOpDelete,
    (void (*)(void))MapObjectMovement_NoOpRestore,
};

// not static: used above its definition
const struct sPathTable26MovementCallbacks_Layout sPathTable26MovementCallbacks = {
    0x00000003,
    PathMovement_InitEastNorthSouthWest,
    PathMovement_Update,
    (void (*)(void))MapObjectMovement_NoOpDelete,
    (void (*)(void))MapObjectMovement_NoOpRestore,
};

// not static: used above its definition
const struct sPathTable27MovementCallbacks_Layout sPathTable27MovementCallbacks = {
    0x00000003,
    PathMovement_InitNorthSouthWestEast,
    PathMovement_Update,
    (void (*)(void))MapObjectMovement_NoOpDelete,
    (void (*)(void))MapObjectMovement_NoOpRestore,
};

// not static: used above its definition
const struct sPathTable28MovementCallbacks_Layout sPathTable28MovementCallbacks = {
    0x00000003,
    PathMovement_InitWestEastNorthSouth,
    PathMovement_Update,
    (void (*)(void))MapObjectMovement_NoOpDelete,
    (void (*)(void))MapObjectMovement_NoOpRestore,
};

// not static: used above its definition
const struct sPathTable29MovementCallbacks_Layout sPathTable29MovementCallbacks = {
    0x00000003,
    PathMovement_InitSouthWestEastNorth,
    PathMovement_Update,
    (void (*)(void))MapObjectMovement_NoOpDelete,
    (void (*)(void))MapObjectMovement_NoOpRestore,
};

// not static: used above its definition
const struct sPathTable30MovementCallbacks_Layout sPathTable30MovementCallbacks = {
    0x00000003,
    PathMovement_InitNorthWestSouthEast,
    PathMovement_Update,
    (void (*)(void))MapObjectMovement_NoOpDelete,
    (void (*)(void))MapObjectMovement_NoOpRestore,
};

// global: C declares it extern although the asm label was local
// clang-format off
void (*const sNoMovementCallbacks[5])(void) = {
    NULL, (void (*)(void))MapObjectMovement_NoOpInit, (void (*)(void))MapObjectMovement_NoOpUpdate,
    (void (*)(void))MapObjectMovement_NoOpDelete, (void (*)(void))MapObjectMovement_NoOpRestore,
};
// clang-format on

// not static: used above its definition
const struct sRandomLookAnyDirectionMovementCallbacks_Layout sRandomLookAnyDirectionMovementCallbacks = {
    0x00000002,
    RandomLookMovement_InitAnyDirection,
    RandomLookMovement_Update,
    RandomLookMovement_Delete,
    (void (*)(void))MapObjectMovement_NoOpRestore,
};

// not static: used above its definition
const struct sRandomWalkLeftRightMovementCallbacks_Layout sRandomWalkLeftRightMovementCallbacks = {
    0x00000003,
    RandomWalkMovement_InitLeftRight,
    RandomWalkMovement_Update,
    (void (*)(void))MapObjectMovement_NoOpDelete,
    (void (*)(void))MapObjectMovement_NoOpRestore,
};

// not static: used above its definition
const struct sRandomLookDownLeftMovementCallbacks_Layout sRandomLookDownLeftMovementCallbacks = {
    0x00000003,
    RandomLookMovement_InitDownLeft,
    RandomLookMovement_Update,
    RandomLookMovement_Delete,
    (void (*)(void))MapObjectMovement_NoOpRestore,
};

// not static: used above its definition
const struct sPathTable36MovementCallbacks_Layout sPathTable36MovementCallbacks = {
    0x00000003,
    PathMovement_InitWestNorthEastSouth,
    PathMovement_Update,
    (void (*)(void))MapObjectMovement_NoOpDelete,
    (void (*)(void))MapObjectMovement_NoOpRestore,
};

// not static: used above its definition
const struct sRandomLookDownLeftRightMovementCallbacks_Layout sRandomLookDownLeftRightMovementCallbacks = {
    0x00000003,
    RandomLookMovement_InitDownLeftRight,
    RandomLookMovement_Update,
    RandomLookMovement_Delete,
    (void (*)(void))MapObjectMovement_NoOpRestore,
};

// not static: used above its definition
const struct sRandomLookLeftRightMovementCallbacks_Layout sRandomLookLeftRightMovementCallbacks = {
    0x00000003,
    RandomLookMovement_InitLeftRight,
    RandomLookMovement_Update,
    RandomLookMovement_Delete,
    (void (*)(void))MapObjectMovement_NoOpRestore,
};

// not static: used above its definition
const struct sFaceDirectionUpMovementCallbacks_Layout sFaceDirectionUpMovementCallbacks = {
    0x00000003,
    FaceDirectionMovement_InitUp,
    FaceDirectionMovement_Update,
    (void (*)(void))MapObjectMovement_NoOpDelete,
    (void (*)(void))MapObjectMovement_NoOpRestore,
};

// not static: used above its definition
const struct sRandomWalkAnyDirectionMovementCallbacks_Layout sRandomWalkAnyDirectionMovementCallbacks = {
    0x00000003,
    RandomWalkMovement_InitAnyDirection,
    RandomWalkMovement_Update,
    (void (*)(void))MapObjectMovement_NoOpDelete,
    (void (*)(void))MapObjectMovement_NoOpRestore,
};

// not static: used above its definition
const struct sHiddenObjectCover0MovementCallbacks_Layout sHiddenObjectCover0MovementCallbacks = {
    0x00000033,
    HiddenObjectMovement_InitCover0,
    HiddenObjectMovement_Update,
    HiddenObjectMovement_Delete,
    HiddenObjectMovement_Resume,
};

// not static: used above its definition
const struct sHiddenObjectCover1MovementCallbacks_Layout sHiddenObjectCover1MovementCallbacks = {
    0x00000034,
    HiddenObjectMovement_InitCover1,
    HiddenObjectMovement_Update,
    HiddenObjectMovement_Delete,
    HiddenObjectMovement_Resume,
};

// not static: used above its definition
const struct sHiddenObjectCover2MovementCallbacks_Layout sHiddenObjectCover2MovementCallbacks = {
    0x00000035,
    HiddenObjectMovement_InitCover2,
    HiddenObjectMovement_Update,
    HiddenObjectMovement_Delete,
    HiddenObjectMovement_Resume,
};

// not static: used above its definition
const struct sHiddenObjectCover3MovementCallbacks_Layout sHiddenObjectCover3MovementCallbacks = {
    0x00000036,
    HiddenObjectMovement_InitCover3,
    HiddenObjectMovement_Update,
    HiddenObjectMovement_Delete,
    HiddenObjectMovement_Resume,
};

// not static: used above its definition
const struct sFollowPlayer55MovementCallbacks_Layout sFollowPlayer55MovementCallbacks = {
    0x00000003,
    FollowPlayerMovement_Init,
    FollowPlayerMovement_Update,
    FollowPlayerMovement_Delete,
    (void (*)(void))MapObjectMovement_NoOpRestore,
};

// not static: used above its definition
const struct sFollowPlayer56MovementCallbacks_Layout sFollowPlayer56MovementCallbacks = {
    0x00000003,
    FollowPlayerMovement_Init,
    FollowPlayerMovement_UpdateMirror,
    FollowPlayerMovement_Delete,
    (void (*)(void))MapObjectMovement_NoOpRestore,
};

// not static: used above its definition
const struct sPathTable20MovementCallbacks_Layout sPathTable20MovementCallbacks = {
    0x00000003,
    PathMovement_InitSouthNorthWestEast,
    PathMovement_Update,
    (void (*)(void))MapObjectMovement_NoOpDelete,
    (void (*)(void))MapObjectMovement_NoOpRestore,
};

// not static: used above its definition
const struct sPathTable23MovementCallbacks_Layout sPathTable23MovementCallbacks = {
    0x00000003,
    PathMovement_InitNorthSouthEastWest,
    PathMovement_Update,
    (void (*)(void))MapObjectMovement_NoOpDelete,
    (void (*)(void))MapObjectMovement_NoOpRestore,
};

// not static: used above its definition
const struct sPathTable25MovementCallbacks_Layout sPathTable25MovementCallbacks = {
    0x00000003,
    PathMovement_InitSouthEastWestNorth,
    PathMovement_Update,
    (void (*)(void))MapObjectMovement_NoOpDelete,
    (void (*)(void))MapObjectMovement_NoOpRestore,
};

// global: C declares it extern although the asm label was local
const u32 sWalkSlowerMovements[4] = { 0x00000004, 0x00000005, 0x00000006, 0x00000007 };

// global: C declares it extern although the asm label was local
const u32 sWalkSlowMovements[4] = { 0x00000008, 0x00000009, 0x0000000A, 0x0000000B };

// global: C declares it extern although the asm label was local
const u32 sWalkSlightlyFastMovements[4] = { 0x0000004C, 0x0000004D, 0x0000004E, 0x0000004F };

// global: C declares it extern although the asm label was local
const u32 sWalkEverSoSlightlyFastMovements[4] = { 0x00000060, 0x00000061, 0x00000062, 0x00000063 };

// global: C declares it extern although the asm label was local
const u32 sWalkOnSpotSlowerMovements[4] = { 0x00000018, 0x00000019, 0x0000001A, 0x0000001B };

// global: C declares it extern although the asm label was local
const u32 sWalkFastMovements[4] = { 0x00000010, 0x00000011, 0x00000012, 0x00000013 };

// global: C declares it extern although the asm label was local
const u32 sWalkOnSpotNormalMovements[4] = { 0x00000020, 0x00000021, 0x00000022, 0x00000023 };

// global: C declares it extern although the asm label was local
const u32 sWalkSlightlyFasterMovements[4] = { 0x00000050, 0x00000051, 0x00000052, 0x00000053 };

// global: C declares it extern although the asm label was local
const u32 sWalkOnSpotFasterMovements[4] = { 0x00000028, 0x00000029, 0x0000002A, 0x0000002B };

// global: C declares it extern although the asm label was local
const u32 sWalkNormalMovements[4] = { 0x0000000C, 0x0000000D, 0x0000000E, 0x0000000F };

// global: C declares it extern although the asm label was local
const u32 sJumpFartherMovements[4] = { 0x0000005E, 0x0000005F, 0x0000005E, 0x0000005F };

// global: C declares it extern although the asm label was local
const u32 sJumpOnSpotFastMovements[4] = { 0x00000030, 0x00000031, 0x00000032, 0x00000033 };

// global: C declares it extern although the asm label was local
const u32 sJumpNearSlowMovements[4] = { 0x0000005C, 0x0000005D, 0x0000005C, 0x0000005D };

// global: C declares it extern although the asm label was local
const u32 sJumpFarMovements[4] = { 0x00000038, 0x00000039, 0x0000003A, 0x0000003B };

// global: C declares it extern although the asm label was local
const u32 sWalkOnSpotSlowMovements[4] = { 0x0000001C, 0x0000001D, 0x0000001E, 0x0000001F };

// global: C declares it extern although the asm label was local
const u32 sWalkOnSpotFastMovements[4] = { 0x00000024, 0x00000025, 0x00000026, 0x00000027 };

// global: C declares it extern although the asm label was local
const u32 sWalkFastestMovements[4] = { 0x00000054, 0x00000055, 0x00000056, 0x00000057 };

// global: C declares it extern although the asm label was local
const u32 sRunMovements[4] = { 0x00000058, 0x00000059, 0x0000005A, 0x0000005B };

// global: C declares it extern although the asm label was local
const u32 sWalkFasterMovements[4] = { 0x00000014, 0x00000015, 0x00000016, 0x00000017 };

// global: C declares it extern although the asm label was local
const u32 sJumpNearFastMovements[4] = { 0x00000034, 0x00000035, 0x00000036, 0x00000037 };

// global: C declares it extern although the asm label was local
const u32 sJumpOnSpotSlowMovements[4] = { 0x0000002C, 0x0000002D, 0x0000002E, 0x0000002F };

// global: C declares it extern although the asm label was local
const u32 sFaceMovements[4] = { 0x00000000, 0x00000001, 0x00000002, 0x00000003 };
