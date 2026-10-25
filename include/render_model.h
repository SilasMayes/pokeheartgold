#ifndef POKEHEARTGOLD_RENDER_MODEL_H
#define POKEHEARTGOLD_RENDER_MODEL_H

#include "field/field_effect_manager.h"

typedef struct RenderModel {
    BOOL loaded;
    NNSG3dResFileHeader *file;
    NNSG3dResMdlSet *set;
    NNSG3dResMdl *model;
    NNSG3dResTex *texture;
} RenderModel;

void RenderModel_LoadFromNarc(RenderModelStorage *data, int index, NARC *narc, int fileId, enum HeapID heapID, BOOL atEnd);
void RenderModel_BindTexturesOnVBlank(RenderModelStorage *model);
void RenderModel_Free(RenderModelStorage *data);

#endif // POKEHEARTGOLD_RENDER_MODEL_H
