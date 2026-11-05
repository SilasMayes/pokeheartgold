#!/bin/bash
# save.sh: save from the field through the touch menu's SAVE button (overwrites), then back the save up
. "${TESTRIG_RUN:-$HOME/hgss_run}/env.sh"
export DISPLAY=:99
H=$TESTRIG_RUN
before=$(stat -c %Y $H/hg/save.bin 2>/dev/null || echo 0)
xdotool mousemove 346 636 mousedown 1; sleep 0.15; xdotool mouseup 1; sleep 3
for i in $(seq 1 60); do
  $H/key.sh z 80; sleep 2
  now=$(stat -c %Y $H/hg/save.bin 2>/dev/null || echo 0)
  [ "$now" -gt "$before" ] && break
done
sleep 3
for i in 1 2 3 4 5; do $H/busy.sh || break; $H/key.sh x 80; sleep 2; done
cp $H/hg/save.bin "$H/save_$(date +%H%M).bin"; ls -la $H/hg/save.bin
