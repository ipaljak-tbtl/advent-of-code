#!/usr/bin/env python3

import math
import sys

boxes = [tuple(map(int, line.strip().split(","))) for line in sys.stdin]

pairs = []
for i, (x1, y1, z1) in enumerate(boxes):
    for j, (x2, y2, z2) in enumerate(boxes[i + 1:]):
        d = (x2 - x1)**2 + (y2 - y1)**2 + (z2 - z1)**2
        pairs.append((d, i, i + j + 1))
pairs.sort()

boxes = list(range(len(boxes)))
circuits = [{i} for i in range(len(boxes))]

for _, i, j in pairs[:1000]:
    ci, cj = boxes[i], boxes[j]
    if ci != cj:
        for b in circuits[cj]:
            boxes[b] = ci

        circuits[ci] |= circuits[cj]
        circuits[cj].clear()

print(math.prod(l for l in sorted(len(c) for c in circuits)[-3:]))
