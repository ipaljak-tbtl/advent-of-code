#!/usr/bin/env python3

import sys
from collections import defaultdict

grid = [l.strip() for l in sys.stdin]

rows = len(grid)
cols = len(grid[0])

antennas = defaultdict(list)

for i in range(rows):
    for j in range(cols):
        if (c := grid[i][j]).isalnum():
            antennas[c].append((i,j))

def move(xy, dxy):
    x, y = xy
    dx, dy = dxy
    x += dx
    y += dy
    if 0 <= x < rows and 0 <= y < cols:
        return x, y

sol = set()

for pos in antennas.values():
    for i in range(len(pos)):
        for j in range(i+1, len(pos)):
            xi, yi = pos[i]
            xj, yj = pos[j]
            dx = xj - xi
            dy = yj - yi
            if anti := move(pos[j], (dx, dy)):
                sol.add(anti)
            if anti := move(pos[i], (-dx, -dy)):
                sol.add(anti)

for i in range(rows):
    for j in range(cols):
        if (i,j) in sol and grid[i][j] == '.':
            print('#', end='')
        else:
            print(grid[i][j], end='')
    print()

print(len(sol))

