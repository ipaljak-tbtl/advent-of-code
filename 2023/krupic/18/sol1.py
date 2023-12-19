#!/usr/bin/env python3

import sys
from collections import defaultdict
from queue import Queue

delta = {
    'U': (-1, 0),
    'D': (1, 0),
    'L': (0, -1),
    'R': (0, 1)
}

def parse_line(line):
    d, steps, color = line.strip().split()
    return d, int(steps)

steps = map(parse_line, sys.stdin)
start = (0, 0)
min_i, max_i = 0, 0
min_j, max_j = 0, 0
visited = set([start])
i, j = start

top_left_j = None

for d, n in steps:
    di, dj = delta[d]
    for _ in range(n):
        i += di
        j += dj
        visited.add((i, j))
        min_i = min(min_i, i)
        min_j = min(min_j, j)
        max_i = max(max_i, i)
        max_j = max(max_j, j)

# lmao
top_left_j = min(j for i, j in visited if i == min_i)
start = (min_i + 1, top_left_j + 1)

for i in range(min_i, max_i+1):
    for j in range(min_j, max_j+1):
        sym = '#' if (i,j) in visited else '.'
        if (i,j) == start:
            sym = 'O'
        print(sym, end='')
    print()
for _ in range(10): print()

q = Queue()
q.put(start)
visited.add(start)

while not q.empty():
    i, j = q.get()
    for di, dj in delta.values():
        n = (i + di, j + dj)
        if n not in visited:
            visited.add(n)
            q.put(n)

for i in range(min_i, max_i+1):
    for j in range(min_j, max_j+1):
        print('#' if (i,j) in visited else '.', end='')
    print()
for _ in range(10): print()

sol = len(visited)
print(sol)

