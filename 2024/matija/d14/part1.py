#!/usr/bin/env python3

import sys

w, h = 101, 103

q1, q2, q3, q4 = 0, 0, 0, 0

for line in sys.stdin:
    [px, py], [vx, vy] = [map(int, s[2:].split(',')) for s in line.split()]
    x, y = (px + 100 * vx) % w, (py + 100*vy) % h
    if x < w // 2 and y < h // 2:
        q1 += 1
    elif x < w // 2 and y > h // 2:
        q2 += 1
    elif x > w // 2 and y < h // 2:
        q3 += 1
    elif x > w // 2 and y > h // 2:
        q4 += 1

print(q1 * q2 * q3 * q4)
