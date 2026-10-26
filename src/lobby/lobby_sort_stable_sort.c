#include "global.h"

#include <nitro/code32.h>

#include "lobby_event_deque.h"

typedef struct {
    int capacity, count;
    LobbyEvent *data;
} Buffer;

typedef struct {
    LobbyEvent *position;
    Buffer *state;
} Out;

typedef struct {
    unsigned value;
} Tag;

extern void LobbySort_StableSortAdaptive(LobbyEventVectorIterator, LobbyEventVectorIterator, Out, Out, Tag *);
extern void _ZdaPv(void *);
void LobbySort_StableSort(LobbyEventVectorIterator, LobbyEventVectorIterator, Tag);

void LobbySort_StableSort(LobbyEventVectorIterator first, LobbyEventVectorIterator last, Tag tag) {
    int count = last.p - first.p;
    Out begin;
    Out end;
    LobbySortTemporaryBuffer temp;
    Buffer buffer;
    if (count <= 20) {
        count = 0;
    }
    LobbySort_GetTemporaryBuffer(&temp, count);
    buffer.capacity = temp.count;
    buffer.count = 0;
    buffer.data = temp.data;
    end.position = temp.data + temp.count;
    end.state = &buffer;
    begin.position = temp.data;
    begin.state = &buffer;
    LobbySort_StableSortAdaptive(first, last, begin, end, &tag);
    _ZdaPv(buffer.data);
}
