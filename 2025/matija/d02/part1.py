#!/usr/bin/env python3

import sys

res = 0

for s, e in map(lambda x: map(int, x.split("-")), next(sys.stdin).split(",")):
    for i in range(s, e + 1):
        si = str(i)
        if si[:len(si) // 2] == si[len(si) // 2:]:
            res += i

print(res)
