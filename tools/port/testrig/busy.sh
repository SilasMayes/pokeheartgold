#!/bin/bash
# busy.sh: exit 0 if a field script/task is running (or the field isn't up), 1 if the player is free
. "${TESTRIG_RUN:-$HOME/hgss_run}/env.sh"
PID=$(pgrep -f "^$HGSS_SRC/build_(linux|asan)/main" | head -1)
r=$(timeout 60 gdb -p $PID -batch -ex 'printf "TM %d\n", sFieldSysPtr != 0 && sFieldSysPtr->taskman == 0 && sFieldSysPtr->processManager->child == 0' 2>/dev/null | grep '^TM' | cut -d' ' -f2)
[ "$r" = "1" ] && exit 1 || exit 0
