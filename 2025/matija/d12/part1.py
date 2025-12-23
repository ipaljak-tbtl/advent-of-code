#!/usr/bin/env python3

import sys

shapes = []

for _ in range(6):
    line = next(sys.stdin)
    cnt = sum(next(sys.stdin).count("#") for _ in range(3))
    shapes.append(cnt)
    line = next(sys.stdin)

res = 0

for line in map(lambda l: l.strip().split(), sys.stdin):
    w, l = line[0][:-1].split("x")
    total = sum(int(n) * a for n, a in zip(line[1:], shapes))

    if total <= int(w) * int(l):
        res += 1

print(res)
