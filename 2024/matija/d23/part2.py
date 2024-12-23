#!/usr/bin/env python3

import sys

conns = {}
sets = []

for line in sys.stdin:
    c1, c2 = line.strip().split('-')
    for c in conns.setdefault(c1, set()):
        if c in conns.setdefault(c2, set()):
            sets.append(set((c1, c2, c)))
    conns[c1].add(c2)
    conns.setdefault(c2, set()).add(c1)

max_len = 0
max_set = None
for c, neighs in conns.items():
    new_sets = []
    for s in sets:
        if c not in s:
            for tc in s:
                if tc not in neighs:
                    break
            else:
                s.add(c)
                if s in new_sets:
                    continue
                if len(s) > max_len:
                    max_len = len(s)
                    max_set = s
        new_sets.append(s)
    sets = new_sets

print(','.join(sorted(max_set)))
