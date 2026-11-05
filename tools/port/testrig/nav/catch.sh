#!/bin/bash
# catch.sh [TRIES]: in a wild battle, throw Poké Balls (BAG > POKé BALLS > first ball > USE) at each command
# menu until the battle ends or a nickname question comes up (exit 0 then, the question still open)
. "${TESTRIG_RUN:-$HOME/hgss_run}/env.sh"
export DISPLAY=:99
H=$TESTRIG_RUN
tap() { xdotool mousemove $1 $2 mousedown 1; sleep 0.15; xdotool mouseup 1; }
menu() { local p=($($H/pix.sh 356 600 300 850)); IFS=, read r1 g1 b1 <<< "${p[0]}"; IFS=, read r2 g2 b2 <<< "${p[1]}"
  [ "$r1" -gt 180 ] && [ "$g1" -lt 110 ] && [ "$b2" -gt 100 ] && [ "$r2" -lt 100 ]; }
throws=0
for i in $(seq 1 60); do [ "$($H/nav/state.sh)" = "app Battle_Init" ] && break; sleep 2; done  # the battle may still be starting
for i in $(seq 1 300); do
  st=$($H/nav/state.sh)
  [[ "$st" == app* ]] || { echo "[catch] battle over ($st) after $throws throws"; exit 0; }
  [[ "$st" == "app Battle_Init" ]] || { echo "[catch] in $st"; exit 0; }
  if menu; then
    [ $throws -ge ${1:-5} ] && { echo "[catch] out of tries"; exit 1; }
    throws=$((throws + 1)); echo "[catch] throw $throws"
    tap 180 822; sleep 3; tap 484 572; sleep 3; tap 228 548; sleep 3; tap 306 830; sleep 12
  else
    $H/key.sh z 120; sleep 1.5
  fi
done
exit 1
