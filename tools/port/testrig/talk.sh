#!/bin/bash
# talk.sh [MAX]: press A once, then press A until no field script is running (checks every 5 presses), at most MAX presses
. "${TESTRIG_RUN:-$HOME/hgss_run}/env.sh"
H=$TESTRIG_RUN
$H/key.sh z 150; sleep 1.5
for i in $(seq 1 ${1:-300}); do
  if [ $((i % 5)) = 1 ]; then $H/busy.sh || { echo "free after $((i-1))"; exit 0; }; fi
  $H/key.sh z 150; sleep 0.8
  pgrep -f "^$HGSS_SRC/build_(linux|asan)/main" >/dev/null || { echo died; exit 2; }
done
echo "still busy"; exit 1
