#ifndef POKEHEARTGOLD_APPLICATION_PLAZA_GAME_MIME_JR_TOP_H
#define POKEHEARTGOLD_APPLICATION_PLAZA_GAME_MIME_JR_TOP_H

#include "global.h"

#include "application/plaza_game.h"

#include "bg_window.h"
#include "camera.h"
#include "filesystem.h"
#include "gf_3d_vramman.h"
#include "model_animation.h"
#include "overlay_manager.h"
#include "palette.h"
#include "sprite_system.h"
#include "sys_task_api.h"

// Mime Jr. Top, a Wi-Fi Plaza game: Mime Jr. balances on a spinning top and every player rubs the
// touch screen to keep the top upright.

// A value moving from start to start + delta over duration frames (linear, or with a start
// velocity and constant acceleration).
typedef struct MimeJrTopTween {
    fx32 value;
    fx32 start;
    fx32 velocity;
    fx32 delta; // acceleration for the accelerated tween
    int frame;
    int duration;
} MimeJrTopTween;

typedef struct MimeJrTopQuat {
    f32 v[4]; // w, x, y, z
} MimeJrTopQuat;

typedef struct MimeJrTopFloatMatrix {
    f32 m[4][4];
} MimeJrTopFloatMatrix;

// A 3D model with its own rotation (a quaternion turned by touch input).
typedef struct MimeJrTopModel {
    ModelInstance instance;
    ModelResource resource;
    ModelAnimation animations[3];
    u8 unkC4[0x8C];
    MimeJrTopFloatMatrix rotationMatrix;
    MimeJrTopQuat rotation;
    MimeJrTopQuat lastTurn;
    MtxFx43 rotationFx;
    VecFx32 position;
    BOOL animate;
    BOOL loaded;
    int animation;
    int spinFrames; // frames the last flick keeps turning the model
    f32 spinX;
    f32 spinY;
    f32 spinStepX;
    f32 spinStepY;
} MimeJrTopModel;

// Part of MimeJrTopApp handed to the game screen.
typedef struct MimeJrTopResources {
    NARC *narc;    // NARC 193 (models, sprites, BGs)
    NARC *unkNarc; // NARC 189 (opened, not read here)
    SpriteSystem *spriteSystem;
    SpriteManager *spriteManager;
    BgConfig *bgConfig;
    PaletteData *palette;
    GF3DVramMan *vramMan;
    Camera *camera;
    u32 unk20;
    NNSFndAllocator allocator;
    u8 connectionLost; // every task stops when set
    u8 unk35[3];
} MimeJrTopResources;

// Run on the parent only: the game clock.
typedef struct MimeJrTopClock {
    u32 unk00;
    u32 playerCount;
    s16 timer;
    u16 unk0A;
    MimeJrTopResources *resources;
} MimeJrTopClock;

typedef struct MimeJrTopFallTask {
    int state;
    int step; // 0 = falling off, 1 = climbing back
    int timer;
    int *pose;
    MimeJrTopModel *mimeJr;
    MimeJrTopModel *top;
    u8 unk18[8];
    VecFx32 tilt;
    u8 unk2C[0x18];
    MimeJrTopTween tweenY;
    MimeJrTopTween tweenZ;
    BOOL selection;
    MimeJrTopResources *resources;
} MimeJrTopFallTask;

// Another player's top falling over.
typedef struct MimeJrTopRivalFallTask {
    int state;
    int step;
    int timer;
    ManagedSprite *face;
    ManagedSprite *body;
    MimeJrTopTween tween;
    MimeJrTopResources *resources;
} MimeJrTopRivalFallTask;

// Another player's tier badge (pulses while the tier holds).
typedef struct MimeJrTopRivalTierTask {
    int state;
    int mode;
    int counter;
    ManagedSprite *sprite;
    MimeJrTopTween tween;
    int previous;
    int *current;
    BOOL active;
    u8 unk34[8];
    MimeJrTopResources *resources;
    BOOL selection;
} MimeJrTopRivalTierTask;

// The local player's tier models (swapped in when the tier changes).
typedef struct MimeJrTopTierModelsTask {
    int state;
    int unk04;
    u8 unk08[0x20];
    int previous;
    int *current;
    BOOL active;
    MimeJrTopModel *modelA;
    MimeJrTopModel *modelB;
    MimeJrTopResources *resources;
    BOOL selection;
} MimeJrTopTierModelsTask;

typedef union MimeJrTopPlayerTask {
    MimeJrTopRivalTierTask rival;
    MimeJrTopTierModelsTask local;
} MimeJrTopPlayerTask;

