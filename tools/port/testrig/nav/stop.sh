#!/bin/bash
# stop.sh: stop every helper (travel, battle, catch, heal, sprout, the gates, go.py, key.sh) and release the keys
# and the mouse button (a helper killed while holding a key leaves it held: the game then sees it pressed)
pkill -f "^/bin/bash (\S*/)?nav/(travel|battle|catch|heal|sprout|gate_\w+)\.sh"
pkill -f "^python3 (\S*/)?nav/go\.py"
pkill -f "^/bin/bash (\S*/)?key\.sh"
sleep 1
DISPLAY=${DISPLAY:-:99} xdotool keyup z x Up Down Left Right Return; DISPLAY=${DISPLAY:-:99} xdotool mouseup 1
