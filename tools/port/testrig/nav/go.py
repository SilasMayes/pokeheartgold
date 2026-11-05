#!/usr/bin/env python3
"""go.py X Z [--grass] [--face] [--max=N]: walk the player toward (X, Z) on the field.

Scans the tiles and map objects around the player through gdb (scan.py) and remembers every tile it has seen
on that map (nav/mem/). Plans with A* over the remembered tiles, with tiles not seen yet assumed open (so a
wall straight ahead is walked around, and a dead end is found when it comes into view), taking ledges,
one-way walls, water and objects into account (tall grass costs more unless --grass). Holds the direction
keys for each straight run. Exits 0 at the target (with --face: next to it, facing it), 3 when a script or
battle started (or the field isn't up), 1 when stuck, 2 when the game died.
"""
import heapq, json, os, subprocess, sys, time

H = os.environ.get("TESTRIG_RUN", os.path.expanduser("~/hgss_run"))
SRC = os.environ.get("HGSS_SRC", os.path.expanduser("~/src/pokeheartgold"))
SCAN = "/tmp/_scan.json"
MEM = f"{H}/mem"  # tiles seen per map (game data: stays out of git)
DIRS = {"Up": (0, -1), "Down": (0, 1), "Left": (-1, 0), "Right": (1, 0)}
FACING = {0: "Up", 1: "Down", 2: "Left", 3: "Right"}  # PlayerAvatar_GetFacingDirection
JUMP = {"Up": "IsJumpNorth", "Down": "IsJumpSouth", "Left": "IsJumpWest", "Right": "IsJumpEast"}
BLOCK_OUT = {"Up": "IsBlockedNorth", "Down": "IsBlockedSouth", "Left": "IsBlockedWest", "Right": "IsBlockedEast"}
BLOCK_IN = {"Up": "IsBlockedSouth", "Down": "IsBlockedNorth", "Left": "IsBlockedEast", "Right": "IsBlockedWest"}
TILE_TIME = float(os.environ.get("TILE_TIME", "0.75"))  # seconds per tile when walking
UNSEEN = 1.2  # cost of a tile not seen yet (a little more than a seen one, so known ways win ties)
MARGIN = 48   # how far outside the start-target box the search may go


def pid():
    r = subprocess.run(["pgrep", "-f", f"^{SRC}/build_(linux|asan)/main"], capture_output=True, text=True)
    return r.stdout.split()[0] if r.stdout.split() else None


def scan(radius=31):
    p = pid()
    if p is None:
        return None
    try:
        os.remove(SCAN)
    except FileNotFoundError:
        pass
    subprocess.run(["timeout", "60", "gdb", "-p", p, "-batch", "-ex", f'py R={radius}; OUT="{SCAN}"', "-x",
                    f"{H}/nav/scan.py"], capture_output=True)
    try:
        return json.load(open(SCAN))
    except Exception:
        return {"ok": False, "error": "no scan output"}


def remember(d):
    """Merge this scan into the map's memory; return (tiles, behaviors) with everything seen so far."""
    os.makedirs(MEM, exist_ok=True)
    name = f"{MEM}/m{d['matrix']}" + (f"_{d['map']}" if d.get("simple") else "") + ".json"
    try:
        m = json.load(open(name))
    except Exception:
        m = {"tiles": {}, "behaviors": {}}
    m["tiles"].update(d["tiles"])
    m["behaviors"].update({str(k): v for k, v in d["behaviors"].items()})
    with open(name + ".tmp", "w") as f:
        json.dump(m, f)
    os.replace(name + ".tmp", name)
    tiles = {tuple(map(int, k.split(","))): v for k, v in m["tiles"].items()}
    beh = {int(k): v for k, v in m["behaviors"].items()}
    return tiles, beh


_WARPS = {}


def map_warps(mapId):
    """The warp tiles of a map from the decomp's event data (ladders and stairs have no warp behavior)."""
    if mapId not in _WARPS:
        import glob, re
        src = SRC
        code = None
        for line in open(f"{src}/include/constants/maps.h"):
            m = re.match(r"#define MAP_\w+\s+(\d+)\s+//\s+MAP_(\w+)", line)
            if m and int(m.group(1)) == mapId:
                code = m.group(2)
                break
        tiles = set()
        if code:
            for f in glob.glob(f"{src}/files/fielddata/eventdata/zone_event/*_{code}.json"):
                for w in json.load(open(f)).get("warps", []):
                    tiles.add((w["x"], w["z"]))
        _WARPS[mapId] = tiles
    return _WARPS[mapId]


def key(name, ms):
    subprocess.run([f"{H}/key.sh", name, str(int(ms))])


