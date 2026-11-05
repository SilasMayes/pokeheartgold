# gdb -p PID -batch -ex 'py R=20; OUT="/tmp/scan.json"' -x scan.py
# Writes the player's position, the tile attributes around it and the field's map objects as JSON.
import gdb, json

def ev(s):
    return int(gdb.parse_and_eval(s))

try:
    R
except NameError:
    R = 20
try:
    OUT
except NameError:
    OUT = "/tmp/scan.json"

res = {"ok": False}
try:
    if ev("sFieldSysPtr == 0") or ev("sFieldSysPtr->playerAvatar == 0"):
        raise Exception("no field")
    fs = "sFieldSysPtr"
    px = ev(f"PlayerAvatar_GetXCoord({fs}->playerAvatar)")
    pz = ev(f"PlayerAvatar_GetZCoord({fs}->playerAvatar)")
    facing = ev(f"PlayerAvatar_GetFacingDirection({fs}->playerAvatar)")
    busy = ev(f"!({fs}->taskman == 0 && {fs}->processManager->child == 0)")
    mapId = ev(f"{fs}->location->mapId")
    buf = ev("(unsigned long)((void *(*)(unsigned long))malloc)(4)")
    q = f"((const FieldTerrainQueries *){fs}->terrainQueries)->getAttributes"
    tiles = {}
    inf = gdb.selected_inferior()
    simple = ev(f"{q} == Terrain_GetAttributes_Simple")
    if not simple and (ev(f"{fs}->mapLoadManager == 0") or ev(f"{fs}->mapLoadManager->stride") == 0
                       or ev(f"{fs}->mapLoadManager->width * {fs}->mapLoadManager->height") == 0):
        raise Exception("map loading")  # mid-warp: the game divides by the stride
    mw = ev(f"MapMatrix_GetWidth({fs}->mapMatrix)")
    mh = ev(f"MapMatrix_GetHeight({fs}->mapMatrix)")
    for bz in range(max(0, pz - R) // 32, min(mh - 1, (pz + R) // 32) + 1):
        for bx in range(max(0, px - R) // 32, min(mw - 1, (px + R) // 32) + 1):
            if simple:
                ptr = ev(f"(unsigned long)TerrainAttributes_Get({bx} + {bz} * MapMatrix_GetWidth({fs}->mapMatrix), {fs}->terrainAttributes)")
            else:
                if not ev(f"MapLoadManager_GetMapSlotAt({fs}->mapLoadManager, {bx * 32}, {bz * 32}, (u8*){buf})"):
                    continue
                slot = ev(f"*(u8*){buf}")
                if slot > 3 or ev(f"((MapLoadManager *){fs}->mapLoadManager)->maps[{slot}] == 0"):
                    continue  # the block is still loading (GetPermissions would read a NULL map)
                ptr = ev(f"(unsigned long)MapLoadManager_GetPermissions({fs}->mapLoadManager, {slot})")
            if ptr == 0:
                continue
            mem = bytes(inf.read_memory(ptr, 2048))
            for tz in range(32):
                for tx in range(32):
                    x, z = bx * 32 + tx, bz * 32 + tz
                    if abs(x - px) <= R and abs(z - pz) <= R:
                        tiles[f"{x},{z}"] = mem[2 * (tz * 32 + tx)] | mem[2 * (tz * 32 + tx) + 1] << 8
    behaviors = sorted(set(a & 0xFF for a in tiles.values()))
    preds = ["IsJumpNorth", "IsJumpSouth", "IsJumpWest", "IsJumpEast", "IsTallGrass", "IsVeryTallGrass",
             "IsSurfableWater", "IsBlockedNorth", "IsBlockedSouth", "IsBlockedWest", "IsBlockedEast",
             "IsDoor", "IsCounter", "IsWarpNorth", "IsWarpSouth", "IsWarpEast", "IsWarpWest",
             "CanGenerateWalkingEncounters", "IsWaterfall", "IsLadderNorth", "IsLadderSouth",
             "IsWarpEntranceNorth", "IsWarpEntranceSouth", "IsWarpEntranceEast", "IsWarpEntranceWest",
             "IsWarpStairsEast", "IsWarpStairsWest", "IsWarpPanel"]
    btab = {}
    for b in behaviors:
        btab[b] = [p for p in preds if ev(f"MetatileBehavior_{p}({b})")]
    gdb.parse_and_eval(f"((void (*)(void *))free)((void*){buf})")
    follow = ev(f"(unsigned long)FollowMon_GetMapObject({fs})")
    objs = []
    n = ev(f"{fs}->mapObjectManager->objectCount")
    base = f"{fs}->mapObjectManager->objects"
    for i in range(n):
        o = f"{base}[{i}]"
        if not (ev(f"{o}.flags") & 1):
            continue
        addr = ev(f"(unsigned long)&{o}")
        objs.append({"i": i, "id": ev(f"{o}.id"), "x": ev(f"{o}.currentX"), "z": ev(f"{o}.currentZ"),
                     "sprite": ev(f"{o}.spriteId"), "type": ev(f"{o}.type"), "movement": ev(f"{o}.movement"),
                     "script": ev(f"{o}.scriptId"), "facing": ev(f"{o}.currentFacing"),
                     "param0": ev(f"{o}.param[0]"), "follow": addr == follow})
    matrix = ev(f"MapMatrix_GetMatrixId({fs}->mapMatrix)")
    res = {"ok": True, "x": px, "z": pz, "facing": facing, "busy": busy, "map": mapId, "matrix": matrix,
           "simple": simple, "mw": mw, "mh": mh,
           "tiles": tiles, "behaviors": btab, "objects": objs}
except Exception as e:
    res = {"ok": False, "error": str(e)}
with open(OUT, "w") as f:
    json.dump(res, f)