// Three sparks thrown out where the screen is rubbed.
typedef struct MimeJrTopBurst {
    BOOL active;
    int state;
    ManagedSprite *sprites[3];
    MimeJrTopTween tweens[3][2]; // x and y per spark
    MimeJrTopResources *resources;
} MimeJrTopBurst;

typedef struct MimeJrTopStar {
    ManagedSprite *sprite;
    fx32 driftX;
    fx32 driftY;
    fx32 originX;
    fx32 originY;
    fx32 jitterX;
    fx32 jitterY;
    fx32 circleX;
    fx32 circleY;
    u8 type;
    u8 visible;
    u8 delay;
    u8 jitterPhase;
    int angle;
    s16 fallSpeed;
    s16 radiusX;
    s16 radiusY;
    s16 timer;
} MimeJrTopStar;

typedef struct MimeJrTopGame MimeJrTopGame;

typedef struct MimeJrTopStarsTask {
    MimeJrTopGame *game;
    s32 state;
    s32 timer;
    s32 group;
    s32 *stop;
    MimeJrTopStar stars[36];
} MimeJrTopStarsTask;

// One effect of the stage animation (flash, pop-ups, audience, stars).
typedef struct MimeJrTopStageEffect {
    int state;
    BOOL active;
    void *targets[8];
    int timer;
    u8 unk2C[0x20];
    int audienceTimer;
    BOOL stop;
    BOOL starsRunning;
    u8 unk58[0x20];
} MimeJrTopStageEffect;

// Stage effects started by the phase (how long the top has kept spinning).
typedef struct MimeJrTopStage {
    u32 previousPhase;
    u32 *phase;
    MimeJrTopStageEffect effects[5];
    SysTask *task;
    MimeJrTopResources *resources;
} MimeJrTopStage;

// A sub screen dancer moved along tweens or circles.
typedef struct MimeJrTopDancer {
    ManagedSprite *sprite;
    int state;
    s16 angle;
    u8 unk0A[6];
    int cycles;
    s16 baseX;
    s16 baseY;
    fx32 radiusX;
    fx32 radiusY;
    MimeJrTopTween tweenX;
    MimeJrTopTween tweenY;
} MimeJrTopDancer;

// The sub screen dance shown from level 1 on (one routine per level).
typedef struct MimeJrTopDance {
    MimeJrTopDancer dancers[4]; // two front and two back dancers
    int count;
    int backSpeed;
    int frontSpeed;
    int loopCount;
    u8 unk150[4];
    SysTask *task;
    u32 *level;
    int *flashBlend;
    int *danceBlend;
    u32 timer;
    int routineState;
    u8 unk16C[4];
    u32 slideState;
    BOOL enabled;
    BOOL shown;
    MimeJrTopResources *resources;
    MimeJrTopTween slides[3];
} MimeJrTopDance;

struct MimeJrTopGame {
    int localIndex;
    int playerCount;
    int demoFrame;
    int demoStep;
    u32 unk10;
    MimeJrTopResources *resources;
    u8 unk18[4];
    ManagedSprite *rivalFaces[3];
    ManagedSprite *rivalBodies[3];
    ManagedSprite *rivalBadges[3];
    ManagedSprite *stars[36];
    ManagedSprite *popups[4];
    ManagedSprite *backDancers[2];
    ManagedSprite *frontDancers[2];
    ManagedSprite *demoHand;
    u16 rivalSlots[4];
    u8 unkFC[0xC];
    int flashBlend;
    int danceBlend;
    int mimeJrPose;
    MimeJrTopModel top;
    MimeJrTopModel mimeJr[3];
    MimeJrTopModel stage;
    MimeJrTopModel audience[8];
    MimeJrTopModel tierModels[2];
    VecFx32 tilt;
    int lastTouchX;
    int lastTouchY;
    u8 unk1FDC[4];
    Window instructions;
    Window nameWindows[3];
    u8 unk2020[0x10];
    MimeJrTopDance dance;
    u8 unk21F8[0x30];
    MimeJrTopStage stageEffects;
    MimeJrTopBurst bursts[8];
    MimeJrTopPlayerTask playerTasks[PLAZA_GAME_MAX_PLAYERS];
    int wobbleTick;
    int frame;
    u32 phase;
    u32 tier;
    u32 score;
    u32 level;
    u32 previousLevel;
    s16 recoverTimer;
    s16 levelTimer;
    s16 rivalSpinFrames[4];
    u32 rivalTiers[4];
    int spinFrames;
    s16 wobbleX;
    s16 wobbleY;
    s16 wobbleTime;
    s16 wobbleStep;
    MimeJrTopTween settleX;
    MimeJrTopTween settleY;
    MimeJrTopTween kickX;
    MimeJrTopTween kickY;
    BOOL touched;
    BOOL settled;
    BOOL wobbleDue;
    BOOL wobbling;
    BOOL everTouched;
    s16 nextWobbleX;
    s16 nextWobbleY;
    u32 playerStates[PLAZA_GAME_MAX_PLAYERS];
    u32 unk2BAC;
    u32 seed;
    BOOL selection;
    BOOL rivalFallShown;
};

