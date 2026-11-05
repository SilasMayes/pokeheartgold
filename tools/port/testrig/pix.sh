#!/bin/bash
# pix.sh X Y [X Y ...]: "r,g,b" of screen pixels on :99 (one line each)
DISPLAY=:99 import -window root /tmp/_pix.png
while [ $# -ge 2 ]; do
  convert /tmp/_pix.png -format "%[fx:int(255*p{$1,$2}.r)],%[fx:int(255*p{$1,$2}.g)],%[fx:int(255*p{$1,$2}.b)]\n" info:
  shift 2
done
