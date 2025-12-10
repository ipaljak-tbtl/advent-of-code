#!/usr/bin/env python3

import sys

lines = [line.strip().split() for line in sys.stdin]

res = [0 if op == "+" else 1 for op in lines[-1]]

for line in lines[:-1]:
    for i, n in enumerate(line):
        res[i] = res[i] + int(n) if lines[-1][i] == "+" else res[i] * int(n)

print(sum(res))
