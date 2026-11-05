#!/bin/bash
# heal.sh: inside a Pokémon Center's 1F, walk to the counter, talk to the nurse until the field is free,
# then walk back out of the door (8, 19)
. "${TESTRIG_RUN:-$HOME/hgss_run}/env.sh"
H=$TESTRIG_RUN
python3 $H/nav/go.py 8 13 || exit 1
$H/key.sh Up 80; sleep 0.8
$H/key.sh z 120; sleep 1.5
$H/nav/battle.sh fight >/dev/null || exit 1
python3 $H/nav/go.py 8 19
