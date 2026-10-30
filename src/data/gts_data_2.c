// Converted from asm/gts_data.s (part 2 of 7) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

// The C declarations of these do not match the data (see the notes at each
// definition): keep them out of the way of the definitions below.
#define gGtsSelectorStates gGtsSelectorStates_header_decl

#include "global.h"

#include "constants/pokemon.h"

#include "gts/gts_internal.h"

#pragma force_active on

#undef gGtsSelectorStates

extern void GtsSelector_BackToCountryLetters(void);
extern void GtsSelector_BackToSpeciesLetters(void);
extern void GtsSelector_CancelCountryList(void);
extern void GtsSelector_CancelSpeciesList(void);
extern void GtsSelector_CloseCountryGroups(void);
extern void GtsSelector_CloseCountryLetters(void);
extern void GtsSelector_CloseSpeciesGroups(void);
extern void GtsSelector_CloseSpeciesLetters(void);
extern void GtsSelector_FinishCountry(void);
extern void GtsSelector_FinishGender(void);
extern void GtsSelector_FinishLevel(void);
extern void GtsSelector_FinishSpecies(void);
extern void GtsSelector_HandleCountryGroups(void);
extern void GtsSelector_HandleCountryLetters(void);
extern void GtsSelector_HandleCountryList(void);
extern void GtsSelector_HandleGenders(void);
extern void GtsSelector_HandleLevels(void);
extern void GtsSelector_HandleSpeciesGroups(void);
extern void GtsSelector_HandleSpeciesLetters(void);
extern void GtsSelector_HandleSpeciesList(void);
extern void GtsSelector_Idle(void);
extern void GtsSelector_OpenCountryGroups(void);
extern void GtsSelector_OpenCountryLetters(void);
extern void GtsSelector_OpenCountryList(void);
extern void GtsSelector_OpenGenders(void);
extern void GtsSelector_OpenLevels(void);
extern void GtsSelector_OpenSpeciesGroups(void);
extern void GtsSelector_OpenSpeciesLetters(void);
extern void GtsSelector_OpenSpeciesList(void);
extern void GtsSelector_ReopenCountryGroups(void);
extern void GtsSelector_ReopenSpeciesGroups(void);
extern void GtsSelector_WaitHide(void);
extern void GtsSelector_WaitMove(void);
extern void GtsSelector_WaitShow(void);

// clang-format off
const u16 gGtsCountries[130] = {
    1, 2, 3, 6, 8, 9, 0x000C, 0x000D, 0x000F, 0x0010, 0x0011, 0x0012, 0x0014, 0x0015, 0x0016, 0x0017, 0x0019,
    0x001B, 0x001C, 0x001D, 0x001F, 0x0021, 0x0022, 0x0023, 0x0024, 0x0028, 0x002A, 0x002B, 0x002D, 0x0030,
    0x0031, 0x0032, 0x0034, 0x0036, 0x0037, 0x0038, 0x003A, 0x003B, 0x003C, 0x003D, 0x003E, 0x0045, 0x0046,
    0x0047, 0x0048, 0x004A, 0x004D, 0x004E, 0x004F, 0x0050, 0x0051, 0x0052, 0x0053, 0x0055, 0x0056, 0x0058,
    0x0059, 0x005A, 0x005B, 0x005C, 0x005D, 0x005E, 0x005F, 0x0061, 0x0062, 0x0064, 0x0065, 0x0066, 0x0067,
    0x0068, 0x006B, 0x006F, 0x0073, 0x0075, 0x0076, 0x0079, 0x007A, 0x007E, 0x0081, 0x0083, 0x0085, 0x0087,
    0x008C, 0x008E, 0x0092, 0x0094, 0x0095, 0x0096, 0x0097, 0x0098, 0x009C, 0x009D, 0x009E, 0x00A0, 0x00A1,
    0x00A3, 0x00A4, 0x00A6, 0x00A7, 0x006E, 0x00AB, 0x00AC, 0x00B3, 0x00B7, 0x00BA, 0x00BB, 0x00BC, 0x00BD,
    0x00C0, 0x00C1, 0x00C2, 0x00C4, 0x00C6, 0x00C7, 0x00C8, 0x00CA, 0x00CD, 0x00CF, 0x00D3, 0x00D4, 0x00D8,
    0x00DA, 0x00DB, 0x00CC, 0x00DD, 0x00DC, 0x00DE, 0x00E0, 0x00E2, 0x00E3,
};
// clang-format on

// clang-format off
const int gGtsSpeciesLetterFiles[44] = {
    18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43,
    44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61,
};
// clang-format on

