// Port only (the DS build assembles lib/NitroDWC/asm/dwc_lobby_chat_data.s, which MWCC can't
// reproduce from C): the desktop lobby library's data, written by
//   python3 tools/s2c.py --verify -o <dir> lib/NitroDWC/asm/dwc_lobby_chat_data.s
// The stats upload objects of that file are in lib/port/stats_upload_data.c, which every target
// builds (src/stats_upload.c is game code).
//
// Converted from asm/dwc_lobby_chat_data.s by tools/s2c.py.

// The C declarations of these do not match the data (see the notes at each
// definition): keep them out of the way of the definitions below.
#define gLobbyStr_N                                                 gLobbyStr_N_header_decl
#define gLobbyStr_M                                                 gLobbyStr_M_header_decl
#define gLobbyStr_C                                                 gLobbyStr_C_header_decl
#define gLobbyStr_F2                                                gLobbyStr_F2_header_decl
#define gLobbyStr_F1                                                gLobbyStr_F1_header_decl
#define gLobbyStr_Invalid                                           gLobbyStr_Invalid_header_decl
#define gLobbyStr_R                                                 gLobbyStr_R_header_decl
#define gLobbyStr_T                                                 gLobbyStr_T_header_decl
#define gLobbyStr_D                                                 gLobbyStr_D_header_decl
#define gLobbyStr_D7                                                gLobbyStr_D7_header_decl
#define gLobbyStr_D8                                                gLobbyStr_D8_header_decl
#define gLobbyStr_D6                                                gLobbyStr_D6_header_decl
#define gLobbyStr_D9                                                gLobbyStr_D9_header_decl
#define gLobbyStr_D1                                                gLobbyStr_D1_header_decl
#define gLobbyStr_D2                                                gLobbyStr_D2_header_decl
#define gLobbyStr_D3                                                gLobbyStr_D3_header_decl
#define gLobbyStr_D4                                                gLobbyStr_D4_header_decl
#define gLobbyStr_D5                                                gLobbyStr_D5_header_decl
#define gPPWLobbyPlayersVtable                                      gPPWLobbyPlayersVtable_header_decl
#define ov45_02255200                                               ov45_02255200_header_decl
#define ov45_02255358                                               ov45_02255358_header_decl
#define gChatStr_ciAddCallback_                                     gChatStr_ciAddCallback__header_decl
#define gChatStr_ciCallCallback                                     gChatStr_ciCallCallback_header_decl
#define gChatStr_ciCallCallbacks                                    gChatStr_ciCallCallbacks_header_decl
#define gChatStr_ciFreeCallbackData                                 gChatStr_ciFreeCallbackData_header_decl
#define gChatStr_ciCleanupCallbacks                                 gChatStr_ciCleanupCallbacks_header_decl
#define gChatStr_ciGetCallbackIndexByID                             gChatStr_ciGetCallbackIndexByID_header_decl
#define gLobbyStr_DataNeNULL                                        gLobbyStr_DataNeNULL_header_decl
#define gLobbyStr_ChatCallbacksC                                    gLobbyStr_ChatCallbacksC_header_decl
#define gChatStr_DataTypeGe0                                        gChatStr_DataTypeGe0_header_decl
#define gChatStr_DataTypeLtCALLBACK_NUM                             gChatStr_DataTypeLtCALLBACK_NUM_header_decl
#define gChatStr_DataCallbackNeNULL                                 gChatStr_DataCallbackNeNULL_header_decl
#define gChatStr_DataCallbackParamsNeNULL                           gChatStr_DataCallbackParamsNeNULL_header_decl
#define gChatStr_DataID_Ge0                                         gChatStr_DataID_Ge0_header_decl
#define gChatStr_0_8                                                gChatStr_0_8_header_decl
#define gChatStr_ChatNeNULL                                         gChatStr_ChatNeNULL_header_decl
#define gChatStr_TypeGe0                                            gChatStr_TypeGe0_header_decl
#define gChatStr_TypeLtCALLBACK_NUM                                 gChatStr_TypeLtCALLBACK_NUM_header_decl
#define gChatStr_ConnectionCallbackListNeNULL                       gChatStr_ConnectionCallbackListNeNULL_header_decl
#define gChatStr_CallbackNeNULL_2                                   gChatStr_CallbackNeNULL_2_header_decl
#define gChatStr_CallbackParamsNeNULL                               gChatStr_CallbackParamsNeNULL_header_decl
#define gChatStr_CallbackParamsSizeGt0                              gChatStr_CallbackParamsSizeGt0_header_decl
#define gChatStr_ID_Ge0                                             gChatStr_ID_Ge0_header_decl
#define gChatStr_SrcParamsNumChannelsGe0                            gChatStr_SrcParamsNumChannelsGe0_header_decl
#define gChatStr_SrcParamsNumUsersNeNULL                            gChatStr_SrcParamsNumUsersNeNULL_header_decl
#define gChatStr_SrcParamsNumUsersGe0                               gChatStr_SrcParamsNumUsersGe0_header_decl
#define gChatStr_SrcParamsModesNeNULL                               gChatStr_SrcParamsModesNeNULL_header_decl
#define gChatStr_SrcParamsNumBansGe0                                gChatStr_SrcParamsNumBansGe0_header_decl
#define gChatStr_SrcParamsNumSuggestedNicksGe0                      gChatStr_SrcParamsNumSuggestedNicksGe0_header_decl
#define gChatStr_SrcParamsNumGe0                                    gChatStr_SrcParamsNumGe0_header_decl
#define gChatStr_ciInChannel                                        gChatStr_ciInChannel_header_decl
#define gChatStr_ciHashString                                       gChatStr_ciHashString_header_decl
#define gChatStr_ciChannelLeft                                      gChatStr_ciChannelLeft_header_decl
#define gChatStr_ciSetChannelMode                                   gChatStr_ciSetChannelMode_header_decl
#define gChatStr_ciChannelEntered                                   gChatStr_ciChannelEntered_header_decl
#define gChatStr_ciGetChannelMode                                   gChatStr_ciGetChannelMode_header_decl
#define gChatStr_ciUserChangedNick                                  gChatStr_ciUserChangedNick_header_decl
#define gChatStr_ciUserChangedMode                                  gChatStr_ciUserChangedMode_header_decl
#define gChatStr_ciUserLeftChannel                                  gChatStr_ciUserLeftChannel_header_decl
#define gChatStr_ciCleanupChannels                                  gChatStr_ciCleanupChannels_header_decl
#define gChatStr_ciUserTableHashFn                                  gChatStr_ciUserTableHashFn_header_decl
#define gChatStr_ciSetChannelTopic                                  gChatStr_ciSetChannelTopic_header_decl
#define gChatStr_ciChannelEntering                                  gChatStr_ciChannelEntering_header_decl
#define gChatStr_ciUserEnumChannels                                 gChatStr_ciUserEnumChannels_header_decl
#define gChatStr_ciSetUserBasicInfo                                 gChatStr_ciSetUserBasicInfo_header_decl
#define gChatStr_ciChannelListUsers                                 gChatStr_ciChannelListUsers_header_decl
#define gChatStr_ciUserChangeNickMap                                gChatStr_ciUserChangeNickMap_header_decl
#define gChatStr_ciIsEnteringChannel                                gChatStr_ciIsEnteringChannel_header_decl
#define gChatStr_ciUserTableCompareFn                               gChatStr_ciUserTableCompareFn_header_decl
#define gChatStr_ciSetChannelPassword                               gChatStr_ciSetChannelPassword_header_decl
#define gChatStr_ciJoinCallbackCalled                               gChatStr_ciJoinCallbackCalled_header_decl
#define gChatStr_ciChannelTableHashFn                               gChatStr_ciChannelTableHashFn_header_decl
#define gChatStr_ciGetChannelNumUsers                               gChatStr_ciGetChannelNumUsers_header_decl
#define gChatStr_ciUserEnteredChannel                               gChatStr_ciUserEnteredChannel_header_decl
#define gChatStr_ciGetChannelCallbacks                              gChatStr_ciGetChannelCallbacks_header_decl
#define gChatStr_ciChannelListUsersMap                              gChatStr_ciChannelListUsersMap_header_decl
#define gChatStr_ciSetUserBasicInfoMap                              gChatStr_ciSetUserBasicInfoMap_header_decl
#define gChatStr_ciUserEnumChannelsMap                              gChatStr_ciUserEnumChannelsMap_header_decl
#define gChatStr_ciWasJoinCallbackCalled                            gChatStr_ciWasJoinCallbackCalled_header_decl
#define gChatStr_ciChannelTableCompareFn                            gChatStr_ciChannelTableCompareFn_header_decl
#define gChatStr_ciUserTableElementFreeFn                           gChatStr_ciUserTableElementFreeFn_header_decl
#define gChatStr_ciChannelTableElementFreeFn                        gChatStr_ciChannelTableElementFreeFn_header_decl
#define gChatStr_StrNeNULL                                          gChatStr_StrNeNULL_header_decl
#define gChatStr_ChatChannelC                                       gChatStr_ChatChannelC_header_decl
#define gChatStr_Str0_Ne0                                           gChatStr_Str0_Ne0_header_decl
#define gChatStr_ElemNeNULL                                         gChatStr_ElemNeNULL_header_decl
#define gChatStr_NumBucketsGt0                                      gChatStr_NumBucketsGt0_header_decl
#define gChatStr_Elem1_NeNULL                                       gChatStr_Elem1_NeNULL_header_decl
#define gChatStr_Elem2_NeNULL                                       gChatStr_Elem2_NeNULL_header_decl
#define gChatStr_Str1_NeNULL                                        gChatStr_Str1_NeNULL_header_decl
#define gChatStr_Str2_NeNULL                                        gChatStr_Str2_NeNULL_header_decl
#define gChatStr_Str1_0_Ne0                                         gChatStr_Str1_0_Ne0_header_decl
#define gChatStr_Str2_0_Ne0                                         gChatStr_Str2_0_Ne0_header_decl
#define gChatStr_ChatNeNULL_2                                       gChatStr_ChatNeNULL_2_header_decl
#define gChatStr_chatChannel                                        gChatStr_chatChannel_header_decl
#define gChatStr_ChannelNeNULL                                      gChatStr_ChannelNeNULL_header_decl
#define gChatStr_Channel0_Ne0                                       gChatStr_Channel0_Ne0_header_decl
#define gChatStr_StrlenChannelLtMAX_CHANNEL                         gChatStr_StrlenChannelLtMAX_CHANNEL_header_decl
#define gChatStr_CallbacksNeNULL                                    gChatStr_CallbacksNeNULL_header_decl
#define gChatStr_Empty_19                                           gChatStr_Empty_19_header_decl
#define gChatStr_ClientDataNeNULL                                   gChatStr_ClientDataNeNULL_header_decl
#define gChatStr_UserNameNeNULL                                     gChatStr_UserNameNeNULL_header_decl
#define gChatStr_UserName0_Ne0                                      gChatStr_UserName0_Ne0_header_decl
#define gChatStr_StrlenUserNameLtMAX_NAME                           gChatStr_StrlenUserNameLtMAX_NAME_header_decl
#define gChatStr_DataNumUsersGe0                                    gChatStr_DataNumUsersGe0_header_decl
#define gChatStr_0_9                                                gChatStr_0_9_header_decl
#define gChatStr_CallbackNeNULL_3                                   gChatStr_CallbackNeNULL_3_header_decl
#define gChatStr_NameNeNULL                                         gChatStr_NameNeNULL_header_decl
#define gChatStr_Name0_Ne0                                          gChatStr_Name0_Ne0_header_decl
#define gChatStr_StrlenNameLtMAX_NAME                               gChatStr_StrlenNameLtMAX_NAME_header_decl
#define gChatStr_ModeGe0_AndModeLe3                                 gChatStr_ModeGe0_AndModeLe3_header_decl
#define gChatStr_TableLookupChatChannelUsersChatUserNeNULL          gChatStr_TableLookupChatChannelUsersChatUserNeNULL_header_decl
#define gChatStr_UserNeNULL                                         gChatStr_UserNeNULL_header_decl
#define gChatStr_User0_Ne0                                          gChatStr_User0_Ne0_header_decl
#define gChatStr_StrlenUserLtMAX_NAME                               gChatStr_StrlenUserLtMAX_NAME_header_decl
#define gChatStr_ChannelUsersNeNULL                                 gChatStr_ChannelUsersNeNULL_header_decl
#define gChatStr_DataUserNeNULL                                     gChatStr_DataUserNeNULL_header_decl
#define gChatStr_DataUserName0_Ne0                                  gChatStr_DataUserName0_Ne0_header_decl
#define gChatStr_DataCallbackNeNULL_2                               gChatStr_DataCallbackNeNULL_2_header_decl
#define gChatStr_DataNewNickNeNULL                                  gChatStr_DataNewNickNeNULL_header_decl
#define gChatStr_DataNewNick0_Ne0                                   gChatStr_DataNewNick0_Ne0_header_decl
#define gChatStr_StrlenDataNewNickLtMAX_NAME                        gChatStr_StrlenDataNewNickLtMAX_NAME_header_decl
#define gChatStr_DataOldNickNeNULL                                  gChatStr_DataOldNickNeNULL_header_decl
#define gChatStr_DataOldNick0_Ne0                                   gChatStr_DataOldNick0_Ne0_header_decl
#define gChatStr_StrlenDataOldNickLtMAX_NAME                        gChatStr_StrlenDataOldNickLtMAX_NAME_header_decl
#define gChatStr_RcodeNe0                                           gChatStr_RcodeNe0_header_decl
#define gChatStr_OldNickNeNULL                                      gChatStr_OldNickNeNULL_header_decl
#define gChatStr_OldNick0_Ne0                                       gChatStr_OldNick0_Ne0_header_decl
#define gChatStr_StrlenOldNickLtMAX_NAME                            gChatStr_StrlenOldNickLtMAX_NAME_header_decl
#define gChatStr_NewNickNeNULL                                      gChatStr_NewNickNeNULL_header_decl
#define gChatStr_NewNick0_Ne0                                       gChatStr_NewNick0_Ne0_header_decl
#define gChatStr_StrlenNewNickLtMAX_NAME                            gChatStr_StrlenNewNickLtMAX_NAME_header_decl
#define gChatStr_NickNeNULL                                         gChatStr_NickNeNULL_header_decl
#define gChatStr_Nick0_Ne0                                          gChatStr_Nick0_Ne0_header_decl
#define gChatStr_StrlenNickLtMAX_NAME                               gChatStr_StrlenNickLtMAX_NAME_header_decl
#define ciNumServerMessageHandlers                                  ciNumServerMessageHandlers_header_decl
#define gChatStr_ciGetNextID                                        gChatStr_ciGetNextID_header_decl
#define gChatStr_ciAddFilter                                        gChatStr_ciAddFilter_header_decl
#define gChatStr_ciParseMode                                        gChatStr_ciParseMode_header_decl
#define gChatStr_ciParseValue                                       gChatStr_ciParseValue_header_decl
#define gChatStr_ciUTMHandler                                       gChatStr_ciUTMHandler_header_decl
#define gChatStr_ciATMHandler                                       gChatStr_ciATMHandler_header_decl
#define gChatStr_ciFindFilter                                       gChatStr_ciFindFilter_header_decl
#define gChatStr_ciFilterThink                                      gChatStr_ciFilterThink_header_decl
#define gChatStr_ciPingHandler                                      gChatStr_ciPingHandler_header_decl
#define gChatStr_ciNickHandler                                      gChatStr_ciNickHandler_header_decl
#define gChatStr_ciJoinHandler                                      gChatStr_ciJoinHandler_header_decl
#define gChatStr_ciPartHandler                                      gChatStr_ciPartHandler_header_decl
#define gChatStr_ciKickHandler                                      gChatStr_ciKickHandler_header_decl
#define gChatStr_ciQuitHandler                                      gChatStr_ciQuitHandler_header_decl
#define gChatStr_ciKillHandler                                      gChatStr_ciKillHandler_header_decl
#define gChatStr_ciModeHandler                                      gChatStr_ciModeHandler_header_decl
#define gChatStr_ciTopicHandler                                     gChatStr_ciTopicHandler_header_decl
#define gChatStr_ciErrorHandler                                     gChatStr_ciErrorHandler_header_decl
#define gChatStr_ciRemoveFilter                                     gChatStr_ciRemoveFilter_header_decl
#define gChatStr_ciFinishFilter                                     gChatStr_ciFinishFilter_header_decl
#define gChatStr_ciAddJOINFilter                                    gChatStr_ciAddJOINFilter_header_decl
#define gChatStr_ciNoticeHandler                                    gChatStr_ciNoticeHandler_header_decl
#define gChatStr_ciInviteHandler                                    gChatStr_ciInviteHandler_header_decl
#define gChatStr_ciDestroyFilter                                    gChatStr_ciDestroyFilter_header_decl
#define gChatStr_ciCleanupFilters                                   gChatStr_ciCleanupFilters_header_decl
#define gChatStr_ciPrivmsgHandler                                   gChatStr_ciPrivmsgHandler_header_decl
#define gChatStr_ciRplListHandler                                   gChatStr_ciRplListHandler_header_decl
#define gChatStr_ciFilterTimedout                                   gChatStr_ciFilterTimedout_header_decl
#define gChatStr_ciRplCDKeyHandler                                  gChatStr_ciRplCDKeyHandler_header_decl
#define gChatStr_ciRplLoginHandler                                  gChatStr_ciRplLoginHandler_header_decl
#define gChatStr_ciRplTopicHandler                                  gChatStr_ciRplTopicHandler_header_decl
#define gChatStr_ciRplGetKeyHandler                                 gChatStr_ciRplGetKeyHandler_header_decl
#define gChatStr_ciRplUserIPHandler                                 gChatStr_ciRplUserIPHandler_header_decl
#define gChatStr_ciNameReplyHandler                                 gChatStr_ciNameReplyHandler_header_decl
#define gChatStr_ciFindGetKeyFilter                                 gChatStr_ciFindGetKeyFilter_header_decl
#define gChatStr_ciCheckFiltersForID                                gChatStr_ciCheckFiltersForID_header_decl
#define gChatStr_ciRplGetCKeyHandler                                gChatStr_ciRplGetCKeyHandler_header_decl
#define gChatStr_ciEndOfNamesHandler                                gChatStr_ciEndOfNamesHandler_header_decl
#define gChatStr_ciRplBanListHandler                                gChatStr_ciRplBanListHandler_header_decl
#define gChatStr_ciRplNoTopicHandler                                gChatStr_ciRplNoTopicHandler_header_decl
#define gChatStr_ciRplWelcomeHandler                                gChatStr_ciRplWelcomeHandler_header_decl
#define gChatStr_ciApplyChangesToMode                               gChatStr_ciApplyChangesToMode_header_decl
#define gChatStr_ciRplWhoReplyHandler                               gChatStr_ciRplWhoReplyHandler_header_decl
#define gChatStr_ciRplEndOfWhoHandler                               gChatStr_ciRplEndOfWhoHandler_header_decl
#define gChatStr_ciRplSecureKeyHandler                              gChatStr_ciRplSecureKeyHandler_header_decl
#define gChatStr_ciRplEndGetKeyHandler                              gChatStr_ciRplEndGetKeyHandler_header_decl
#define gChatStr_ciRplListStartHandler                              gChatStr_ciRplListStartHandler_header_decl
#define gChatStr_ciRplWhoisUserHandler                              gChatStr_ciRplWhoisUserHandler_header_decl
#define gChatStr_ciErrNickInUseHandler                              gChatStr_ciErrNickInUseHandler_header_decl
#define gChatStr_ciRplEndGetCKeyHandler                             gChatStr_ciRplEndGetCKeyHandler_header_decl
#define gChatStr_ciRplGetChanKeyHandler                             gChatStr_ciRplGetChanKeyHandler_header_decl
#define gChatStr_ciRplEndOfWhoisHandler                             gChatStr_ciRplEndOfWhoisHandler_header_decl
#define gChatStr_ciErrBadChanMaskHandler                            gChatStr_ciErrBadChanMaskHandler_header_decl
#define gChatStr_ciErrLoginFailedHandler                            gChatStr_ciErrLoginFailedHandler_header_decl
#define gChatStr_ciErrNoUniqueNickHandler                           gChatStr_ciErrNoUniqueNickHandler_header_decl
#define gChatStr_ciRplEndOfBanListHandler                           gChatStr_ciRplEndOfBanListHandler_header_decl
#define gChatStr_ciErrBadChannelKeyHandler                          gChatStr_ciErrBadChannelKeyHandler_header_decl
#define gChatStr_ciErrNoSuchChannelHandler                          gChatStr_ciErrNoSuchChannelHandler_header_decl
#define gChatStr_ciRplChannelModeIsHandler                          gChatStr_ciRplChannelModeIsHandler_header_decl
#define gChatStr_ciRplWhoisChannelsHandler                          gChatStr_ciRplWhoisChannelsHandler_header_decl
#define gChatStr_ciErrChannelIsFullHandler                          gChatStr_ciErrChannelIsFullHandler_header_decl
#define gChatStr_ciQuitEnumChannelsCallback                         gChatStr_ciQuitEnumChannelsCallback_header_decl
#define gChatStr_ciKillEnumChannelsCallback                         gChatStr_ciKillEnumChannelsCallback_header_decl
#define gChatStr_ciErrInviteOnlyChanHandler                         gChatStr_ciErrInviteOnlyChanHandler_header_decl
#define gChatStr_ciErrBannedFromChanHandler                         gChatStr_ciErrBannedFromChanHandler_header_decl
#define gChatStr_ciErrTooManyChannelsHandler                        gChatStr_ciErrTooManyChannelsHandler_header_decl
#define gChatStr_ciErrErroneusNicknameHandler                       gChatStr_ciErrErroneusNicknameHandler_header_decl
#define gChatStr_ciErrUniqueNickExpiredHandler                      gChatStr_ciErrUniqueNickExpiredHandler_header_decl
#define gChatStr_ciErrRegisterNickFailedHandler                     gChatStr_ciErrRegisterNickFailedHandler_header_decl
#define ciServerMessageHandlers                                     ciServerMessageHandlers_header_decl
#define gChatStr_ChatNeNULL_3                                       gChatStr_ChatNeNULL_3_header_decl
#define gChatStr_ChatHandlersC                                      gChatStr_ChatHandlersC_header_decl
#define gChatStr_NumMatchesGt0                                      gChatStr_NumMatchesGt0_header_decl
#define gChatStr_matches                                            gChatStr_matches_header_decl
#define gChatStr_MatchesI_TypeGe0_AndMatchesI_TypeLtNUM_TYPES       gChatStr_MatchesI_TypeGe0_AndMatchesI_TypeLtNUM_TYPES_header_decl
#define gChatStr_channel                                            gChatStr_channel_header_decl
#define gChatStr_Channel0                                           gChatStr_Channel0_header_decl
#define gChatStr_FilterNeNULL                                       gChatStr_FilterNeNULL_header_decl
#define gChatStr_filter                                             gChatStr_filter_header_decl
#define gChatStr_FilterTypeGe0_AndFilterTypeLtNUM_TYPES             gChatStr_FilterTypeGe0_AndFilterTypeLtNUM_TYPES_header_decl
#define gChatStr_0_10                                               gChatStr_0_10_header_decl
#define gChatStr_TimedOut                                           gChatStr_TimedOut_header_decl
#define gChatStr_ID_Gt0                                             gChatStr_ID_Gt0_header_decl
#define gChatStr_PasswordNeNULL                                     gChatStr_PasswordNeNULL_header_decl
#define gChatStr_StrlenPasswordLtMAX_PASSWORD                       gChatStr_StrlenPasswordLtMAX_PASSWORD_header_decl
#define gChatStr_B_UnderscoreStar                                   gChatStr_B_UnderscoreStar_header_decl
#define gChatStr_ModeNeNULL                                         gChatStr_ModeNeNULL_header_decl
#define gChatStr_MessageNumParamsEq2                                gChatStr_MessageNumParamsEq2_header_decl
#define gChatStr_Empty_20                                           gChatStr_Empty_20_header_decl
#define gChatStr_ACTION                                             gChatStr_ACTION_header_decl
#define gChatFmt_PONG                                               gChatFmt_PONG_header_decl
#define gChatStr_MessageNumParamsEq1                                gChatStr_MessageNumParamsEq1_header_decl
#define gChatStr_StrlenNewNickLtMAX_NICK                            gChatStr_StrlenNewNickLtMAX_NICK_header_decl
#define gChatStr_NickNe0                                            gChatStr_NickNe0_header_decl
#define gChatFmt_MODE                                               gChatFmt_MODE_header_decl
#define gChatStr_MessageNumParamsEq2_OrMessageNumParamsEq3          gChatStr_MessageNumParamsEq2_OrMessageNumParamsEq3_header_decl
#define gChatStr_UserNeNULL_2                                       gChatStr_UserNeNULL_2_header_decl
#define gChatStr_User0_Ne0_2                                        gChatStr_User0_Ne0_2_header_decl
#define gChatStr_ChannelNeNULL_2                                    gChatStr_ChannelNeNULL_2_header_decl
#define gChatStr_Channel0_Ne0_2                                     gChatStr_Channel0_Ne0_2_header_decl
#define gChatStr_ReasonNeNULL                                       gChatStr_ReasonNeNULL_header_decl
#define gChatStr_MessageNumParamsGe2                                gChatStr_MessageNumParamsGe2_header_decl
#define gChatStr_MessageNumParamsEq4                                gChatStr_MessageNumParamsEq4_header_decl
#define gChatStr_Space_3                                            gChatStr_Space_3_header_decl
#define gChatStr_Nick0_Ne0_2                                        gChatStr_Nick0_Ne0_2_header_decl
#define gChatStr_Nick1_Ne0                                          gChatStr_Nick1_Ne0_header_decl
#define gChatStr_MessageNumParamsEq3                                gChatStr_MessageNumParamsEq3_header_decl
#define gChatStr_Star_2                                             gChatStr_Star_2_header_decl
#define gChatStr_ConnectionConnecting                               gChatStr_ConnectionConnecting_header_decl
#define gChatStr_MessageNumParamsEq8                                gChatStr_MessageNumParamsEq8_header_decl
#define gChatStr_flags                                              gChatStr_flags_header_decl
#define gChatStr_len                                                gChatStr_len_header_decl
#define gChatStr_MessageNumParamsEq5                                gChatStr_MessageNumParamsEq5_header_decl
#define gChatStr_BCAST                                              gChatStr_BCAST_header_decl
#define gChatStr_b_                                                 gChatStr_b__header_decl
#define gChatStr_MessageNumParamsGe1                                gChatStr_MessageNumParamsGe1_header_decl
#define gChatStr_DataNeNULL_2                                       gChatStr_DataNeNULL_2_header_decl
#define gChatStr_MessageNumParamsGe3                                gChatStr_MessageNumParamsGe3_header_decl
#define gChatStr_MessageNumParamsEq6                                gChatStr_MessageNumParamsEq6_header_decl
#define gChatStr_DataChannelNeNULL                                  gChatStr_DataChannelNeNULL_header_decl
#define gChatStr_DataChannel0_Ne0                                   gChatStr_DataChannel0_Ne0_header_decl
#define gChatFmt_MODE_B                                             gChatFmt_MODE_B_header_decl
#define gChatStr_MessageNumParamsGe3_2                              gChatStr_MessageNumParamsGe3_2_header_decl
#define gChatStr_DataNumBansGe0                                     gChatStr_DataNumBansGe0_header_decl
#define gChatStr_USRIP                                              gChatStr_USRIP_header_decl
#define gChatStr_Backslash_2                                        gChatStr_Backslash_2_header_decl
#define gChatCryptVersion                                           gChatCryptVersion_header_decl
#define gChatStr_ciThink                                            gChatStr_ciThink_header_decl
#define gChatStr_ciSendNick                                         gChatStr_ciSendNick_header_decl
#define gChatStr_ciSendUser                                         gChatStr_ciSendUser_header_decl
#define gChatStr_ciNickError                                        gChatStr_ciNickError_header_decl
#define gChatStr_ciSendLogin                                        gChatStr_ciSendLogin_header_decl
#define gChatStr_chatInChannelA                                     gChatStr_chatInChannelA_header_decl
#define gChatStr_chatDisconnect                                     gChatStr_chatDisconnect_header_decl
#define gChatStr_chatEnumUsersA                                     gChatStr_chatEnumUsersA_header_decl
#define gChatStr_chatConnectDoit                                    gChatStr_chatConnectDoit_header_decl
#define gChatStr_chatEnumChannelsA                                  gChatStr_chatEnumChannelsA_header_decl
#define gChatStr_chatEnterChannelA                                  gChatStr_chatEnterChannelA_header_decl
#define gChatStr_chatLeaveChannelA                                  gChatStr_chatLeaveChannelA_header_decl
#define gChatStr_ciHandleDisconnect                                 gChatStr_ciHandleDisconnect_header_decl
#define gChatStr_chatRetryWithNickA                                 gChatStr_chatRetryWithNickA_header_decl
#define gChatStr_ciSendGetChannelKey                                gChatStr_ciSendGetChannelKey_header_decl
#define gChatStr_ciEnumUsersCallback                                gChatStr_ciEnumUsersCallback_header_decl
#define gChatStr_chatGetChannelKeysA                                gChatStr_chatGetChannelKeysA_header_decl
#define gChatStr_chatSetChannelKeysA                                gChatStr_chatSetChannelKeysA_header_decl
#define gChatStr_chatSetChannelModeA                                gChatStr_chatSetChannelModeA_header_decl
#define gChatStr_chatGetChannelModeA                                gChatStr_chatGetChannelModeA_header_decl
#define gChatStr_chatSetChannelLimitA                               gChatStr_chatSetChannelLimitA_header_decl
#define gChatStr_chatSendUserMessageA                               gChatStr_chatSendUserMessageA_header_decl
#define gChatStr_ciProcessServerMessage                             gChatStr_ciProcessServerMessage_header_decl
#define gChatStr_chatRegisterUniqueNickA                            gChatStr_chatRegisterUniqueNickA_header_decl
#define gChatStr_chatGetChannelNumUsersA                            gChatStr_chatGetChannelNumUsersA_header_decl
#define gChatStr_chatSendChannelMessageA                            gChatStr_chatSendChannelMessageA_header_decl
#define gChatStr_MessageNeNULL_2                                    gChatStr_MessageNeNULL_2_header_decl
#define gChatStr_ChatMainC                                          gChatStr_ChatMainC_header_decl
#define gChatStr_ChatNeNULL_4                                       gChatStr_ChatNeNULL_4_header_decl
#define gChatStr_Disconnected                                       gChatStr_Disconnected_header_decl
#define gChatStr_Star_3                                             gChatStr_Star_3_header_decl
#define gChatFmt_NICK                                               gChatFmt_NICK_header_decl
#define gChatFmt_USER                                               gChatFmt_USER_header_decl
#define gChatStr_127_Dot0_Dot0_Dot1                                 gChatStr_127_Dot0_Dot0_Dot1_header_decl
#define gChatFmt_LOGINPREAUTH                                       gChatFmt_LOGINPREAUTH_header_decl
#define gChatFmt_LOGIN                                              gChatFmt_LOGIN_header_decl
#define gChatFmt_LOGIN_2                                            gChatFmt_LOGIN_2_header_decl
#define gChatStr_0_11                                               gChatStr_0_11_header_decl
#define gChatStr_Empty_21                                           gChatStr_Empty_21_header_decl
#define gChatStr_ServerAddressNeNULL                                gChatStr_ServerAddressNeNULL_header_decl
#define gChatStr_CallbacksNeNULL_2                                  gChatStr_CallbacksNeNULL_2_header_decl
#define gChatStr_ConnectCallbackNeNULL                              gChatStr_ConnectCallbackNeNULL_header_decl
#define gChatStr_NickNeNULL_2                                       gChatStr_NickNeNULL_2_header_decl
#define gChatStr_Nick0_Ne0_3                                        gChatStr_Nick0_Ne0_3_header_decl
#define gChatStr_StrlenNickLtMAX_NICK                               gChatStr_StrlenNickLtMAX_NICK_header_decl
#define gChatStr_NamespaceID_Gt0                                    gChatStr_NamespaceID_Gt0_header_decl
#define gChatStr_UniquenickAndUniquenick0                           gChatStr_UniquenickAndUniquenick0_header_decl
#define gChatStr_PasswordAndPassword0                               gChatStr_PasswordAndPassword0_header_decl
#define gChatStr_NamespaceID_Ge0                                    gChatStr_NamespaceID_Ge0_header_decl
#define gChatStr_EmailAndEmail0                                     gChatStr_EmailAndEmail0_header_decl
#define gChatStr_ProfilenickAndProfilenick0                         gChatStr_ProfilenickAndProfilenick0_header_decl
#define gChatStr_AuthtokenAndAuthtoken0                             gChatStr_AuthtokenAndAuthtoken0_header_decl
#define gChatStr_PartnerchallengeAndPartnerchallenge0               gChatStr_PartnerchallengeAndPartnerchallenge0_header_decl
#define gChatStr_preauth                                            gChatStr_preauth_header_decl
#define gChatStr_GamenameAndGamename0                               gChatStr_GamenameAndGamename0_header_decl
#define gChatStr_SecretKeyAndSecretKey0                             gChatStr_SecretKeyAndSecretKey0_header_decl
#define gChatFmt_CRYPT_Des                                          gChatFmt_CRYPT_Des_header_decl
#define gChatStr_USRIP_2                                            gChatStr_USRIP_2_header_decl
#define gChatFmt_NICK_2                                             gChatFmt_NICK_2_header_decl
#define gChatFmt_REGISTERNICK                                       gChatFmt_REGISTERNICK_header_decl
#define gChatStr_QUIT_Later                                         gChatStr_QUIT_Later_header_decl
#define gChatStr_ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuv_3 gChatStr_ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuv_3_header_decl
#define gChatStr_CallbackAllNeNULL_OrCallbackEachNeNULL             gChatStr_CallbackAllNeNULL_OrCallbackEachNeNULL_header_decl
#define gChatFmt_LIST                                               gChatFmt_LIST_header_decl
#define gChatStr_ChannelNeNULL_3                                    gChatStr_ChannelNeNULL_3_header_decl
#define gChatStr_Channel0_Ne0_3                                     gChatStr_Channel0_Ne0_3_header_decl
#define gChatFmt_JOIN                                               gChatFmt_JOIN_header_decl
#define gChatFmt_PART                                               gChatFmt_PART_header_decl
#define gChatStr_TypeEqCHAT_MESSAGE_OrTypeEqCHAT_ACTION_OrTypeEq    gChatStr_TypeEqCHAT_MESSAGE_OrTypeEqCHAT_ACTION_OrTypeEq_header_decl
#define gChatFmt_PRIVMSG                                            gChatFmt_PRIVMSG_header_decl
#define gChatFmt_PRIVMSG_ACTION                                     gChatFmt_PRIVMSG_ACTION_header_decl
#define gChatFmt_NOTICE                                             gChatFmt_NOTICE_header_decl
#define gChatFmt_UTM                                                gChatFmt_UTM_header_decl
#define gChatFmt_ATM                                                gChatFmt_ATM_header_decl
#define gChatStr_CallbackNeNULL_4                                   gChatStr_CallbackNeNULL_4_header_decl
#define gChatStr_ModeNeNULL_2                                       gChatStr_ModeNeNULL_2_header_decl
#define gChatStr_XiXpXsXmXnXtXlXe                                   gChatStr_XiXpXsXmXnXtXlXe_header_decl
#define gChatFmt_SpaceInt                                           gChatFmt_SpaceInt_header_decl
#define gChatFmt_MODE_2                                             gChatFmt_MODE_2_header_decl
#define gChatFmt_MODE_3                                             gChatFmt_MODE_3_header_decl
#define gChatStr_LimitGe0                                           gChatStr_LimitGe0_header_decl
#define gChatFmt_MODE_L                                             gChatFmt_MODE_L_header_decl
#define gChatFmt_MODE_L_2                                           gChatFmt_MODE_L_2_header_decl
#define gChatStr_NumUsersGe0                                        gChatStr_NumUsersGe0_header_decl
#define gChatStr_ParamNeNULL                                        gChatStr_ParamNeNULL_header_decl
#define gChatStr_DataCallbackNeNULL_3                               gChatStr_DataCallbackNeNULL_3_header_decl
#define gChatFmt_NAMES                                              gChatFmt_NAMES_header_decl
#define gChatStr_UserNeNULL_3                                       gChatStr_UserNeNULL_3_header_decl
#define gChatStr_User0_Ne0_3                                        gChatStr_User0_Ne0_3_header_decl
#define gChatStr_StrlenUserLtMAX_USER                               gChatStr_StrlenUserLtMAX_USER_header_decl
#define gChatFmt_BackslashStrBackslashStr                           gChatFmt_BackslashStrBackslashStr_header_decl
#define gChatFmt_Int_6                                              gChatFmt_Int_6_header_decl
#define gChatStr_CookieAndCookie0                                   gChatStr_CookieAndCookie0_header_decl
#define gChatStr_NumGe0                                             gChatStr_NumGe0_header_decl
#define gChatFmt_SETCHANKEY                                         gChatFmt_SETCHANKEY_header_decl
#define gChatFmt_SETCKEY                                            gChatFmt_SETCKEY_header_decl
#define gChatStr_ChannelAndChannel0                                 gChatStr_ChannelAndChannel0_header_decl
#define gChatStr_NotNumOrKeys                                       gChatStr_NotNumOrKeys_header_decl
#define gChatFmt_GETCHANKEY_0                                       gChatFmt_GETCHANKEY_0_header_decl
#define gChatFmt_GETCKEY_0                                          gChatFmt_GETCKEY_0_header_decl
#define gChatStr_B_UnderscoreStar_2                                 gChatStr_B_UnderscoreStar_2_header_decl
#define gChatStr_ciParseUser                                        gChatStr_ciParseUser_header_decl
#define gChatStr_ciSocketSend                                       gChatStr_ciSocketSend_header_decl
#define gChatStr_ciSocketRecv                                       gChatStr_ciSocketRecv_header_decl
#define gChatStr_ciBufferInit                                       gChatStr_ciBufferInit_header_decl
#define gChatStr_ciParseParam                                       gChatStr_ciParseParam_header_decl
#define gChatStr_ciSocketInit                                       gChatStr_ciSocketInit_header_decl
#define gChatStr_ciSocketSendf                                      gChatStr_ciSocketSendf_header_decl
#define gChatStr_ciSocketThink                                      gChatStr_ciSocketThink_header_decl
#define gChatStr_ciParseMessage                                     gChatStr_ciParseMessage_header_decl
#define gChatStr_ciSocketConnect                                    gChatStr_ciSocketConnect_header_decl
#define gChatStr_ciBufferPreAppend                                  gChatStr_ciBufferPreAppend_header_decl
#define gChatStr_ciBufferClipFront                                  gChatStr_ciBufferClipFront_header_decl
#define gChatStr_ciSocketThinkSend                                  gChatStr_ciSocketThinkSend_header_decl
#define gChatStr_ciSocketThinkRecv                                  gChatStr_ciSocketThinkRecv_header_decl
#define gChatStr_ciSocketDisconnect                                 gChatStr_ciSocketDisconnect_header_decl
#define gChatStr_BufferNeNULL_2                                     gChatStr_BufferNeNULL_2_header_decl
#define gChatStr_ChatSocketC                                        gChatStr_ChatSocketC_header_decl
#define gChatStr_BufferNeNULL_3                                     gChatStr_BufferNeNULL_3_header_decl
#define gChatStr_BufferSizeGe0                                      gChatStr_BufferSizeGe0_header_decl
#define gChatStr_BufferSizeBUFFER_INC_Eq0                           gChatStr_BufferSizeBUFFER_INC_Eq0_header_decl
#define gChatStr_BufferLengthGe0                                    gChatStr_BufferLengthGe0_header_decl
#define gChatStr_BufferLengthLeBufferSize                           gChatStr_BufferLengthLeBufferSize_header_decl
#define gChatStr_LenGe0_2                                           gChatStr_LenGe0_2_header_decl
#define gChatStr_LenLeSHRT_MAX                                      gChatStr_LenLeSHRT_MAX_header_decl
#define gChatStr_LenLeBufferLength                                  gChatStr_LenLeBufferLength_header_decl
#define gChatStr_SockNeNULL                                         gChatStr_SockNeNULL_header_decl
#define gChatStr_SockNeNULL_2                                       gChatStr_SockNeNULL_2_header_decl
#define gChatStr_SockConnectStateEqCiNotConnectedOrSock             gChatStr_SockConnectStateEqCiNotConnectedOrSock_header_decl
#define gChatStr_SockInputQueueNeNULL                               gChatStr_SockInputQueueNeNULL_header_decl
#define gChatStr_SockInputQueueSizeGe0                              gChatStr_SockInputQueueSizeGe0_header_decl
#define gChatStr_SockInputQueueSizeBUFFER_INC_Eq0                   gChatStr_SockInputQueueSizeBUFFER_INC_Eq0_header_decl
#define gChatStr_SockInputQueueLengthGe0                            gChatStr_SockInputQueueLengthGe0_header_decl
#define gChatStr_SockInputQueueLengthLeSockInputQueueSize           gChatStr_SockInputQueueLengthLeSockInputQueueSize_header_decl
#define gChatStr_SockOutputQueueNeNULL                              gChatStr_SockOutputQueueNeNULL_header_decl
#define gChatStr_SockOutputQueueSizeGe0                             gChatStr_SockOutputQueueSizeGe0_header_decl
#define gChatStr_SockOutputQueueSizeBUFFER_INC_Eq0                  gChatStr_SockOutputQueueSizeBUFFER_INC_Eq0_header_decl
#define gChatStr_SockOutputQueueLengthGe0                           gChatStr_SockOutputQueueLengthGe0_header_decl
#define gChatStr_SockOutputQueueLengthLeSockOutputQueueSize         gChatStr_SockOutputQueueLengthLeSockOutputQueueSize_header_decl
#define gChatStr_ServerAddressNeNULL_2                              gChatStr_ServerAddressNeNULL_2_header_decl
#define gChatStr_PortGe0                                            gChatStr_PortGe0_header_decl
#define gChatStr_PortLeUSHRT_MAX                                    gChatStr_PortLeUSHRT_MAX_header_decl
#define gChatStr_SockConnectStateEqCiNotConnected                   gChatStr_SockConnectStateEqCiNotConnected_header_decl
#define gChatStr_SockConnectStateEqCiConnected                      gChatStr_SockConnectStateEqCiConnected_header_decl
#define gChatStr_0_12                                               gChatStr_0_12_header_decl
#define gChatStr_PTextNeNULL                                        gChatStr_PTextNeNULL_header_decl
#define gChatStr_MessageNeNULL_3                                    gChatStr_MessageNeNULL_3_header_decl
#define gChatStr_SpaceColon_2                                       gChatStr_SpaceColon_2_header_decl
#define gChatStr_Space_4                                            gChatStr_Space_4_header_decl

