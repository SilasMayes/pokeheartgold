#!/bin/bash
# cont.sh: boot to the main menu and pick CONTINUE (needs hg/save.bin)
. "${TESTRIG_RUN:-$HOME/hgss_run}/env.sh"
export DISPLAY=:99
K=$TESTRIG_RUN/key.sh
blue() { # the main menu: black top screen, blue border left of the bottom screen
  local p=($($TESTRIG_RUN/pix.sh 360 250 108 700)); IFS=, read r g b <<< "${p[1]}"
  [ "${p[0]}" = "0,0,0" ] && [ "$b" -gt 150 ] && [ "$r" -lt 120 ]
}
until xdotool search --name "POKEMON" >/dev/null 2>&1; do sleep 1; done
sleep 8
for i in $(seq 1 60); do blue && break; pgrep -f "build_(linux|asan)/main" >/dev/null || exit 1; $K Return 120; sleep 3; done
blue || exit 2
sleep 1; $K z 100; sleep 6
