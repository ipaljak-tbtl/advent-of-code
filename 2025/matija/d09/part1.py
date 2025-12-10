#!/usr/bin/env python3

import sys

tiles = [tuple(map(int, line.strip().split(","))) for line in sys.stdin]

area = 0
for i, (x1, y1) in enumerate(tiles):
    for x2, y2 in tiles[i + 1:]:
        area = max(area, (abs(x2 - x1) + 1) * (abs(y2 - y1) + 1))

print(area)
