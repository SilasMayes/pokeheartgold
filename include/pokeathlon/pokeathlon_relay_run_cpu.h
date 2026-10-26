#ifndef POKEHEARTGOLD_POKEATHLON_POKEATHLON_RELAY_RUN_CPU_H
#define POKEHEARTGOLD_POKEATHLON_POKEATHLON_RELAY_RUN_CPU_H

#include "global.h"

#include "pokeathlon/pokeathlon_course_types_def.h"
#include "pokeathlon/pokeathlon_relay_run.h"

// The CPU of the Relay Run teams without a player: it rates the cells ahead of the team's runner and either flicks
// the runner towards one of the best cells or hands over to the next member of the team.

#define RELAY_RUN_CPU_LANES     4
#define RELAY_RUN_CPU_COLUMNS   4 // cells ahead of the runner in each lane
#define RELAY_RUN_CPU_CELLS     (RELAY_RUN_CPU_LANES * RELAY_RUN_CPU_COLUMNS)
#define RELAY_RUN_CPU_CELL_SIZE 40
#define RELAY_RUN_CPU_LOOKAHEAD (RELAY_RUN_CPU_COLUMNS * RELAY_RUN_CPU_CELL_SIZE)
#define RELAY_RUN_CPU_NONE      POKEATHLON_PARTICIPANTS // PokeathlonRelayRunCpu_Update: no team was looked at

// What the CPU sees of a team: the team and the collision centre of its runner (whole pixels).
typedef struct PokeathlonRelayRunCpuTeam {
    PokeathlonRelayRunTeam *team;
    u32 unk04;
    int x;
    int y;
} PokeathlonRelayRunCpuTeam;

// An obstacle of the track layout, as a square of `size` pixels.
typedef struct PokeathlonRelayRunCpuObstacle {
    BOOL active;
    int x;    // left
    int y;    // top
    int kind; // RELAY_RUN_OBSTACLE_*
    int size;
} PokeathlonRelayRunCpuObstacle;

typedef struct PokeathlonRelayRunCpu {
    PokeathlonRelayRunCpuTeam teams[POKEATHLON_PARTICIPANTS];
    PokeathlonRelayRunCpuObstacle obstacles[RELAY_RUN_OBSTACLES];
    u8 lanes[POKEATHLON_PARTICIPANTS]; // lane (0-3) of each team's runner
    PokeathlonCourseCpuCell cells[RELAY_RUN_CPU_CELLS];
    u32 thinking; // looking at the CPU teams one per frame
    u8 cpuCount;
    u8 cursor; // next CPU team to look at
    u8 timer;
    u8 interval;
    u8 firstCpu; // the CPU teams come after the players
    u8 humanCount;
} PokeathlonRelayRunCpu;

void PokeathlonRelayRunHud_GetPicVramOffsets(PokeathlonCourseSpritePool *pool, PokeathlonRelayRunHud *hud);
void PokeathlonRelayRunHud_InitWindows(PokeathlonRelayRunHud *hud);
PokeathlonRelayRunCpu *PokeathlonRelayRunCpu_New(enum HeapID heapId, int cpuCount, int mode);
void PokeathlonRelayRunCpu_SetTeam(PokeathlonRelayRunCpu *cpu, u8 index, PokeathlonRelayRunTeam *team);
void PokeathlonRelayRunCpu_SetObstacles(PokeathlonRelayRunCpu *cpu, s32 *layout);
void PokeathlonRelayRunCpu_Delete(PokeathlonRelayRunCpu *cpu);
u8 PokeathlonRelayRunCpu_Update(PokeathlonCourseData *course, PokeathlonRelayRunCpu *cpu, s32 timer);
u8 PokeathlonRelayRunCpu_SortCells(PokeathlonCourseCpuCell **cells, PokeathlonCourseCpuCell **out);

#endif // POKEHEARTGOLD_POKEATHLON_POKEATHLON_RELAY_RUN_CPU_H
