#!/usr/bin/env python3

import sys

grid = list(map(str.strip, sys.stdin))
rows = len(grid)
cols = len(grid[0])
galaxies = [(i,j) for i in range(rows) for j in range(cols) if grid[i][j] == '#']

empty_rows = [i for i in range(rows) if all(map(lambda x: x == '.', grid[i]))]
empty_cols = [j for j in range(cols) if all(grid[i][j] == '.' for i in range(rows))]

#print(galaxies)
#print(empty_rows)
#print(empty_cols)
xs, ys = map(sorted, zip(*galaxies))

sol = 0

factor = 1000000

for i, x_larger in enumerate(xs):
    for x_smaller in xs[:i]:
        expansion = sum(1 for x in empty_rows if x_smaller < x < x_larger)
        sol += x_larger - x_smaller + expansion * (factor - 1)


for i, y_larger in enumerate(ys):
    for y_smaller in ys[:i]:
        expansion = sum(1 for y in empty_cols if y_smaller < y < y_larger)
        sol += y_larger - y_smaller + expansion * (factor - 1)

print(sol)

