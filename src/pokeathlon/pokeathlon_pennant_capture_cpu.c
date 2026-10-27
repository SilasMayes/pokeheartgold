#include "global.h"

#include "pokeathlon/pokeathlon_course_objects.h"
#include "pokeathlon/pokeathlon_course_types_def.h"
#include "pokeathlon/pokeathlon_pennant_capture.h"

#include "assert.h"
#include "bg_window.h"
#include "font.h"
#include "gf_gfx_planes.h"
#include "heap.h"
#include "math_util.h"
#include "sprite_transfer.h"

extern const PokeathlonPennantCaptureSpriteIds gPokeathlonPennantCaptureSpriteIds[];

typedef struct PokeathlonPennantCaptureCpuPoint {
    int y;
    int x;
} PokeathlonPennantCaptureCpuPoint;

static void PokeathlonPennantCaptureCpu_ChooseTarget(PokeathlonPennantCaptureCpu *cpu, u8 who);
static PokeathlonCourseCpuCell *PokeathlonPennantCaptureCpu_PickBestCell(PokeathlonPennantCaptureCpu *cpu);
static u8 PokeathlonPennantCaptureCpu_SortCells(PokeathlonCourseCpuCell **cells, PokeathlonCourseCpuCell **out);

static const WindowTemplate sPokeathlonPennantCaptureWindowTemplate = {
    .bgId = GF_BG_LYR_SUB_0,
    .left = 0,
    .top = 22,
    .width = 16,
    .height = 2,
    .palette = 15,
    .baseTile = 1,
};

const VecFx32 gPokeathlonPennantCaptureInitialPosition = { FX32_CONST(112), FX32_CONST(708), 0 };

void PokeathlonPennantCaptureDisplay_GetPicVramOffsets(PokeathlonCourseSpritePool *pool, PokeathlonPennantCaptureDisplay *display) {
    PokeathlonPennantCaptureSpriteIds ids = gPokeathlonPennantCaptureSpriteIds[3];
    u8 i;
    for (i = 0; i < 2; i++) {
        int id = ids.ids[i];
        SpriteResource *charResource = *PokeathlonCourseSpritePool_GetResourceSlot(pool, id, 0);
        SpriteResource *plttResource = *PokeathlonCourseSpritePool_GetResourceSlot(pool, id, 1);
        NNSG2dImageProxy *image = SpriteTransfer_GetCharProxy(charResource);
        NNSG2dImagePaletteProxy *palette = SpriteTransfer_GetPaletteProxy(plttResource, image);
        display->picCharOffsets[i] = NNS_G2dGetImageLocation(image, NNS_G2D_VRAM_TYPE_2DSUB);
        display->picPlttOffsets[i] = NNS_G2dGetImagePaletteLocation(palette, NNS_G2D_VRAM_TYPE_2DSUB);
    }
}

void PokeathlonPennantCaptureDisplay_InitWindow(PokeathlonPennantCaptureDisplay *display) {
    AddWindow(display->bgConfig, &display->window, &sPokeathlonPennantCaptureWindowTemplate);
    BG_FillCharDataRange(display->bgConfig, GF_BG_LYR_SUB_0, 0, 1, 0);
    LoadFontPal0(GF_PAL_LOCATION_SUB_BG, GF_PAL_SLOT_15_OFFSET, display->heapId);
}

void PokeathlonPennantCaptureDisplay_ShowStatus(PokeathlonCourseSpritePoolSprite **sprites, int show) {
    PokeathlonCourseSpritePoolSprite_Show(sprites[0], TRUE, show);
    PokeathlonCourseSpritePoolSprite_Show(sprites[2], TRUE, show);
    PokeathlonCourseSpritePoolSprite_Show(sprites[1], TRUE, show);
}

PokeathlonPennantCaptureCpu *PokeathlonPennantCaptureCpu_New(enum HeapID heapId, int cpuCount, int mode) {
    PokeathlonPennantCaptureCpu *cpu = Heap_Alloc(heapId, sizeof(PokeathlonPennantCaptureCpu));
    MI_CpuFill8(cpu, 0, sizeof(PokeathlonPennantCaptureCpu));
    cpu->cpuCount = cpuCount;
    cpu->humanCount = POKEATHLON_PARTICIPANTS - cpuCount;
    cpu->firstCpu = cpu->humanCount;
    cpu->interval = 6;
    cpu->timer = cpu->interval;
    return cpu;
}

void PokeathlonPennantCaptureCpu_SetPlayer(PokeathlonPennantCaptureCpu *cpu, u8 participant, PokeathlonPennantCapturePlayer *player) {
    cpu->players[participant].player = player;
}

void PokeathlonPennantCaptureCpu_SetPennants(PokeathlonPennantCaptureCpu *cpu, PokeathlonPennantCapturePennant *pennants) {
    cpu->pennants = pennants;
}

