#!/usr/bin/env python3

import sys

grid = [l.strip() for l in sys.stdin]

rows = len(grid)
cols = len(grid[0])

dirs = [(dx, dy) for dx in (-1, 0, 1) for dy in (-1, 0, 1) if not (dx, dy) == (0, 0)]

def move(xy, dxy):
    x, y = xy
    dx, dy = dxy
    x += dx
    y += dy
    if 0 <= x < rows and 0 <= y < cols:
        return x, y

def match(xy, d):
    x, y = xy
    for k, c in enumerate('XMAS'):
        if grid[x][y] != c:
            return False
        if k == len('XMAS') - 1:
            return True

        if t := move((x, y), d):
            x, y = t
        else:
            return False

sol = 0

for i in range(rows):
    for j in range(cols):
        for d in dirs:
            if match((i, j), d):
                sol += 1

print(sol)

