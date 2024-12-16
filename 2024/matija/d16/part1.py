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
heapq.heappush(queue, (0, s, 0))
dist[s, 0] = 0

while queue:
    c, (i, j), r = heapq.heappop(queue)
    if grid[i][j] == 'E':
        print(c)
        break

    for dr in (0, 1, -1, 2):
        nr = (r + dr + 4) % 4
        di, dj = rs[nr]
        ni, nj = i + di, j + dj
        nc = c + 1 + abs(dr) * 1000
        if grid[ni][nj] != '#' and nc < dist[(ni, nj), nr]:
            heapq.heappush(queue, (nc, (ni, nj), nr))
            dist[(ni, nj), nr] = nc
