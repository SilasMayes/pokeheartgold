#!/bin/bash
# Stand-in for "wine mwccarm.exe/mwasmarm.exe" used ONLY to derive generated headers
# (naix symbol names) for the port. Output data is not used.
exe="$1"; shift
args=(); out=""; src=""; mode=""
case "$exe" in
  *mwccarm.exe) mode=cc;;
  *mwasmarm.exe) mode=as;;
  *) echo "fakewine: unsupported $exe" >&2; exit 1;;
esac
while [ $# -gt 0 ]; do
  case "$1" in
    -o) out="$2"; shift 2;;
    -i|-I) args+=("-I$2"); shift 2;;
    -I*) args+=("$1"); shift;;
    -D*) args+=("$1"); shift;;
    -c) shift;;
    -proc|-msgstyle|-enum|-lang|-inline|-char|-ipa|-W|-sym) shift 2;;
    *.c|*.s) src="$1"; shift;;
    *) shift;;
  esac
done
if [ $mode = cc ]; then
  exec arm-none-eabi-gcc -c -fsigned-char -fno-common -w -std=gnu99 -DSDK_ARM9 "${args[@]}" -o "$out" "$src"
else
  tmp=$(mktemp --suffix=.s)
  sed -E 's/@object/%object/g; s/@function/%function/g; s/^\s*\.rodata\s*$/.section .rodata/; s/^\s*\.data\s*$/.section .data/; s/^\s*\.bss\s*$/.section .bss/' "$src" > "$tmp"
  arm-none-eabi-gcc -c -x assembler-with-cpp -w -I"$(dirname "$src")" "${args[@]}" -o "$out" "$tmp"; rc=$?
  rm -f "$tmp"; exit $rc
fi
