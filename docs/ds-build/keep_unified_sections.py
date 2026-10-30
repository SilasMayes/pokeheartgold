#!/usr/bin/env python3
"""Add the fork's split SDK data sections to KEEP_SECTION in the NitroSDK 3.2 ARM9 template.

usage: python3 -I docs/ds-build/keep_unified_sections.py ARM9-TS.lcf.template

The fork splits a few SDK objects (lib/asm/nitro_sdk_data.o, SND_util.o, SND_main.o, ...)
into named sections (.rodata.unified_01, .rodata.snd_decibel, .bss.unified_04, ...) and
tools/nitro-section-renames/patch_nitro_lcf.py places them in retail order. In the retail
link each of these was part of one whole .rodata/.data/.bss and was kept with it; split,
the ones nothing references (.rodata.unified_01 has no symbols at all; SNDi_DecibelTable
is unused on ARM9) are dead-stripped by mwldarm, the static module comes out 0x7F4 bytes
short and every module that points into it fails main.sha1. This is the "keep the split
.rodata/.data/.bss unified sections" step from ClickingMaster's notes (ssrecomp #9).

The section list is read from tools/nitro-section-renames/nitro_link_order.json, so it
follows the repo. Idempotent: an existing block written by this script is replaced.
"""
import json
import sys
from pathlib import Path

MARK = "# keep_unified_sections.py"


def split_sections(root):
    plan = json.loads((root / "tools/nitro-section-renames/nitro_link_order.json").read_text())
    names = []
    for kind in ("rodata", "data", "bss"):
        for row in plan["sections"][kind]:
            sel = row["selector"]
            if sel != "." + kind and sel not in names:
                names.append(sel)
    return names


def main():
    template = Path(sys.argv[1])
    root = Path(__file__).resolve().parents[2]
    raw = template.read_bytes()
    nl = "\r\n" if b"\r\n" in raw else "\n"
    lines = raw.decode("latin-1").split(nl)
    if MARK in lines:  # drop a previous block
        at = lines.index(MARK)
        end = lines.index("}", at)
        del lines[at:end + 2]
    try:
        at = lines.index("SECTIONS")
    except ValueError:
        sys.exit(f"{template}: no SECTIONS line")
    names = split_sections(root)  # mwldarm syntax: KEEP_SECTION { .a, .b, ... }
    block = [MARK, "KEEP_SECTION", "{"] + [
        "\t" + s + ("," if i < len(names) - 1 else "") for i, s in enumerate(names)] + ["}", ""]
    lines[at:at] = block
    template.write_bytes(nl.join(lines).encode("latin-1"))
    print(f"{template}: KEEP_SECTION for {len(names)} split sections")


if __name__ == "__main__":
    main()
