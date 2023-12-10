#!/usr/bin/env python3

import sys
from collections import deque

LOG=False

dirs = {
    'n': (-1, 0),
    's': (1, 0),
    'w': (0, -1),
    'e': (0, 1),
}

cw_dirs = ('n', 'e', 's', 'w')

def right(d):
    i = cw_dirs.index(d)
    return cw_dirs[(i + 1)%4]

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

def adj_pipes_cw(i, j):
    tile = grid[i][j]
    for d in cw_dirs:
        if (adj := connects_to(i, j, d)):
            yield (adj, d)


def traverse_pipe_cw(f):
    last_pipe = start
    cur_pipe, last_dir = next(adj_pipes_cw(*start))
    next_dir_of_start = last_dir
    while cur_pipe != start:
        if LOG: print(f'{last_pipe} -> {cur_pipe} via {last_dir}')
        f(
            last_pipe=last_pipe,
            last_dir=last_dir,
            cur_pipe=cur_pipe,
        )
        next_pipe, next_dir = next((adj, d) for adj, d in adj_pipes_cw(*cur_pipe) if adj != last_pipe)
        last_pipe = cur_pipe
        cur_pipe, last_dir = next_pipe, next_dir
    prev_dir_of_start = last_dir
    f(
        last_pipe=last_pipe,
        last_dir=last_dir,
        cur_pipe=cur_pipe,
    )
    # Fix start based on prev and last dirs
    dirs = prev_dir_of_start+next_dir_of_start
    dir_map = {
        'nn': '|', 'ss':'|',
        'ww':'-', 'ee':'-',
        'nw': '7', 'es': '7',
        'ne': 'F', 'ws:': 'F',
        'sw': 'J', 'en': 'J',
        'se': 'L', 'wn': 'L',
    }
    start_tile = dir_map[dirs]
    print(f'Start is actually {start_tile}')
    i, j = start
    grid[i] = grid[i][:j] + start_tile + grid[i][j+1:]
    

def print_grid(f=None):
    print('#'*80)
    for i, row in enumerate(grid):
        for j, tile in enumerate(row):
            if f and (sym := f(i,j)):
                tile = sym
            print(tile, end='')
        print()
    print('#'*80)
    
pipeline = {start}
traverse_pipe_cw(lambda cur_pipe, **kwargs: pipeline.add(cur_pipe))
print_grid(lambda i,j: '*' if (i,j) in pipeline else None)

inside = set()

def solve_row(i):
    last_open_vertical = None
    is_inside = False

    vertical = '|F7LJ'

    for j, tile in enumerate(grid[i]):
        if LOG: print(f'processing {(i, j)} = {tile}')
        if (i,j) not in pipeline:
            if is_inside:
                inside.add((i,j))
            continue
        # tile is part of pipeline 
        if not tile in vertical:
            # nothing changes
            assert tile == '-'
            assert last_open_vertical is not None
            continue 
        # tile is a vertical pipeline tile
        if tile == '|':
            is_inside = not is_inside
            assert last_open_vertical is None
        elif tile in 'FL':
            # rightwards open vertical - no change yet
            last_open_vertical = tile
        elif tile in '7J':
            # leftwards open vertical
            pair = last_open_vertical + tile
            if pair in ('FJ', 'L7'):
                is_inside = not is_inside
            last_open_vertical = None

for i in range(rows):
    solve_row(i)

print_grid(lambda i,j: 'I' if (i,j) in inside else None)
print(len(inside))

