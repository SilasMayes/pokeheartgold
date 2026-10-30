# Matching DS build on Linux (HeartGold and SoulSilver)

Reproduced 2026-10-30 from `ctrl-cheeb-del/pokeheartgold` master
`2e0a4e000ff3c9ae5e8f41ad8a2e493eca49d87e` (the tree `SilasMayes/pokeheartgold` was forked from),
with no game-source changes. Both ROMs hash to the retail SHA-1s in the README, and the HeartGold
build is `cmp`-identical to a retail dump.

## Result

| Output | SHA-1 | Check |
|---|---|---|
| `build/heartgold.us/pokeheartgold.us.nds` | `4fcded0e2713dc03929845de631d0932ea2b5a37` | `heartgold.us/rom.sha1` OK, `cmp`-identical to a retail dump |
| `build/soulsilver.us/pokesoulsilver.us.nds` | `f8dc38ea20c17541a43b58c5e6d18c1732c7e582` | `soulsilver.us/rom.sha1` OK (see the note on SoulSilver dumps below) |
| `sub/build/ichneumon_sub.sbin` (ARM7, shared) | `1d0b3418b85fa8b5e1a9e345d3a182073cb968ac` | `sub/ichneumon_sub.sha1` OK |
| ARM9 static + 129 overlays, each game | per `<game>.us/main.sha1` | 130/130 OK, both games |
| NitroFS files, each game | per `<game>.us/filesystem.sha1` | 384/384 OK, both games |

## Inputs (proprietary, not in the repo)

| What | Where it goes | Identity |
|---|---|---|
| `mwccarm.zip` (Metrowerks CodeWarrior for NITRO, all 1.2 and 2.0 service packs; this copy ships a patched `lmgr8c.dll` in each version directory, so no `license.dat` is needed) | extract to `tools/mwccarm/` | `2.0/sp2p2/mwccarm.exe` sha256 `b1da5a2f…419a7`, `2.0/sp2p3/mwccarm.exe` `900e6b2c…cf86f2`; after `mwasmarm_patcher`, `2.0/sp2p3/mwasmarm.exe` `4ff88659…68114b`. These are the hashes the repo's object producers pin (`tools/*/profile.json`), so any mwccarm.zip that yields them works. (The zip used here has sha256 `02dc0da3…c56414`; `scripts/setup-macos.sh` expects a differently packed `dc386e37…`.) |
| `NitroSDK-3_2-20060901.7z` (top directory `NitroSDK-3_2-060901`) | `tools/bin/`, two templates in the repo root, one in `sub/` | sha256 `0ee935e34237cb1954e657083cd80a31ec9de1aeddd9468cceef684cac75b491`, the same archive `scripts/setup-macos.sh` checks. SDK **3.2**, not 4.2: pret's open SDK 4.2 templates are a different file and do not reproduce this link. |

Compilers used by the build: `2.0/sp2p2` (game code, ARM9 link), `2.0/sp2p3` (SDK, MSL, ARM7),
`2.0/sp2`, `2.0/sp1`, `2.0/sp1p5`, `2.0/base` and `1.2/sp2p3` for a handful of library objects (see
the per-object `MWCCVER` lines in `Makefile` and `sub/Makefile`).

## Host

Ubuntu 24.04 x86_64, Wine 9.0 (`9.0~repack-4build3`, 32-bit Wine is required: the Metrowerks tools
are 32-bit PE), GNU make 4.3, Python 3.12/3.13. Two cores: about 15 minutes per game from clean.

```sh
sudo dpkg --add-architecture i386 && sudo apt update
sudo apt install --no-install-recommends wine wine32:i386 wine64 \
    build-essential binutils-arm-none-eabi libpng-dev libpugixml-dev pkg-config p7zip-full python3
```

## Recipe

From the repository root:

```sh
# 1. Compilers
unzip -q /path/to/mwccarm.zip -d tools/          # -> tools/mwccarm/2.0/sp2p2/mwccarm.exe etc.

# 2. NitroSDK 3.2 (exactly the INSTALL.md layout)
7z x -o/tmp/nitrosdk /path/to/NitroSDK-3_2-20060901.7z
SDK=/tmp/nitrosdk/NitroSDK-3_2-060901
cp -r $SDK/tools/bin tools/bin
cp $SDK/include/nitro/specfiles/ARM9-TS.lcf.template $SDK/include/nitro/specfiles/mwldarm.response.template .
cp $SDK/include/nitro/specfiles/ARM7-TS.lcf.template sub/

# 3. Keep the split SDK data sections at link (see "Unified sections" below)
python3 -I docs/ds-build/keep_unified_sections.py ARM9-TS.lcf.template

# 4. Wine: quiet. (The Makefile already turns off Wine's display drivers.)
export WINEDEBUG=-all

# 5. Build. Generate fx_const.h first: with -j, lib/dsprot can otherwise compile before it exists.
make tools
make lib/include/nitro/fx/fx_const.h
make -j"$(nproc)" GAME_VERSION=HEARTGOLD     # ends with: build/heartgold.us/pokeheartgold.us.nds: OK
make -j"$(nproc)" GAME_VERSION=SOULSILVER    # ends with: build/soulsilver.us/pokesoulsilver.us.nds: OK
```

