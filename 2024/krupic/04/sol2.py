#!/usr/bin/env python3

import sys

grid = [l.strip() for l in sys.stdin]

rows = len(grid)
cols = len(grid[0])

dirs = [(-1, -1), (-1, 1), (1, 1), (1, -1)]

def cw(d):
    return (d + 1) % 4

def opp(d):
    return (d + 2) % 4

def move(xy, dxy):
    x, y = xy
    dx, dy = dxy
    x += dx
    y += dy
    if 0 <= x < rows and 0 <= y < cols:
        return x, y

def match(xy):
    def check(ij, d, c):
        if t := move(ij, dirs[d]):
            i, j = t
            return grid[i][j] == c
        else:
            return False

    x, y = xy
    if grid[x][y] != 'A':
        return False

    for k in range(4):
        m1 = k
        m2 = cw(m1)
        s1 = opp(m1)
        s2 = opp(m2)
        if check(xy, m1, 'M') and check(xy, s1, 'S') and check(xy, m2, 'M') and check(xy, s2, 'S'):
            return True

    return False

sol = 0

for i in range(rows):
    for j in range(cols):
        if match((i, j)):
            sol += 1

print(sol)

