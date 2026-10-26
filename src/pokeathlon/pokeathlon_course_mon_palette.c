#include "global.h"

#include "pokeathlon/pokeathlon_course_internal.h"

// Loads a palette into the slot of mon object `index`.
void PokeathlonCourseMonObjects_SetPalette(PokeathlonCourseMonObjects *objects, u8 index, int vram, const u16 *palette) {
    PokeathlonCourseMonGfx_SetPalette(objects->gfxManager, index, vram, palette);
}
