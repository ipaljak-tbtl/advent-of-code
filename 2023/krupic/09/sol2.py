#!/usr/bin/env python3

import sys

def parse_line(line):
    return list(map(int, line.strip().split()))

def fwd_diff(ys):
    return [y_next - y for y_next, y in zip(ys[1:], ys)]

def solve(ys):
    diffs = [ys]
    while not all(map(lambda y: y == 0, dy := fwd_diff(diffs[-1]))):
        diffs.append(dy)
    acc = 0
    for dys in diffs[::-1]:
        dy = dys[0]
        acc = dy - acc
    return acc

sol = 0

for line in sys.stdin:
    sol += solve(parse_line(line))
print(sol)
