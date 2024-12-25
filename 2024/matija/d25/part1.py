#!/usr/bin/env python3

import sys

locks = []
keys = []

while True:
    top = next(sys.stdin, None)
    counts = [0] * 5
    for _ in range(5):
        for i, c in enumerate(next(sys.stdin).strip()):
            if c == '#':
                counts[i] += 1

    if top.startswith('#'):
        locks.append(counts)
    else:
        keys.append(counts)

    next(sys.stdin)
    if next(sys.stdin, None) is None:
        break

total = 0
for lock in locks:
    for key in keys:
        for lock_height, key_height in zip(lock, key):
            if lock_height + key_height > 5:
                break
        else:
            total += 1

print(total)
