#!/usr/bin/env python3

import sys


lines = [l.strip() for l in sys.stdin]
grid = [list(l) for l in lines[:lines.index('')]]
cmds = [c for l in lines[lines.index('')+1:] for c in l]

rows = len(grid)
cols = len(grid[0])

dirs = {'^': (-1, 0), '>': (0, 1), 'v': (1, 0), '<': (0, -1)}

def move(xy, dxy):
    x, y = xy
    dx, dy = dxy
    x += dx
    y += dy
    if 0 <= x < rows and 0 <= y < cols:
        return (x, y), grid[x][y]

def set(pos, v):
    i, j = pos
    grid[i][j] = v

robot = next((i, j) for i in range(rows) for j in range(cols) if grid[i][j] == '@')

for c in cmds:
    assert grid[robot[0]][robot[1]] == '@'
    #for i in range(rows):
    #    print(''.join(grid[i]))
    print(c)
    d = dirs[c]
    n_robot, n_tile = move(robot, d)
    if n_tile == '#':
        continue
    if n_tile == '.':
        set(robot, '.')
        set(n_robot, '@')
        robot = n_robot
        continue
    assert n_tile == 'O'

    free_pos, free_tile = move(n_robot, d)
    while free_tile == 'O':
        free_pos, free_tile = move(free_pos, d)
    if free_tile == '#':
        continue
    assert free_tile == '.'
    set(free_pos, 'O')
    set(robot, '.')
    set(n_robot, '@')
    robot = n_robot

sol = 0
for i in range(rows):
    print(''.join(grid[i]))
    for j in range(cols):
        if grid[i][j] == 'O':
            sol += 100 * i + j

print(sol)

