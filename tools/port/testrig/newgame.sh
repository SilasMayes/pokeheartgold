#!/bin/bash
# newgame.sh [PRESSES]: drive a fresh start to the field (intro, title, "No info needed", Oak, boy,
# name AAAAAAA), then keep pressing A
. "${TESTRIG_RUN:-$HOME/hgss_run}/env.sh"
export DISPLAY=:99
K=$TESTRIG_RUN/key.sh
menu() { [ "$($TESTRIG_RUN/pix.sh 345 775)" = "49,222,230" ]; }
until xdotool search --name "POKEMON" >/dev/null 2>&1; do sleep 1; done
sleep 8
for i in $(seq 1 60); do menu && break; pgrep -f build_linux/main >/dev/null || exit 1; $K Return 120; sleep 3; done
menu || exit 2
for i in 1 2 3; do $K Down 80; sleep 0.5; done
$K Tab 80; $K z 80; sleep 1
for i in $(seq 1 ${1:-60}); do $K z 60; sleep 0.4; pgrep -f build_linux/main >/dev/null || exit 1; done