The default target already runs `tools/mwasmarm_patcher` over the assemblers and checks
`sub/ichneumon_sub.sha1`, `<game>.us/main.sha1`, `<game>.us/filesystem.sha1` and
`<game>.us/rom.sha1` along the way; `COMPARE=0` turns the checks off.

All the inputs land in ignored paths (`tools/mwccarm/**`, `tools/bin/**`, `*.lcf.template`,
`*.response.template`), so `git status` stays clean.

## Unified sections (the one non-obvious step)

The fork splits some SDK objects into named sections so they can be placed in retail order:
`lib/asm/nitro_sdk_data.s` into `.rodata.unified_00..03`, `.data.unified_00..01`,
`.bss.unified_00..05`, and `SND_util.c`/`SND_main.c`/... into `.rodata.snd_decibel`,
`.bss.snd_main` and so on. `tools/nitro-section-renames/patch_nitro_lcf.py` rewrites the generated
`main.lcf` to place them, but mwldarm still dead-strips any section nothing references. In the
retail link each of these was part of a whole `.rodata`/`.data`/`.bss` that was kept as a unit.
Split, `.rodata.unified_00` (0x100), `.rodata.unified_01` (0x600, no symbols at all) and
`.rodata.snd_decibel` (`SNDi_DecibelTable`, unused on ARM9) disappear, and so do two small `.bss`
pieces. The static module comes out 0x7F4 bytes short (`_0210E27C` lands at `0x0210DA7C`). Every
overlay that points into it then differs, which gives 119 of 130 `main.sha1` failures with all
overlays still the right size.

`docs/ds-build/keep_unified_sections.py` adds a `KEEP_SECTION { ... }` block listing every split
section from `tools/nitro-section-renames/nitro_link_order.json` (19 today) to the SDK's
`ARM9-TS.lcf.template`. After that, all 130 ARM9 modules match for both games. It edits only the
untracked SDK template, is idempotent, and follows the repo if the split list changes. This is
the "keep the split `.rodata`/`.data`/`.bss` unified sections" step ClickingMaster describes in
ssrecomp issue #9.

## Checking against a retail ROM

`docs/ds-build/extract_modules.py ROM.nds OUTDIR` writes the retail ARM9 static and every overlay,
decompressed (Nintendo backward LZ), as `main.sbin` and `ov_<id>.sbin`. The overlays hash to the
values in `<game>.us/main.sha1`, so a failing module can be `cmp`-ed against its retail
counterpart (overlay id N is the Nth `Overlay` in `main.lsf`). This is how the dead-stripped
sections above were found.

### SoulSilver dumps: check the ROM version byte

The repo targets SoulSilver US **ROM version 0** (`f8dc38ea…`, header byte 0x1E = 0x00). The dump
on hand here (`27a25c23aa1c0ecabe48a30a004b96c9dbc97730`, scene release 4840) is a later retail
revision: header byte 0x1E = 0x0A. Against the matching build it differs in only 663 bytes:
the version byte, the header CRC (0x15E), the header SHA-1 (0x378–0x38B), the header RSA
signature (0xF80–0xFFF), and 512 bytes inside `/a/2/6/2` (`files/demo/opening/gs_opening.narc`,
opening-demo graphics). ARM9, overlays, ARM7 and every other file are identical. So a dump with a
non-zero 0x1E will never hash to `f8dc38ea…`, and that is not a build problem. HeartGold US
`4fcded0e…` is ROM version 0.

## Things that cost time

- **Clean-tree race:** `make -j main` from a clean tree compiles `lib/dsprot` before
  `lib/include/nitro/fx/fx_const.h` is generated (`make tidy` deletes it). Step 5 generates it
  first.
- **First Wine start** takes ~25 s while Wine creates its prefix; later tool starts are quick. The
  Makefile already disables Wine's display drivers (`WINEDLLOVERRIDES`), which otherwise cost ~8 s
  per compile on a headless machine.
- **The object producers pin the real tools.** `tools/alarm-partition`, `arm7-alarm-partition`,
  `msl-new-partition`, `msl-d1-partition` and `dwc-iterator-advance` check the sha256 of
  `tools/mwccarm/2.0/sp2p{2,3}/mwccarm.exe` and the patched `mwasmarm.exe`. They also check Win32
  `Z:\...` include directories inside the DWARF of what they compile. An open toolchain
  (mid-kid's metroskrew 0.1.3, as the Platinum fork uses) compiles and links the tree, and its
  output agreed with the real tools on the 11 modules that matched before the KEEP_SECTION fix.
  But these producers reject its binaries by hash, and its native build writes `\home\...` with a
  literal `\.\` where they expect `Z:\home\...`. Getting there would mean editing those
  `profile.json` pins, so it was not pursued; the Windows tools under Wine are the route that
  matches without touching the repo.
