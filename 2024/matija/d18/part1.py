#!/usr/bin/env python3

from collections import deque
import sys

n = 71
b = 1024

grid = [['.'] * n for _ in range(n)]

for _ in range(b):
    x, y = map(int, next(sys.stdin).split(','))
    grid[y][x] = '#'

queue = deque()
visited = set()
queue.append((0, 0, 0))
visited.add((0, 0))

while queue:
    i, j, c = queue.popleft()
    if i + 1 == n and j + 1 == n:
        print(c)
        break

    for di, dj in [(1, 0), (-1, 0), (0, 1), (0, -1)]:
        ni, nj = i + di, j + dj
        if (0 <= ni < n and 0 <= nj < n and grid[ni][nj] != '#'
                and (ni, nj) not in visited):
            queue.append((ni, nj, c + 1))
            visited.add((ni, nj))
