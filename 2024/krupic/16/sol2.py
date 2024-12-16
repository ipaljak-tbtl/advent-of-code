#!/usr/bin/env python3

import sys
from queue import PriorityQueue as PQ

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

dist = {(start, 1): 0}
prev = {(start, 1): {}}
q = PQ()
q.put((0, (start, 1)))
while not q.empty():
    cost, (pos, d) = q.get()
    if (pos, d) in dist and dist[(pos, d)] < cost:
        continue

    if (fwd := move(pos, dirs[d])) and grid[fwd[0]][fwd[1]] != '#':
        n = (fwd, d)
        c = cost + 1
        if n not in dist or c < dist[n]:
            dist[n] = c
            q.put((c, n))
            prev[n] = {(pos, d)}
        elif c == dist[n]:
            prev[n].add((pos, d))

    for d2 in [(d-1)%4, (d+1)%4]:
        n = (pos, d2)
        c = cost + 1000
        if n not in dist or c < dist[n]:
            dist[n] = c
            q.put((c, n))
            prev[n] = {(pos, d)}
        elif c == dist[n]:
            prev[n].add((pos, d))

best_cost = min(dist[(end, d)] for d in range(4) if (end, d) in dist)
best = set()

def rec(s):
    best.add(s[0])
    for ps in prev[s]:
        rec(ps)

for d in range(4):
    s = (end, d)
    if (c := dist.get(s)) is not None and c == best_cost:
        rec(s)

print(len(best))

