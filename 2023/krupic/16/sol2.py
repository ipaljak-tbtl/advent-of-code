#!/usr/bin/env python3

import sys
from collections import deque, defaultdict

delta = {
    'n': (-1, 0),
    's': (1, 0),
    'w': (0, -1),
    'e': (0, 1)
}

def prop(tile, d):
    if tile == '.':
        return [d]
    if tile == '-':
        return [d] if d in 'we' else ['w', 'e']
    if tile == '|':
        return [d] if d in 'ns' else ['n', 's']
    if tile == '/':
        return {'n': 'e', 'e': 'n', 's': 'w', 'w': 's'}[d]
    if tile == '\\':
        return {'n': 'w', 'w': 'n', 's': 'e', 'e': 's'}[d]

grid = list(map(str.strip, sys.stdin))
rows = len(grid)
cols = len(grid[0])

def next_iter(i, j, d):
    for next_d in prop(grid[i][j], d):
        di, dj = delta[next_d]
        n_i, n_j = i + di, j + dj
        if n_i in range(rows) and n_j in range(cols):
            yield n_i, n_j, next_d

def bfs(start):
    q = deque()
    q.append(start)
    visited = defaultdict(set)
    while q:
        i, j, d = q.popleft()
        if d in visited[(i, j)]:
            continue
        visited[(i, j)].add(d)
        for n in next_iter(i, j, d):
            q.append(n)
    return len(visited)

sol = 0
for i in range(rows):
    sol = max(sol, bfs((i, 0, 'e')))
    sol = max(sol, bfs((i, cols - 1, 'w')))
for j in range(cols):
    sol = max(sol, bfs((0, j, 's')))
    sol = max(sol, bfs((rows - 1, j, 'n')))
print(sol)

