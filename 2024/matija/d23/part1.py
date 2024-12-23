#!/usr/bin/env python3

import sys

conns = {}

total = 0
for line in sys.stdin:
    c1, c2 = line.strip().split('-')
    for c in conns.setdefault(c1, set()):
        if c in conns.setdefault(c2, set()) and 't' in c1[0] + c2[0] + c[0]:
            total += 1
    conns[c1].add(c2)
    conns.setdefault(c2, set()).add(c1)

print(total)