// The obstacle spots: 20 (x, y) pairs in units of 8 (0, 0 = none).
void PokeathlonPennantCaptureCpu_SetObstacles(PokeathlonPennantCaptureCpu *cpu, const u8 *spots) {
    int i;
    for (i = 0; i < PENNANT_CAPTURE_OBSTACLES; i++) {
        u16 x = spots[0] << 3, y = spots[1] << 3;
        if (x && y) {
            cpu->obstacles[i].active = TRUE;
            cpu->obstacles[i].x = x;
            cpu->obstacles[i].y = y;
        } else {
            cpu->obstacles[i].active = FALSE;
        }
        spots += 2;
    }
}

void PokeathlonPennantCaptureCpu_Delete(PokeathlonPennantCaptureCpu *cpu) {
    Heap_Free(cpu);
}

// Every `interval` frames the CPUs pick new targets, one CPU per frame. Returns the participant that
// decided (4 = none, 0 = no CPUs).
int PokeathlonPennantCaptureCpu_Update(PokeathlonPennantCaptureCpu *cpu) {
    s32 participant;
    int result = 4;

    if (cpu->humanCount == POKEATHLON_PARTICIPANTS) {
        return 0;
    }

    cpu->timer++;
    if (cpu->timer >= cpu->interval) {
        cpu->thinking = TRUE;
        cpu->timer = 0;
    }

    if (cpu->thinking) {
        participant = cpu->firstCpu + cpu->cursor;
        GF_ASSERT(participant >= cpu->firstCpu);
        PokeathlonPennantCaptureCpu_ChooseTarget(cpu, participant);
        result = (u8)participant;
        cpu->cursor++;
        if (cpu->cursor >= cpu->cpuCount) {
            cpu->cursor = 0;
            cpu->thinking = FALSE;
        }
    }
    return result;
}

// Rates the cells around the Pokemon (pennants +7, field items +2, other Pokemon -3, obstacles -2,
// off the field -100; towards the goal rows when carrying pennants) and heads for one of the best.
static void PokeathlonPennantCaptureCpu_ChooseTarget(PokeathlonPennantCaptureCpu *cpu, u8 who) {
    PokeathlonPennantCaptureCpuObject obstacles[PENNANT_CAPTURE_OBSTACLES], fieldItems[PENNANT_CAPTURE_FIELD_ITEMS];
    PokeathlonPennantCaptureCpuPlayer players[POKEATHLON_PARTICIPANTS];
    PokeathlonPennantCaptureCpuPlayer *self;
    PokeathlonPennantCapturePennant *pennants;
    PokeathlonPennantCapturePlayer *player;
    PokeathlonPennantCaptureCpuPoint raw, screen, chosen;
    PokeathlonCourseCpuCell *best;
    int i, j, k;
    player = cpu->players[who].player;
    if (player->depositing || player->knockedDown == 1 || player->freezeTimer) {
        return;
    }
    for (i = 0; i < POKEATHLON_PARTICIPANTS; i++) {
        PokeathlonPennantCapturePlayer *other;
        players[i] = cpu->players[i];
        other = players[i].player;
        PokeathlonCourseObject_GroundToCenter(other->monObjects[other->member], other->position.x / FX32_ONE, other->position.y / FX32_ONE, &raw.x, &raw.y);
        PokeathlonCourseObject_GetCollisionCenter(other->monObjects[other->member], raw.x << FX32_SHIFT, raw.y << FX32_SHIFT, &screen.x, &screen.y);
        players[i].x = screen.x / FX32_ONE;
        players[i].y = screen.y / FX32_ONE;
    }
    self = &players[who];
    for (i = 0; i < PENNANT_CAPTURE_OBSTACLES; i++) {
        obstacles[i] = cpu->obstacles[i];
    }
    for (i = 0; i < PENNANT_CAPTURE_FIELD_ITEMS; i++) {
        fieldItems[i] = cpu->fieldItems[i];
    }
    pennants = cpu->pennants;
    for (i = 0; i < PENNANT_CAPTURE_CPU_CELLS; i++) {
        cpu->cells[i].index = i;
        cpu->cells[i].x = self->x - 80 + (i % 6) * 32;
        cpu->cells[i].y = self->y - 48 + (i / 6) * 32;
        cpu->cells[i].targetX = self->x - 96 + (i % 6) * 32 + (int)LCRandom() % 32;
        cpu->cells[i].targetY = self->y - 128 + (i / 6) * 32 + (int)LCRandom() % 32;
    }
    for (i = 0; i < PENNANT_CAPTURE_CPU_CELLS; i++) {
        cpu->cells[i].score = 0;
    }
    // BUG: k is not used, so the four cells in front of the player (19..22) simply get the bonus twice.
    for (k = 0; k < 2; k++) {
        for (j = 0; j < 4; j++) {
            u8 id = j + 19;
            cpu->cells[id].score += 2;
        }
    }
    for (i = 0; i < PENNANT_CAPTURE_CPU_CELLS; i++) {
        PokeathlonCourseCpuCell *cell = &cpu->cells[i];
        {
            PokeathlonPennantCapturePennant *pennant = pennants;
            for (j = 0; j < PENNANT_CAPTURE_PENNANTS; j++, pennant++) {
                if (pennant->active && PokeathlonPennantCaptureCpu_IsNearCellTarget(cell, pennant->x, pennant->y)) {
                    cell->score += 7;
                }
            }
        }
        for (j = 0; j < POKEATHLON_PARTICIPANTS; j++) {
            if (j != who && PokeathlonPennantCaptureCpu_IsNearCellTarget(cell, players[j].x, players[j].y)) {
                cell->score -= 3;
            }
        }
        for (j = 0; j < PENNANT_CAPTURE_OBSTACLES; j++) {
            if (!obstacles[j].active) {
                break;
            }
            if (PokeathlonPennantCaptureCpu_IsNearCellTarget(cell, (u16)obstacles[j].x, (u16)obstacles[j].y)) {
                cell->score -= 2;
            }
        }
        for (j = 0; j < PENNANT_CAPTURE_FIELD_ITEMS; j++) {
            if (!fieldItems[j].active) {
                break;
            }
            if (PokeathlonPennantCaptureCpu_IsNearCellTarget(cell, (u16)fieldItems[j].x, (u16)fieldItems[j].y)) {
                cell->score += 2;
            }
        }
        if (!PokeathlonPennantCaptureCpu_IsCellTargetOnField(cell)) {
            cell->score -= 100;
        }
    }
    {
        u16 y = player->position.y / FX32_ONE;
        if (y > 256) {
            for (i = 0; i < 6; i++) {
                cpu->cells[i + 30].score += 3;
            }
        } else if (y < 256) {
            for (i = 0; i < 6; i++) {
                cpu->cells[i].score += 3;
            }
        }
    }
    if (player->pennants) {
        for (i = 0; i < 6; i++) {
            cpu->cells[i + 30].score += player->pennants;
        }
        {
            u16 x = player->position.x / FX32_ONE;
            if (x > 256) {
                for (i = 0; i < 3; i++) {
                    cpu->cells[i + 30].score += 2;
                }
            } else if (x < 256) {
                for (i = 0; i < 3; i++) {
                    cpu->cells[i + 33].score += 2;
                }
            }
        }
    }
    best = PokeathlonPennantCaptureCpu_PickBestCell(cpu);
    if ((u32)who >= cpu->firstCpu) {
        PokeathlonPennantCapturePlayer *mon = self->player;
        PokeathlonCourseObject_GroundToCenter(mon->monObjects[mon->member], self->x, self->y, &chosen.x, &chosen.y);
        self->player->cpuFrom.x = chosen.x << FX32_SHIFT;
        self->player->cpuFrom.y = chosen.y << FX32_SHIFT;
        self->player->cpuFrom.z = 0;
        self->player->cpuTarget.x = best->targetX << FX32_SHIFT;
        self->player->cpuTarget.y = best->targetY << FX32_SHIFT;
        self->player->cpuTarget.z = 0;
        self->player->cpuHasTarget = 1;
    }
}

