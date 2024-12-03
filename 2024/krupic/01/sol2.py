#!/usr/bin/env python3

import sys
from collections import defaultdict

first = []
second = defaultdict(int)

for line in sys.stdin:
    x, y = map(int, line.split())
    first.append(x)
    second[y] += 1

sol = sum(x * second[x] for x in first)
print(sol)

