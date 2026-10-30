#ifndef PORT_SDK_SIZE_T_H
#define PORT_SDK_SIZE_T_H

// Port build: MSL's size_t.h, which also put size_t in namespace std for C++.
#ifdef __cplusplus
#include <cstddef>
#else
#include <stddef.h>
#endif

#endif // PORT_SDK_SIZE_T_H
