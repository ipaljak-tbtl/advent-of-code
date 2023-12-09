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
    y_next = sum(dy[-1] for dy in diffs)
    return y_next

sol = 0

for line in sys.stdin:
    sol += solve(parse_line(line))
print(sol)
