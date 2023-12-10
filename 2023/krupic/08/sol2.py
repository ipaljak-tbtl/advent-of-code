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
start = [node for node in graph if node.endswith('A')]

def step(node, d):
    return graph[node][d]

nodes = start

cycle_lengths = []

for start_node in start:
    sol = 0
    steps_cyc = cycle(steps)
    node = start_node
    while not node.endswith('Z'):
        #print(node)
        s = next(steps_cyc)
        node = step(node, s)
        sol += 1
        #if sol % 1000 == 0:
        #    print(f'{sol} ...')
    print(f'{start_node} -> {node} {sol}')
    end_node = node
    sol2 = 1
    node = step(node, next(steps_cyc))
    while node != end_node:
        node = step(node, next(steps_cyc))
        sol2 += 1
    print(f'{end_node} cycle length {sol2}')
    cycle_lengths.append(sol2)

def gcd(a, b):
    return gcd(b, a % b) if b else a

def lcm(a, b):
    return a // gcd(a, b) * b

sol = 1
for l in cycle_lengths:
    sol = lcm(sol, l)
print(sol)

