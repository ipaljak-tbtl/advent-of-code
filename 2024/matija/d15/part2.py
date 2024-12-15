#!/usr/bin/env python3

import sys


def move(grid, i, j, di):
    ni = i + di

    if grid[ni][j] == '[':
        move(grid, ni, j, di)
    if grid[ni][j] == ']':
        move(grid, ni, j - 1, di)
    if grid[ni][j + 1] == '[':
        move(grid, ni, j + 1, di)

    grid[ni][j:j+2] = ['[', ']']
    grid[i][j:j+2] = ['.'] * 2


def can_move(grid, i, j, di):
    ni = i + di

    if '#' in grid[ni][j:j+2]:
        return False

    res = True

    if grid[ni][j] == '[':
        res = res and can_move(grid, ni, j, di)
    if grid[ni][j] == ']':
        res = res and can_move(grid, ni, j - 1, di)
    if grid[ni][j + 1] == '[':
        res = res and can_move(grid, ni, j + 1, di)

    return res


dms = {
    '^': (-1, 0),
    'v': (1, 0),
    '<': (0, -1),
    '>': (0, 1),
}

grid = []
l, i, j = 0, 0, 0
while line := next(sys.stdin).strip():
    new_line = []
    for k, c in enumerate(line):
        if c == '#':
            new_line.extend(['#'] * 2)
        elif c == 'O':
            new_line.extend(['[', ']'])
        elif c == '.':
            new_line.extend(['.'] * 2)
        else:
            new_line.extend(['@', '.'])
            i, j = l, 2 * k
    grid.append(new_line)
    l += 1

moves = sys.stdin.read().replace('\n', '')

for im, m in enumerate(moves):
    di, dj = dms[m]
    ni, nj = i + di, j + dj

    if grid[ni][nj] == '#':
        continue

    if m in "><" and grid[ni][nj] in "[]":
        bj = nj + dj
        while grid[i][bj] in "[]":
            bj += dj

        if grid[i][bj] == '#':
            continue

        while bj != nj:
            if dj > 0:
                grid[i][bj - dj] = '['
                grid[i][bj] = ']'
            else:
                grid[i][bj] = '['
                grid[i][bj - dj] = ']'

            bj -= 2*dj

    if m in "^v" and grid[ni][nj] in "[]":
        if grid[ni][nj] == '[' and can_move(grid, ni, nj, di):
            move(grid, ni, nj, di)
        elif grid[ni][nj] == ']' and can_move(grid, ni, nj - 1, di):
            move(grid, ni, nj - 1, di)
        else:
            continue

    grid[i][j] = '.'
    grid[ni][nj] = '@'
    i, j = ni, nj

total = 0
for i, row in enumerate(grid):
    for j, c in enumerate(row):
        if c == '[':
            total += 100 * i + j

print(total)
