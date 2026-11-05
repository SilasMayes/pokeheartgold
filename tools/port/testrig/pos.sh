#!/bin/bash
# pos.sh: print the player's "x z facing" (attaches gdb for a moment)
. "${TESTRIG_RUN:-$HOME/hgss_run}/env.sh"
PID=$(pgrep -f "^$HGSS_SRC/build_(linux|asan)/main" | head -1)
cat > /tmp/pos.gdb <<'G'
set pagination off
printf "POS %d %d %d\n", PlayerAvatar_GetXCoord(sFieldSysPtr->playerAvatar), PlayerAvatar_GetZCoord(sFieldSysPtr->playerAvatar), PlayerAvatar_GetFacingDirection(sFieldSysPtr->playerAvatar)
detach
quit
G
timeout 60 gdb -p $PID -batch -x /tmp/pos.gdb 2>/dev/null | grep "^POS" | cut -d' ' -f2-
