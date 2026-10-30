#!/bin/bash
# Regenerates the headers the port build needs from files/ (message ID headers and NARC
# index .naix files) into generated/. The port has no data pipeline: NARC contents come from
# the player's ROM at runtime, but the C code still needs the IDs at compile time.
#
# Works on a scratch copy of the tree so the DS Make build's outputs are never touched.
# Needs: gcc/g++, make, libpng, arm-none-eabi-gcc (stands in for mwcc/mwasm on the few data
# files that are compiled; only symbol names reach the headers).
#
# Both versions are generated and merged: the headers are the same except for the
# version-exclusive NARCs (g_enc_data / s_enc_data), so one set serves both.
#
# Usage: tools/port/gen_headers.sh [outdir]
set -euo pipefail
ROOT=$(cd "$(dirname "$0")/../.." && pwd)
OUT=${1:-$ROOT/generated}
WORK=$(mktemp -d)
trap 'rm -rf "$WORK"' EXIT

echo "copying tree to $WORK"
tar -C "$ROOT" --exclude=./.git --exclude=./build --exclude=./generated -cf - . | tar -C "$WORK" -xf -
cd "$WORK"
chmod +x tools/port/fakewine.sh

for t in jsonproc nitrogfx nitroarc msgenc csv2bin o2narc; do
    make -s -C tools/$t -j"$(nproc)" >/dev/null
done

# The Makefile wants a toolchain present; the stand-in replaces wine+mwcc/mwasm.
mkdir -p tools/mwccarm/2.0/sp2p2
touch tools/mwccarm/2.0/sp2p2/mwccarm.exe tools/mwccarm/2.0/sp2p2/mwasmarm.exe

# Every generated header the C code includes: msgdata/msg/*.h and *.naix
grep -rhoE '#include "[^"]+\.(naix|h)"' src include lib/src | sed -E 's/#include "(.*)"/\1/' | sort -u |
    grep -E '^msgdata/msg/msg_[0-9]+.*\.h$|\.naix$' > needed.txt

# Field scripts are mwasm-only macro assembly; the naix only needs their names
for s in files/fielddata/script/scr_seq/*.s; do : > "${s%.s}.bin"; done

MK="make -k -j$(nproc) NODEP=1 COMPARE=0 WINE=$WORK/tools/port/fakewine.sh"
for VERSION in SOULSILVER HEARTGOLD; do
    # Pass 1: headers with their own rule (msg headers, version-normalized .naix).
    # Pass 2: the rest of the .naix are a side product of packing their NARC.
    # -k skips the misses; asking for the NARC first would bypass the normalizing rules.
    $MK GAME_VERSION=$VERSION $(sed 's#^#files/#' needed.txt) >>make.log 2>&1 || true
    narcs=()
    while read -r f; do
        [ -f "files/$f" ] || narcs+=("files/${f%.naix}.narc")
    done < <(grep '\.naix$' needed.txt)
    [ ${#narcs[@]} -eq 0 ] || $MK GAME_VERSION=$VERSION "${narcs[@]}" >>make.log 2>&1 || true
    # scr_seq: pack the placeholder bins directly (its rule runs the real assembler)
    tools/nitroarc/nitroarc -cf files/fielddata/script/scr_seq.narc --index-namespace files/fielddata/script/scr_seq
done

rm -rf "$OUT.tmp"; missing=0
while read -r f; do
    if [ -f "files/$f" ]; then
        mkdir -p "$OUT.tmp/$(dirname "$f")"
        # the banner comment names the scratch path; keep the files reproducible
        sed "s#$WORK/##g" "files/$f" > "$OUT.tmp/$f"
    else
        echo "not generated: $f" >&2; missing=1
    fi
done < needed.txt
if [ $missing -ne 0 ]; then tail -40 make.log >&2; exit 1; fi
rm -rf "$OUT"; mv "$OUT.tmp" "$OUT"
echo "wrote $(find "$OUT" -type f | wc -l) headers to $OUT"
