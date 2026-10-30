// Converted from asm/map_object_behavior_data.s by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout. Keep that when editing, or rerun tools/s2c.py.

#include "global.h"

#include "constants/field_move_response.h"
#include "constants/flags.h"
#include "constants/items.h"
#include "constants/maps.h"
#include "constants/pokemon.h"
#include "constants/sndseq.h"
#include "constants/species.h"
#include "constants/std_script.h"
#include "constants/vars.h"

#include "fielddata/script/scr_seq/event_D24R0204.h"

#include "map_object_behavior_internal.h"

#pragma force_active on

// clang-format off
const MapObjectAction gMapObjectTypeBehaviorInits[12] = {
    TypeBehavior_NoOpInit, TypeBehavior_NoOpInit, TypeBehavior_NoOpInit, TypeBehavior_NoOpInit,
    TypeBehavior_LookSidewaysInit, TypeBehavior_SpinInit, TypeBehavior_SpinInit, TypeBehavior_NoOpInit,
    TypeBehavior_NoOpInit, TypeBehavior_NoOpInit, TypeBehavior_NoOpInit, TypeBehavior_NoOpInit,
};
// clang-format on

// clang-format off
const MapObjectPredicate gMapObjectTypeBehaviorChecks[12] = {
    TypeBehavior_NoOpCheck, TypeBehavior_NoOpCheck, TypeBehavior_NoOpCheck, TypeBehavior_NoOpCheck,
    TypeBehavior_LookSidewaysCheck, TypeBehavior_SpinCheck, TypeBehavior_SpinCheck, TypeBehavior_NoOpCheck,
    TypeBehavior_NoOpCheck, TypeBehavior_NoOpCheck, TypeBehavior_NoOpCheck, TypeBehavior_NoOpCheck,
};
// clang-format on

// clang-format off
const MapObjectPredicate gMapObjectTypeBehaviorUpdates[12] = {
    TypeBehavior_NoOpUpdate, TypeBehavior_NoOpUpdate, TypeBehavior_NoOpUpdate, TypeBehavior_NoOpUpdate,
    TypeBehavior_LookSidewaysUpdate, TypeBehavior_SpinUpdate, TypeBehavior_SpinUpdate,
    TypeBehavior_NoOpUpdate, TypeBehavior_NoOpUpdate, TypeBehavior_NoOpUpdate, TypeBehavior_NoOpUpdate,
    TypeBehavior_NoOpUpdate,
};
// clang-format on

const DirectionMovementTable gTypeBehaviorSpinOrders = {
    { { 0, 2, 1, 3 }, { 0, 3, 1, 2 } }
};

const FourValues gLookSidewaysAxisByFacing = {
    { 0, 0, 1, 1 }
};

const TwoByTwoValues gLookSidewaysDirections = {
    { { 2, 3 }, { 0, 1 } }
};
