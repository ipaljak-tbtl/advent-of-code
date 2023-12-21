#!/usr/bin/env python3

import sys
from collections import defaultdict, deque

delta = [(-1, 0), (1, 0), (0, -1), (0, 1)]

grid = list(map(str.strip, sys.stdin))
rows, cols = len(grid), len(grid[0])
print(rows, cols)
start = next((i, j) for i in range(rows) for j in range(cols) if grid[i][j] == 'S')

def adj_iter(i, j):
    for di, dj in delta:
        ni, nj = i + di, j + dj
        if 0 <= ni < rows and 0 <= nj < cols and grid[ni][nj] != '#':
            yield ni, nj

front = {start}
for _ in range(64):
    front = {npos for pos in front for npos in adj_iter(*pos)}
print(len(front))

