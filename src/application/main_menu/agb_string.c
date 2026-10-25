#include "global.h"

#include "constants/charcode.h"

#include "application/main_menu/agb_cartridge.h"

// Conversion of Ruby/Sapphire/Emerald/FireRed/LeafGreen strings to this game's characters (Migrate from GBA).

static u32 AgbString_GetSpaceChar(u32 language);
static u16 AgbString_GetOpenQuoteChar(u32 language);
static u16 AgbString_GetCloseQuoteChar(u32 language);

// The space
static u32 AgbString_GetSpaceChar(u32 language) {
    u32 result;
    if (language == LANGUAGE_JAPANESE) {
        result = CHAR_JP_SPACE;
    } else {
        result = CHAR_SPACE;
    }
    return (u16)result;
}

// The opening double quote
static u16 AgbString_GetOpenQuoteChar(u32 language) {
    switch (language) {
    case LANGUAGE_JAPANESE:
    default:
        return CHAR_JP_OPEN_DQUOT;
    case LANGUAGE_ENGLISH:
    case LANGUAGE_ITALIAN:
    case LANGUAGE_SPANISH:
        return CHAR_LDQUOT;
    case LANGUAGE_FRENCH:
        return CHAR_FR_LQUOT;
    case LANGUAGE_GERMAN:
        return CHAR_LOW_RDQUOT;
    }
}

// The closing double quote
static u16 AgbString_GetCloseQuoteChar(u32 language) {
    switch (language) {
    case LANGUAGE_JAPANESE:
    default:
        return CHAR_JP_CLOSE_DQUOT;
    case LANGUAGE_ENGLISH:
    case LANGUAGE_ITALIAN:
    case LANGUAGE_SPANISH:
        return CHAR_RDQUOT;
    case LANGUAGE_FRENCH:
        return CHAR_FR_RQUOT;
    case LANGUAGE_GERMAN:
        return CHAR_LDQUOT;
    }
}

BOOL ConvertRSStringToDPStringInternational(const u8 *src, u16 *dst, u32 length, u32 language) {
    BOOL nonJa = (language != LANGUAGE_JAPANESE);
    u32 i;
    for (i = 0; i < (length - 1); i++) {
        if (src[i] == 0xFF) { // EOS
            break;
        }
        if (src[i] >= 0xF7) { // control characters: the string becomes "?????" (up to 10 characters)
            int invalidStrLen = (length - 1 < 10) ? length - 1 : 10;
            int j;
            for (j = 0; j < invalidStrLen; j++) {
                dst[j] = CHAR_QMARK;
            }
            dst[j] = EOS;
            return FALSE;
        }
        switch (sAgbToDpCharMap[src[i]][nonJa]) {
        case CHAR_JP_SPACE:
            dst[i] = AgbString_GetSpaceChar(language);
            break;
        case CHAR_JP_OPEN_DQUOT:
            dst[i] = AgbString_GetOpenQuoteChar(language);
            break;
        case CHAR_JP_CLOSE_DQUOT:
            dst[i] = AgbString_GetCloseQuoteChar(language);
            break;
        default:
            dst[i] = sAgbToDpCharMap[src[i]][nonJa];
            break;
        }
    }
    dst[i] = EOS;
    return TRUE;
}
