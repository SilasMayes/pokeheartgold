#!/bin/bash
# setup.sh [RUN_DIR]: install the test rig for the Linux port into RUN_DIR (default ~/hgss_run).
#
# Links the rig's scripts from this checkout into RUN_DIR, writes RUN_DIR/env.sh (TESTRIG_RUN, HGSS_SRC,
# TESTRIG_LOGS, DISPLAY) that every script sources, creates RUN_DIR/logs and RUN_DIR/mem, installs the packages
# it needs (apt), writes RUN_DIR/hg/sim_config.ini if there is none, and starts Xvfb on :99 under a restart loop
# (a sandbox's background tasks are stopped after a while, and the game dies with its display).
#
# Still yours to provide: RUN_DIR/hg, the game's data directory (the HG ROM as the port's cart import extracts
# it), and a save in RUN_DIR/hg/save.bin (milestone saves: README.md). Builds: build_linux and build_asan in
# HGSS_SRC (README.md).
set -e
RIG=$(cd "$(dirname "$0")" && pwd)
SRC=$(cd "$RIG/../../.." && pwd)
RUN=${1:-${TESTRIG_RUN:-$HOME/hgss_run}}
mkdir -p "$RUN/nav" "$RUN/logs" "$RUN/mem" "$RUN/hg"
for f in "$RIG"/*.sh "$RIG"/ubsan.supp; do ln -sf "$f" "$RUN/"; done
rm -f "$RUN/setup.sh"
for f in "$RIG"/nav/*; do ln -sf "$f" "$RUN/nav/"; done
cat > "$RUN/env.sh" <<ENV
export TESTRIG_RUN=$RUN
export HGSS_SRC=$SRC
export TESTRIG_LOGS=$RUN/logs
export DISPLAY=\${DISPLAY:-:99}
ENV
if ! command -v xdotool >/dev/null || ! command -v Xvfb >/dev/null || ! command -v import >/dev/null || ! command -v gdb >/dev/null; then
  (sudo -n true 2>/dev/null && SUDO=sudo) || SUDO=
  $SUDO apt-get install -y xvfb xdotool imagemagick gdb python3 bc >/dev/null
fi
[ -f "$RUN/hg/sim_config.ini" ] || cp "$RIG/sim_config.ini" "$RUN/hg/sim_config.ini"
if ! pgrep -f "^Xvfb :99" >/dev/null; then
  setsid bash -c 'while true; do Xvfb :99 -screen 0 1280x1024x24 -nolisten tcp >/dev/null 2>&1; sleep 1; done' >/dev/null 2>&1 < /dev/null &
  sleep 2
fi
echo "rig in $RUN (source $RUN/env.sh); Xvfb :99 $(pgrep -f '^Xvfb :99' >/dev/null && echo up || echo DOWN)"
