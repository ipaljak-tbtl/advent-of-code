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

def bfs(start, end):
    dist = {start: 0}
    q = Q()
    q.put(start)
    while not q.empty():
        pos = q.get()

        for d in dirs:
            if (npos := move(pos, d)):
                if grid[npos[0]][npos[1]] != '#' and npos not in dist:
                    dist[npos] = dist[pos] + 1
                    q.put(npos)
    return dist

from_start = bfs(start, end)
from_end = bfs(end, start)

best_normal = from_start[end]

def cheat(pos, c, prev=None):
    if c == 1:
        return [(prev, pos, from_end[pos])] if pos in from_end else []

    cs = []
    for d in dirs:
        if (npos := move(pos, d)):
            if npos != prev:
                cs += cheat(npos, c-1, prev=pos)
    return cs

savings = defaultdict(int)
for pos, dist in from_start.items():
    for d in dirs:
        if (c1_pos := move(pos, d)):
            if grid[c1_pos[0]][c1_pos[1]] == '#':
                for c2_pos, npos, to_end in cheat(c1_pos, 2):
                    c = dist + 2 + to_end
                    if c < best_normal:
                        savings[best_normal - c] += 1

print(sum(c for s, c in savings.items() if s >= 100))
