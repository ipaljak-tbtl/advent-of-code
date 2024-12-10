#!/usr/bin/env python3

import sys


def search(grid, i, j, peaks):
    n = len(grid)
    h = grid[i][j]
    if h == 9:
        peaks.add((i, j))
    else:
        for di, dj in [(1, 0), (-1, 0), (0, 1), (0, -1)]:
            ni, nj = i + di, j + dj
            if 0 <= ni < n and 0 <= nj < n and grid[ni][nj] == h + 1:
                search(grid, ni, nj, peaks)


grid = [list(map(int, l.strip())) for l in sys.stdin]

total = 0
for i, row in enumerate(grid):
    for j, h in enumerate(row):
        if h == 0:
            peaks = set()
            search(grid, i, j, peaks)
            total += len(peaks)

print(total)