// Command 22: sent by the parent to start the game.
typedef struct MimeJrTopStartMessage {
    u8 selection;
    u8 unk01[3];
    u32 seed;
} MimeJrTopStartMessage;

typedef struct MimeJrTopPlayerScore {
    u32 score;
    u32 unk04;
} MimeJrTopPlayerScore;

typedef struct MimeJrTopApp {
    MimeJrTopClock *clock;
    MimeJrTopGame *game;
    BOOL startReceived;
    BOOL finishReceived;
    u32 unk10;
    MimeJrTopStartMessage start;
    u32 finalScore; // command 25
    u8 unk20[4];
    MimeJrTopPlayerScore scores[PLAZA_GAME_MAX_PLAYERS];
    int netId;
    MimeJrTopResources resources;
    u32 savedSeed;
    PlazaGameSign *sign;
    PlazaGameArgs *args;
    PlazaGameRoster roster;
    PlazaGameEntry *entry;
    PlazaGameResultData resultData;
    PlazaGameResults *results;
    u32 netIds[PLAZA_GAME_MAX_PLAYERS];
    BOOL keepPlaying;
} MimeJrTopApp;

typedef void (*MimeJrTopReceiveFunc)(int netId, int size, void *data, MimeJrTopApp *app);
typedef u32 (*MimeJrTopSizeFunc)(void);

typedef struct MimeJrTopCommand {
    MimeJrTopReceiveFunc receive;
    MimeJrTopSizeFunc getSize;
    void *(*getBuffer)(int netId, void *context, int size);
} MimeJrTopCommand;

typedef struct MimeJrTopModelFiles {
    int files[16][2]; // model file, animation file
} MimeJrTopModelFiles;

typedef struct MimeJrTopTopModels {
    int files[4];
} MimeJrTopTopModels;

typedef struct MimeJrTopGraphicsModes {
    u32 values[4];
} MimeJrTopGraphicsModes;

typedef struct MimeJrTopBanks {
    u32 values[10];
} MimeJrTopBanks;

typedef struct MimeJrTopBgTemplates {
    BgTemplate bgs[4];
} MimeJrTopBgTemplates;

typedef struct MimeJrTopDemoPoint {
    s16 x;
    s16 y;
} MimeJrTopDemoPoint;

typedef struct MimeJrTopDemoPath {
    MimeJrTopDemoPoint points[48];
} MimeJrTopDemoPath;

typedef struct MimeJrTopRivalAnims {
    int anims[4][2]; // face, body
} MimeJrTopRivalAnims;

typedef struct MimeJrTopTierPoints {
    u16 values[4];
} MimeJrTopTierPoints;

typedef struct MimeJrTopWobbleIntervals {
    s16 values[4];
} MimeJrTopWobbleIntervals;

typedef struct MimeJrTopTouchData {
    TouchscreenHitbox hitboxes[2];
    u8 unk08[8];
    MimeJrTopTierPoints tierScores; // points per frame
    MimeJrTopTierPoints tierBonus;  // points for reaching a tier
    MimeJrTopWobbleIntervals wobbleIntervals;
} MimeJrTopTouchData;

typedef struct MimeJrTopWobbleChoice {
    int speed;
    int weight;
} MimeJrTopWobbleChoice;

typedef struct MimeJrTopOffsets {
    int values[6];
} MimeJrTopOffsets;

typedef struct MimeJrTopStarOrigins {
    s16 values[10];
} MimeJrTopStarOrigins;

typedef struct MimeJrTopDoneFlags {
    BOOL done[4];
} MimeJrTopDoneFlags;

typedef struct MimeJrTopRoutine {
    int timer;
    int count;
    int speed;
    int frontPalettes[3];
    int backPalettes[3];
    SysTaskFunc func;
} MimeJrTopRoutine;

typedef struct MimeJrTopRoutineValue {
    int value;
    u8 unk04[0x24];
} MimeJrTopRoutineValue;

