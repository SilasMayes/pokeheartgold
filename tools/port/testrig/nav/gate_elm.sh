#!/bin/bash
# gate_elm.sh: the ASan/UBSan build from the save after the rival: Route 29 to New Bark, Elm's lab (the officer,
# the naming screen, Elm), the aide's Poké Balls, Options (CONFIRM), then a wild catch on Route 29 with a
# nickname. The log is checked for sanitizer reports.
. "${TESTRIG_RUN:-$HOME/hgss_run}/env.sh"
H=$TESTRIG_RUN; S=$TESTRIG_LOGS
export DISPLAY=:99
tap() { xdotool mousemove $1 $2; sleep 0.3; xdotool mousedown 1; sleep 0.2; xdotool mouseup 1; sleep 1.5; }
step() { echo "[gate] $* ($(date +%H:%M:%S))"; }
$H/nav/stop.sh; $H/kill.sh; cp $H/save_after_rival.bin $H/hg/save.bin
(setsid $H/run_asan.sh $S/asan_elm.log &); sleep 2
timeout 900 $H/cont.sh || { step "cont failed"; exit 1; }
step "continued at $($H/pos.sh)"
ROUNDS=60 $H/nav/travel.sh 684 395 --grass --max=200; step "travel $? at $($H/pos.sh)"
$H/key.sh Up 400; sleep 3; $H/key.sh Up 400; sleep 10
$H/nav/battle.sh fight; step "lab scene done, at $($H/pos.sh)"
$H/nav/var.sh VAR_SCENE_ELMS_LAB 2>/dev/null
import -window root $S/asan_lab.png
python3 $H/nav/go.py 4 13; $H/key.sh Down 400; sleep 3; $H/nav/battle.sh fight; sleep 8
step "out of the lab at $($H/pos.sh), balls $($H/nav/item.sh ITEM_POKE_BALL)"
tap 346 716; sleep 8; tap 555 557; tap 539 653; tap 395 847; sleep 10
step "options closed: $($H/nav/state.sh)"
$H/nav/travel.sh 650 397 --grass --max=100; step "grass at $($H/pos.sh)"
for t in 1 2 3; do
  $H/grass.sh >/dev/null; sleep 12; $H/nav/catch.sh 5; $H/nav/battle.sh fight
  [ "$($H/nav/party.sh | wc -l)" -ge 2 ] && break
done
$H/nav/party.sh
import -window root $S/asan_end.png
echo "sanitizer reports: $(grep -c 'ERROR: AddressSanitizer\|runtime error' $S/asan_elm.log)"
grep "\[port\]\|\[assert\]" $S/asan_elm.log
step DONE
