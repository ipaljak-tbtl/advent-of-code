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
    fence = 0
    x, y = start
    plant = grid[x][y]

    q = Queue()
    q.put(start)
    visited.add((x, y))
    while not q.empty():
        tile = q.get()
        area += 1
        for d in dirs:
            if ntile := move(tile, d):
                nx, ny = ntile
                if grid[nx][ny] == plant:
                    if ntile not in visited:
                        visited.add(ntile)
                        q.put(ntile)
                else:
                    fence += 1
            else:
                fence += 1
    return area, fence

for i in range(rows):
    for j in range(cols):
        if (i, j) not in visited:
            area, fence = bfs((i, j))
            sol += area * fence

print(sol)

