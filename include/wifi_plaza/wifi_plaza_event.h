#ifndef POKEHEARTGOLD_WIFI_PLAZA_EVENT_H
#define POKEHEARTGOLD_WIFI_PLAZA_EVENT_H

#include "global.h"

#include "wifi_plaza/wifi_plaza_light.h"
#include "wifi_plaza/wifi_plaza_map.h"
#include "wifi_plaza/wifi_plaza_room.h"

#include "heap.h"

typedef struct WiFiPlazaEventModelList {
    const u8 *ids;
    u32 count;
} WiFiPlazaEventModelList;

// Plaza-wide effect selected by the lobby (6 kinds)
typedef struct WiFiPlazaEventEffect {
    WiFiPlazaWork *lobby;
    WiFiPlazaModels *models;
    u8 effect;
    u8 seLooping; // SEQ 0x5B5 is playing
    u16 activeCount;
    u32 step;
} WiFiPlazaEventEffect;

// Rocking / hopping animation of one model (angle and height follow a sine over `duration` frames)
typedef struct WiFiPlazaEventWobble {
    u16 active;
    u16 kind;
    s16 frame;
    s16 duration;
    u16 maxAngle;
    s16 maxHeight;
    s16 repeats;
} WiFiPlazaEventWobble;

typedef struct WiFiPlazaMoverMarker {
    s16 x;
    s16 z;
} WiFiPlazaMoverMarker;

// Nine models whose x position follows lobby values; three markers from the map grid
typedef struct WiFiPlazaEventMovers {
    WiFiPlazaRoomWork *room;
    WiFiPlazaWork *lobby;
    WiFiPlazaModels *models;
    WiFiPlazaMap *map;
    u8 states[9][3];
    u8 unk_2B;
    WiFiPlazaEventWobble wobbles[9];
    WiFiPlazaMoverMarker points[3]; // cell positions (pixels) of the map tags
    u8 unk_B6[6];
    fx32 baseX;
    fx32 range;
} WiFiPlazaEventMovers;

typedef struct WiFiPlazaEvent {
    WiFiPlazaRoomWork *room;
    WiFiPlazaWork *lobby;
    WiFiPlazaModels *models;
    WiFiPlazaObjManager *objManager;
    WiFiPlazaLight *light;
    WiFiPlazaEventMovers *movers;
    WiFiPlazaEventEffect *effect;
} WiFiPlazaEvent;

extern void (*const gWiFiPlazaEventEffectPhaseUpdates[])(WiFiPlazaEventEffect *effect, int arg);
extern void (*const gWiFiPlazaEventEffectPhaseStarts[])(WiFiPlazaEventEffect *effect, u32 arg);
extern const u8 gWiFiPlazaEventPhase3PropIds[];
extern const u32 gWiFiPlazaEventPhase3PropGroups[][2];
extern const u8 gWiFiPlazaEventPhase4Steps[];
extern const u8 gWiFiPlazaEventPhase4HideSteps[];
extern const u32 gWiFiPlazaEventPhase5Thresholds[];
extern const u32 gWiFiPlazaEventPhase5AnimSpeeds[];
extern const u8 gWiFiPlazaEventModelIds3[];
extern const u8 gWiFiPlazaEventModelIds4[];
extern const u8 gWiFiPlazaEventModelIds2[];
extern const u8 gWiFiPlazaEventModelIds5[];
extern const u8 gWiFiPlazaEventModelIds1[];
extern const u8 gWiFiPlazaEventModelIds6[];
extern const u8 gWiFiPlazaEventModelIds0[];
extern const u8 gWiFiPlazaMoverMarkerTags[];
extern const u16 gWiFiPlazaMoverSounds[][6];
extern BOOL (*const gWiFiPlazaEventWobbleSteps[])(WiFiPlazaEventWobble *wobble, WiFiPlazaModels *models, int index);
extern BOOL (*const gWiFiPlazaEventWobbleInits[])(WiFiPlazaEventWobble *wobble, WiFiPlazaModels *models, int index);

WiFiPlazaEvent *WiFiPlazaEvent_Create(enum HeapID heapID, WiFiPlazaRoomWork *room);
void WiFiPlazaEvent_Delete(WiFiPlazaEvent *event);
void WiFiPlazaEvent_Update(WiFiPlazaEvent *event);
u8 WiFiPlazaEvent_GetMoverState(WiFiPlazaEvent *event, u32 index, int field);
void WiFiPlazaEventEffect_UpdateNone(WiFiPlazaEventEffect *effect, u32 arg);
void WiFiPlazaEventEffect_UpdatePhase2(WiFiPlazaEventEffect *effect, u32 arg);
void WiFiPlazaEventEffect_UpdatePhase3(WiFiPlazaEventEffect *effect, u32 tick);
void WiFiPlazaEventEffect_UpdatePhase4(WiFiPlazaEventEffect *effect, u32 tick);
void WiFiPlazaEventEffect_UpdatePhase5(WiFiPlazaEventEffect *effect, u32 value);
void WiFiPlazaEventEffect_StartHideProps(WiFiPlazaEventEffect *effect);
void WiFiPlazaEventEffect_StartPhase2(WiFiPlazaEventEffect *effect);
void WiFiPlazaEventEffect_StartPhase3(WiFiPlazaEventEffect *effect);
void WiFiPlazaEventEffect_StartPhase4(WiFiPlazaEventEffect *effect);
void WiFiPlazaEventEffect_StartPhase5(WiFiPlazaEventEffect *effect);
BOOL WiFiPlazaTalk_Survey(WiFiPlazaPlayerState *state, WiFiPlazaRoomWork *room, u32 index);
void WiFiPlazaEventWobble_InitSmall(WiFiPlazaEventWobble *wobble);
void WiFiPlazaEventWobble_InitLarge(WiFiPlazaEventWobble *wobble);
BOOL WiFiPlazaEventWobble_Step(WiFiPlazaEventWobble *wobble, WiFiPlazaModels *models, int index);

#endif // POKEHEARTGOLD_WIFI_PLAZA_EVENT_H
