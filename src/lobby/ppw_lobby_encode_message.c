#include "global.h"

#include <nitro/code32.h>

#include "ppw_lobby_internal.h"
#include "ppw_lobby_state.h"

int LobbyString_ToLowerChar(int c) {
    if (c < 0 || c >= 0x80) {
        return c;
    }
    return __lower_mapC[c];
}

BOOL PPWLobby_EncodeMessage(int type, int mode, u32 value, const void *data, u32 len, Str *out) {
    char buf[0x191];
    Str s0;
    Str s1;
    Str s2;
    Str s3;
    if (type == PPW_LOBBY_MESSAGE_FORMAT_STRING && len > 400) {
        return FALSE;
    }
    if (type == PPW_LOBBY_MESSAGE_FORMAT_BINARY && len > 300) {
        return FALSE;
    }
    LobbyString_AssignCStr(out, gLobbyStr_Empty_16);
    LobbyString_FormatN(&s0, 3, gLobbyFmt_Hex_3, 0);
    LobbyString_Append(out, &s0);
    LobbyString_Destroy(&s0);
    LobbyString_AppendCStr(out, gLobbyStr_Space_2);
    LobbyString_FormatN(&s1, 2, gLobbyFmt_Hex_3, 6);
    LobbyString_Append(out, &s1);
    LobbyString_Destroy(&s1);
    LobbyString_AppendCStr(out, gLobbyStr_Space_2);
    switch (type) {
    case PPW_LOBBY_MESSAGE_FORMAT_STRING:
        LobbyString_AppendCStr(out, gLobbyStr_S);
        break;
    case PPW_LOBBY_MESSAGE_FORMAT_BINARY:
        LobbyString_AppendCStr(out, gLobbyStr_B);
        break;
    default:
        return FALSE;
    }
    LobbyString_AppendCStr(out, gLobbyStr_Space_2);
    switch (mode) {
    case PPW_LOBBY_MESSAGE_KIND_USER:
        LobbyString_AppendCStr(out, gLobbyStr_A);
        break;
    case PPW_LOBBY_MESSAGE_KIND_SYSTEM:
        LobbyString_AppendCStr(out, gLobbyStr_S);
        break;
    default:
        return FALSE;
    }
    LobbyString_AppendCStr(out, gLobbyStr_Space_2);
    LobbyString_FormatN(&s2, 8, gLobbyFmt_Hex_3, value);
    LobbyString_Append(out, &s2);
    LobbyString_Destroy(&s2);
    LobbyString_AppendCStr(out, gLobbyStr_Space_2);
    LobbyString_AppendCStr(out, gLobbyStr__);
    LobbyString_AppendCStr(out, gLobbyStr_SpaceSpace);
    switch (type) {
    case 0:
        LobbyString_FormatN(&s3, len, gLobbyFmt_Str_3, data);
        LobbyString_Append(out, &s3);
        LobbyString_Destroy(&s3);
        break;
    case 1:
        MI_CpuFill8(buf, 0, sizeof(buf));
        if (DWC_Base64Encode(data, len, buf, sizeof(buf)) == -1) {
            return FALSE;
        }
        LobbyString_AppendCStr(out, buf);
        break;
    default:
        return FALSE;
    }
    return TRUE;
}

void LobbyCharVector_PushBackSlow(LobbyCharVector *s, const char *c) {
    TouchTag();
    LobbyCharVector_RecommendSize(s, 1);
    LobbyCharVector_AppendFillSlow(s, 1, c);
}

void LobbyString_Append(Str *s, void *arg) {
    LobbyString_Replace(s, StrSize(s), 0, arg);
}

void LobbyString_AppendCStr(Str *s, const char *arg) {
    LobbyString_ReplaceCStr(s, StrSize(s), 0, arg);
}

void LobbyString_AssignCStr(Str *s, const char *arg) {
    LobbyString_ReplaceCStr(s, 0, StrSize(s), arg);
}

#pragma warn_uninitializedvar off
void LobbyString_ReplaceCStr(Str *s, u32 pos, u32 length, const char *str) {
    LobbyTag tag;
    LobbyString_ReplaceRange(s, pos, length, str, str + strlen(str), tag);
}

int LobbyString_CompareSubstring(const Str *s, u32 pos, u32 length, const Str *other) {
    u32 otherLength;
    const char *otherChars;
    if (StrIsShort(other)) {
        otherChars = other->s.buf;
        otherLength = other->s.len;
    } else {
        otherChars = other->l.ptr;
        otherLength = other->l.size;
    }
    return LobbyString_CompareChars(s, pos, length, otherChars, otherLength);
}
