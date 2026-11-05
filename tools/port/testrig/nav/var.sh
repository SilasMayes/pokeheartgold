#!/bin/bash
# var.sh NAME|0xID ...: values of script vars (VAR_*) and flags (FLAG_*) by their decomp names
. "${TESTRIG_RUN:-$HOME/hgss_run}/env.sh"
PID=$(pgrep -f "^$HGSS_SRC/build_(linux|asan)/main" | head -1)
args=()
for n in "$@"; do
  case $n in
    0x*|[0-9]*) args+=("-ex" "printf \"$n %d\\n\", FieldSystem_VarGet(sFieldSysPtr, $n)");;
    FLAG_*) id=$(grep -rh "define $n\b" $HGSS_SRC/include/constants/flags.h | awk '{print $3}')
            args+=("-ex" "printf \"$n %d\\n\", Save_VarsFlags_CheckFlagInArray(Save_VarsFlags_Get(sFieldSysPtr->saveData), $id)");;
    *) id=$(grep -rh "define $n\b" $HGSS_SRC/include/constants/vars.h | awk '{print $3}')
       args+=("-ex" "printf \"$n %d\\n\", FieldSystem_VarGet(sFieldSysPtr, $id)");;
  esac
done
timeout 60 gdb -p $PID -batch "${args[@]}" 2>/dev/null | grep -E "^(VAR|FLAG|0x[0-9a-fA-F]+ -?[0-9]+$|[0-9]+ -?[0-9]+$)"