def plan(d, tiles, beh, tx, tz, grass_ok, face):
    blocked = {(o["x"], o["z"]) for o in d["objects"] if not o["follow"] and o["id"] != 255}
    blocked |= {t for t in map_warps(d["map"]) if t != (tx, tz)}  # don't step on a warp on the way
    start = (d["x"], d["z"])
    x0 = max(0, min(start[0], tx) - MARGIN)
    x1 = min(d["mw"] * 32 - 1, max(start[0], tx) + MARGIN)
    z0 = max(0, min(start[1], tz) - MARGIN)
    z1 = min(d["mh"] * 32 - 1, max(start[1], tz) + MARGIN)

    def inside(t):
        return x0 <= t[0] <= x1 and z0 <= t[1] <= z1

    def preds(t):
        return beh.get(tiles[t] & 0xFF, []) if t in tiles else []

    def walkable(t):
        if not inside(t) or t in blocked:
            return False
        if t not in tiles:
            return True
        a = tiles[t]
        p = preds(t)
        if t == (tx, tz) and any(w.startswith("IsWarp") or w == "IsDoor" for w in p):
            return True  # a door asked for (its tile may be marked as a wall)
        if a & 0x8000 or "IsSurfableWater" in p or "IsWaterfall" in p:
            return False
        if any(w.startswith("IsWarp") or w == "IsDoor" for w in p) and t != (tx, tz):
            return False
        return True

    def moves(s):
        for dname, (dx, dz) in DIRS.items():
            n = (s[0] + dx, s[1] + dz)
            if not inside(n) or BLOCK_OUT[dname] in preds(s):
                continue
            p = preds(n)
            if JUMP[dname] in p:
                land = (n[0] + dx, n[1] + dz)
                if walkable(land):
                    yield dname + "!", land, 2
                continue
            if any(j in p for j in JUMP.values()) or BLOCK_IN[dname] in p or not walkable(n):
                continue
            cost = 1 if n in tiles else UNSEEN
            if not grass_ok and ("IsTallGrass" in p or "IsVeryTallGrass" in p):
                cost = 8
            yield dname, n, cost

    goals = set()
    if face:
        for dx, dz in DIRS.values():
            goals.add((tx - dx, tz - dz))
    else:
        goals.add((tx, tz))

    def h(t):
        return min(abs(t[0] - g[0]) + abs(t[1] - g[1]) for g in goals)

    dist = {start: 0}
    prev = {}
    pq = [(h(start), 0, start)]
    end = None
    while pq:
        f, c, s = heapq.heappop(pq)
        if c > dist[s]:
            continue
        if s in goals:
            end = s
            break
        for dname, n, cost in moves(s):
            if c + cost < dist.get(n, 1e9):
                dist[n] = c + cost
                prev[n] = (s, dname)
                heapq.heappush(pq, (c + cost + h(n), c + cost, n))
    if end is None:  # walled in: the reachable tile closest to the target
        end = min(dist, key=lambda t: (h(t), dist[t]))
    path, route = [], [end]
    s = end
    while s != start:
        s, dname = prev[s]
        path.append(dname)
        route.append(s)
    path.reverse()
    route.reverse()
    known = all(t in tiles for t in route)
    return path, end, end in goals, known, route


def run_of(path, route, tiles):
    """The first straight run of the path, cut where it would step onto a tile not seen yet."""
    n = 1
    while n < len(path) and path[n] == path[0] and route[n + 1] in tiles:
        n += 1
    return path[0], n


def main():
    args = [a for a in sys.argv[1:] if not a.startswith("--")]
    tx, tz = int(args[0]), int(args[1])
    grass_ok = "--grass" in sys.argv
    face = "--face" in sys.argv
    maxit = 60
    for a in sys.argv:
        if a.startswith("--max="):
            maxit = int(a[6:])
    last = None
    stuck = 0
    for it in range(maxit):
        d = scan()
        if d is None:
            print("died")
            return 2
        if not d.get("ok"):
            print("no field:", d.get("error"))
            return 3
        if d["busy"]:
            print(f"busy at {d['x']} {d['z']} map {d['map']}")
            return 3
        pos = (d["x"], d["z"])
        if last is not None and pos == last:
            stuck += 1
            if stuck >= 4:
                print(f"stuck at {pos[0]} {pos[1]}")
                return 1
        else:
            stuck = 0
        tiles, beh = remember(d)
        path, end, reached, known, route = plan(d, tiles, beh, tx, tz, grass_ok, face)
        if not path:
            if reached:
                if face:
                    want = next(k for k, (dx, dz) in DIRS.items() if (pos[0] + dx, pos[1] + dz) == (tx, tz))
                    if FACING.get(d["facing"]) != want:
                        key(want, 60)
                        time.sleep(0.5)
                print(f"at {pos[0]} {pos[1]} map {d['map']}")
                return 0
            print(f"no way on from {pos[0]} {pos[1]} map {d['map']}")
            return 1
        if os.environ.get("GO_DEBUG"):
            print(f"[go] at {pos} facing {d['facing']} -> {end} {'known' if known else 'guess'} "
                  f"{''.join(m[0] for m in path[:60])}", file=sys.stderr)
        dname, n = run_of(path, route, tiles)
        n = min(n, 12)
        if dname.endswith("!"):  # a ledge: one press jumps it
            key(dname[:-1], 200)
            time.sleep(TILE_TIME * 1.5)
        elif n == 1:
            key(dname, 450)
            time.sleep(TILE_TIME * 0.9)
        else:
            key(dname, max(450, (n - 0.8) * TILE_TIME * 1000))
            time.sleep(TILE_TIME * 0.6)
        last = pos
    print("gave up")
    return 1


if __name__ == "__main__":
    sys.exit(main())
