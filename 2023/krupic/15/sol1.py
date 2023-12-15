#!/usr/bin/env python3

import sys

def my_hash(s):
    h = 0
    for c in s:
        h = ((h + ord(c)) * 17) & 255
    return h

strs = next(sys.stdin).strip().split(',')
sol = sum(map(my_hash, strs))
print(sol)

