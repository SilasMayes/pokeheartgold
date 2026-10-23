#include "orbit_cursor.h"

#include "global.h"

#include "geometry_math.h"
#include "math_util.h"

// Sprite chain that follows a target point and then circles it (sin/cos around sprites[0]).

typedef struct Vec2f {
    float x;
    float y;
} Vec2f;

static BOOL OrbitCursor_StepToward(s16 x, s16 y, float fx, float fy, float *outX, float *outY, float speed, s16 minDist);

fx32 FX_Sqrt(fx32 x);

OrbitCursor *OrbitCursor_New(OrbitCursorArgs args, SpriteSystem *spriteSys, SpriteManager *spriteMan, PaletteData *plttData) {
    OrbitCursor *motion = Heap_Alloc(args.heapId, sizeof(OrbitCursor));

    motion->count = args.count;
    motion->heapId = args.heapId;
    motion->resBase = args.resBase;
    motion->fixedPalette = args.fixedPalette;
    motion->yOffset = args.yOffset;
    motion->spriteSys = spriteSys;
    motion->spriteMan = spriteMan;
    motion->plttData = plttData;
    motion->state = 0;
    motion->radiusX = 15;
    motion->radiusY = 15;
    motion->task = NULL;
    motion->active = 0;
    return motion;
}

const int gOrbitCursorPaletteMembers[] = {
    0x61,
    0x62,
    0x63,
    0x64,
    0x65,
    0x80,
    0x85,
};

static BOOL OrbitCursor_StepToward(s16 x, s16 y, float fx, float fy, float *outX, float *outY, float speed, s16 minDist) {
    Vec2f step;
    Vec2f delta;
    Vec2f origin;
    float distSq;
    float dist;

    origin.x = 0.0f;
    origin.y = 0.0f;
    delta.x = (float)x - fx;
    delta.y = (float)y - fy;
    step.x = 0.0f;
    step.y = 0.0f;

    distSq = delta.x * delta.x + delta.y * delta.y;
    dist = (float)FX_Sqrt((fx32)(distSq > 0.0f ? 0.5f + 4096.0f * distSq : 4096.0f * distSq - 0.5f)) / 4096.0f;
    if (dist < speed || (float)minDist > dist || dist == 0.0f) {
        return FALSE;
    }
    step.x = delta.x * speed / dist;
    step.y = delta.y * speed / dist;
    *outX = step.x + origin.x;
    *outY = step.y + origin.y;
    return TRUE;
}

void OrbitCursor_Task(SysTask *task, void *data) {
    OrbitCursor *cursor = data;
    fx32 posX, posY;
    float outX, outY;
    s16 pos[2];
    int i;
    int done;
    float fx, fy;
    if (cursor->active == 0) {
        return;
    }
    done = 0;
    for (i = 0; i < cursor->count; i++) {
        if (i != 0) {
            cursor->sprites[i].x = cursor->sprites[i - 1].x;
            cursor->sprites[i].y = cursor->sprites[i - 1].y;
        }
        ManagedSprite_GetPositionFxXYWithSubscreenOffset(cursor->sprites[i].sprite, &posX, &posY, cursor->yOffset);
        fx = (float)posX / 4096.0f;
        fy = (float)posY / 4096.0f;
        if (OrbitCursor_StepToward(cursor->sprites[i].x, cursor->sprites[i].y, fx, fy, &outX, &outY, (8.0f - 0.5f * (float)(i - done)) / 2.0f, 16) && cursor->sprites[i].orbitPhase == 0) {
            float ry = outY > 0.0f ? 0.5f + 4096.0f * outY : 4096.0f * outY - 0.5f;
            ManagedSprite_AddSpritePrecisePositionXY(cursor->sprites[i].sprite, (fx32)(outX > 0.0f ? 0.5f + 4096.0f * outX : 4096.0f * outX - 0.5f), (fx32)ry);
            continue;
        }
        switch (cursor->sprites[i].orbitPhase) {
        case 0:
            ManagedSprite_GetPositionXYWithSubscreenOffset(cursor->sprites[i].sprite, &pos[1], &pos[0], cursor->yOffset);
            if (cursor->leadSprite == 0xFF) {
                int diff;
                float ax, ay;
                cursor->leadSprite = i;
                diff = cursor->sprites[0].x - pos[1];
                ax = diff > 0 ? 0.5f + (float)(diff << 12) : (float)(diff << 12) - 0.5f;
                diff = cursor->sprites[0].y - pos[0];
                ay = diff > 0 ? 0.5f + (float)(diff << 12) : (float)(diff << 12) - 0.5f;
                cursor->sprites[i].angle = FX_Atan2Idx((fx32)ay, (fx32)ax);
            } else {
                cursor->sprites[i].angle = cursor->sprites[cursor->leadSprite].angle - (720 / cursor->count) * cursor->orbitingCount;
            }
            cursor->sprites[i].angle %= 720;
            cursor->orbitingCount++;
            cursor->sprites[i].orbitPhase++;
            break;
        case 1:
            cursor->sprites[i].angle += 4;
            cursor->sprites[i].angle %= 720;
            {
                fx32 x = (cursor->sprites[0].x << 12) + GF_SinDeg(cursor->sprites[i].angle) * cursor->radiusX;
                fx32 y = (cursor->sprites[0].y << 12) + GF_CosDeg(cursor->sprites[i].angle) * cursor->radiusY;
                ManagedSprite_SetPositionFxXYWithSubscreenOffset(cursor->sprites[i].sprite, x, y, cursor->yOffset);
            }
            break;
        }
        done++;
    }
}

