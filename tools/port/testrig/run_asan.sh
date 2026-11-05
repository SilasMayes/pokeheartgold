#!/bin/bash
# run_asan.sh LOG: like run.sh with the ASan/UBSan build (leaks off: the game frees little at exit)
. "${TESTRIG_RUN:-$HOME/hgss_run}/env.sh"
cd $TESTRIG_RUN/${GAMEDIR:-hg}
export DISPLAY=:99
export SDL_AUDIODRIVER=${SDL_AUDIODRIVER:-dummy}
export ASAN_OPTIONS=detect_leaks=0:abort_on_error=0
export UBSAN_OPTIONS=print_stacktrace=1:suppressions=$TESTRIG_RUN/ubsan.supp
exec $HGSS_SRC/build_asan/main > "$1" 2>&1