#include "global.h"

#include "lobby_chat_internal.h"
#include "lobby_chat_request.h"
#include "lobby_event_deque.h"
#include "lobby_tree.h"
#include "ppw_lobby_internal.h"

#pragma force_active on

#undef gLobbyStr_N
#undef gLobbyStr_M
#undef gLobbyStr_C
#undef gLobbyStr_F2
#undef gLobbyStr_F1
#undef gLobbyStr_Invalid
#undef gLobbyStr_R
#undef gLobbyStr_T
#undef gLobbyStr_D
#undef gLobbyStr_D7
#undef gLobbyStr_D8
#undef gLobbyStr_D6
#undef gLobbyStr_D9
#undef gLobbyStr_D1
#undef gLobbyStr_D2
#undef gLobbyStr_D3
#undef gLobbyStr_D4
#undef gLobbyStr_D5
#undef gPPWLobbyPlayersVtable
#undef ov45_02255200
#undef ov45_02255358
#undef gChatStr_ciAddCallback_
#undef gChatStr_ciCallCallback
#undef gChatStr_ciCallCallbacks
#undef gChatStr_ciFreeCallbackData
#undef gChatStr_ciCleanupCallbacks
#undef gChatStr_ciGetCallbackIndexByID
#undef gLobbyStr_DataNeNULL
#undef gLobbyStr_ChatCallbacksC
#undef gChatStr_DataTypeGe0
#undef gChatStr_DataTypeLtCALLBACK_NUM
#undef gChatStr_DataCallbackNeNULL
#undef gChatStr_DataCallbackParamsNeNULL
#undef gChatStr_DataID_Ge0
#undef gChatStr_0_8
#undef gChatStr_ChatNeNULL
#undef gChatStr_TypeGe0
#undef gChatStr_TypeLtCALLBACK_NUM
#undef gChatStr_ConnectionCallbackListNeNULL
#undef gChatStr_CallbackNeNULL_2
#undef gChatStr_CallbackParamsNeNULL
#undef gChatStr_CallbackParamsSizeGt0
#undef gChatStr_ID_Ge0
#undef gChatStr_SrcParamsNumChannelsGe0
#undef gChatStr_SrcParamsNumUsersNeNULL
#undef gChatStr_SrcParamsNumUsersGe0
#undef gChatStr_SrcParamsModesNeNULL
#undef gChatStr_SrcParamsNumBansGe0
#undef gChatStr_SrcParamsNumSuggestedNicksGe0
#undef gChatStr_SrcParamsNumGe0
#undef gChatStr_ciInChannel
#undef gChatStr_ciHashString
#undef gChatStr_ciChannelLeft
#undef gChatStr_ciSetChannelMode
#undef gChatStr_ciChannelEntered
#undef gChatStr_ciGetChannelMode
#undef gChatStr_ciUserChangedNick
#undef gChatStr_ciUserChangedMode
#undef gChatStr_ciUserLeftChannel
#undef gChatStr_ciCleanupChannels
#undef gChatStr_ciUserTableHashFn
#undef gChatStr_ciSetChannelTopic
#undef gChatStr_ciChannelEntering
#undef gChatStr_ciUserEnumChannels
#undef gChatStr_ciSetUserBasicInfo
#undef gChatStr_ciChannelListUsers
#undef gChatStr_ciUserChangeNickMap
#undef gChatStr_ciIsEnteringChannel
#undef gChatStr_ciUserTableCompareFn
#undef gChatStr_ciSetChannelPassword
#undef gChatStr_ciJoinCallbackCalled
#undef gChatStr_ciChannelTableHashFn
#undef gChatStr_ciGetChannelNumUsers
#undef gChatStr_ciUserEnteredChannel
#undef gChatStr_ciGetChannelCallbacks
#undef gChatStr_ciChannelListUsersMap
#undef gChatStr_ciSetUserBasicInfoMap
#undef gChatStr_ciUserEnumChannelsMap
#undef gChatStr_ciWasJoinCallbackCalled
#undef gChatStr_ciChannelTableCompareFn
#undef gChatStr_ciUserTableElementFreeFn
#undef gChatStr_ciChannelTableElementFreeFn
#undef gChatStr_StrNeNULL
#undef gChatStr_ChatChannelC
#undef gChatStr_Str0_Ne0
#undef gChatStr_ElemNeNULL
#undef gChatStr_NumBucketsGt0
#undef gChatStr_Elem1_NeNULL
#undef gChatStr_Elem2_NeNULL
#undef gChatStr_Str1_NeNULL
#undef gChatStr_Str2_NeNULL
#undef gChatStr_Str1_0_Ne0
#undef gChatStr_Str2_0_Ne0
#undef gChatStr_ChatNeNULL_2
#undef gChatStr_chatChannel
#undef gChatStr_ChannelNeNULL
#undef gChatStr_Channel0_Ne0
#undef gChatStr_StrlenChannelLtMAX_CHANNEL
#undef gChatStr_CallbacksNeNULL
#undef gChatStr_Empty_19
#undef gChatStr_ClientDataNeNULL
#undef gChatStr_UserNameNeNULL
#undef gChatStr_UserName0_Ne0
#undef gChatStr_StrlenUserNameLtMAX_NAME
#undef gChatStr_DataNumUsersGe0
#undef gChatStr_0_9
#undef gChatStr_CallbackNeNULL_3
#undef gChatStr_NameNeNULL
#undef gChatStr_Name0_Ne0
#undef gChatStr_StrlenNameLtMAX_NAME
#undef gChatStr_ModeGe0_AndModeLe3
#undef gChatStr_TableLookupChatChannelUsersChatUserNeNULL
#undef gChatStr_UserNeNULL
#undef gChatStr_User0_Ne0
#undef gChatStr_StrlenUserLtMAX_NAME
#undef gChatStr_ChannelUsersNeNULL
#undef gChatStr_DataUserNeNULL
#undef gChatStr_DataUserName0_Ne0
#undef gChatStr_DataCallbackNeNULL_2
#undef gChatStr_DataNewNickNeNULL
#undef gChatStr_DataNewNick0_Ne0
#undef gChatStr_StrlenDataNewNickLtMAX_NAME
#undef gChatStr_DataOldNickNeNULL
#undef gChatStr_DataOldNick0_Ne0
#undef gChatStr_StrlenDataOldNickLtMAX_NAME
#undef gChatStr_RcodeNe0
#undef gChatStr_OldNickNeNULL
#undef gChatStr_OldNick0_Ne0
#undef gChatStr_StrlenOldNickLtMAX_NAME
#undef gChatStr_NewNickNeNULL
#undef gChatStr_NewNick0_Ne0
#undef gChatStr_StrlenNewNickLtMAX_NAME
#undef gChatStr_NickNeNULL
#undef gChatStr_Nick0_Ne0
#undef gChatStr_StrlenNickLtMAX_NAME
#undef ciNumServerMessageHandlers
#undef gChatStr_ciGetNextID
#undef gChatStr_ciAddFilter
#undef gChatStr_ciParseMode
#undef gChatStr_ciParseValue
#undef gChatStr_ciUTMHandler
#undef gChatStr_ciATMHandler
#undef gChatStr_ciFindFilter
#undef gChatStr_ciFilterThink
#undef gChatStr_ciPingHandler
#undef gChatStr_ciNickHandler
#undef gChatStr_ciJoinHandler
#undef gChatStr_ciPartHandler
#undef gChatStr_ciKickHandler
#undef gChatStr_ciQuitHandler
#undef gChatStr_ciKillHandler
#undef gChatStr_ciModeHandler
#undef gChatStr_ciTopicHandler
#undef gChatStr_ciErrorHandler
#undef gChatStr_ciRemoveFilter
#undef gChatStr_ciFinishFilter
#undef gChatStr_ciAddJOINFilter
#undef gChatStr_ciNoticeHandler
#undef gChatStr_ciInviteHandler
#undef gChatStr_ciDestroyFilter
#undef gChatStr_ciCleanupFilters
#undef gChatStr_ciPrivmsgHandler
#undef gChatStr_ciRplListHandler
#undef gChatStr_ciFilterTimedout
#undef gChatStr_ciRplCDKeyHandler
#undef gChatStr_ciRplLoginHandler
#undef gChatStr_ciRplTopicHandler
#undef gChatStr_ciRplGetKeyHandler
#undef gChatStr_ciRplUserIPHandler
#undef gChatStr_ciNameReplyHandler
#undef gChatStr_ciFindGetKeyFilter
#undef gChatStr_ciCheckFiltersForID
#undef gChatStr_ciRplGetCKeyHandler
#undef gChatStr_ciEndOfNamesHandler
#undef gChatStr_ciRplBanListHandler
#undef gChatStr_ciRplNoTopicHandler
#undef gChatStr_ciRplWelcomeHandler
#undef gChatStr_ciApplyChangesToMode
#undef gChatStr_ciRplWhoReplyHandler
#undef gChatStr_ciRplEndOfWhoHandler
#undef gChatStr_ciRplSecureKeyHandler
#undef gChatStr_ciRplEndGetKeyHandler
#undef gChatStr_ciRplListStartHandler
#undef gChatStr_ciRplWhoisUserHandler
#undef gChatStr_ciErrNickInUseHandler
#undef gChatStr_ciRplEndGetCKeyHandler
#undef gChatStr_ciRplGetChanKeyHandler
#undef gChatStr_ciRplEndOfWhoisHandler
#undef gChatStr_ciErrBadChanMaskHandler
#undef gChatStr_ciErrLoginFailedHandler
#undef gChatStr_ciErrNoUniqueNickHandler
#undef gChatStr_ciRplEndOfBanListHandler
#undef gChatStr_ciErrBadChannelKeyHandler
#undef gChatStr_ciErrNoSuchChannelHandler
#undef gChatStr_ciRplChannelModeIsHandler
#undef gChatStr_ciRplWhoisChannelsHandler
#undef gChatStr_ciErrChannelIsFullHandler
#undef gChatStr_ciQuitEnumChannelsCallback
#undef gChatStr_ciKillEnumChannelsCallback
#undef gChatStr_ciErrInviteOnlyChanHandler
#undef gChatStr_ciErrBannedFromChanHandler
#undef gChatStr_ciErrTooManyChannelsHandler
#undef gChatStr_ciErrErroneusNicknameHandler
#undef gChatStr_ciErrUniqueNickExpiredHandler
#undef gChatStr_ciErrRegisterNickFailedHandler
#undef ciServerMessageHandlers
#undef gChatStr_ChatNeNULL_3
#undef gChatStr_ChatHandlersC
#undef gChatStr_NumMatchesGt0
#undef gChatStr_matches
#undef gChatStr_MatchesI_TypeGe0_AndMatchesI_TypeLtNUM_TYPES
#undef gChatStr_channel
#undef gChatStr_Channel0
#undef gChatStr_FilterNeNULL
#undef gChatStr_filter
#undef gChatStr_FilterTypeGe0_AndFilterTypeLtNUM_TYPES
#undef gChatStr_0_10
#undef gChatStr_TimedOut
#undef gChatStr_ID_Gt0
#undef gChatStr_PasswordNeNULL
#undef gChatStr_StrlenPasswordLtMAX_PASSWORD
#undef gChatStr_B_UnderscoreStar
#undef gChatStr_ModeNeNULL
#undef gChatStr_MessageNumParamsEq2
#undef gChatStr_Empty_20
#undef gChatStr_ACTION
#undef gChatFmt_PONG
#undef gChatStr_MessageNumParamsEq1
#undef gChatStr_StrlenNewNickLtMAX_NICK
#undef gChatStr_NickNe0
#undef gChatFmt_MODE
#undef gChatStr_MessageNumParamsEq2_OrMessageNumParamsEq3
#undef gChatStr_UserNeNULL_2
#undef gChatStr_User0_Ne0_2
#undef gChatStr_ChannelNeNULL_2
#undef gChatStr_Channel0_Ne0_2
#undef gChatStr_ReasonNeNULL
#undef gChatStr_MessageNumParamsGe2
#undef gChatStr_MessageNumParamsEq4
#undef gChatStr_Space_3
#undef gChatStr_Nick0_Ne0_2
#undef gChatStr_Nick1_Ne0
#undef gChatStr_MessageNumParamsEq3
#undef gChatStr_Star_2
#undef gChatStr_ConnectionConnecting
#undef gChatStr_MessageNumParamsEq8
#undef gChatStr_flags
#undef gChatStr_len
#undef gChatStr_MessageNumParamsEq5
#undef gChatStr_BCAST
#undef gChatStr_b_
#undef gChatStr_MessageNumParamsGe1
#undef gChatStr_DataNeNULL_2
#undef gChatStr_MessageNumParamsGe3
#undef gChatStr_MessageNumParamsEq6
#undef gChatStr_DataChannelNeNULL
#undef gChatStr_DataChannel0_Ne0
#undef gChatFmt_MODE_B
#undef gChatStr_MessageNumParamsGe3_2
#undef gChatStr_DataNumBansGe0
#undef gChatStr_USRIP
#undef gChatStr_Backslash_2
#undef gChatCryptVersion
#undef gChatStr_ciThink
#undef gChatStr_ciSendNick
#undef gChatStr_ciSendUser
#undef gChatStr_ciNickError
#undef gChatStr_ciSendLogin
#undef gChatStr_chatInChannelA
#undef gChatStr_chatDisconnect
#undef gChatStr_chatEnumUsersA
#undef gChatStr_chatConnectDoit
#undef gChatStr_chatEnumChannelsA
#undef gChatStr_chatEnterChannelA
#undef gChatStr_chatLeaveChannelA
#undef gChatStr_ciHandleDisconnect
#undef gChatStr_chatRetryWithNickA
#undef gChatStr_ciSendGetChannelKey
#undef gChatStr_ciEnumUsersCallback
#undef gChatStr_chatGetChannelKeysA
#undef gChatStr_chatSetChannelKeysA
#undef gChatStr_chatSetChannelModeA
#undef gChatStr_chatGetChannelModeA
#undef gChatStr_chatSetChannelLimitA
#undef gChatStr_chatSendUserMessageA
#undef gChatStr_ciProcessServerMessage
#undef gChatStr_chatRegisterUniqueNickA
#undef gChatStr_chatGetChannelNumUsersA
#undef gChatStr_chatSendChannelMessageA
#undef gChatStr_MessageNeNULL_2
#undef gChatStr_ChatMainC
#undef gChatStr_ChatNeNULL_4
#undef gChatStr_Disconnected
#undef gChatStr_Star_3
#undef gChatFmt_NICK
#undef gChatFmt_USER
#undef gChatStr_127_Dot0_Dot0_Dot1
#undef gChatFmt_LOGINPREAUTH
#undef gChatFmt_LOGIN
#undef gChatFmt_LOGIN_2
#undef gChatStr_0_11
#undef gChatStr_Empty_21
#undef gChatStr_ServerAddressNeNULL
#undef gChatStr_CallbacksNeNULL_2
#undef gChatStr_ConnectCallbackNeNULL
#undef gChatStr_NickNeNULL_2
#undef gChatStr_Nick0_Ne0_3
#undef gChatStr_StrlenNickLtMAX_NICK
#undef gChatStr_NamespaceID_Gt0
#undef gChatStr_UniquenickAndUniquenick0
#undef gChatStr_PasswordAndPassword0
#undef gChatStr_NamespaceID_Ge0
#undef gChatStr_EmailAndEmail0
#undef gChatStr_ProfilenickAndProfilenick0
#undef gChatStr_AuthtokenAndAuthtoken0
#undef gChatStr_PartnerchallengeAndPartnerchallenge0
#undef gChatStr_preauth
#undef gChatStr_GamenameAndGamename0
#undef gChatStr_SecretKeyAndSecretKey0
#undef gChatFmt_CRYPT_Des
#undef gChatStr_USRIP_2
#undef gChatFmt_NICK_2
#undef gChatFmt_REGISTERNICK
#undef gChatStr_QUIT_Later
#undef gChatStr_ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuv_3
#undef gChatStr_CallbackAllNeNULL_OrCallbackEachNeNULL
#undef gChatFmt_LIST
#undef gChatStr_ChannelNeNULL_3
#undef gChatStr_Channel0_Ne0_3
#undef gChatFmt_JOIN
#undef gChatFmt_PART
#undef gChatStr_TypeEqCHAT_MESSAGE_OrTypeEqCHAT_ACTION_OrTypeEq
#undef gChatFmt_PRIVMSG
#undef gChatFmt_PRIVMSG_ACTION
#undef gChatFmt_NOTICE
#undef gChatFmt_UTM
#undef gChatFmt_ATM
#undef gChatStr_CallbackNeNULL_4
#undef gChatStr_ModeNeNULL_2
#undef gChatStr_XiXpXsXmXnXtXlXe
#undef gChatFmt_SpaceInt
#undef gChatFmt_MODE_2
#undef gChatFmt_MODE_3
#undef gChatStr_LimitGe0
#undef gChatFmt_MODE_L
#undef gChatFmt_MODE_L_2
#undef gChatStr_NumUsersGe0
#undef gChatStr_ParamNeNULL
#undef gChatStr_DataCallbackNeNULL_3
#undef gChatFmt_NAMES
#undef gChatStr_UserNeNULL_3
#undef gChatStr_User0_Ne0_3
#undef gChatStr_StrlenUserLtMAX_USER
#undef gChatFmt_BackslashStrBackslashStr
#undef gChatFmt_Int_6
#undef gChatStr_CookieAndCookie0
#undef gChatStr_NumGe0
#undef gChatFmt_SETCHANKEY
#undef gChatFmt_SETCKEY
#undef gChatStr_ChannelAndChannel0
#undef gChatStr_NotNumOrKeys
#undef gChatFmt_GETCHANKEY_0
#undef gChatFmt_GETCKEY_0
#undef gChatStr_B_UnderscoreStar_2
#undef gChatStr_ciParseUser
#undef gChatStr_ciSocketSend
#undef gChatStr_ciSocketRecv
#undef gChatStr_ciBufferInit
#undef gChatStr_ciParseParam
#undef gChatStr_ciSocketInit
#undef gChatStr_ciSocketSendf
#undef gChatStr_ciSocketThink
#undef gChatStr_ciParseMessage
#undef gChatStr_ciSocketConnect
#undef gChatStr_ciBufferPreAppend
#undef gChatStr_ciBufferClipFront
#undef gChatStr_ciSocketThinkSend
#undef gChatStr_ciSocketThinkRecv
#undef gChatStr_ciSocketDisconnect
#undef gChatStr_BufferNeNULL_2
#undef gChatStr_ChatSocketC
#undef gChatStr_BufferNeNULL_3
#undef gChatStr_BufferSizeGe0
#undef gChatStr_BufferSizeBUFFER_INC_Eq0
#undef gChatStr_BufferLengthGe0
#undef gChatStr_BufferLengthLeBufferSize
#undef gChatStr_LenGe0_2
#undef gChatStr_LenLeSHRT_MAX
#undef gChatStr_LenLeBufferLength
#undef gChatStr_SockNeNULL
#undef gChatStr_SockNeNULL_2
#undef gChatStr_SockConnectStateEqCiNotConnectedOrSock
#undef gChatStr_SockInputQueueNeNULL
#undef gChatStr_SockInputQueueSizeGe0
#undef gChatStr_SockInputQueueSizeBUFFER_INC_Eq0
#undef gChatStr_SockInputQueueLengthGe0
#undef gChatStr_SockInputQueueLengthLeSockInputQueueSize
#undef gChatStr_SockOutputQueueNeNULL
#undef gChatStr_SockOutputQueueSizeGe0
#undef gChatStr_SockOutputQueueSizeBUFFER_INC_Eq0
#undef gChatStr_SockOutputQueueLengthGe0
#undef gChatStr_SockOutputQueueLengthLeSockOutputQueueSize
#undef gChatStr_ServerAddressNeNULL_2
#undef gChatStr_PortGe0
#undef gChatStr_PortLeUSHRT_MAX
#undef gChatStr_SockConnectStateEqCiNotConnected
#undef gChatStr_SockConnectStateEqCiConnected
#undef gChatStr_0_12
#undef gChatStr_PTextNeNULL
#undef gChatStr_MessageNeNULL_3
#undef gChatStr_SpaceColon_2
#undef gChatStr_Space_4

