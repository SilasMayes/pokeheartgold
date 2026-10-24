#ifndef POKEHEARTGOLD_APPLICATION_PLAZA_NEWS_H
#define POKEHEARTGOLD_APPLICATION_PLAZA_NEWS_H

#include "overlay_manager.h"

struct WiFiPlazaNews;
struct WiFiPlazaWork;
union WiFiPlazaTime;

// Arguments of the plaza news app.
typedef struct PlazaNewsArgs {
    struct WiFiPlazaNews *news;
    const union WiFiPlazaTime *time; // WiFiPlazaWork.currentTime
    struct WiFiPlazaWork *lobby;
} PlazaNewsArgs;

BOOL PlazaNews_Init(OverlayManager *man, int *state);
BOOL PlazaNews_Main(OverlayManager *man, int *state);
BOOL PlazaNews_Exit(OverlayManager *man, int *state);

#endif // POKEHEARTGOLD_APPLICATION_PLAZA_NEWS_H
