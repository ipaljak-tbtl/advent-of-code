#!/usr/bin/env python3

import sys

points = []

line = next(sys.stdin).strip()
while line:
    line = line.split("-")
    points.append((int(line[0]), 0))
    points.append((int(line[1]), 1))
    line = next(sys.stdin).strip()

points.sort()

res = 0
cnt = 0
prev = 0

for p, t in points:
    if cnt > 0:
        res += p - prev

    if t == 0:
        cnt += 1
    else:
        if cnt == 1:
            res += 1

        cnt -= 1

    prev = p

print(res)
