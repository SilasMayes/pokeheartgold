#ifndef PORT_SDK_LOBBY_CPP_PRELUDE_H
#define PORT_SDK_LOBBY_CPP_PRELUDE_H

// Port build only: force-included into the Wi-Fi Plaza lobby's C++ files. MSL's C headers
// also declared their functions in namespace std (the lobby uses std::memcmp, std::va_list,
// ...); with the host C++ library that takes the <c...> headers.
#include <cstdarg>
#include <cstddef>
#include <cstring>

#endif // PORT_SDK_LOBBY_CPP_PRELUDE_H
