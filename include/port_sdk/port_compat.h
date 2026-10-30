#ifndef PORT_SDK_PORT_COMPAT_H
#define PORT_SDK_PORT_COMPAT_H

// Port build only (included from global.h when SDK_PORT is defined).
// The decomp was written against its own reconstruction of the NitroSDK headers (lib/include);
// the port compiles against libntr, which follows Nintendo's real headers. This file bridges
// the names and helpers that differ. Keep it to spelling differences: anything with behaviour
// belongs in libntr or in the game code behind SDK_PORT.

// mwcc accepted extern prototypes for functions defined static; gcc and clang don't.
// Headers mark those prototypes PORT_STATIC (empty on the DS build). Also marks globals two
// overlays both define (fine for the DS link, a duplicate symbol in one binary).
#define PORT_STATIC static

// Functions that fall off their end after a call, so the DS returns that call's result (it is
// still in r0): the port keeps it in a variable and returns it. The bare call on the DS.
#define PORT_RESULT(var, call) ((var) = (call))

// cw/function_target.h
#ifndef ALIGN
#define ALIGN(num) __attribute__((aligned(num)))
#endif
#define ARM_FUNC
#define THUMB_FUNC
#define ENUMS_ALWAYS_INT_ON
#define ENUMS_ALWAYS_INT_OFF
#define ENUMS_ALWAYS_INT_RESET

// SDK_CW_FORCE_EXPORT_SUPPORT is set for libntr's own build; __declspec means nothing here
#undef SDK_FORCE_EXPORT
#define SDK_FORCE_EXPORT

// nitro/os/common/interrupt_shared.h
#define OS_IE_VBLANK OS_IE_V_BLANK
#define OS_IE_HBLANK OS_IE_H_BLANK

// nitro/gx/gx.h
#define GX_PLANEMASK_ALL (GX_PLANEMASK_BG0 | GX_PLANEMASK_BG1 | GX_PLANEMASK_BG2 | GX_PLANEMASK_BG3 | GX_PLANEMASK_OBJ)

// nitro/card/common.h (libntr has it since hgss-stubs)
#ifndef CARD_BACKUP_TYPE_FLASH_4MBITS_EX
#define CARD_BACKUP_TYPE_FLASH_4MBITS_EX (CARDBackupType)(CARD_BACKUP_TYPE_FLASH_4MBITS | (255 << CARD_BACKUP_TYPE_VENDER_SHIFT))
#endif

// The decomp's NNSG2dCharacterData spells this member "mapingType"; libntr has the SDK's
// "mappingType". The token never appears anywhere else.
#define mapingType mappingType

// A game callback whose prototype differs from the SDK typedef only in ways the ABI doesn't
// see (an enum where the game says int, trailing arguments the game ignores). clang treats
// the mismatch as an error; on the DS build this is just the function name.
#define PORT_CB(type, func) ((type)(func))

// The decomp's NitroSDK declares this in nitro/card/backup.h (Pokéwalker IR path); libntr does
// too since hgss-stubs, with the same prototype
int CARD_SpiWaitGetStatus(void);

// nitro/math/qsort.h: the decomp declares MATH_QSort locally with its own comparator types;
// route every call through libntr's MATHCompareFunc (same ABI: two pointers in, s32 out).
#define MATH_QSort(head, num, width, comp, buf) (MATH_QSort)((head), (num), (width), (MATHCompareFunc)(comp), (buf))

#endif // PORT_SDK_PORT_COMPAT_H
