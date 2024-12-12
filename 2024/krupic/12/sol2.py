#!/usr/bin/env python3

import sys
from queue import Queue

grid = [l.strip() for l in sys.stdin]

rows = len(grid)
cols = len(grid[0])

dirs = [(-1, 0), (0, 1), (1, 0), (0, -1)]

def move(xy, dxy):
    x, y = xy
    dx, dy = dxy
    x += dx
    y += dy
    if 0 <= x < rows and 0 <= y < cols:
        return x, y

sol = 0

visited = set()

def bfs(start):
    area = 0
    border = {i: set() for i in range(len(dirs))}
    x, y = start
    plant = grid[x][y]

    q = Queue()
    q.put(start)
    visited.add((x, y))
    while not q.empty():
        tile = q.get()
        area += 1
        for di, d in enumerate(dirs):
            if ntile := move(tile, d):
                nx, ny = ntile
                if grid[nx][ny] == plant:
                    if ntile not in visited:
                        visited.add(ntile)
                        q.put(ntile)
                else:
                    border[di].add(tile)
            else:
                border[di].add(tile)

    sides = 0

    for di, b_tiles in border.items():
        b_visited = set()
        side_dirs = [(di-1)%4, (di+1)%4]
        for start in b_tiles:
            if start in b_visited:
                continue
            b_visited.add(start)
            for si in side_dirs:
                b_tile = start
                while (ntile := move(b_tile, dirs[si])) and ntile in b_tiles and ntile not in b_visited:
                    b_visited.add(ntile)
                    b_tile = ntile
            sides += 1

    return area, sides

for i in range(rows):
    for j in range(cols):
        if (i, j) not in visited:
            area, sides = bfs((i, j))
            sol += area * sides

print(sol)

