#!/usr/bin/env python3

import sys

dial = 50
cnt = 0

for line in sys.stdin:
    d, n = line[0], int(line[1:])

    cnt += n // 100
    n %= 100

    cnt += d == "R" and dial + n >= 100 or d == "L" and dial != 0 and dial <= n
    dial = (dial + (1 - 2 * (d == "L")) * n) % 100

print(cnt)