static PokeathlonCourseCpuCell *PokeathlonPennantCaptureCpu_PickBestCell(PokeathlonPennantCaptureCpu *cpu) {
    PokeathlonCourseCpuCell *sorted[48];
    PokeathlonCourseCpuCell *list[PENNANT_CAPTURE_CPU_CELLS];
    s32 i;
    s32 count;
    u8 index;

    for (i = 0; i < PENNANT_CAPTURE_CPU_CELLS; i++) {
        list[i] = &cpu->cells[i];
    }
    count = PokeathlonPennantCaptureCpu_SortCells(list, sorted);
    index = (int)LCRandom() % count;
    return sorted[index];
}

// Sorts the cells by score (insertion into a linked list, best first); returns how many share the best score.
static u8 PokeathlonPennantCaptureCpu_SortCells(PokeathlonCourseCpuCell **cells, PokeathlonCourseCpuCell **out) {
    PokeathlonCourseCpuCellNode nodes[PENNANT_CAPTURE_CPU_CELLS + 1];
    u8 count;
    u8 i, j;
    PokeathlonCourseCpuCellNode *node;
    PokeathlonCourseCpuCellNode *cur;

    nodes[0].prev = &nodes[1];
    nodes[0].next = &nodes[1];
    nodes[0].cell = NULL;
    count = 0;
    for (i = 0; i < PENNANT_CAPTURE_CPU_CELLS; i++) {
        node = &nodes[i + 1];
        node->cell = cells[i];
        node->next = NULL;
        node->prev = NULL;
        cur = &nodes[0];
        for (j = 0; j < i; j++) {
            cur = cur->next;
            if (cur->cell->score < node->cell->score) {
                cur->prev->next = node;
                node->prev = cur->prev;
                node->next = cur;
                cur->prev = node;
                break;
            }
        }
        if (j == i) {
            cur->next = node;
            node->prev = cur;
        }
    }
    {
        PokeathlonCourseCpuCellNode *it;
        s16 first;
        first = nodes[0].next->cell->score;
        for (j = 0, it = &nodes[0]; j < PENNANT_CAPTURE_CPU_CELLS; j++) {
            it = it->next;
            out[j] = it->cell;
            if (first == out[j]->score) {
                count++;
            }
        }
    }
    GF_ASSERT(count != 0);
    return count;
}
