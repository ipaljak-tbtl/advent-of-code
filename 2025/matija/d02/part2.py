#!/usr/bin/env python3

import sys

res = 0

for s, e in map(lambda x: map(int, x.split("-")), next(sys.stdin).split(",")):
    for i in range(s, e + 1):
        si = str(i)
        for d in range(1, len(si) // 2 + 1):
            if len(si) % d == 0:
                for c in range(1, len(si) // d):
                    if si[:d] != si[c*d: (c+1)*d]:
                        break
                else:
                    res += i
                    break

print(res)
