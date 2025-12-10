#!/usr/bin/env python3

import sys

grid = [list(line.strip()) for line in sys.stdin]
for i, row in enumerate(grid):
    for j, c in enumerate(row):
        grid[i][j] = (c, 0)

grid[0][len(grid[0]) // 2] = ("|", 1)

cnt = 0
for i, row in enumerate(grid[:-1]):
    for j, (c, n) in enumerate(row):
        if c == "|":
            if grid[i + 1][j][0] == "^":
                grid[i + 1][j - 1] = ("|", grid[i + 1][j - 1][1] + n)
                grid[i + 1][j + 1] = ("|", grid[i + 1][j + 1][1] + n)
            else:
                grid[i + 1][j] = ("|", grid[i + 1][j][1] + n)

print(sum(n for _, n in grid[-1]))