extern void ciATMHandler(void);
extern void ciEndOfNamesHandler(void);
extern void ciErrBadChanMaskHandler(void);
extern void ciErrBadChannelKeyHandler(void);
extern void ciErrBannedFromChanHandler(void);
extern void ciErrChannelIsFullHandler(void);
extern void ciErrErroneusNicknameHandler(void);
extern void ciErrInviteOnlyChanHandler(void);
extern void ciErrLoginFailedHandler(void);
extern void ciErrNickInUseHandler(void);
extern void ciErrNoSuchChannelHandler(void);
extern void ciErrNoSuchNickHandler(void);
extern void ciErrNoUniqueNickHandler(void);
extern void ciErrRegisterNickFailedHandler(void);
extern void ciErrTooManyChannelsHandler(void);
extern void ciErrUniqueNickExpiredHandler(void);
extern void ciErrorHandler(void);
extern void ciInviteHandler(void);
extern void ciJoinHandler(void);
extern void ciKickHandler(void);
extern void ciKillHandler(void);
extern void ciModeHandler(void);
extern void ciNameReplyHandler(void);
extern void ciNickHandler(void);
extern void ciNoticeHandler(void);
extern void ciPartHandler(void);
extern void ciPingHandler(void);
extern void ciPrivmsgHandler(void);
extern void ciQuitHandler(void);
extern void ciRplBanListHandler(void);
extern void ciRplCDKeyHandler(void);
extern void ciRplChannelModeIsHandler(void);
extern void ciRplEndGetCKeyHandler(void);
extern void ciRplEndGetKeyHandler(void);
extern void ciRplEndOfBanListHandler(void);
extern void ciRplEndOfWhoHandler(void);
extern void ciRplEndOfWhoisHandler(void);
extern void ciRplGetCKeyHandler(void);
extern void ciRplGetChanKeyHandler(void);
extern void ciRplGetKeyHandler(void);
extern void ciRplListEndHandler(void);
extern void ciRplListHandler(void);
extern void ciRplListStartHandler(void);
extern void ciRplLoginHandler(void);
extern void ciRplNoTopicHandler(void);
extern void ciRplSecureKeyHandler(void);
extern void ciRplTopicHandler(void);
extern void ciRplUserIPHandler(void);
extern void ciRplWelcomeHandler(void);
extern void ciRplWhoReplyHandler(void);
extern void ciRplWhoisChannelsHandler(void);
extern void ciRplWhoisUserHandler(void);
extern void ciTopicHandler(void);
extern void ciUTMHandler(void);

// Initialised data (.data)

// C declares this const, but it lives in .data
u8 gLobbyStr_N[4] __attribute__((aligned(4))) = "N";

// C declares this const, but it lives in .data
u8 gLobbyStr_M[4] __attribute__((aligned(4))) = "M";

// C declares this const, but it lives in .data
u8 gLobbyStr_C[4] __attribute__((aligned(4))) = "C";

// C declares this const, but it lives in .data
u8 gLobbyStr_F2[4] __attribute__((aligned(4))) = "F2";

// C declares this const, but it lives in .data
u8 gLobbyStr_F1[4] __attribute__((aligned(4))) = "F1";

// 0x02254F88
char gLobbyFmt_M_IntUnderscoreUint[8] __attribute__((aligned(4))) = "M%d_%u";

// C declares this const, but it lives in .data
u8 gLobbyStr_Invalid[16] __attribute__((aligned(4))) = "Invalid";

// 0x02254FA0
// An address sits where that type has a 1-byte field.
void (*gPPWLobbyPlayersVtable[4])(void) = {
    (void (*)(void))PPWLobbyPlayers_Destroy,
    (void (*)(void))PPWLobbyPlayers_Delete,
    NULL,
    NULL,
};

// 0x02254FB0
PPWLobbyPlayerVtable gPPWLobbyPlayerVtable = { PPWLobbyPlayer_Destroy, PPWLobbyPlayer_Delete };

#pragma explicit_zero_data on
// zero bytes after gPPWLobbyPlayerVtable in the asm
static u8 gPPWLobbyPlayerVtable_pad[8] __attribute__((aligned(4))) = { 0 };
#pragma explicit_zero_data reset

// 0x02254FC0
void (*gPPWLobbyWebRequestVtable[2])(void) = {
    (void (*)(void))PPWLobbyWebRequest_Destroy,
    (void (*)(void))PPWLobbyWebRequest_Delete,
};

char gLobbyStr_WebEncLobbyGetVIP_Asp[28] __attribute__((aligned(4))) = "/web/enc/lobby/getVIP.asp";

char gLobbyStr_WebEncLobbyGetScheduleAsp[32] __attribute__((aligned(4))) = "/web/enc/lobby/getSchedule.asp";

char gLobbyStr_WebEncLobbyCheckProfileAsp[32] __attribute__((aligned(4))) = "/web/enc/lobby/checkProfile.asp";

