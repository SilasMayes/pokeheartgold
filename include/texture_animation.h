#ifndef POKEHEARTGOLD_TEXTURE_ANIMATION_H
#define POKEHEARTGOLD_TEXTURE_ANIMATION_H

#include "billboard_gfx_sequence.h"
#include "heap.h"

typedef struct TextureAnimation TextureAnimation;
typedef struct TextureAnimationPool TextureAnimationPool;

TextureAnimationPool *TextureAnimationPool_New(int count, enum HeapID heapID);
void TextureAnimationPool_Free(TextureAnimationPool *pool);
TextureAnimation *TextureAnimationPool_Add(TextureAnimationPool *pool, const BillboardGfxSequence *gfxSequence, NNSG3dResTex *texture, u32 textureKey, u32 paletteKey, fx32 frame);
void TextureAnimation_Remove(TextureAnimation *animation);
void TextureAnimation_SetFrame(TextureAnimation *animation, fx32 frame);
void *Texture_GetImageData(NNSG3dResTex *texture, u32 index);
void *Texture_GetPaletteData(NNSG3dResTex *texture, u32 index);
u32 Texture_GetImageVramOffsetByName(NNSG3dResTex *texture, const char *name);
u32 Texture_GetImageVramOffsetByIndex(NNSG3dResTex *texture, u32 index);
u32 Texture_GetImageSizeByIndex(NNSG3dResTex *texture, u32 index);
u32 Texture_GetImageSizeByName(NNSG3dResTex *texture, const char *name);

#endif // POKEHEARTGOLD_TEXTURE_ANIMATION_H
