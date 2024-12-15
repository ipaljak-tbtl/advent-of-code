#!/usr/bin/env python3

import sys

expand = {'#': '##', '.': '..', '@': '@.', 'O': '[]'}

lines = [l.strip() for l in sys.stdin]
grid = [[t2 for t in l for t2 in expand[t]] for l in lines[:lines.index('')]]
cmds = [c for l in lines[lines.index('')+1:] for c in l]

rows = len(grid)
cols = len(grid[0])

for i in range(rows):
    print(''.join(grid[i]))

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

def move_box_h(box, c):
    dj = dirs[c][1]
    i, j = box
    assert (c == '<' and grid[i][j] == ']') or (c == '>' and grid[i][j] == '[')

    free_j = j + 2 * dj
    while grid[i][free_j] in '[]':
        free_j += dj
    if grid[i][free_j] == '#':
        return False
    assert grid[i][free_j] == '.'

    for k in range(free_j, j, -dj):
        set((i, k), grid[i][k-dj])
    set(box, '.')
    return True

def move_box_v(box, c, dry=False):
    assert c in '^v'
    di = dirs[c][0]
    i, j = box
    assert grid[i][j] in '[]'

    j_l = j if grid[i][j] == '[' else j - 1
    j_r = j_l + 1

    if grid[i+di][j_l] == grid[i+di][j_r] == '.':
        if not dry:
            set((i+di, j_l), '[')
            set((i+di, j_r), ']')
            set((i, j_l), '.')
            set((i, j_r), '.')
        return True
    if grid[i+di][j_l] == '#' or grid[i+di][j_r] == '#':
        return False

    if grid[i+di][j_l] in '[]':
        if not move_box_v((i+di, j_l), c, dry=dry):
            return False

    if grid[i+di][j_r] == '[':
        if not move_box_v((i+di, j_r), c, dry=dry):
            return False

    if not dry:
        assert grid[i+di][j_l] == grid[i+di][j_r] == '.'
        set((i+di, j_l), '[')
        set((i+di, j_r), ']')
        set((i, j_l), '.')
        set((i, j_r), '.')
    return True

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
    assert n_tile in '[]'

    if c in '<>':
        if not move_box_h(n_robot, c):
            continue
    else:
        if not move_box_v(n_robot, c, dry=True):
            continue
        move_box_v(n_robot, c)

    set(robot, '.')
    set(n_robot, '@')
    robot = n_robot

sol = 0
for i in range(rows):
    print(''.join(grid[i]))
    for j in range(cols):
        if grid[i][j] == '[':
            sol += 100 * i + j

print(sol)

