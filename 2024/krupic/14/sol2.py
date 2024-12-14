#!/usr/bin/env python3

import sys

cols = 101
rows = 103

pos = []
vel = []

for line in sys.stdin:
    p, v = map(lambda x: tuple(map(int, x.split('=')[-1].split(','))), line.split())
    pos.append(p)
    vel.append(v)

t = 12
while True:
    t += 101

    robots = set()
    for p, v in zip(pos, vel):
        x, y = p
        vx, vy = v
        x = (x + vx * t) % cols
        y = (y + vy * t) % rows
        robots.add((x, y))

    print('=' * (cols + 5))
    for y in range(rows):
        for x in range(cols):
            print('#' if (x, y) in robots else ' ', end='')
        print()
    print('Time: ', t)