char gLobbyStr_WebEncLobbyGetQuestionnaireAsp[36] __attribute__((aligned(4))) = "/web/enc/lobby/getQuestionnaire.asp";

char gLobbyStr_WebEncLobbySubmitQuestionnaireAsp[40] __attribute__((aligned(4))) = "/web/enc/lobby/submitQuestionnaire.asp";

char gLobbyStr_StatsUploadKey[64] __attribute__((aligned(4))) = "uLMOGEiiJogofchScpXb000244fd00006015100000005b440e7epokemondpds";

// 0x022550B0
char gLobbyStr_Star[4] __attribute__((aligned(4))) = "*";

#pragma explicit_zero_data on
// 0x022550B4
char gLobbyStr_Empty_15[4] __attribute__((aligned(4))) = "";
#pragma explicit_zero_data reset

// 0x022550B8
char gLobbyStr_Bang[4] __attribute__((aligned(4))) = "!";

// 0x022550BC
char gLobbyFmt_C_IntUnderscoreUint[8] __attribute__((aligned(4))) = "C%d_%u";

// 0x022550C4
char gLobbyStr_b_lib_u_user[16] __attribute__((aligned(4))) = "b_lib_u_user";

// 0x022550D4
char gLobbyStr_b_lib_u_system[16] __attribute__((aligned(4))) = "b_lib_u_system";

// 0x022550E4
char gLobbyStr_b_lib_c_time[16] __attribute__((aligned(4))) = "b_lib_c_time";

// 0x022550F4
char gLobbyStr_b_lib_c_lobby[16] __attribute__((aligned(4))) = "b_lib_c_lobby";

// 0x02255104
char gLobbyStr_TreeInsertLengthError[28] __attribute__((aligned(4))) = "tree::insert length error";

// 0x02255120
char gLobbyStr_BasicStringReserveLengthError[36] __attribute__((aligned(4))) = "basic_string::reserve length_error";

// 0x02255144
char gLobbyStr_BasicStringOutOfRange[28] __attribute__((aligned(4))) = "basic_string: out_of_range";

// 0x02255160
char gLobbyStr_StringComparePosGtLen[28] __attribute__((aligned(4))) = "string compare: pos > len";

// 0x0225517C
char gLobbyStr_BasicStringLengthError[28] __attribute__((aligned(4))) = "basic_string: length_error";

#pragma explicit_zero_data on
// 0x02255198
u8 gLobbySortEmptyBuffer[8] __attribute__((aligned(4))) = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
#pragma explicit_zero_data reset

#pragma explicit_zero_data on
// 0x022551A0
u32 gLobbyEventDequeMapBufferMaxSize = 0;
#pragma explicit_zero_data reset

#pragma explicit_zero_data on
// 0x022551A4
u32 gLobbyEventDequeMapMaxSize = 0;
#pragma explicit_zero_data reset

#pragma explicit_zero_data on
// 0x022551A8
u32 gLobbyDequeMaxSize = 0;
#pragma explicit_zero_data reset

// 0x022551AC
char gLobbyStr_DequeLengthError[24] = "deque:: length error";

// 0x022551C4
char gLobbyStr_CdequeLengthError[20] __attribute__((aligned(4))) = "cdeque length error";

#pragma explicit_zero_data on
// 0x022551D8
u8 ov45_022551D8[1] __attribute__((aligned(4))) = { 0x00 };
#pragma explicit_zero_data reset

#pragma explicit_zero_data on
// 0x022551D9
u8 ov45_022551D9[3] = { 0x00, 0x00, 0x00 };
#pragma explicit_zero_data reset

// 0x022551DC
char gLobbyStr_SpaceSpace[4] = "  ";

// 0x022551E0
char gLobbyStr_Space_2[4] __attribute__((aligned(4))) = " ";

// 0x022551E4
char gLobbyStr_B[4] __attribute__((aligned(4))) = "B";

// 0x022551E8
char gLobbyStr_S[4] __attribute__((aligned(4))) = "S";

#pragma explicit_zero_data on
// 0x022551EC
char gLobbyStr_Empty_16[4] __attribute__((aligned(4))) = "";
#pragma explicit_zero_data reset

// 0x022551F0
char gLobbyFmt_Hex_3[4] __attribute__((aligned(4))) = "%x";

// 0x022551F4
char gLobbyStr_A[4] __attribute__((aligned(4))) = "A";

// 0x022551F8
char gLobbyStr__[4] __attribute__((aligned(4))) = "_";

// 0x022551FC
char gLobbyFmt_Str_3[4] __attribute__((aligned(4))) = "%s";

// 0x02255200
// C declares this as `u8 ov45_02255200[]`, but an address sits where that type has a 1-byte field.
struct {
    u8 unk0[4];
    void (*unk4)(void);
    u32 unk8;
} ov45_02255200 = {
    { 0x01, 0x00, 0x00, 0x00 },
    (void (*)(void))PPWLobbyPlayer_HasProfiles,
    0,
};

// 0x0225520C
char gLobbyStr_TreeInsertLengthError_2[28] = "tree::insert length error";

// 0x02255228
// clang-format off
u8 gLobbyRequestMapInsertFlags[16] __attribute__((aligned(4))) = {
    0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};
// clang-format on

// 0x02255238
// clang-format off
LobbyRequestVtable gLobbyRequestVtable = {
    (void (*)(LobbyRequest *))LobbyRequest_Destroy, (LobbyRequest *(*)(LobbyRequest *))LobbyRequest_Delete,
    (u32 (*)(LobbyRequest *))LobbyRequest_GetId, (u32 (*)(LobbyRequest *))LobbyRequest_GetParam,
};
// clang-format on

#pragma explicit_zero_data on
// zero bytes after gLobbyRequestVtable in the asm
static u8 gLobbyRequestVtable_pad[8] __attribute__((aligned(4))) = { 0 };
#pragma explicit_zero_data reset

// 0x02255250
// clang-format off
LobbyRequestVtable gLobbyGetChannelModeRequestVtable = {
    (void (*)(LobbyRequest *))LobbyGetChannelModeRequest_Destroy,
    (LobbyRequest *(*)(LobbyRequest *))LobbyGetChannelModeRequest_Delete,
    (u32 (*)(LobbyRequest *))LobbyRequest_GetId, (u32 (*)(LobbyRequest *))LobbyRequest_GetParam,
};
// clang-format on

#pragma explicit_zero_data on
// zero bytes after gLobbyGetChannelModeRequestVtable in the asm
static u8 gLobbyGetChannelModeRequestVtable_pad[8] __attribute__((aligned(4))) = { 0 };
#pragma explicit_zero_data reset

// 0x02255268
// clang-format off
LobbyRequestVtable gLobbyGetChannelKeysRequestVtable = {
    (void (*)(LobbyRequest *))LobbyGetChannelKeysRequest_Destroy,
    (LobbyRequest *(*)(LobbyRequest *))LobbyGetChannelKeysRequest_Delete,
    (u32 (*)(LobbyRequest *))LobbyRequest_GetId, (u32 (*)(LobbyRequest *))LobbyRequest_GetParam,
};
// clang-format on

#pragma explicit_zero_data on
// zero bytes after gLobbyGetChannelKeysRequestVtable in the asm
static u8 gLobbyGetChannelKeysRequestVtable_pad[8] __attribute__((aligned(4))) = { 0 };
#pragma explicit_zero_data reset

// 0x02255280
// clang-format off
LobbyRequestVtable gLobbyEnterChannelRequestVtable = {
    (void (*)(LobbyRequest *))LobbyEnterChannelRequest_Destroy,
    (LobbyRequest *(*)(LobbyRequest *))LobbyEnterChannelRequest_Delete,
    (u32 (*)(LobbyRequest *))LobbyRequest_GetId, (u32 (*)(LobbyRequest *))LobbyRequest_GetParam,
};
// clang-format on

#pragma explicit_zero_data on
// zero bytes after gLobbyEnterChannelRequestVtable in the asm
static u8 gLobbyEnterChannelRequestVtable_pad[8] __attribute__((aligned(4))) = { 0 };
#pragma explicit_zero_data reset

// 0x02255298
// clang-format off
LobbyRequestVtable gLobbyEnumUsersRequestVtable = {
    (void (*)(LobbyRequest *))LobbyEnumUsersRequest_Destroy,
    (LobbyRequest *(*)(LobbyRequest *))LobbyEnumUsersRequest_Delete,
    (u32 (*)(LobbyRequest *))LobbyRequest_GetId, (u32 (*)(LobbyRequest *))LobbyRequest_GetParam,
};
// clang-format on

#pragma explicit_zero_data on
// zero bytes after gLobbyEnumUsersRequestVtable in the asm
static u8 gLobbyEnumUsersRequestVtable_pad[8] __attribute__((aligned(4))) = { 0 };
#pragma explicit_zero_data reset

// 0x022552B0
// clang-format off
LobbyRequestVtable gLobbyEnumChannelsRequestVtable = {
    (void (*)(LobbyRequest *))LobbyEnumChannelsRequest_Destroy,
    (LobbyRequest *(*)(LobbyRequest *))LobbyEnumChannelsRequest_Delete,
    (u32 (*)(LobbyRequest *))LobbyRequest_GetId, (u32 (*)(LobbyRequest *))LobbyRequest_GetParam,
};
// clang-format on

// 0x022552C0
char gLobbyStr_SERVER[8] = "SERVER";

// 0x022552C8
char gLobbyStr_ExcessFlood[16] __attribute__((aligned(4))) = "Excess Flood";

// 0x022552D8
char gLobbyStr_SpaceColon[4] __attribute__((aligned(4))) = " :";

// 0x022552DC
char gLobbyStr_normal[8] __attribute__((aligned(4))) = "normal";

// 0x022552E4
char gLobbyStr_voice[8] __attribute__((aligned(4))) = "voice";

// 0x022552EC
char gLobbyStr_ops[4] __attribute__((aligned(4))) = "ops";

// 0x022552F0
char gLobbyStr_VoiceOps[12] __attribute__((aligned(4))) = "voice+ops";

// 0x022552FC
char gLobbyStr_invalid[8] __attribute__((aligned(4))) = "invalid";

#pragma explicit_zero_data on
// 0x02255304
char gLobbyStr_Empty_17[4] __attribute__((aligned(4))) = "";
#pragma explicit_zero_data reset

// 0x02255308
char gLobbyStr_DWCUser[8] __attribute__((aligned(4))) = "DWCUser";

// 0x02255310
char gLobbyStr_DWCName[8] __attribute__((aligned(4))) = "DWCName";

// 0x02255318
char gLobbyStr_Dot[4] __attribute__((aligned(4))) = ".";

// 0x0225531C
char gLobbyStr_PeerchatGsNintendowifiNet[32] __attribute__((aligned(4))) = "peerchat.gs.nintendowifi.net";

// 0x0225533C
char gLobbyStr_TreeInsertLengthError_3[28] __attribute__((aligned(4))) = "tree::insert length error";

// 0x02255358
// C declares this as `u8 ov45_02255358[]`, but an address sits where that type has a 1-byte field.
struct {
    u8 unk0[8];
    void (*unk8)(void);
    u8 unkC[4];
} ov45_02255358 = {
    { 0x01, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00 },
    (void (*)(void))LobbyChat_RemoveUserIfUnused,
    { 0 },
};

// C declares this const, but it lives in .data
u8 gLobbyStr_R[4] = "R";

// C declares this const, but it lives in .data
u8 gLobbyStr_T[4] __attribute__((aligned(4))) = "T";

// C declares this const, but it lives in .data
u8 gLobbyStr_D[4] __attribute__((aligned(4))) = "D";

// C declares this const, but it lives in .data
u8 gLobbyStr_D7[4] __attribute__((aligned(4))) = "D7";

// C declares this const, but it lives in .data
u8 gLobbyStr_D8[4] __attribute__((aligned(4))) = "D8";

// C declares this const, but it lives in .data
u8 gLobbyStr_D6[4] __attribute__((aligned(4))) = "D6";

// C declares this const, but it lives in .data
u8 gLobbyStr_D9[4] __attribute__((aligned(4))) = "D9";

// C declares this const, but it lives in .data
u8 gLobbyStr_D1[4] __attribute__((aligned(4))) = "D1";

// C declares this const, but it lives in .data
u8 gLobbyStr_D2[4] __attribute__((aligned(4))) = "D2";

// C declares this const, but it lives in .data
u8 gLobbyStr_D3[4] __attribute__((aligned(4))) = "D3";

// C declares this const, but it lives in .data
u8 gLobbyStr_D4[4] __attribute__((aligned(4))) = "D4";

// C declares this const, but it lives in .data
u8 gLobbyStr_D5[4] __attribute__((aligned(4))) = "D5";

// 0x02255398
char gLobbyStr_Bang_2[4] __attribute__((aligned(4))) = "!";

// 0x0225539C
char gLobbyFmt_N_UnderscoreIntUnderscoreUint[8] __attribute__((aligned(4))) = "N_%d_%u";

// 0x022553A4
char gLobbyStr___2[4] __attribute__((aligned(4))) = "_";

#pragma explicit_zero_data on
// 0x022553A8
char gLobbyStr_Empty_18[4] __attribute__((aligned(4))) = "";
#pragma explicit_zero_data reset

// 0x022553AC
char gLobbyStr_TreeInsertLengthError_4[28] __attribute__((aligned(4))) = "tree::insert length error";

// 0x022553C8
// C declares this as `const char gChatStr_ciAddCallback_[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_ciAddCallback_[16] __attribute__((aligned(4))) = "ciAddCallback_";

// 0x022553D8
// C declares this as `const char gChatStr_ciCallCallback[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_ciCallCallback[16] __attribute__((aligned(4))) = "ciCallCallback";

// 0x022553E8
// C declares this as `const char gChatStr_ciCallCallbacks[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_ciCallCallbacks[16] __attribute__((aligned(4))) = "ciCallCallbacks";

// 0x022553F8
// C declares this as `const char gChatStr_ciFreeCallbackData[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_ciFreeCallbackData[20] __attribute__((aligned(4))) = "ciFreeCallbackData";

// 0x0225540C
// C declares this as `const char gChatStr_ciCleanupCallbacks[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_ciCleanupCallbacks[20] __attribute__((aligned(4))) = "ciCleanupCallbacks";

// 0x02255420
// C declares this as `const char gChatStr_ciGetCallbackIndexByID[]`, but s2c could not read that type
// (its header needs generated files).
char gChatStr_ciGetCallbackIndexByID[24] __attribute__((aligned(4))) = "ciGetCallbackIndexByID";

// 0x02255438
char gLobbyStr_ciCallbacksArrayElementFreeFn[32] __attribute__((aligned(4))) = "ciCallbacksArrayElementFreeFn";

// 0x02255458
// C declares this as `const char gLobbyStr_DataNeNULL[]`, but s2c could not read that type (its header
// needs generated files).
char gLobbyStr_DataNeNULL[16] __attribute__((aligned(4))) = "data != NULL";

// 0x02255468
// C declares this as `const char gLobbyStr_ChatCallbacksC[]`, but s2c could not read that type (its
// header needs generated files).
char gLobbyStr_ChatCallbacksC[16] __attribute__((aligned(4))) = "chatCallbacks.c";

// 0x02255478
// C declares this as `const char gChatStr_DataTypeGe0[]`, but s2c could not read that type (its header
// needs generated files).
char gChatStr_DataTypeGe0[16] __attribute__((aligned(4))) = "data->type >= 0";

// 0x02255488
// C declares this as `const char gChatStr_DataTypeLtCALLBACK_NUM[]`, but s2c could not read that type
// (its header needs generated files).
char gChatStr_DataTypeLtCALLBACK_NUM[28] __attribute__((aligned(4))) = "data->type < CALLBACK_NUM";

// 0x022554A4
// C declares this as `const char gChatStr_DataCallbackNeNULL[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_DataCallbackNeNULL[24] __attribute__((aligned(4))) = "data->callback != NULL";

// 0x022554BC
// C declares this as `const char gChatStr_DataCallbackParamsNeNULL[]`, but s2c could not read that
// type (its header needs generated files).
char gChatStr_DataCallbackParamsNeNULL[32] __attribute__((aligned(4))) = "data->callbackParams != NULL";

// 0x022554DC
// C declares this as `const char gChatStr_DataID_Ge0[]`, but s2c could not read that type (its header
// needs generated files).
char gChatStr_DataID_Ge0[16] __attribute__((aligned(4))) = "data->ID >= 0";

// 0x022554EC
// C declares this as `const char gChatStr_0_8[]`, but s2c could not read that type (its header needs
// generated files).
char gChatStr_0_8[4] __attribute__((aligned(4))) = "0";

// 0x022554F0
// C declares this as `const char gChatStr_ChatNeNULL[]`, but s2c could not read that type (its header
// needs generated files).
char gChatStr_ChatNeNULL[16] __attribute__((aligned(4))) = "chat != NULL";

// 0x02255500
// C declares this as `const char gChatStr_TypeGe0[]`, but s2c could not read that type (its header
// needs generated files).
char gChatStr_TypeGe0[12] __attribute__((aligned(4))) = "type >= 0";

// 0x0225550C
// C declares this as `const char gChatStr_TypeLtCALLBACK_NUM[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_TypeLtCALLBACK_NUM[20] __attribute__((aligned(4))) = "type < CALLBACK_NUM";

// 0x02255520
// C declares this as `const char gChatStr_ConnectionCallbackListNeNULL[]`, but s2c could not read that
// type (its header needs generated files).
char gChatStr_ConnectionCallbackListNeNULL[36] __attribute__((aligned(4))) = "connection->callbackList != NULL";

// 0x02255544
// C declares this as `const char gChatStr_CallbackNeNULL_2[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_CallbackNeNULL_2[20] __attribute__((aligned(4))) = "callback != NULL";

// 0x02255558
// C declares this as `const char gChatStr_CallbackParamsNeNULL[]`, but s2c could not read that type
// (its header needs generated files).
char gChatStr_CallbackParamsNeNULL[24] __attribute__((aligned(4))) = "callbackParams != NULL";

// 0x02255570
// C declares this as `const char gChatStr_CallbackParamsSizeGt0[]`, but s2c could not read that type
// (its header needs generated files).
char gChatStr_CallbackParamsSizeGt0[24] __attribute__((aligned(4))) = "callbackParamsSize > 0";

// 0x02255588
// C declares this as `const char gChatStr_ID_Ge0[]`, but s2c could not read that type (its header
// needs generated files).
char gChatStr_ID_Ge0[8] __attribute__((aligned(4))) = "ID >= 0";

// 0x02255590
// C declares this as `const char gChatStr_SrcParamsNumChannelsGe0[]`, but s2c could not read that type
// (its header needs generated files).
char gChatStr_SrcParamsNumChannelsGe0[32] __attribute__((aligned(4))) = "srcParams-> numChannels >= 0";

// 0x022555B0
// C declares this as `const char gChatStr_SrcParamsNumUsersNeNULL[]`, but s2c could not read that type
// (its header needs generated files).
char gChatStr_SrcParamsNumUsersNeNULL[28] __attribute__((aligned(4))) = "srcParams->numUsers != NULL";

// 0x022555CC
// C declares this as `const char gChatStr_SrcParamsNumUsersGe0[]`, but s2c could not read that type
// (its header needs generated files).
char gChatStr_SrcParamsNumUsersGe0[28] __attribute__((aligned(4))) = "srcParams-> numUsers >= 0";

// 0x022555E8
// C declares this as `const char gChatStr_SrcParamsModesNeNULL[]`, but s2c could not read that type
// (its header needs generated files).
char gChatStr_SrcParamsModesNeNULL[28] __attribute__((aligned(4))) = "srcParams->modes != NULL";

// 0x02255604
// C declares this as `const char gChatStr_SrcParamsNumBansGe0[]`, but s2c could not read that type
// (its header needs generated files).
char gChatStr_SrcParamsNumBansGe0[28] __attribute__((aligned(4))) = "srcParams-> numBans >= 0";

// 0x02255620
// C declares this as `const char gChatStr_SrcParamsNumSuggestedNicksGe0[]`, but s2c could not read
// that type (its header needs generated files).
char gChatStr_SrcParamsNumSuggestedNicksGe0[36] __attribute__((aligned(4))) = "srcParams-> numSuggestedNicks >= 0";

// 0x02255644
// C declares this as `const char gChatStr_SrcParamsNumGe0[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_SrcParamsNumGe0[24] __attribute__((aligned(4))) = "srcParams-> num >= 0";

// 0x0225565C
// C declares this as `const char gChatStr_ciInChannel[]`, but s2c could not read that type (its header
// needs generated files).
char gChatStr_ciInChannel[12] __attribute__((aligned(4))) = "ciInChannel";

// 0x02255668
// C declares this as `const char gChatStr_ciHashString[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_ciHashString[16] __attribute__((aligned(4))) = "ciHashString";

// 0x02255678
// C declares this as `const char gChatStr_ciChannelLeft[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_ciChannelLeft[16] __attribute__((aligned(4))) = "ciChannelLeft";

// 0x02255688
// C declares this as `const char gChatStr_ciSetChannelMode[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_ciSetChannelMode[20] __attribute__((aligned(4))) = "ciSetChannelMode";

// 0x0225569C
// C declares this as `const char gChatStr_ciChannelEntered[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_ciChannelEntered[20] __attribute__((aligned(4))) = "ciChannelEntered";

// 0x022556B0
// C declares this as `const char gChatStr_ciGetChannelMode[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_ciGetChannelMode[20] __attribute__((aligned(4))) = "ciGetChannelMode";

// 0x022556C4
// C declares this as `const char gChatStr_ciUserChangedNick[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_ciUserChangedNick[20] __attribute__((aligned(4))) = "ciUserChangedNick";

// 0x022556D8
// C declares this as `const char gChatStr_ciUserChangedMode[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_ciUserChangedMode[20] __attribute__((aligned(4))) = "ciUserChangedMode";

// 0x022556EC
// C declares this as `const char gChatStr_ciUserLeftChannel[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_ciUserLeftChannel[20] __attribute__((aligned(4))) = "ciUserLeftChannel";

// 0x02255700
// C declares this as `const char gChatStr_ciCleanupChannels[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_ciCleanupChannels[20] __attribute__((aligned(4))) = "ciCleanupChannels";

// 0x02255714
// C declares this as `const char gChatStr_ciUserTableHashFn[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_ciUserTableHashFn[20] __attribute__((aligned(4))) = "ciUserTableHashFn";

// 0x02255728
// C declares this as `const char gChatStr_ciSetChannelTopic[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_ciSetChannelTopic[20] __attribute__((aligned(4))) = "ciSetChannelTopic";

