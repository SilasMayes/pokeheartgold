# Test rig for the Linux port

Scripts that play HeartGold on the Linux port under Xvfb: boot and continue a save, walk to a tile, get
through scripts and battles, catch, heal, and run the ASan/UBSan build through a fixed path (the Thor rule's
desktop gate). They read the game through gdb (calling the game's own functions), press keys with xdotool and
look at pixels with ImageMagick. Nothing here is from the ROM; the game data and saves stay outside git.

## Setup
```sh
tools/port/testrig/setup.sh            # links the scripts into ~/hgss_run, writes ~/hgss_run/env.sh, starts Xvfb :99
. ~/hgss_run/env.sh
```
- **Builds** (in the checkout `setup.sh` came from):
  - `meson setup build_linux -Dbuild_target=linux -Dlibntr:card_game_code=IPKE,IPGE && ninja -C build_linux`
  - `meson setup build_asan -Dbuild_target=linux -Dport_sanitize=address,undefined -Dlibntr:card_game_code=IPKE,IPGE && ninja -C build_asan`
  - Two cores take about an hour from scratch; incremental builds are seconds.
- **Game data**: `~/hgss_run/hg` is the port's data directory for HeartGold (the ROM as the port's cart import
  extracts it, plus `sim_config.ini` and `save.bin`). `GAMEDIR=ss` runs `~/hgss_run/ss` (SoulSilver).
- **`hg/sim_config.ini`** (`setup.sh` copies `sim_config.ini` if there is none): `InternalResolutionScale=1`
  (~25 vblanks/s under Xvfb + llvmpipe on 2 cores; 10x gave ~15), A = `z`, B = `x`, Start = Return.
- **Milestone saves** live on the Mac: `/Users/silasmayes/pokemon-port/saves/hgss/<milestone>.bin` (index in
  `INDEX.txt` there). Copy one to `~/hgss_run/hg/save.bin` and `cont.sh`.

## Running
- `run.sh LOG` / `run_asan.sh LOG` start the game (detached: `(setsid ~/hgss_run/run.sh LOG &)`), `cont.sh`
  boots to the menu and picks CONTINUE, `kill.sh` stops it. `newgame.sh` drives a fresh start to the field.
- The window sits at (100, 100): top screen 512x384 from there, bottom screen below it (2x the DS's).
- `stop.sh` stops every helper and releases the keys: a helper killed while it holds a key leaves the key
  held, and the game sees it pressed.

## Scripts
| Script | What it does |
|---|---|
| `nav/go.py X Z [--face] [--grass] [--max=N]` | Walks to a tile: scans the loaded map blocks and objects (`nav/scan.py`), remembers every tile seen per map (`~/hgss_run/mem`), plans A* with tiles not seen yet assumed open, keeps off the map's warps (from `files/fielddata/eventdata`) unless one is the target, holds keys per straight run. Exit 0 arrived, 3 a script or battle started, 1 stuck, 2 the game died. |
| `nav/travel.sh X Z [go.py flags]` | `go.py`, then `battle.sh` whenever something starts, until it arrives. |
| `nav/battle.sh [fight\|run]` | Through a battle or script: FIGHT (or RUN) at the command menu, the strongest move with PP at the move menu (`bmon.sh`), B in the Pokégear, A otherwise. |
| `nav/catch.sh [TRIES]` | Throws the first ball in the bag at each command menu until caught or out of tries. |
| `nav/heal.sh` | In a Pokémon Center's 1F: the nurse, then out of the door. |
| `nav/sprout.sh` | Violet City to Sprout Tower 3F (ladders and all). |
| `grass.sh`, `talk.sh`, `save.sh` | Step in grass until an encounter; A until free; save through the touch menu (and back the save up). |
| `nav/state.sh` | `free`, `script`, `app <init function>`, `nofield` or `dead`. |
| `nav/party.sh`, `nav/bmon.sh`, `nav/item.sh ITEM_…`, `nav/var.sh VAR_…\|FLAG_…`, `pos.sh` | Party, the battler's moves and PP, bag counts, script vars and flags, the player's tile. |
| `nav/show.py [R]` | ASCII map around the player. |
| `nav/gate_rival.sh`, `nav/gate_elm.sh`, `nav/gate_violet.sh` | ASan/UBSan runs over a fixed path from a milestone save; they print the sanitizer report count. |

## Gotchas
- gdb calls game functions: never scan during a warp (`scan.py` refuses while the map is loading). Under the
  ASan build cast libc calls in gdb (`((void *(*)(unsigned long))malloc)(4)`).
- `pgrep -f`/`pkill -f` match their own shell when the pattern is in the command line: anchor them (`^…`).
- The game's stdout is fully buffered and lost on `kill -9`: print to stderr when debugging.
- Options → Battle Style: SET, or A on "switch Pokémon?" walks into the party screen. A on "forget a move?"
  forgets the first move.
- Ladders: step onto the ladder tile, then press the direction again.
- Event coordinates (`files/fielddata/eventdata/zone_event/*.json`) are global on the overworld, local indoors.
