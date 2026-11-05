#!/bin/bash
# key.sh KEY [HOLD_MS] [SHOT]: press a key in the game window, optional screenshot after 1s
# (the key is released even when this script is killed while holding it)
export DISPLAY=:99
K=$1
trap 'xdotool keyup "$K"; exit 1' TERM INT HUP
W=$(xdotool search --name "POKEMON" 2>/dev/null | head -1)
xdotool windowactivate --sync $W 2>/dev/null; xdotool windowfocus $W 2>/dev/null
xdotool keydown "$K"; sleep $(echo "${2:-120}/1000" | bc -l) & wait $!; xdotool keyup "$K"
if [ -n "$3" ]; then sleep 1; import -window root "$3"; fi
