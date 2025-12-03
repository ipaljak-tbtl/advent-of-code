#!/usr/bin/env python3

import sys

res = 0

for line in sys.stdin:
    bank = list(map(int, list(line.strip())))

    si = 0
    for i in range(11, -1, -1):
        mi = si
        for j in range(si + 1, len(bank) - i):
            if bank[j] > bank[mi]:
                mi = j

        res += bank[mi] * 10**i
        si = mi + 1

print(res)
