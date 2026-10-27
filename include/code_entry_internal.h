#ifndef POKEHEARTGOLD_CODE_ENTRY_INTERNAL_H
#define POKEHEARTGOLD_CODE_ENTRY_INTERNAL_H

#include "global.h"

#include "bg_window.h"
#include "code_entry.h"
#include "filesystem.h"
#include "font_sprite.h"
#include "obj_char_transfer.h"
#include "palette.h"
#include "sprite_system.h"
#include "touch_hitbox_controller.h"
#include "touchscreen.h"

// Touch hitboxes: the 16 digit slots, the 10 digit keys, BACK, OK.
#define CODE_ENTRY_HITBOX_KEYS 16
#define CODE_ENTRY_HITBOX_BACK 26
#define CODE_ENTRY_HITBOX_OK   27
#define CODE_ENTRY_HITBOX_NUM  28

// CodeEntryApp.cursors
enum CodeEntryCursor {
    CODE_ENTRY_CURSOR_DIGIT, // value: the digit index
    CODE_ENTRY_CURSOR_KEY,   // value: CODE_ENTRY_KEY_CURSOR_*
    CODE_ENTRY_CURSOR_FLASH, // key press flash
    CODE_ENTRY_CURSOR_COUNT,
};

// Key cursor anims: around a digit key, around BACK / OK, the flash of a pressed key.
enum CodeEntryKeyCursorAnim {
    CODE_ENTRY_KEY_CURSOR_DIGIT = 1,
    CODE_ENTRY_KEY_CURSOR_BUTTON,
    CODE_ENTRY_KEY_CURSOR_PRESS,
};

enum CodeEntryState {
    CODE_ENTRY_STATE_SETUP,
    CODE_ENTRY_STATE_INPUT,
    CODE_ENTRY_STATE_SWITCH_GROUP,
    CODE_ENTRY_STATE_FADE_OUT,
};

enum CodeEntryAction {
    CODE_ENTRY_ACTION_NONE = 0,
    CODE_ENTRY_ACTION_SELECT_GROUP = 1, // arg: group (1-based)
    CODE_ENTRY_ACTION_MOVE_CURSOR = 2,  // arg: digit index
    CODE_ENTRY_ACTION_BUSY = 0xFF,
};

// A digit slot, a group separator, one of the three cursors or a BACK/OK button.
typedef struct CodeEntryCell {
    int value;  // digit + 1 (0: empty); separator: index of the digit before it; cursor: current anim
    int group;  // 1-based group of a digit
    BOOL active; // digit is in the selected group (drawn large)
    ManagedSprite *sprite;
    TouchscreenHitbox *hitbox;
    union {
        struct {
            s16 velocityX; // digit or separator sliding to its place
            s16 velocityY;
        };
        struct {
            s16 column; // key cursor: the selected key
            s16 row;
        };
    };
    u8 moveFrames; // button: frames since it was pressed
    u8 animStep;
    u8 padding[2];
} CodeEntryCell;

typedef struct CodeEntryRange {
    u16 start;
    u16 end;
} CodeEntryRange;

typedef struct CodeEntryButtonLabelAlloc {
    ObjCharSpaceReservation charAlloc;
} CodeEntryButtonLabelAlloc;

typedef struct CodeEntryApp {
    CodeEntryCell digits[16];
    CodeEntryCell separators[3];
    CodeEntryCell cursors[CODE_ENTRY_CURSOR_COUNT];
    CodeEntryCell buttons[2]; // BACK, OK (value: pressed state)
    s16 groupX[5];
    CodeEntryRange groupRanges[5];
    u8 padding2BE[2];
    enum CodeEntryState state;
    int unk2C4;
    int subState;
    int frame;
    int digitCount;
    int selectedGroup;
    int previousGroup;
    int selectedStart;
    int selectedEnd;
    int previousStart;
    int previousEnd;
    NARC *narc;
    SpriteSystem *spriteSystem;
    SpriteManager *spriteManager;
    BgConfig *bgConfig;
    PaletteData *paletteData;
    TouchHitboxController *touchController;
    TouchscreenHitbox hitboxes[CODE_ENTRY_HITBOX_NUM];
    BOOL touchActive;
    FontSystem *fontSystem;
    TextOBJ *buttonLabels[2];
    CodeEntryButtonLabelAlloc buttonLabelAllocs[2];
    Window promptWindow;
    enum CodeEntryAction pendingAction;
    int pendingArg;
    BOOL pendingToLast;
    CodeEntryArgs args;
    int separatorCount;
    int firstEditable;
} CodeEntryApp;
typedef struct CodeEntryKeyGrid {
    int cells[3][5];
} CodeEntryKeyGrid;

typedef BOOL (*CodeEntryStateFunc)(CodeEntryApp *app);

void CodeEntry_SelectGroup(CodeEntryApp *app, int group);
BOOL CodeEntry_RunState(CodeEntryApp *app);
void CodeEntry_InitTouch(CodeEntryApp *app);
void CodeEntry_InitSpriteSystem(CodeEntryApp *app);
void CodeEntry_LoadGraphics(CodeEntryApp *app);
void CodeEntry_FreeGraphics(CodeEntryApp *app);
void CodeEntry_CreateDigitSprites(CodeEntryApp *app);
void CodeEntry_CreateCursorSprites(CodeEntryApp *app);
void CodeEntry_CreateButtonSprites(CodeEntryApp *app);
void CodeEntry_SetCursorVisible(CodeEntryApp *app, enum CodeEntryCursor cursor, BOOL visible);
void CodeEntry_MoveDigitCursor(CodeEntryApp *app, int digit);
void CodeEntry_MoveKeyCursor(CodeEntryApp *app, int key);
void CodeEntry_MoveCursorToKey(CodeEntryApp *app, int key, enum CodeEntryCursor cursor);
void CodeEntry_UpdateCursors(CodeEntryApp *app);
void CodeEntry_UpdateButtons(CodeEntryApp *app);
int CodeEntry_GetDigitAnim(int value, BOOL active);
void CodeEntry_MarkSelectedDigits(CodeEntryApp *app);
void CodeEntry_LayoutDigits(CodeEntryApp *app, BOOL animate);
void CodeEntry_UpdateDigitHitboxes(CodeEntryApp *app);
void CodeEntry_InitFont(CodeEntryApp *app);
void CodeEntry_CreateButtonLabels(CodeEntryApp *app);
void CodeEntry_CreatePromptWindow(BgConfig *bgConfig, Window *window, int bgId, int x, int y, int width, int height, int baseTile, int msgNo);

#endif // POKEHEARTGOLD_CODE_ENTRY_INTERNAL_H
