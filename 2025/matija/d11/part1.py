#!/usr/bin/env python3

import sys

devices = {line[0][:-1]: set(line[1:])
           for line in map(lambda l: l.strip().split(), sys.stdin)}

res = 0

q = ["you"]
while q:
    device = q.pop()

    if device == "out":
        res += 1
        continue

    q.extend(devices[device])

print(res)