// 0x0225573C
// C declares this as `const char gChatStr_ciChannelEntering[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_ciChannelEntering[20] __attribute__((aligned(4))) = "ciChannelEntering";

// 0x02255750
// C declares this as `const char gChatStr_ciUserEnumChannels[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_ciUserEnumChannels[20] __attribute__((aligned(4))) = "ciUserEnumChannels";

// 0x02255764
// C declares this as `const char gChatStr_ciSetUserBasicInfo[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_ciSetUserBasicInfo[20] __attribute__((aligned(4))) = "ciSetUserBasicInfo";

// 0x02255778
// C declares this as `const char gChatStr_ciChannelListUsers[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_ciChannelListUsers[20] __attribute__((aligned(4))) = "ciChannelListUsers";

// 0x0225578C
// C declares this as `const char gChatStr_ciUserChangeNickMap[]`, but s2c could not read that type
// (its header needs generated files).
char gChatStr_ciUserChangeNickMap[20] __attribute__((aligned(4))) = "ciUserChangeNickMap";

// 0x022557A0
// C declares this as `const char gChatStr_ciIsEnteringChannel[]`, but s2c could not read that type
// (its header needs generated files).
char gChatStr_ciIsEnteringChannel[20] __attribute__((aligned(4))) = "ciIsEnteringChannel";

// 0x022557B4
// C declares this as `const char gChatStr_ciUserTableCompareFn[]`, but s2c could not read that type
// (its header needs generated files).
char gChatStr_ciUserTableCompareFn[24] __attribute__((aligned(4))) = "ciUserTableCompareFn";

// 0x022557CC
// C declares this as `const char gChatStr_ciSetChannelPassword[]`, but s2c could not read that type
// (its header needs generated files).
char gChatStr_ciSetChannelPassword[24] __attribute__((aligned(4))) = "ciSetChannelPassword";

// 0x022557E4
// C declares this as `const char gChatStr_ciJoinCallbackCalled[]`, but s2c could not read that type
// (its header needs generated files).
char gChatStr_ciJoinCallbackCalled[24] __attribute__((aligned(4))) = "ciJoinCallbackCalled";

// 0x022557FC
// C declares this as `const char gChatStr_ciChannelTableHashFn[]`, but s2c could not read that type
// (its header needs generated files).
char gChatStr_ciChannelTableHashFn[24] __attribute__((aligned(4))) = "ciChannelTableHashFn";

// 0x02255814
// C declares this as `const char gChatStr_ciGetChannelNumUsers[]`, but s2c could not read that type
// (its header needs generated files).
char gChatStr_ciGetChannelNumUsers[24] __attribute__((aligned(4))) = "ciGetChannelNumUsers";

// 0x0225582C
// C declares this as `const char gChatStr_ciUserEnteredChannel[]`, but s2c could not read that type
// (its header needs generated files).
char gChatStr_ciUserEnteredChannel[24] __attribute__((aligned(4))) = "ciUserEnteredChannel";

// 0x02255844
// C declares this as `const char gChatStr_ciGetChannelCallbacks[]`, but s2c could not read that type
// (its header needs generated files).
char gChatStr_ciGetChannelCallbacks[24] __attribute__((aligned(4))) = "ciGetChannelCallbacks";

// 0x0225585C
// C declares this as `const char gChatStr_ciChannelListUsersMap[]`, but s2c could not read that type
// (its header needs generated files).
char gChatStr_ciChannelListUsersMap[24] __attribute__((aligned(4))) = "ciChannelListUsersMap";

// 0x02255874
// C declares this as `const char gChatStr_ciSetUserBasicInfoMap[]`, but s2c could not read that type
// (its header needs generated files).
char gChatStr_ciSetUserBasicInfoMap[24] __attribute__((aligned(4))) = "ciSetUserBasicInfoMap";

// 0x0225588C
// C declares this as `const char gChatStr_ciUserEnumChannelsMap[]`, but s2c could not read that type
// (its header needs generated files).
char gChatStr_ciUserEnumChannelsMap[24] __attribute__((aligned(4))) = "ciUserEnumChannelsMap";

// 0x022558A4
// C declares this as `const char gChatStr_ciWasJoinCallbackCalled[]`, but s2c could not read that type
// (its header needs generated files).
char gChatStr_ciWasJoinCallbackCalled[24] __attribute__((aligned(4))) = "ciWasJoinCallbackCalled";

// 0x022558BC
// C declares this as `const char gChatStr_ciChannelTableCompareFn[]`, but s2c could not read that type
// (its header needs generated files).
char gChatStr_ciChannelTableCompareFn[24] __attribute__((aligned(4))) = "ciChannelTableCompareFn";

// 0x022558D4
// C declares this as `const char gChatStr_ciUserTableElementFreeFn[]`, but s2c could not read that
// type (its header needs generated files).
char gChatStr_ciUserTableElementFreeFn[28] __attribute__((aligned(4))) = "ciUserTableElementFreeFn";

// 0x022558F0
// C declares this as `const char gChatStr_ciChannelTableElementFreeFn[]`, but s2c could not read that
// type (its header needs generated files).
char gChatStr_ciChannelTableElementFreeFn[28] __attribute__((aligned(4))) = "ciChannelTableElementFreeFn";

// 0x0225590C
// C declares this as `const char gChatStr_StrNeNULL[]`, but s2c could not read that type (its header
// needs generated files).
char gChatStr_StrNeNULL[12] __attribute__((aligned(4))) = "str != NULL";

// 0x02255918
// C declares this as `const char gChatStr_ChatChannelC[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_ChatChannelC[16] __attribute__((aligned(4))) = "chatChannel.c";

// 0x02255928
// C declares this as `const char gChatStr_Str0_Ne0[]`, but s2c could not read that type (its header
// needs generated files).
char gChatStr_Str0_Ne0[16] __attribute__((aligned(4))) = "str[0] != '\\0'";

// 0x02255938
// C declares this as `const char gChatStr_ElemNeNULL[]`, but s2c could not read that type (its header
// needs generated files).
char gChatStr_ElemNeNULL[16] __attribute__((aligned(4))) = "elem != NULL";

// 0x02255948
// C declares this as `const char gChatStr_NumBucketsGt0[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_NumBucketsGt0[16] __attribute__((aligned(4))) = "numBuckets > 0";

// 0x02255958
// C declares this as `const char gChatStr_Elem1_NeNULL[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_Elem1_NeNULL[16] __attribute__((aligned(4))) = "elem1 != NULL";

// 0x02255968
// C declares this as `const char gChatStr_Elem2_NeNULL[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_Elem2_NeNULL[16] __attribute__((aligned(4))) = "elem2 != NULL";

// 0x02255978
// C declares this as `const char gChatStr_Str1_NeNULL[]`, but s2c could not read that type (its header
// needs generated files).
char gChatStr_Str1_NeNULL[16] __attribute__((aligned(4))) = "str1 != NULL";

// 0x02255988
// C declares this as `const char gChatStr_Str2_NeNULL[]`, but s2c could not read that type (its header
// needs generated files).
char gChatStr_Str2_NeNULL[16] __attribute__((aligned(4))) = "str2 != NULL";

// 0x02255998
// C declares this as `const char gChatStr_Str1_0_Ne0[]`, but s2c could not read that type (its header
// needs generated files).
char gChatStr_Str1_0_Ne0[16] __attribute__((aligned(4))) = "str1[0] != '\\0'";

// 0x022559A8
// C declares this as `const char gChatStr_Str2_0_Ne0[]`, but s2c could not read that type (its header
// needs generated files).
char gChatStr_Str2_0_Ne0[16] __attribute__((aligned(4))) = "str2[0] != '\\0'";

// 0x022559B8
// C declares this as `const char gChatStr_ChatNeNULL_2[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_ChatNeNULL_2[16] __attribute__((aligned(4))) = "chat != NULL";

// 0x022559C8
// C declares this as `const char gChatStr_chatChannel[]`, but s2c could not read that type (its header
// needs generated files).
char gChatStr_chatChannel[12] __attribute__((aligned(4))) = "chatChannel";

// 0x022559D4
// C declares this as `const char gChatStr_ChannelNeNULL[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_ChannelNeNULL[16] __attribute__((aligned(4))) = "channel != NULL";

// 0x022559E4
// C declares this as `const char gChatStr_Channel0_Ne0[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_Channel0_Ne0[20] __attribute__((aligned(4))) = "channel[0] != '\\0'";

// 0x022559F8
// C declares this as `const char gChatStr_StrlenChannelLtMAX_CHANNEL[]`, but s2c could not read that
// type (its header needs generated files).
char gChatStr_StrlenChannelLtMAX_CHANNEL[32] __attribute__((aligned(4))) = "strlen(channel) < MAX_CHANNEL";

// 0x02255A18
// C declares this as `const char gChatStr_CallbacksNeNULL[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_CallbacksNeNULL[20] __attribute__((aligned(4))) = "callbacks != NULL";

#pragma explicit_zero_data on
// 0x02255A2C
// C declares this as `const char gChatStr_Empty_19[]`, but s2c could not read that type (its header
// needs generated files).
char gChatStr_Empty_19[4] __attribute__((aligned(4))) = "";
#pragma explicit_zero_data reset

// 0x02255A30
// C declares this as `const char gChatStr_ClientDataNeNULL[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_ClientDataNeNULL[20] __attribute__((aligned(4))) = "clientData != NULL";

// 0x02255A44
// C declares this as `const char gChatStr_UserNameNeNULL[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_UserNameNeNULL[20] __attribute__((aligned(4))) = "user->name != NULL";

// 0x02255A58
// C declares this as `const char gChatStr_UserName0_Ne0[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_UserName0_Ne0[24] __attribute__((aligned(4))) = "user->name[0] != '\\0'";

// 0x02255A70
// C declares this as `const char gChatStr_StrlenUserNameLtMAX_NAME[]`, but s2c could not read that
// type (its header needs generated files).
char gChatStr_StrlenUserNameLtMAX_NAME[32] __attribute__((aligned(4))) = "strlen(user->name) < MAX_NAME";

// 0x02255A90
// C declares this as `const char gChatStr_DataNumUsersGe0[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_DataNumUsersGe0[20] __attribute__((aligned(4))) = "data->numUsers >= 0";

// 0x02255AA4
// C declares this as `const char gChatStr_0_9[]`, but s2c could not read that type (its header needs
// generated files).
char gChatStr_0_9[4] __attribute__((aligned(4))) = "0";

// 0x02255AA8
// C declares this as `const char gChatStr_CallbackNeNULL_3[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_CallbackNeNULL_3[20] __attribute__((aligned(4))) = "callback != NULL";

// 0x02255ABC
// C declares this as `const char gChatStr_NameNeNULL[]`, but s2c could not read that type (its header
// needs generated files).
char gChatStr_NameNeNULL[16] __attribute__((aligned(4))) = "name != NULL";

// 0x02255ACC
// C declares this as `const char gChatStr_Name0_Ne0[]`, but s2c could not read that type (its header
// needs generated files).
char gChatStr_Name0_Ne0[16] __attribute__((aligned(4))) = "name[0] != '\\0'";

// 0x02255ADC
// C declares this as `const char gChatStr_StrlenNameLtMAX_NAME[]`, but s2c could not read that type
// (its header needs generated files).
char gChatStr_StrlenNameLtMAX_NAME[24] __attribute__((aligned(4))) = "strlen(name) < MAX_NAME";

// 0x02255AF4
// C declares this as `const char gChatStr_ModeGe0_AndModeLe3[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_ModeGe0_AndModeLe3[28] __attribute__((aligned(4))) = "(mode >= 0) && (mode <= 3)";

// 0x02255B10
// C declares this as `const char gChatStr_TableLookupChatChannelUsersChatUserNeNULL[]`, but s2c could
// not read that type (its header needs generated files).
char gChatStr_TableLookupChatChannelUsersChatUserNeNULL[52] __attribute__((aligned(4))) = "TableLookup(chatChannel->users, &chatUser) != NULL";

// 0x02255B44
// C declares this as `const char gChatStr_UserNeNULL[]`, but s2c could not read that type (its header
// needs generated files).
char gChatStr_UserNeNULL[16] __attribute__((aligned(4))) = "user != NULL";

// 0x02255B54
// C declares this as `const char gChatStr_User0_Ne0[]`, but s2c could not read that type (its header
// needs generated files).
char gChatStr_User0_Ne0[16] __attribute__((aligned(4))) = "user[0] != '\\0'";

// 0x02255B64
// C declares this as `const char gChatStr_StrlenUserLtMAX_NAME[]`, but s2c could not read that type
// (its header needs generated files).
char gChatStr_StrlenUserLtMAX_NAME[24] __attribute__((aligned(4))) = "strlen(user) < MAX_NAME";

// 0x02255B7C
// C declares this as `const char gChatStr_ChannelUsersNeNULL[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_ChannelUsersNeNULL[24] __attribute__((aligned(4))) = "channel->users != NULL";

// 0x02255B94
// C declares this as `const char gChatStr_DataUserNeNULL[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_DataUserNeNULL[20] __attribute__((aligned(4))) = "data->user != NULL";

// 0x02255BA8
// C declares this as `const char gChatStr_DataUserName0_Ne0[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_DataUserName0_Ne0[28] __attribute__((aligned(4))) = "data->user->name[0] != '\\0'";

// 0x02255BC4
// C declares this as `const char gChatStr_DataCallbackNeNULL_2[]`, but s2c could not read that type
// (its header needs generated files).
char gChatStr_DataCallbackNeNULL_2[24] __attribute__((aligned(4))) = "data->callback != NULL";

// 0x02255BDC
// C declares this as `const char gChatStr_DataNewNickNeNULL[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_DataNewNickNeNULL[24] __attribute__((aligned(4))) = "data->newNick != NULL";

// 0x02255BF4
// C declares this as `const char gChatStr_DataNewNick0_Ne0[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_DataNewNick0_Ne0[28] __attribute__((aligned(4))) = "data->newNick[0] != '\\0'";

// 0x02255C10
// C declares this as `const char gChatStr_StrlenDataNewNickLtMAX_NAME[]`, but s2c could not read that
// type (its header needs generated files).
char gChatStr_StrlenDataNewNickLtMAX_NAME[36] __attribute__((aligned(4))) = "strlen(data->newNick) < MAX_NAME";

// 0x02255C34
// C declares this as `const char gChatStr_DataOldNickNeNULL[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_DataOldNickNeNULL[24] __attribute__((aligned(4))) = "data->oldNick != NULL";

// 0x02255C4C
// C declares this as `const char gChatStr_DataOldNick0_Ne0[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_DataOldNick0_Ne0[28] __attribute__((aligned(4))) = "data->oldNick[0] != '\\0'";

// 0x02255C68
// C declares this as `const char gChatStr_StrlenDataOldNickLtMAX_NAME[]`, but s2c could not read that
// type (its header needs generated files).
char gChatStr_StrlenDataOldNickLtMAX_NAME[36] __attribute__((aligned(4))) = "strlen(data->oldNick) < MAX_NAME";

// 0x02255C8C
// C declares this as `const char gChatStr_RcodeNe0[]`, but s2c could not read that type (its header
// needs generated files).
char gChatStr_RcodeNe0[12] __attribute__((aligned(4))) = "rcode != 0";

// 0x02255C98
// C declares this as `const char gChatStr_OldNickNeNULL[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_OldNickNeNULL[16] __attribute__((aligned(4))) = "oldNick != NULL";

// 0x02255CA8
// C declares this as `const char gChatStr_OldNick0_Ne0[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_OldNick0_Ne0[20] __attribute__((aligned(4))) = "oldNick[0] != '\\0'";

// 0x02255CBC
// C declares this as `const char gChatStr_StrlenOldNickLtMAX_NAME[]`, but s2c could not read that type
// (its header needs generated files).
char gChatStr_StrlenOldNickLtMAX_NAME[28] __attribute__((aligned(4))) = "strlen(oldNick) < MAX_NAME";

// 0x02255CD8
// C declares this as `const char gChatStr_NewNickNeNULL[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_NewNickNeNULL[16] __attribute__((aligned(4))) = "newNick != NULL";

// 0x02255CE8
// C declares this as `const char gChatStr_NewNick0_Ne0[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_NewNick0_Ne0[20] __attribute__((aligned(4))) = "newNick[0] != '\\0'";

// 0x02255CFC
// C declares this as `const char gChatStr_StrlenNewNickLtMAX_NAME[]`, but s2c could not read that type
// (its header needs generated files).
char gChatStr_StrlenNewNickLtMAX_NAME[28] __attribute__((aligned(4))) = "strlen(newNick) < MAX_NAME";

// 0x02255D18
// C declares this as `const char gChatStr_NickNeNULL[]`, but s2c could not read that type (its header
// needs generated files).
char gChatStr_NickNeNULL[16] __attribute__((aligned(4))) = "nick != NULL";

// 0x02255D28
// C declares this as `const char gChatStr_Nick0_Ne0[]`, but s2c could not read that type (its header
// needs generated files).
char gChatStr_Nick0_Ne0[16] __attribute__((aligned(4))) = "nick[0] != '\\0'";

// 0x02255D38
// C declares this as `const char gChatStr_StrlenNickLtMAX_NAME[]`, but s2c could not read that type
// (its header needs generated files).
char gChatStr_StrlenNickLtMAX_NAME[24] __attribute__((aligned(4))) = "strlen(nick) < MAX_NAME";

static char gLobbyStr_475[4] __attribute__((aligned(4))) = "475";

static char gLobbyStr_302[4] __attribute__((aligned(4))) = "302";

static char gLobbyStr_401[4] __attribute__((aligned(4))) = "401";

static char gLobbyStr_UTM[4] __attribute__((aligned(4))) = "UTM";

static char gLobbyStr_366[4] __attribute__((aligned(4))) = "366";

static char gLobbyStr_701[4] __attribute__((aligned(4))) = "701";

static char gLobbyStr_433[4] __attribute__((aligned(4))) = "433";

static char gLobbyStr_707[4] __attribute__((aligned(4))) = "707";

static char gLobbyStr_352[4] __attribute__((aligned(4))) = "352";

static char gLobbyStr_711[4] __attribute__((aligned(4))) = "711";

static char gLobbyStr_323[4] __attribute__((aligned(4))) = "323";

static char gLobbyStr_476[4] __attribute__((aligned(4))) = "476";

static char gLobbyStr_324[4] __attribute__((aligned(4))) = "324";

static char gLobbyStr_704[4] __attribute__((aligned(4))) = "704";

static char gLobbyStr_474[4] __attribute__((aligned(4))) = "474";

static char gLobbyStr_705[4] __attribute__((aligned(4))) = "705";

static char gLobbyStr_405[4] __attribute__((aligned(4))) = "405";

static char gLobbyStr_702[4] __attribute__((aligned(4))) = "702";

static char gLobbyStr_471[4] __attribute__((aligned(4))) = "471";

static char gLobbyStr_331[4] __attribute__((aligned(4))) = "331";

// 0x02255DA0
// C declares this as `int ciNumServerMessageHandlers`, but s2c could not read that type (its header
// needs generated files).
char ciNumServerMessageHandlers[4] __attribute__((aligned(4))) = "6";

static char gLobbyStr_473[4] __attribute__((aligned(4))) = "473";

static char gLobbyStr_353[4] __attribute__((aligned(4))) = "353";

static char gLobbyStr_319[4] __attribute__((aligned(4))) = "319";

static char gLobbyStr_001[4] __attribute__((aligned(4))) = "001";

static char gLobbyStr_332[4] __attribute__((aligned(4))) = "332";

static char gLobbyStr_318[4] __attribute__((aligned(4))) = "318";

static char gLobbyStr_322[4] __attribute__((aligned(4))) = "322";

static char gLobbyStr_700[4] __attribute__((aligned(4))) = "700";

static char gLobbyStr_321[4] __attribute__((aligned(4))) = "321";

static char gLobbyStr_703[4] __attribute__((aligned(4))) = "703";

static char gLobbyStr_706[4] __attribute__((aligned(4))) = "706";

static char gLobbyStr_432[4] __attribute__((aligned(4))) = "432";

static char gLobbyStr_311[4] __attribute__((aligned(4))) = "311";

static char gLobbyStr_367[4] __attribute__((aligned(4))) = "367";

static char gLobbyStr_315[4] __attribute__((aligned(4))) = "315";

static char gLobbyStr_ATM[4] __attribute__((aligned(4))) = "ATM";

static char gLobbyStr_368[4] __attribute__((aligned(4))) = "368";

static char gLobbyStr_708[4] __attribute__((aligned(4))) = "708";

static char gLobbyStr_710[4] __attribute__((aligned(4))) = "710";

static char gLobbyStr_709[4] __attribute__((aligned(4))) = "709";

static char gLobbyStr_403[4] __attribute__((aligned(4))) = "403";

static char gLobbyStr_MODE[8] __attribute__((aligned(4))) = "MODE";

static char gLobbyStr_KICK[8] __attribute__((aligned(4))) = "KICK";

static char gLobbyStr_NICK[8] __attribute__((aligned(4))) = "NICK";

static char gLobbyStr_PART[8] __attribute__((aligned(4))) = "PART";

static char gLobbyStr_QUIT[8] __attribute__((aligned(4))) = "QUIT";

static char gLobbyStr_JOIN[8] __attribute__((aligned(4))) = "JOIN";

static char gLobbyStr_KILL[8] __attribute__((aligned(4))) = "KILL";

static char gLobbyStr_PING[8] __attribute__((aligned(4))) = "PING";

static char gLobbyStr_TOPIC[8] __attribute__((aligned(4))) = "TOPIC";

static char gLobbyStr_ERROR[8] __attribute__((aligned(4))) = "ERROR";

static char gLobbyStr_INVITE[8] __attribute__((aligned(4))) = "INVITE";

static char gLobbyStr_NOTICE[8] __attribute__((aligned(4))) = "NOTICE";

static char gLobbyStr_PRIVMSG[8] __attribute__((aligned(4))) = "PRIVMSG";

// 0x02255E60
// C declares this as `const char gChatStr_ciGetNextID[]`, but s2c could not read that type (its header
// needs generated files).
char gChatStr_ciGetNextID[12] __attribute__((aligned(4))) = "ciGetNextID";

// 0x02255E6C
// C declares this as `const char gChatStr_ciAddFilter[]`, but s2c could not read that type (its header
// needs generated files).
char gChatStr_ciAddFilter[12] __attribute__((aligned(4))) = "ciAddFilter";

// 0x02255E78
// C declares this as `const char gChatStr_ciParseMode[]`, but s2c could not read that type (its header
// needs generated files).
char gChatStr_ciParseMode[12] __attribute__((aligned(4))) = "ciParseMode";

// 0x02255E84
// C declares this as `const char gChatStr_ciParseValue[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_ciParseValue[16] __attribute__((aligned(4))) = "ciParseValue";

