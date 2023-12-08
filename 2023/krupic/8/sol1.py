#!/usr/bin/env python3

import sys
from itertools import cycle

steps = next(sys.stdin).strip()
next(sys.stdin)

def parse_line(line):
    node, adj = line.strip().split(' = ')
    l, r = adj[1:-1].split(', ')
    return node, {'L': l, 'R': r}

graph = dict(map(parse_line, sys.stdin))

def step(node, d):
    return graph[node][d]

sol = 0
node = 'AAA'
steps = cycle(steps)

while node != 'ZZZ':
    print(node)
    node = step(node, next(steps))
    sol += 1
print(sol)