void OrbitCursor_ReloadPalette(OrbitCursor *cursor, int palette) {
    SpriteSystem *spriteSys = cursor->spriteSys;
    NARC *narc;
    SpriteManager *spriteMan = cursor->spriteMan;
    PaletteData *plttData = cursor->plttData;
    narc = cursor->narc;

    SpriteManager_UnloadPlttObjById(spriteMan, 0x56CF);
    SpriteManager_UnloadPlttObjById(spriteMan, 0x56D0);
    SpriteSystem_LoadPaletteBufferFromOpenNarc(plttData, PLTTBUF_MAIN_OBJ, spriteSys, spriteMan, narc, gOrbitCursorPaletteMembers[palette], FALSE, 1, NNS_G2D_VRAM_TYPE_2DMAIN, 0x56CF);
    SpriteSystem_LoadPaletteBufferFromOpenNarc(plttData, PLTTBUF_SUB_OBJ, spriteSys, spriteMan, narc, gOrbitCursorPaletteMembers[palette], FALSE, 1, NNS_G2D_VRAM_TYPE_2DSUB, 0x56D0);
}

void OrbitCursor_LoadResources(OrbitCursor *cursor, int palette) {
    int resBase = cursor->resBase;
    NARC *narc;
    SpriteSystem *spriteSys = cursor->spriteSys;
    int resId = resBase + 0x56CE;
    SpriteManager *spriteMan = cursor->spriteMan;
    PaletteData *plttData = cursor->plttData;
    narc = cursor->narc;

    if (resBase == 1) {
        if (cursor->fixedPalette == 0) {
            SpriteSystem_LoadPaletteBufferFromOpenNarc(plttData, PLTTBUF_MAIN_OBJ, spriteSys, spriteMan, narc, gOrbitCursorPaletteMembers[palette], FALSE, 1, NNS_G2D_VRAM_TYPE_2DMAIN, resId);
        } else {
            SpriteSystem_LoadPaletteBufferFromOpenNarc(plttData, PLTTBUF_MAIN_OBJ, spriteSys, spriteMan, narc, 0x60, FALSE, 1, NNS_G2D_VRAM_TYPE_2DMAIN, resId);
        }
        SpriteSystem_LoadCharResObjFromOpenNarc(spriteSys, spriteMan, narc, 0x5F, FALSE, 1, resId);
    } else {
        if (cursor->fixedPalette == 0) {
            SpriteSystem_LoadPaletteBufferFromOpenNarc(plttData, PLTTBUF_SUB_OBJ, spriteSys, spriteMan, narc, gOrbitCursorPaletteMembers[palette], FALSE, 1, NNS_G2D_VRAM_TYPE_2DSUB, resId);
        } else {
            SpriteSystem_LoadPaletteBufferFromOpenNarc(plttData, PLTTBUF_SUB_OBJ, spriteSys, spriteMan, narc, 0x60, FALSE, 1, NNS_G2D_VRAM_TYPE_2DSUB, resId);
        }
        SpriteSystem_LoadCharResObjFromOpenNarc(spriteSys, spriteMan, narc, 0x5F, FALSE, 2, resId);
    }
    SpriteSystem_LoadCellResObjFromOpenNarc(spriteSys, spriteMan, narc, 0x5D, FALSE, resId);
    SpriteSystem_LoadAnimResObjFromOpenNarc(spriteSys, spriteMan, narc, 0x5E, FALSE, resId);
}

void OrbitCursor_CreateSprites(OrbitCursor *cursor) {
    ManagedSpriteTemplate tmpl;
    SpriteSystem *spriteSys = cursor->spriteSys;
    SpriteManager *spriteMan = cursor->spriteMan;
    int i = 0;

    tmpl.x = 0x80;
    tmpl.y = 0x60;
    tmpl.z = 0;
    tmpl.animation = 0;
    tmpl.drawPriority = 0;
    tmpl.vram = (NNS_G2D_VRAM_TYPE)cursor->resBase;
    tmpl.bgPriority = 0;
    tmpl.vramTransfer = 0;
    tmpl.pal = 0;
    tmpl.resIdList[0] = cursor->resBase + 0x56CE;
    tmpl.resIdList[1] = cursor->resBase + 0x56CE;
    tmpl.resIdList[2] = cursor->resBase + 0x56CE;
    tmpl.resIdList[3] = cursor->resBase + 0x56CE;
    tmpl.resIdList[4] = -1;
    tmpl.resIdList[5] = -1;

    for (i = 0; i < cursor->count; i++) {
        cursor->sprites[i].sprite = SpriteSystem_NewSprite(spriteSys, spriteMan, &tmpl);
        ManagedSprite_TickFrame(cursor->sprites[i].sprite);
        ManagedSprite_SetPositionXY(cursor->sprites[i].sprite, 0x80, 0x60);
    }
}

