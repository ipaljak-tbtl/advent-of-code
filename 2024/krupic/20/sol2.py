#!/usr/bin/env python3

import sys
from collections import defaultdict
from queue import Queue as Q

grid = [l.strip() for l in sys.stdin]

rows = len(grid)
cols = len(grid[0])

dirs = [(-1, 0), (0, 1), (1, 0), (0, -1)]
start = next((i, j) for i in range(rows) for j in range(cols) if grid[i][j] == 'S')
end = next((i, j) for i in range(rows) for j in range(cols) if grid[i][j] == 'E')

def move(xy, dxy):
    x, y = xy
    dx, dy = dxy
    x += dx
    y += dy
    if 0 <= x < rows and 0 <= y < cols:
        return (x, y)

def bfs(start, cheat=False):
    dist = {start: 0}
    q = Q()
    q.put(start)
    while not q.empty():
        pos = q.get()

        if cheat and dist[pos] == 20:
            continue

        for d in dirs:
            if (npos := move(pos, d)):
                if (cheat or grid[npos[0]][npos[1]] != '#') and npos not in dist:
                    dist[npos] = dist[pos] + 1
                    q.put(npos)
    return dist

from_start = bfs(start)
from_end = bfs(end)

best_normal = from_start[end]

def cheat(pos):
    return [(c_end, c_len + from_end[c_end]) for c_end, c_len in bfs(pos, cheat=True).items() if grid[c_end[0]][c_end[1]] != '#']

savings = defaultdict(int)
for pos, dist in from_start.items():
    c_ends = set()
    for npos, to_end in cheat(pos):
        if npos in c_ends:
            continue
        c_ends.add(npos)
        c = dist + to_end
        if c < best_normal:
            savings[best_normal - c] += 1

print(sum(c for s, c in savings.items() if s >= 100))
