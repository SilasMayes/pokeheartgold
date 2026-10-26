#include "global.h"

#include "lobby_tree.h"
#include "lobby_vector.h"

#include <nitro/code32.h>
#include "ppw_lobby_internal.h"

typedef struct {
    Iterator advance;
    void *other;
} Iter;

void LobbyU32Vector_AssignFromSet(LobbyU32Vector *vector, Iter first, Iter last);

typedef struct {
    u8 fillFlag, reserveFlag;
    u8 pad[2];

    struct {
        LobbyUserIdSetNode *a;
        int b;
        LobbyUserIdSetNode *c;
    } tail;

    Iter fill, count;
} Frame;

void LobbyU32Vector_AssignFromSet(LobbyU32Vector *vector, Iter first, Iter last) {
    Frame frame;
    LobbyUserIdSetNode *node;
    int value;
    u32 *out;
    u32 count, capacity;
    frame.count = first;
    Iter *counter = &frame.count;
    count = 0;
    while (frame.count.advance.current != last.advance.current) {
        count++;
        LobbyTreeIterator_Advance(&counter->advance);
    }
    capacity = vector->capacity;
    if (count > capacity) {
        frame.reserveFlag = 0;
        u32 newCapacity = LobbyU32Vector_RecommendSize(vector, count - capacity);
        LobbyU32Vector_Reallocate(vector, count, newCapacity);
    }
    out = vector->data;
    frame.fill = first;
    if (frame.fill.advance.current != last.advance.current) {
        do {
            node = *(void *volatile *)&frame.fill.advance.current;
            frame.fillFlag = 0;
            value = *(volatile int *)&node->userId;
            *out++ = value;
            LobbyTreeIterator_Advance(&frame.fill.advance);
        } while (frame.fill.advance.current != last.advance.current);
        frame.tail.b = value;
        frame.tail.a = node;
        frame.tail.c = node;
    }
    vector->size = count;
}