// 0x02255E94
// C declares this as `const char gChatStr_ciUTMHandler[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_ciUTMHandler[16] __attribute__((aligned(4))) = "ciUTMHandler";

// 0x02255EA4
// C declares this as `const char gChatStr_ciATMHandler[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_ciATMHandler[16] __attribute__((aligned(4))) = "ciATMHandler";

// 0x02255EB4
// C declares this as `const char gChatStr_ciFindFilter[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_ciFindFilter[16] __attribute__((aligned(4))) = "ciFindFilter";

// 0x02255EC4
// C declares this as `const char gChatStr_ciFilterThink[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_ciFilterThink[16] __attribute__((aligned(4))) = "ciFilterThink";

// 0x02255ED4
// C declares this as `const char gChatStr_ciPingHandler[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_ciPingHandler[16] __attribute__((aligned(4))) = "ciPingHandler";

// 0x02255EE4
// C declares this as `const char gChatStr_ciNickHandler[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_ciNickHandler[16] __attribute__((aligned(4))) = "ciNickHandler";

// 0x02255EF4
// C declares this as `const char gChatStr_ciJoinHandler[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_ciJoinHandler[16] __attribute__((aligned(4))) = "ciJoinHandler";

// 0x02255F04
// C declares this as `const char gChatStr_ciPartHandler[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_ciPartHandler[16] __attribute__((aligned(4))) = "ciPartHandler";

// 0x02255F14
// C declares this as `const char gChatStr_ciKickHandler[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_ciKickHandler[16] __attribute__((aligned(4))) = "ciKickHandler";

// 0x02255F24
// C declares this as `const char gChatStr_ciQuitHandler[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_ciQuitHandler[16] __attribute__((aligned(4))) = "ciQuitHandler";

// 0x02255F34
// C declares this as `const char gChatStr_ciKillHandler[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_ciKillHandler[16] __attribute__((aligned(4))) = "ciKillHandler";

// 0x02255F44
// C declares this as `const char gChatStr_ciModeHandler[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_ciModeHandler[16] __attribute__((aligned(4))) = "ciModeHandler";

// 0x02255F54
// C declares this as `const char gChatStr_ciTopicHandler[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_ciTopicHandler[16] __attribute__((aligned(4))) = "ciTopicHandler";

// 0x02255F64
// C declares this as `const char gChatStr_ciErrorHandler[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_ciErrorHandler[16] __attribute__((aligned(4))) = "ciErrorHandler";

// 0x02255F74
// C declares this as `const char gChatStr_ciRemoveFilter[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_ciRemoveFilter[16] __attribute__((aligned(4))) = "ciRemoveFilter";

// 0x02255F84
// C declares this as `const char gChatStr_ciFinishFilter[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_ciFinishFilter[16] __attribute__((aligned(4))) = "ciFinishFilter";

// 0x02255F94
// C declares this as `const char gChatStr_ciAddJOINFilter[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_ciAddJOINFilter[16] __attribute__((aligned(4))) = "ciAddJOINFilter";

// 0x02255FA4
// C declares this as `const char gChatStr_ciNoticeHandler[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_ciNoticeHandler[16] __attribute__((aligned(4))) = "ciNoticeHandler";

// 0x02255FB4
// C declares this as `const char gChatStr_ciInviteHandler[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_ciInviteHandler[16] __attribute__((aligned(4))) = "ciInviteHandler";

// 0x02255FC4
// C declares this as `const char gChatStr_ciDestroyFilter[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_ciDestroyFilter[16] __attribute__((aligned(4))) = "ciDestroyFilter";

// 0x02255FD4
// C declares this as `const char gChatStr_ciCleanupFilters[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_ciCleanupFilters[20] __attribute__((aligned(4))) = "ciCleanupFilters";

// 0x02255FE8
// C declares this as `const char gChatStr_ciPrivmsgHandler[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_ciPrivmsgHandler[20] __attribute__((aligned(4))) = "ciPrivmsgHandler";

// 0x02255FFC
// C declares this as `const char gChatStr_ciRplListHandler[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_ciRplListHandler[20] __attribute__((aligned(4))) = "ciRplListHandler";

// 0x02256010
// C declares this as `const char gChatStr_ciFilterTimedout[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_ciFilterTimedout[20] __attribute__((aligned(4))) = "ciFilterTimedout";

// 0x02256024
// C declares this as `const char gChatStr_ciRplCDKeyHandler[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_ciRplCDKeyHandler[20] __attribute__((aligned(4))) = "ciRplCDKeyHandler";

// 0x02256038
// C declares this as `const char gChatStr_ciRplLoginHandler[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_ciRplLoginHandler[20] __attribute__((aligned(4))) = "ciRplLoginHandler";

// 0x0225604C
// C declares this as `const char gChatStr_ciRplTopicHandler[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_ciRplTopicHandler[20] __attribute__((aligned(4))) = "ciRplTopicHandler";

// 0x02256060
// C declares this as `const char gChatStr_ciRplGetKeyHandler[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_ciRplGetKeyHandler[20] __attribute__((aligned(4))) = "ciRplGetKeyHandler";

// 0x02256074
// C declares this as `const char gChatStr_ciRplUserIPHandler[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_ciRplUserIPHandler[20] __attribute__((aligned(4))) = "ciRplUserIPHandler";

// 0x02256088
// C declares this as `const char gChatStr_ciNameReplyHandler[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_ciNameReplyHandler[20] __attribute__((aligned(4))) = "ciNameReplyHandler";

// 0x0225609C
// C declares this as `const char gChatStr_ciFindGetKeyFilter[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_ciFindGetKeyFilter[20] __attribute__((aligned(4))) = "ciFindGetKeyFilter";

// 0x022560B0
// C declares this as `const char gChatStr_ciCheckFiltersForID[]`, but s2c could not read that type
// (its header needs generated files).
char gChatStr_ciCheckFiltersForID[20] __attribute__((aligned(4))) = "ciCheckFiltersForID";

// 0x022560C4
// C declares this as `const char gChatStr_ciRplGetCKeyHandler[]`, but s2c could not read that type
// (its header needs generated files).
char gChatStr_ciRplGetCKeyHandler[20] __attribute__((aligned(4))) = "ciRplGetCKeyHandler";

// 0x022560D8
// C declares this as `const char gChatStr_ciEndOfNamesHandler[]`, but s2c could not read that type
// (its header needs generated files).
char gChatStr_ciEndOfNamesHandler[20] __attribute__((aligned(4))) = "ciEndOfNamesHandler";

// 0x022560EC
// C declares this as `const char gChatStr_ciRplBanListHandler[]`, but s2c could not read that type
// (its header needs generated files).
char gChatStr_ciRplBanListHandler[20] __attribute__((aligned(4))) = "ciRplBanListHandler";

// 0x02256100
// C declares this as `const char gChatStr_ciRplNoTopicHandler[]`, but s2c could not read that type
// (its header needs generated files).
char gChatStr_ciRplNoTopicHandler[20] __attribute__((aligned(4))) = "ciRplNoTopicHandler";

// 0x02256114
// C declares this as `const char gChatStr_ciRplWelcomeHandler[]`, but s2c could not read that type
// (its header needs generated files).
char gChatStr_ciRplWelcomeHandler[20] __attribute__((aligned(4))) = "ciRplWelcomeHandler";

// 0x02256128
// C declares this as `const char gChatStr_ciApplyChangesToMode[]`, but s2c could not read that type
// (its header needs generated files).
char gChatStr_ciApplyChangesToMode[24] __attribute__((aligned(4))) = "ciApplyChangesToMode";

// 0x02256140
// C declares this as `const char gChatStr_ciRplWhoReplyHandler[]`, but s2c could not read that type
// (its header needs generated files).
char gChatStr_ciRplWhoReplyHandler[24] __attribute__((aligned(4))) = "ciRplWhoReplyHandler";

// 0x02256158
// C declares this as `const char gChatStr_ciRplEndOfWhoHandler[]`, but s2c could not read that type
// (its header needs generated files).
char gChatStr_ciRplEndOfWhoHandler[24] __attribute__((aligned(4))) = "ciRplEndOfWhoHandler";

// 0x02256170
// C declares this as `const char gChatStr_ciRplSecureKeyHandler[]`, but s2c could not read that type
// (its header needs generated files).
char gChatStr_ciRplSecureKeyHandler[24] __attribute__((aligned(4))) = "ciRplSecureKeyHandler";

// 0x02256188
// C declares this as `const char gChatStr_ciRplEndGetKeyHandler[]`, but s2c could not read that type
// (its header needs generated files).
char gChatStr_ciRplEndGetKeyHandler[24] __attribute__((aligned(4))) = "ciRplEndGetKeyHandler";

// 0x022561A0
// C declares this as `const char gChatStr_ciRplListStartHandler[]`, but s2c could not read that type
// (its header needs generated files).
char gChatStr_ciRplListStartHandler[24] __attribute__((aligned(4))) = "ciRplListStartHandler";

// 0x022561B8
// C declares this as `const char gChatStr_ciRplWhoisUserHandler[]`, but s2c could not read that type
// (its header needs generated files).
char gChatStr_ciRplWhoisUserHandler[24] __attribute__((aligned(4))) = "ciRplWhoisUserHandler";

// 0x022561D0
// C declares this as `const char gChatStr_ciErrNickInUseHandler[]`, but s2c could not read that type
// (its header needs generated files).
char gChatStr_ciErrNickInUseHandler[24] __attribute__((aligned(4))) = "ciErrNickInUseHandler";

// 0x022561E8
// C declares this as `const char gChatStr_ciRplEndGetCKeyHandler[]`, but s2c could not read that type
// (its header needs generated files).
char gChatStr_ciRplEndGetCKeyHandler[24] __attribute__((aligned(4))) = "ciRplEndGetCKeyHandler";

// 0x02256200
// C declares this as `const char gChatStr_ciRplGetChanKeyHandler[]`, but s2c could not read that type
// (its header needs generated files).
char gChatStr_ciRplGetChanKeyHandler[24] __attribute__((aligned(4))) = "ciRplGetChanKeyHandler";

// 0x02256218
// C declares this as `const char gChatStr_ciRplEndOfWhoisHandler[]`, but s2c could not read that type
// (its header needs generated files).
char gChatStr_ciRplEndOfWhoisHandler[24] __attribute__((aligned(4))) = "ciRplEndOfWhoisHandler";

// 0x02256230
// C declares this as `const char gChatStr_ciErrBadChanMaskHandler[]`, but s2c could not read that type
// (its header needs generated files).
char gChatStr_ciErrBadChanMaskHandler[24] __attribute__((aligned(4))) = "ciErrBadChanMaskHandler";

// 0x02256248
// C declares this as `const char gChatStr_ciErrLoginFailedHandler[]`, but s2c could not read that type
// (its header needs generated files).
char gChatStr_ciErrLoginFailedHandler[24] __attribute__((aligned(4))) = "ciErrLoginFailedHandler";

// 0x02256260
// C declares this as `const char gChatStr_ciErrNoUniqueNickHandler[]`, but s2c could not read that
// type (its header needs generated files).
char gChatStr_ciErrNoUniqueNickHandler[28] __attribute__((aligned(4))) = "ciErrNoUniqueNickHandler";

// 0x0225627C
// C declares this as `const char gChatStr_ciRplEndOfBanListHandler[]`, but s2c could not read that
// type (its header needs generated files).
char gChatStr_ciRplEndOfBanListHandler[28] __attribute__((aligned(4))) = "ciRplEndOfBanListHandler";

// 0x02256298
// C declares this as `const char gChatStr_ciErrBadChannelKeyHandler[]`, but s2c could not read that
// type (its header needs generated files).
char gChatStr_ciErrBadChannelKeyHandler[28] __attribute__((aligned(4))) = "ciErrBadChannelKeyHandler";

// 0x022562B4
// C declares this as `const char gChatStr_ciErrNoSuchChannelHandler[]`, but s2c could not read that
// type (its header needs generated files).
char gChatStr_ciErrNoSuchChannelHandler[28] __attribute__((aligned(4))) = "ciErrNoSuchChannelHandler";

// 0x022562D0
// C declares this as `const char gChatStr_ciRplChannelModeIsHandler[]`, but s2c could not read that
// type (its header needs generated files).
char gChatStr_ciRplChannelModeIsHandler[28] __attribute__((aligned(4))) = "ciRplChannelModeIsHandler";

// 0x022562EC
// C declares this as `const char gChatStr_ciRplWhoisChannelsHandler[]`, but s2c could not read that
// type (its header needs generated files).
char gChatStr_ciRplWhoisChannelsHandler[28] __attribute__((aligned(4))) = "ciRplWhoisChannelsHandler";

// 0x02256308
// C declares this as `const char gChatStr_ciErrChannelIsFullHandler[]`, but s2c could not read that
// type (its header needs generated files).
char gChatStr_ciErrChannelIsFullHandler[28] __attribute__((aligned(4))) = "ciErrChannelIsFullHandler";

// 0x02256324
// C declares this as `const char gChatStr_ciQuitEnumChannelsCallback[]`, but s2c could not read that
// type (its header needs generated files).
char gChatStr_ciQuitEnumChannelsCallback[28] __attribute__((aligned(4))) = "ciQuitEnumChannelsCallback";

// 0x02256340
// C declares this as `const char gChatStr_ciKillEnumChannelsCallback[]`, but s2c could not read that
// type (its header needs generated files).
char gChatStr_ciKillEnumChannelsCallback[28] __attribute__((aligned(4))) = "ciKillEnumChannelsCallback";

// 0x0225635C
// C declares this as `const char gChatStr_ciErrInviteOnlyChanHandler[]`, but s2c could not read that
// type (its header needs generated files).
char gChatStr_ciErrInviteOnlyChanHandler[28] __attribute__((aligned(4))) = "ciErrInviteOnlyChanHandler";

// 0x02256378
// C declares this as `const char gChatStr_ciErrBannedFromChanHandler[]`, but s2c could not read that
// type (its header needs generated files).
char gChatStr_ciErrBannedFromChanHandler[28] __attribute__((aligned(4))) = "ciErrBannedFromChanHandler";

// 0x02256394
// C declares this as `const char gChatStr_ciErrTooManyChannelsHandler[]`, but s2c could not read that
// type (its header needs generated files).
char gChatStr_ciErrTooManyChannelsHandler[28] __attribute__((aligned(4))) = "ciErrTooManyChannelsHandler";

// 0x022563B0
// C declares this as `const char gChatStr_ciErrErroneusNicknameHandler[]`, but s2c could not read that
// type (its header needs generated files).
char gChatStr_ciErrErroneusNicknameHandler[32] __attribute__((aligned(4))) = "ciErrErroneusNicknameHandler";

// 0x022563D0
// C declares this as `const char gChatStr_ciErrUniqueNickExpiredHandler[]`, but s2c could not read
// that type (its header needs generated files).
char gChatStr_ciErrUniqueNickExpiredHandler[32] __attribute__((aligned(4))) = "ciErrUniqueNickExpiredHandler";

// 0x022563F0
// C declares this as `const char gChatStr_ciErrRegisterNickFailedHandler[]`, but s2c could not read
// that type (its header needs generated files).
char gChatStr_ciErrRegisterNickFailedHandler[32] __attribute__((aligned(4))) = "ciErrRegisterNickFailedHandler";

// 0x02256410
// C declares this as `ChatServerCommand ciServerMessageHandlers[]`, but s2c could not read that type
// (its header needs generated files).
const void *ciServerMessageHandlers[108] = {
    gLobbyStr_PRIVMSG,
    (const void *)ciPrivmsgHandler,
    gLobbyStr_NOTICE,
    (const void *)ciNoticeHandler,
    gLobbyStr_UTM,
    (const void *)ciUTMHandler,
    gLobbyStr_ATM,
    (const void *)ciATMHandler,
    gLobbyStr_PING,
    (const void *)ciPingHandler,
    gLobbyStr_NICK,
    (const void *)ciNickHandler,
    gLobbyStr_JOIN,
    (const void *)ciJoinHandler,
    gLobbyStr_PART,
    (const void *)ciPartHandler,
    gLobbyStr_KICK,
    (const void *)ciKickHandler,
    gLobbyStr_QUIT,
    (const void *)ciQuitHandler,
    gLobbyStr_KILL,
    (const void *)ciKillHandler,
    gLobbyStr_TOPIC,
    (const void *)ciTopicHandler,
    gLobbyStr_MODE,
    (const void *)ciModeHandler,
    gLobbyStr_ERROR,
    (const void *)ciErrorHandler,
    gLobbyStr_INVITE,
    (const void *)ciInviteHandler,
    gLobbyStr_353,
    (const void *)ciNameReplyHandler,
    gLobbyStr_366,
    (const void *)ciEndOfNamesHandler,
    gLobbyStr_332,
    (const void *)ciRplTopicHandler,
    gLobbyStr_331,
    (const void *)ciRplNoTopicHandler,
    gLobbyStr_352,
    (const void *)ciRplWhoReplyHandler,
    gLobbyStr_302,
    (const void *)ciRplUserIPHandler,
    gLobbyStr_321,
    (const void *)ciRplListStartHandler,
    gLobbyStr_322,
    (const void *)ciRplListHandler,
    gLobbyStr_323,
    (const void *)ciRplListEndHandler,
    gLobbyStr_324,
    (const void *)ciRplChannelModeIsHandler,
    gLobbyStr_311,
    (const void *)ciRplWhoisUserHandler,
    gLobbyStr_319,
    (const void *)ciRplWhoisChannelsHandler,
    gLobbyStr_318,
    (const void *)ciRplEndOfWhoisHandler,
    gLobbyStr_367,
    (const void *)ciRplBanListHandler,
    gLobbyStr_368,
    (const void *)ciRplEndOfBanListHandler,
    gLobbyStr_001,
    (const void *)ciRplWelcomeHandler,
    gLobbyStr_315,
    (const void *)ciRplEndOfWhoHandler,
    gLobbyStr_700,
    (const void *)ciRplGetKeyHandler,
    gLobbyStr_701,
    (const void *)ciRplEndGetKeyHandler,
    gLobbyStr_702,
    (const void *)ciRplGetCKeyHandler,
    gLobbyStr_703,
    (const void *)ciRplEndGetCKeyHandler,
    gLobbyStr_704,
    (const void *)ciRplGetChanKeyHandler,
    gLobbyStr_705,
    (const void *)ciRplSecureKeyHandler,
    gLobbyStr_706,
    (const void *)ciRplCDKeyHandler,
    gLobbyStr_707,
    (const void *)ciRplLoginHandler,
    gLobbyStr_433,
    (const void *)ciErrNickInUseHandler,
    gLobbyStr_403,
    (const void *)ciErrNoSuchChannelHandler,
    gLobbyStr_405,
    (const void *)ciErrTooManyChannelsHandler,
    gLobbyStr_471,
    (const void *)ciErrChannelIsFullHandler,
    gLobbyStr_473,
    (const void *)ciErrInviteOnlyChanHandler,
    gLobbyStr_474,
    (const void *)ciErrBannedFromChanHandler,
    gLobbyStr_475,
    (const void *)ciErrBadChannelKeyHandler,
    gLobbyStr_476,
    (const void *)ciErrBadChanMaskHandler,
    gLobbyStr_401,
    (const void *)ciErrNoSuchNickHandler,
    gLobbyStr_432,
    (const void *)ciErrErroneusNicknameHandler,
    gLobbyStr_708,
    (const void *)ciErrLoginFailedHandler,
    gLobbyStr_709,
    (const void *)ciErrNoUniqueNickHandler,
    gLobbyStr_710,
    (const void *)ciErrUniqueNickExpiredHandler,
    gLobbyStr_711,
    (const void *)ciErrRegisterNickFailedHandler,
};

// 0x022565C0
// C declares this as `const char gChatStr_ChatNeNULL_3[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_ChatNeNULL_3[16] __attribute__((aligned(4))) = "chat != NULL";

// 0x022565D0
// C declares this as `const char gChatStr_ChatHandlersC[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_ChatHandlersC[16] __attribute__((aligned(4))) = "chatHandlers.c";

// 0x022565E0
// C declares this as `const char gChatStr_NumMatchesGt0[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_NumMatchesGt0[16] __attribute__((aligned(4))) = "numMatches > 0";

// 0x022565F0
// C declares this as `const char gChatStr_matches[]`, but s2c could not read that type (its header
// needs generated files).
char gChatStr_matches[8] __attribute__((aligned(4))) = "matches";

// 0x022565F8
// C declares this as `const char gChatStr_MatchesI_TypeGe0_AndMatchesI_TypeLtNUM_TYPES[]`, but s2c
// could not read that type (its header needs generated files).
char gChatStr_MatchesI_TypeGe0_AndMatchesI_TypeLtNUM_TYPES[56] __attribute__((aligned(4))) = "(matches[i].type >= 0) && (matches[i].type < NUM_TYPES)";

// 0x02256630
// C declares this as `const char gChatStr_channel[]`, but s2c could not read that type (its header
// needs generated files).
char gChatStr_channel[8] __attribute__((aligned(4))) = "channel";

// 0x02256638
// C declares this as `const char gChatStr_Channel0[]`, but s2c could not read that type (its header
// needs generated files).
char gChatStr_Channel0[12] __attribute__((aligned(4))) = "channel[0]";

// 0x02256644
// C declares this as `const char gChatStr_FilterNeNULL[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_FilterNeNULL[16] __attribute__((aligned(4))) = "filter != NULL";

// 0x02256654
// C declares this as `const char gChatStr_filter[]`, but s2c could not read that type (its header
// needs generated files).
char gChatStr_filter[8] __attribute__((aligned(4))) = "filter";

// 0x0225665C
// C declares this as `const char gChatStr_FilterTypeGe0_AndFilterTypeLtNUM_TYPES[]`, but s2c could not
// read that type (its header needs generated files).
char gChatStr_FilterTypeGe0_AndFilterTypeLtNUM_TYPES[52] __attribute__((aligned(4))) = "(filter->type >= 0) && (filter->type < NUM_TYPES)";

// 0x02256690
// C declares this as `const char gChatStr_0_10[]`, but s2c could not read that type (its header needs
// generated files).
char gChatStr_0_10[4] __attribute__((aligned(4))) = "0";

// 0x02256694
// C declares this as `const char gChatStr_TimedOut[]`, but s2c could not read that type (its header
// needs generated files).
char gChatStr_TimedOut[12] __attribute__((aligned(4))) = "Timed out";

// 0x022566A0
// C declares this as `const char gChatStr_ID_Gt0[]`, but s2c could not read that type (its header
// needs generated files).
char gChatStr_ID_Gt0[8] __attribute__((aligned(4))) = "ID > 0";

