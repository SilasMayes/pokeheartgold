#ifndef POKEHEARTGOLD_CODE_ENTRY_H
#define POKEHEARTGOLD_CODE_ENTRY_H

#include "heap.h"
#include "options.h"
#include "overlay_manager.h"
#include "pm_string.h"

// Code entry app (heap 108): a touch/button keypad for entering a digit code split into groups, e.g. a
// Friend Code (4-4-4), a Wii number, a registration code or a 4-digit password. The prompt text is
// message promptMsg of msg_0038. On OK the digits are appended to text.
typedef struct CodeEntryArgs {
    u32 length;          // total number of digits
    int groupLengths[5]; // digits per group, 0-terminated (the last entry repeats the 4th)
    u32 unk18;
    String *text;      // receives the entered digits
    Options *options;  // window frame
    int fixedGroups;   // leading groups that are pre-filled with fixedValue and cannot be edited
    u32 fixedValue;
    int promptMsg;
    u32 showWirelessIcon;
} CodeEntryArgs;

extern const OverlayManagerTemplate gOverlayTemplate_CodeEntry;

BOOL CodeEntry_Init(OverlayManager *manager, int *state);
BOOL CodeEntry_Main(OverlayManager *manager, int *state);
BOOL CodeEntry_Exit(OverlayManager *manager, int *state);
CodeEntryArgs *CodeEntryArgs_New(enum HeapID heapID, u32 length, const int *groupLengths, Options *options, int promptMsg, u32 showWirelessIcon);
CodeEntryArgs *CodeEntryArgs_NewWithFixedDigits(enum HeapID heapID, u32 length, const int *groupLengths, Options *options, int promptMsg, u32 showWirelessIcon, int fixedGroups, u32 fixedValue);
void CodeEntryArgs_Delete(CodeEntryArgs *args);

#endif // POKEHEARTGOLD_CODE_ENTRY_H
