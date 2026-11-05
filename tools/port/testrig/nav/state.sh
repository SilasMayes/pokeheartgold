#!/bin/bash
# state.sh: "free", "script", "app <init function of the running field application>" or "nofield"
. "${TESTRIG_RUN:-$HOME/hgss_run}/env.sh"
PID=$(pgrep -f "^$HGSS_SRC/build_(linux|asan)/main" | head -1)
[ -z "$PID" ] && { echo dead; exit 2; }
timeout 60 gdb -p $PID -batch \
  -ex 'printf "ST %d %d %d\n", sFieldSysPtr != 0, sFieldSysPtr ? sFieldSysPtr->taskman != 0 : 0, sFieldSysPtr ? sFieldSysPtr->processManager->child != 0 : 0' \
  -ex 'info symbol sFieldSysPtr->processManager->child->template.init' 2>/dev/null |
awk '/^ST/{f=$2; t=$3; c=$4} / in section /{sym=$1} END{ if (f!=1) print "nofield"; else if (c==1) print "app " sym; else if (t==1) print "script"; else print "free"}'
