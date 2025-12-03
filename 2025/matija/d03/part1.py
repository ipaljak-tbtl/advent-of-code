#!/usr/bin/env python3

import sys

res = 0

for line in sys.stdin:
    bank = list(map(int, list(line.strip())))
    d1 = max(bank[:-1])
    d2 = max(bank[bank.index(d1) + 1:])
    res += 10 * d1 + d2

print(res)
