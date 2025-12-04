#!/usr/bin/env python3

import sys

grid = [list(line.strip()) for line in sys.stdin]

res = 0
found = True
while found:
    found = False
    for i, r in enumerate(grid):
        for j, c in enumerate(r):
            if c == "@":
                cnt = 0
                for di, dj in [(-1, -1), (-1, 0), (-1, 1), (0, -1), (0, 1), (1, -1), (1, 0), (1, 1)]:
                    ti, tj = i + di, j + dj
                    if 0 <= ti < len(grid) and 0 <= tj < len(r) and grid[ti][tj] == "@":
                        cnt += 1
                        if cnt >= 4:
                            break
                else:
                    res += 1
                    grid[i][j] = '.'
                    found = True

print(res)
