#!/bin/bash
# gate_rival.sh: the ASan/UBSan build from the save next to Cherrygrove's east trigger: Continue, the Pokédex
# (opening, list, an entry), then the rival battle; the log is checked for sanitizer reports
. "${TESTRIG_RUN:-$HOME/hgss_run}/env.sh"
H=$TESTRIG_RUN; S=$TESTRIG_LOGS
export DISPLAY=:99
$H/kill.sh; cp $H/save_before_rival.bin $H/hg/save.bin
(setsid $H/run_asan.sh $S/asan_rival.log &); sleep 2
timeout 600 $H/cont.sh || { echo "cont failed"; exit 1; }
sleep 3; $H/key.sh x 150; sleep 2
xdotool mousemove 186 556 mousedown 1; sleep 0.15; xdotool mouseup 1; sleep 20
import -window root $S/asan_dex1.png
$H/key.sh z 150; sleep 15; import -window root $S/asan_dex2.png
$H/key.sh z 150; sleep 15; import -window root $S/asan_dex3.png
for i in 1 2 3 4 5; do $H/key.sh x 150; sleep 5; done
echo "after dex: $($H/nav/state.sh)"
$H/key.sh x 150; sleep 3   # close the touch menu if it is open
for i in 1 2 3; do $H/key.sh Right 450; sleep 2; st=$($H/nav/state.sh); echo "step $i: $st"; [ "$st" != free ] && break; done
$H/nav/battle.sh fight; echo "battle.sh exit $?"
$H/nav/party.sh; $H/nav/var.sh VAR_SCENE_CHERRYGROVE_CITY_OW
import -window root $S/asan_end.png
echo "sanitizer reports: $(grep -c 'ERROR: AddressSanitizer\|runtime error' $S/asan_rival.log)"
echo DONE
