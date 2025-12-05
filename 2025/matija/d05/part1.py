#!/usr/bin/env python3

import sys

ranges = []

line = next(sys.stdin).strip()
while line:
    ranges.append(tuple(map(int, line.split("-"))))
    line = next(sys.stdin).strip()

res = 0

for iid in sys.stdin:
    for l, h in ranges:
        if l <= int(iid.strip()) <= h:
            res += 1
            break

print(res)
