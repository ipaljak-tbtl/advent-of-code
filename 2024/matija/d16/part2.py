#!/usr/bin/env python3

from collections import defaultdict
import heapq
import sys

grid = list(map(list, map(str.strip, sys.stdin)))

rs = [(0, 1), (1, 0), (0, -1), (-1, 0)]

s = 0, 0
for i, row in enumerate(grid):
    for j, c in enumerate(row):
        if c == 'S':
            s = i, j

queue = []
dist = defaultdict(lambda: float('inf'))
heapq.heappush(queue, (0, s, 0, [s]))
dist[s, 0] = 0

min_cost = float('inf')
result = set()

while queue:
    c, (i, j), r, p = heapq.heappop(queue)
    if c > min(min_cost, dist[(i, j), r]):
        continue
    if grid[i][j] == 'E':
        min_cost = c
        result.update(p)
        continue

    for dr in (0, 1, -1, 2):
        nr = (r + dr + 4) % 4
        di, dj = rs[nr]
        ni, nj = i + di, j + dj
        nc = c + 1 + abs(dr) * 1000
        if grid[ni][nj] != '#' and nc <= dist[(ni, nj), nr]:
            heapq.heappush(queue, (nc, (ni, nj), nr, p + [(ni, nj)]))
            dist[(ni, nj), nr] = nc

print(len(result))
