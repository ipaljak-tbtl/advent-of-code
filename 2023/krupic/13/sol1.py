#!/usr/bin/env python3

import sys

def solve(pat):
    r, c = len(pat), len(pat[0])
    if (s := solve_horiz(pat)) is not None:
        return 100 * s
    else:
        pat = list(zip(*pat))
        return solve_horiz(pat)

def solve_horiz(pat):
    rows = len(pat)
    for i in range(1, rows):
        l = min(i, rows - i) 
        if pat[i-l:i] == pat[i+l-1:i-1:-1]:
            print(i)
            return i

sol = 0
pat = []
for line in map(str.rstrip, sys.stdin):
    if line:
        pat.append(line)
    else:
        sol += solve(pat)
        pat = []
sol += solve(pat)
print(sol)

