#ifndef POKEHEARTGOLD_BATTLE_BATTLE_ANIM_EMITTER_H
#define POKEHEARTGOLD_BATTLE_BATTLE_ANIM_EMITTER_H

// SPL emitter callbacks of the battle animations, the emitter configured from script arguments with its flag and camera
// callbacks, battler screen positions and motion helpers.

#include "battle/battle_anim_util.h"

#include "camera.h"
#include "spl.h"

// Emitter configured from six script arguments (BattleAnimEmitterCb_ConfigureFromScript)
typedef struct BattleAnimEmitterConfig {
    BattleAnimSystem *system;
    SPLEmitter *particleSystem;
    s8 sideSign; // +1 / -1 by the side of battlerA, see BattleAnimEmitter_GetConfiguredSideSign
    u32 zMode;   // first script argument
    u32 battlerOrder;
    int positionMode;
    int axisMode;
    u32 flags; // a flag callback runs for every mask of gBattleAnimEmitterFlagMasks set here
    int cameraMode;
    int battlerA;
    int battlerB;
    VecFx32 position;
} BattleAnimEmitterConfig;

// Script arguments of the flag callbacks (BattleAnimEmitter_ReadFlagCbParams)
typedef struct BattleAnimEmitterFlagParams {
    int mode;
    BOOL ignoreSide; // TRUE: the value is not mirrored by BattleAnimEmitterConfig.sideSign
    VecFx32 value;
} BattleAnimEmitterFlagParams;

typedef BOOL (*BattleAnimEmitterConfigCb)(SPLEmitter *emitter, BattleAnimEmitterConfig *config);

// Emitter offsets by attacker type and defender type (units of 172)
typedef struct BattleAnimEmitterOffsetTable {
    s16 values[6][6];
} BattleAnimEmitterOffsetTable;

// Screen positions (x, y) per battler type
typedef struct BattleAnimScreenPosTable6 {
    struct {
        int x, y;
    } pos[6];
} BattleAnimScreenPosTable6;

typedef struct BattleAnimScreenPosTable7 {
    struct {
        int x, y;
    } pos[7];
} BattleAnimScreenPosTable7;

typedef struct BattleAnimEmitterAxisRow {
    int v[4]; // x, y, z, [3] == 1: not negated
} BattleAnimEmitterAxisRow;

typedef struct BattleAnimEmitterAxisRows {
    BattleAnimEmitterAxisRow rows[7];
} BattleAnimEmitterAxisRows;

typedef struct BattleAnimEmitterAxisPositions {
    int pos[6][2];
} BattleAnimEmitterAxisPositions;

// One VecFx32 per (attacker type, defender type)
typedef struct BattleAnimEmitterAxisEntry {
    int v[3];
} BattleAnimEmitterAxisEntry;

typedef struct BattleAnimEmitterFlagMasks {
    int masks[15];
} BattleAnimEmitterFlagMasks;

extern const BattleAnimEmitterOffsetTable gBattleAnimEmitterOffsetsX;
extern const BattleAnimEmitterOffsetTable gBattleAnimEmitterOffsetsY;
extern const BattleAnimEmitterAxisRow gBattleAnimEmitterAxisBase;
extern const BattleAnimScreenPosTable6 gBattleAnimEmitterPositions_Mode31;
extern const BattleAnimEmitterAxisPositions gBattleAnimEmitterAxisPositions;
extern const BattleAnimScreenPosTable7 gBattleAnimEmitterPositions_Mode32;
extern const BattleAnimScreenPosTable7 gBattleAnimEmitterPositions_Mode30;
extern const BattleAnimEmitterAxisRows gBattleAnimEmitterAxisRows;
extern const BattleAnimEmitterAxisEntry gBattleAnimEmitterAxes_Mode1[6][6];
extern const BattleAnimEmitterAxisEntry gBattleAnimEmitterAxes_Mode8[6][6];
extern const BattleAnimEmitterAxisEntry gBattleAnimEmitterAxes_Mode10[6][6];
extern const BattleAnimEmitterAxisEntry gBattleAnimEmitterAxes_Mode12[6][6];
extern const BattleAnimEmitterAxisEntry gBattleAnimEmitterAxes_Mode14[6][6];
extern const BattleAnimEmitterAxisEntry gBattleAnimEmitterAxes_Mode16[6][6];
extern const BattleAnimEmitterAxisEntry gBattleAnimEmitterAxes_Mode18[6][6];
extern const BattleAnimEmitterAxisEntry gBattleAnimEmitterAxes_Mode20[6][6];
extern BattleAnimEmitterConfigCb gBattleAnimEmitterFlagCallbacks[];
extern const BattleAnimEmitterFlagMasks gBattleAnimEmitterFlagMasks; // terminated
extern CameraAngle gBattleAnimEmitterCameraAngles[];
extern BattleAnimEmitterConfigCb gBattleAnimEmitterCameraCallbacks[];
// Per battler slot: set 0 singles, set 1 doubles
extern const BattleAnimPosition gBattleAnimBattlerScreenPositions[][6];

