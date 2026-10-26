#include "global.h"

#include <nitro/code32.h>

#include "lobby_event_deque.h"

// Rotation and binary search over sorted runs: the sort merges with these in place when its buffer is too small.

void LobbySort_Rotate(LobbyEventVectorIterator *out, LobbyEventVectorIterator first, LobbyEventVectorIterator middle, LobbyEventVectorIterator last);
void LobbySort_LowerBound(LobbyEventVectorIterator *out, LobbyEventVectorIterator first, LobbyEventVectorIterator last, const LobbyEvent *value);
void LobbySort_UpperBound(LobbyEventVectorIterator *out, LobbyEventVectorIterator first, LobbyEventVectorIterator last, const LobbyEvent *value);

void LobbySort_Rotate(LobbyEventVectorIterator *out, LobbyEventVectorIterator first, LobbyEventVectorIterator middle, LobbyEventVectorIterator last) {
    LobbyEvent *pivot, *left, *right, *result;
    LobbyEvent temp1, temp2;
    left = first.p;
    pivot = middle.p;
    if (left == pivot) {
        *out = last;
        return;
    }
    if (pivot == last.p) {
        out->p = ((volatile LobbyEventVectorIterator *)&first)->p;
        return;
    }
    right = ((volatile LobbyEventVectorIterator *)&middle)->p;
    for (;;) {
        temp1 = *left;
        left->time = right->time;
        left->type = right->type;
        right->time = temp1.time;
        right->type = temp1.type;
        ++right;
        ++left;
        if (right == last.p) {
            break;
        }
        if (left == pivot) {
            pivot = right;
        }
    }
    result = left;
    if (left != pivot) {
        right = pivot;
        for (;;) {
            temp2 = *left;
            left->time = right->time;
            left->type = right->type;
            right->time = temp2.time;
            right->type = temp2.type;
            ++right;
            ++left;
            if (right == last.p) {
                if (left == pivot) {
                    break;
                }
                right = pivot;
            } else if (left == pivot) {
                pivot = right;
            }
        }
    }
    out->p = result;
}

void LobbySort_LowerBound(LobbyEventVectorIterator *out, LobbyEventVectorIterator first, LobbyEventVectorIterator last, const LobbyEvent *value) {
    LobbyEventVectorIterator start = first;
    int count = last.p - start.p;
    while (count > 0) {
        int half = count / 2;
        LobbyEventVectorIterator mid;
        mid.p = first.p + half;
        if (mid.p->time < value->time) {
            first.p = mid.p + 1;
            count -= half + 1;
        } else {
            count = half;
        }
    }
    *out = first;
}

void LobbySort_UpperBound(LobbyEventVectorIterator *out, LobbyEventVectorIterator first, LobbyEventVectorIterator last, const LobbyEvent *value) {
    LobbyEventVectorIterator start = first;
    int count = last.p - start.p;
    while (count > 0) {
        int half = count / 2;
        LobbyEventVectorIterator mid;
        mid.p = first.p + half;
        if (!(value->time < mid.p->time)) {
            first.p = mid.p + 1;
            count -= half + 1;
        } else {
            count = half;
        }
    }
    *out = first;
}