// 0x022566A8
// C declares this as `const char gChatStr_PasswordNeNULL[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_PasswordNeNULL[20] __attribute__((aligned(4))) = "password != NULL";

// 0x022566BC
// C declares this as `const char gChatStr_StrlenPasswordLtMAX_PASSWORD[]`, but s2c could not read that
// type (its header needs generated files).
char gChatStr_StrlenPasswordLtMAX_PASSWORD[32] __attribute__((aligned(4))) = "strlen(password) < MAX_PASSWORD";

// 0x022566DC
// C declares this as `const char gChatStr_B_UnderscoreStar[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_B_UnderscoreStar[4] __attribute__((aligned(4))) = "b_*";

// 0x022566E0
// C declares this as `const char gChatStr_ModeNeNULL[]`, but s2c could not read that type (its header
// needs generated files).
char gChatStr_ModeNeNULL[16] __attribute__((aligned(4))) = "mode != NULL";

// 0x022566F0
// C declares this as `const char gChatStr_MessageNumParamsEq2[]`, but s2c could not read that type
// (its header needs generated files).
char gChatStr_MessageNumParamsEq2[24] __attribute__((aligned(4))) = "message->numParams == 2";

#pragma explicit_zero_data on
// 0x02256708
// C declares this as `const char gChatStr_Empty_20[]`, but s2c could not read that type (its header
// needs generated files).
char gChatStr_Empty_20[4] __attribute__((aligned(4))) = "";
#pragma explicit_zero_data reset

// 0x0225670C
// C declares this as `const char gChatStr_ACTION[]`, but s2c could not read that type (its header
// needs generated files).
char gChatStr_ACTION[8] __attribute__((aligned(4))) = "ACTION";

// 0x02256714
// C declares this as `const char gChatFmt_PONG[]`, but s2c could not read that type (its header needs
// generated files).
char gChatFmt_PONG[8] __attribute__((aligned(4))) = "PONG %s";

// 0x0225671C
// C declares this as `const char gChatStr_MessageNumParamsEq1[]`, but s2c could not read that type
// (its header needs generated files).
char gChatStr_MessageNumParamsEq1[24] __attribute__((aligned(4))) = "message->numParams == 1";

// 0x02256734
// C declares this as `const char gChatStr_StrlenNewNickLtMAX_NICK[]`, but s2c could not read that type
// (its header needs generated files).
char gChatStr_StrlenNewNickLtMAX_NICK[28] __attribute__((aligned(4))) = "strlen(newNick) < MAX_NICK";

// 0x02256750
// C declares this as `const char gChatStr_NickNe0[]`, but s2c could not read that type (its header
// needs generated files).
char gChatStr_NickNe0[16] __attribute__((aligned(4))) = "*nick != '\\0'";

// 0x02256760
// C declares this as `const char gChatFmt_MODE[]`, but s2c could not read that type (its header needs
// generated files).
char gChatFmt_MODE[8] __attribute__((aligned(4))) = "MODE %s";

// 0x02256768
// C declares this as `const char gChatStr_MessageNumParamsEq2_OrMessageNumParamsEq3[]`, but s2c could
// not read that type (its header needs generated files).
char gChatStr_MessageNumParamsEq2_OrMessageNumParamsEq3[56] __attribute__((aligned(4))) = "(message->numParams == 2) || (message->numParams == 3)";

// 0x022567A0
// C declares this as `const char gChatStr_UserNeNULL_2[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_UserNeNULL_2[16] __attribute__((aligned(4))) = "user != NULL";

// 0x022567B0
// C declares this as `const char gChatStr_User0_Ne0_2[]`, but s2c could not read that type (its header
// needs generated files).
char gChatStr_User0_Ne0_2[16] __attribute__((aligned(4))) = "user[0] != '\\0'";

// 0x022567C0
// C declares this as `const char gChatStr_ChannelNeNULL_2[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_ChannelNeNULL_2[16] __attribute__((aligned(4))) = "channel != NULL";

// 0x022567D0
// C declares this as `const char gChatStr_Channel0_Ne0_2[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_Channel0_Ne0_2[20] __attribute__((aligned(4))) = "channel[0] != '\\0'";

// 0x022567E4
// C declares this as `const char gChatStr_ReasonNeNULL[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_ReasonNeNULL[16] __attribute__((aligned(4))) = "reason != NULL";

// 0x022567F4
// C declares this as `const char gChatStr_MessageNumParamsGe2[]`, but s2c could not read that type
// (its header needs generated files).
char gChatStr_MessageNumParamsGe2[24] __attribute__((aligned(4))) = "message->numParams >= 2";

// 0x0225680C
// C declares this as `const char gChatStr_MessageNumParamsEq4[]`, but s2c could not read that type
// (its header needs generated files).
char gChatStr_MessageNumParamsEq4[24] __attribute__((aligned(4))) = "message->numParams == 4";

// 0x02256824
// C declares this as `const char gChatStr_Space_3[]`, but s2c could not read that type (its header
// needs generated files).
char gChatStr_Space_3[4] __attribute__((aligned(4))) = " ";

// 0x02256828
// C declares this as `const char gChatStr_Nick0_Ne0_2[]`, but s2c could not read that type (its header
// needs generated files).
char gChatStr_Nick0_Ne0_2[16] __attribute__((aligned(4))) = "nick[0] != '\\0'";

// 0x02256838
// C declares this as `const char gChatStr_Nick1_Ne0[]`, but s2c could not read that type (its header
// needs generated files).
char gChatStr_Nick1_Ne0[16] __attribute__((aligned(4))) = "nick[1] != '\\0'";

// 0x02256848
// C declares this as `const char gChatStr_MessageNumParamsEq3[]`, but s2c could not read that type
// (its header needs generated files).
char gChatStr_MessageNumParamsEq3[24] __attribute__((aligned(4))) = "message->numParams == 3";

// 0x02256860
// C declares this as `const char gChatStr_Star_2[]`, but s2c could not read that type (its header
// needs generated files).
char gChatStr_Star_2[4] __attribute__((aligned(4))) = "*";

// 0x02256864
// C declares this as `const char gChatStr_ConnectionConnecting[]`, but s2c could not read that type
// (its header needs generated files).
char gChatStr_ConnectionConnecting[24] __attribute__((aligned(4))) = "connection->connecting";

// 0x0225687C
// C declares this as `const char gChatStr_MessageNumParamsEq8[]`, but s2c could not read that type
// (its header needs generated files).
char gChatStr_MessageNumParamsEq8[24] __attribute__((aligned(4))) = "message->numParams == 8";

// 0x02256894
// C declares this as `const char gChatStr_flags[]`, but s2c could not read that type (its header needs
// generated files).
char gChatStr_flags[8] __attribute__((aligned(4))) = "flags";

// 0x0225689C
// C declares this as `const char gChatStr_len[]`, but s2c could not read that type (its header needs
// generated files).
char gChatStr_len[4] __attribute__((aligned(4))) = "len";

// 0x022568A0
// C declares this as `const char gChatStr_MessageNumParamsEq5[]`, but s2c could not read that type
// (its header needs generated files).
char gChatStr_MessageNumParamsEq5[24] __attribute__((aligned(4))) = "message->numParams == 5";

// 0x022568B8
// C declares this as `const char gChatStr_BCAST[]`, but s2c could not read that type (its header needs
// generated files).
char gChatStr_BCAST[8] __attribute__((aligned(4))) = "BCAST";

// 0x022568C0
// C declares this as `const char gChatStr_b_[]`, but s2c could not read that type (its header needs
// generated files).
char gChatStr_b_[4] __attribute__((aligned(4))) = "b_";

// 0x022568C4
// C declares this as `const char gChatStr_MessageNumParamsGe1[]`, but s2c could not read that type
// (its header needs generated files).
char gChatStr_MessageNumParamsGe1[24] __attribute__((aligned(4))) = "message->numParams >= 1";

// 0x022568DC
// C declares this as `const char gChatStr_DataNeNULL_2[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_DataNeNULL_2[16] __attribute__((aligned(4))) = "data != NULL";

// 0x022568EC
// C declares this as `const char gChatStr_MessageNumParamsGe3[]`, but s2c could not read that type
// (its header needs generated files).
char gChatStr_MessageNumParamsGe3[24] __attribute__((aligned(4))) = "message->numParams >=3";

// 0x02256904
// C declares this as `const char gChatStr_MessageNumParamsEq6[]`, but s2c could not read that type
// (its header needs generated files).
char gChatStr_MessageNumParamsEq6[24] __attribute__((aligned(4))) = "message->numParams == 6";

// 0x0225691C
// C declares this as `const char gChatStr_DataChannelNeNULL[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_DataChannelNeNULL[24] __attribute__((aligned(4))) = "data->channel != NULL";

// 0x02256934
// C declares this as `const char gChatStr_DataChannel0_Ne0[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_DataChannel0_Ne0[28] __attribute__((aligned(4))) = "data->channel[0] != '\\0'";

// 0x02256950
// C declares this as `const char gChatFmt_MODE_B[]`, but s2c could not read that type (its header
// needs generated files).
char gChatFmt_MODE_B[20] __attribute__((aligned(4))) = "MODE %s +b *!*@%s";

// 0x02256964
// C declares this as `const char gChatStr_MessageNumParamsGe3_2[]`, but s2c could not read that type
// (its header needs generated files).
char gChatStr_MessageNumParamsGe3_2[24] __attribute__((aligned(4))) = "message->numParams >= 3";

// 0x0225697C
// C declares this as `const char gChatStr_DataNumBansGe0[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_DataNumBansGe0[20] __attribute__((aligned(4))) = "data->numBans >= 0";

// 0x02256990
// C declares this as `const char gChatStr_USRIP[]`, but s2c could not read that type (its header needs
// generated files).
char gChatStr_USRIP[8] __attribute__((aligned(4))) = "USRIP";

// 0x02256998
// C declares this as `const char gChatStr_Backslash_2[]`, but s2c could not read that type (its header
// needs generated files).
char gChatStr_Backslash_2[4] __attribute__((aligned(4))) = "\\";

// 0x0225699C
// C declares this as `int gChatCryptVersion`, but s2c could not read that type (its header needs
// generated files).
char gChatCryptVersion[4] __attribute__((aligned(4))) = "\001";

// 0x022569A0
// C declares this as `const char gChatStr_ciThink[]`, but s2c could not read that type (its header
// needs generated files).
char gChatStr_ciThink[8] __attribute__((aligned(4))) = "ciThink";

// 0x022569A8
// C declares this as `const char gChatStr_ciSendNick[]`, but s2c could not read that type (its header
// needs generated files).
char gChatStr_ciSendNick[12] __attribute__((aligned(4))) = "ciSendNick";

// 0x022569B4
// C declares this as `const char gChatStr_ciSendUser[]`, but s2c could not read that type (its header
// needs generated files).
char gChatStr_ciSendUser[12] __attribute__((aligned(4))) = "ciSendUser";

// 0x022569C0
// C declares this as `const char gChatStr_ciNickError[]`, but s2c could not read that type (its header
// needs generated files).
char gChatStr_ciNickError[12] __attribute__((aligned(4))) = "ciNickError";

// 0x022569CC
// C declares this as `const char gChatStr_ciSendLogin[]`, but s2c could not read that type (its header
// needs generated files).
char gChatStr_ciSendLogin[12] __attribute__((aligned(4))) = "ciSendLogin";

// 0x022569D8
// C declares this as `const char gChatStr_chatInChannelA[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_chatInChannelA[16] __attribute__((aligned(4))) = "chatInChannelA";

// 0x022569E8
// C declares this as `const char gChatStr_chatDisconnect[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_chatDisconnect[16] __attribute__((aligned(4))) = "chatDisconnect";

// 0x022569F8
// C declares this as `const char gChatStr_chatEnumUsersA[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_chatEnumUsersA[16] __attribute__((aligned(4))) = "chatEnumUsersA";

// 0x02256A08
// C declares this as `const char gChatStr_chatConnectDoit[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_chatConnectDoit[16] __attribute__((aligned(4))) = "chatConnectDoit";

// 0x02256A18
// C declares this as `const char gChatStr_chatEnumChannelsA[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_chatEnumChannelsA[20] __attribute__((aligned(4))) = "chatEnumChannelsA";

// 0x02256A2C
// C declares this as `const char gChatStr_chatEnterChannelA[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_chatEnterChannelA[20] __attribute__((aligned(4))) = "chatEnterChannelA";

// 0x02256A40
// C declares this as `const char gChatStr_chatLeaveChannelA[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_chatLeaveChannelA[20] __attribute__((aligned(4))) = "chatLeaveChannelA";

// 0x02256A54
// C declares this as `const char gChatStr_ciHandleDisconnect[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_ciHandleDisconnect[20] __attribute__((aligned(4))) = "ciHandleDisconnect";

// 0x02256A68
// C declares this as `const char gChatStr_chatRetryWithNickA[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_chatRetryWithNickA[20] __attribute__((aligned(4))) = "chatRetryWithNickA";

// 0x02256A7C
// C declares this as `const char gChatStr_ciSendGetChannelKey[]`, but s2c could not read that type
// (its header needs generated files).
char gChatStr_ciSendGetChannelKey[20] __attribute__((aligned(4))) = "ciSendGetChannelKey";

// 0x02256A90
// C declares this as `const char gChatStr_ciEnumUsersCallback[]`, but s2c could not read that type
// (its header needs generated files).
char gChatStr_ciEnumUsersCallback[20] __attribute__((aligned(4))) = "ciEnumUsersCallback";

// 0x02256AA4
// C declares this as `const char gChatStr_chatGetChannelKeysA[]`, but s2c could not read that type
// (its header needs generated files).
char gChatStr_chatGetChannelKeysA[20] __attribute__((aligned(4))) = "chatGetChannelKeysA";

// 0x02256AB8
// C declares this as `const char gChatStr_chatSetChannelKeysA[]`, but s2c could not read that type
// (its header needs generated files).
char gChatStr_chatSetChannelKeysA[20] __attribute__((aligned(4))) = "chatSetChannelKeysA";

// 0x02256ACC
// C declares this as `const char gChatStr_chatSetChannelModeA[]`, but s2c could not read that type
// (its header needs generated files).
char gChatStr_chatSetChannelModeA[20] __attribute__((aligned(4))) = "chatSetChannelModeA";

// 0x02256AE0
// C declares this as `const char gChatStr_chatGetChannelModeA[]`, but s2c could not read that type
// (its header needs generated files).
char gChatStr_chatGetChannelModeA[20] __attribute__((aligned(4))) = "chatGetChannelModeA";

// 0x02256AF4
// C declares this as `const char gChatStr_chatSetChannelLimitA[]`, but s2c could not read that type
// (its header needs generated files).
char gChatStr_chatSetChannelLimitA[24] __attribute__((aligned(4))) = "chatSetChannelLimitA";

// 0x02256B0C
// C declares this as `const char gChatStr_chatSendUserMessageA[]`, but s2c could not read that type
// (its header needs generated files).
char gChatStr_chatSendUserMessageA[24] __attribute__((aligned(4))) = "chatSendUserMessageA";

// 0x02256B24
// C declares this as `const char gChatStr_ciProcessServerMessage[]`, but s2c could not read that type
// (its header needs generated files).
char gChatStr_ciProcessServerMessage[24] __attribute__((aligned(4))) = "ciProcessServerMessage";

// 0x02256B3C
// C declares this as `const char gChatStr_chatRegisterUniqueNickA[]`, but s2c could not read that type
// (its header needs generated files).
char gChatStr_chatRegisterUniqueNickA[24] __attribute__((aligned(4))) = "chatRegisterUniqueNickA";

// 0x02256B54
// C declares this as `const char gChatStr_chatGetChannelNumUsersA[]`, but s2c could not read that type
// (its header needs generated files).
char gChatStr_chatGetChannelNumUsersA[24] __attribute__((aligned(4))) = "chatGetChannelNumUsersA";

// 0x02256B6C
// C declares this as `const char gChatStr_chatSendChannelMessageA[]`, but s2c could not read that type
// (its header needs generated files).
char gChatStr_chatSendChannelMessageA[24] __attribute__((aligned(4))) = "chatSendChannelMessageA";

// 0x02256B84
// C declares this as `const char gChatStr_MessageNeNULL_2[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_MessageNeNULL_2[16] __attribute__((aligned(4))) = "message != NULL";

// 0x02256B94
// C declares this as `const char gChatStr_ChatMainC[]`, but s2c could not read that type (its header
// needs generated files).
char gChatStr_ChatMainC[12] __attribute__((aligned(4))) = "chatMain.c";

// 0x02256BA0
// C declares this as `const char gChatStr_ChatNeNULL_4[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_ChatNeNULL_4[16] __attribute__((aligned(4))) = "chat != NULL";

// 0x02256BB0
// C declares this as `const char gChatStr_Disconnected[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_Disconnected[16] __attribute__((aligned(4))) = "Disconnected";

// 0x02256BC0
// C declares this as `const ChatBytes2 gChatStr_Star_3`, but s2c could not read that type (its header
// needs generated files).
char gChatStr_Star_3[4] __attribute__((aligned(4))) = "*";

// 0x02256BC4
// C declares this as `const char gChatFmt_NICK[]`, but s2c could not read that type (its header needs
// generated files).
char gChatFmt_NICK[8] __attribute__((aligned(4))) = "NICK %s";

// 0x02256BCC
// C declares this as `const char gChatFmt_USER[]`, but s2c could not read that type (its header needs
// generated files).
char gChatFmt_USER[20] __attribute__((aligned(4))) = "USER %s %s %s :%s";

// 0x02256BE0
// C declares this as `const char gChatStr_127_Dot0_Dot0_Dot1[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_127_Dot0_Dot0_Dot1[12] __attribute__((aligned(4))) = "127.0.0.1";

// 0x02256BEC
// C declares this as `const char gChatFmt_LOGINPREAUTH[]`, but s2c could not read that type (its
// header needs generated files).
char gChatFmt_LOGINPREAUTH[20] __attribute__((aligned(4))) = "LOGINPREAUTH %s %s";

// 0x02256C00
// C declares this as `const char gChatFmt_LOGIN[]`, but s2c could not read that type (its header needs
// generated files).
char gChatFmt_LOGIN[16] __attribute__((aligned(4))) = "LOGIN %d %s %s";

// 0x02256C10
// C declares this as `const char gChatFmt_LOGIN_2[]`, but s2c could not read that type (its header
// needs generated files).
char gChatFmt_LOGIN_2[24] __attribute__((aligned(4))) = "LOGIN %d * %s :%s@%s";

// 0x02256C28
// C declares this as `const char gChatStr_0_11[]`, but s2c could not read that type (its header needs
// generated files).
char gChatStr_0_11[4] __attribute__((aligned(4))) = "0";

#pragma explicit_zero_data on
// 0x02256C2C
// C declares this as `const char gChatStr_Empty_21[]`, but s2c could not read that type (its header
// needs generated files).
char gChatStr_Empty_21[4] __attribute__((aligned(4))) = "";
#pragma explicit_zero_data reset

// 0x02256C30
// C declares this as `const char gChatStr_ServerAddressNeNULL[]`, but s2c could not read that type
// (its header needs generated files).
char gChatStr_ServerAddressNeNULL[24] __attribute__((aligned(4))) = "serverAddress != NULL";

// 0x02256C48
// C declares this as `const char gChatStr_CallbacksNeNULL_2[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_CallbacksNeNULL_2[20] __attribute__((aligned(4))) = "callbacks != NULL";

// 0x02256C5C
// C declares this as `const char gChatStr_ConnectCallbackNeNULL[]`, but s2c could not read that type
// (its header needs generated files).
char gChatStr_ConnectCallbackNeNULL[24] __attribute__((aligned(4))) = "connectCallback != NULL";

// 0x02256C74
// C declares this as `const char gChatStr_NickNeNULL_2[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_NickNeNULL_2[16] __attribute__((aligned(4))) = "nick != NULL";

// 0x02256C84
// C declares this as `const char gChatStr_Nick0_Ne0_3[]`, but s2c could not read that type (its header
// needs generated files).
char gChatStr_Nick0_Ne0_3[16] __attribute__((aligned(4))) = "nick[0] != '\\0'";

// 0x02256C94
// C declares this as `const char gChatStr_StrlenNickLtMAX_NICK[]`, but s2c could not read that type
// (its header needs generated files).
char gChatStr_StrlenNickLtMAX_NICK[24] __attribute__((aligned(4))) = "strlen(nick) < MAX_NICK";

// 0x02256CAC
// C declares this as `const char gChatStr_NamespaceID_Gt0[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_NamespaceID_Gt0[16] __attribute__((aligned(4))) = "namespaceID > 0";

// 0x02256CBC
// C declares this as `const char gChatStr_UniquenickAndUniquenick0[]`, but s2c could not read that
// type (its header needs generated files).
char gChatStr_UniquenickAndUniquenick0[28] __attribute__((aligned(4))) = "uniquenick && uniquenick[0]";

// 0x02256CD8
// C declares this as `const char gChatStr_PasswordAndPassword0[]`, but s2c could not read that type
// (its header needs generated files).
char gChatStr_PasswordAndPassword0[24] __attribute__((aligned(4))) = "password && password[0]";

// 0x02256CF0
// C declares this as `const char gChatStr_NamespaceID_Ge0[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_NamespaceID_Ge0[20] __attribute__((aligned(4))) = "namespaceID >= 0";

// 0x02256D04
// C declares this as `const char gChatStr_EmailAndEmail0[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_EmailAndEmail0[20] __attribute__((aligned(4))) = "email && email[0]";

// 0x02256D18
// C declares this as `const char gChatStr_ProfilenickAndProfilenick0[]`, but s2c could not read that
// type (its header needs generated files).
char gChatStr_ProfilenickAndProfilenick0[32] __attribute__((aligned(4))) = "profilenick && profilenick[0]";

// 0x02256D38
// C declares this as `const char gChatStr_AuthtokenAndAuthtoken0[]`, but s2c could not read that type
// (its header needs generated files).
char gChatStr_AuthtokenAndAuthtoken0[28] __attribute__((aligned(4))) = "authtoken && authtoken[0]";

// 0x02256D54
// C declares this as `const char gChatStr_PartnerchallengeAndPartnerchallenge0[]`, but s2c could not
// read that type (its header needs generated files).
char gChatStr_PartnerchallengeAndPartnerchallenge0[40] __attribute__((aligned(4))) = "partnerchallenge && partnerchallenge[0]";

// 0x02256D7C
// C declares this as `const char gChatStr_preauth[]`, but s2c could not read that type (its header
// needs generated files).
char gChatStr_preauth[8] __attribute__((aligned(4))) = "preauth";