void BattleAnimEmitterCb_SetPositionAtFirstOpponent(SPLEmitter *emitter);
void BattleAnimEmitterCb_SetPositionAtBattler0(SPLEmitter *emitter);
void BattleAnimEmitterCb_SetPositionAtDefender(SPLEmitter *emitter);
void BattleAnimEmitterCb_SetPositionAtAttacker(SPLEmitter *emitter);
void BattleAnimEmitterCb_SetPositionAtAttacker2(SPLEmitter *emitter);
void BattleAnimEmitterCb_SetPositionAtAttackerSide(SPLEmitter *emitter);
void BattleAnimEmitterCb_SetPositionAtDefenderSide(SPLEmitter *emitter);
void BattleAnimEmitterCb_SetPositionByBattlerTypes(SPLEmitter *emitter);
void BattleAnimEmitterCb_AttackerToDefender(SPLEmitter *emitter);
void BattleAnimEmitterCb_ConvergeBySide(SPLEmitter *emitter);
void BattleAnimEmitterCb_ConvergeUp(SPLEmitter *emitter);
void BattleAnimEmitterCb_ConvergeToDefender(SPLEmitter *emitter);
void BattleAnimEmitterCb_ConvergeToAttacker(SPLEmitter *emitter);
void BattleAnimEmitterCb_ConvergeFromScript(SPLEmitter *emitter);
void BattleAnimEmitterCb_MagnetBySide(SPLEmitter *emitter);
void BattleAnimEmitterCb_MagnetUp(SPLEmitter *emitter);
void BattleAnimEmitterCb_MagnetToDefender(SPLEmitter *emitter);
void BattleAnimEmitterCb_MagnetToAttacker(SPLEmitter *emitter);
void BattleAnimEmitterCb_MagnetFromScript(SPLEmitter *emitter);
void BattleAnimEmitterCb_DefenderToAttacker(SPLEmitter *emitter);
void BattleAnimEmitterCb_ConfigureFromScript(SPLEmitter *emitter);
int BattleAnimEmitter_GetConfiguredSideSign(BattleAnimEmitterConfig *config);
void BattleAnimEmitter_ReadFlagCbParams(BattleAnimEmitterConfig *config, BattleAnimEmitterFlagParams *params);
BOOL BattleAnimEmitterFlagCb_Nop0(SPLEmitter *emitter, BattleAnimEmitterConfig *config);
BOOL BattleAnimEmitterFlagCb_SetGravity(SPLEmitter *emitter, BattleAnimEmitterConfig *config);
BOOL BattleAnimEmitterFlagCb_Nop2(SPLEmitter *emitter, BattleAnimEmitterConfig *config);
BOOL BattleAnimEmitterFlagCb_Nop3(SPLEmitter *emitter, BattleAnimEmitterConfig *config);
BOOL BattleAnimEmitterFlagCb_SetMagnetPos(SPLEmitter *emitter, BattleAnimEmitterConfig *config);
BOOL BattleAnimEmitterFlagCb_SetMagnetForce(SPLEmitter *emitter, BattleAnimEmitterConfig *config);
BOOL BattleAnimEmitterFlagCb_SetSpinAngle(SPLEmitter *emitter, BattleAnimEmitterConfig *config);
BOOL BattleAnimEmitterFlagCb_SetSpinAxis(SPLEmitter *emitter, BattleAnimEmitterConfig *config);
BOOL BattleAnimEmitterFlagCb_Nop8(SPLEmitter *emitter, BattleAnimEmitterConfig *config);
BOOL BattleAnimEmitterFlagCb_Nop9(SPLEmitter *emitter, BattleAnimEmitterConfig *config);
BOOL BattleAnimEmitterFlagCb_Nop10(SPLEmitter *emitter, BattleAnimEmitterConfig *config);
BOOL BattleAnimEmitterFlagCb_Nop11(SPLEmitter *emitter, BattleAnimEmitterConfig *config);
BOOL BattleAnimEmitterFlagCb_SetConvergencePos(SPLEmitter *emitter, BattleAnimEmitterConfig *config);
BOOL BattleAnimEmitterFlagCb_SetConvergenceForce(SPLEmitter *emitter, BattleAnimEmitterConfig *config);
BOOL BattleAnimEmitterCameraCb_ResetAngle(SPLEmitter *emitter, BattleAnimEmitterConfig *config);
BOOL BattleAnimEmitterCameraCb_SetPresetAngle4(SPLEmitter *emitter, BattleAnimEmitterConfig *config);
BOOL BattleAnimEmitterCameraCb_SetAngleFromScript(SPLEmitter *emitter, BattleAnimEmitterConfig *config);
BOOL BattleAnimEmitterCameraCb_SetPresetAngle3(SPLEmitter *emitter, BattleAnimEmitterConfig *config);
BOOL BattleAnimEmitterCameraCb_SetAngleByMode(SPLEmitter *emitter, BattleAnimEmitterConfig *config);
BOOL BattleAnimEmitterCameraCb_SetPresetAngle0(SPLEmitter *emitter, BattleAnimEmitterConfig *config);
BOOL BattleAnimEmitterCameraCb_SetPresetAngle1(SPLEmitter *emitter, BattleAnimEmitterConfig *config);
BOOL BattleAnimEmitterCameraCb_LookAtBattlerA(SPLEmitter *emitter, BattleAnimEmitterConfig *config);
BOOL BattleAnimEmitterCameraCb_LookAtBattlerB(SPLEmitter *emitter, BattleAnimEmitterConfig *config);
void BattleAnimUtil_LookupScreenPos(int set, int index, s16 *x, s16 *y);
void BattleAnimSystem_GetBattlerScreenPos(BattleAnimSystem *system, int index, s16 *x, s16 *y);
s16 BattleAnimSystem_GetBattlerScreenCoord(BattleAnimSystem *system, int battler, u32 coord);
u8 BattleAnimUtil_GetSpritePaletteSlot(ManagedSprite *sprite);
int BattleAnimUtil_GetBattlerSideSignByMode(BattleAnimSystem *system, int battler);
int BattleAnimUtil_GetBattlerSideSign(BattleAnimSystem *system, int battler);
fx32 BattleAnimUtil_CalcStep(fx32 start, fx32 end, int duration);
int BattleAnimUtil_CalcStepCount(fx32 start, fx32 end, fx32 step);
void BattleAnimUtil_SetSpritePosWithOffset(void *position, ManagedSprite *sprite, s16 x, s16 y);
void BattleAnimUtil_SetSpriteScale(BattleAnimLinearMotion *scale, ManagedSprite *sprite);
void BattleAnimUtil_SetPokepicPosWithOffset(void *position, Pokepic *pokepic, int x, int y);
void BattleAnimUtil_SetPokepicScale(BattleAnimLinearMotion *scale, Pokepic *pokepic);
void BattleAnimUtil_InitSinMotion(BattleAnimSinMotion *motion, int startX, int endX, int startY, u16 endY, fx32 ampX, fx32 ampY, int duration);

