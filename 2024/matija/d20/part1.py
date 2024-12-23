#!/usr/bin/env python3

import sys

grid = list(map(list, map(str.strip, sys.stdin)))
n = len(grid)

rs = [(0, 1), (1, 0), (0, -1), (-1, 0)]

e = next((i, j) for i in range(n) for j in range(n) if grid[i][j] == 'E')

dist = {}
dist[e] = 0

path = [e]
i, j = e
while grid[i][j] != 'S':
    for di, dj in rs:
        ni, nj = i + di, j + dj
        if grid[ni][nj] != '#' and (ni, nj) not in dist:
            dist[ni, nj] = dist[i, j] + 1
            i, j = ni, nj
            path.append((i, j))
            break

DURATION = 2

total = 0
for csi, csj in path:
    for di in range(-DURATION, DURATION + 1):
        for dj in range(-DURATION, DURATION + 1):
            cost = abs(di) + abs(dj)
            cei, cej = csi + di, csj + dj
            if (cost <= DURATION and 0 <= cei < n and 0 <= cej < n
                    and grid[cei][cej] != '#'
                    and dist[csi, csj] - dist[cei, cej] - cost >= 100):
                total += 1

print(total)
