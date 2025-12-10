#!/usr/bin/env python3

import sys

boxes = [tuple(map(int, line.strip().split(","))) for line in sys.stdin]

pairs = []
for i, (x1, y1, z1) in enumerate(boxes):
    for j, (x2, y2, z2) in enumerate(boxes[i + 1:]):
        d = (x2 - x1)**2 + (y2 - y1)**2 + (z2 - z1)**2
        pairs.append((d, i, i + j + 1))
pairs.sort()

boxes = [[i, x] for i, (x, _, _) in enumerate(boxes)]
circuits = [{i} for i in range(len(boxes))]

n_circuits = len(circuits)
for _, i, j in pairs:
    ci, cj = boxes[i][0], boxes[j][0]
    if ci != cj:
        for b in circuits[cj]:
            boxes[b][0] = ci

        circuits[ci] |= circuits[cj]
        circuits[cj].clear()

        n_circuits -= 1
        if n_circuits == 1:
            print(boxes[i][1] * boxes[j][1])
            break
