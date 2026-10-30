#!/usr/bin/env python3
"""Extract the ARM9 static module and every ARM9 overlay from a retail NDS ROM, decompressed.

usage: python3 -I docs/ds-build/extract_modules.py ROM.nds OUTDIR

Writes OUTDIR/main.sbin and OUTDIR/ov_<id>.sbin, comparable to the build's
build/<game>.us/main.sbin and the overlay .sbin files listed in <game>.us/main.sha1
(the overlay with id N is the Nth "Overlay" in main.lsf). The static module's
compressed_static_end word in _start_ModuleParams is cleared again, as in the
uncompressed build output.
"""
import struct
import sys
from pathlib import Path


def blz_decode(data):
    """Nintendo backward LZ (compstatic / BLZ) decoder."""
    end = len(data)
    word0, inc_len = struct.unpack_from("<II", data, end - 8)
    enc_len, hdr_len = word0 & 0xFFFFFF, word0 >> 24
    out = bytearray(data) + bytearray(inc_len)
    src, dst, limit = end - hdr_len, end + inc_len, end - enc_len
    while src > limit:
        src -= 1
        flags = data[src]
        for _ in range(8):
            if src <= limit:
                break
            if flags & 0x80:
                hi, lo = data[src - 1], data[src - 2]
                src -= 2
                v = (hi << 8) | lo
                n, disp = (v >> 12) + 3, (v & 0xFFF) + 3
                for _ in range(n):
                    dst -= 1
                    out[dst] = out[dst + disp]
            else:
                src -= 1
                dst -= 1
                out[dst] = data[src]
            flags = (flags << 1) & 0xFF
    return bytes(out)


def main():
    rom = Path(sys.argv[1]).read_bytes()
    out = Path(sys.argv[2])
    out.mkdir(parents=True, exist_ok=True)
    arm9_off, _entry, arm9_ram, arm9_size = struct.unpack_from("<IIII", rom, 0x20)
    fat_off = struct.unpack_from("<I", rom, 0x48)[0]
    ovt_off, ovt_size = struct.unpack_from("<II", rom, 0x50)

    arm9 = rom[arm9_off:arm9_off + arm9_size]
    magic, params_off = struct.unpack_from("<II", rom, arm9_off + arm9_size)
    assert magic == 0xDEC00621, hex(magic)
    comp_end_addr = struct.unpack_from("<I", arm9, params_off + 0x14)[0]
    if comp_end_addr:
        n = comp_end_addr - arm9_ram
        arm9 = bytearray(blz_decode(arm9[:n]) + arm9[n:])
        struct.pack_into("<I", arm9, params_off + 0x14, 0)
    (out / "main.sbin").write_bytes(arm9)

    for i in range(ovt_size // 32):
        ov_id, ram, size, bss, s0, s1, file_id, flag = struct.unpack_from("<8I", rom, ovt_off + 32 * i)
        start, stop = struct.unpack_from("<II", rom, fat_off + 8 * file_id)
        blob = rom[start:stop]
        if flag >> 24 & 1:
            blob = blz_decode(blob[: flag & 0xFFFFFF])
        assert len(blob) == size, (ov_id, len(blob), size)
        (out / f"ov_{ov_id}.sbin").write_bytes(blob)
    print(f"main.sbin {len(arm9):#x} bytes, {ovt_size // 32} overlays -> {out}")


if __name__ == "__main__":
    main()
