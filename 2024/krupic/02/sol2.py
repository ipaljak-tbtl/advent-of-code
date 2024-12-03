#!/usr/bin/env python3

import sys

def safe(levels):
    asc = all(1 <= y - x <= 3 for x, y in zip(levels, levels[1:]))
    desc = all(1 <= x - y <= 3 for x, y in zip(levels, levels[1:]))
    return asc or desc

def safe_tolerant(levels):
    if safe(levels):
        return True
    for i in range(len(levels)):
        if safe(levels[:i] + levels[i+1:]):
            return True
    return False

sol = 0
for line in sys.stdin:
    levels = list(map(int, line.split()))
    if safe_tolerant(levels):
        sol += 1

print(sol)

