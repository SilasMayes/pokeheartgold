#include "global.h"

#include <nitro/code32.h>

#include "ppw_lobby_work.h"

void LobbyVipVector_AssignRange(PPWLobbyVipVector *vector, const PPWLobbyVipRecord *first, const PPWLobbyVipRecord *last, LobbyTag tag) {
    u32 count = last - first, growth;
    const PPWLobbyVipRecord *end;
    PPWLobbyVipRecord *dest;
    volatile u8 a, c, d, b;
    if (vector->capacity < count) {
        a = 0;
        growth = LobbyVipVector_RecommendSize(vector, count - vector->capacity);
    } else {
        end = first;
        end += *(vector->size < count ? &vector->size : &count);
        dest = vector->data;
        while (first < end) {
            dest->id = first->id;
            dest->value = first->value;
            ++first;
            ++dest;
        }
        if (count < vector->size) {
            u32 old = vector->size;
            c = 0;
            vector->size = *(volatile u32 *)&vector->size - (old - count);
            return;
        }
        if (vector->size >= count) {
            return;
        }
        d = 0;
        dest = *(PPWLobbyVipRecord *volatile *)&vector->data + *(volatile u32 *)&vector->size;
        while (end != last) {
            if (dest) {
                *dest = *end;
            }
            ++vector->size;
            ++end;
            ++dest;
        }
        return;
    }
    LobbyVipVector_Reallocate(vector, count, growth);
    b = 0;
    dest = vector->data + *(volatile u32 *)&vector->size;
    for (; first != last; ++first, ++dest) {
        if (dest) {
            *dest = *first;
        }
        ++vector->size;
    }
}
