#!/bin/bash
# grass.sh: step left/right in tall grass until something starts (a battle), up to 80 steps
. "${TESTRIG_RUN:-$HOME/hgss_run}/env.sh"
H=$TESTRIG_RUN
for i in $(seq 1 80); do
  if [ $((i % 2)) = 0 ]; then $H/key.sh Left 450; else $H/key.sh Right 450; fi
  sleep 0.6
  if $H/busy.sh; then echo "encounter at step $i"; exit 0; fi
done
exit 1
