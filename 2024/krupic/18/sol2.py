#!/usr/bin/env python3

import sys
from queue import Queue

cols = rows = 70 + 1
limit = 1024

bytes_pos = []
for line in sys.stdin:
    x, y = map(int, line.split(','))
    bytes_pos.append((x, y))


dirs = [(-1, 0), (0, 1), (1, 0), (0, -1)]

def move(xy, dxy):
    x, y = xy
    dx, dy = dxy
    x += dx
    y += dy
    if 0 <= x < rows and 0 <= y < cols:
        return (x, y)

obstacles = set(bytes_pos[:limit])
for limit in range(1024+1, len(bytes_pos)):
    obs = bytes_pos[limit]
    obstacles.add(obs)

    start = (0, 0)
    end = (cols - 1, rows - 1)
    visited = {start}
    q = Queue()
    q.put(start)
    while not q.empty():
        pos = q.get()
        if pos == end:
            break

        for d in dirs:
            if (npos := move(pos, d)) and npos not in visited and npos not in obstacles:
                visited.add(npos)
                q.put(npos)
    if not end in visited:
        print(obs)
        break

