// Converted from asm/pokeathlon_course_data.s (part 2 of 2) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

#include "global.h"

#include "pokeathlon/pokeathlon_course_internal.h"

#pragma force_active on

extern void CommCmd_GetSizeVariable(void);

const PokeathlonCourseCmd gPokeathlonCourseCmds[POKEATHLON_COURSE_CMD_JUICE_RECORD - POKEATHLON_COURSE_CMD_FIRST + 1] = {
    {
     (PokeathlonCourseCmdFunc)PokeathlonCourseCmd_RecvEvents,
     (PokeathlonCourseCmdSizeFunc)PokeathlonCourseCmd_EventsSize,
     NULL,
     },
    {
     (PokeathlonCourseCmdFunc)PokeathlonCourseCmd_RecvParticipant,
     (PokeathlonCourseCmdSizeFunc)PokeathlonCourseCmd_ParticipantSize,
     NULL,
     },
    {
     (PokeathlonCourseCmdFunc)PokeathlonCourseCmd_RecvAllParticipants,
     (PokeathlonCourseCmdSizeFunc)PokeathlonCourseCmd_AllParticipantsSize,
     NULL,
     },
    {
     (PokeathlonCourseCmdFunc)PokeathlonCourseCmd_RecvProfiles,
     (PokeathlonCourseCmdSizeFunc)PokeathlonCourseCmd_ProfilesSize,
     NULL,
     },
    {
     (PokeathlonCourseCmdFunc)PokeathlonCourseCmd_RecvRecord,
     (PokeathlonCourseCmdSizeFunc)PokeathlonCourseCmd_RecordSize,
     (PokeathlonCourseCmdBufferFunc)PokeathlonCourseCmd_GetRecordBuffer,
     },
    {
     (PokeathlonCourseCmdFunc)PokeathlonCourseCmd_RecvPacket,
     (PokeathlonCourseCmdSizeFunc)PokeathlonCourseCmd_PacketSize,
     NULL,
     },
    {
     (PokeathlonCourseCmdFunc)PokeathlonCourseCmd_RecvEventData,
     (PokeathlonCourseCmdSizeFunc)CommCmd_GetSizeVariable,
     (PokeathlonCourseCmdBufferFunc)PokeathlonCourseCmd_GetEventDataBuffer,
     },
    {
     (PokeathlonCourseCmdFunc)PokeathlonCourseCmd_RecvEventResult,
     (PokeathlonCourseCmdSizeFunc)PokeathlonCourseCmd_PacketSize,
     NULL,
     },
    {
     (PokeathlonCourseCmdFunc)PokeathlonCourseCmd_RecvEventResults,
     (PokeathlonCourseCmdSizeFunc)PokeathlonCourseCmd_PacketSize,
     NULL,
     },
    {
     (PokeathlonCourseCmdFunc)PokeathlonCourseCmd_RecvMonCounters,
     (PokeathlonCourseCmdSizeFunc)PokeathlonCourseCmd_MonCountersSize,
     (PokeathlonCourseCmdBufferFunc)PokeathlonCourseCmd_GetMonCountersBuffer,
     },
    {
     (PokeathlonCourseCmdFunc)PokeathlonCourseCmd_RecvResults,
     (PokeathlonCourseCmdSizeFunc)PokeathlonCourseCmd_ResultsSize,
     (PokeathlonCourseCmdBufferFunc)PokeathlonCourseCmd_GetResultsBuffer,
     },
    {
     (PokeathlonCourseCmdFunc)PokeathlonCourseCmd_RecvJuiceRecord,
     (PokeathlonCourseCmdSizeFunc)PokeathlonCourseCmd_JuiceRecordSize,
     (PokeathlonCourseCmdBufferFunc)PokeathlonCourseCmd_GetJuiceRecordBuffer,
     },
};