typedef struct MimeJrTopRoutineTask {
    SysTaskFunc func;
    u8 unk04[0x24];
} MimeJrTopRoutineTask;

typedef struct MimeJrTopPlayerPalettes {
    int values[5];
} MimeJrTopPlayerPalettes;

extern const VecFx32 gMimeJrTopDemoTurnTiltAxis;
extern const VecFx32 gMimeJrTopDemoSpinTiltAxis;
extern const MimeJrTopGraphicsModes gMimeJrTopGraphicsModes;
extern const MimeJrTopTopModels gMimeJrTopTopModels;
extern const u16 gMimeJrTopEdgeColors[];
extern const OamCharTransferParam gMimeJrTopOamCharTransferParam;
extern const SpriteResourceCountsListUnion gMimeJrTopSpriteResourceCounts;
extern const OamManagerParam gMimeJrTopOamManagerParam;
extern const MimeJrTopBanks gMimeJrTopBanks;
extern const MimeJrTopBgTemplates gMimeJrTopMainBgTemplates;
extern const MimeJrTopBgTemplates gMimeJrTopSubBgTemplates;
extern const MimeJrTopModelFiles gMimeJrTopAudienceModelFiles;
extern const MimeJrTopDemoPath gMimeJrTopDemoPath;
extern const u16 gMimeJrTopPopupPositions[4];
extern const VecFx32 gMimeJrTopCameraPosition;
extern const VecFx32 gMimeJrTopLightVector;
extern const s16 gMimeJrTopRivalSpriteX[][3];
extern const MimeJrTopRivalAnims gMimeJrTopRivalAnims;
extern const MimeJrTopRivalAnims gMimeJrTopRivalSetAnims;
extern const s16 gMimeJrTopRivalNamePositions[3][3][4];
extern const MimeJrTopTouchData gMimeJrTopTouchData;
extern const TouchscreenHitbox gMimeJrTopSelectionHitboxes[];
extern const VecFx32 gMimeJrTopSpinTiltAxis;
extern const VecFx32 gMimeJrTopTurnTiltAxis;
extern const VecFx32 gMimeJrTopSettleTiltAxis;
extern const VecFx32 gMimeJrTopSettleTouchTiltAxis;
extern const VecFx32 gMimeJrTopWobbleTiltAxis;
extern const int gMimeJrTopTierModels[][2];
extern const int gMimeJrTopTierChangeModels[][2];
extern const MimeJrTopWobbleChoice gMimeJrTopWobbleChoices[][4];
extern const s32 gMimeJrTopWobbleWeights[][8];
extern const u16 gMimeJrTopPopupLimits[];
extern const MimeJrTopDoneFlags gMimeJrTopDance3DoneFlags;
extern const MimeJrTopDoneFlags gMimeJrTopDance2DoneFlags;
extern const MimeJrTopDoneFlags gMimeJrTopDance4DoneFlags;
extern const MimeJrTopDoneFlags gMimeJrTopPopupDoneFlags;
extern const MimeJrTopDoneFlags gMimeJrTopDance5DoneFlags;
extern const MimeJrTopStarOrigins gMimeJrTopStarOrigins;
extern const MimeJrTopOffsets gMimeJrTopBurstOffsetsX;
extern const MimeJrTopOffsets gMimeJrTopBurstOffsetsY;
extern const MimeJrTopRoutine gMimeJrTopRoutines[];
extern const MimeJrTopRoutineValue gMimeJrTopRoutineCounts[];
extern const MimeJrTopRoutineValue gMimeJrTopRoutineSpeeds[];
extern const MimeJrTopRoutineTask gMimeJrTopRoutineTasks[];
extern MimeJrTopPlayerPalettes gMimeJrTopPlayerPalettes[];

BOOL MimeJrTop_Init(OverlayManager *man, int *state);
BOOL MimeJrTop_Main(OverlayManager *man, int *state);
BOOL MimeJrTop_Exit(OverlayManager *man, int *state);
void MimeJrTopDance_Routine1(SysTask *sysTask, MimeJrTopDance *dance);
void MimeJrTopDance_Routine2(SysTask *sysTask, MimeJrTopDance *dance);
void MimeJrTopDance_Routine3(SysTask *sysTask, MimeJrTopDance *dance);
void MimeJrTopDance_Routine4(SysTask *sysTask, MimeJrTopDance *dance);
void MimeJrTopDance_Routine5(SysTask *sysTask, MimeJrTopDance *dance);

#endif // POKEHEARTGOLD_APPLICATION_PLAZA_GAME_MIME_JR_TOP_H
