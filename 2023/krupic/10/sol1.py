#!/usr/bin/env python3

import sys
from collections import deque

dirs = {
    'n': (-1, 0),
    's': (1, 0),
    'w': (0, -1),
    'e': (0, 1),
}

opp = {
    'n': 's',
    's': 'n',
    'w': 'e',
    'e': 'w',
}

ports = {
    '|': ('n', 's'),
    '-': ('w', 'e'),
    'L': ('n', 'e'),
    'J': ('n', 'w'),
    '7': ('s', 'w'),
    'F': ('s', 'e'),
    'S': ('n', 's', 'w', 'e'),
    '.': (),
}

grid = list(map(str.strip, sys.stdin))
rows = len(grid)
columns = len(grid[0])
start = next((i, j) for i in range(rows) for j in range(columns) if grid[i][j] == 'S')

def connects_to(i, j, d): 
    tile = grid[i][j]
    if not d in ports[tile]:
        return None
    di, dj = dirs[d]
    adj_i, adj_j = i + di, j + dj
    if not (0 <= adj_i < rows and 0 <= adj_j < columns):
        return None
    adj_tile = grid[adj_i][adj_j]
    if opp[d] in ports[adj_tile]:
        return (adj_i, adj_j)
    else:
        return None

def adj_tiles(i, j):
    tile = grid[i][j]
    for d in ports[tile]:
        if (adj := connects_to(i, j, d)):
            yield adj
    

visited = {start: 0}
q = deque()
q.append(start)

sol = 0

while q:
    i, j = q.popleft()
    for adj in adj_tiles(i, j):
        if adj not in visited:
            visited[adj] = visited[(i, j)] + 1
            sol = max(sol, visited[adj])
            q.append(adj)

print(sol)

