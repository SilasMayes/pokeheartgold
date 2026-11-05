#!/bin/bash
# item.sh ITEM_NAME|ID ...: quantity of each item in the bag
. "${TESTRIG_RUN:-$HOME/hgss_run}/env.sh"
PID=$(pgrep -f "^$HGSS_SRC/build_(linux|asan)/main" | head -1)
args=()
for n in "$@"; do
  case $n in
    [0-9]*) id=$n;;
    *) id=$(grep -h "define $n\b" $HGSS_SRC/include/constants/items.h | awk '{print $3}');;
  esac
  args+=("-ex" "printf \"$n %d\\n\", Bag_GetQuantity(Save_Bag_Get(sFieldSysPtr->saveData), $id, 11)")
done
timeout 60 gdb -p $PID -batch "${args[@]}" 2>/dev/null | grep -E "^[A-Z0-9_]+ -?[0-9]+$"
