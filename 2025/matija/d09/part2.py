#!/usr/bin/env python3

import sys

tiles = [tuple(map(int, line.strip().split(","))) for line in sys.stdin]

for i, (x, y) in enumerate(tiles[:-1]):
    if tiles[i+1][0] > x + 50_000:
        (t1x, t1y), (t2x, t2y) = tiles[i+1], tiles[i+2]
        break

hor, ver = {}, {}
for (x1, y1), (x2, y2) in zip(tiles[:-1], tiles[1:]):
    if y1 == y2:
        hor[y1] = (min(x1, x2), max(x1, x2))
    if x1 == x2:
        ver[x1] = (min(y1, y2), max(y1, y2))

max_area = 0

my = t1y + 1
while not (my in hor and hor[my][0] < t1x <= hor[my][1]):
    my += 1

mx = hor[my][0] - 1
while not (mx in ver and ver[mx][0] < my <= ver[mx][1]):
    mx -= 1
my = ver[mx][0]

for x, y in tiles[tiles.index((mx, my))-3:]:
    if y <= t1y:
        break

    if y <= my:
        cy = y - 1
        while not (cy in hor and hor[cy][0] <= x < hor[cy][1]):
            cy -= 1

        if cy == t1y:
            max_area = max(max_area, (t1x - x + 1) * (y - t1y + 1))

my = t2y - 1
while not (my in hor and hor[my][0] < t2x <= hor[my][1]):
    my -= 1

mx = hor[my][0] - 1
while not (mx in ver and ver[mx][0] <= my < ver[mx][1]):
    mx -= 1
my = ver[mx][1]

for x, y in tiles[tiles.index((mx, my))+3::-1]:
    if y >= t1y:
        break

    if y >= my:
        cy = y + 1
        while not (cy in hor and hor[cy][0] <= x < hor[cy][1]):
            cy += 1

        if cy == t2y:
            max_area = max(max_area, (t2x - x + 1) * (t2y - y + 1))

print(max_area)
