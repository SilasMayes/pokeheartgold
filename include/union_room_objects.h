#ifndef POKEHEARTGOLD_UNION_ROOM_OBJECTS_H
#define POKEHEARTGOLD_UNION_ROOM_OBJECTS_H

#include "player_avatar.h"
#include "pm_string.h"
#include "save_palpad.h"
#include "field_warp_reset.h"

enum UnionRoomSlotState {
    UNION_ROOM_SLOT_HIDDEN,
    UNION_ROOM_SLOT_APPEARING,
    UNION_ROOM_SLOT_SHOWN,
    UNION_ROOM_SLOT_LEAVING,
    UNION_ROOM_SLOT_LEFT,
};

enum UnionRoomSlotRequest {
    UNION_ROOM_SLOT_REQUEST_NONE,
    UNION_ROOM_SLOT_REQUEST_APPEAR_ALONE,
    UNION_ROOM_SLOT_REQUEST_APPEAR_IN_GROUP,
    UNION_ROOM_SLOT_REQUEST_LEAVE,
};

// One union room map object: slots 0-9 are the other players (object ids 1-10), slots 10-49 the members of their
// groups (4 per player, first slot from a table), slot 50 is the player's own avatar.
typedef struct UnionRoomSlot {
    u8 request;    // enum UnionRoomSlotRequest
    u8 state;      // enum UnionRoomSlotState
    u8 friendship; // Pal Pad friend level, shown as an effect when the object appears
    u8 emoteRequest;
    u8 emoteActive;
    u8 unk_05;
    u16 emoteTimer;
    u8 sprite;
    u8 isWandering; // set when a lone player starts walking around
    u8 unk_0A[2];
    u32 id; // the player record's id when the object appeared
    FieldEffect *emote;
    FieldEffect *friendEffect;
} UnionRoomSlot;

typedef struct UnionRoomMessage {
    String *name;
    String *string1;
    String *string2;
    u32 trainerId;
    u32 gender;
    MailMessage mail;
} UnionRoomMessage;

#define UNION_CHAT_LOG_NUM_MESSAGES 30

// The chat messages of the players in the room, shown by the chat log (union_chat_log.h). Once count reaches
// UNION_CHAT_LOG_NUM_MESSAGES the oldest message is at head.
typedef struct UnionChatLogMessages {
    UnionRoomMessage slots[UNION_CHAT_LOG_NUM_MESSAGES];
    int count;
    int head;
} UnionChatLogMessages;

typedef struct UnionRoomObjects {
    struct UnionRoom *unionRoom;
    SysTask *task;
    PlayerAvatar *avatar;
    UnionRoomSlot slots[51];
    FieldSystem *fieldSystem;
    SavePalPad *palPad;
    UnionChatLogMessages *messages;
    u32 enabled;
    u32 unk4E4;
} UnionRoomObjects;

UnionRoomObjects *UnionRoomObjects_New(struct UnionRoom *unionRoom);
void UnionRoomObjects_ResetSlots(UnionRoomObjects *);
void UnionRoomObjects_RequestLeaveAll(UnionRoomObjects *objects);
void UnionRoomObjects_Delete(UnionRoomObjects *objects);
void UnionRoomObjects_RestoreAfterScript(MapObjectManager *mapObjectManager, UnionRoomObjects *objects);

#endif // POKEHEARTGOLD_UNION_ROOM_OBJECTS_H
