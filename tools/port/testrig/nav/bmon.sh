#!/bin/bash
# bmon.sh: in a battle, the player's battler 0 moves "move:pp:power" (one line), e.g. "33:0:40 45:40:0 ..."
. "${TESTRIG_RUN:-$HOME/hgss_run}/env.sh"
PID=$(pgrep -f "^$HGSS_SRC/build_(linux|asan)/main" | head -1)
cat > /tmp/_bmon.py <<'P'
import gdb
def ev(s): return int(gdb.parse_and_eval(s))
b = "((BattleSystem *)sFieldSysPtr->processManager->child->data)->ctx->battleMons[0]"
out = []
for i in range(4):
    m = ev(f"{b}.moves[{i}]")
    out.append(f"{m}:{ev(f'{b}.movePPCur[{i}]')}:{ev(f'GetMoveAttr({m}, 2)') if m else 0}")
print("BMON " + " ".join(out))
P
timeout 60 gdb -p $PID -batch -x /tmp/_bmon.py 2>/dev/null | grep '^BMON' | cut -d' ' -f2-
