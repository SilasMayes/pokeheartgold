#!/bin/bash
# sprout.sh: from Violet City, through Sprout Tower to 3F: 1F center ladder -> 2F -> 2F's east ladder down ->
# 1F's outer ring -> 1F's west ladder -> 2F's west side -> the ladder to 3F (battles on the way are fought)
. "${TESTRIG_RUN:-$HOME/hgss_run}/env.sh"
H=$TESTRIG_RUN
step() { echo "[sprout] $*"; }
ladder() { $H/key.sh $1 300; sleep 6; step "ladder $1 -> $($H/pos.sh)"; }
on_map() { [ "$(timeout 60 gdb -p $(pgrep -f '^$HGSS_SRC/build_(linux|asan)/main' | head -1) -batch -ex 'printf "M %d\n", sFieldSysPtr->location->mapId' 2>/dev/null | awk '/^M/{print $2}')" = "$1" ]; }
on_map 110 || { $H/nav/travel.sh 487 228; sleep 6; on_map 110 || exit 1; }
$H/nav/travel.sh 10 15 || exit 1; ladder Up               # 1F -> 2F (11, 13)
on_map 155 || exit 2
$H/nav/travel.sh 24 10 || exit 1; ladder Up               # 2F (24, 9) -> 1F ring
on_map 110 || exit 3
$H/nav/travel.sh 6 17 || exit 1; ladder Up                # 1F (6, 16) -> 2F west
on_map 155 || exit 4
$H/nav/travel.sh 15 28 || exit 1; ladder Up               # 2F (15, 27) -> 3F
on_map 156 || exit 5
step "on 3F at $($H/pos.sh)"
