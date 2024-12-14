#!/usr/bin/env python3

import sys

cols = 101
rows = 103
time = 100
quad = {(i, j): 0 for i in (0, 1) for j in (0, 1)}

for line in sys.stdin:
    p, v = map(lambda x: map(int, x.split('=')[-1].split(',')), line.split())
    x, y = p
    vx, vy = v
    x = (x + vx * time) % cols
    y = (y + vy * time) % rows
    i = 0 if x < cols//2 else 1 if x > cols//2 else None
    j = 0 if y < rows//2 else 1 if y > rows//2 else None
    if i is not None and j is not None:
        quad[(i, j)] += 1

sol = 1
for x in quad.values():
    sol *= x
print(sol)

