#!/usr/bin/env python3

import sys

grid = [list(map(int, l.strip())) for l in sys.stdin]

rows = len(grid)
cols = len(grid[0])

trailheads = [(i, j) for i in range(rows) for j in range(cols) if grid[i][j] == 0]

dirs = [(-1, 0), (0, 1), (1, 0), (0, -1)]

def move(xy, dxy):
    x, y = xy
    dx, dy = dxy
    x += dx
    y += dy
    if 0 <= x < rows and 0 <= y < cols:
        return x, y

def rec(x, y):
    if grid[x][y] == 9:
        return 1
    paths = 0
    for d in dirs:
        if nxy := move((x, y), d):
            nx, ny = nxy
            if grid[nx][ny] == grid[x][y] + 1:
                paths += rec(nx, ny)
    return paths

sol = 0

for x, y in trailheads:
    sol += rec(x, y)

print(sol)

