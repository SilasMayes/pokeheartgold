#!/bin/bash
# party.sh: species, level, HP/max HP and moves of each party Pokémon
. "${TESTRIG_RUN:-$HOME/hgss_run}/env.sh"
PID=$(pgrep -f "^$HGSS_SRC/build_(linux|asan)/main" | head -1)
cat > /tmp/_party.py <<'P'
import gdb
def ev(s): return int(gdb.parse_and_eval(s))
p = "SaveArray_Party_Get(sFieldSysPtr->saveData)"
for i in range(ev(f"Party_GetCount({p})")):
    m = f"Party_GetMonByIndex({p}, {i})"
    g = lambda k: ev(f"GetMonData({m}, {k}, 0)")
    print(f"MON {i}: species {g(5)} lv {g(161)} hp {g(163)}/{g(164)} moves {[g(54+j) for j in range(4)]} pp {[g(58+j) for j in range(4)]}")
P
timeout 60 gdb -p $PID -batch -x /tmp/_party.py 2>/dev/null | grep '^MON'
