#!/bin/bash
# run.sh LOG: start HeartGold in $TESTRIG_RUN/hg on :99 (stdout/stderr to LOG)
. "${TESTRIG_RUN:-$HOME/hgss_run}/env.sh"
ulimit -c unlimited
cd $TESTRIG_RUN/${GAMEDIR:-hg}
export DISPLAY=:99
export SDL_AUDIODRIVER=${SDL_AUDIODRIVER:-dummy}
exec $HGSS_SRC/build_linux/main > "$1" 2>&1
