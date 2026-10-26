#ifndef POKEHEARTGOLD_FIELD_BOTTOM_SCREEN_APP_H
#define POKEHEARTGOLD_FIELD_BOTTOM_SCREEN_APP_H

#include "field_system.h"

// The field's bottom-screen apps, run in FieldSystem.bottomScreenTask. FieldSystem_SwitchBottomScreenApp fades the
// sub screen out, exits the current app and starts the requested one.
enum BottomScreenAppId {
    BOTTOM_SCREEN_APP_TOUCHSCREEN_MENU,
    BOTTOM_SCREEN_APP_TOUCH_SAVE,
    BOTTOM_SCREEN_APP_TOUCH_MART,
    BOTTOM_SCREEN_APP_CHOICE_MENU,
    BOTTOM_SCREEN_APP_DOWSING_MCHN,
    BOTTOM_SCREEN_APP_NUMBER_ENTRY,
    BOTTOM_SCREEN_APP_FRIEND_ROSTER,
    BOTTOM_SCREEN_APP_COMM_CLUB_BUTTONS,
    BOTTOM_SCREEN_APP_UNION_CHAT_LOG,
};

enum BottomScreenAppState {
    BOTTOM_SCREEN_APP_STATE_INIT,
    BOTTOM_SCREEN_APP_STATE_RUNNING,
    BOTTOM_SCREEN_APP_STATE_SWITCH_REQUESTED,
    BOTTOM_SCREEN_APP_STATE_FADE_OUT,
    BOTTOM_SCREEN_APP_STATE_EXIT,
    BOTTOM_SCREEN_APP_STATE_WAIT_EXIT,
    BOTTOM_SCREEN_APP_STATE_START_NEXT,
    BOTTOM_SCREEN_APP_STATE_FADE_IN,
};

// The choice menu app's states (FieldSystem_SetTouchscreenChoiceMenuState / GetTouchscreenChoiceMenuState).
enum TouchscreenChoiceMenuState {
    TOUCHSCREEN_CHOICE_MENU_STATE_INIT,
    TOUCHSCREEN_CHOICE_MENU_STATE_IDLE,
    TOUCHSCREEN_CHOICE_MENU_STATE_WAIT_RETURN,
    TOUCHSCREEN_CHOICE_MENU_STATE_SHOW_YES_NO,
    TOUCHSCREEN_CHOICE_MENU_STATE_YES_NO_INPUT,
    TOUCHSCREEN_CHOICE_MENU_STATE_YES_NO_END,
    TOUCHSCREEN_CHOICE_MENU_STATE_DONE,
    TOUCHSCREEN_CHOICE_MENU_STATE_SHOW_LIST,
    TOUCHSCREEN_CHOICE_MENU_STATE_LIST_INPUT,
    TOUCHSCREEN_CHOICE_MENU_STATE_LIST_END,
    TOUCHSCREEN_CHOICE_MENU_STATE_LIST_WRITE_RESULT,
    TOUCHSCREEN_CHOICE_MENU_STATE_CANCEL_YES_NO,
};

void FieldSystem_SendBottomScreenEvent(FieldSystem *fieldSystem, int event, int unused);
void BottomScreen_TouchSave_Init(FieldSystem *fieldSystem);
void BottomScreen_TouchSave_End(FieldSystem *fieldSystem);
BOOL BottomScreen_TouchSave_IsDone(FieldSystem *fieldSystem);
void BottomScreen_Apps_Init(FieldSystem *fieldSystem);
void BottomScreen_Apps_End(FieldSystem *fieldSystem);
BOOL BottomScreen_Apps_IsDone(FieldSystem *fieldSystem);
void FieldSystem_RequestTouchscreenMenuSelectedIconAnim(FieldSystem *fieldSystem);
void FieldSystem_RequestTouchscreenMenuRegisteredItemAnim(FieldSystem *fieldSystem, int item);

// The label of the touchscreen menu's and the dowsing machine's action button: what the A button does now
// (FieldSystem_GetFacingActionType gives check / talk / check BG event).
enum TouchscreenMenuActionType {
    TOUCHSCREEN_MENU_ACTION_CHECK,
    TOUCHSCREEN_MENU_ACTION_TALK,
    TOUCHSCREEN_MENU_ACTION_CHECK_BG_EVENT,
    TOUCHSCREEN_MENU_ACTION_FISHING,
    TOUCHSCREEN_MENU_ACTION_NEXT,
};

BOOL IsSpriteIdWithoutTalkAction(int spriteId);
BOOL IsScriptIdWithoutTalkAction(int scriptId);

#endif // POKEHEARTGOLD_FIELD_BOTTOM_SCREEN_APP_H