// C declares this const, but it lives in .data
// clang-format off
int (*gGtsSelectorStates[34])(GtsSelector *selector) = {
    (int (*)(GtsSelector *))GtsSelector_Idle, (int (*)(GtsSelector *))GtsSelector_WaitShow,
    (int (*)(GtsSelector *))GtsSelector_WaitMove, (int (*)(GtsSelector *))GtsSelector_WaitHide,
    (int (*)(GtsSelector *))GtsSelector_OpenSpeciesGroups,
    (int (*)(GtsSelector *))GtsSelector_HandleSpeciesGroups,
    (int (*)(GtsSelector *))GtsSelector_CloseSpeciesGroups,
    (int (*)(GtsSelector *))GtsSelector_ReopenSpeciesGroups,
    (int (*)(GtsSelector *))GtsSelector_OpenSpeciesLetters,
    (int (*)(GtsSelector *))GtsSelector_HandleSpeciesLetters,
    (int (*)(GtsSelector *))GtsSelector_CloseSpeciesLetters,
    (int (*)(GtsSelector *))GtsSelector_BackToSpeciesLetters,
    (int (*)(GtsSelector *))GtsSelector_OpenSpeciesList,
    (int (*)(GtsSelector *))GtsSelector_HandleSpeciesList,
    (int (*)(GtsSelector *))GtsSelector_CancelSpeciesList, (int (*)(GtsSelector *))GtsSelector_FinishSpecies,
    (int (*)(GtsSelector *))GtsSelector_OpenCountryGroups,
    (int (*)(GtsSelector *))GtsSelector_HandleCountryGroups,
    (int (*)(GtsSelector *))GtsSelector_CloseCountryGroups,
    (int (*)(GtsSelector *))GtsSelector_ReopenCountryGroups,
    (int (*)(GtsSelector *))GtsSelector_OpenCountryLetters,
    (int (*)(GtsSelector *))GtsSelector_HandleCountryLetters,
    (int (*)(GtsSelector *))GtsSelector_CloseCountryLetters,
    (int (*)(GtsSelector *))GtsSelector_BackToCountryLetters,
    (int (*)(GtsSelector *))GtsSelector_OpenCountryList,
    (int (*)(GtsSelector *))GtsSelector_HandleCountryList,
    (int (*)(GtsSelector *))GtsSelector_CancelCountryList, (int (*)(GtsSelector *))GtsSelector_FinishCountry,
    (int (*)(GtsSelector *))GtsSelector_OpenGenders, (int (*)(GtsSelector *))GtsSelector_HandleGenders,
    (int (*)(GtsSelector *))GtsSelector_FinishGender, (int (*)(GtsSelector *))GtsSelector_OpenLevels,
    (int (*)(GtsSelector *))GtsSelector_HandleLevels, (int (*)(GtsSelector *))GtsSelector_FinishLevel,
};
// clang-format on

const GtsLevelRange gGtsWantedLevelRanges[12] = {
    { 0x00000080, 0,   0   },
    { 0x00000081, 0,   9   },
    { 0x00000082, 10,  0   },
    { 0x00000083, 20,  0   },
    { 0x00000084, 30,  0   },
    { 0x00000085, 40,  0   },
    { 0x00000086, 50,  0   },
    { 0x00000087, 60,  0   },
    { 0x00000088, 70,  0   },
    { 0x00000089, 80,  0   },
    { 0x0000008A, 90,  0   },
    { 0x0000008B, 100, 100 },
};

const GtsLevelRange gGtsSearchLevelRanges[11] = {
    { 0x0000009F, 0,  0   },
    { 0x000000A0, 1,  10  },
    { 0x000000A1, 11, 20  },
    { 0x000000A2, 21, 30  },
    { 0x000000A3, 31, 40  },
    { 0x000000A4, 41, 50  },
    { 0x000000A5, 51, 60  },
    { 0x000000A6, 61, 70  },
    { 0x000000A7, 71, 80  },
    { 0x000000A8, 81, 90  },
    { 0x000000A9, 91, 100 },
};

const GtsCountryGroup gGtsCountryGroups[22] = {
    { 0x00, 0x00 },
    { 0x08, 0x01 },
    { 0x16, 0x02 },
    { 0x23, 0x03 },
    { 0x26, 0x04 },
    { 0x29, 0x05 },
    { 0x2D, 0x06 },
    { 0x38, 0x07 },
    { 0x3C, 0x08 },
    { 0x43, 0x09 },
    { 0x46, 0x0A },
    { 0x48, 0x0B },
    { 0x4C, 0x0C },
    { 0x54, 0x0D },
    { 0x5B, 0x0E },
    { 0x5C, 0x0F },
    { 0x63, 0x11 },
    { 0x66, 0x12 },
    { 0x73, 0x13 },
    { 0x78, 0x14 },
    { 0x7F, 0x15 },
    { 0x82, 0xFF },
};

GtsFriendKey gGtsServerFriendKey;

u8 gGtsServerRequest[236];
