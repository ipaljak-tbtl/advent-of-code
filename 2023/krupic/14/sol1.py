#!/usr/bin/env python3

import sys

def solve(col):
    l = len(col)
    load = 0
    lowest_empty = 0
    for i, tile in enumerate(col):
        if tile == 'O':
            load += l - lowest_empty
            lowest_empty += 1
        elif tile == '#':
            lowest_empty = i + 1
    return load

grid = map(str.rstrip, sys.stdin)

sol = sum(solve(col) for col in zip(*grid))
print(sol)

