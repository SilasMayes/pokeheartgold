#ifndef DWC_TREE_ITERATOR4_H
#define DWC_TREE_ITERATOR4_H
typedef struct Iterator {
    void *current;
#ifdef __cplusplus
    void Advance();
#endif
} Iterator;
#ifndef SDK_PORT // 32-bit layout checks for the DS build; pointers are 8 bytes here
typedef char DwcTreeIteratorSize4[sizeof(Iterator)==4?1:-1];
#endif // SDK_PORT
#ifndef __cplusplus
void LobbyTreeIterator_Advance(Iterator *);
#endif
#endif
