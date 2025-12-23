#!/usr/bin/env python3

from functools import reduce
from itertools import combinations
from operator import xor
import sys

res = 0

for line in map(lambda l: l.strip().split(), sys.stdin):
    end = int(''.join("01"[c == "#"] for c in reversed(line[0][1:-1])), 2)
    wires = [sum(2**int(w) for w in x[1:-1].split(",")) for x in line[1:-1]]

    for k in range(len(wires) + 1):
        for idxs in combinations(range(len(wires)), k):
            if end == reduce(xor, (wires[i] for i in idxs), 0):
                res += k
                break
        else:
            continue
        break

print(res)
