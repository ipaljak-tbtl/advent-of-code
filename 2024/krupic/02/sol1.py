#!/usr/bin/env python3

import sys

def safe(levels):
    asc = all(1 <= y - x <= 3 for x, y in zip(levels, levels[1:]))
    desc = all(1 <= x - y <= 3 for x, y in zip(levels, levels[1:]))
    return asc or desc

sol = 0
for line in sys.stdin:
    levels = list(map(int, line.split()))
    if safe(levels):
        sol += 1

print(sol)

