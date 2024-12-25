import sys
import copy

sys.setrecursionlimit(1000000)
track = []
with open(sys.argv[1], 'r') as file:
    for line in file:
        track.append(list(line.strip()))

start = None
for x in range(len(track)):
    for y in range(len(track[0])):
        if track[x][y] == 'S':
            start = x, y
        if track[x][y] == 'E':
            end = x, y

def outside(x, y):
    return x < 0 or x >= len(track) or y < 0 or y >= len(track[0])

def neighbours(x, y):
    return [(x + dx, y + dy) for dx, dy in [(-1, 0), (1, 0), (0, -1), (0, 1)]]

INF = 1e18
mem = dict()
mem[(end[0], end[1])] = 0
def dfs(x, y):
    if (x, y) in mem:
        return mem[(x, y)]
    if outside(x, y):
        return INF
    if track[x][y] == '#':
        return INF

    mem[(x, y)] = INF

    for a, b in neighbours(x, y):
        mem[(x, y)] = min(mem[(x, y)], dfs(a, b) + 1)

    return mem[(x, y)]

original = dfs(start[0], start[1])

CHEAT_LEN = 20

cnt = 0

cheats = set()
for x in range(len(track)):
    for y in range(len(track[0])):
        if (x, y) not in mem or mem[(x, y)] == INF:
            continue

        for c in range(len(track)):
            for d in range(len(track[0])):
                dist = abs(c-x) + abs(d-y)
                if dist > CHEAT_LEN:
                    continue
                if (c, d) not in mem:
                    continue

                if original - mem[(x, y)] + dist + mem[(c, d)] + 100 <= original:
                    cheats.add((x, y, c, d))

        
print(len(cheats))
