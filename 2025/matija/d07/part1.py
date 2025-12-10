#!/usr/bin/env python3

import sys

grid = [list(line.strip()) for line in sys.stdin]

grid[0][len(grid[0]) // 2] = "|"

cnt = 0
for i, row in enumerate(grid[:-1]):
    for j, c in enumerate(row):
        if c == "|":
            if grid[i + 1][j] == "^":
                grid[i + 1][j - 1] = "|"
                grid[i + 1][j + 1] = "|"
                cnt += 1
            else:
                grid[i + 1][j] = "|"

print(cnt)
