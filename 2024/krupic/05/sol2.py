#!/usr/bin/env python3

import sys

grid = [list(l.strip()) for l in sys.stdin]

rows = len(grid)
cols = len(grid[0])

dirs = [(-1, 0), (0, 1), (1, 0), (0, -1)]

def cw(d):
    return (d + 1) % 4

def move(xy, dxy):
    x, y = xy
    dx, dy = dxy
    x += dx
    y += dy
    if 0 <= x < rows and 0 <= y < cols:
        return x, y

def simulate():
    visited = set()

    pos = next((x, y) for x in range(rows) for y in range(cols) if grid[x][y] == '^')
    d = 0

    while pos:
        if (pos, d) in visited:
            return True
        visited.add((pos, d))
        if npos := move(pos, dirs[d]):
            x, y = npos
            if grid[x][y] == '#':
                d = cw(d)
                continue
            else:
                pos = npos
        else:
            return False

sol = 0
for i in range(rows):
    for j in range(cols):
        if grid[i][j] == '.':
            grid[i][j] = '#'
            sol += simulate()
            grid[i][j] = '.'    

print(sol)

