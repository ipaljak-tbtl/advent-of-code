#!/usr/bin/env python3

import sys

first = []
second = []

for line in sys.stdin:
    x, y = map(int, line.split())
    first.append(x)
    second.append(y)

sol = sum(abs(x - y) for x, y in zip(sorted(first), sorted(second)))
print(sol)

