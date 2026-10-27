#ifndef POKEHEARTGOLD_LEGENDARY_CINEMATIC_H
#define POKEHEARTGOLD_LEGENDARY_CINEMATIC_H

#include "global.h"

struct LegendaryCinematic;

// The cinematics of overlay 106, run one frame at a time by LegendaryCinematic_Main through
// LegendaryCinematicArgs.scene: 0 Ho-Oh, 1 Lugia, 2 Arceus. Each takes the overlay's work data and
// returns FALSE once it has finished.
BOOL ScriptCinematic_HoOh(struct LegendaryCinematic *cinematic);
BOOL ScriptCinematic_Lugia(struct LegendaryCinematic *cinematic);
BOOL ScriptCinematic_Arceus(struct LegendaryCinematic *cinematic);

#endif // POKEHEARTGOLD_LEGENDARY_CINEMATIC_H