// 0x02256D84
// C declares this as `const char gChatStr_GamenameAndGamename0[]`, but s2c could not read that type
// (its header needs generated files).
char gChatStr_GamenameAndGamename0[24] __attribute__((aligned(4))) = "gamename && gamename[0]";

// 0x02256D9C
// C declares this as `const char gChatStr_SecretKeyAndSecretKey0[]`, but s2c could not read that type
// (its header needs generated files).
char gChatStr_SecretKeyAndSecretKey0[28] __attribute__((aligned(4))) = "secretKey && secretKey[0]";

// 0x02256DB8
// C declares this as `const char gChatFmt_CRYPT_Des[]`, but s2c could not read that type (its header
// needs generated files).
char gChatFmt_CRYPT_Des[16] __attribute__((aligned(4))) = "CRYPT des %d %s";

// 0x02256DC8
// C declares this as `const char gChatStr_USRIP_2[]`, but s2c could not read that type (its header
// needs generated files).
char gChatStr_USRIP_2[8] __attribute__((aligned(4))) = "USRIP";

// 0x02256DD0
// C declares this as `const char gChatFmt_NICK_2[]`, but s2c could not read that type (its header
// needs generated files).
char gChatFmt_NICK_2[12] __attribute__((aligned(4))) = "NICK :%s";

// 0x02256DDC
// C declares this as `const char gChatFmt_REGISTERNICK[]`, but s2c could not read that type (its
// header needs generated files).
char gChatFmt_REGISTERNICK[24] __attribute__((aligned(4))) = "REGISTERNICK %d %s %s";

// 0x02256DF4
// C declares this as `const char gChatStr_QUIT_Later[]`, but s2c could not read that type (its header
// needs generated files).
char gChatStr_QUIT_Later[16] __attribute__((aligned(4))) = "QUIT :Later!";

// 0x02256E04
// C declares this as `const char gChatStr_ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuv_3[]`, but
// s2c could not read that type (its header needs generated files).
char gChatStr_ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuv_3[96] __attribute__((aligned(4))) = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789\"#$%&'()*+,-./:;<=>?@[]^_`{|}~";

// 0x02256E64
// C declares this as `const char gChatStr_CallbackAllNeNULL_OrCallbackEachNeNULL[]`, but s2c could not
// read that type (its header needs generated files).
char gChatStr_CallbackAllNeNULL_OrCallbackEachNeNULL[48] __attribute__((aligned(4))) = "(callbackAll != NULL) || (callbackEach != NULL)";

// 0x02256E94
// C declares this as `const char gChatFmt_LIST[]`, but s2c could not read that type (its header needs
// generated files).
char gChatFmt_LIST[8] __attribute__((aligned(4))) = "LIST %s";

// 0x02256E9C
// C declares this as `const char gChatStr_ChannelNeNULL_3[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_ChannelNeNULL_3[16] __attribute__((aligned(4))) = "channel != NULL";

// 0x02256EAC
// C declares this as `const char gChatStr_Channel0_Ne0_3[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_Channel0_Ne0_3[20] __attribute__((aligned(4))) = "channel[0] != '\\0'";

// 0x02256EC0
// C declares this as `const char gChatFmt_JOIN[]`, but s2c could not read that type (its header needs
// generated files).
char gChatFmt_JOIN[12] __attribute__((aligned(4))) = "JOIN %s %s";

// 0x02256ECC
// C declares this as `const char gChatFmt_PART[]`, but s2c could not read that type (its header needs
// generated files).
char gChatFmt_PART[12] __attribute__((aligned(4))) = "PART %s :%s";

// 0x02256ED8
// C declares this as `const char gChatStr_TypeEqCHAT_MESSAGE_OrTypeEqCHAT_ACTION_OrTypeEq[]`, but s2c
// could not read that type (its header needs generated files).
char gChatStr_TypeEqCHAT_MESSAGE_OrTypeEqCHAT_ACTION_OrTypeEq[120] __attribute__((aligned(4))) = "(type == CHAT_MESSAGE) || (type == CHAT_ACTION) || (type == CHAT_NOTICE) || (type == CHAT_UTM) || (type == CHAT_ATM)";

// 0x02256F50
// C declares this as `const char gChatFmt_PRIVMSG[]`, but s2c could not read that type (its header
// needs generated files).
char gChatFmt_PRIVMSG[16] __attribute__((aligned(4))) = "PRIVMSG %s :%s";

// 0x02256F60
// C declares this as `const char gChatFmt_PRIVMSG_ACTION[]`, but s2c could not read that type (its
// header needs generated files).
char gChatFmt_PRIVMSG_ACTION[24] __attribute__((aligned(4))) = "PRIVMSG %s :\001ACTION %s\001";

// 0x02256F78
// C declares this as `const char gChatFmt_NOTICE[]`, but s2c could not read that type (its header
// needs generated files).
char gChatFmt_NOTICE[16] __attribute__((aligned(4))) = "NOTICE %s :%s";

// 0x02256F88
// C declares this as `const char gChatFmt_UTM[]`, but s2c could not read that type (its header needs
// generated files).
char gChatFmt_UTM[12] __attribute__((aligned(4))) = "UTM %s :%s";

// 0x02256F94
// C declares this as `const char gChatFmt_ATM[]`, but s2c could not read that type (its header needs
// generated files).
char gChatFmt_ATM[12] __attribute__((aligned(4))) = "ATM %s :%s";

// 0x02256FA0
// C declares this as `const char gChatStr_CallbackNeNULL_4[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_CallbackNeNULL_4[20] __attribute__((aligned(4))) = "callback != NULL";

// 0x02256FB4
// C declares this as `const char gChatStr_ModeNeNULL_2[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_ModeNeNULL_2[16] __attribute__((aligned(4))) = "mode != NULL";

// 0x02256FC4
// C declares this as `const char gChatStr_XiXpXsXmXnXtXlXe[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_XiXpXsXmXnXtXlXe[20] __attribute__((aligned(4))) = "XiXpXsXmXnXtXlXe";

// 0x02256FD8
// C declares this as `const char gChatFmt_SpaceInt[]`, but s2c could not read that type (its header
// needs generated files).
char gChatFmt_SpaceInt[4] __attribute__((aligned(4))) = " %d";

// 0x02256FDC
// C declares this as `const char gChatFmt_MODE_2[]`, but s2c could not read that type (its header
// needs generated files).
char gChatFmt_MODE_2[12] __attribute__((aligned(4))) = "MODE %s %s";

// 0x02256FE8
// C declares this as `const char gChatFmt_MODE_3[]`, but s2c could not read that type (its header
// needs generated files).
char gChatFmt_MODE_3[8] __attribute__((aligned(4))) = "MODE %s";

// 0x02256FF0
// C declares this as `const char gChatStr_LimitGe0[]`, but s2c could not read that type (its header
// needs generated files).
char gChatStr_LimitGe0[12] __attribute__((aligned(4))) = "limit >= 0";

// 0x02256FFC
// C declares this as `const char gChatFmt_MODE_L[]`, but s2c could not read that type (its header
// needs generated files).
char gChatFmt_MODE_L[16] __attribute__((aligned(4))) = "MODE %s +l %d";

// 0x0225700C
// C declares this as `const char gChatFmt_MODE_L_2[]`, but s2c could not read that type (its header
// needs generated files).
char gChatFmt_MODE_L_2[12] __attribute__((aligned(4))) = "MODE %s -l";

// 0x02257018
// C declares this as `const char gChatStr_NumUsersGe0[]`, but s2c could not read that type (its header
// needs generated files).
char gChatStr_NumUsersGe0[16] __attribute__((aligned(4))) = "numUsers >= 0";

// 0x02257028
// C declares this as `const char gChatStr_ParamNeNULL[]`, but s2c could not read that type (its header
// needs generated files).
char gChatStr_ParamNeNULL[16] __attribute__((aligned(4))) = "param != NULL";

// 0x02257038
// C declares this as `const char gChatStr_DataCallbackNeNULL_3[]`, but s2c could not read that type
// (its header needs generated files).
char gChatStr_DataCallbackNeNULL_3[24] __attribute__((aligned(4))) = "data->callback != NULL";

// 0x02257050
// C declares this as `const char gChatFmt_NAMES[]`, but s2c could not read that type (its header needs
// generated files).
char gChatFmt_NAMES[12] __attribute__((aligned(4))) = "NAMES %s";

// 0x0225705C
// C declares this as `const char gChatStr_UserNeNULL_3[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_UserNeNULL_3[16] __attribute__((aligned(4))) = "user != NULL";

// 0x0225706C
// C declares this as `const char gChatStr_User0_Ne0_3[]`, but s2c could not read that type (its header
// needs generated files).
char gChatStr_User0_Ne0_3[16] __attribute__((aligned(4))) = "user[0] != '\\0'";

// 0x0225707C
// C declares this as `const char gChatStr_StrlenUserLtMAX_USER[]`, but s2c could not read that type
// (its header needs generated files).
char gChatStr_StrlenUserLtMAX_USER[24] __attribute__((aligned(4))) = "strlen(user) < MAX_USER";

// 0x02257094
// C declares this as `const char gChatFmt_BackslashStrBackslashStr[]`, but s2c could not read that
// type (its header needs generated files).
char gChatFmt_BackslashStrBackslashStr[8] __attribute__((aligned(4))) = "\\%s\\%s";

// 0x0225709C
// C declares this as `const char gChatFmt_Int_6[]`, but s2c could not read that type (its header needs
// generated files).
char gChatFmt_Int_6[8] __attribute__((aligned(4))) = "%03d";

// 0x022570A4
// C declares this as `const char gChatStr_CookieAndCookie0[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_CookieAndCookie0[20] __attribute__((aligned(4))) = "cookie && cookie[0]";

// 0x022570B8
// C declares this as `const char gChatStr_NumGe0[]`, but s2c could not read that type (its header
// needs generated files).
char gChatStr_NumGe0[12] __attribute__((aligned(4))) = "num >= 0";

// 0x022570C4
// C declares this as `const char gChatFmt_SETCHANKEY[]`, but s2c could not read that type (its header
// needs generated files).
char gChatFmt_SETCHANKEY[16] __attribute__((aligned(4))) = "SETCHANKEY %s :";

// 0x022570D4
// C declares this as `const char gChatFmt_SETCKEY[]`, but s2c could not read that type (its header
// needs generated files).
char gChatFmt_SETCKEY[16] __attribute__((aligned(4))) = "SETCKEY %s %s :";

// 0x022570E4
// C declares this as `const char gChatStr_ChannelAndChannel0[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_ChannelAndChannel0[24] __attribute__((aligned(4))) = "channel && channel[0]";

// 0x022570FC
// C declares this as `const char gChatStr_NotNumOrKeys[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_NotNumOrKeys[16] __attribute__((aligned(4))) = "!num || keys";

// 0x0225710C
// C declares this as `const char gChatFmt_GETCHANKEY_0[]`, but s2c could not read that type (its
// header needs generated files).
char gChatFmt_GETCHANKEY_0[24] __attribute__((aligned(4))) = "GETCHANKEY %s %s 0 :";

// 0x02257124
// C declares this as `const char gChatFmt_GETCKEY_0[]`, but s2c could not read that type (its header
// needs generated files).
char gChatFmt_GETCKEY_0[24] __attribute__((aligned(4))) = "GETCKEY %s %s %s 0 :";

// 0x0225713C
// C declares this as `const char gChatStr_B_UnderscoreStar_2[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_B_UnderscoreStar_2[4] __attribute__((aligned(4))) = "b_*";

// 0x02257140
char gChatStr_BackslashB_UnderscoreStar[8] __attribute__((aligned(4))) = "\\b_*";

// 0x02257148
// C declares this as `const char gChatStr_ciParseUser[]`, but s2c could not read that type (its header
// needs generated files).
char gChatStr_ciParseUser[12] __attribute__((aligned(4))) = "ciParseUser";

// 0x02257154
// C declares this as `const char gChatStr_ciSocketSend[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_ciSocketSend[16] __attribute__((aligned(4))) = "ciSocketSend";

// 0x02257164
// C declares this as `const char gChatStr_ciSocketRecv[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_ciSocketRecv[16] __attribute__((aligned(4))) = "ciSocketRecv";

// 0x02257174
// C declares this as `const char gChatStr_ciBufferInit[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_ciBufferInit[16] __attribute__((aligned(4))) = "ciBufferInit";

// 0x02257184
// C declares this as `const char gChatStr_ciParseParam[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_ciParseParam[16] __attribute__((aligned(4))) = "ciParseParam";

// 0x02257194
// C declares this as `const char gChatStr_ciSocketInit[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_ciSocketInit[16] __attribute__((aligned(4))) = "ciSocketInit";

// 0x022571A4
// C declares this as `const char gChatStr_ciSocketSendf[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_ciSocketSendf[16] __attribute__((aligned(4))) = "ciSocketSendf";

// 0x022571B4
// C declares this as `const char gChatStr_ciSocketThink[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_ciSocketThink[16] __attribute__((aligned(4))) = "ciSocketThink";

// 0x022571C4
// C declares this as `const char gChatStr_ciParseMessage[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_ciParseMessage[16] __attribute__((aligned(4))) = "ciParseMessage";

// 0x022571D4
// C declares this as `const char gChatStr_ciSocketConnect[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_ciSocketConnect[16] __attribute__((aligned(4))) = "ciSocketConnect";

// 0x022571E4
// C declares this as `const char gChatStr_ciBufferPreAppend[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_ciBufferPreAppend[20] __attribute__((aligned(4))) = "ciBufferPreAppend";

// 0x022571F8
// C declares this as `const char gChatStr_ciBufferClipFront[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_ciBufferClipFront[20] __attribute__((aligned(4))) = "ciBufferClipFront";

// 0x0225720C
// C declares this as `const char gChatStr_ciSocketThinkSend[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_ciSocketThinkSend[20] __attribute__((aligned(4))) = "ciSocketThinkSend";

// 0x02257220
// C declares this as `const char gChatStr_ciSocketThinkRecv[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_ciSocketThinkRecv[20] __attribute__((aligned(4))) = "ciSocketThinkRecv";

// 0x02257234
// C declares this as `const char gChatStr_ciSocketDisconnect[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_ciSocketDisconnect[20] __attribute__((aligned(4))) = "ciSocketDisconnect";

// 0x02257248
// C declares this as `const char gChatStr_BufferNeNULL_2[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_BufferNeNULL_2[16] __attribute__((aligned(4))) = "buffer != NULL";

// 0x02257258
// C declares this as `const char gChatStr_ChatSocketC[]`, but s2c could not read that type (its header
// needs generated files).
char gChatStr_ChatSocketC[16] __attribute__((aligned(4))) = "chatSocket.c";

// 0x02257268
// C declares this as `const char gChatStr_BufferNeNULL_3[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_BufferNeNULL_3[20] __attribute__((aligned(4))) = "(buffer) != NULL";

// 0x0225727C
// C declares this as `const char gChatStr_BufferSizeGe0[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_BufferSizeGe0[20] __attribute__((aligned(4))) = "(buffer)->size >= 0";

// 0x02257290
// C declares this as `const char gChatStr_BufferSizeBUFFER_INC_Eq0[]`, but s2c could not read that
// type (its header needs generated files).
char gChatStr_BufferSizeBUFFER_INC_Eq0[36] __attribute__((aligned(4))) = "((buffer)->size % BUFFER_INC) == 0";

// 0x022572B4
// C declares this as `const char gChatStr_BufferLengthGe0[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_BufferLengthGe0[24] __attribute__((aligned(4))) = "(buffer)->length >= 0";

// 0x022572CC
// C declares this as `const char gChatStr_BufferLengthLeBufferSize[]`, but s2c could not read that
// type (its header needs generated files).
char gChatStr_BufferLengthLeBufferSize[36] __attribute__((aligned(4))) = "(buffer)->length <= (buffer)->size";

// 0x022572F0
// C declares this as `const char gChatStr_LenGe0_2[]`, but s2c could not read that type (its header
// needs generated files).
char gChatStr_LenGe0_2[12] __attribute__((aligned(4))) = "len >= 0";

// 0x022572FC
// C declares this as `const char gChatStr_LenLeSHRT_MAX[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_LenLeSHRT_MAX[16] __attribute__((aligned(4))) = "len <= SHRT_MAX";

// 0x0225730C
// C declares this as `const char gChatStr_LenLeBufferLength[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_LenLeBufferLength[24] __attribute__((aligned(4))) = "len <= buffer->length";

// 0x02257324
// C declares this as `const char gChatStr_SockNeNULL[]`, but s2c could not read that type (its header
// needs generated files).
char gChatStr_SockNeNULL[16] __attribute__((aligned(4))) = "sock != NULL";

// 0x02257334
// C declares this as `const char gChatStr_SockNeNULL_2[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_SockNeNULL_2[16] __attribute__((aligned(4))) = "(sock) != NULL";

// 0x02257344
// C declares this as `const char gChatStr_SockConnectStateEqCiNotConnectedOrSock[]`, but s2c could not
// read that type (its header needs generated files).
char gChatStr_SockConnectStateEqCiNotConnectedOrSock[128] __attribute__((aligned(4))) = "((sock)->connectState == ciNotConnected) || ((sock)->connectState == ciConnected) || ((sock)->connectState == ciDisconnected)";

// 0x022573C4
// C declares this as `const char gChatStr_SockInputQueueNeNULL[]`, but s2c could not read that type
// (its header needs generated files).
char gChatStr_SockInputQueueNeNULL[32] __attribute__((aligned(4))) = "(&(sock)->inputQueue) != NULL";

// 0x022573E4
// C declares this as `const char gChatStr_SockInputQueueSizeGe0[]`, but s2c could not read that type
// (its header needs generated files).
char gChatStr_SockInputQueueSizeGe0[36] __attribute__((aligned(4))) = "(&(sock)->inputQueue)->size >= 0";

// 0x02257408
// C declares this as `const char gChatStr_SockInputQueueSizeBUFFER_INC_Eq0[]`, but s2c could not read
// that type (its header needs generated files).
char gChatStr_SockInputQueueSizeBUFFER_INC_Eq0[48] __attribute__((aligned(4))) = "((&(sock)->inputQueue)->size % BUFFER_INC) == 0";

// 0x02257438
// C declares this as `const char gChatStr_SockInputQueueLengthGe0[]`, but s2c could not read that type
// (its header needs generated files).
char gChatStr_SockInputQueueLengthGe0[36] __attribute__((aligned(4))) = "(&(sock)->inputQueue)->length >= 0";

// 0x0225745C
// C declares this as `const char gChatStr_SockInputQueueLengthLeSockInputQueueSize[]`, but s2c could
// not read that type (its header needs generated files).
char gChatStr_SockInputQueueLengthLeSockInputQueueSize[64] __attribute__((aligned(4))) = "(&(sock)->inputQueue)->length <= (&(sock)->inputQueue)->size";

// 0x0225749C
// C declares this as `const char gChatStr_SockOutputQueueNeNULL[]`, but s2c could not read that type
// (its header needs generated files).
char gChatStr_SockOutputQueueNeNULL[32] __attribute__((aligned(4))) = "(&(sock)->outputQueue) != NULL";

// 0x022574BC
// C declares this as `const char gChatStr_SockOutputQueueSizeGe0[]`, but s2c could not read that type
// (its header needs generated files).
char gChatStr_SockOutputQueueSizeGe0[36] __attribute__((aligned(4))) = "(&(sock)->outputQueue)->size >= 0";

// 0x022574E0
// C declares this as `const char gChatStr_SockOutputQueueSizeBUFFER_INC_Eq0[]`, but s2c could not read
// that type (its header needs generated files).
char gChatStr_SockOutputQueueSizeBUFFER_INC_Eq0[52] __attribute__((aligned(4))) = "((&(sock)->outputQueue)->size % BUFFER_INC) == 0";

// 0x02257514
// C declares this as `const char gChatStr_SockOutputQueueLengthGe0[]`, but s2c could not read that
// type (its header needs generated files).
char gChatStr_SockOutputQueueLengthGe0[36] __attribute__((aligned(4))) = "(&(sock)->outputQueue)->length >= 0";

// 0x02257538
// C declares this as `const char gChatStr_SockOutputQueueLengthLeSockOutputQueueSize[]`, but s2c could
// not read that type (its header needs generated files).
char gChatStr_SockOutputQueueLengthLeSockOutputQueueSize[64] __attribute__((aligned(4))) = "(&(sock)->outputQueue)->length <= (&(sock)->outputQueue)->size";

// 0x02257578
// C declares this as `const char gChatStr_ServerAddressNeNULL_2[]`, but s2c could not read that type
// (its header needs generated files).
char gChatStr_ServerAddressNeNULL_2[24] __attribute__((aligned(4))) = "serverAddress != NULL";

// 0x02257590
// C declares this as `const char gChatStr_PortGe0[]`, but s2c could not read that type (its header
// needs generated files).
char gChatStr_PortGe0[12] __attribute__((aligned(4))) = "port >= 0";

// 0x0225759C
// C declares this as `const char gChatStr_PortLeUSHRT_MAX[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_PortLeUSHRT_MAX[20] __attribute__((aligned(4))) = "port <= USHRT_MAX";

// 0x022575B0
// C declares this as `const char gChatStr_SockConnectStateEqCiNotConnected[]`, but s2c could not read
// that type (its header needs generated files).
char gChatStr_SockConnectStateEqCiNotConnected[40] __attribute__((aligned(4))) = "sock->connectState == ciNotConnected";

// 0x022575D8
// C declares this as `const char gChatStr_SockConnectStateEqCiConnected[]`, but s2c could not read
// that type (its header needs generated files).
char gChatStr_SockConnectStateEqCiConnected[36] __attribute__((aligned(4))) = "(sock)->connectState == ciConnected";

// 0x022575FC
// C declares this as `const char gChatStr_0_12[]`, but s2c could not read that type (its header needs
// generated files).
char gChatStr_0_12[4] __attribute__((aligned(4))) = "0";

// 0x02257600
// C declares this as `const char gChatStr_PTextNeNULL[]`, but s2c could not read that type (its header
// needs generated files).
char gChatStr_PTextNeNULL[16] __attribute__((aligned(4))) = "pText != NULL";

// 0x02257610
// C declares this as `const char gChatStr_MessageNeNULL_3[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_MessageNeNULL_3[16] __attribute__((aligned(4))) = "message != NULL";

// 0x02257620
// C declares this as `const char gChatStr_SpaceColon_2[]`, but s2c could not read that type (its
// header needs generated files).
char gChatStr_SpaceColon_2[4] __attribute__((aligned(4))) = " :";

// 0x02257624
// C declares this as `const char gChatStr_Space_4[]`, but s2c could not read that type (its header
// needs generated files).
char gChatStr_Space_4[4] __attribute__((aligned(4))) = " ";

