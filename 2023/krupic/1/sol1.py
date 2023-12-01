#!/usr/bin/env python3

import sys

sol = 0

for line in sys.stdin:
    first = None
    last = None
    for c in line:
        if c.isdigit():
            last = c
            if not first:
                first = c
    print(first+last)
    sol += int(first+last)
print(sol)
