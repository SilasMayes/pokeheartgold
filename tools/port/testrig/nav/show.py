#!/usr/bin/env python3
"""show.py [R]: ASCII map around the player from a scan: @ player, # wall, . floor, " grass, ~ water,
v^<> ledges (jump direction), D door/warp, o object, f follower."""
import json, subprocess, sys, os
sys.path.insert(0, os.path.dirname(__file__))
import go
R = int(sys.argv[1]) if len(sys.argv) > 1 else 31
d = go.scan(R)
if not d or not d.get("ok"):
    print(d); sys.exit(1)
tiles = {tuple(map(int, k.split(","))): v for k, v in d["tiles"].items()}
beh = {int(k): v for k, v in d["behaviors"].items()}
objs = {(o["x"], o["z"]): ("f" if o["follow"] else "o") for o in d["objects"]}
px, pz = d["x"], d["z"]
xs = [t[0] for t in tiles]; zs = [t[1] for t in tiles]
print(f"player {px} {pz} map {d['map']} x {min(xs)}..{max(xs)} z {min(zs)}..{max(zs)}")
for z in range(min(zs), max(zs) + 1):
    row = []
    for x in range(min(xs), max(xs) + 1):
        t = (x, z)
        if t == (px, pz): c = "@"
        elif t in objs: c = objs[t]
        elif t not in tiles: c = " "
        else:
            a = tiles[t]; p = beh.get(a & 0xFF, [])
            if "IsJumpSouth" in p: c = "v"
            elif "IsJumpNorth" in p: c = "^"
            elif "IsJumpWest" in p: c = "<"
            elif "IsJumpEast" in p: c = ">"
            elif any(w.startswith("IsWarp") or w == "IsDoor" for w in p): c = "D"
            elif a & 0x8000: c = "#"
            elif "IsSurfableWater" in p: c = "~"
            elif "IsTallGrass" in p or "IsVeryTallGrass" in p: c = '"'
            else: c = "."
        row.append(c)
    print(f"{z:4d} " + "".join(row))
