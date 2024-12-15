#!/usr/bin/env python3

import sys

dms = {
    '^': (-1, 0),
    'v': (1, 0),
    '<': (0, -1),
    '>': (0, 1),
}

grid = []
l, i, j = 0, 0, 0
while line := next(sys.stdin).strip():
    if '@' in line:
        i, j = l, line.index('@')
    grid.append(list(line))
    l += 1

moves = sys.stdin.read().replace('\n', '')

for m in moves:
    di, dj = dms[m]
    ni, nj = i + di, j + dj

    if grid[ni][nj] == '#':
        continue

    if grid[ni][nj] == 'O':
        bi, bj = ni, nj
        while grid[bi + di][bj + dj] == 'O':
            bi, bj = bi + di, bj + dj
        if grid[bi + di][bj + dj] == '#':
            continue
        grid[bi + di][bj + dj] = 'O'

    grid[i][j] = '.'
    grid[ni][nj] = '@'
    i, j = ni, nj

total = 0
for i, row in enumerate(grid):
    for j, c in enumerate(row):
        if c == 'O':
            total += 100 * i + j

print(total)
