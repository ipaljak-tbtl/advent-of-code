#!/usr/bin/env python3

import sys

dial = 50
cnt = 0

for line in sys.stdin:
    dial = (dial + (1 - 2 * (line[0] == "L")) * int(line[1:])) % 100
    cnt += dial == 0

print(cnt)
