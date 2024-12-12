#!/usr/bin/env python3

from collections import deque
import sys


def cost(grid, n, i, j, visited):
    if (i, j) in visited:
        return 0

    q = deque()
    q.append((i, j))
    visited.add((i, j))

    area = 0
    per = 0

    while q:
        i, j = q.popleft()
        area += 1

        for di, dj in [(1, 0), (-1, 0), (0, 1), (0, -1)]:
            ni, nj = i + di, j + dj
            if (not (0 <= ni < n) or not (0 <= nj < n)
                    or grid[ni][nj] != grid[i][j]):
                per += 1
            elif (ni, nj) not in visited:
                visited.add((ni, nj))
                q.append((ni, nj))

    return area * per


grid = list(map(list, map(str.strip, sys.stdin)))
n = len(grid)

visited = set()
total = sum(cost(grid, n, i, j, visited) for i in range(n) for j in range(n))
print(total)
