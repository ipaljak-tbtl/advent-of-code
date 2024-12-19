#!/usr/bin/env python3

import sys
from collections import defaultdict

pat = list(input().strip().split(', '))
input()

pat1 = defaultdict(list)

for p in pat:
    pat1[p[0]].append(p)

memo = {}

def rec(design):
    if not design:
        return True

    if design in memo:
        return memo[design]

    for p in pat1[design[0]]:
        if design.startswith(p):
            if rec(design[len(p):]):
                memo[design] = True
                return True
    memo[design] = False
    return False

sol = 0
for line in sys.stdin:
    design = line.strip()
    sol += rec(design)

print(sol)

