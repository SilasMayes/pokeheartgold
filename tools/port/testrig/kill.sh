#!/bin/bash
# kill.sh: stop every running game (SDL turns SIGTERM into a quit event a hung game never reads)
. "${TESTRIG_RUN:-$HOME/hgss_run}/env.sh"
pkill -9 -f "^$HGSS_SRC/build_(linux|asan)/main"; sleep 1
