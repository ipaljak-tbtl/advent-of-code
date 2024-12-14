#!/usr/bin/env python3

import sys

w, h = 101, 103

ps = [[list(map(int, s[2:].split(','))) for s in l.split()] for l in sys.stdin]

grid = [[0 for _ in range(w)] for _ in range(h)]
for [px, py], _ in ps:
    grid[py][px] += 1

for i in range(1, 1_000_000):
    found = False
    for j, [[px, py], [vx, vy]] in enumerate(ps):
        x, y = (px + vx) % w, (py + vy) % h
        ps[j][0] = [x, y]
        grid[py][px] -= 1
        grid[y][x] += 1

        if x + 9 < w and 0 not in grid[y][x:x+10]:
            found = True

    if found:
        for row in grid:
            print(''.join(map(lambda x: 'X' if x else '.', row)))
        print(i)
        break