void OrbitCursor_DeleteSprites(OrbitCursor *cursor) {
    int i;
    for (i = 0; i < cursor->count; i++) {
        SpriteManager_UnloadCharObjById(cursor->spriteMan, cursor->resBase + 0x56CE);
        SpriteManager_UnloadCellObjById(cursor->spriteMan, cursor->resBase + 0x56CE);
        SpriteManager_UnloadAnimObjById(cursor->spriteMan, cursor->resBase + 0x56CE);
        Sprite_DeleteAndFreeResources(cursor->sprites[i].sprite);
    }
}

BOOL OrbitCursor_Start(OrbitCursor *cursor, int palette) {
    cursor->narc = NARC_New(NARC_a_1_9_1, cursor->heapId);
    OrbitCursor_LoadResources(cursor, palette);
    OrbitCursor_CreateSprites(cursor);
    cursor->task = SysTask_CreateOnVBlankQueue(OrbitCursor_Task, cursor, 0x1000);
    return TRUE;
}

BOOL OrbitCursor_SetActive(OrbitCursor *cursor, int active) {
    cursor->active = active;
    return TRUE;
}

BOOL OrbitCursor_SetTarget(OrbitCursor *cursor, int x, int y) {
    int i;
    cursor->sprites[0].x = x;
    cursor->sprites[0].y = y;
    cursor->leadSprite = 0xFF;
    cursor->orbitingCount = 0;
    for (i = 0; i < cursor->count; i++) {
        cursor->sprites[i].orbitPhase = 0;
    }
    return TRUE;
}

BOOL OrbitCursor_MoveTarget(OrbitCursor *cursor, int x, int y) {
    int i;
    if (!OrbitCursor_IsNewTarget(cursor, x, y)) {
        return FALSE;
    }
    cursor->sprites[0].x = x;
    cursor->sprites[0].y = y;
    cursor->leadSprite = 0xFF;
    cursor->orbitingCount = 0;
    for (i = 0; i < cursor->count; i++) {
        cursor->sprites[i].orbitPhase = 0;
    }
    return TRUE;
}

BOOL OrbitCursor_IsNewTarget(OrbitCursor *cursor, int x, int y) {
    if (cursor->sprites[0].x == x && cursor->sprites[0].y == y) {
        return FALSE;
    }
    return TRUE;
}

BOOL OrbitCursor_SetPosition(OrbitCursor *cursor, s16 x, s16 y) {
    int i;
    cursor->leadSprite = 0xFF;
    cursor->orbitingCount = 0;
    for (i = 0; i < cursor->count; i++) {
        cursor->sprites[i].x = x;
        cursor->sprites[i].y = y;
        ManagedSprite_SetPositionXYWithSubscreenOffset(cursor->sprites[i].sprite, x, y, cursor->yOffset);
    }
    return TRUE;
}

BOOL OrbitCursor_Delete(OrbitCursor *cursor) {
    switch (cursor->state) {
    case 0:
        OrbitCursor_SetActive(cursor, FALSE);
        cursor->state++;
        break;
    case 1:
        SysTask_Destroy(cursor->task);
        cursor->state++;
        break;
    default:
        OrbitCursor_DeleteSprites(cursor);
        NARC_Delete(cursor->narc);
        Heap_Free(cursor);
        return FALSE;
    }
    return TRUE;
}

BOOL OrbitCursor_SetVisible(OrbitCursor *cursor, int flag) {
    int i;
    for (i = 0; i < cursor->count; i++) {
        ManagedSprite_SetDrawFlag(cursor->sprites[i].sprite, flag);
    }
    return TRUE;
}

void OrbitCursor_SetRadius(OrbitCursor *cursor, int radiusX, int radiusY) {
    if (radiusX != 0 && radiusY != 0) {
        cursor->radiusX = radiusX;
        cursor->radiusY = radiusY;
    } else {
        cursor->radiusX = 15;
        cursor->radiusY = 15;
    }
}

void OrbitCursor_SetAltAnim(OrbitCursor *cursor) {
    int i;
    for (i = 0; i < cursor->count; i++) {
        ManagedSprite_SetAnim(cursor->sprites[i].sprite, 1);
    }
}

void OrbitCursor_SetDefaultAnim(OrbitCursor *cursor) {
    int i;
    for (i = 0; i < cursor->count; i++) {
        ManagedSprite_SetAnim(cursor->sprites[i].sprite, 0);
    }
}
