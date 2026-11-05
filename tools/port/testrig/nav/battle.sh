#!/bin/bash
# battle.sh [fight|run]: get through a battle or field script. At a battle's command menu: FIGHT (or RUN); at the
# move menu: the strongest move with PP left (bmon.sh); in the Pokégear: B (a call ends there and A would dial
# again); otherwise A. Exits 0 once the field is free again.
. "${TESTRIG_RUN:-$HOME/hgss_run}/env.sh"
export DISPLAY=:99
H=$TESTRIG_RUN
mode=${1:-fight}
tap() { xdotool mousemove $1 $2; sleep 0.2; xdotool mousedown 1; sleep 0.15; xdotool mouseup 1; }
screen() { # "command" (FIGHT red above, RUN dark blue below, off its label), "moves" (CANCEL blue below, no red), or "other"
  local p=($($H/pix.sh 356 600 300 850 150 834)); IFS=, read r1 g1 b1 <<< "${p[0]}"; IFS=, read r2 g2 b2 <<< "${p[1]}"
  IFS=, read r3 g3 b3 <<< "${p[2]}"
  if [ "$r1" -gt 180 ] && [ "$g1" -lt 110 ] && [ "$b2" -gt 100 ] && [ "$r2" -lt 100 ]; then echo command
  elif [ "$b3" -gt 150 ] && [ "$r3" -lt 120 ] && ! { [ "$r1" -gt 180 ] && [ "$g1" -lt 110 ]; }; then echo moves
  else echo other; fi
}
free=0
for i in $(seq 1 600); do
  st=$($H/nav/state.sh)
  case "$st" in
    dead) echo died; exit 2;;
    free) free=$((free + 1)); [ $free -ge 2 ] && { echo "[battle] free"; exit 0; }; sleep 1; continue;;
    *Pokegear*) free=0; $H/key.sh x 150; sleep 1.2; continue;;
  esac
  free=0
  sc=other; [[ "$st" == "app Battle_Init" ]] && sc=$(screen)
  if [ $sc = command ]; then
    if [ "$mode" = run ]; then echo "[battle] RUN"; tap 356 830; sleep 2
    else echo "[battle] FIGHT"; tap 356 650; sleep 3; fi
  elif [ $sc = moves ]; then
    slot=$($H/nav/bmon.sh | tr ' ' '\n' | awk -F: '$2 > 0 { if ($3 > best || !found) { best = $3; s = NR - 1; found = 1 } } END { print found ? s : 0 }')
    echo "[battle] move slot $slot"; tap $((228 + 256 * (slot % 2))) $((588 + 128 * (slot / 2))); sleep 2
  else
    $H/key.sh z 150; sleep 0.8
  fi
done
echo "[battle] still busy ($st)"; exit 1