// Particle emitter parameters
void ParticleEmitter_SetGravity(SPLEmitter *emitter, VecFx16 *value);
void ParticleEmitter_SetMagnetPos(SPLEmitter *emitter, VecFx32 *value);
void ParticleEmitter_GetMagnetPos(SPLEmitter *emitter, VecFx32 *value);
void ParticleEmitter_SetMagnetForce(SPLEmitter *emitter, s16 *value);
void ParticleEmitter_GetMagnetForce(SPLEmitter *emitter, s16 *value);
void ParticleEmitter_SetSpinAngle(SPLEmitter *emitter, u16 *value);
void ParticleEmitter_GetSpinAngle(SPLEmitter *emitter, u16 *value);
void ParticleEmitter_SetSpinAxis(SPLEmitter *emitter, u16 *value);
void ParticleEmitter_GetSpinAxis(SPLEmitter *emitter, u16 *value);
void ParticleEmitter_SetConvergencePos(SPLEmitter *emitter, VecFx32 *value);
void ParticleEmitter_GetConvergencePos(SPLEmitter *emitter, VecFx32 *value);
void ParticleEmitter_SetConvergenceForce(SPLEmitter *emitter, s16 *value);
void ParticleEmitter_GetConvergenceForce(SPLEmitter *emitter, s16 *value);

#endif // POKEHEARTGOLD_BATTLE_BATTLE_ANIM_EMITTER_H
