#!/bin/bash
# travel.sh X Z [go.py flags]: go.py toward (X, Z); battles (fight while the lead has >= 50% HP, else run) and
# scripts on the way are pressed through
. "${TESTRIG_RUN:-$HOME/hgss_run}/env.sh"
H=$TESTRIG_RUN
for round in $(seq 1 ${ROUNDS:-40}); do
  python3 $H/nav/go.py "$@"; r=$?
  case $r in
    0) exit 0;;
    3) hp=$($H/nav/party.sh | head -1 | sed -n 's/.* hp \([0-9]*\)\/\([0-9]*\).*/\1 \2/p')
       set -- "$@"; read cur max <<< "$hp"
       mode=fight; [ -n "$max" ] && [ $((cur * 2)) -lt "$max" ] && mode=run
       echo "[travel] busy (lead hp $cur/$max): $mode"; $H/nav/battle.sh $mode || exit 4;;
    *) exit $r;;
  esac
done
exit 1
