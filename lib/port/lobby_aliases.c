// Port-only pieces of the desktop Wi-Fi Plaza lobby library (not part of the make build).
//
// The DS build adds the C++ destructors the lobby code calls as aliases of C functions
// (src/lobby/*.alias-map.json, applied by tools/object_aliases.py); here they are thin wrappers.
// Itanium C++ ABI: a complete-object destructor (D1) takes `this` and returns nothing.
// throw_length_error comes from MSL's C++ library on the DS; the lobby is built without exceptions.

#include "global.h"

void *LobbyEventDeque_Destroy2(void *deque);
void *LobbyCharVector_Destroy(void *vector);

// Deque::~Deque()
void _ZN5DequeD1Ev(void *self) {
    LobbyEventDeque_Destroy2(self);
}

// Bytes::~Bytes()
void _ZN5BytesD1Ev(void *self) {
    LobbyCharVector_Destroy(self);
}

// The lobby's version string, which the DS keeps in src/data/middleware_4.c (left out of the port's
// source list with the other SDK version strings, whose headers clash with libntr's)
const char _version_NINTENDO_DWC_LOBBY[25] = "[SDK+NINTENDO:DWC_LOBBY]";

// std::__vector_common<true>::throw_length_error()
void _ZNSt15__vector_commonILb1EE18throw_length_errorEv(void) {
    OS_Terminate();
}
