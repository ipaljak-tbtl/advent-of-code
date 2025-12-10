#!/usr/bin/env python3

import math
import sys

lines = [line.rstrip("\n") for line in sys.stdin]

res = 0

j = len(lines[0]) - 1
ns = []
while j >= 0:
    ns.append(int("".join(lines[i][j] for i in range(len(lines) - 1)).strip()))

    if lines[-1][j] != " ":
        res += sum(ns) if lines[-1][j] == "+" else math.prod(ns)
        j -= 1
        ns.clear()

    j -= 1

print(res)
