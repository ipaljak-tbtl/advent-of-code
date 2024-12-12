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
    per = set()

    while q:
        i, j = q.popleft()
        area += 1

        for di, dj in [(1, 0), (-1, 0), (0, 1), (0, -1)]:
            ni, nj = i + di, j + dj
            if (not (0 <= ni < n) or not (0 <= nj < n)
                    or grid[ni][nj] != grid[i][j]):
                per.add((i, j, di, dj))
            elif (ni, nj) not in visited:
                visited.add((ni, nj))
                q.append((ni, nj))

    sides = 0

    for i, j, di, dj in per:
        if ((di, dj) == (1, 0)
                and ((i, j, 0, -1) in per or (i+1, j-1, 0, 1) in per)):
            sides += 1
        if ((di, dj) == (-1, 0)
                and ((i, j, 0, -1) in per or (i-1, j-1, 0, 1) in per)):
            sides += 1
        if ((di, dj) == (0, 1)
                and ((i, j, -1, 0) in per or (i-1, j+1, 1, 0) in per)):
            sides += 1
        if ((di, dj) == (0, -1)
                and ((i, j, -1, 0) in per or (i-1, j-1, 1, 0) in per)):
            sides += 1

    return area * sides


grid = list(map(list, map(str.strip, sys.stdin)))
n = len(grid)

visited = set()
total = sum(cost(grid, n, i, j, visited) for i in range(n) for j in range(n))
print(total)
