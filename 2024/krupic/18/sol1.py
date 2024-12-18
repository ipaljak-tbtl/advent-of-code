#!/usr/bin/env python3

import sys
from queue import Queue

cols = rows = 70 + 1
limit = 1024

bytes_pos = []
for line in sys.stdin:
    x, y = map(int, line.split(','))
    bytes_pos.append((x, y))

obstacles = set(bytes_pos[:limit])

dirs = [(-1, 0), (0, 1), (1, 0), (0, -1)]
start = (0, 0)
end = (cols - 1, rows - 1)

def move(xy, dxy):
    x, y = xy
    dx, dy = dxy
    x += dx
    y += dy
    if 0 <= x < rows and 0 <= y < cols:
        return (x, y)

dist = {start: 0}
q = Queue()
q.put(start)
while not q.empty():
    pos = q.get()

    for d in dirs:
        if (npos := move(pos, d)) and npos not in dist and npos not in obstacles:
            dist[npos] = dist[pos] + 1
            q.put(npos)

print(dist[end])
