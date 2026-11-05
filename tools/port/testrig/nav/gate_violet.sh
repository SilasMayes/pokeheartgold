#!/bin/bash
# gate_violet.sh: the ASan/UBSan build from the healed Violet save: the Mart (buy Poké Balls), then through the
# Route 31 gatehouse to its grass and a wild catch with a nickname. The log is checked for sanitizer reports.
. "${TESTRIG_RUN:-$HOME/hgss_run}/env.sh"
H=$TESTRIG_RUN; S=$TESTRIG_LOGS
export DISPLAY=:99
tap() { xdotool mousemove $1 $2; sleep 0.3; xdotool mousedown 1; sleep 0.2; xdotool mouseup 1; sleep 2.5; }
step() { echo "[gate] $* ($(date +%H:%M:%S))"; }
$H/nav/stop.sh; $H/kill.sh; cp $H/save_violet_healed.bin $H/hg/save.bin
(setsid $H/run_asan.sh $S/asan_violet.log &); sleep 2
timeout 900 $H/cont.sh || { step "cont failed"; exit 1; }
step "continued at $($H/pos.sh)"
$H/nav/travel.sh 469 257; sleep 8; step "mart at $($H/pos.sh)"
python3 $H/nav/go.py 3 6; $H/key.sh Left 100; sleep 2
$H/key.sh z 150; sleep 5; $H/key.sh z 150; sleep 8
import -window root $S/asan_shop.png
tap 228 595; $H/key.sh Up 100; sleep 1.5; $H/key.sh Up 100; sleep 1.5; $H/key.sh z 150; sleep 4; $H/key.sh z 150; sleep 5
for i in $(seq 1 12); do [ "$($H/nav/state.sh)" = free ] && break; $H/key.sh x 150; sleep 3; done
step "bought: $($H/nav/item.sh ITEM_POKE_BALL | tail -1)"
python3 $H/nav/go.py 4 11; sleep 8
$H/nav/travel.sh 511 269; $H/key.sh Right 400; sleep 10; step "gatehouse at $($H/pos.sh)"
$H/nav/travel.sh 10 7; $H/key.sh Right 400; sleep 10; step "route 31 at $($H/pos.sh)"
$H/nav/travel.sh 527 272 --grass; step "grass at $($H/pos.sh)"
for t in 1 2 3; do
  $H/grass.sh >/dev/null; sleep 15; $H/nav/catch.sh 5; $H/nav/battle.sh fight
  [ "$($H/nav/party.sh | wc -l)" -ge 2 ] && break
done
$H/nav/party.sh
import -window root $S/asan_end2.png
echo "sanitizer reports: $(grep -c 'ERROR: AddressSanitizer\|runtime error' $S/asan_violet.log)"
grep "\[port\]\|\[assert\]" $S/asan_violet.log
step DONE
